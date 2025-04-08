/*
 * EPWM Register Definitions for AM6442
 *
 * Note
 * ----
 *
 * The EPWM driver provided by TI through the "MCU PLUS SDK" package has too
 * many dependencies and I decided not to use it.
 *
 * The EPWM on the F2806x appears to be similar to the EPWM on the AM6442. This
 * file is copied from the F2806x and I have made changes in the bit field
 * definitions to match the AM6442 reference manual.
 *
 * John Yu
 * April 7 2025
 * byu9@ncsu.edu
 */

/*
 * Original file signature
 */
//###########################################################################
// $TI Release: F2806x C/C++ Header Files and Peripheral Examples V136 $
// $Release Date: Apr 15, 2013 $
//###########################################################################
#ifndef HF91746F8_CFA9_4690_AEB0_0D7D4E402D80
#define HF91746F8_CFA9_4690_AEB0_0D7D4E402D80

#include <stdint.h>

#define EPWM0  ((volatile struct EPWM_REGS*) 0x23000000UL)
#define EPWM1  ((volatile struct EPWM_REGS*) 0x23010000UL)
#define EPWM2  ((volatile struct EPWM_REGS*) 0x23020000UL)
#define EPWM3  ((volatile struct EPWM_REGS*) 0x23030000UL)
#define EPWM4  ((volatile struct EPWM_REGS*) 0x23040000UL)
#define EPWM5  ((volatile struct EPWM_REGS*) 0x23050000UL)
#define EPWM6  ((volatile struct EPWM_REGS*) 0x23060000UL)
#define EPWM7  ((volatile struct EPWM_REGS*) 0x23070000UL)
#define EPWM8  ((volatile struct EPWM_REGS*) 0x23080000UL)


__attribute__((aligned, packed))
struct TBCTL_REG
{
    uint16_t CTRMODE:2;   // 1:0   Counter Mode
    uint16_t PHSEN:1;     // 2:2   Phase Load Enable
    uint16_t PRDLD:1;     // 3:3   Active Period Load
    uint16_t SYNCOSEL:2;  // 5:4   Sync Output Select
    uint16_t SWFSYNC:1;   // 6:6   Software Force Sync Pulse
    uint16_t HSPCLKDIV:3; // 9:7   High Speed Time-Base Clock Pre-scaler
    uint16_t CLKDIV:3;    // 12:10 Time-Base Clock Pre-scaler
    uint16_t PHSDIR:1;    // 13:13 Phase Direction Bit
    uint16_t FREE_SOFT:2; // 15:14 Emulation Mode Bits
};

__attribute__((aligned, packed))
struct TBSTS_REG
{
    uint16_t CTRDIR:1;     // 0:0  Counter Direction Status
    uint16_t SYNCI:1;      // 1:1  External Input Sync Status
    uint16_t CTRMAX:1;     // 2:2  Counter Max Latched Status
    uint16_t reserved1:13; // 15:3 Reserved
};

__attribute__((aligned, packed))
struct CMPCTL_REG
{
    uint16_t LOADAMODE:2; // 1:0   Active Compare A Load
    uint16_t LOADBMODE:2; // 3:2   Active Compare B Load
    uint16_t SHDWAMODE:1; // 4:4   Compare A Register Operating Mode
    uint16_t reserved1:1; // 5:5   Reserved
    uint16_t SHDWBMODE:1; // 6:6   Compare B Register Operating Mode
    uint16_t reserved2:1; // 7:7   Reserved
    uint16_t SHDWAFULL:1; // 8:8   Compare A Shadow Register Full Status
    uint16_t SHDWBFULL:1; // 9:9   Compare B Shadow Register Full Status
    uint16_t reserved3:6; // 15:10 reserved
};

__attribute__((aligned, packed))
struct AQCTL_REG
{
    uint16_t ZRO:2;       // 1:0    Action Counter = Zero
    uint16_t PRD:2;       // 3:2    Action Counter = Period
    uint16_t CAU:2;       // 5:4    Action Counter = Compare A Up
    uint16_t CAD:2;       // 7:6    Action Counter = Compare A Down
    uint16_t CBU:2;       // 9:8    Action Counter = Compare B Up
    uint16_t CBD:2;       // 11:10  Action Counter = Compare B Down
    uint16_t reserved1:4; // 15:12  Reserved
};

__attribute__((aligned, packed))
struct AQSFRC_REG
{
    uint16_t ACTSFA:2;    // 1:0  Action when One-time SW Force A Invoked
    uint16_t OTSFA:1;     // 2:2  One-time SW Force A Output
    uint16_t ACTSFB:2;    // 4:3  Action when One-time SW Force B Invoked
    uint16_t OTSFB:1;     // 5:5  One-time SW Force A Output
    uint16_t RLDCSF:2;    // 7:6  Reload from Shadow Options
    uint16_t reserved1:8; // 15:8 Reserved
};

