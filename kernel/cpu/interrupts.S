
.macro isr_generic no=0
.byte \no
.byte 0
  .global _isr\no
  _isr\no\():
    cli
    push $0
    push $\no
    jmp isr_generic_wrapper
.endm

.macro isr_error no=0
.byte \no
  .global _isr\no
  _isr\no\():
    cli
    push $\no
    jmp isr_generic_wrapper    
.endm

.macro irq no=0, rno=32
.byte \rno
  .global _irq\no
  _irq\no\():
    cli
    push $0
    push $\rno
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
isr_generic 126
isr_generic 127
isr_generic 254
isr_generic 255

irq         0   32
irq         1   33
irq         2   34
irq         3   35
irq         4   36
irq         5   37
irq         6   38
irq         7   39
irq         8   40
irq         9   41
irq         10  42
irq         11  43
irq         12  44
irq         13  45
irq         14  46
irq         15  47

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
  mov $16, %eax 
  mov %eax, %ds
  mov %eax, %es
  mov %eax, %fs
  mov %eax, %gs
  push %esp
  call interrupt_handler_generic 
  pop %esp
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
  add $8, %esp
  iretl

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
  mov $16, %eax 
  mov %eax, %ds
  mov %eax, %es
  mov %eax, %fs
  mov %eax, %gs
  push %esp
  call interrupt_handler_irq
  pop %esp
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
  add $8, %esp
  iretl
