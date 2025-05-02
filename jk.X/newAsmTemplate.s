
#include "xc.inc"

    ; Aquí empieza el código
    ; Puedes definir una etiqueta de inicio como esta:
    aux1 equ 0x00
    aux2 equ 0x01
    aux3 equ 0x02
    aux4 equ 0x03
PSECT code, class=CODE, reloc = 2
 
inicio:
    ;PRIMER PUNTO: 
    movlw 0x07; 7->W
    movwf aux1; W->aux1
        
    addlw 0x03; W + 0x03 -> W
    movwf aux1; W->aux1
    
    ;1. El addlw k, necesita de una literal, no una variable de acceso RAM
    
    ;2. Con el addwf varx, por defecto la suma se guarda en varx. De ser 
    ;   necesario, se puede agregar un ", w" para guardarlo en WRITE
    
    ;SEGUNDO PUNTO:
    movlw 0x08; 8->W
    movwf aux1; W->aux1
    
    movlw 0x0A; 10->W
    movwf aux2; W->aux2
   
    movf aux1, w; aux1 ->w
    addwf aux2, w; W + aux2 -> W	 
    
    ;TERCER PUNTO:
    movlw 0x05; 5->W
    movwf aux1; W->aux1
    
    movf aux1, w; aux1->W
    sublw 0x09; 0x09-W -> W
    
    ;CUARTO PUNTO:
    movlw 0x04; 4->W
    movwf aux2; W->aux2
    
    movlw 0x06; 6->W
    movwf aux1; W->aux1
         
    subwf aux2, w; aux2-W -> W		
    
    ;QUINTO PUNTO:
    movlw 0x05; 5->W
    movwf aux1; W->aux1
    
    mullw 0x04; W * 0x04 -> PRODL
    
    ;SEXTO PUNTO:
    movlw 0x0C; 12->W
    movwf aux1; W->aux1
    
    movlw 0x0F; 15->W
    movwf aux2; W->aux2
    
    mulwf aux1; W * aux1 -> PRODL      
    
    ;SEPTIMO PUNTO:
    movlw 0x0C; 12->W
    movwf aux1; W->aux1
    
    comf aux1;
    
    ;OCTAVO PUNTO:
    movlw 0x0C; 12->W
    movwf aux1; W->aux1
    
    negf aux1;
    
    ;NOVENO PUNTO:
    movlw 0x23;	35->W
    movwf aux1	; W->aux1
    
    iorlw 0x07; W or 0x07 -> W
    
    ;DÉCIMO PUNTO:
    movlw 0x14; 20->W
    movwf aux1; W->aux1
    
    movlw 0x38; 56->W
    movwf aux2; W->aux2
    
    iorwf aux1, W; W or aux1 -> W
    
    ;UNDÉCIMO PUNTO:
    movlw 0x3D; 62->W
    movwf aux1; W->aux1
    
    andlw 0x0F; W and 0x0F -> W
    
    ;DUODÉCIMO PUNTO:
    movlw 0x64; 100->W
    movwf aux1; W->aux1
    
    movlw 0x2D; 45->W
    movwf aux2; W->aux2
    
    andwf aux1,w    ; W and aux2 -> W
    
    ;TRECEAVO PUNTO:
    movlw 0x78; 120->W
    movwf aux1; W->aux1
    
    xorlw 0x01; w xor 0x01 ->W
    
    ;CATORCEAVO PUNTO:
    movlw 0x11; 17->W
    movwf aux1; W->aux1
    
    movlw 0x5A; 90->W
    movwf aux2; W->aux2
    
    xorwf aux1, w; w xor aux1 -> W
    
    ;QUINCEAVO PUNTO:
    movlw 0x19; 25->W
    movwf aux1; W->aux1
    
    movlw 0x28; 40->W
    movwf aux2; W->aux2
    
    movlw 0x67; 103->W
    movwf aux3; W->aux3 
    
    movf aux1,w; aux1 -> W
    iorwf aux2; aux2 or W -> aux2;
    
    movf aux3,w; aux3 -> W
    xorlw 0xD0; W xor D0 -> W
    
    andwf aux2,w; aux2 and W;
    movwf aux4; W -> aux4
         
    ;DECIMOSEXTO PUNTO:
    ;Finalmente se debe realizar la siguiente operación, con aux1, aux2 y aux3 previamente
;cargadas con 18, 60 y 16 respectivamente:

;aux4 ? (aux1 + aux2) ? 3 ? (aux3 ? 0b11010)
    movlw 0x12; 18->W
    movwf aux1; W->aux1
    
    movlw 0x3C; 60->W
    movwf aux2; W->aux2
    
    movlw 0x10; 16->W
    movwf aux3; W->aux3
    
    movf aux1,w; aux1 -> W
    addwf aux2; aux1 + aux2 -> aux2
    
    movf aux3,w; aux3 -> W
    sublw 0b11010; 0b11010 - W -> W
    mullw 0x03; 0x03 * W -> W
    
    movf PRODL,W;
    addwf aux2, w; aux2 + W -> W
    movwf aux4; W -> aux4
    goto inicio ; bucle infinito
    
    
    end

