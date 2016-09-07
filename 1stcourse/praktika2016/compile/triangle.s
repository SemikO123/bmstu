	.file	"triangle.c"
	.intel_syntax noprefix
	.text
	.globl	_getc
	.def	_getc;	.scl	2;	.type	32;	.endef
_getc:
LFB0:
	.cfi_startproc
	push	ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	mov	ebp, esp
	.cfi_def_cfa_register 5
	sub	esp, 24
	mov	eax, DWORD PTR [ebp+8]
	mov	eax, DWORD PTR [eax+4]
	lea	edx, [eax-1]
	mov	eax, DWORD PTR [ebp+8]
	mov	DWORD PTR [eax+4], edx
	mov	eax, DWORD PTR [ebp+8]
	mov	eax, DWORD PTR [eax+4]
	test	eax, eax
	js	L2
	mov	eax, DWORD PTR [ebp+8]
	mov	eax, DWORD PTR [eax]
	lea	ecx, [eax+1]
	mov	edx, DWORD PTR [ebp+8]
	mov	DWORD PTR [edx], ecx
	movzx	eax, BYTE PTR [eax]
	movzx	eax, al
	jmp	L3
L2:
	mov	eax, DWORD PTR [ebp+8]
	mov	DWORD PTR [esp], eax
	call	__filbuf
L3:
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE0:
	.globl	_putc
	.def	_putc;	.scl	2;	.type	32;	.endef
_putc:
LFB1:
	.cfi_startproc
	push	ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	mov	ebp, esp
	.cfi_def_cfa_register 5
	sub	esp, 24
	mov	eax, DWORD PTR [ebp+12]
	mov	eax, DWORD PTR [eax+4]
	lea	edx, [eax-1]
	mov	eax, DWORD PTR [ebp+12]
	mov	DWORD PTR [eax+4], edx
	mov	eax, DWORD PTR [ebp+12]
	mov	eax, DWORD PTR [eax+4]
	test	eax, eax
	js	L6
	mov	eax, DWORD PTR [ebp+12]
	mov	eax, DWORD PTR [eax]
	lea	ecx, [eax+1]
	mov	edx, DWORD PTR [ebp+12]
	mov	DWORD PTR [edx], ecx
	mov	edx, DWORD PTR [ebp+8]
	mov	BYTE PTR [eax], dl
	movzx	eax, BYTE PTR [eax]
	movzx	eax, al
	jmp	L7
L6:
	mov	eax, DWORD PTR [ebp+12]
	mov	DWORD PTR [esp+4], eax
	mov	eax, DWORD PTR [ebp+8]
	mov	DWORD PTR [esp], eax
	call	__flsbuf
L7:
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE1:
	.globl	_getchar
	.def	_getchar;	.scl	2;	.type	32;	.endef
_getchar:
LFB2:
	.cfi_startproc
	push	ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	mov	ebp, esp
	.cfi_def_cfa_register 5
	sub	esp, 24
	mov	eax, DWORD PTR __imp___iob
	mov	eax, DWORD PTR [eax+4]
	lea	edx, [eax-1]
	mov	eax, DWORD PTR __imp___iob
	mov	DWORD PTR [eax+4], edx
	mov	eax, DWORD PTR __imp___iob
	mov	eax, DWORD PTR [eax+4]
	test	eax, eax
	js	L10
	mov	eax, DWORD PTR __imp___iob
	mov	eax, DWORD PTR [eax]
	lea	ecx, [eax+1]
	mov	edx, DWORD PTR __imp___iob
	mov	DWORD PTR [edx], ecx
	movzx	eax, BYTE PTR [eax]
	movzx	eax, al
	jmp	L11
L10:
	mov	eax, DWORD PTR __imp___iob
	mov	DWORD PTR [esp], eax
	call	__filbuf
L11:
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE2:
	.globl	_putchar
	.def	_putchar;	.scl	2;	.type	32;	.endef
