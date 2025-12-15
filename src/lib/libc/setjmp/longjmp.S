
        .syntax unified
        .arch armv7-m

        .section    ".text"

        .globl      longjmp
        .type       longjmp STT_FUNC
        .thumb_func
longjmp:
	// Restore r4 to r11, r13(sp) and r14(lr) from the jump buffer
	// We will need to move sp from r12 since we can't put sp in the
	// reg list
	ldmfd   r0!, { r4-r12, r14 }
	mov     sp, r12
	// Return arg2 in r0
	movs    r0, r1
	// Unless it's a 0
	bne     1f
	// In which case make it a 1
	mov     r0, #1
1:
	bx      lr
