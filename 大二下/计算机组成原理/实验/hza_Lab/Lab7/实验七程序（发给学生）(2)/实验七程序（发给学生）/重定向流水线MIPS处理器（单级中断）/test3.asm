#单周期MIPS处理器（单级中断）测试程序        test3.asm                         冒泡法排序（降序排列，从大到小）                       

#主程序起始地址：						0                                                              ROM对应000H

#IRA中断服务程序的入口地址：				3400H     				ROM对应100H  （3400H-3000H)/4=100H
#IRB中断服务程序的入口地址：				3800H    				ROM对应200H  （3800H-3000H)/4=200H
#IRC中断服务程序的入口地址：				3C00H    				ROM对应300H  （3C00H-3000H)/4=300H

#10个数（8、1、5、2、7、9、6、4、3、10）存放的起始地址：	0 =  0H     			RAM对应000H

#堆栈的起始地址：  						1024 = 400H                         		RAM对应100H   （400H/4=100H）

main:
 	addi $s0,$zero,8                        #第1个数=8（可以修改）保存到(0)
 	sw $s0,0($zero)

 	addi $s0,$zero,1                        #第2个数=1（可以修改）保存到(4)
 	sw $s0,4($zero)

 	addi $s0,$zero,5                        #第3个数=5（可以修改）保存到(8)
 	sw $s0,8($zero)

 	addi $s0,$zero,2                        #第4个数=2（可以修改）保存到(12)
	sw $s0,12($zero)

 	addi $s0,$zero,7                        #第5个数=7（可以修改）保存到(16)
	sw $s0,16($zero)

 	addi $s0,$zero,9                        #第6个数=9（可以修改）保存到(20)
 	sw $s0,20($zero)

 	addi $s0,$zero,6                        #第7个数=6（可以修改）保存到(24)
 	sw $s0,24($zero)

 	addi $s0,$zero,4                        #第8个数=4（可以修改）保存到(28)
 	sw $s0,28($zero)

 	addi $s0,$zero,3                        #第9个数=3（可以修改）保存到(32)
 	sw $s0,32($zero)

 	addi $s0,$zero,10                      #第10个数=10（可以修改）保存到(36)
 	sw $s0,36($zero)

 	addi $s0,$zero,0                  	#$s0=0                             排序区间开始地址
 	addi $s1,$zero,36  	  	#$s1=36=10*4-4              排序区间结束地址 

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
	addi $s1,$zero,36                     #$s1=36=10*4-4   排序区间结束地址
 	beq $s0,$s1,loop2                    #如果$s0=$s1，则转loop2
 	beq $zero,$zero,sort_loop       #转sort_loop

loop2:
                lw $a0,0($zero)
                addi $v0,$zero,34                   #syscall的34号功能（在数码管上显示a0的值        0号单元）
                syscall             
                nop
                nop
                nop  
                nop
                nop
                nop  
                nop
                nop
                nop  

                lw $a0,4($zero)
                addi $v0,$zero,34                   #syscall的34号功能（在数码管上显示a0的值        4号单元）
                syscall               
                nop
                nop
                nop
                nop
                nop
                nop  
                nop
                nop
                nop  

                lw $a0,8($zero)
                addi $v0,$zero,34                   #syscall的34号功能（在数码管上显示a0的值        8号单元）
                syscall             
                nop
                nop
                nop  
                nop
                nop
                nop  
                nop
                nop
                nop  

                lw $a0,12($zero)
                addi $v0,$zero,34                   #syscall的34号功能（在数码管上显示a0的值        12号单元）
                syscall               
                nop
                nop
                nop
                nop
                nop
                nop  
                nop
                nop
                nop  

                lw $a0,16($zero)
                addi $v0,$zero,34                   #syscall的34号功能（在数码管上显示a0的值        16号单元）
                syscall             
                nop
                nop
                nop  
                nop
                nop
                nop  
                nop
                nop
                nop  

                lw $a0,20($zero)
                addi $v0,$zero,34                   #syscall的34号功能（在数码管上显示a0的值        0号单元）
                syscall             
                nop
                nop
                nop  
                nop
                nop
                nop  
                nop
                nop
                nop  

                lw $a0,24($zero)
                addi $v0,$zero,34                   #syscall的34号功能（在数码管上显示a0的值        4号单元）
                syscall               
                nop
                nop
                nop
                nop
                nop
                nop  
                nop
                nop
                nop  

                lw $a0,28($zero)
                addi $v0,$zero,34                   #syscall的34号功能（在数码管上显示a0的值        8号单元）
                syscall             
                nop
                nop
                nop  
                nop
                nop
                nop  
                nop
                nop
                nop  

                lw $a0,32($zero)
                addi $v0,$zero,34                   #syscall的34号功能（在数码管上显示a0的值        12号单元）
                syscall               
                nop
                nop
                nop
                nop
                nop
                nop  
                nop
                nop
                nop  

                lw $a0,36($zero)
                addi $v0,$zero,34                   #syscall的34号功能（在数码管上显示a0的值        16号单元）
                syscall             
                nop
                nop
                nop  
                nop
                nop
                nop  
                nop
                nop
                nop  

 	beq $zero,$zero,loop2	  #转loop2             死循环







