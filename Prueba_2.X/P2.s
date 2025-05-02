#include "xc.inc"
    
CONFIG FOSC=INTOSC_EC
    
CONFIG WDT=OFF

aux1 equ 0x00
PSECT code, class=CODE, reloc = 2
 
inicio:
    bcf TRISD,0
Menu:
    bsf LATD,0
    call Retardo
    bcf LATD,0
    call Retardo
    goto Menu
Retardo:
    movlw 0x01
    movwf aux1
AuxRetardo:
    decfsz aux1,f ;Decrementar y preguntar si el resultado es 0
    goto AuxRetardo
    return
end

