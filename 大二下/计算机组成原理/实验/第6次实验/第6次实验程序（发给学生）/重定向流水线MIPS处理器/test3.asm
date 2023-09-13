#该测试测试通过气泡流水线解决数据相关性       test3.asm   （见教材的P267）

and $s1,$s1,$s2 		#s1 = s1 ^ s2
sub $s2,$s1,$zero 		#s2 = s1 - 0
add $s3,$s1,$s1 		#s3=s1 + s1
or $s4,$s5,$s1 		#s4=s5 | s1
and $s5,$s6,$s1		#s5=s6 ^ s1

addi $s1,$zero,1                     #给s1、s2、s5、s6赋值
addi $s2,$zero,1
addi $s5,$zero,5
addi $s6,$zero,5

and $s1,$s1,$s2 		#s1 = s1 ^ s2   = 1 ^ 1 		=1
sub $s2,$s1,$zero 		#s2 = s1 - 0      = 1-0		=1
add $s3,$s1,$s1 		#s3 = s1 + s1   = 1+1		=2
or $s4,$s5,$s1 		#s4 = s5 | s1     = 101 | 001 = 101	=5  
and $s5,$s6,$s1		#s5 = s6 ^ s1   = 101 ^ 001 		=1

add $a0,$0,$s1		#要显示的值放在a0中      
addi $v0,$zero,34                   #syscall的34号功能（在数码管上显示s1的值）
syscall

add $a0,$0,$s2		#要显示的值放在a0中
addi $v0,$zero,34                   #syscall的34号功能（在数码管上显示s2的值）
syscall

add $a0,$0,$s3		#要显示的值放在a0中
addi $v0,$zero,34                   #syscall的34号功能（在数码管上显示s3的值）
syscall

add $a0,$0,$s4		#要显示的值放在a0中
addi $v0,$zero,34                   #syscall的34号功能（在数码管上显示s4的值）
syscall

add $a0,$0,$s5		#要显示的值放在a0中
addi $v0,$zero,34                   #syscall的34号功能（在数码管上显示s5的值）
syscall               

addi $v0,$zero,10        #v0=10    设置syscall指令的编号（10号表示停机）
syscall		#停机





 