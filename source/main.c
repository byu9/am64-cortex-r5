/*
 * John Yu
 * April 7 2025
 * byu9@ncsu.edu
 */
#include "epwm_registers.h"

void set_pwm_duty(float a, float b, float c);

static void claim_device_pwm_pins(void);
static void configure_three_phase_pwm(void);

void main(void)
{

    /*
     * Before running this program the EPWM Time Base Clocks need to be enabled in Linux.
     * Write 0x1FF into register 0x43004130 using the following command:
     *
     *     devmem2 0x43004130 w 0x1FF
     *
     * Since the above register is not visible by default in the Cortex-R5 memory map, we need to
     * configure RAT to translate the address before we can access. For now we access the register
     * through Linux.
     */

    claim_device_pwm_pins();
    configure_three_phase_pwm();

    set_pwm_duty(0.1f, 0.2f, 0.3f);
    set_pwm_duty(0.4f, 0.5f, 0.6f);
    set_pwm_duty(0.7f, 0.8f, 0.9f);
    set_pwm_duty(0.0f, 0.0f, 0.0f);
    set_pwm_duty(1.0f, 1.0f, 1.0f);


    for (;;)
        ;
}


static void claim_device_pwm_pins(void)
{
    /*
     * List of enslaved pins on the device
     *
     * | Signal | PADCONFIG       | MUX Mode | BGA Ball | EVM User Connector |
     * | EPWM4A | 0x000F4088 (34) | 3        | R18      | 32                 |
     * | EPWM4B | 0x000F408C (35) | 3        | T21      | 33                 |
     * | EPWM5A | 0x000F4094 (37) | 3        | T19      | 29                 |
     * | EPWM5B | 0x000F4098 (38) | 3        | W19      | 31                 |
     * | EPWM6A | 0x000F40A0 (40) | 8        | N16      | 18                 |
     * | EPWM6B | 0x000F40A4 (41) | 8        | N17      | 22                 |
     */

     volatile uint32_t *const padconfig34 = (volatile uint32_t*) 0x000F4088;
     volatile uint32_t *const padconfig35 = (volatile uint32_t*) 0x000F408C;
     volatile uint32_t *const padconfig37 = (volatile uint32_t*) 0x000F4094;
     volatile uint32_t *const padconfig38 = (volatile uint32_t*) 0x000F4098;
     volatile uint32_t *const padconfig40 = (volatile uint32_t*) 0x000F40A0;
     volatile uint32_t *const padconfig41 = (volatile uint32_t*) 0x000F40A4;

     *padconfig34 = 0x00000000 | 3;
     *padconfig35 = 0x00000000 | 3;
     *padconfig37 = 0x00000000 | 3;
     *padconfig38 = 0x00000000 | 3;
     *padconfig40 = 0x00000000 | 8;
     *padconfig41 = 0x00000000 | 8;
}


#define PWM_FREQ_HZ           (10000)
#define EPWM_TBCLK_FREQ_HZ    (250000000)
#define EPWM_PERIOD_REG       (EPWM_TBCLK_FREQ_HZ / PWM_FREQ_HZ / 2)

static void stop_epwm_counter(volatile struct EPWM_REGS *epwm_inst);
static void start_epwm_counter_in_up_down_mode(volatile struct EPWM_REGS *epwm_inst);
static void configure_epwm_timebase(volatile struct EPWM_REGS *epwm_inst);
static void configure_epwm_compare_channels(volatile struct EPWM_REGS *epwm_inst);
static void synchronize_epwm_submodules(void);

static void configure_three_phase_pwm(void)
{
    stop_epwm_counter(EPWM4);
    stop_epwm_counter(EPWM5);
    stop_epwm_counter(EPWM6);

    configure_epwm_timebase(EPWM4);
    configure_epwm_timebase(EPWM5);
    configure_epwm_timebase(EPWM6);

    configure_epwm_compare_channels(EPWM4);
    configure_epwm_compare_channels(EPWM5);
    configure_epwm_compare_channels(EPWM6);

    synchronize_epwm_submodules();

    start_epwm_counter_in_up_down_mode(EPWM4);
    start_epwm_counter_in_up_down_mode(EPWM5);
    start_epwm_counter_in_up_down_mode(EPWM6);
}

static void stop_epwm_counter(volatile struct EPWM_REGS *epwm_inst)
{
    epwm_inst->TBCTL.CTRMODE = 3;
}

