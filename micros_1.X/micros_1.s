;===========================================================================
; File        : micros_1.s
; Authors     : Andrés Morales, Oscar Guzmán 
; Date        : 2025-04-23
; Lab         : 1 
; Version     : 2.0
; Description : Introducción a las instrucciones en ensamblador. 
;               Compilado con pic-as (diferente a mpasm clásico
;               de la versión 3.2 de MPLAB X).
;===========================================================================

;===========================================================================
; Revision History:
; Version  Date        Author(s)              Description
; -------  ----------  ---------------------  ---------------------------------
; 1.0      2025-04-24  A. Morales, O. Guzmán  Versión inicial.
; 2.0      2025-05-02  A. Morales, O. Guzmán  Adición ejercicios pares.
;===========================================================================


;===========================================================================
; 0. Configuración de archivo     
;===========================================================================

    processor   18F4550              ; Definir el PIC a utilizar
    #include    <xc.inc>            ; Incluir definiciones del compilador pic-as

;===========================================================================
; 1. Declaración de variables 
;===========================================================================

    aux1    EQU     0x01            ; Variable temporal 1
    aux2    EQU     0x02            ; Variable temporal 2
    aux3    EQU     0x03            ; Variable temporal 3
    aux4    EQU     0x04            ; Variable temporal 4

;===========================================================================
; 2. Código principal 
;===========================================================================

PSECT code, class=CODE, reloc=2

; Cada etiqueta representa un ejercicio, nombrado ex_<n>

ex_1:
    movlw   0x07
    movwf   aux1                   ; 7 -> aux1

    movlw   0x03
    addwf   aux1                   ; aux1 + 3 -> aux1

    call    clean


ex_2:
    movlw   0x08
    movwf   aux1                   ; 8 -> aux1

    movlw   0x0A
    movwf   aux2                   ; 10 -> aux2

    movf    aux1, w
    addwf   aux2, w                ; W(aux1) + aux2 -> W

    call    clean


ex_3:
    movlw   0x05
    movwf   aux1

    movf    aux1, w
    sublw   0x09                   ; 9 - W(aux1) -> W

    call    clean


ex_4:
    movlw   0x06
    movwf   aux1

    movlw   0x04
    movwf   aux2

    movf    aux1, w
    subwf   aux2                   ; aux2 - W(aux1) -> aux2


ex_5:
    movlw   0x04
    movwf   aux1

    movlw   0x05
    mulwf   aux1, 1
    movf    PRODL, w               ; Resultado -> W


ex_6:
    movlw   0x0C
    movwf   aux1

    movlw   0x0F
    movwf   aux2

    movf    aux1, w
    mulwf   aux2
    movf    PRODL, w
    movwf   aux2


ex_7:
    movlw   0x0C
    movwf   aux1

    comf    aux1, 0


ex_8:
    movlw   0x0C
    movwf   aux1

    negf    aux1                   ; -aux1 + 1 -> aux1


ex_9:
    movlw   35
    movwf   aux1

    movlw   7
    iorwf   aux1, 0


ex_10:
    movlw   0x14                   ; 20
    movwf   aux1

    movlw   0x38                   ; 56
    movwf   aux2

    movf    aux1, w
    iorwf   aux2, w


ex_11:
    movlw   62
    movwf   aux1

    movlw   15
    andwf   aux1, 0


ex_12:
    movlw   0x64                   ; 100
    movwf   aux1

    movlw   0x2D                   ; 45
    movwf   aux2

    movf    aux1, w
    andwf   aux2, w


ex_13:
    movlw   120
    movwf   aux1

    movlw   1
    xorwf   aux1, 0


ex_14:
    movlw   0x11
    movwf   aux1

    movlw   0x5A
    movwf   aux2

    movf    aux1, w
    xorwf   aux2, w


ex_15:
    movlw   25
    movwf   aux1

    movlw   40
    movwf   aux2

    movlw   103
    movwf   aux3

    movlw   0x06
    movwf   aux1

    movlw   0x04
    movwf   aux2

    movf    aux1, w
    subwf   aux2                   ; aux2 - aux1 -> aux2


ex_16:
    movlw   0x12
    movwf   aux1

    movlw   0x3C
    movwf   aux2

    movlw   0x10
    movwf   aux3

    movf    aux1, w
    addwf   aux2                   ; aux2 + aux1 -> aux2

    movf    aux3, w
    sublw   0b11010                ; 26 - aux3 -> W
    mullw   0x03                   ; *3 -> PRODL

    movf    PRODL, w
    addwf   aux2, w
    movwf   aux4

    movf    aux1, w
    iorwf   aux2, 0
    movwf   aux4

    movf    aux3, w
    xorlw   0xD0
    andwf   aux4, 1


loop:
    goto    ex_1


clean:
    clrf    aux1
    clrf    aux2
    clrf    aux3
    clrf    aux4
    return


;===========================================================================
; End of file
;===========================================================================

    END
