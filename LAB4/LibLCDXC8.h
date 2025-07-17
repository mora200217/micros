/* 
 * File:   LibLCDXC8.h
 * Author: Robin
 *
 * Created on 2 de septiembre de 2018, 08:15 PM
 */

// ---------- Protección contra inclusiones múltiples del archivo ----------
/*
 * Esta directiva asegura que el contenido del archivo .h solo se incluya una vez,
 * incluso si es llamado varias veces en diferentes archivos fuente.
 * Esto evita errores de redefinición durante la compilación. ifndef
 * 
 * Las siguientes macros definen los pines del PIC usados para conectar el LCD.
 * Si el usuario ya definió estas macros en su archivo principal,
 * estas definiciones se ignoran, permitiendo flexibilidad.
 */
#ifndef LIBLCDXC8_H
#define	LIBLCDXC8_H

#ifdef	__cplusplus  //Esto asegura compatibilidad con compiladores C++: les indica que el contenido del archivo se debe tratar como código C, para evitar el name mangling que hace C++
extern "C" {
#endif


#ifdef	__cplusplus
}
#endif
#include<xc.h>
#ifndef _XTAL_FREQ
#define _XTAL_FREQ 20000000 //Define la frecuencia del oscilador (20 MHz) si no ha sido definida ya
#endif
#ifndef Datos
#define Datos LATD	//El puerto de conexion de los datos el cual se puede cambiar
#endif
#ifndef RS
#define RS LATA4	//Los pines de control al LCD los cuales se
#endif
 
/*
 * RS sirve para leer o escribir, define el tipo de operación:
 * Si es un comando (como limpiar pantalla, mover cursor),
 * o si es un dato (como escribir letras).
*/

#ifndef E
#define E LATA5	//pueden cambiar 
#endif

// Comando para OCULTAR el cursor
#define CURSOR_OFF 0x0C    // Display ON, Cursor OFF, Blink OFF

// Comando para MOSTRAR el cursor  
#define CURSOR_ON  0x0F    // Display ON, Cursor ON, Blink ON

// Comando para cursor sin parpadeo
#define CURSOR_NO_BLINK 0x0E  // Display ON, Cursor ON, Blink OFF



unsigned char LeerTeclado(void);

unsigned char interfaz=8;

void ConfiguraLCD(unsigned char);
void RetardoLCD(unsigned char);
void EnviaDato(unsigned char);
void InicializaLCD(void);
void HabilitaLCD(void);
void BorraLCD(void);
void CursorAInicio(void);
void ComandoLCD(unsigned char);
void EscribeLCD_c(unsigned char);
void EscribeLCD_n8(unsigned char, unsigned char);
void EscribeLCD_n16(unsigned int, unsigned char);
void EscribeLCD_d(double, unsigned char, unsigned char);
void MensajeLCD_Var(char *);
void DireccionaLCD(unsigned char);
void FijaCursorLCD(unsigned char,unsigned char);
void DesplazaPantallaD(void);
void DesplazaPantallaI(void);

void DesplazaCursorD(void);
void DesplazaCursorI(void);

void EraseDigit(unsigned char *Temp, unsigned char *cursorPos);

void StartCount(unsigned char totalPiezas, unsigned char *Temp, unsigned char *cursor_pos, unsigned char *inactividad);

void SETUP_RGB(unsigned char piezasContadas);

unsigned char numDigits(unsigned int n);

void PARADA(void);

void RevisarTeclaESP(void);

void PunteroTeclaESP(unsigned char *conteoPiezas, unsigned char *totalPiezas);

void BackLight(void);

void ReiniciarCuenta(unsigned char *piezasContadas, unsigned char *totalPiezas);

void finConteo(unsigned char *piezasContadas, unsigned char *totalPiezas);

void Buzzer(void);

void OcultarCursor(void);
void MostrarCursor(void);
void CursorSinParpadeo(void);



