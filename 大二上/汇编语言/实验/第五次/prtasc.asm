        DATA  SEGMENT
    UPSTRING  DB        0AH,0DH,'$'
        DATA  ENDS

        CODE  SEGMENT
              ASSUME    CS:CODE,DS:DATA

      START:


   LINELOOP:



 CHANGELINE:


     ENDPRO:  MOV       AX,4C00H
              INT       21H
        CODE  ENDS
              END       START

