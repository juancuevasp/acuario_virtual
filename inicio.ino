void clrscreen()
{
  myGLCD.clrScr();
  myGLCD.fillScr(12, 6, 140);       //define color de la pantalla
}

void clockFooter()                         //dihuja fecha y hora en la parte inferior de la pantalla
{
  setFont(SMALL, 255, 255, 255, 12, 6, 140);
  myGLCD.print(rtc.getDOWStr(), 7, 223);      //dia de la semana
  myGLCD.print(String(t.date), 85, 223);      //dia del mes
  myGLCD.print(String("DE"), 113, 223);
  myGLCD.print(rtc.getMonthStr(), 140, 223);  //mes
  myGLCD.print(String("DE"), 220, 223);
  myGLCD.print(String(t.year), 250, 223);     //año
  myGLCD.print(rtc.getTimeStr(), 330, 223);   //fecha
}

void draw_screen(boolean refreshAll = false)
{
  int ledlevel;
  int offset = 0;

  //dibuja cuadros de pantalla
  myGLCD.setColor(255, 0, 0);
  myGLCD.fillRect(4, 4, 198, 5);
  myGLCD.fillRect(4, 4, 5, 160);
  myGLCD.fillRect(4, 160, 198, 159);
  myGLCD.fillRect(198, 4, 197, 160);
  myGLCD.fillRect(4, 163, 5, 210);
  myGLCD.fillRect(4, 163, 198, 164);
  myGLCD.fillRect(4, 210, 198, 211);
  myGLCD.fillRect(198, 163, 197, 210);
  myGLCD.fillRect(201, 4, 396, 5);
  myGLCD.fillRect(201, 4, 202, 210);
  myGLCD.fillRect(201, 210, 396, 211);
  myGLCD.fillRect(396, 4, 395, 210);

  if (refreshAll == true)
  {
    setFont (SMALL, 255, 255, 255, 12, 6, 140);
    myGLCD.print(String("POTENCIA DE LUCES"), 30, 10);

    //dibuja regla que marca el porcentaje
    for (byte y = 152; y > 30; y = y - 12)   //marca de 10
    {
      for (byte x = 38; x < 48; x++)
      {
        myGLCD.getColor();
        myGLCD.drawPixel(x, y);
      }
      for (byte x = 65; x < 75; x++)
      {
        myGLCD.getColor();
        myGLCD.drawPixel(x, y);
      }
      for (byte x = 90; x < 100; x++)
      {
        myGLCD.getColor();
        myGLCD.drawPixel(x, y);
      }
      for (byte x = 115; x < 125; x++)
      {
        myGLCD.getColor();
        myGLCD.drawPixel(x, y);
      }
    }
    for (byte y = 146; y > 35; y = y - 12)    //marca de 5
    {
      for (byte x = 38; x < 43; x++)
      {
        myGLCD.getColor();
        myGLCD.drawPixel(x, y);
      }
    }
    myGLCD.drawLine(37, 29, 37, 152);

    //dibuja numeros de regla
    byte numero[] = {10, 20, 30, 40, 50, 60, 70, 80, 90};
    for ( byte h = 0, i = 133; i >= 37; i -= 12)
    {

      myGLCD.print(String(numero[h++]), 18, i);
    }
    myGLCD.print(String("0"), 26, 145);
    myGLCD.print(String("100"), 10, 25);

    //textos pantalla general
    myGLCD.print(String("TEMP. AGUA:"), 210, 15);
    myGLCD.print(String("CALENTADOR:"), 210, 37);
    myGLCD.print(String("TEMP. DISIPADOR:"), 210, 59);
    myGLCD.print(String("NIVEL ACUARIO:"), 210, 81);
    myGLCD.print(String("TEMP. DEPOSITO:"), 210, 103);
    myGLCD.print(String("NIVEL DEPOSITO:"), 210, 125);
    myGLCD.print(String("TEMP. AMBIENTE:"), 210, 147);
    myGLCD.print(String("HUM. AMBIENTE:"), 210, 169);
    myGLCD.print(String("ENERGIA:"), 210, 191);
    myGLCD.print(String("LED 2"), 145, 75);
    myGLCD.print(String("LED 3"), 145, 120);

    //unidades de medida
    myGLCD.setColor(0, 255, 0);
    myGLCD.drawCircle(347, 12, 2);                   // Unidad t. agua
    myGLCD.print(String("C"), 350, 15);              // Unidad t. agua
    myGLCD.drawCircle(375, 57, 2);                   // Unidad t. disipador
    myGLCD.print(String("C"), 378, 59);              // Unidad t. disipador
    myGLCD.drawCircle(375, 101, 2);                  // Unidad t. deposito
    myGLCD.print(String("C"), 378, 103);             // Unidad t. deposito
    myGLCD.drawCircle(375, 145, 2);                  // Unidad t. ambiente
    myGLCD.print(String("C"), 378, 147);             // Unidad t. ambiente
    myGLCD.print(String("%"), 370, 169);             // Unidad humedad ambiente
  }

  if ((led1 != led_out1) || refreshAll)          //actualiza grafico led 1
  {
    led1 = led_out1;
    ledlevel = LedPorcentaje(led_out1);
    myGLCD.setColor(255, 255, 255);
    myGLCD.print(String("LED 1"), 145, 30);
    offset = map(ledlevel, 100, 0, 32, 152);
    myGLCD.fillRect(50, offset, 65, 152);               //dibuja barra actual
    myGLCD.print(String(ledlevel), 147, 43);
    myGLCD.print(String("%"), 172, 43);
    drawFillRect(50, offset -1, 65, 29, 12, 6, 140);    //apaga barra anterior
  }

  if ((led2 != led_out2) || refreshAll)                 //actualiza grafico led 2
  {
    led2 = led_out2;
    ledlevel = LedPorcentaje(led_out2);
    myGLCD.setColor(255, 255, 255);
    offset = map(ledlevel, 100, 0, 32, 152);
    myGLCD.fillRect(75, offset, 90, 152);               //dibuja barra actual
    myGLCD.print(String(ledlevel), 147, 88);
    myGLCD.print(String("%"), 172, 88);
    drawFillRect(75, offset -1, 90, 29, 12, 6, 140);    //apaga barra anterior
  }

  if ((led3 != led_out3) || refreshAll)                 //actualiza grafico led 3
  {
    led3 = led_out3;
    ledlevel = LedPorcentaje(led_out3);
    myGLCD.setColor(255, 255, 255);
    offset = map(ledlevel, 100, 0, 32, 152);
    myGLCD.fillRect(100, offset, 115, 152);               //dibuja barra actual
    myGLCD.print(String(ledlevel), 147, 133);
    myGLCD.print(String("%"), 172, 133);
    drawFillRect(100, offset -1, 115, 29, 12, 6, 140);    //apaga barra anterior
  }

  //borra valores de pantalla
  myGLCD.setColor(12, 6, 140);
  myGLCD.fillRect(313, 15, 347, 26);              //apagar t. agua
  myGLCD.fillRect(313, 37, 370, 48);              //apagar calefactor encendido

  //imprime valores de sensores en pantalla principal
  if (tempC == -127)
  {
    myGLCD.setColor(255, 0, 0);
    myGLCD.print(String("ERROR"), 300, 15);
  }
  else
  {
    myGLCD.setColor(0, 255, 0);
    myGLCD.printNumF(tempC, 2, 300, 15);

    myGLCD.setColor(255, 0, 0);

    if (bitRead(status_parametros,1) == true)
    {
      myGLCD.printNumF(tempC, 2, 300, 15);       //imprime temperatura en rojo
    }
  }

  if (bitRead(status_parametros, 0) == true)
  {
    myGLCD.setColor(255, 0, 0);
    myGLCD.print(String("ENCENDIDO"), 300, 37);
  }
  else
  {
    myGLCD.setColor(0, 255, 0);
    myGLCD.print(String("APAGADO"), 300, 37);
  }

  if (tempD == -127)
  {
    myGLCD.setColor(255, 0, 0);
    myGLCD.print(String("ERROR"), 330, 103);
  }
  else
  {
    myGLCD.setColor(0, 255, 0);
    myGLCD.printNumF(tempD, 2, 330, 103);           //imprime temperatura de deposito
  }

  myGLCD.setColor(0, 255, 0);
  myGLCD.printNumF(room_temp, 2, 330, 147);   //imprime temperatura ambiente
  myGLCD.printNumF(ambient_hum, 2, 325, 169);    //imprime humedad ambiente


}