__attribute__((aligned, packed))
struct AQCSFRC_REG
{
    uint16_t CSFA:2;       // 1:0  Continuous Software Force on output A
    uint16_t CSFB:2;       // 3:2  Continuous Software Force on output B
    uint16_t reserved1:12; // 15:4 Reserved
};

__attribute__((aligned, packed))
struct DBCTL_REG
{
    uint16_t OUT_MODE:2;   // 1:0  Dead Band Output Mode Control
    uint16_t POLSEL:2;     // 3:2  Polarity Select Control
    uint16_t IN_MODE:2;    // 5:4  Dead Band Input Select Mode Control
    uint16_t reserved1:10; // 15:6 Reserved
};

__attribute__((aligned, packed))
struct TZSEL_REG
{
    uint16_t CBC0:1;      // 0:0 TZ0 CBC select
    uint16_t CBC1:1;      // 1:1 TZ1 CBC select
    uint16_t CBC2:1;      // 2:2 TZ2 CBC select
    uint16_t CBC3:1;      // 3:3 TZ3 CBC select
    uint16_t CBC4:1;      // 4:4 TZ4 CBC select
    uint16_t CBC5:1;      // 5:5 TZ5 CBC select
    uint16_t reserved1:2; // 7:6 Reserved

    uint16_t OSHT0:1;     // 8:8   One-shot TZ0 select
    uint16_t OSHT1:1;     // 9:9   One-shot TZ1 select
    uint16_t OSHT2:1;     // 10:10 One-shot TZ2 select
    uint16_t OSHT3:1;     // 11:11 One-shot TZ3 select
    uint16_t OSHT4:1;     // 12:12 One-shot TZ4 select
    uint16_t OSHT5:1;     // 13:13 One-shot TZ5 select
    uint16_t reserved2:2; // 15:14 Reserved
};

__attribute__((aligned, packed))
struct TZCTL_REG
{
    uint16_t TZA:2;        // 1:0  TZ1 to TZ6 Trip Action On EPWMxA
    uint16_t TZB:2;        // 3:2  TZ1 to TZ6 Trip Action On EPWMxB
    uint16_t reserved1:12; // 15:4 Reserved
};

__attribute__((aligned, packed))
struct TZEINT_REG
{
    uint16_t reserved1:1;  // 0:0  Reserved
    uint16_t CBC:1;        // 1:1  Trip Zones Cycle-By-Cycle Interrupt Enable
    uint16_t OST:1;        // 2:2  Trip Zones One-Shot Interrupt Enable
    uint16_t reserved2:13; // 15:3 Reserved
};

__attribute__((aligned, packed))
struct TZFLG_REG
{
    uint16_t INT:1;        // 0:0  Global Int Status Flag
    uint16_t CBC:1;        // 1:1  Trip Zones Cycle By Cycle Flag
    uint16_t OST:1;        // 2:2  Trip Zones One Shot Flag
    uint16_t reserved1:13; // 15:3 Reserved
};

__attribute__((aligned, packed))
struct TZCLR_REG
{
    uint16_t INT:1;        // 0:0  Global Int Status Flag
    uint16_t CBC:1;        // 1:1  Trip Zones Cycle By Cycle Flag
    uint16_t OST:1;        // 2:2  Trip Zones One Shot Flag
    uint16_t reserved1:13; // 15:3 Reserved
};

__attribute__((aligned, packed))
struct TZFRC_REG
{
    uint16_t reserved1:1;  // 0:0  Reserved
    uint16_t CBC:1;        // 1:1  Trip Zones Cycle By Cycle Flag
    uint16_t OST:1;        // 2:2  Trip Zones One Shot Flag
    uint16_t reserved2:13; // 15:3 Reserved
};

__attribute__((aligned, packed))
struct ETSEL_REG
{
    uint16_t INTSEL:3;    // 2:0   EPWMxINTn Select
    uint16_t INTEN:1;     // 3:3   EPWMxINTn Enable
    uint16_t reserved1:4; // 7:4   Reserved
    uint16_t SOCASEL:3;   // 10:8  SOCA Selection Options
    uint16_t SOCA:1;      // 11:11 SOCA Enable
    uint16_t SOCBSEL:3;   // 14:12 SOCB Selection Options
    uint16_t SOCB:1;      // 15:15 SOCB Enable
};

__attribute__((aligned, packed))
struct ETPS_REG
{
    uint16_t INTPRD:2;    // 1:0   EPWMxINTn Period Select
    uint16_t INTCNT:2;    // 3:2   EPWMxINTn Counter Register
    uint16_t reserved1:4; // 7:4   Reserved
    uint16_t SOCAPRD:2;   // 9:8   SOCA Period Select
    uint16_t SOCACNT:2;   // 11:10 SOCA Counter Register
    uint16_t SOCBPRD:2;   // 13:12 SOCB Period Select
    uint16_t SOCBCNT:2;   // 15:14 SOCB Counter Register
};

