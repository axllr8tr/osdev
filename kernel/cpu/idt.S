.extern global_idt_pointer
.global idt_deploy
idt_deploy:
  lidt global_idt_pointer
  ret