void ConfiguraLCD(unsigned char a){
	if(a==4 | a ==8)
		interfaz=a;	
}
void EnviaDato(unsigned char a){
	if(interfaz==4){
		Datos=(Datos & 0b00001111) | (a & 0b11110000);
		HabilitaLCD();
		RetardoLCD(1);
		Datos=(Datos & 0b00001111) | (a<<4);
		//HabilitaLCD();
		//RetardoLCD(1);
	}else if(interfaz==8){
		Datos=a;
	}	
}
void InicializaLCD(void){
//Funci�n que inicializa el LCD caracteres
	RS=0;
	if(interfaz==4)
		Datos=(Datos & 0b00001111) | 0x30;  
	else	
		Datos=0x3F;
	HabilitaLCD();
	RetardoLCD(1);
	if(interfaz==4)
		Datos=(Datos & 0b00001111) | 0x30;
	else	
		Datos=0x3F;
	HabilitaLCD();
	RetardoLCD(3);
	if(interfaz==4)
		Datos=(Datos & 0b00001111) | 0x30;
	else	
		Datos=0x3F;
	HabilitaLCD();
	RetardoLCD(4);
	if(interfaz==4){
		Datos=(Datos & 0b00001111) | 0x20;
		HabilitaLCD();
		RetardoLCD(4);
		EnviaDato(0x2F);
		HabilitaLCD();
		RetardoLCD(4);
	}
	BorraLCD();
	EnviaDato(0xF);
	HabilitaLCD();
	RetardoLCD(4);	
}
void HabilitaLCD(void){
//Funci�n que genera los pulsos de habilitaci�n al LCD 	
	E=1;
	__delay_us(40);
    //Delay1TCY();
	E=0;
}
void BorraLCD(void){
//Funci�n que borra toda la pantalla	
	RS=0;
	EnviaDato(0x01);
	HabilitaLCD();
	RetardoLCD(2);
}
void CursorAInicio(){
//Funci�n que lleva el cursor a la primera posici�n o la de la
//primera l�nea mas a la izquierda 	
}	
void ComandoLCD(unsigned char a){
//Funci�n que envia cualquier comando al LCD
	RS=0;
	if(a==1)
		BorraLCD();
	else if((a&0b11111110)==2)	
		CursorAInicio();
	else{	
		EnviaDato(a);
		HabilitaLCD();
		RetardoLCD(4);
	}		
}
void EscribeLCD_c(unsigned char a){
//Funci�n que escribe un caracter en la pantalla
//a es un valor en codigo ascii
//Ejemplo EscribeLCD_c('A');
	RS=1;
	EnviaDato(a);
	HabilitaLCD();
	RetardoLCD(4);
}
void EscribeLCD_n8(unsigned char a,unsigned char b){
//Funci�n que escribe un n�mero positivo de 8 bits en la pantalla
//a es el n�mero a escribir, el cual debe estar en el rango de 0 a 255
//b es el n�mero de digitos que se desea mostrar empezando desde las unidades
//Ejemplo EscribeLCD_n8(204,3);	
    unsigned char centena,decena,unidad;
	RS=1;
	switch(b){
		case 1: unidad=a%10;
				EnviaDato(unidad+48);
				HabilitaLCD();
				RetardoLCD(4);
				break;
		case 2:	decena=(a%100)/10;
				unidad=a%10;
				EnviaDato(decena+48);
				HabilitaLCD();
				RetardoLCD(4);
				EnviaDato(unidad+48);
				HabilitaLCD();
				RetardoLCD(4);
				break;
		case 3: centena=a/100;
				decena=(a%100)/10;
				unidad=a%10;
				EnviaDato(centena+48);
				HabilitaLCD();
				RetardoLCD(4);
				EnviaDato(decena+48);
				HabilitaLCD();
				RetardoLCD(4);
				EnviaDato(unidad+48);
				HabilitaLCD();
				RetardoLCD(4);
				break;
		default: break;
	}
}
void EscribeLCD_n16(unsigned int a,unsigned char b){
//Funci�n que escribe un n�mero positivo de 16 bits en la pantalla
//a es el n�mero a escribir, el cual debe estar en el rango de 0 a 65535
//b es el n�mero de digitos que se desea mostrar empezando desde las unidades
//Ejemplo EscribeLCD_n16(12754,5);	
    unsigned char decena,unidad;
	unsigned int centena,millar;
    RS=1;
	switch(b){
		case 1: unidad=a%10;
                EscribeLCD_c(unidad+48);
				break;
		case 2:	decena=(a%100)/10;
				unidad=a%10;
				EscribeLCD_c(decena+48);
                EscribeLCD_c(unidad+48);
				break;
		case 3: centena=(a%1000)/100;
                decena=(a%100)/10;
				unidad=a%10;
                EscribeLCD_c(centena+48);
				EscribeLCD_c(decena+48);
                EscribeLCD_c(unidad+48);
				break;
		case 4: millar=(a%10000)/1000;
                centena=(a%1000)/100;
                decena=(a%100)/10;
				unidad=a%10;
                EscribeLCD_c(millar+48);
				EscribeLCD_c(centena+48);
				EscribeLCD_c(decena+48);
                EscribeLCD_c(unidad+48);
				break;
		case 5: EscribeLCD_c(a/10000 +48);
				millar=(a%10000)/1000;
                centena=(a%1000)/100;
                decena=(a%100)/10;
				unidad=a%10;
                EscribeLCD_c(millar+48);
				EscribeLCD_c(centena+48);
				EscribeLCD_c(decena+48);
                EscribeLCD_c(unidad+48);
				break;
		default: break;
	}	
}
void EscribeLCD_d(double num, unsigned char digi, unsigned char digd){
	
}


