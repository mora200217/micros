;===========================================================================
; File        : lab_3.s
; Authors     : Andrés Morales, Oscar Guzmán 
; Date        : 2025-06-06
; Lab         : 3
; Version     : 1.0
; Description : Prueba de módulo de temporizadores. El valor de TMR0 controla
;               un decodificador conectado a LATB. Además, se usa FSR0 como 
;               puntero para recorrer una tabla de patrones y actualizar LATD.
;===========================================================================

;===========================================================================
; Revision History:
; Version  Date        Author(s)               Description
; -------  ----------  ---------------------   ---------------------------------
; 1.0      2025-06-06  A. Morales	       Implementación con TMR0 y FSR0
;===========================================================================

;===========================================================================
; 0. Configuración de archivo     
;===========================================================================

PROCESSOR 18F4550
#include <xc.inc>

CONFIG LVP    = OFF
CONFIG FOSC   = INTOSC_EC
CONFIG WDT    = OFF
CONFIG PBADEN = OFF    ; Entradas digitales del puerto B

;===========================================================================
; 1. Código principal
;===========================================================================

PSECT code, class=CODE, reloc=2

inicio:
    ; Tabla de patrones para LATD en RAM (0x00 a 0x03)
    movlw   0b101
    movwf   0x00        ; Magenta 

    movlw   0b001
    movwf   0x01        ; Azul

    movlw   0b011
    movwf   0x02        ; Cyan

    movlw   0b010
    movwf   0x03        ; Verde
    
    movlw   0b110
    movwf   0x04        ; Amarillo
    
    movlw   0b111
    movwf   0x05       ; Blanco

    ; Inicialización del puntero
    movlw   0xFF        ; Apunta a la dirección 0x00 (Apunta a la dirección 0xFF, pero por efecto de desbordamiento con el INCF llega a 0x00)
    movwf   FSR0

    ; Configurar PORTD como salida
    clrf    TRISD ;(Configurar PORTD como salida)
    clrf    LATD  ;(Configurar salida en 0 o desenergizada)
    

main:
    movlw   10
    ; Reflejar el valor de TMR0 en LATB (decodificador)
    movwf TMR0
    movff   TMR0, LATB ; TMR0 -> LATB

    ; Si TMR0 < WREG (2), llamar a resetCounter
    cpfslt  TMR0    ; Si TMR0 < WREG no ejecuta a call resetCounter (Skip if (f) < (W) )
    call    resetCounter

    ; Actualizar salida con el contenido apuntado por FSR0
    movff   INDF0, LATD ; (Operando o "registro virtual") INDF0 -> LATD

    ; Reiniciar puntero si llegó al final (6)
    movlw   6
    cpfslt  FSR0    ;Si FSR0 < WREG no ejecuta a clrf FSR0 (Skip if (f) < (W) )
    clrf    FSR0
    
    
    goto main
    
;===========================================================================
; 2. Subrutinas
;===========================================================================

resetCounter:
    clrf    TMR0       ; Reiniciar temporizador
    incf    FSR0       ; Avanzar al siguiente patrón
    return

END