_putchar:
LFB3:
	.cfi_startproc
	push	ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	mov	ebp, esp
	.cfi_def_cfa_register 5
	sub	esp, 24
	mov	eax, DWORD PTR __imp___iob
	mov	eax, DWORD PTR [eax+36]
	lea	edx, [eax-1]
	mov	eax, DWORD PTR __imp___iob
	mov	DWORD PTR [eax+36], edx
	mov	eax, DWORD PTR __imp___iob
	mov	eax, DWORD PTR [eax+36]
	test	eax, eax
	js	L14
	mov	eax, DWORD PTR __imp___iob
	mov	eax, DWORD PTR [eax+32]
	lea	ecx, [eax+1]
	mov	edx, DWORD PTR __imp___iob
	mov	DWORD PTR [edx+32], ecx
	mov	edx, DWORD PTR [ebp+8]
	mov	BYTE PTR [eax], dl
	movzx	eax, BYTE PTR [eax]
	movzx	eax, al
	jmp	L15
L14:
	mov	eax, DWORD PTR __imp___iob
	add	eax, 32
	mov	DWORD PTR [esp+4], eax
	mov	eax, DWORD PTR [ebp+8]
	mov	DWORD PTR [esp], eax
	call	__flsbuf
L15:
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE3:
	.globl	__get_output_format
	.def	__get_output_format;	.scl	2;	.type	32;	.endef
__get_output_format:
LFB4:
	.cfi_startproc
	push	ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	mov	ebp, esp
	.cfi_def_cfa_register 5
	sub	esp, 8
	call	___mingw_get_output_format
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE4:
	.globl	__set_output_format
	.def	__set_output_format;	.scl	2;	.type	32;	.endef
__set_output_format:
LFB5:
	.cfi_startproc
	push	ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	mov	ebp, esp
	.cfi_def_cfa_register 5
	sub	esp, 24
	mov	eax, DWORD PTR [ebp+8]
	mov	DWORD PTR [esp], eax
	call	___mingw_set_output_format
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE5:
	.globl	__get_printf_count_output
	.def	__get_printf_count_output;	.scl	2;	.type	32;	.endef
__get_printf_count_output:
LFB6:
	.cfi_startproc
	push	ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	mov	ebp, esp
	.cfi_def_cfa_register 5
	sub	esp, 8
	call	___mingw_get_printf_count_output
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE6:
	.globl	__set_printf_count_output
	.def	__set_printf_count_output;	.scl	2;	.type	32;	.endef
__set_printf_count_output:
LFB7:
	.cfi_startproc
	push	ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	mov	ebp, esp
	.cfi_def_cfa_register 5
	sub	esp, 24
	mov	eax, DWORD PTR [ebp+8]
	mov	DWORD PTR [esp], eax
	call	___mingw_set_printf_count_output
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE7:
	.globl	_fopen64
	.def	_fopen64;	.scl	2;	.type	32;	.endef
_fopen64:
LFB8:
	.cfi_startproc
	push	ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	mov	ebp, esp
	.cfi_def_cfa_register 5
	sub	esp, 24
	mov	eax, DWORD PTR [ebp+12]
	mov	DWORD PTR [esp+4], eax
	mov	eax, DWORD PTR [ebp+8]
	mov	DWORD PTR [esp], eax
	call	_fopen
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE8:
	.globl	_ftello64
	.def	_ftello64;	.scl	2;	.type	32;	.endef
_ftello64:
LFB9:
	.cfi_startproc
	push	ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	mov	ebp, esp
	.cfi_def_cfa_register 5
	sub	esp, 40
	lea	eax, [ebp-16]
	mov	DWORD PTR [esp+4], eax
	mov	eax, DWORD PTR [ebp+8]
	mov	DWORD PTR [esp], eax
	call	_fgetpos
	test	eax, eax
	je	L28
	mov	eax, -1
	mov	edx, -1
	jmp	L30
L28:
	mov	eax, DWORD PTR [ebp-16]
	mov	edx, DWORD PTR [ebp-12]
L30:
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE9:
	.def	___main;	.scl	2;	.type	32;	.endef
	.section .rdata,"dr"
LC0:
	.ascii "Input a,b,c\0"
