/*
 * Linker script for ARM Cortex-R5 Cores on the AM6442
 * Intended to be used with GCC compiler officially maintained by ARM.
 * Not guaranteed to work properly under TI ARM Compilers.
 *
 * John Yu
 * byu9@ncsu.edu
 * April 3 2025
 */

/*
 * The memory region definition applies to the Cortex-R5 subsystem when
 * it is configured for single-core mode with the redundant core CPU1
 * disabled.
 */
MEMORY
{
	/* Table 2-3 in Reference Manual SPRUIM2H */
	ATCM    (XR): ORIGIN = 0x00000000, LENGTH = 64K
	RAT0    (RW): ORIGIN = 0x00010000, LENGTH = 524224K
	SOC0    (RW): ORIGIN = 0x20000000, LENGTH = 256M
	RAT_CFG (RW): ORIGIN = 0x2FFE0000, LENGTH = 4K
	VIC_CFG (RW): ORIGIN = 0x2FFF0000, LENGTH = 16K
	RAT1    (RW): ORIGIN = 0x30000000, LENGTH = 278592K
	BTCM    (RW): ORIGIN = 0x41010000, LENGTH = 64K
	RAT2    (RW): ORIGIN = 0x41018000, LENGTH = 1032096K
	RAT3    (RW): ORIGIN = 0x80000000, LENGTH = 2048M
}

ENTRY(main);
stack_size = 2K;

SECTIONS
{
	/* The ARM Cortex-R5 vector table */
	.vectors : ALIGN(4) {
		KEEP(*(.vectors))
	} >ATCM

	/*
	 * The text section.
	 * Contains executable code and constant tables.
	 */
	.text : ALIGN(4) {
		*(.text .text.*)
		*(.rodata .rodata.*)
		*(.common .common.*)
	} >ATCM

	/*
	 * The main stack.
	 * The ARMv7 architecture stack point decreases when stack grows, so the
	 * initial stack pointer is at the end of the stack memory.
	 */
	.stack (NOLOAD) : ALIGN(4)
	{
		. += stack_size;
		initial_stack_pointer = .;
	} >BTCM = 0

	/*
	 * The data section
	 * Contains global variables whose initial values are not zero.
	 * The initial values of those variables are stored at the load address.
	 */
	 .data : ALIGN(4)
	 {
	 	data_start = .;
	 	*(.data .data.*)
	 	data_end = .;
	 } >BTCM AT>ATCM
	 data_load = LOADADDR(.data);

	/*
	 * The bss section (stands for block started by symbol)
	 * Contains global variables whose initial values are set to zero.
	 * This section MUST be zeroed by the C early runtime system!
	 */
	.bss (NOLOAD) : ALIGN(4)
	{
		bss_start = .;
		*(.bss .bss.*)
		bss_end = .;
	} >BTCM
}
