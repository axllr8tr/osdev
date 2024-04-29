.extern interrupt_handler_generic
.global interrupt_handler_generic_entry
interrupt_handler_generic_entry:
  pushal
  push %gs 
  push %fs
  push %es
  push %ds
  movl $0x10, %eax
  movl %eax, %gs 
  movl %eax, %fs 
  movl %eax, %es
  movl %eax, %ds
  pushl %esp
  call interrupt_handler_generic 
  popl %eax 
  pop %ds
  pop %es
  pop %fs
  pop %gs
  popal
  iret

.extern interrupt_handler_err
.global interrupt_handler_err_entry
interrupt_handler_err_entry:
  pushal
  push %gs 
  push %fs
  push %es
  push %ds
  movl $0x10, %eax
  movl %eax, %gs 
  movl %eax, %fs 
  movl %eax, %es
  movl %eax, %ds
  pushl %esp
  call interrupt_handler_err
  popl %eax 
  pop %ds
  pop %es
  pop %fs
  pop %gs
  popal
  iret
