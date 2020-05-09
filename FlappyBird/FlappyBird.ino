//*
/* Librería para el uso de la pantalla ILI9341 en modo 8 bits
 * Basado en el código de martinayotte - https://www.stm32duino.com/viewtopic.php?t=637
 * Adaptación, migración y creación de nuevas funciones: Pablo Mazariegos y José Morales
 * Con ayuda de: José Guerra
 * IE3027: Electrónica Digital 2 - 2019
 * 
 * 
 * 
 *            PROYECTO 2 - DIGITAL 2
 *                (FLAPPY BIRD) 
 *    SECCION 20
 *    INTEGRANTES:
 *      MARCELA IXQUIAC - 17285
 *      ANDRES SIERRA - 17025
 */
//*
#include <stdint.h>
#include <stdbool.h>
#include <TM4C123GH6PM.h>
#include "inc/hw_ints.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/debug.h"
#include "driverlib/gpio.h"
#include "driverlib/interrupt.h"
#include "driverlib/rom_map.h"
#include "driverlib/rom.h"
#include "driverlib/sysctl.h"
#include "driverlib/timer.h"

#include "bitmaps.h"
#include "font.h"
#include "lcd_registers.h"

#define LCD_RST PE_2
#define LCD_CS PE_3
#define LCD_RS PD_2
#define LCD_WR PD_3
#define LCD_RD PE_1
int DPINS[] = {PB_0, PB_1, PB_2, PB_3, PB_4, PB_5, PB_6, PB_7,PA_7};  

const int buttonPin1 = PUSH1;  // PLAYER 1 
const int buttonPin2 = PUSH2;  // PLAYER 2
// ------------ VARIABLES -------------------

int menu=0;
int in=0;
int alarma=0;

int caidaInt = 0;              // CONTROLA LA CAIDA
float caida = 0;               // AUMENTO DE VELOCIDAD
int caidaInt2 = 0;             // CONTROLA LA CAIDA 2
float caida2 = 0;              // AUMENTO DE VELOCIDAD 2

int y = 160;                  // POSICION DEL PAJARO
int y2 = 32;                  // POSICION DEL PAJARO 2

int x = 319;                  // POSICION DEL PAJARO
int x2 = 319;                 // POSICION DEL PAJARO ARRIBA
int movimiento = 2;           // MOVIMIENTO DE LOS TUBOS

int yc = 0;                   // ALTURA DE LOS TUBOS ABAJO
int yc2 = 0;                  // ALTURA DE LOS TUBOS ARRIBA

int yT = 0;                   // POSICION PARA LA Y EL TUBO DE ABAJO
int aT = 0;                   // ALTURA DEL TUBO DE ABAJO
int yT2 = 0;                  // POSICION PARA LA Y EL TUBO DE ARRIBA
int aT2 = 0;                  // ALTURA DEL TUBO DE ARRIBA
int PAJ1=0;
int PAJ2=0;
int score = 0;                // contador del puntaje del jugador

//*
// Functions Prototypes
//*
void LCD_Init(void);
void LCD_CMD(uint8_t cmd);
void LCD_DATA(uint8_t data);
void SetWindows(unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2);
void LCD_Clear(unsigned int c);
void H_line(unsigned int x, unsigned int y, unsigned int l, unsigned int c);
void V_line(unsigned int x, unsigned int y, unsigned int l, unsigned int c);
void Rect(unsigned int x, unsigned int y, unsigned int w, unsigned int h, unsigned int c);
void FillRect(unsigned int x, unsigned int y, unsigned int w, unsigned int h, unsigned int c);
void LCD_Print(String text, int x, int y, int fontSize, int color, int background);

void LCD_Bitmap(unsigned int x, unsigned int y, unsigned int width, unsigned int height, unsigned char bitmap[]);
void LCD_Sprite(int x, int y, int width, int height, unsigned char bitmap[],int columns, int index, char flip, char offset);


