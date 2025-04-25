
    processor 18F4550
    #include <xc.inc>
    
    ORG 0x0000
    
    CONFIG FOSC	    = INTOSC_EC ; Oscilador interno
    CONFIG WDT	    = OFF
    

    PSECT code, class = CODE, reloc = 2
	setup: 
	    bcf	    TRISD, 0 ; Salida
	    
	main: 
	    bsf	    LATD, 0  ; Aumentar 
	    bcf	    LATD, 0  ; Aumentar 
	    
	    goto main

    
    
    