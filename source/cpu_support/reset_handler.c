/*
 * CPU Exception Handlers
 *
 * John Yu
 * byu9@ncsu.edu
 * April 3 2025
 */
#include <stdint.h>



static void zero_bss_section(void);
static void load_data_section(void);

/*
 * Upon reset, the CPU executes content in the reset handler.
 */
__attribute__((noreturn))
void reset_handler(void)
{
    /*
     * Initializes the stack pointer.
     *
     * The placement of the stack section and initial stack pointer is defined
     * in the linker script.
     */
    __asm volatile("\n\t LDR SP, =initial_stack_pointer");

    /*
     * Enables CPU hardware floating point support.
     *
     * If floating point support is disabled, floating point instructions
     * raise "undefined instruction" exception. Inform the compiler to use
     * software floating point instead.
     */

    // CP10 and CP11 co-processors must be enabled at the same time.
    __asm volatile("\n\t MRC p15, 0, R0, c1, c0, 2");
    __asm volatile("\n\t ORR R0, R0, #(3 << 22)");
    __asm volatile("\n\t MCR p15, 0, R0, c1, c0, 2");

    // Floating point exceptions must be enabled.
    __asm volatile("\n\t MOV R0, #(1 << 30)");
    __asm volatile("\n\t VMSR FPEXC, R0");

    /*
     * Prepares the C runtime environment.
     *
     *   The .bss section contains static variables whose initial values must
     *   be cleared to zero before main().
     *
     *   The .data section contains static variables whose initial values must
     *   be loaded before main().
     *
     * Failure to initialize the sections results in invalid program behavior.
     *
     * The placement of the sections is defined in the linker script.
     */
    zero_bss_section();
    load_data_section();

    extern void main(void);
    main();

    /*
     * Returning from reset handler would result in stack overflow and a
     * runaway program.
     */
    for( ; ;)
        ;
}

static void zero_bss_section(void)
{
    /*
     * The following variables are defined in the linker script. The address
     * of the variables have meaning.
     */
    extern int bss_start;
    extern int bss_end;

    for (int *p = &bss_start; p < &bss_end; ++p)
        *p = 0;
}

static void load_data_section(void)
{
    /*
     * The following variables are defined in the linker script. The address
     * of the variables have meaning.
     */
    extern int data_start;
    extern int data_end;
    extern int data_load;

    const int *from = &data_load;
    for (int *to = &data_start; to < &data_end; ++to)
    {
        *to = *from;
        ++from;
    }
}