extern uint8_t fondo[];
//*
// Inicialización
//*
void setup() {
  
  SysCtlClockSet(SYSCTL_SYSDIV_2_5|SYSCTL_USE_PLL|SYSCTL_OSC_MAIN|SYSCTL_XTAL_16MHZ);
  Serial.begin(9600);
  GPIOPadConfigSet(GPIO_PORTB_BASE, 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7, GPIO_STRENGTH_8MA, GPIO_PIN_TYPE_STD_WPU);
  Serial.println("Inicio");
  LCD_Init();
  LCD_Clear(0x00);
pinMode(PA_7, OUTPUT);
  pinMode(buttonPin1, INPUT_PULLUP);
  pinMode(buttonPin2, INPUT_PULLUP);
  
  FillRect(0, 0, 319, 206, 0x0000);
//  LCD_Sprite(int x, int y, int width, int height, unsigned char bitmap[],int columns, int index, char flip, char offset);
    
  //LCD_Bitmap(unsigned int x, unsigned int y, unsigned int width, unsigned int height, unsigned char bitmap[]);
  //LCD_Bitmap(0, 0, 320, 240, fondo);

  //LCD_Sprite(20, 175, 16, 32, luigi,8, 1 ,1, 0);
  
  for(int x = 0; x <319; x++){
    //LCD_Bitmap(x, 112, 16, 16, tile2);
    //LCD_Bitmap(x, 68, 16, 16, tile);
    
    //LCD_Bitmap(x, 207, 16, 16, tile);
    //LCD_Bitmap(x, 223, 16, 16, tile);
    x += 15;
    
 }
        
    delay(500);
    FillRect(0, 0, 319, 240, 0x0bfff);
 
    
  
}
//***
//              Loop Infinito
//***
void loop() {
  int boton1 = digitalRead(buttonPin1);         // DECLARAMO LAS VARIABLES DE LOS BOTONES
  int boton2 = digitalRead(buttonPin2); 
  
  if(menu==0){ // Si el juego está en modo MENU y no en Modo jugador
    alarma=0;                   // RESETEA TODAS LAS VARIABLES 
     y=160;
     y2=32;
     x=339;
     x2=339;
     yc = 20;
     yc2 = 40;
     score = 0; 
     PAJ1=0;
     PAJ2=0;
    String text1 = "Flappy Bird";
     LCD_Print(text1, 80, 40, 2, 0x00000, 0x00bfff);
     for(int x=0 ; x<4; x++){
     LCD_Sprite(60, 40, 16, 16, PAJARO,3,x,0, 0);
     LCD_Sprite(260, 40, 16, 16, PAJARO,3,x,0, 0);
     for(int x = 0; x <319; x = x + 22){
       LCD_Bitmap(x, 201, 22, 39, GRAMA);} // Dibuja la pantalla de inicio y escribe el titulo
     delay(90);
     }
     
     String text2 = "Instrucciones:";
     String text3 = "Con los botones ";
     LCD_Print(text2, 60, 70, 2, 0xf0ff, 0x0bfff);
     LCD_Print(text3, 50, 90, 2, 0xf0ff, 0x0bfff);
     String text4 = "evite los obstaculos";
     String text5 = "Presione Boton 1 y 2";
    LCD_Print(text4, 0, 110, 2, 0xf0ff, 0x0bfff);
    LCD_Print(text5, 0, 130, 2, 0xf0ff, 0x0bfff); // Escribe las instrucciones
    if (boton1==0 && boton2==0){                  // Si el Usuario presiona ambos botones, se ingresa al juego 
      menu=1;                                     // Cambia al modo Jugador
       digitalWrite(PA_7,HIGH);                   // Cambia el estado del pin digital para cambiar la melodía al comunicarse con el arduino
      FillRect(0, 0, 319, 240, 0x0000);            // Dibuja la Línea divisora
       for(int x = 0; x <319; x = x + 16){
       LCD_Bitmap(x, 112, 16, 16, tile2);}
      //LCD_Sprite(50, y, 16, 16, J2,3, 1 ,0, 0);
    }
    
  }

if(menu==1){  // Si el juego se encuentra en modo jugador, entonces
  
  // ------------ CAIDA DEL PAJARO --------------- 
  y+=caidaInt;            // POSICION DEL PAJARO   La esta variable aumenta su valor con cada repeticion
  caida=caida+0.2;        // AUMENTO DE VELOCIDAD EN LA CAIDA. Se hace que cada vez aumente de velocidad mas rapido.
  caidaInt= int(caida);   // Convierte a entero

  // ------------ CAIDA DEL PAJARO 2 --------------- 
  y2+=caidaInt2;            // POSICION DEL PAJARO 
  caida2=caida2+0.2;        // Aumento de velocidad en la caida
  caidaInt2= int(caida2);   // Convierte a entero
  
  // ----------- SALTO DEL PAJARO --------------- 
  if (boton1 == 0 && alarma==0) {
    caida = -3;                             //GENERA EL SALTO DEL PAJARO. CADA QUE SE PRESIONE EL BOTON DISMINUYE EL VALOR DE LA POSICION EN Y   
  }

    // ----------- SALTO DEL PAJARO 2 --------------- 
  if (boton2 == 0 && alarma==0) {
    caida2 = -3; //    GENERA EL SALTO DEL PAJARO (COLOCA LA Y 6 POSICIONES ARRIBA)  
  }
  
  // ------------- DIBUJO DE LOS PAJAROS ------------------
    int anim = (y/11)%8;                 // PARA LA ANIMACION DEL MOVIMIENTO
  
     if(alarma==0){
  // ------------------ PAJARO 1 ---------------------
     LCD_Sprite(50, y, 16, 16, J1,3, anim,0, 0);          // DIBUJA EL PAJARO EN LA POSICION YA DEFINIDA Y SE CREAN 3 LINEAS PARA BORRAR EL RASTRO QUE DEJA
     H_line( 50, y+15, 15, 0x0000);
     H_line( 50, y+16, 15, 0x0000);
     H_line( 50, y+17, 15, 0x0000);
     
     H_line( 50, y-1, 15, 0x0000);
     H_line( 50, y-2, 15, 0x0000);
     H_line( 50, y-3, 15, 0x0000);

  // ------------------ PAJARO 2 -------------------
     LCD_Sprite(50, y2, 16, 16, J2,3, anim,0, 0);
     H_line( 50, y2+15, 15, 0x0000);
     H_line( 50, y2+16, 15, 0x0000);
     H_line( 50, y2+17, 15, 0x0000);
     
     H_line( 50, y2-1, 15, 0x0000);
     H_line( 50, y2-2, 15, 0x0000);
     H_line( 50, y2-3, 15, 0x0000);  

  // --------------- MOVIMIENTO TUBOS ----------------------
  // -------------------------------------------------------
  //                TUBOS DE ABAJO 
  // -------------------------------------------------------
    x=x-movimiento;         // Genera el movimiento de los tubos restando el valor de la variable movimiento.    
    
  // ---------------- TUBO SUPERIOR ----------------------
    FillRect(x, 128, 10, yc, 0x0f00);               // Crea un tubo verde cuya altura esta definido por la variable yc. 
    V_line( x+11, 128, yc, 0x0000);
    V_line( x+12, 128, yc, 0x0000);

  // ----------- POSICION Y ALTO DEL TUBO INFERIOR -------------  
    yT = 128 + 40 + yc;                      //COORDENADA DEL TUBO DE ABAJO. Tomamos la coordenada donde empieza el tubo de arriba, se resta la altura del tubo de arriba y por ultimo se dejan 40 pixeles para que pase el pajaro
    aT = 240 - 128 - 40 - yc;                // ALTURA DEL TUBO INFERIOR. Tomamos el alto de la pantalla y le quitamos el area donde no se trabaja, luego le resto la altura del tubo superior y le resto los 40 pixeles de espacio libre

  // --------------- DIBUJA TUBO INFERIOR --------------------
    FillRect(x, yT, 10, aT, 0x0f00);        //Dibujamos el tubo con la coordenada y y altura que se crearon anteriormente
    V_line( x+11, 128 + yc + 40, 240- 128 + yc + 40, 0x0000);
    V_line( x+12, 128 + yc + 40, 240- 128 + yc + 40, 0x0000);    

  // -------------------------------------------------------      
  //               TUBOS DE ARRIBA
  // -------------------------------------------------------

    x2=x2-movimiento;         // GENERA EL MOVIMIENTO DE LOS TUBOS     

  // ---------------- TUBO SUPERIOR ----------------------
    FillRect(x2, 0, 10, yc2, 0x0f00);
    V_line( x2+11, 0, yc2, 0x0000);
    V_line( x2+12, 0, yc2, 0x0000);

  // ----------- POSICION Y ALTO DEL TUBO INFERIOR -------------  
    yT2 = 40 + yc2;
    aT2 = 112 - 40 - yc2;

  // --------------- DIBUJA TUBO INFERIOR --------------------
    FillRect(x2, yT2, 10, aT2, 0x0f00);
    V_line( x2+11, yT2, aT2, 0x0000);
    V_line( x2+12, yT2, aT2, 0x0000);  
    
  
    delay(15); }

  // -------------- CUANDO LOS TUBOS LLEGA AL FINAL (ABAJO) -----------
    if (x<=-51){
      x=319;                    // REINICIA LA POSICION INICAL DE LOS TUBOS
      yc = 0;                   // REINICIO EL VALOR DEL ALTO DE LOS TUBOS
      yc = rand() % 45 +10;     // PONGO OTRO VALOR ALEATORIO PARA EL ALTO DE LOS TUBOS 
      
  // --------------- PARA EL OTRO TUBO -------------------   
      x2=319;                    // REINICIA LA POSICION INICAL DE LOS TUBOS
      yc2 = 0;                   // REINICIO EL VALOR DEL ALTO DE LOS TUBOS
      yc2 = rand() % 45 +10;     // PONGO OTRO VALOR ALEATORIO PARA EL ALTO DE LOS TUBOS  
      score = score + 1;          // AUMENTO EN 1 EL SCORE
    }
    
  // -------------- CUANDO LOS TUBOS LLEGA AL FINAL (ARRIBA) -----------
    if (x<=-51){
      x2=319;                    // REINICIA LA POSICION INICAL DE LOS TUBOS
      yc2 = 0;                   // REINICIO EL VALOR DEL ALTO DE LOS TUBOS
      yc2 = rand() % 45 +10;     // PONGO OTRO VALOR ALEATORIO PARA EL ALTO DE LOS TUBOS    
    }  

// ----------------- VERIFICA SI EL PAJARO CHOCO CON ALGO ------------------------
  if (y >= 225 ||y <= 130 || x <= 60 && x >= 40 && y <= yc + 128 || x <= 60 && x >= 40 && y + 16 >= yT ){ // COMPARO SI EL PAJARO COLISIONO CON ALGO COMPARANDO COORDENADAS, SE COMPARA EL TECHO, EL SUELO Y LOS                                                                                                          
    if(PAJ2==0){                                                                                          //DOS TUBOS. 
    in=1;
 
    //FillRect(0, 128, 319, 112, 0x0000);
    String text10 = "GAME OVER"; // Indica que el juego se acabo
    alarma=1;
    digitalWrite(PA_7,LOW);        // Cambia el estado del pin digital para cambiar la melodía
    LCD_Print(text10, 100, 158, 2, 0xf000, 0x0000);   
    LCD_Print(text10, 100, 158, 2, 0xf000, 0x0000);
    String text11 = "Para Reiniciar";
     LCD_Print(text11, 25, 188, 2, 0xffff, 0x0000);
    String text12 = "Presione boton 1 y 2";
    LCD_Print(text12, 0, 213, 2, 0xffff, 0x0000);
  delay(1000);
    //FillRect(66, 0, 253, 112, 0x0000);
    String text18 = "GANADOR:";
    LCD_Print(text18, 80, 30, 2, 0xffff, 0x0000);
    String text19 = "JUGADOR 1";
    LCD_Print(text19, 80, 50, 2, 0xffff, 0x0000); //Imprime las leyendas de final de juego en la pantalla
 PAJ1=1;                                          // Banderas que evitan que el juego siga si un jugador ya perdió
 PAJ2=0;
    String text20 = "Score:";                     // Imprime el puntaje del ganador 
    LCD_Print(String(score), 80, 75, 2, 0xf000, 0x0000);
    delay(500);
  }}

  if (x2 <= 60 && x2 >=40 && y2 + 16 >= yT2 || x2 <= 60 && x2 >= 40 && y2 <= yc2 || y2 + 16 >= 112 ||y2 <= 1){
    if(PAJ1==0){
  in=1;
 
    //FillRect(0, 0, 319, 112, 0x0000);
    String text13 = "GAME OVER"; // Indica que el juego se acabo
    alarma=1;
    digitalWrite(PA_7,LOW);      // Cambia el estado del pin digital para cambiar la melodía
    LCD_Print(text13, 100, 30, 2, 0xf000, 0x0000);   
    LCD_Print(text13, 100, 30, 2, 0xf000, 0x0000); 
    String text14 = "Para Reiniciar";
     LCD_Print(text14, 25, 60, 2, 0xffff, 0x0000);
    String text15 = "Presione boton 1 y 2";
    LCD_Print(text15, 0, 85, 2, 0xffff, 0x0000);
    delay(1000);
    //FillRect(66, 128, 253, 112, 0x0000);
    String text16 = "GANADOR:";
    LCD_Print(text16, 80, 140, 2, 0xffff, 0x0000);
    String text17 = "JUGADOR 2";               //Imprime las leyendas de final de juego en la pantalla
    LCD_Print(text17, 80, 160, 2, 0xffff, 0x0000);
PAJ1=0;  // Banderas que evitan que el juego siga si un jugador ya perdió
 PAJ2=1;
    String text19 = "Score:";              // Imprime el puntaje del ganador 
    LCD_Print(String(score), 80, 185, 2, 0xf000, 0x0000);
  
    delay(500);
  }}
  

  // ----------------------- VUELVE AL INICIO ------------------
   if(in==1){
   
FillRect(0, 0, 319, 240, 0x0000); 
/*String text13 = "GAME OVER";
 LCD_Print(text13, 100, 30, 2, 0xf000, 0x0000);
 String text14 = "Para Reiniciar";
     LCD_Print(text14, 25, 60, 2, 0xffff, 0x0000);
    String text15 = "Presione boton 1 y 2";
    LCD_Print(text15, 0, 85, 2, 0xffff, 0x0000); */
    if(boton1==0 && boton2==0){
   menu=0;
   in=0;
   FillRect(0, 0, 319, 240, 0x0bfff);   
    }
  }
  }
}



