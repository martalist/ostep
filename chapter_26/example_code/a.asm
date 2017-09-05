a.out:
(__TEXT,__text) section
_Pthread_mutex_lock:
0000000100000af0	pushq	%rbp
0000000100000af1	movq	%rsp, %rbp
0000000100000af4	subq	$0x10, %rsp
0000000100000af8	movq	%rdi, -0x8(%rbp)
0000000100000afc	movq	-0x8(%rbp), %rdi
0000000100000b00	callq	0x100000e54 ## symbol stub for: _pthread_mutex_lock
0000000100000b05	movl	%eax, -0xc(%rbp)
0000000100000b08	cmpl	$0x0, -0xc(%rbp)
0000000100000b0c	sete	%cl
0000000100000b0f	xorb	$-0x1, %cl
0000000100000b12	andb	$0x1, %cl
0000000100000b15	movzbl	%cl, %eax
0000000100000b18	movslq	%eax, %rdi
0000000100000b1b	cmpq	$0x0, %rdi
0000000100000b1f	je	0x100000b44
0000000100000b25	leaq	0x39e(%rip), %rdi ## literal pool for: "Pthread_mutex_lock"
0000000100000b2c	leaq	0x3aa(%rip), %rsi ## literal pool for: "./mythreads.h"
0000000100000b33	movl	$0xc, %edx
0000000100000b38	leaq	0x3ac(%rip), %rcx ## literal pool for: "rc == 0"
0000000100000b3f	callq	0x100000e2a ## symbol stub for: ___assert_rtn
0000000100000b44	jmp	0x100000b49
0000000100000b49	addq	$0x10, %rsp
0000000100000b4d	popq	%rbp
0000000100000b4e	retq
0000000100000b4f	nop
_Pthread_mutex_unlock:
0000000100000b50	pushq	%rbp
0000000100000b51	movq	%rsp, %rbp
0000000100000b54	subq	$0x10, %rsp
0000000100000b58	movq	%rdi, -0x8(%rbp)
0000000100000b5c	movq	-0x8(%rbp), %rdi
0000000100000b60	callq	0x100000e5a ## symbol stub for: _pthread_mutex_unlock
0000000100000b65	movl	%eax, -0xc(%rbp)
0000000100000b68	cmpl	$0x0, -0xc(%rbp)
0000000100000b6c	sete	%cl
0000000100000b6f	xorb	$-0x1, %cl
0000000100000b72	andb	$0x1, %cl
0000000100000b75	movzbl	%cl, %eax
0000000100000b78	movslq	%eax, %rdi
0000000100000b7b	cmpq	$0x0, %rdi
0000000100000b7f	je	0x100000ba4
0000000100000b85	leaq	0x367(%rip), %rdi ## literal pool for: "Pthread_mutex_unlock"
0000000100000b8c	leaq	0x34a(%rip), %rsi ## literal pool for: "./mythreads.h"
0000000100000b93	movl	$0x13, %edx
0000000100000b98	leaq	0x34c(%rip), %rcx ## literal pool for: "rc == 0"
0000000100000b9f	callq	0x100000e2a ## symbol stub for: ___assert_rtn
0000000100000ba4	jmp	0x100000ba9
0000000100000ba9	addq	$0x10, %rsp
0000000100000bad	popq	%rbp
0000000100000bae	retq
0000000100000baf	nop
_Pthread_create:
0000000100000bb0	pushq	%rbp
0000000100000bb1	movq	%rsp, %rbp
0000000100000bb4	subq	$0x30, %rsp
0000000100000bb8	movq	%rdi, -0x8(%rbp)
0000000100000bbc	movq	%rsi, -0x10(%rbp)
0000000100000bc0	movq	%rdx, -0x18(%rbp)
0000000100000bc4	movq	%rcx, -0x20(%rbp)
0000000100000bc8	movq	-0x8(%rbp), %rdi
0000000100000bcc	movq	-0x10(%rbp), %rsi
0000000100000bd0	movq	-0x18(%rbp), %rdx
0000000100000bd4	movq	-0x20(%rbp), %rcx
0000000100000bd8	callq	0x100000e48 ## symbol stub for: _pthread_create
0000000100000bdd	movl	%eax, -0x24(%rbp)
0000000100000be0	cmpl	$0x0, -0x24(%rbp)
0000000100000be4	sete	%r8b
0000000100000be8	xorb	$-0x1, %r8b
0000000100000bec	andb	$0x1, %r8b
0000000100000bf0	movzbl	%r8b, %eax
0000000100000bf4	movslq	%eax, %rcx
0000000100000bf7	cmpq	$0x0, %rcx
0000000100000bfb	je	0x100000c20
0000000100000c01	leaq	0x300(%rip), %rdi ## literal pool for: "Pthread_create"
0000000100000c08	leaq	0x2ce(%rip), %rsi ## literal pool for: "./mythreads.h"
0000000100000c0f	movl	$0x1b, %edx
0000000100000c14	leaq	0x2d0(%rip), %rcx ## literal pool for: "rc == 0"
0000000100000c1b	callq	0x100000e2a ## symbol stub for: ___assert_rtn
0000000100000c20	jmp	0x100000c25
0000000100000c25	addq	$0x30, %rsp
0000000100000c29	popq	%rbp
0000000100000c2a	retq
0000000100000c2b	nopl	(%rax,%rax)
_Pthread_join:
0000000100000c30	pushq	%rbp
0000000100000c31	movq	%rsp, %rbp
0000000100000c34	subq	$0x20, %rsp
0000000100000c38	movq	%rdi, -0x8(%rbp)
0000000100000c3c	movq	%rsi, -0x10(%rbp)
0000000100000c40	movq	-0x8(%rbp), %rdi
0000000100000c44	movq	-0x10(%rbp), %rsi
0000000100000c48	callq	0x100000e4e ## symbol stub for: _pthread_join
0000000100000c4d	movl	%eax, -0x14(%rbp)
0000000100000c50	cmpl	$0x0, -0x14(%rbp)
0000000100000c54	sete	%cl
0000000100000c57	xorb	$-0x1, %cl
0000000100000c5a	andb	$0x1, %cl
0000000100000c5d	movzbl	%cl, %eax
0000000100000c60	movslq	%eax, %rsi
0000000100000c63	cmpq	$0x0, %rsi
0000000100000c67	je	0x100000c8c
0000000100000c6d	leaq	0x2a3(%rip), %rdi ## literal pool for: "Pthread_join"
0000000100000c74	leaq	0x262(%rip), %rsi ## literal pool for: "./mythreads.h"
0000000100000c7b	movl	$0x22, %edx
0000000100000c80	leaq	0x264(%rip), %rcx ## literal pool for: "rc == 0"
0000000100000c87	callq	0x100000e2a ## symbol stub for: ___assert_rtn
0000000100000c8c	jmp	0x100000c91
0000000100000c91	addq	$0x20, %rsp
0000000100000c95	popq	%rbp
0000000100000c96	retq
0000000100000c97	nopw	(%rax,%rax)
_mythread:
0000000100000ca0	pushq	%rbp
0000000100000ca1	movq	%rsp, %rbp
0000000100000ca4	subq	$0x20, %rsp
0000000100000ca8	leaq	0x275(%rip), %rax ## literal pool for: "%s: begin [addr of i: %p]\n"
0000000100000caf	leaq	-0x14(%rbp), %rdx
0000000100000cb3	movq	%rdi, -0x8(%rbp)
0000000100000cb7	movq	-0x8(%rbp), %rdi
0000000100000cbb	movq	%rdi, -0x10(%rbp)
0000000100000cbf	movq	-0x10(%rbp), %rsi
0000000100000cc3	movq	%rax, %rdi
0000000100000cc6	movb	$0x0, %al
0000000100000cc8	callq	0x100000e42 ## symbol stub for: _printf
0000000100000ccd	movl	$0x0, -0x14(%rbp)
0000000100000cd4	movl	%eax, -0x18(%rbp)
0000000100000cd7	leaq	_max(%rip), %rax
0000000100000cde	movl	-0x14(%rbp), %ecx
0000000100000ce1	cmpl	(%rax), %ecx
0000000100000ce3	jge	0x100000d06
0000000100000ce9	movl	_counter(%rip), %eax
0000000100000cef	addl	$0x1, %eax
0000000100000cf2	movl	%eax, _counter(%rip)
0000000100000cf8	movl	-0x14(%rbp), %eax
0000000100000cfb	addl	$0x1, %eax
0000000100000cfe	movl	%eax, -0x14(%rbp)
0000000100000d01	jmp	0x100000cd7
0000000100000d06	leaq	0x232(%rip), %rdi ## literal pool for: "%s: done\n"
0000000100000d0d	movq	-0x10(%rbp), %rsi
0000000100000d11	movb	$0x0, %al
0000000100000d13	callq	0x100000e42 ## symbol stub for: _printf
0000000100000d18	xorl	%ecx, %ecx
0000000100000d1a	movl	%ecx, %esi
0000000100000d1c	movl	%eax, -0x1c(%rbp)
0000000100000d1f	movq	%rsi, %rax
0000000100000d22	addq	$0x20, %rsp
0000000100000d26	popq	%rbp
0000000100000d27	retq
0000000100000d28	nopl	(%rax,%rax)
_main:
0000000100000d30	pushq	%rbp
0000000100000d31	movq	%rsp, %rbp
0000000100000d34	subq	$0x30, %rsp
0000000100000d38	movl	$0x0, -0x4(%rbp)
0000000100000d3f	movl	%edi, -0x8(%rbp)
0000000100000d42	movq	%rsi, -0x10(%rbp)
0000000100000d46	cmpl	$0x2, -0x8(%rbp)
0000000100000d4a	je	0x100000d75
0000000100000d50	leaq	0x1f2(%rip), %rsi ## literal pool for: "usage: main-first <loopcount>\n"
0000000100000d57	movq	0x2b2(%rip), %rax ## literal pool symbol address: ___stderrp
0000000100000d5e	movq	(%rax), %rdi
0000000100000d61	movb	$0x0, %al
0000000100000d63	callq	0x100000e3c ## symbol stub for: _fprintf
0000000100000d68	movl	$0x1, %edi
0000000100000d6d	movl	%eax, -0x24(%rbp)
0000000100000d70	callq	0x100000e36 ## symbol stub for: _exit
0000000100000d75	movq	-0x10(%rbp), %rax
0000000100000d79	movq	0x8(%rax), %rdi
0000000100000d7d	callq	0x100000e30 ## symbol stub for: _atoi
0000000100000d82	leaq	0x1df(%rip), %rdi ## literal pool for: "main: begin [counter = %d] [%x]\n"
0000000100000d89	leaq	_counter(%rip), %rcx
0000000100000d90	movl	%ecx, %edx
0000000100000d92	leaq	_max(%rip), %rcx
0000000100000d99	movl	%eax, (%rcx)
0000000100000d9b	movl	_counter(%rip), %esi
0000000100000da1	movb	$0x0, %al
0000000100000da3	callq	0x100000e42 ## symbol stub for: _printf
0000000100000da8	leaq	-0x18(%rbp), %rdi
0000000100000dac	xorl	%edx, %edx
0000000100000dae	movl	%edx, %esi
0000000100000db0	leaq	_mythread(%rip), %rdx
0000000100000db7	leaq	0x1cb(%rip), %rcx ## literal pool for: "A"
0000000100000dbe	movl	%eax, -0x28(%rbp)
0000000100000dc1	callq	_Pthread_create
0000000100000dc6	leaq	-0x20(%rbp), %rdi
0000000100000dca	xorl	%eax, %eax
0000000100000dcc	movl	%eax, %esi
0000000100000dce	leaq	_mythread(%rip), %rdx
0000000100000dd5	leaq	0x1af(%rip), %rcx ## literal pool for: "B"
0000000100000ddc	callq	_Pthread_create
0000000100000de1	xorl	%eax, %eax
0000000100000de3	movl	%eax, %esi
0000000100000de5	movq	-0x18(%rbp), %rdi
0000000100000de9	callq	_Pthread_join
0000000100000dee	xorl	%eax, %eax
0000000100000df0	movl	%eax, %esi
0000000100000df2	movq	-0x20(%rbp), %rdi
0000000100000df6	callq	_Pthread_join
0000000100000dfb	leaq	0x18b(%rip), %rdi ## literal pool for: "main: done\n [counter: %d]\n [should: %d]\n"
0000000100000e02	leaq	_max(%rip), %rcx
0000000100000e09	movl	_counter(%rip), %esi
0000000100000e0f	movl	(%rcx), %eax
0000000100000e11	shll	$0x1, %eax
0000000100000e14	movl	%eax, %edx
0000000100000e16	movb	$0x0, %al
0000000100000e18	callq	0x100000e42 ## symbol stub for: _printf
0000000100000e1d	xorl	%edx, %edx
0000000100000e1f	movl	%eax, -0x2c(%rbp)
0000000100000e22	movl	%edx, %eax
0000000100000e24	addq	$0x30, %rsp
0000000100000e28	popq	%rbp
0000000100000e29	retq
