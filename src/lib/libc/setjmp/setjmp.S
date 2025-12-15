
        .syntax unified
        .arch armv7-m

        .section    ".text"

        .globl      setjmp
        .type       setjmp STT_FUNC
        .thumb_func
setjmp:
	// Save r4 to r11, r13(sp) and r14(lr) to the jump buffer
	// We can't put sp in the reg list so move it to r12
	// which we don't need to save
	mov     r12, sp
	stmia   r0!, { r4-r12, r14 }
	// Return 0
	mov     r0, #0
	bx      lr
