#理想流水线测试程序    test.asm
#该程序将0、1、2、3分别存放到0、1、2、3号存储器中（地址为0、4、8、12）
#该程序中的所有指令（17条）均无相关性
#5段流水线执行周期数=5+(17-1)=21

addi $s0,$zero,0         # 将4个寄存器s0至s3全部赋值为0
addi $s1,$zero,0
addi $s2,$zero,0
addi $s3,$zero,0

ori $s0,$s0,0               # 将4个寄存器s0至s3分别赋值为0、1、2、3
ori $s1,$s1,1
ori $s2,$s2,2
ori $s3,$s3,3

sw $s0,0($s0)         # 将4个寄存器s0至s3分别存储到地址为0、4、8、12的存储单元中
sw $s1,4($s0)
sw $s2,8($s0)
sw $s3,12($s0)

addi $v0,$zero,10        #v0=10    设置syscall指令的编号（10号表示停机）

addi $s1,$zero,0         #3条无用指令，消除syscall指令与“addi $v0,$zero,10”指令的相关性
addi $s2,$zero,0
addi $s3,$zero,0

syscall		#停机
