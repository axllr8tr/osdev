
.macro isr_generic no=0
.byte \no
.byte 0
  .global _isr\no
  _isr\no\():
    cli
    push 0
    push \no
    jmp isr_generic_wrapper
.endm

.macro isr_error no=0
.byte \no
  .global _isr\no
  _isr\no\():
    cli
    push \no
    jmp isr_generic_wrapper
.endm

.macro irq no=0, rno=32
.byte \no
  .global _irq\no
  _irq\no\():
    cli
    push 0
    push \no
    jmp irq_handler_wrapper
.endm


isr_generic 0
isr_generic 1
isr_generic 2
isr_generic 3
isr_generic 4
isr_generic 5
isr_generic 6
isr_generic 7
isr_error   8
isr_generic 9
isr_error   10
isr_error   11
isr_error   12
isr_error   13
isr_error   14
isr_generic 15
isr_generic 16
isr_error   17
isr_generic 18
isr_generic 19
isr_generic 20
isr_error   21
isr_generic 22
isr_generic 23
isr_generic 24
isr_generic 25
isr_generic 26
isr_generic 27
isr_generic 28
isr_error   29
isr_error   30
isr_error   31
isr_generic 127
irq         0   32
irq         1   33
irq         2   34


.extern interrupt_handler_generic
.global isr_generic_wrapper
isr_generic_wrapper:
  push %eax
  push %ecx
  push %edx
  push %ebx
  push %esp
  push %ebp
  push %edi
  push %esi
  push %ds
  push %es
  push %fs
  push %gs 
  movl $0x10, %eax
  movl %eax, %ds
  movl %eax, %es
  movl %eax, %fs
  movl %eax, %gs
  movl %esp, %edi 
  push %edi
  call interrupt_handler_generic 
  pop %edi
  pop %gs
  pop %fs
  pop %es
  pop %ds
  pop %esi
  pop %edi
  pop %ebp
  pop %esp
  pop %ebx
  pop %edx
  pop %ecx
  pop %eax
  add $16, %esp
  iret

.extern interrupt_handler_irq
.global irq_handler_wrapper
irq_handler_wrapper:
  push %eax
  push %ecx
  push %edx
  push %ebx
  push %esp
  push %ebp
  push %edi
  push %esi
  push %ds
  push %es
  push %fs
  push %gs 
  movl $0x10, %eax
  movl %eax, %ds
  movl %eax, %es
  movl %eax, %fs
  movl %eax, %gs
  movl %esp, %edi 
  push %edi
  call interrupt_handler_irq
  pop %edi
  pop %gs
  pop %fs
  pop %es
  pop %ds
  pop %esi
  pop %edi
  pop %ebp
  pop %esp
  pop %ebx
  pop %edx
  pop %ecx
  pop %eax
  add $16, %esp
  iret
 

/*
.extern interrupt_handler_err
.global interrupt_handler_err_entry
interrupt_handler_err_entry:
  push %eax
  push %ecx
  push %edx
  push %ebx
  push %esp
  push %ebp
  push %edi
  push %esi
  push %ds
  push %es
  push %fs
  push %gs 
  movl $0x10, %eax
  movl %eax, %ds
  movl %eax, %es
  movl %eax, %fs
  movl %eax, %gs
  movl %esp, %edi
  push %edi
  call interrupt_handler_err
  movl %eax, %esp
  pop %gs
  pop %fs
  pop %es
  pop %ds
  pop %esi
  pop %edi
  pop %ebp
  pop %esp
  pop %ebx
  pop %edx
  pop %ecx
  pop %eax
  add $16, %esp
  iret
  */
