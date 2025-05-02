;===============================================================
; File        : micros_1.s
; Authors     : Andrés Morales, Oscar Guzmán 
; Date        : 2025-04-23
; Lab         : 1 
; Version     : 2.0
; Description : Introducción a las instrucciones en ensamblador. 
;               Compilado con pic-as (diferente a mpasm clásico
;               de la versión 3.2 de MPLAB X).
;===============================================================
; Revision History:
; Version  Date        Author(s)              Description
; -------  ----------  ---------------------  ----------------------------
; 1.0      2025-04-24  A. Morales, O. Guzmán  Versión inicial.
; -------  ----------  ---------------------  ----------------------------
; 2.0      2025-05-02  A. Morales, O. Guzmán  Adición ejercicios pares.
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
	
	call clean 
	
 
    ex_2: 
	movlw 0x08; 8->W
        movwf aux1; W->aux1
    
	movlw 0x0A; 10->W
	movwf aux2; W->aux2
	
	movf aux1, w; aux1 ->w
        addwf aux2, w; W + aux2 -> W
	
	call clean 
	
    ex_3: 
	movlw	    0x05
	movwf	    aux1
	movf	    aux1, w	; cargo a WREG
	sublw	    0x09
	
	call clean 
	
	;sublw	    0x07
    ex_4: 
	movlw 0x06; 6->W
	movwf aux1; W->aux1
         
	movlw 0x04; 4->W
	movwf aux2; W->aux2
    
	movf aux1,w; aux1->W
	subwf aux2; aux2-W -> aux2

    ex_5: 
	movlw	    4
	movwf	    aux1 ; Asignacion de valor 
	
	movlw	    5
	mulwf	    aux1, 1
	movf	    PRODL, w		; No se necesita el bloque superior 
	
    ex_6:
	movlw 0x0C; 12->W
	movwf aux1; W->aux1
    
	movlw 0x0F; 15->W
	movwf aux2; W->aux2
    
	movf aux1,w; aux1 -> W    
	mulwf aux2; W * aux2 -> PRODL    
	movf PRODL, w; PRODL -> W
	movwf aux2; 

    
    ex_7: 
	movlw	    12 
	movwf	    aux1 
	
	comf	    aux1,   0
	
    ex_8:
	movlw 0x0C; 12->W
	movwf aux1; W->aux1
    
	negf aux1;  -aux1 + 1 -> aux1$
	
    ex_9:
	movlw	35
	movwf	aux1 
	
	movlw	7
	
	iorwf	aux1, 0
	
	
    ex_10:
	movlw 0x14; 20->W      0001 0100
	movwf aux1; W->aux1    0011 1000
    
	movlw 0x38; 56->W      0011 1100 = 3C = 48 + 12 = 60
	movwf aux2; W->aux2
    
	movf aux1,w; aux1->W
	iorwf aux2, w; W or aux2 -> W
	
    ex_11:
	movlw	    62; 
	movwf	    aux1
	
	movlw	    15
	andwf	    aux1, 0
	
	
    ex_12:
	movlw 0x64; 100->W     0110 0100
	movwf aux1; W->aux1    0010 1110
			 ;     0010 0100 = 24 = 36
	movlw 0x2D; 45->W
	movwf aux2; W->aux2
    
	movf aux1, w; aux1->W
	andwf aux2,w; W and aux2 -> W
	
    ex_13:
	movlw	    120
	movwf	    aux1
	
	movlw	    1
	xorwf	    aux1, 0
	
    ex_14:
	movlw 0x11; 17->W     0001 0001
	movwf aux1; W->aux1   0101 1010
    
	movlw 0x5A; 90->W     0100 1011 = 4B = 75
	movwf aux2; W->aux2
    
	movf aux1, w; aux1->W
	xorwf aux2, w; w xor aux2 -> W
	
	
    ex_15:
	movlw	    25;
	movwf	    aux1
	
	movlw	    40;
	movwf	    aux2
	
	movlw	    103;
	movwf	    aux3

	movlw 0x06; 6->W
	movwf aux1; W->aux1
         
	movlw 0x04; 4->W
	movwf aux2; W->aux2
    
	movf aux1,w; aux1->W
	subwf aux2; aux2-W -> aux2
	
    ex_16: 
	movlw 0x12; 18->W
	movwf aux1; W->aux1
    
	movlw 0x3C; 60->W
	movwf aux2; W->aux2
    
	movlw 0x10; 16->W
	movwf aux3; W->aux3
    
	movf aux1,w; aux1 -> W
	addwf aux2; W(aux1) + aux2 -> aux2
    
	movf aux3,w; aux3 -> W
	sublw 0b11010; 0b11010 - W -> W    ; 0b11010 = 26
	mullw 0x03; 0x03 * W -> PRODL
    
	movf PRODL,W; PRODL->w
	addwf aux2, w; aux2 + W -> W
	movwf aux4; W -> aux4
	
	movf	    aux1, w
	iorwf	    aux2, 0 ; quede en WREG
	movwf	    aux4	; Reusltado parcial 
	
	movf	    aux3,   w
	xorlw	    0xD0	; Que quede en WREG
	
	andwf	    aux4,   1

    loop: 
        goto    ex_1              ; Bucle infinito
	
    clean:
	clrf	aux1
	clrf	aux2
	clrf	aux3
	clrf	aux4
	
	return 
	

;===============================================================
; End of file
;===============================================================

	END
