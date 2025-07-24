#气泡流水线测试程序——数据相关测试     test2.asm
#该程序用于测试数据相关，使用气泡流水线后，该程序无数据相关
#该程序计算：0+1+2+3+4+5+6+7=28=1CH
#该程序执行结束后，数码管显示1C

addi $s1,$0,4              #s1=4
sw $s1,0($s1)              # 4 -> (4)
lw $s2,0($s1)               # (4) -> s2=4

addi $s2,$s2,-4            # s2-4=0 -> s2=0
addi $s0,$0,0              # s0=0

addi $s1,$s0,1              #s1=1
add $s0,$s0,$s1            #s0=1
addi $s2,$s2,4              #s2=4
sw $s0,0($s2)               #1 -> (4)   04H

addi $s1,$s1,1            #s1=2
add $s0,$s0,$s1         #s0=1+2=3
addi $s2,$s2,4            #s2=8
sw $s0,0($s2)             #3 -> (8)    08H

addi $s1,$s1,1            #s1=3
add $s0,$s0,$s1         #s0=1+2+3=6
addi $s2,$s2,4            #s2=12
sw $s0,0($s2)             #6 -> (12)   0CH

addi $s1,$s1,1            #s1=4
add $s0,$s0,$s1         #s0=1+2+3+4=10
addi $s2,$s2,4            #s2=16
sw $s0,0($s2)             #10 -> (16)   10H

addi $s1,$s1,1            #s1=5
add $s0,$s0,$s1         #s0=1+2+3+4+5=15
addi $s2,$s2,4            #s2=20
sw $s0,0($s2)             #15 -> (20)   14H

addi $s1,$s1,1            #s1=6
add $s0,$s0,$s1         #s0=1+2+3+4+5+6=21
addi $s2,$s2,4            #s2=24
sw $s0,0($s2)             #21 -> (24)   18H

addi $s1,$s1,1            #s1=7
add $s0,$s0,$s1         #s0=1+2+3+4+5+6+7=28
addi $s2,$s2,4            #s2=28
sw $s0,0($s2)             #28 -> (28)    1CH

add $a0,$0,$s0		#a0=s0     a0送数码管显示
addi $v0,$zero,34           	#syscall的34号功能（在数码管上显示a0的值）
syscall

addi $v0,$zero,10		#syscall的10号功能（系统退出）
addi $s0,$zero,0
addi $s0,$zero,0
addi $s0,$zero,0
syscall


