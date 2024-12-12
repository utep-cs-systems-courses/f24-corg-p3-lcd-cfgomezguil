	.text
	.balign 2
	.global WDT

	.section __interrupt_vector_11,"ax"
	.word WDT
	.text

	.extern redrawScreen
	.extern wdt_c_handler
WDT:
;;;  Prologue
	PUSH    R15
	PUSH    R14
	PUSH    R13
	PUSH    R12
	PUSH    R11
	PUSH    R10
	PUSH    R9
	PUSH    R8
	PUSH    R7
	PUSH    R6
	PUSH    R5
	PUSH    R4

;;;  Call C handler
	CALL    #wdt_c_handler

;;;  Clear low-power mode if redrawScreen flag is set
	CMP     #0, &redrawScreen
	JZ      dont_wake
	BIC     #LPM4_bits, 0(R1) ; Clear LPM bits in saved SR

dont_wake:
;;;  Epilogue
	POP     R4
	POP     R5
	POP     R6
	POP     R7
	POP     R8
	POP     R9
	POP     R10
	POP     R11
	POP     R12
	POP     R13
	POP     R14
	POP     R15
	RETI
