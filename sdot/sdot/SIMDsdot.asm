;Cai, Edison B. S11
section .text
bits 64
default rel
global SIMDsdot

SIMDsdot:
	shr rcx, 2
	xorps xmm2, xmm2
L1:
	vmovdqu ymm1, [r9]
	vmovdqu ymm2, [rax]
	vmulpd ymm0, ymm1, ymm2

	add r8, 32
	add r9, 32
	add rax, 32
	loop L1

	shl rcx, 2
L2:
	movsd xmm0, 

	ret
