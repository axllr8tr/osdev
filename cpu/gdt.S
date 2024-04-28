.global gdt_deploy_flat
.extern global_gdt_pointer
gdt_deploy_flat:
  lgdt global_gdt_pointer
  ret
  