LC1:
	.ascii "%f %f %f\0"
LC3:
	.ascii "Area of triangle: %6.2f\0"
LC4:
	.ascii "Incorrect entry\0"
	.text
	.globl	_main
	.def	_main;	.scl	2;	.type	32;	.endef
_main:
LFB10:
	.cfi_startproc
	push	ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	mov	ebp, esp
	.cfi_def_cfa_register 5
	and	esp, -16
	sub	esp, 64
	call	___main
	mov	DWORD PTR [esp], OFFSET FLAT:LC0
	call	_puts
	lea	eax, [esp+44]
	mov	DWORD PTR [esp+12], eax
	lea	eax, [esp+48]
	mov	DWORD PTR [esp+8], eax
	lea	eax, [esp+52]
	mov	DWORD PTR [esp+4], eax
	mov	DWORD PTR [esp], OFFSET FLAT:LC1
	call	_scanf
	mov	DWORD PTR [esp+60], eax
	cmp	DWORD PTR [esp+60], 3
	jne	L32
	fld	DWORD PTR [esp+52]
	fld	DWORD PTR [esp+48]
	faddp	st(1), st
	fld	DWORD PTR [esp+44]
	faddp	st(1), st
	fld	TBYTE PTR LC2
	fdivp	st(1), st
	fld	DWORD PTR [esp+52]
	fld	DWORD PTR [esp+48]
	faddp	st(1), st
	fld	DWORD PTR [esp+44]
	faddp	st(1), st
	fld	TBYTE PTR LC2
	fdivp	st(1), st
	fld	DWORD PTR [esp+52]
	fsubp	st(1), st
	fmulp	st(1), st
	fld	DWORD PTR [esp+52]
	fld	DWORD PTR [esp+48]
	faddp	st(1), st
	fld	DWORD PTR [esp+44]
	faddp	st(1), st
	fld	TBYTE PTR LC2
	fdivp	st(1), st
	fld	DWORD PTR [esp+48]
	fsubp	st(1), st
	fmulp	st(1), st
	fld	DWORD PTR [esp+52]
	fld	DWORD PTR [esp+48]
	faddp	st(1), st
	fld	DWORD PTR [esp+44]
	faddp	st(1), st
	fld	TBYTE PTR LC2
	fdivp	st(1), st
	fld	DWORD PTR [esp+44]
	fsubp	st(1), st
	fmulp	st(1), st
	fstp	QWORD PTR [esp+24]
	fld	QWORD PTR [esp+24]
	fstp	QWORD PTR [esp]
	call	_sqrt
	fstp	DWORD PTR [esp+56]
	fld	DWORD PTR [esp+56]
	fstp	QWORD PTR [esp+4]
	mov	DWORD PTR [esp], OFFSET FLAT:LC3
	call	_printf
	jmp	L33
L32:
	mov	DWORD PTR [esp], OFFSET FLAT:LC4
	call	_puts
L33:
	mov	eax, 0
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE10:
	.section .rdata,"dr"
	.align 16
LC2:
	.long	0
	.long	-2147483648
	.long	16384
	.ident	"GCC: (GNU) 4.9.3"
	.def	__filbuf;	.scl	2;	.type	32;	.endef
	.def	__flsbuf;	.scl	2;	.type	32;	.endef
	.def	___mingw_get_output_format;	.scl	2;	.type	32;	.endef
	.def	___mingw_set_output_format;	.scl	2;	.type	32;	.endef
	.def	___mingw_get_printf_count_output;	.scl	2;	.type	32;	.endef
	.def	___mingw_set_printf_count_output;	.scl	2;	.type	32;	.endef
	.def	_fopen;	.scl	2;	.type	32;	.endef
	.def	_fgetpos;	.scl	2;	.type	32;	.endef
	.def	_puts;	.scl	2;	.type	32;	.endef
	.def	_scanf;	.scl	2;	.type	32;	.endef
	.def	_sqrt;	.scl	2;	.type	32;	.endef
	.def	_printf;	.scl	2;	.type	32;	.endef
