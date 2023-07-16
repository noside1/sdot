section .text
bits 64
default rel
global x86sdot

x86sdot:
	xorps xmm3, xmm3
L1:
	movsd xmm1, [r9]
	movsd xmm2, [rax]
	vmulsd xmm0, xmm1, xmm2
	movsd [r8], xmm0
	addsd xmm3, xmm0

	add r8, 8
	add r9, 8
	add rax, 8
	loop L1
	movsd [rdx], xmm3
	ret