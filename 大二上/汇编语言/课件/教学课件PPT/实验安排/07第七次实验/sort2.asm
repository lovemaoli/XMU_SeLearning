.MODEL        SMALL
.STACK
.DATA
           SOURCENUMBERS  DB        64
              DB        0
       ARRAY  EQU       THIS BYTE
              DB        64 DUP('$')
           PROMPTSTRINGA  DB        0AH,0DH,'input string:',0AH,0DH,'$'
           PROMPTSTRINGB  DB        0AH,0DH,'output string:',0AH,0DH,'$'
.CODE
.startup
              MOV       DX,OFFSET PROMPTSTRINGA
              MOV       AH,09H
              INT       21H

              ;读入数字，以数组的形式
              MOV       DX,OFFSET SOURCENUMBERS
              MOV       AH,0AH
              INT       21H

              MOV       AL, [SOURCENUMBERS+1]
              MOV       AH,0H
              MOV       CX,AX		;CX←数组元素个数
              ;输出提示
              MOV       DX,OFFSET PROMPTSTRINGB
              MOV       AH,09H
              INT       21H

              DEC       CX          ;元素个数减1为外循环次数
      OUTLP:  MOV       DX,CX       ;DX←内循环次数
              MOV       BX,OFFSET ARRAY	;BX是当前处理位置的偏移指针
       INLP:  					     ;取前一个元素
									;与后一个元素比较
              JNA       NEXT		;前一个不大于后一个元素，则不进行交换
									;否则，交换两个元素
              
       NEXT:  			            ;下一次循环（改变BX、DX的值），请补全
              
              JNZ       INLP        ;内循环尾（如果内循环剩余次数还不是0，那么继续做内循环）
              LOOP      OUTLP       ;外循环尾（否则，做外循环）
   OUPUTING:  MOV       DX,OFFSET ARRAY
              MOV       AH,09H
              INT       21H
.EXIT         0
              END
