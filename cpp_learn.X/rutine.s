; rutina.s (sin incluir xc.inc)
   PROCESSOR 18F4550
   GLOBAL _my_rutine
    
   #define TRISD_ADDR  0xF95
    #define LATD_ADDR   0xF8C
    
_my_rutine:
        ; Tu código en ensamblador aquí
        clrf    TRISD_ADDR              ; Configura todos los pines de PORTD como salida
        clrf    LATD_ADDR             ; Enciende todos los colores inicialmente
loop: 
	
	; Azul
        bsf     LATD_ADDR, 2
	
        ; Cyan (Azul + Verde)
        bsf     LATD_ADDR, 1
        ; Verde
        bcf     LATD_ADDR, 2
        ; Amarillo (Verde + Rojo)
        bsf     LATD_ADDR, 0
        ; Blanco (Rojo + Verde + Azul)
        bsf     LATD_ADDR, 2
	
        ; Magenta (Rojo + Azul)
        bcf     LATD_ADDR, 1
	    
        ; Rojo
        bcf     LATD_ADDR, 2
        ; Apagado (Negro)
        bcf     LATD_ADDR, 0
        goto loop
END