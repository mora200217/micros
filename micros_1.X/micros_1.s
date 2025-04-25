;===============================================================
; File        : micros_1.s
; Authors     : Andrés Morales, Oscar Guzmán 
; Date        : 2025-04-23
; Lab         : 1 
; Version     : 1.0
; Description : Introducción a las instrucciones en ensamblador. 
;               Compilado con pic-as (diferente a mpasm clásico
;               de la versión 3.2 de MPLAB X).
;===============================================================
; Revision History:
; Version  Date        Author(s)              Description
; -------  ----------  ---------------------  ----------------------------
; 1.0      2025-04-24  A. Morales, O. Guzmán  Versión inicial.
;===============================================================

;===============================================================
; 0. Configuración de archivo     
;===============================================================

    processor   18F4550          ; Definir el PIC a utilizar
    #include	<xc.inc>	 ;Incluir definiciones del compilador pic-as

;===============================================================
; 1. Declaración de variables 
;=============================================================== 

    aux1    EQU     0x01          ; Variable temporal 1
    aux2    EQU     0x02          ; Variable temporal 2
    aux3    EQU     0x03          ; Variable temporal 2
    aux4    EQU     0x04          ; Variable temporal 2

;===============================================================
; 2. Código principal 
;===============================================================     

    PSECT code, class=CODE, reloc=2

 ; Para fines de organización, cada etiqueta representará un 
 ; ejercicio. Se nombrará ex_<i> 
    
 
    ex_1:			
        movlw	    0x07
	movwf	    aux1
	movlw	    0x02
	addwf	    aux1
	
    
    ex_2: 
	movlw	    0x08
	movwf	    aux1
	
	movlw	    0x0A
	movwf	    aux2
	
	movf	    aux1, w	; Movemos a WREG para operar 
	addwf	    aux2, w
	
	
	
	
    

    loop: 
        goto    $              ; Bucle infinito
	

;===============================================================
; End of file
;===============================================================

	END