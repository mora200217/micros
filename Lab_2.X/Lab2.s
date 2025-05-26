;===========================================================================
; File        : micros_2.s
; Authors     : Andrés Morales, Oscar Guzmán 
; Date        : 2025-20-05
; Lab         : 2
; Version     : 2.0
; Description : se plantea el desarrollo de cuatro algoritmos, el primero para análisis y los otros para diseño a partir del uso de un led RGB.
;               Compilado con pic-as (diferente a mpasm clásico
;               de la versión 3.2 de MPLAB X).
;===========================================================================

;===========================================================================
; Revision History:
; Version  Date        Author(s)               Description
; -------  ----------  ---------------------   ---------------------------------
; 1.0      2025-04-24  O. Guzmán               Primer retardo de 1 s
; 2.0      2025-04-25  O. Guzmán - A. Morales  Código Final
; 3.0      2025-04-26  O. Guzmán - A. Morales  Bono 
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
    bcf TRISD,0	;Inicializar el pin 0 del puerto D como salida
    bcf TRISD,1	;Inicializar el pin 1 del puerto D como salida
    bcf TRISD,2	;Inicializar el pin 2 del puerto D como salida
    
Menu:
    ;Color azul
    bsf LATD,2 ;Energizar salida; poner en 1 la salida del pin 2 del puerto D (color azul) 
    
    ;Color cyan
    bsf LATD,1 ;Energizar salida; poner en 1 la salida del pin 1 del puerto D (color verde) 
    
    ;Color verde
    bcf LATD,2 ;Desenergizar salida; poner en 0 la salida del pin 2 del puerto D (color azul) 
    
    ;Color Amarillo
    bsf LATD,0 ;Energizar salida; poner en 1 la salida del pin 0 del puerto D (color rojo) 
    
    ;Color Blanco
    bsf LATD,2 ;Energizar salida; poner en 1 la salida del pin 2 del puerto D (color azul) 
    
    ;Color Magenta
    bcf LATD,1 ;Desenergizar salida; poner en 0 la salida del pin 1 del puerto D (color verde) 
    
    ;Color Rojo
    bcf LATD,2 ;Desenergizar salida; poner en 0 la salida del pin 2 del puerto D (color azu) 
    
    ;Color Negro
    bcf LATD,0 ;Desenergizar salida; poner en 0 la salida del pin 0 del puerto D (color rojo) 
    
    BRA Menu
end