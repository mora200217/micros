#include<xc.h>
#include<stdio.h>
#define _XTAL_FREQ 1000000
#include "LibLCDXC8.h"
#pragma config FOSC=INTOSC_EC
#pragma config WDT=OFF
//#pragma LVP=OFF Redundante


unsigned char inactividad = 0;  // Cuenta los segundos sin actividad

unsigned char cursor_pos = 0;   // Posición del cursor
unsigned char t;                // Lectura del teclado
int ArrConteo[2];               // Un arreglo de 2 enteros: arreglo[0] a arreglo[1] para guardar el número objetivo a contar
unsigned char Temp=0;           // Entero que sirve como contador para almacenar los dos valores
unsigned char totalPiezas;                // Inclusión de los dos dígitos de ArrConteo

void putch(char);
unsigned char LeerTeclado(void);

void conteoPiezas(void);

void CrearCaracterLCD(unsigned char direccion, unsigned char *patron);
void MostrarCaracterPersonalizado(unsigned char direccion);
void InicializarCaracteresEspeciales(void);

void AnimacionBienvenida(void);

void __interrupt () ISR(void);

// Frame 1 - Pierna derecha adelante
unsigned char runMan1[8] = {
    0b01110,
    0b11111,
    0b01110,
    0b00101,
    0b11111,
    0b10100,
    0b00111,
    0b11101
};

// Frame 2 - Posición intermedia
unsigned char runMan2[8] = {
    0b01110,
    0b11111,
    0b01110,
    0b00100,
    0b01110,
    0b01110,
    0b01110,
    0b01110
};

// Frame 3 - Pierna izquierda adelante
unsigned char runMan3[8] = {
    0b01110,
    0b11111,
    0b01110,
    0b00100,
    0b11101,
    0b10111,
    0b00111,
    0b01101
};

unsigned char skullChar[8] = {
    0b00110,
    0b11111,
    0b10101,
    0b11101,
    0b11111,
    0b01010,
    0b10001,
    0b01110
};

unsigned char skullAngry[8] = {
    0b00110,
    0b11111,
    0b11011,  // Ojos más malvados
    0b11011,
    0b11111,
    0b01110,  // Boca más grande
    0b10001,
    0b01110
};




void main(void){
    unsigned char i=0,t;
    ADCON1 = 15;              //Configuración de todos los pines como digitales 
    TRISA = 0;                //Puerto A como salida
    TRISB = 0B11110000;       //Pines <7:4> como entrada y <3:0> como salida para el teclado matricial
    TRISD = 0;                //Pines de salida a la pantallla LCD y del 7Seg
    TRISC1 = 1;               //Pin de entrada del contador de piezas 
    TRISE = 0B11111000;       //Puerto E con pines <2:0> como salida
    
    LATA = 0;                 //Inicialización puerto D como 0 
    LATB = 0;                 //Inicialización puerto B como 0
    LATD = 0;                 //Inicialización puerto A como 0
    LATE = 0;                 //Inicialización puerto A como 0
    RBPU = 0;                 //Pull-ups are enabled by individual PORTD latch values
    __delay_ms(100);
    
    
//Interrupciones
    T0CON=0b00000001;       //Prescaler de 4 para TMR0
    TMR0=3036;              //Precarga necesaria para Fencendido = 1Hz
    TMR0IF=0;               //Limpia bandera de interrupción TMR0
    TMR0IE=1;               //Activa interrupción por TMR0
   
    
    GIE=1;                  //Activa las interrupciones globales 
    TMR0ON=1;               //Empieza el conteo del TMR0    
    
    __delay_ms(1000);
    ConfiguraLCD(4);
    InicializaLCD();
    
    // Inicializar caracteres especiales
    InicializarCaracteresEspeciales();
    
    // Ejemplo de uso
    BorraLCD();
    //printf("Hola ");
    //MostrarCaracterPersonalizado(0); // Muestra el smiley
    //MostrarCaracterPersonalizado(1);
    //MostrarCaracterPersonalizado(2);
    //MostrarCaracterPersonalizado(3);
    //printf(" Mundo!");
    
    AnimacionBienvenida();
   
    __delay_ms(20);       //Se debe cambiar a 5s, se pone 1s para las simulaciones del funcionamiento del código 
    while(1){
        conteoPiezas();
    }
}

void putch (char data){
    EscribeLCD_c(data);
}

