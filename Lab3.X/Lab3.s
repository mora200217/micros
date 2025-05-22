
    processor   18F4550              ; Definir el PIC a utilizar
    #include    <xc.inc>             ; Incluir definiciones del compilador pic-as
    CONFIG FOSC = INTOSC_EC
    CONFIG LVP = OFF
    CONFIG PBADEN = OFF
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



inicio; RB7 Rojo, RB6  Amarillo, RB5 Verde
	movlw b00011111 
	movwf TRISB
	clrf LATB
	bcf INTCON2, INTEDG0 ;bajada
	bcf INTCON, INT0IF ;Apagar
	bsf INTCON, INT0IE ;interruptor
	bsf INTCON, GIE ;tacos
Menu
Verde
	movlw b00100000
	movwf LATB
	goto Verde
Amarillo
	movlw b01000000
	movwf LATB
Rojo
	movlw b10000000
	movwf LATB
RojoAmarillo
	movlw b'10000000'
	movwf LATB
	bcf INTCON, INT0IF
	goto Menu
END