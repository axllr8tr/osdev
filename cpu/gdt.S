.global gdt_deploy_flat
.extern global_gdt_pointer
gdt_deploy_flat:
  lgdt global_gdt_pointer
  mov $16, %eax
  mov %eax, %ds
  mov %eax, %es
  mov %eax, %fs
  mov %eax, %gs
  mov %eax, %ss
  ljmp $8, $1f
1:
  ret