unsigned char LeerTeclado(void){
    while(RB4==1 && RB5==1 && RB6==1 && RB7==1);
    __delay_ms(150);
    
        inactividad = 0;            // Reinicia la variable de inactividad
        
        LATB=0B11111110;                // Barrido de la primer fila de arriba hacia abajo del teclado matricial
        
        if(RB4==0) return '1';
        
        if(RB5==0) return '2';
  
        if(RB6==0) return '3';
        
        if(RB7==0) return '!';          // Tecla de OK!
        
        LATB=0B11111101;                // Barrido de la segunda fila de arriba hacia abajo del teclado matricial
        
        if(RB4==0) return '4';
        
        if(RB5==0) return '5';
        
        if(RB6==0) return '6';
        
        if(RB7==0) return 'S';          // Tecla de STOP
        
        LATB=0B11111011;                // Barrido de la tercera fila de arriba hacia abajo del teclado matricial
        
        if(RB4==0) return '7';
        
        if(RB5==0) return '8';
        
        if(RB6==0) return '9';
        
        if(RB7==0) return 'B';          // Tecla de borrar dígito
           
        LATB=0B11110111;                // Barrido de la cuarta fila de arriba hacia abajo del teclado matricial
        
        if(RB4==0) return 'E';
        
        if(RB5==0) return '0';
        
        if(RB6==0) return 'N';
        
        if(RB7==0) return 'L';          // Tecla de backlight
    
} 

void conteoPiezas(void) {
    BorraLCD();                            // Limpia la pantalla
    Temp = 0;                              // Reinicia el contador al empezar a contar de nuevo
    totalPiezas = 0;                       // Reinicia la variable que tiene la cantidad de piezas a contar
    
    LATD = (LATD & 0xF0);                  // Inicializa el contador del 7Seg en 0
    SETUP_RGB(0);                          // Inicializa el color del RGB
    
    DireccionaLCD(0);                      // Lleva el cursor al inicio
    MensajeLCD_Var("Piezas a contar: ");   // Escribe el mensaje para iniciar el conteo
    DireccionaLCD(16);                     // Posicionamiento del cursor al inicio de la segunda línea (Celda número "16")
    cursor_pos=16;                         // Guarda posición del cursor
    
    
    while (t != '!' || Temp == 0){         // Mientras que no se presione  OK o no se haya digitado nada
        
        t = LeerTeclado();                 // Variable de lectura del teclado
        
        if (t >= '0' && t <= '9') {
            
            if ( (Temp == 0 && ( t >= '6' || t == '0')) ) ; // Ignora valores no válidos en el primer dígito {0,6,7,8,9}, simplemente continua con la ejecución
            
            if ( (Temp == 0 && t< '6' && t > '0') || ( Temp>0 && Temp<2) ){  // Inserta el dígito si es válido, el primer dígito ∈ {1,...,5} y el segundo puedee ser cualquiera
                
                ArrConteo[Temp] = t - '0';       // Se guardan los valores numéricos según el índice en el arreglo de ArrConteo
                EscribeLCD_c(t);                 // Imprime en pantalla el número válido presionado
                cursor_pos++;                    // Suma posición al cursor
                Temp++;                          // Suma al contador
            }
        }       
        if (t == 'B' && Temp > 0) {              // Borrar último número digitado (no se llama si no se  ha digitado nada)
            EraseDigit(&Temp,&cursor_pos);       // Llamada a la función  que elimina el dígito actual por medio de mover el cursor
        }
        
        if (t == 'S') {                          // Si se presiona la tecla de STOP
            PARADA();                            // Llamada a la función de emergencia
        }
  
        if (t == 'L') {                          // Si se presiona la tecla de BackLight
           BackLight();                        // Llamada a la función de prendido de la luz
        }
        
        LATB = 0;                                // Limpia la salida
        
        while(RB4 == 0 || RB5 == 0 || RB6 == 0 || RB7 == 0);  //Antirrebote, mientras siguen presionadas las teclas ("filas") se espera para volver a leer a t
            __delay_ms(150);
    }
    
    if (Temp == 1) {                                            
        totalPiezas = ArrConteo[0];                           // Registra las unidades de las piezas a contar cuando solo se ha presionado una tecla
    }   
    
    if (Temp == 2) {
        totalPiezas = ArrConteo[0] * 10 + ArrConteo[1];       // Registra las decenas y unidades de las piezas a contar
    }
    StartCount(totalPiezas, &Temp, &cursor_pos, &inactividad);       // Empieza con el conteo de las piezas
   
}

