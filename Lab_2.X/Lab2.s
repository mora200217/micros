;===========================================================================
; File        : micros_2.s
; Authors     : Andrés Morales, Oscar Guzmán 
; Date        : 2025-20-05
; Lab         : 2
; Version     : 1.0
; Description : se plantea el desarrollo de cuatro algoritmos, el primero para análisis y los otros para diseño a partir del uso de un led RGB.
;               Compilado con pic-as (diferente a mpasm clásico
;               de la versión 3.2 de MPLAB X).
;===========================================================================

;===========================================================================
; Revision History:
; Version  Date        Author(s)              Description
; -------  ----------  ---------------------  ---------------------------------
; 1.0      2025-04-24  O. Guzmán              Primer retardo de 1 s
;===========================================================================


;===========================================================================
; 0. Configuración de archivo     
;===========================================================================

#include "xc.inc"
    
CONFIG FOSC=INTOSC_EC
    
CONFIG WDT=OFF

aux1 equ 0x00
aux2 equ 0x01
aux3 equ 0x02
 
PSECT code, class=CODE, reloc = 2
 
inicio:
    bcf TRISD,0
    bcf TRISD,1 
    bcf TRISD,2  
Menu:
    bsf LATD,2
    
    bsf LATD,1
    
    bcf LATD,2
    
    bsf LATD,0
    
    bsf LATD,2
    
    bcf LATD,1
    
    bsf LATD,2
    
    bcf LATD,2
    
    bcf LATD,0
    
    BRA Menu
Retardo:
	movlw 50
	movwf aux1
	movlw 62
	movwf aux2
	movlw 26
	movwf aux3
AuxRetardo:
	decfsz aux1,f
	goto AuxRetardo
	movlw 50
	movwf aux1
	decfsz aux2,f
	goto AuxRetardo
	movlw 62
	movwf aux2
	decfsz aux3,f
	goto AuxRetardo
	return
end