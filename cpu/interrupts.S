.extern interrupt_handler_generic
.global interrupt_handler_generic_entry
interrupt_handler_generic_entry:
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
  movl %esp, %edi
  call interrupt_handler_generic 
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
  movl %esp, %edi 
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