IRA:                                                       #IRA中断服务程序的入口地址：3400H       RAM对应100H         
	addi $sp,$zero,1024    	#push registers  需要保留中断程序用到的寄存器（$a0    $v0）       
  	sw $a0,0($sp)
  	sw $v0,4($sp)

 	addi   $a0,$0,0x1111         	#display  00001111
	addi   $v0,$0,34           	
	syscall          

                nop
	nop
                nop
	nop
                nop
	nop
                nop
	nop
                nop
	nop
                nop
	nop
                nop
	nop
                nop
	nop
                nop
	nop
                nop
	nop
                nop
	nop
                nop
	nop
                nop
	nop
                nop
	nop
                nop
	nop
                nop
	nop

 	addi   $a0,$0,0x6666         	#display  0000aaaa
	addi   $v0,$0,34           	
	syscall      
       	
  	lw $v0,4($sp)   		#pop registers
  	lw $a0,0($sp)

  	eret











IRB: 				#IRB中断服务程序的入口地址：3800H         RAM对应200H            
	addi $sp,$zero,1024    	#push registers  需要保留中断程序用到的寄存器（$a0    $v0）       
  	sw $a0,0($sp)
  	sw $v0,4($sp)

  	addi   $a0,$0,0x2222         	#display  00002222
	addi   $v0,$0,34           	
	syscall                 	

                nop
	nop
                nop
	nop
                nop
	nop
                nop
	nop
                nop
	nop
                nop
	nop
                nop
	nop
                nop
	nop
                nop
	nop
                nop
	nop
                nop
	nop
                nop
	nop
                nop
	nop
                nop
	nop
                nop
	nop
                nop
	nop

 	addi   $a0,$0,0x7777         	#display  00007777
	addi   $v0,$0,34           	
	syscall      

  	lw $v0,4($sp)   		#pop registers
  	lw $a0,0($sp)

  	eret










IRC: 				#IRC中断服务程序的入口地址：3C00H            RAM对应300H          
	addi $sp,$zero,1024    	#push registers  需要保留中断程序用到的寄存器（$a0    $v0）        
  	sw $a0,0($sp)
  	sw $v0,4($sp)

 	addi   $a0,$0,0x3333         	#display  00003333
	addi   $v0,$0,34           	
	syscall                 	

                nop
	nop
                nop
	nop
                nop
	nop
                nop
	nop
                nop
	nop
                nop
	nop
                nop
	nop
                nop
	nop
                nop
	nop
                nop
	nop
                nop
	nop
                nop
	nop
                nop
	nop
                nop
	nop
                nop
	nop
                nop
	nop

 	addi   $a0,$0,0x8888         	#display  00008888
	addi   $v0,$0,34           	
	syscall      

  	lw $v0,4($sp)   		#pop registers
  	lw $a0,0($sp)

  	eret



