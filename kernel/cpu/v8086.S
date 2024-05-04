.code32

.global enter_v8086
enter_v8086: /* isr 0xfe */
  push 4(%ebp) /* push ss */
  push 8(%ebp) /* push esp */
  pushfl /* push eflags onto stack */
  orl $(1 << 17), %esp /* enable v8086 flag */
  push 12(%ebp) /* push cs */
  push 16(%ebp) /* push eip */
  iret /* bye-bye! */

.global run_inside_v8086
run_inside_v8086:
  int $0xfe /* set VM flag (basically) */
  int $0x7e /* debug */


.code16
.global test_v8086
test_v8086:
  mov $0, %ah 
  mov $5, %al
  int $0x10
