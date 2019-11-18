//************************************************************************
//**********BIBLIOTECAS UTILIZADAS****************************************
//************************************************************************
#include <DS1307_HENNING.h>
#include <UTFT.h>
#include <DallasTemperature.h>
#include <OneWire.h>
#include <dht11.h>

//****************************************************************************************************
//****************** Variables de texos y fuentes ****************************************************
//****************************************************************************************************
#define LARGE true
#define SMALL false
extern uint8_t RusFont1[];    // Declara que fuentes vamos usar
extern uint8_t BigFont[];     // Declara que fuentes vamos usar
char buffer[50];
extern uint8_t SevenSegNumFontPlus[];

//************************************************************************
//**********define funciones de los pines digitales y analogicos**********
//************************************************************************
#define MAX_PIN_NUMBER 69 // Numero de pines disponibles en el Arduino Mega.
//pines 3, 4, 5, 6 y 7 reservados para touch
//pines 20 y 21 reservados para rtc
//pines 22 a 41 reservados para el LCD
const byte ledblanco1 = 8;        // Pin que conecta los leds 1
const byte ledblanco2 = 9;        // Pin que conecta los leds 2
const byte ledblanco3 = 10;       // Pin que conecta los leds 3
const byte calefactor = 42;       // Pin que conecta el calentador
const byte temhum = 48;           // pin que lee la temperatura y humedad ambiente
const byte sensores = 49;         // Pin que lee los sensores de temperatura
const byte nivel1 = 58;           // pin analogico que verifica el nivel de acuario
//*******************************************************************************************************
//*********** Variables de las huellas de la pantalla táctil y la pantalla de inicio ********************
//*******************************************************************************************************
UTFT myGLCD(ITDB32WD, 38, 39, 40, 41); // "ITDB32WD" es el modelo del LCD

unsigned long previomillis = 0;

//*****************************************************************************************
//*********************** Parametros ******************************************************
//*****************************************************************************************
byte status_parametros = 0x0;
//bit 0;   // Señala que el calentador está encendido / apagado
//bit 1;   // Señala que la alarma de temperatura está activa
//bit 2;   //

byte outlets[9];
//outlets[0] = calentador > 0 = auto, 1 = on, 2 = off
byte outlets_changed[9];
boolean outlets_settings = false;
unsigned long outlets_millis = 0;
int resultado = 0;

//***********************************************************************
//**********inicia RTC***************************************************
//***********************************************************************
DS1307 rtc(SDA, SCL);
Time t_temp, t;

//****************************************************************************************************
//***************** Variables de sensores de temperatura *********************************************
//****************************************************************************************************
OneWire OneWireBus(sensores);        // Sensores de temperatura
DallasTemperature sensors(&OneWireBus); // Pasa nuestra referencia OneWire a los sensores de temperatura.
DeviceAddress sensor_agua = {0x28, 0xFF, 0xE, 0x74, 0x3B, 0x4, 0x0, 0x68} ;              // Asigna las direcciones de los sensores de temperatura.
DeviceAddress sensor_disipador;        // Asigna las direcciones de los sensores de temperatura
DeviceAddress sensor_deposito = {0x28, 0xFF, 0x35, 0x9C, 0x3C, 0x4, 0x0, 0xB3} ;          // Asigna las direcciones de los sensores de temperatura
byte sonda_associada_1 = 1;
byte sonda_associada_2 = 2;
byte sonda_associada_3 = 3;

//****************************************************************************************************
//***************** Variables de sensores de temperatura y humedad ambiente **************************
//****************************************************************************************************
dht11 DHT;
byte contador_th = 0;
float temp_temporal = 0;
float hum_temporal = 0;
float temp_ambiente = 0;          //temperatura ambiente
float hum_ambiente = 0;           //humedad ambiente

//*******************************************************************************************************
//********************** Variables del control de temperatura del agua **********************************
//*******************************************************************************************************
float tempC = 0;                  // Temperatura del agua
float setTempC = 25.5;            // Temperatura deseada
float offTempC = 0.5;             // Variación permitida de la temperatura
float alarmTempC = 1;             // variación para accionar la alarma de temperatura del agua
byte contador_temp = 0;
float temperatura_agua_temp = 0;  // Temperatura temporal

//*******************************************************************************************************
//********************** Variables del control de temperatura del agua deposito *************************
//*******************************************************************************************************

float tempD = 0;                        //temperatura del deposito
float temperatura_desposito_temp = 0;   //temperatura temporal

//*******************************************************************************************************
//********************** Variables del control de iluminacion *******************************************
//*******************************************************************************************************

byte led1, led2, led3;                    //valor anterior pwm
int min_cnt;
byte led_out1;
byte led_out2;
byte led_out3;
byte led_on_minuto = 2;                  //minuto de encendio
byte led_on_hora = 10;                   //hora de encendido
byte led_off_minuto = 00;                 //minuto de apagado
byte led_off_hora = 17;                  //hora de apagado
byte amanecer_anochecer = 30;            //duracion periodo de amanecer y anochecer
byte pwm_definido = 240;

//*******************************************************************************************************
//********************** Variables del control de la potencia de los leds *******************************
//*******************************************************************************************************

byte wled[96] = {                         //Potencia de salida de los leds blancos 255 = 100% de la potencia
  0, 0, 0, 0, 0, 0, 0, 0,       // 0 e 2
  0, 0, 0, 0, 0, 0, 0, 0,       // 2 e 4
  0, 0, 0, 0, 12, 21, 30, 39,       // 4 e 6
  48, 57, 66, 75, 84, 93, 102, 111,     // 6 e 8
  120, 129, 138, 147, 156, 165, 174, 183, // 8 e 10
  192, 201, 210, 219, 228, 237, 246, 255, // 10 e 12
  255, 246, 237, 228, 219, 210, 201, 192, // 12 e 14
  183, 174, 165, 156, 147, 138, 129, 120,  // 14 e 16
  111, 102, 93, 84, 75, 66, 57, 48,       // 16 e 18
  39, 30, 21, 12, 0, 0, 0, 0,         // 18 a 20
  0, 0, 0, 0, 0, 0, 0, 0,         // 20 e 22
  0, 0, 0, 0, 0, 0, 0, 0          // 22 a 0
};
