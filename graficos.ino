
void tempGrapScreen()
{
  int x, y, z, graphic;
  int16_t n;
  char buf[8];
  float temperature;
  int j = 0;
  int i = 0;
  int k = 0;
  float sum = 0.0f;       //suma los valores de todos los elementos
  float half = 0.0f;      //media de los valores
  float lineR;
  float lineG;
  float lineB;
  int f = 30;

  printHeader("GRAFICO DE TEMPERATURA DE AGUA");

  setFont(SMALL, 255, 255, 255, 12, 6, 140);

  for (float i = 27.5; i > 22; i -= 0.5)
  {
    myGLCD.printNumF(i, 1, 5, 3 + f);
    f += 15;
  }

  f = 255;
  for (int i = 22; i > 0; i -= 2)
  {
    myGLCD.printNumI(i, f, 193);
    f -= 20;
  }

  myGLCD.print(String("0"), 275, 193);
  myGLCD.drawCircle(15, 21, 2);
  myGLCD.print(String("C"), 20, 18);
  myGLCD.print(String("H"), 290, 193);

  myGLCD.drawLine(40, 30, 40, 190);     //eje y
  myGLCD.drawLine(40, 190, 290, 190);   //eje x

  myGLCD.setColor(150, 150, 150);          //malla

  // eje X
  for (int k = 40; k < 180; k += 15)
  {
    myGLCD.drawLine(40, k, 290, k);
  }

  // eje Y
  for (int l = 60; l < 300; l += 20)
  {
    myGLCD.drawLine(l, 30, l, 190);
  }
  lineR = setTempC;     //lineas de comparacion
  lineG = (setTempC + offTempC);
  lineB = (setTempC - offTempC);

  if ((lineR >= 22.5) && (lineR <= 27.5))
  {
    x = (190 - ((lineR - 22.5) * 30));
  }
  else if (lineR > 27.5)
  {
    x = 30;
  }
  else if (lineR < 22.5)
  {
    x = 190;
  }

  if ((lineG >= 22.5) && (lineG <= 27.5))
  {
    y = (190 - ((lineG - 22.5) * 30));
  }
  else if (lineG > 27.5)
  {
    y = 30;
  }
  else if (lineG < 22.5)
  {
    y = 190;
  }

  if ((lineB >= 22.5) && (lineB <= 27.5))
  {
    z = (190 - ((lineB - 22.5) * 30));
  }
  else if (lineB > 27.5)
  {
    z = 30;
  }
  else if (lineB < 22.5)
  {
    z = 190;
  }

  myGLCD.setColor(0, 255, 0);
  myGLCD.drawLine(40, x, 290, x);     //temperatura deseada
  myGLCD.setColor(255, 0, 0);       //variacion permitida
  myGLCD.drawLine(40, y, 290, y);     //variacion superior
  myGLCD.drawLine(40, z, 290, z);     //variacion inferior

  printButton("INICIO", iniC[0], iniC[1], iniC[2], iniC[3]);
  printButton ("MENU", menU[0], menU[1], menU[2], menU[3]);

  setFont(SMALL, 255, 255, 0, 0, 0, 0);

  int d = 41 + (NumMins(t.hour, t.min) / 6);

  myGLCD.drawLine(d, 30, d, 190);       //linea de marcacion de horario
  myGLCD.print(rtc.getTimeStr(FORMAT_SHORT), d + 2, 75, 270);

  select_SD();
  if (file.open("LOGTEMPDIA.TXT", O_READ))
  {
    while((n = file.read(buf, sizeof(buf))) > 0)
    {
      temperature = atof(buf);
      sum += temperature;

      if (strlen(buf) == 5)
      {
        i++;
        k++;
      }

      if (temperature <= 2)
      {
        k -= 1;
      }

      if (i == 6)
      {
        half = sum / k;
        i = 0;
        j++;
        sum = 0;
        k = 0;

        if ((half) > 27.5)
        {
          graphic = 30;
        }
        else if ((half >= 22.5) && (half <= 27.5))
        {
          graphic = (190 - ((half - 22.5) * 30));
        }
        else
        {
          graphic = 190;
        }

        setFont(SMALL, 255, 0, 255, 0, 0, 0);

        if (j < 250)
        {
          myGLCD.drawPixel((40 + j), graphic);

        }
      }
    }
    file.close();
  }
}
