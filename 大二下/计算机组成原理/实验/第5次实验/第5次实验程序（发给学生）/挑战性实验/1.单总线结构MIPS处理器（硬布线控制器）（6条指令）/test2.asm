#单总线结构MIPS处理器测试程序                             test2.asm
#测试6条指令 （lw、sw、beq、addi、slt、add）                 
#程序执行完   100、101、102单元的内容分别为：8、9、a

main:
 	addi $s0,$zero,8                          #s0=8
 	sw $s0,1024($zero)		    #s0=8 保存到(1024，即100单元)

 	addi $s0,$zero,9                        #s0=9
 	sw $s0,1028($zero)		   #s0=9 保存到(1028，即101单元)

 	lw $s1,1024($zero)                    #$s1=8
	lw $s2,1028($zero)                	   #$s2=9

                slt $s3,$s1,$s2                            # s1 < s2       s3=1

 	beq $s1,$s2,loop1   	  #s1不等于s2      执行下一条指令

                add $s4,$s3,$s2                              # s4=1+9=10=a

                sw $s4,1032($zero)                   #s4=10=a   保存到(1032，即102单元)        

                beq $zero,$zero,loop2	  #转loop2                       

loop1:
               addi $s4,$zero,2                        #s4=2                                 		这条指令不会执行到
               sw $s4,1032($zero)                   #s4=2 保存到(1032，即102单元)            这条指令不会执行到   

loop2:
              beq $zero,$zero,loop2	  #转loop2             死循环