void MensajeLCD_Var(char* a){
    while (*a) {                // Mientras no lleguemos al final de la cadena ('\0')
        EscribeLCD_c(*a);       // Escribe el caracter actual en el LCD
        a++;                    // Avanza al siguiente caracter
    }
}


void StartCount(unsigned char totalPiezas, unsigned char *Temp, unsigned char *cursor_pos, unsigned char *inactividad) {

    unsigned char piezasContadas = 0;         // Iniciar el conteo desde cero
    unsigned char tec = 0;                    // Instancia de la variable que lee la tecla presionada
    unsigned char banderaConteo;              // Variable de control antirrebote para RC1
    unsigned char ultimoBuzzer = 0;           // Variable de control del buzzer
    
    BorraLCD();                               // Se borra toda la pantalla (el cursor se posiciona en 0x80)
    
    printf("Contadas: 0");                    // Impresión del valor inicial del conteo
    
    DireccionaLCD(16);                        // Posición en el inicio de la segunda línea
    printf("Faltan  : %d",totalPiezas);       // Impresión de las piezas a contar 
    
    while (piezasContadas < totalPiezas) {    // Ciclo de conteo
        
        banderaConteo = 1;                    // Prepara el comienzo del conteo
        
        if ( totalPiezas - piezasContadas == 9 ){    // Si solo se está en unidades, que se elimine el 0 restante de la posición de la DDRAM  
            
            *cursor_pos = 28;                        // Posición para proceder a limpiar la posición de la DDRAM deseada  
            EraseDigit(Temp, cursor_pos);            // Uso de la función para eliminar dígitos

        }

        while (banderaConteo && RC1){            // Mientras banderaConteo este en 1 y RC1 este presionada

            piezasContadas++;                    // Suma una pieza

            DireccionaLCD(10);                   // Se cambia solo la posición en la DDRAM que muestra el conteo
            printf("%d", piezasContadas);        // Imprime las piezas contadas
            
            DireccionaLCD(26);                                 // Posicionamiento del cursor en la segunda línea en la posición que muestra las piezas faltantes de la DDRAM
            printf("%d", totalPiezas - piezasContadas);        // Imprime las piezas faltantes
        
            LATD = (LATD & 0xF0) | (piezasContadas % 10);      // Actualiza solo RD0–RD3 con el conteo, preservando RD4–RD7

            while(RC1 == 1) ;                    // Si se mantiene presionado a RC1, no hace nada
            banderaConteo = 0;                   // Después de sumar una pieza se sale del while, esperando a que se presione nuevamente RC1
        }

        SETUP_RGB(piezasContadas);               // Llamado de la función que determina el color del RGB

        RevisarTeclaESP();                                    // Llamado de la función que revisa si se ha presionado la tecla de STOP o Backlight
        PunteroTeclaESP(&piezasContadas,&totalPiezas);        // Llamado de la función que revisa si se ha presionado la tecla de RESTART o FIN

         
        if ((piezasContadas % 10 == 0) && (piezasContadas != ultimoBuzzer)) {
            Buzzer();                                         // Suena una vez
            ultimoBuzzer = piezasContadas;                    // Marca que ya sonó para ese múltiplo
        }
        
        *inactividad = 0 ;

        LATB = 0 ;                                            // Se limpia la entrada para poder seguir obteniendo entradas del teclado
        
        while(RB4 == 0 || RB5 == 0 || RB6 == 0 || RB7 == 0);  //Antirrebote
            __delay_ms(150);
    
    }

    BorraLCD();                       // Tras acabar el conteo se limpia la pantalla
    printf("OBJETIVO LOGRADO");       // Mensaje de logro del conteo

    while(tec != '!'){                // Espera a que se presione la tecla ok para poder continuar
        
        tec = LeerTeclado();          // Lectura del teclado
        RevisarTeclaESP();            // Revisa si se han presionado las teclas con funciones especiales

        LATB = 0 ;                                              // Se limpia la entrada para poder seguir obteniendo entradas del teclado  

        while(RB0 == 1 || RB1 == 1 || RB2 == 1 || RB3 == 1);    // Antirrebote
            __delay_ms(150);
    }
    
}


