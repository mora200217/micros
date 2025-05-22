;===========================================================================
; File        : micros_1.s
; Authors     : Andr�s Morales, Oscar Guzm�n 
; Date        : 2025-04-23
; Lab         : 1 
; Version     : 2.0
; Description : Introducci�n a las instrucciones en ensamblador. 
;               Compilado con pic-as (diferente a mpasm cl�sico
;               de la versi�n 3.2 de MPLAB X).
;===========================================================================

;===========================================================================
; Revision History:
; Version  Date        Author(s)              Description
; -------  ----------  ---------------------  ---------------------------------
; 1.0      2025-04-24  A. Morales, O. Guzm�n  Versi�n inicial.
; 2.0      2025-05-02  A. Morales, O. Guzm�n  Adici�n ejercicios pares.
;===========================================================================


;===========================================================================
; 0. Configuraci�n de archivo     
;===========================================================================

    processor   18F4550              ; Definir el PIC a utilizar
    #include    <xc.inc>             ; Incluir definiciones del compilador pic-as

;===========================================================================
; 1. Declaraci�n de variables 
;===========================================================================

    aux1    EQU     0x01            ; Variable temporal 1
    aux2    EQU     0x02            ; Variable temporal 2
    aux3    EQU     0x03            ; Variable temporal 3
    aux4    EQU     0x04            ; Variable temporal 4

;===========================================================================
; 2. C�digo principal 
;===========================================================================

PSECT code, class=CODE, reloc=2

; Cada etiqueta representa un ejercicio, nombrado ex_<n>

ex_1:
    movlw   0b10000000
    movwf   aux1                   ; 7 -> aux


;===========================================================================
; End of file
;===========================================================================

    END