//*
// Función para inicializar LCD
//*
void LCD_Init(void) {
  pinMode(LCD_RST, OUTPUT);
  pinMode(LCD_CS, OUTPUT);
  pinMode(LCD_RS, OUTPUT);
  pinMode(LCD_WR, OUTPUT);
  pinMode(LCD_RD, OUTPUT);
  for (uint8_t i = 0; i < 8; i++){
    pinMode(DPINS[i], OUTPUT);
  }
  //**
  // Secuencia de Inicialización
  //**
  digitalWrite(LCD_CS, HIGH);
  digitalWrite(LCD_RS, HIGH);
  digitalWrite(LCD_WR, HIGH);
  digitalWrite(LCD_RD, HIGH);
  digitalWrite(LCD_RST, HIGH);
  delay(5);
  digitalWrite(LCD_RST, LOW);
  delay(20);
  digitalWrite(LCD_RST, HIGH);
  delay(150);
  digitalWrite(LCD_CS, LOW);
  //**
  LCD_CMD(0xE9);  // SETPANELRELATED
  LCD_DATA(0x20);
  //**
  LCD_CMD(0x11); // Exit Sleep SLEEP OUT (SLPOUT)
  delay(100);
  //**
  LCD_CMD(0xD1);    // (SETVCOM)
  LCD_DATA(0x00);
  LCD_DATA(0x71);
  LCD_DATA(0x19);
  //**
  LCD_CMD(0xD0);   // (SETPOWER) 
  LCD_DATA(0x07);
  LCD_DATA(0x01);
  LCD_DATA(0x08);
  //**
  LCD_CMD(0x36);  // (MEMORYACCESS)
  LCD_DATA(0x40|0x80|0x20|0x08); // LCD_DATA(0x19);
  //**
  LCD_CMD(0x3A); // Set_pixel_format (PIXELFORMAT)
  LCD_DATA(0x05); // color setings, 05h - 16bit pixel, 11h - 3bit pixel
  //**
  LCD_CMD(0xC1);    // (POWERCONTROL2)
  LCD_DATA(0x10);
  LCD_DATA(0x10);
  LCD_DATA(0x02);
  LCD_DATA(0x02);
  //**
  LCD_CMD(0xC0); // Set Default Gamma (POWERCONTROL1)
  LCD_DATA(0x00);
  LCD_DATA(0x35);
  LCD_DATA(0x00);
  LCD_DATA(0x00);
  LCD_DATA(0x01);
  LCD_DATA(0x02);
  //**
  LCD_CMD(0xC5); // Set Frame Rate (VCOMCONTROL1)
  LCD_DATA(0x04); // 72Hz
  //**
  LCD_CMD(0xD2); // Power Settings  (SETPWRNORMAL)
  LCD_DATA(0x01);
  LCD_DATA(0x44);
  //**
  LCD_CMD(0xC8); //Set Gamma  (GAMMASET)
  LCD_DATA(0x04);
  LCD_DATA(0x67);
  LCD_DATA(0x35);
  LCD_DATA(0x04);
  LCD_DATA(0x08);
  LCD_DATA(0x06);
  LCD_DATA(0x24);
  LCD_DATA(0x01);
  LCD_DATA(0x37);
  LCD_DATA(0x40);
  LCD_DATA(0x03);
  LCD_DATA(0x10);
  LCD_DATA(0x08);
  LCD_DATA(0x80);
  LCD_DATA(0x00);
  //**
  LCD_CMD(0x2A); // Set_column_address 320px (CASET)
  LCD_DATA(0x00);
  LCD_DATA(0x00);
  LCD_DATA(0x01);
  LCD_DATA(0x3F);
  //**
  LCD_CMD(0x2B); // Set_page_address 480px (PASET)
  LCD_DATA(0x00);
  LCD_DATA(0x00);
  LCD_DATA(0x01);
  LCD_DATA(0xE0);
//  LCD_DATA(0x8F);
  LCD_CMD(0x29); //display on 
  LCD_CMD(0x2C); //display on

  LCD_CMD(ILI9341_INVOFF); //Invert Off
  delay(120);
  LCD_CMD(ILI9341_SLPOUT);    //Exit Sleep
  delay(120);
  LCD_CMD(ILI9341_DISPON);    //Display on
  digitalWrite(LCD_CS, HIGH);
}
//*
// Función para enviar comandos a la LCD - parámetro (comando)
//*
void LCD_CMD(uint8_t cmd) {
  digitalWrite(LCD_RS, LOW);
  digitalWrite(LCD_WR, LOW);
  GPIO_PORTB_DATA_R = cmd;
  digitalWrite(LCD_WR, HIGH);
}
//*
// Función para enviar datos a la LCD - parámetro (dato)
//*
void LCD_DATA(uint8_t data) {
  digitalWrite(LCD_RS, HIGH);
  digitalWrite(LCD_WR, LOW);
  GPIO_PORTB_DATA_R = data;
  digitalWrite(LCD_WR, HIGH);
}
//*
// Función para definir rango de direcciones de memoria con las cuales se trabajara (se define una ventana)
//*
void SetWindows(unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2) {
  LCD_CMD(0x2a); // Set_column_address 4 parameters
  LCD_DATA(x1 >> 8);
  LCD_DATA(x1);   
  LCD_DATA(x2 >> 8);
  LCD_DATA(x2);   
  LCD_CMD(0x2b); // Set_page_address 4 parameters
  LCD_DATA(y1 >> 8);
  LCD_DATA(y1);   
  LCD_DATA(y2 >> 8);
  LCD_DATA(y2);   
  LCD_CMD(0x2c); // Write_memory_start
}
//*
// Función para borrar la pantalla - parámetros (color)
//*
void LCD_Clear(unsigned int c){  
  unsigned int x, y;
  LCD_CMD(0x02c); // write_memory_start
  digitalWrite(LCD_RS, HIGH);
  digitalWrite(LCD_CS, LOW);   
  SetWindows(0, 0, 319, 239); // 479, 319);
  for (x = 0; x < 320; x++)
    for (y = 0; y < 240; y++) {
      LCD_DATA(c >> 8); 
      LCD_DATA(c); 
    }
  digitalWrite(LCD_CS, HIGH);
} 
//*
// Función para dibujar una línea horizontal - parámetros ( coordenada x, cordenada y, longitud, color)
//* 
void H_line(unsigned int x, unsigned int y, unsigned int l, unsigned int c) {  
  unsigned int i, j;
  LCD_CMD(0x02c); //write_memory_start
  digitalWrite(LCD_RS, HIGH);
  digitalWrite(LCD_CS, LOW);
  l = l + x;
  SetWindows(x, y, l, y);
  j = l;// * 2;
  for (i = 0; i < l; i++) {
      LCD_DATA(c >> 8); 
      LCD_DATA(c); 
  }
  digitalWrite(LCD_CS, HIGH);
}
//*
// Función para dibujar una línea vertical - parámetros ( coordenada x, cordenada y, longitud, color)
//* 
void V_line(unsigned int x, unsigned int y, unsigned int l, unsigned int c) {  
  unsigned int i,j;
  LCD_CMD(0x02c); //write_memory_start
  digitalWrite(LCD_RS, HIGH);
  digitalWrite(LCD_CS, LOW);
  l = l + y;
  SetWindows(x, y, x, l);
  j = l; //* 2;
  for (i = 1; i <= j; i++) {
    LCD_DATA(c >> 8); 
    LCD_DATA(c);
  }
  digitalWrite(LCD_CS, HIGH);  
}
//*
// Función para dibujar un rectángulo - parámetros ( coordenada x, cordenada y, ancho, alto, color)
//*
void Rect(unsigned int x, unsigned int y, unsigned int w, unsigned int h, unsigned int c) {
  H_line(x  , y  , w, c);
  H_line(x  , y+h, w, c);
  V_line(x  , y  , h, c);
  V_line(x+w, y  , h, c);
}
//*
// Función para dibujar un rectángulo relleno - parámetros ( coordenada x, cordenada y, ancho, alto, color)
//*
/*void FillRect(unsigned int x, unsigned int y, unsigned int w, unsigned int h, unsigned int c) {
  unsigned int i;
  for (i = 0; i < h; i++) {
    H_line(x  , y  , w, c);
    H_line(x  , y+i, w, c);
  }
}
*/