void __interrupt() ISR(void){        // Bandera de interrupción 
 
    if(TMR0IF==1){                   // Condicional; si se  ha activado la bandera de TMR0
        
        TMR0=3036;                   // Precarga para obtener F = 1Hz con reloj interno de 1MHz
        TMR0IF=0;                    // Se baja la bandera
        LATA1=LATA1^1;               // Se hace Toggle de LATA1
        
        inactividad++;               // Sumar cada segundo sin actividad
        if (inactividad == 10){
            RA3 = 0;                 // Apagar backlight tras 10s sin actividad
        }
        if (inactividad == 20) {
            BorraLCD();
            printf("SUSPENDIDO...");
            MostrarCaracterPersonalizado(4);
            Sleep(); // Entra en suspensión
            
        }
    }
 }
 
void CrearCaracterLCD(unsigned char direccion, unsigned char *patron) {
    
    // Función para crear un carácter personalizado en la CGRAM (Character Generator RAM),
    // direccion: la dirección donde se desea guardar el caracter especial
    // patron: secuencia de 8 bits que construyen al caracter       
    
    unsigned char i;            // Contador en un ciclo for
    
    if (direccion > 7) return;  // La dirección debe estar entre 0 y 7 (8 caracteres personalizados máximo)
    
    RS = 0; // Modo comando
    EnviaDato(0x40 + (direccion * 8)); // Dirección base de CGRAM + offset
                                       // Cada carácter ocupa 8 bytes consecutivos en la CGRAM (una fila por byte)
    HabilitaLCD();
    RetardoLCD(4);
    
    RS = 1; // Modo datos
    for (i = 0; i < 8; i++) {      
        EnviaDato(patron[i]);       // Envía una fila del carácter
        HabilitaLCD();              // Inicio de proceso de la fila
        RetardoLCD(4);              // Retardo para proceso de información
    }
    
    // Regresar a DDRAM
    RS = 0;          // Envio de comandos 
    EnviaDato(0x80); // Dirección 0 de DDRAM
    HabilitaLCD();   // Ejecución del comando 
    RetardoLCD(4);   // Procesamiento del comando
}

// Función para mostrar un carácter personalizado
void MostrarCaracterPersonalizado(unsigned char direccion) {
    
    if (direccion > 7) return; // Solo hay 8 posiciones disponibles
    
    RS = 1; // Modo datos
    EnviaDato(direccion); // Envía el código del carácter (0-7) para mostrarlo en pantalla
    HabilitaLCD();        // Instrucción de procesamiento
    RetardoLCD(4);        // Timepo para el proceso
}

void InicializarCaracteresEspeciales(void) {
    // Crear los caracteres en la CGRAM
    CrearCaracterLCD(0, runMan1);       // Posición 0
    CrearCaracterLCD(1, runMan2);       // Posición 1  
    CrearCaracterLCD(2, runMan3);       // Posición 2
    CrearCaracterLCD(3, skullChar);     // Posición 3
    CrearCaracterLCD(4, skullAngry);    // Posición 4
}

void AnimacionBienvenida(void) {
    unsigned char posicion;
    unsigned char frame;
    
    OcultarCursor();
    BorraLCD();
    
    // Fase 1: Solo el runner corriendo tranquilo
    DireccionaLCD(16);
    printf("  Just running...");
    
    for (posicion = 0; posicion <= 4; posicion++) {
        frame = posicion % 3;
        
        DireccionaLCD(0);
        printf("                ");
        DireccionaLCD(posicion);
        MostrarCaracterPersonalizado(frame);
        
        __delay_ms(200);
    }
    
    // Fase 2: ¡Aparece el monstruo!
    DireccionaLCD(16);
    printf("  OH NO! RUN!!!");
    
    for (posicion = 5; posicion <= 14; posicion++) {
        frame = posicion % 3;
        
        DireccionaLCD(0);
        printf("                ");
        
        // Skull persiguiendo
        DireccionaLCD(posicion - 3);
        MostrarCaracterPersonalizado(3);
        
        // Runner huyendo
        DireccionaLCD(posicion);
        MostrarCaracterPersonalizado(frame);
        
        __delay_ms(20); // Más rápido, es una persecución!
    }
    
    // Fase 3: Escape final
    DireccionaLCD(0);
    printf("   SAFE! ");
    DireccionaLCD(16);
    printf("  Skull defeated!");
    
    __delay_ms(1000);
    
    
    BorraLCD();
    DireccionaLCD(0);
    printf("  ¡Bienvenido!");
    __delay_ms(1000);
    MostrarCursor();
}