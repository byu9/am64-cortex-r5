/*
 * The ARM Cortex-R5 Exception Table
 *
 * John Yu
 * byu9@ncsu.edu
 * April 4 2025
 */
	.weak reset_handler
	.weak undefined_instruction_handler
	.weak supervisor_call_handler
	.weak prefetch_abort_handler
	.weak data_abort_handler
	.weak irq_handler
	.weak fiq_handler

	.set undefined_instruction_handler, unhandled_exception
	.set supervisor_call_handler, unhandled_exception
	.set prefetch_abort_handler, unhandled_exception
	.set data_abort_handler, unhandled_exception
	.set irq_handler, unhandled_exception
	.set fiq_handler, unhandled_exception


	.section .vectors, "ax"
	.type vector_table, %object
	.align 2
vector_table:
	LDR PC, =reset_handler
	LDR PC, =undefined_instruction_handler
	LDR PC, =supervisor_call_handler
	LDR PC, =prefetch_abort_handler
	LDR PC, =data_abort_handler
	LDR PC, =unhandled_exception // reserved vector
	LDR PC, =irq_handler
	LDR PC, =fiq_handler
	.size vector_table, .-vector_table



	.section .text, "ax"
	.type unhandled_exception, %function
unhandled_exception:
	BKPT 0
	BX LR
	.size unhandled_exception, .-unhandled_exception