void SETUP_RGB(unsigned char piezasContadas){
    unsigned char colores[6] = {0b101, 0b001, 0b011, 0b010, 0b110, 0b111};    // Arreglo que contiene la combinación  de colores según el conteo realizado
    unsigned char idx;                                                        // Inicialización variable de índice de colores
    
    if (numDigits(piezasContadas) == 1) {                                     // Condición que determina si se han contado de 0 a 9 piezas
        idx = 0;                                                              // Se inicia con el primer color (magenta)  
    }

    else if (numDigits(piezasContadas) == 2) {                                // Condición que determina si se han contado de más de 9 piezas
        idx = piezasContadas / 10;                                            // Se le asigna a idx el índice según la decena que se haya contado
    }
    LATE = colores[idx];                                                      // Se le asigna a LATE el valor de RGB según piezasContadas 
}

void Buzzer(void){
    LATA2 = 1;
    __delay_ms(500);
    LATA2 = 0;  
}

void PARADA(void){
    
    BorraLCD();                        // Borra la pantalla 
    printf(" PARADA DE ");             // Imprime la primer parte del mensaje de emergencia la primer parte
    DireccionaLCD(16);                 // Posiciona el cursor a inicios de la segunda línea
    printf("    EMERGENCIA");          // Imprime la segunda parte del mensaje de emergencia la primer parte
    LATE = (LATE & 0xF0) | 0b100 ;
    while(1);
}

void RevisarTeclaESP(){
    
    
    LATB = 0b11111101;        // Activar fila 2 del teclado
    
    if(RB7 == 0){             // Si está presionada la tecla STOP
        PARADA();             // Llamar a la función de parada de emergencia
    }
    
    LATB = 0b11110111;        // Activar fila 4 del teclado
    if(RB7 == 0){             // Si está presionada la tecla STOP
        BackLight();          // Llamar a la función de parada de emergencia
    }
    LATB = 0;                 // Limpiar LATB después del barrido
}

void PunteroTeclaESP(unsigned char *piezasContadas, unsigned char *totalPiezas){
    
    LATB=0B11110111;                         // Barrido de la cuarta fila de arriba hacia abajo del teclado matricial
        
    if(RB4==0) {                             // Si está presionada la tecla de RESTART
        
        ReiniciarCuenta(piezasContadas, totalPiezas);     // Llamar a la función de reinicio de conteo
    }
    
    if(RB6==0) {                             // Si está presionada la tecla de END                         
        
        finConteo(piezasContadas, totalPiezas);  // Llama la función que  termina el conteo      
    }
    
    LATB = 0;                 // Limpiar LATB después del barrido
}


void BackLight(){             // Función de prendido y apagado del led
    
    RA3 = RA3^1;              // Toggle
}

void ReiniciarCuenta(unsigned char *piezasContadas, unsigned char *totalPiezas){
    unsigned char cursorV = 12;
    unsigned char TempV = 1;
    
    if ( numDigits(*piezasContadas) == 2){
        
        EraseDigit( &TempV , &cursorV);
    }
    
    *piezasContadas = 0;
    LATD = (LATD & 0xF0);
    DireccionaLCD(10);
    printf("%d", *piezasContadas);
    DireccionaLCD(26);
    printf("%d", *totalPiezas - *piezasContadas);
}