static void start_epwm_counter_in_up_down_mode(volatile struct EPWM_REGS *epwm_inst)
{
    epwm_inst->TBCTL.CTRMODE = 2;
}

static void synchronize_epwm_submodules(void)
{
    /*
     * Synchronize EPWM4, EPWM5, EPWM6.
     *
     * The synchronization input/output pair for each EPWM submodule can be used to synchronize
     * the operation of multiple EPWM channel pairs. We use EPWM4 to generate the synchronization
     * signal when its counter reaches zero. The synchronization signal is piped into EPWM5,
     * triggering a reload of its counter with the value of its phase register TBPHS, which is set
     * to zero, before being mirrored on the synchronization output of EPWM5, where it gets piped
     * into EPWM6 and does the same thing again.
     */
    EPWM4->TBPHS = 0;
    EPWM5->TBPHS = 0;
    EPWM6->TBPHS = 0;

    EPWM4->TBCTL.SYNCOSEL = 1; // EPWM4 SYNCOUT will emit when its counter reaches zero.
    EPWM5->TBCTL.SYNCOSEL = 0; // EPWM5 SYNCOUT will mirror the signal on its SYNCIN (from EPWM4).
    EPWM6->TBCTL.SYNCOSEL = 0; // EPWM6 SYNCOUT will mirror the signal on its SYNCIN (from EPWM5).

    EPWM4->TBCTL.PHSEN = 0; // EPWM4 does nothing when receiving a signal on its SYNCIN.
    EPWM5->TBCTL.PHSEN = 1; // EPWM5 reloads its counter from TBPHS when receiving SYNCIN.
    EPWM6->TBCTL.PHSEN = 1; // EPWM6 reloads its counter from TBPHS when receiving SYNCIN.

    EPWM4->TBCTL.PHSDIR = 1; // EPWM4 counter counts up after receiving SYNCIN.
    EPWM5->TBCTL.PHSDIR = 1; // EPWM5 counter counts up after receiving SYNCIN.
    EPWM6->TBCTL.PHSDIR = 1; // EPWM6 counter counts up after receiving SYNCIN.

    EPWM4->TBCTL.SWFSYNC = 1; // Triggers a once-off synchronization from EPWM4.
}

static void configure_epwm_timebase(volatile struct EPWM_REGS *epwm_inst)
{
    /*
     * Time Base Configuration
     *
     * For an intuitive illustration, see Figure 12-2233 in the Reference Manual SPRUIM2H.
     * We begin from left to right in the figure, starting from the counter clock source,
     * proceeding with configuration of the counter mode, followed by counter period, and
     * ending with miscellaneous items related to the counter.
     */

    // Clears all flags in the counter status register by writing 1.
    epwm_inst->TBSTS.SYNCI = 1;
    epwm_inst->TBSTS.CTRMAX = 1;

    /*
     * Counter clock pre-scaler
     *
     * For EPWM peripheral functional and interface clock FICLK, the counter clock frequency TBCLK
     * is given by TBCLK = FICLK / division_of(CLKDIV) / division_of(HSPCLKDIV).
     */
    epwm_inst->TBCTL.HSPCLKDIV = 0; // Divides by 1
    epwm_inst->TBCTL.CLKDIV = 0;    // Divides by 1

    /*
     * Counter mode configuration
     *
     * We configure the counter in up-down mode. The counter starts counting from 0, reaching the
     * value of the period register TBPRD, when it switches direction and counts down, reaching
     * zero again. The process then repeats.
     */
    epwm_inst->TBCNT = 0;           // Clears the counter to 0.
    epwm_inst->TBCTL.FREE_SOFT = 3; // Makes counter free-running when the debugger is halted.

    /*
     * Counter period configuration
     *
     * We configure the period register in shadow mode, in which the period updates, if any, are
     * deferred until the counter completes a full up-down cycle. Compared to non-shadow mode when
     * the period is updated immediately upon a write access to the TBPRD, operating in shadow mode
     * results in a deterministic glitch-free behavior.
     *
     * The PWM period is given by period_of(PWM) = 2 * period_of(TBCLK) * value_of(TBPRD)
     */
    epwm_inst->TBCTL.PRDLD = 0;           // Counter period register is set to shadow mode.
    epwm_inst->TBPRD = EPWM_PERIOD_REG;   // Counter period.
}

