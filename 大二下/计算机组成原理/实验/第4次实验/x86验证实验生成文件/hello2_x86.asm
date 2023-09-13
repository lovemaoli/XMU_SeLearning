IF 0  
    Build this template with "CONSOLE ASSEMBLE AND LINK"
ENDIF  
__UNICODE__ equ 1
include \masm32\include\masm32rt.inc

.code
start:
    call main
    inkey
    exit
main proc
    cls
    print "Hello World in UNICODE",13,10
    ret
main endp
end start
