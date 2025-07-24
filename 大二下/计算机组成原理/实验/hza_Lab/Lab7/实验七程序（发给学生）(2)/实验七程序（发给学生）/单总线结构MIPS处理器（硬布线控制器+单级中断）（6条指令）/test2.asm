#MIPS程序    test2.asm    冒泡法排序（降序排列，从大到小）   +  求累加和                    

#主程序起始地址：0                                                                			RAM对应000

#IRQ0中断服务程序的入口地址：1024  =  400H     				RAM对应100                 
#IRQ1中断服务程序的入口地址：1536  =  600H     				RAM对应180
#IRQ2中断服务程序的入口地址：2048  =  800H    				RAM对应200
#IRQ3中断服务程序的入口地址：2560  =  A00H    				RAM对应280

#10个数（8、1、5、2、7、9、6、4、3、10）存放的起始地址：3072          	RAM对应300

#累加和的值存放到地址为：3136                                                                             RAM对应310                                               

#IRQ0中断服务程序将地址为3328的存储单元的内容加1         			RAM对应340
#IRQ0中断服务程序将地址为3392的存储单元的内容加1         			RAM对应350
#IRQ0中断服务程序将地址为3456的存储单元的内容加1         			RAM对应360
#IRQ0中断服务程序将地址为3520的存储单元的内容加1         			RAM对应370

#堆栈的起始地址：  3840                           				RAM对应3c0




 	addi $s0,$zero,8                        #第1个数=8（可以修改）保存到(3072+0)
 	sw $s0,3072($zero)

 	addi $s0,$zero,1                        #第2个数=1（可以修改）保存到(3072+4)
 	sw $s0,3076($zero)

 	addi $s0,$zero,5                        #第3个数=5（可以修改）保存到(3072+8)
 	sw $s0,3080($zero)

 	addi $s0,$zero,2                        #第4个数=2（可以修改）保存到(3072+12)
	sw $s0,3084($zero)

 	addi $s0,$zero,7                        #第5个数=7（可以修改）保存到(3072+16)
	sw $s0,3088($zero)

 	addi $s0,$zero,9                        #第6个数=9（可以修改）保存到(3072+20)
 	sw $s0,3092($zero)

 	addi $s0,$zero,6                        #第7个数=6（可以修改）保存到(3072+24)
 	sw $s0,3096($zero)

 	addi $s0,$zero,4                        #第8个数=4（可以修改）保存到(3072+28)
 	sw $s0,3100($zero)

 	addi $s0,$zero,3                        #第9个数=3（可以修改）保存到(3072+32)
 	sw $s0,3104($zero)

 	addi $s0,$zero,10                      #第10个数=10（可以修改）保存到(3072+36)
 	sw $s0,3108($zero)

 	addi $s0,$zero,3072                  #$s0=3072                              排序区间开始地址
 	addi $s1,$zero,3108  	  #$s1=3108=3072+10*4-4       排序区间结束地址        

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
	addi $s1,$zero,3108                 #$s1=3108=3072+10*4-4   排序区间结束地址               
 	beq $s0,$s1,loop2                    #如果$s0=$s1，则转loop2
 	beq $zero,$zero,sort_loop       #转sort_loop

loop2:
	addi $s0,$zero,10                    # n=10 -> s0                              
	addi $s1,$zero,1               	#        1 -> s1              
	addi $s2,$zero,1               	#        1 -> s2
	addi $s3,$zero,0              	#        0 -> s3           
loop3:
	add $s3,$s3,$s1                 	# s3+s1 -> s3                       
	beq $s1,$s0,loop4              	# 如果s1=s0，则转loop4       
	add $s1,$s1,$s2                  	# s1+s2 -> s1     
	beq $zero,$zero,loop3
loop4:
	sw $s3,3136($zero)                	# s3 存到地址为3136的存储单元中

loop5:     beq $zero,$zero,loop5









IRQ0:                                                       #IRQ0中断服务程序的入口地址：1024   =   400H    		RAM对应100            
	addi $sp,$zero,3840    	#push registers  需要保留中断程序用到的寄存器                 $s0    $s1       
  	sw $s0,0($sp)
  	sw $s1,4($sp)

  	addi $s1,$zero,3328              #RAM对应340
  	lw $s0,0($s1)
  	addi $s0,$s0,1
  	sw $s0,0($s1)

  	lw $s1,4($sp)   		#pop registers
  	lw $s0,0($sp)
  	eret







IRQ1: 				#IRQ0中断服务程序的入口地址：1536     =   600H  		RAM对应180            
	addi $sp,$zero,3840    	#push registers  需要保留中断程序用到的寄存器                 $s0    $s1       
  	sw $s0,0($sp)
  	sw $s1,4($sp)

  	addi $s1,$zero,3392              #RAM对应350
  	lw $s0,0($s1)
  	addi $s0,$s0,1
  	sw $s0,0($s1)

  	lw $s1,4($sp)   		#pop registers
  	lw $s0,0($sp)
  	eret





IRQ2: 				#IRQ0中断服务程序的入口地址：2048       =  800H			RAM对应200            
	addi $sp,$zero,3840    	#push registers  需要保留中断程序用到的寄存器      	$s0    $s1        
  	sw $s0,0($sp)
  	sw $s1,4($sp)

  	addi $s1,$zero,3456             #RAM对应360
  	lw $s0,0($s1)
  	addi $s0,$s0,1
  	sw $s0,0($s1)

  	lw $s1,4($sp)   		#pop registers
  	lw $s0,0($sp)
  	eret





IRQ3: 				#IRQ0中断服务程序的入口地址：2560       =  A00H		RAM对应280            
	addi $sp,$zero,3840    	#push registers  需要保留中断程序用到的寄存器              $s0    $s1          
  	sw $s0,0($sp)
  	sw $s1,4($sp)

  	addi $s1,$zero,3520               #RAM对应370
  	lw $s0,0($s1)
  	addi $s0,$s0,1
  	sw $s0,0($s1)

  	lw $s1,4($sp)   		#pop registers
  	lw $s0,0($sp)
  	eret