static void configure_epwm_compare_channels(volatile struct EPWM_REGS *epwm_inst)
{
    /*
     * Compare Channel Configuration
     * For an intuitive illustration, see Figure 12-2241 in the Reference Manual SPRUIM2H.
     */

    /*
     * Compare register mode configuration.
     *
     * We configure the compare registers in shadow mode, in which the updates are deferred
     * until the PWM completes a full cycle. Compared to non-shadow mode when the duty cycle is
     * updated immediately upon a write access to the compare registers, operating in shadow mode
     * results in a deterministic glitch-free behavior.
     */

    // Clears values in the compare registers.
    epwm_inst->CMPA = 0;
    epwm_inst->CMPB = 0;

    epwm_inst->CMPCTL.SHDWAMODE = 0; // Compare register A set to shadow mode.
    epwm_inst->CMPCTL.SHDWBMODE = 0; // Compare register B set to shadow mode.

    epwm_inst->CMPCTL.LOADAMODE = 0; // A channel shadow transfer occurs when counter reaches zero.
    epwm_inst->CMPCTL.LOADBMODE = 0; // B channel shadow transfer occurs when counter reaches zero.

    /*
     * Channel action qualifier configuration
     *
     * This section configures the action taken by channel A and B when the hardware compare event
     * occurs on the corresponding channel.
     */
    epwm_inst->AQCTLA.ZRO = 0; // Do nothing on channel A when the counter reaches zero.
    epwm_inst->AQCTLA.PRD = 0; // Do nothing on channel A when the counter reaches the period.
    epwm_inst->AQCTLA.CAU = 2; // A=LO when A compare event occurs during counter up.
    epwm_inst->AQCTLA.CAD = 1; // A=HI when A compare event occurs during counter down.
    epwm_inst->AQCTLA.CBU = 0; // A does nothing when B compare event occurs during counter up.
    epwm_inst->AQCTLA.CBD = 0; // A does nothing when B compare event occurs during counter down.

    epwm_inst->AQCTLB.ZRO = 0; // Do nothing on channel B when the counter reaches zero.
    epwm_inst->AQCTLB.PRD = 0; // Do nothing on channel B when the counter reaches the period.
    epwm_inst->AQCTLB.CAU = 0; // B does nothing when A compare event occurs during counter up.
    epwm_inst->AQCTLB.CAD = 0; // B does nothing when A compare event occurs during counter down.
    epwm_inst->AQCTLB.CBU = 1; // B=HI when B compare event occurs during counter up.
    epwm_inst->AQCTLB.CBD = 2; // B=LO when B compare event occurs during counter down.

    epwm_inst->AQSFRC.ACTSFA = 1; // A=LO when once-off software action is triggered.
    epwm_inst->AQSFRC.ACTSFB = 1; // B=LO when once-off software action is triggered.

    epwm_inst->AQSFRC.OTSFA = 1; // Triggers software action on A to reset channel.
    epwm_inst->AQSFRC.OTSFB = 1; // Triggers software action on B to reset channel.
}


static uint16_t duty_to_compare_reg(float duty)
{
    /*
     * Note
     *
     * Conversion from floating point to integer type is IMPLEMENTATION-DEFINED behavior in C if
     * the floating point is out of the range of the integer type. Failure to range check floating
     * point before conversion results in a bug and will cause the source code to fail functional
     * safety certification related to IEC61508 and ISO26262. This is important if we are making
     * an automotive or medical device.
     *
     * John Yu
     * byu9@ncsu.edu
     * April 9 2025
     */

    // This will take care of the NaN case.
    duty = (duty == duty)? duty : 0.0f;

    // This will take care of the out-of-range and infinity case
    duty = (duty > 1.0f)? 1.0f : duty;
    duty = (duty < 0.0f)? 0.0f : duty;

    const uint16_t compare_reg = (uint16_t) ((1.0f - duty) * EPWM_PERIOD_REG);
    return compare_reg;
}

void set_pwm_duty(float a, float b, float c)
{
    const uint16_t compare_a = duty_to_compare_reg(a);
    const uint16_t compare_b = duty_to_compare_reg(b);
    const uint16_t compare_c = duty_to_compare_reg(c);

    EPWM4->CMPA = compare_a;
    EPWM4->CMPB = compare_a;

    EPWM5->CMPA = compare_b;
    EPWM5->CMPB = compare_b;

    EPWM6->CMPA = compare_c;
    EPWM6->CMPB = compare_c;
}
