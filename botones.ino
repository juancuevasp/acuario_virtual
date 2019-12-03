//**********************************************************************************************
//*********************** Botones de los menus *************************************************
//**********************************************************************************************

const byte horM[] = {10, 27, 150, 67};      //menus fecha y hora
const byte ledM[] = {10, 77, 150, 117};     //menu configurar leds
const int temP[] = {170, 77, 310, 117};     //menu configurar temperatura
const byte graF[] = {10, 127, 150, 167};    //menu graficos
const int cpaA[] = {170, 27, 310, 67};      //menu cambio parcial de agua
const int iniC[] = {325, 27, 390, 67};      //boton inicio
const int menU[] = {325, 77, 390, 117};     //boton menu
const int savE[] = {325, 172, 390, 210};    //boton guardar
const byte horU[] = {70, 18, 95, 43};       //boton mas hora
const byte horD[] = {70, 69, 95, 92};       //boton menos hora
const byte minU[] = {160, 18, 185, 43};     //boton mas minutos
const byte minD[] = {160, 69, 185, 92};     //boton menos minutos
const int segU[] = {250, 18, 275, 43};      //boton mas segundos
const int segD[] = {250, 69, 275, 92};      //boton menos segundos
const int anoU[] = {250, 102, 275, 127};    //boton mas año
const int anoD[] = {250, 152, 275, 177};    //boton menos año
const byte diaU[] = {70, 102, 95, 127};     //boton mas dia
const byte diaD[] = {70, 152, 95, 177};     //boton menos dia
const byte mesU[] = {160, 102, 185, 127};   //boton mas mes
const byte mesD[] = {160, 152, 185, 177};   //boton menos mes
const byte temU[] = {205, 35, 230, 60};     //boton mas temperatura
const byte temD[] = {90, 35, 115, 60};      //boton menos temperatura
const byte offU[] = {205, 85, 230, 110};    //boton mas set point temperatura
const byte offD[] = {90, 85, 115, 110};     //boton menos set point temperatura
const byte almU[] = {205, 135, 230, 160};   //boton mas set point alarma temperatura
const byte almD[] = {90, 135, 115, 160};    //boton menos se point alarma temperatura
const byte temG[] = {10, 20, 150, 60};      //boton grafico de temperatura
const int humA[] = {170, 20, 310, 60};      //boton grafico de humedad ambiente
const byte temAG[] = {10, 70, 150, 110};    //boton grafico de temperatura ambiente
const byte minUT[] = {120, 18, 145, 43};    //minuto cpa mas
const byte minDT[] = {120, 69, 145, 92};    //minuto cpa menos
const int durU[] = {275, 18, 300, 43};      //duracion cpa +
const int durD[] = {275, 69, 300, 92};      //duracion cpa -
const byte monD[] = {30, 99, 110, 139};     //lunes cpa
const byte tueS[] = {120, 99, 200, 139};    //martes cpa
const  int wedN[] = {210, 99, 290, 139};    //miercoles cpa
const byte thuR[] = {30, 146, 110, 186};    //jueves cpa
const byte friD[] = {120, 146, 200, 186};   //viernes cpa
const int satU[] = {210, 146, 290, 186};    //sabado cpa
const byte sunD[] = {120, 193, 200, 233};   //domingo cpa
const int estT[] = {210, 193, 290, 233};    //estado cpa

void printHeader (const char* texto)
{
  setFont(SMALL, 255, 255, 0, 255, 255, 0);
  myGLCD.fillRect(1, 1, 310, 14);
  myGLCD.setColor(0, 0, 0);
  myGLCD.print(texto, 5, 4);
}

void setFont(boolean font, byte cr, byte cg, byte cb, byte br, byte bg, byte bb)
{
  myGLCD.setBackColor (br, bg, bb);        //color de fondo
  myGLCD.setColor (cr, cg, cb);            //color principal
  if (font == LARGE)
    myGLCD.setFont (BigFont);
  else if (font == SMALL)
    myGLCD.setFont (RusFont1);
}

void tocado(int x1, int y1, int x2, int y2)
{
  myGLCD.setColor (255, 0, 0);
  myGLCD.drawRoundRect (x1, y1, x2, y2);
  while (myTouch.dataAvailable())
  {
    myTouch.read();
  }
  myGLCD.setColor(255, 255, 255);
  myGLCD.drawRoundRect(x1, y1, x2, y2);
}

void printButton (const char* texto, int x1, int y1, int x2, int y2, boolean setFont = false, byte cor = 0)
{
  int stl = strlen(texto);
  int fx, fy;
  const byte color [3][3] = {{0, 0, 200}, {0, 150, 86}, {255, 0, 0}};

  myGLCD.setColor(color[cor][0], color[cor][1], color[cor][2]);
  myGLCD.fillRoundRect (x1, y1, x2, y2);
  myGLCD.setColor(255, 255, 255);
  myGLCD.drawRoundRect (x1, y1, x2, y2);

  myGLCD.setBackColor(color[cor][0], color[cor][1], color[cor][2]);
  if (setFont == true)
  {
    myGLCD.setFont(BigFont);
    fx = x1 + (((x2 - x1 + 1) - (stl * 16)) / 2);
    fy = y1 + (((y2 - y1 + 1) - 16) / 2);
    myGLCD.print(texto, fx, fy);
  }
  else
  {
    myGLCD.setFont(RusFont1);
    fx = x1 + (((x2 - x1) - (stl * 8)) / 2);
    fy = y1 + (((y2 - y1 - 1) - 6) / 2);
    myGLCD.print(texto, fx, fy);
  }
}
void drawFillRect(int x1, byte y1, int x2, byte y2, byte r, byte g, byte b)
{
  myGLCD.setColor(r, g, b);
  myGLCD.fillRect(x1, y1, x2, y2);
}

boolean checkButton(int x1, int y1, int x2, int y2)
{
  boolean match = false;
  int touch_x = map((myTouch.getX()),399,0,0,399);
  int touch_y = map((myTouch.getY()),0,239,0,239);

  if ((touch_x >= x1) && (touch_x <= x2) && (touch_y >= y1) && (touch_y <= y2))
  {
    match = true;
    tocado(x1, y1, x2, y2);
  }
  return match;
}