void FillRect(unsigned int x, unsigned int y, unsigned int w, unsigned int h, unsigned int c) {
  LCD_CMD(0x02c); // write_memory_start
  digitalWrite(LCD_RS, HIGH);
  digitalWrite(LCD_CS, LOW); 
  
  unsigned int x2, y2;
  x2 = x+w;
  y2 = y+h;
  SetWindows(x, y, x2-1, y2-1);
  unsigned int k = w*h*2-1;
  unsigned int i, j;
  for (int i = 0; i < w; i++) {
    for (int j = 0; j < h; j++) {
      LCD_DATA(c >> 8);
      LCD_DATA(c);
      
      //LCD_DATA(bitmap[k]);    
      k = k - 2;
     } 
  }
  digitalWrite(LCD_CS, HIGH);
}
//*
// Función para dibujar texto - parámetros ( texto, coordenada x, cordenada y, color, background) 
//*
void LCD_Print(String text, int x, int y, int fontSize, int color, int background) {
  int fontXSize ;
  int fontYSize ;
  
  if(fontSize == 1){
    fontXSize = fontXSizeSmal ;
    fontYSize = fontYSizeSmal ;
  }
  if(fontSize == 2){
    fontXSize = fontXSizeBig ;
    fontYSize = fontYSizeBig ;
  }
  
  char charInput ;
  int cLength = text.length();
  Serial.println(cLength,DEC);
  int charDec ;
  int c ;
  int charHex ;
  char char_array[cLength+1];
  text.toCharArray(char_array, cLength+1) ;
  for (int i = 0; i < cLength ; i++) {
    charInput = char_array[i];
    Serial.println(char_array[i]);
    charDec = int(charInput);
    digitalWrite(LCD_CS, LOW);
    SetWindows(x + (i * fontXSize), y, x + (i * fontXSize) + fontXSize - 1, y + fontYSize );
    long charHex1 ;
    for ( int n = 0 ; n < fontYSize ; n++ ) {
      if (fontSize == 1){
        charHex1 = pgm_read_word_near(smallFont + ((charDec - 32) * fontYSize) + n);
      }
      if (fontSize == 2){
        charHex1 = pgm_read_word_near(bigFont + ((charDec - 32) * fontYSize) + n);
      }
      for (int t = 1; t < fontXSize + 1 ; t++) {
        if (( charHex1 & (1 << (fontXSize - t))) > 0 ) {
          c = color ;
        } else {
          c = background ;
        }
        LCD_DATA(c >> 8);
        LCD_DATA(c);
      }
    }
    digitalWrite(LCD_CS, HIGH);
  }
}
//*
// Función para dibujar una imagen a partir de un arreglo de colores (Bitmap) Formato (Color 16bit R 5bits G 6bits B 5bits)
//*
void LCD_Bitmap(unsigned int x, unsigned int y, unsigned int width, unsigned int height, unsigned char bitmap[]){  
  LCD_CMD(0x02c); // write_memory_start
  digitalWrite(LCD_RS, HIGH);
  digitalWrite(LCD_CS, LOW); 
  
  unsigned int x2, y2;
  x2 = x+width;
  y2 = y+height;
  SetWindows(x, y, x2-1, y2-1);
  unsigned int k = 0;
  unsigned int i, j;

  for (int i = 0; i < width; i++) {
    for (int j = 0; j < height; j++) {
      LCD_DATA(bitmap[k]);
      LCD_DATA(bitmap[k+1]);
      //LCD_DATA(bitmap[k]);    
      k = k + 2;
     } 
  }
  digitalWrite(LCD_CS, HIGH);
}
//*
// Función para dibujar una imagen sprite - los parámetros columns = número de imagenes en el sprite, index = cual desplegar, flip = darle vuelta
//*
void LCD_Sprite(int x, int y, int width, int height, unsigned char bitmap[],int columns, int index, char flip, char offset){
  LCD_CMD(0x02c); // write_memory_start
  digitalWrite(LCD_RS, HIGH);
  digitalWrite(LCD_CS, LOW); 

  unsigned int x2, y2;
  x2 =   x+width;
  y2=    y+height;
  SetWindows(x, y, x2-1, y2-1);
  int k = 0;
  int ancho = ((width*columns));
  if(flip){
  for (int j = 0; j < height; j++){
      k = (j*(ancho) + index*width -1 - offset)*2;
      k = k+width*2;
     for (int i = 0; i < width; i++){
      LCD_DATA(bitmap[k]);
      LCD_DATA(bitmap[k+1]);
      k = k - 2;
     } 
  }
  }else{
     for (int j = 0; j < height; j++){
      k = (j*(ancho) + index*width + 1 + offset)*2;
     for (int i = 0; i < width; i++){
      LCD_DATA(bitmap[k]);
      LCD_DATA(bitmap[k+1]);
      k = k + 2;
     } 
  }
    
    
    }
  digitalWrite(LCD_CS, HIGH);
}