__attribute__((aligned, packed))
struct ETFLG_REG
{
    uint16_t INT:1;        // 0:0  EPWMxINTn Flag
    uint16_t reserved1:1;  // 1:1  Reserved
    uint16_t SOCA:1;       // 2:2  Latched SOCA Flag Bit Status
    uint16_t SOCB:1;       // 3:3  Latched SOCB Flag Bit Status
    uint16_t reserved2:12; // 15:4 Reserved
};

__attribute__((aligned, packed))
struct ETCLR_REG
{
    uint16_t INT:1;        // 0:0  EPWMxINTn Flag
    uint16_t reserved1:15; // 15:1 Reserved
};

__attribute__((aligned, packed))
struct ETFRC_REG
{
    uint16_t INT:1;        // 0:0  EPWMxINTn Flag
    uint16_t reserved1:1;  // 1:1  Reserved
    uint16_t SOCA:1;       // 2:2  SOCA Flag Clear Bit
    uint16_t SOCB:1;       // 3:3  SOCB Flag Clear Bit
    uint16_t reserved2:12; // 15:4 Reserved
};

__attribute__((aligned, packed))
struct PCCTL_REG
{
    uint16_t CHPEN:1;     // 0:0   PWM chopping enable
    uint16_t OSHTWTH:4;   // 4:1   One-shot pulse width
    uint16_t CHPFREQ:3;   // 7:5   Chopping clock frequency
    uint16_t CHPDUTY:3;   // 10:8  Chopping clock Duty cycle
    uint16_t reserved1:5; // 15:11 Reserved
};



__attribute__((aligned, packed))
struct EPWM_REGS
{
    struct TBCTL_REG   TBCTL;      // 0x00 Time-Base Control Register
    struct TBSTS_REG   TBSTS;      // 0x02 Time-Base Status Register
    uint16_t           reserved1;  // 0x04
    uint16_t           TBPHS;      // 0x06 Time-Base Counter Phase Register
    uint16_t           TBCNT;      // 0x08 Time-Base Counter Register
    uint16_t           TBPRD;      // 0x0A Time-Base Period Register
    uint16_t           reserved2;  // 0x0C
    struct CMPCTL_REG  CMPCTL;     // 0x0E Counter-Compare Control Register

    uint16_t           reserved3;  // 0x10
    uint16_t           CMPA;       // 0x12 Counter-Compare A Register
    uint16_t           CMPB;       // 0x14 Counter-Compare B Register
    struct AQCTL_REG   AQCTLA;     // 0x16 Action Qualifier Control Register For Output A
    struct AQCTL_REG   AQCTLB;     // 0x18 Action Qualifier Control Register For Output B
    struct AQSFRC_REG  AQSFRC;     // 0x1A Action Qualifier Software Force Register
    struct AQCSFRC_REG AQCSFRC;    // 0x1C Action Qualifier Continuous Software Force Register
    struct DBCTL_REG   DBCTL;      // 0x1E Dead-Band Generator Control Register

    uint16_t           DBRED;      // 0x20 Dead-Band Generator Rising Edge Delay Count Register
    uint16_t           DBFED;      // 0x22 Dead-Band Generator Falling Edge Delay Count Register
    struct TZSEL_REG   TZSEL;      // 0x24 Trip-Zone Select Register
    uint16_t           reserved4;  // 0x26
    struct TZCTL_REG   TZCTL;      // 0x28 Trip-Zone Control Register
    struct TZEINT_REG  TZEINT;     // 0x2A Trip-Zone Enable Interrupt Register
    struct TZFLG_REG   TZFLG;      // 0x2C Trip-Zone Flag Register
    struct TZCLR_REG   TZCLR;      // 0x2E Trip-Zone Clear Register

    struct TZFRC_REG   TZFRC;      // 0x30 Trip-Zone Force Register
    struct ETSEL_REG   ETSEL;      // 0x32 Event Trigger Selection Register
    struct ETPS_REG    ETPS;       // 0x34 Event Trigger Pre-Scale Register
    struct ETFLG_REG   ETFLG;      // 0x36 Event Trigger Flag Register
    struct ETCLR_REG   ETCLR;      // 0x38 Event Trigger Clear Register
    struct ETFRC_REG   ETFRC;      // 0x3A Event Trigger Force Register
    struct PCCTL_REG   PCCTL;      // 0x3C PWM Chopper Control Register
};

#endif /* HF91746F8_CFA9_4690_AEB0_0D7D4E402D80 */
