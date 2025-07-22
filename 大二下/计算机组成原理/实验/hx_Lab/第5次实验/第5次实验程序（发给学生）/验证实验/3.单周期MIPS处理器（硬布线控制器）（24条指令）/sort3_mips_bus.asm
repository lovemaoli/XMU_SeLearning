#MIPS程序    sort3_mips_bus.asm    排序程序（降序排列，从大到小）     仅使用5条指令 （lw、sw、beq、addi、slt）                 

#先将5个数（3、1、5、2、4）存放到地址为0开始的数据存储器中，然后对这5个数进行排序。

.text

main:
 	addi $s0,$zero,3                        #第1个数=3（可以修改）保存到(0)
 	sw $s0,0($zero)
 	addi $s0,$zero,1                        #第2个数=1（可以修改）保存到(4)
 	sw $s0,4($zero)
 	addi $s0,$zero,5                        #第3个数=5（可以修改）保存到(8)
 	sw $s0,8($zero)
 	addi $s0,$zero,2                        #第4个数=2（可以修改）保存到(12)
	sw $s0,12($zero)
 	addi $s0,$zero,4                        #第5个数=4（可以修改）保存到(16)
	sw $s0,16($zero)

 	addi $s0,$zero,0                  	#$s0=0                              排序区间开始地址
 	addi $s1,$zero,16  	  	#$s1=16=5*4-4       排序区间结束地址         5个数        
sort_loop:
 	lw $s3,0($s0)                     	  #$s3=($s0)
	lw $s4,0($s1)                	  #$s4=($s1)
 	slt $t0,$s3,$s4                	  #如果$s3<$s4，则置$t0=1；否则，置$t0=0        降序排序         从大到小
 	beq $t0,$zero,sort_next   	  #如果$t0=0，则转sort_nent       
 	sw $s3,0($s1)                	  #交换($s0)和($s1)
	sw $s4,0($s0)                   	  #交换($s0)和($s1)
sort_next:
	addi $s1,$s1,-4                          #$s1-4 -> $s1
 	beq $s0,$s1,loop1                     #如果$s0=$s1，则转loop1   
 	beq $zero,$zero,sort_loop        #转sort_loop
loop1:
  	addi $s0,$s0,4                           #$s0+4 -> $s0
	addi $s1,$zero,16                 	#$s1=16=5*4-4   排序区间结束地址                5个数            
 	beq $s0,$s1,loop2                    #如果$s0=$s1，则转loop2
 	beq $zero,$zero,sort_loop       #转sort_loop
loop2:
 	beq $zero,$zero,loop2	  #转loop2             死循环