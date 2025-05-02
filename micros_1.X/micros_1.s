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
    aux3    EQU     0x03          ; Variable temporal 3
    aux4    EQU     0x04          ; Variable temporal 4
    

;===============================================================
; 2. Código principal 
;=============================================================== 

PSECT code, class=CODE, reloc=2

 ; Para fines de organización, cada etiqueta representará un 
 ; ejercicio. Se nombrará ex_<i> 
    
    ex_1:		
	;  Sumar 3 a la variable aux1 cargada previamente con el valor de 7.
        movlw	    0x07
	movwf	    aux1 ; Cargar la variable
	
	movlw	    0x03
	addwf	    aux1
 
    ex_2: 
	movlw	    0x08
	movwf	    aux1 ; Condiocion que dice robin
	
	movlw	    0x0A
	movwf	    aux2
	
	movf	    aux1, w	; Movemos a WREG para operar 
	addwf	    aux2, w
	
    ex_3: 
	movlw	    0x05
	movwf	    aux1
	movf	    aux1, w	; cargo a WREG
	sublw	    0x09
	
	;sublw	    0x07
	
    ex_4: 
    
    ex_5: 
	movlw	    4
	movwf	    aux1 ; Asignacion de valor 
	
	movlw	    5
	mulwf	    aux1, 1
	movf	    PRODL, w		; No se necesita el bloque superior 
	
    
    ex_7: 
	movlw	    12 
	movwf	    aux1 
	
	comf	    aux1,   0
	
    ex_9:
	movlw	35
	movwf	aux1 
	
	movlw	7
	
	iorwf	aux1, 0
	
    ex_11:
	movlw	    62; 
	movwf	    aux1
	
	movlw	    15
	andwf	    aux1, 0
	
    ex_13:
	movlw	    120
	movwf	    aux1
	
	movlw	    1
	xorwf	    aux1, 0
	
    ex_15:
	movlw	    25;
	movwf	    aux1
	
	movlw	    40;
	movwf	    aux2
	
	movlw	    103;
	movwf	    aux3
	
	
	movf	    aux1, w
	iorwf	    aux2, 0 ; quede en WREG
	movwf	    aux4	; Reusltado parcial 
	
	movf	    aux3,   w
	xorlw	    0xD0	; Que quede en WREG
	
	andwf	    aux4,   1
	
	
	
	
	
	
	
	
	
	
	
	
    
    
	
	
    loop: 
        goto    ex_1              ; Bucle infinito
	

;===============================================================
; End of file
;===============================================================

	END