void finConteo(unsigned char *piezasContadas, unsigned char *totalPiezas){    //Función de END
    
    SETUP_RGB(*totalPiezas);
    
    LATD = (LATD & 0xF0) | (*totalPiezas % 10);     // Se le asigna el valor al 7Seg como si se hubiera finalizado el conteo
            
    *piezasContadas = *totalPiezas;                 // Sale del primer while de la función startCount();
    
}

void EraseDigit(unsigned char *Temp, unsigned char *cursor_pos){
    // Función que elimina un dígito
    (*Temp)--;
    (*cursor_pos)--;
    DireccionaLCD(*cursor_pos);
    EscribeLCD_c(' ');
    DireccionaLCD(*cursor_pos);
}

void DireccionaLCD(unsigned char pos) {
//Funci�n que ubica el cursor en una posici�n especificada
//a debe ser una direcci�n de 8 bits valida de la DDRAM o la CGRAM	
    RS = 0;                // Modo comando
    if (pos>=0 && pos<15){
        EnviaDato(0x80 + pos); // Set DDRAM address
        HabilitaLCD();
        RetardoLCD(2);
    }
	else if (pos>15 && pos<31){
		EnviaDato(0xC0 + pos - 16); // Set DDRAM address for second line
		HabilitaLCD();
		RetardoLCD(2);
	}
	else if (pos>31 && pos<47){
		EnviaDato(0x94 + pos - 32); // Set DDRAM address for third line
		HabilitaLCD();
		RetardoLCD(2);
	}
	else {
		printf("Error: Direccion no valida %d", pos);
	}
}

unsigned char numDigits(unsigned int n) {       // Función que cuenta los dígitos de un número
    if (n == 0) return 1;                       // Si el número es 0 no tiene dígitos

    unsigned char count = 0;                    // Se inicializa la variable que guarda la cantidad de dígitos
    while (n > 0) {                             // Si n>0 va sumando a count por cada vez que se puede dividir n en 10
        count++;
        n /= 10;
    }
    return count;
}


void fijaCursor(unsigned char col, unsigned char row) {
    unsigned char pos = (row == 0) ? col : (0x40 + col);
    EnviaDato(0x80 + pos);
    HabilitaLCD();
    RetardoLCD(2);
}

void P2L(unsigned char col, unsigned char row) {
    unsigned char pos = (row == 0) ? col : (0x40 + col);
    EnviaDato(0x80 + pos);
    HabilitaLCD();
    RetardoLCD(2);
}
void DesplazaPantallaD(void){
//Funci�n que desplaza una sola vez la pantalla a la derecha	
  RS=0;
  EnviaDato(8);   
  HabilitaLCD();
  RetardoLCD(4);	
}
void DesplazaPantallaI(void){
//Funci�n que desplaza una sola vez la pantalla a la izquierda
	
}
void DesplazaCursorD(void){
    RS = 0;
    EnviaDato(0x14);  // Comando para desplazar cursor a la derecha
}

void DesplazaCursorI(void){
//Funci�n que desplaza una sola vez la pantalla a la izquierda
    RS = 0;
    EnviaDato(0x10);  // Comando para desplazar cursor a la izquierda
}	

void RetardoLCD(unsigned char a){
	switch(a){
		case 1: __delay_ms(15);
                //Delay100TCYx(38); //Retardo de mas de 15 ms
				break;
		case 2: __delay_ms(1);
                __delay_us(640);
                //Delay10TCYx(41); //Retardo de mas de 1.64 ms
				break;
		case 3: __delay_us(100);
                //Delay10TCYx(3);	//Retardo de mas de 100 us
				break;
		case 4: __delay_us(40);
                //Delay10TCYx(1); //Retardo de mas de 40 us
				break;
		default:
				break;
	}
}

void OcultarCursor(void) {
    RS = 0;              // Modo comando
    EnviaDato(0x0C);     // Display ON, Cursor OFF, Blink OFF
    HabilitaLCD();
    RetardoLCD(4);
}

void MostrarCursor(void) {
    RS = 0;              // Modo comando  
    EnviaDato(0x0F);     // Display ON, Cursor ON, Blink ON
    HabilitaLCD();
    RetardoLCD(4);
}

void CursorSinParpadeo(void) {
    RS = 0;              // Modo comando
    EnviaDato(0x0E);     // Display ON, Cursor ON, Blink OFF  
    HabilitaLCD();
    RetardoLCD(4);
}

#endif	/* LIBLCDXC8_H */
