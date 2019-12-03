
void menus()
{
  printHeader("       MENU");     //imprime cabecera de pantalla

  printButton("HORA Y FECHA", horM[0], horM[1], horM[2], horM[3]);
  printButton("CONFIG LEDS", ledM[0], ledM[1], ledM[2], ledM[3]);
  printButton("CONTROL TEMP.", temP[0], temP[1], temP[2], temP[3]);
  printButton("GRAFICOS", graF[0], graF[1], graF[2], graF[3]);
  printButton("CPA AUTOMATICA", cpaA[0], cpaA[1], cpaA[2], cpaA[3]);
  printButton("INICIO", iniC[0], iniC[1], iniC[2], iniC[3]);
}

void adjustClock(boolean refreshAll = false)
{
  if (refreshAll == true)
  {
    t_temp = rtc.getTime();

    printHeader("ALTERAR HORA Y FECHA");        //imprime cabecera de pantalla

    printButton ("+", horU[0], horU[1], horU[2], horU[3], true);       //hora +
    printButton ("-", horD[0], horD[1], horD[2], horD[3], true);       //hora -

    printButton ("+", minU[0], minU[1], minU[2], minU[3], true);       //minuto +
    printButton ("-", minD[0], minD[1], minD[2], minD[3], true);       //minuto -

    printButton ("+", segU[0], segU[1], segU[2], segU[3], true);       //segundo +
    printButton ("-", segD[0], segD[1], segD[2], segD[3], true);       //segundo -

    printButton ("+", anoU[0], anoU[1], anoU[2], anoU[3], true);       //año +
    printButton ("-", anoD[0], anoD[1], anoD[2], anoD[3], true);       //año -

    printButton ("-", diaD[0], diaD[1], diaD[2], diaD[3], true);       //dia -
    printButton ("+", diaU[0], diaU[1], diaU[2], diaU[3], true);       //dia +

    printButton ("+", mesU[0], mesU[1], mesU[2], mesU[3], true);     //mes +
    printButton ("-", mesD[0], mesD[1], mesD[2], mesD[3], true);     //mes -

    printButton ("GUARDAR", savE[0], savE[1], savE[2], savE[3]);
    printButton ("INICIO", iniC[0], iniC[1], iniC[2], iniC[3]);
    printButton ("MENU", menU[0], menU[1], menU[2], menU[3]);
    setFont (SMALL, 255, 255, 255, 12, 6, 140);
    myGLCD.print (String("HORA"), 10, 51);
    myGLCD.print (String("DIA"), 10, 134);
    setFont (LARGE, 255, 255, 255, 12, 6, 140);
    myGLCD.print (String(":"), 120, 48);
    myGLCD.print (String(":"), 210, 48);
  }

  if (t_temp.hour < 10)
  {
    myGLCD.printNumI (0, 70, 48);
    myGLCD.printNumI (t_temp.hour, 86, 48);
  }
  else
  {
    myGLCD.printNumI(t_temp.hour, 70, 48);
  }

  if (t_temp.min <10)
  {
    myGLCD.printNumI(0, 160, 48);
    myGLCD.printNumI(t_temp.min, 176, 48);
  }
  else
  {
    myGLCD.printNumI(t_temp.min, 160, 48);
  }

  if (t_temp.sec < 10)
  {
    myGLCD.printNumI(0, 250, 48);
    myGLCD.printNumI(t_temp.sec, 266, 48);
  }
  else
  {
    myGLCD.printNumI(t_temp.sec, 250, 48);
  }

  if (t_temp.date < 10)
  {
    myGLCD.printNumI(0, 70, 132);
    myGLCD.printNumI(t_temp.date, 86, 132);
  }
  else
  {
    myGLCD.printNumI(t_temp.date, 70, 132);
  }

  if (t_temp.mon < 10)
  {
    myGLCD.printNumI(0, 160, 132);
    myGLCD.printNumI(t_temp.mon, 176, 132);
  }
  else
  {
    myGLCD.printNumI(t_temp.mon, 160, 132);
  }

  myGLCD.printNumI(t_temp.year, 230, 132);
}

void cpa (boolean refreshAll = false)
{
  if (refreshAll)
  {
    temp2hora = hora;
    temp2minuto = minuto;
    temp2duracionmximacpa = duracionmaximacpa;
    for(byte i = 0; i < 7; i++)
    {
      semana[i] = semana_e[i];
    }
    printHeader("CONF. DIAS Y HORARIO CPA AUTOMATICA");        //imprime cabecera de pantalla

    printButton ("+", horU[0], horU[1], horU[2], horU[3], true);       //hora +
    printButton ("-", horD[0], horD[1], horD[2], horD[3], true);       //hora -
    printButton ("+", minUT[0], minUT[1], minUT[2], minUT[3], true);   //minuto +
    printButton ("-", minDT[0], minDT[1], minDT[2], minDT[3], true);   //minuto -
    printButton ("+", durU[0], durU[1], durU[2], durU[3], true);       //minuto +
    printButton ("-", durD[0], durD[1], durD[2], durD[3], true);       //minuto -

    setFont(LARGE, 255, 255, 255, 12, 6, 140);
    myGLCD.print(String(":"), 105, 48);
    myGLCD.setFont(RusFont1);
    myGLCD.print(String("HORA"), 10, 51);
    myGLCD.print(String("DURACION MAXIMA"), 153, 31);
    myGLCD.print(String("POR ESTADO"), 170, 46);
    printButton ("GUARDAR", savE[0], savE[1], savE[2], savE[3]);
    printButton ("INICIO", iniC[0], iniC[1], iniC[2], iniC[3]);
    printButton ("MENU", menU[0], menU[1], menU[2], menU[3]);
  }
  if (semana[0] == 1)
  {
    printButton("LUNES", monD[0], monD[1], monD[2], monD[3], false, 1);      //boton lunes
  }
  else
  {
    printButton("LUNES", monD[0], monD[1], monD[2], monD[3]);                //boton lunes
  }

  if (semana[1] == 2)
  {
    printButton("MARTES", tueS[0], tueS[1], tueS[2], tueS[3], false, 1);     //boton martes
  }
  else
  {
    printButton("MARTES", tueS[0], tueS[1], tueS[2], tueS[3]);               //boton martes
  }

  if (semana[2] == 3)
  {
    printButton("MIERCOLES", wedN[0], wedN[1], wedN[2], wedN[3], false, 1);  //boton miercoles
  }
  else
  {
    printButton("MIERCOLES", wedN[0], wedN[1], wedN[2], wedN[3]);            //boton miercoles
  }

  if (semana[3] == 4)
  {
    printButton("JUEVES", thuR[0], thuR[1], thuR[2], thuR[3], false, 1);     //boton jueves
  }
  else
  {
    printButton("JUEVES", thuR[0], thuR[1], thuR[2], thuR[3]);              //boton jueves
  }

  if (semana[4] == 5)
  {
    printButton("VIERNES", friD[0], friD[1], friD[2], friD[3], false, 1);   //boton viernes
  }
  else
  {
    printButton("VIERNES", friD[0], friD[1], friD[2], friD[3]);            //boton viernes
  }

  if (semana[5] ==6)
  {
    printButton("SABADO", satU[0], satU[1], satU[2], satU[3], false, 1);   //boton sabado
  }
  else
  {
    printButton("SABADO", satU[0], satU[1], satU[2], satU[3]);            //boton sabado
  }

  if (semana[6] == 7)
  {
    printButton("DOMINGO", sunD[0], sunD[1], sunD[2], sunD[3], false, 1); //boton domingo
  }
  else
  {
    printButton("DOMINGO", sunD[0], sunD[1], sunD[2], sunD[3]);           //boton domingo
  }

  if (bitRead(cpa_status, 2) == true)
  {
    printButton("FALLA!", estT[0], estT[1], estT[2], estT[3], false, 2); //señaliza que hubo un fallo durante cpa automatica
  }
  else
  {
    printButton("NORMAL", estT[0], estT[1], estT[2], estT[3]);           //señaliza que cpa fue realizada normalmente
  }

  setFont(LARGE, 255, 255, 255, 12, 6, 140);
  if (temp2hora < 10)
  {
    myGLCD.printNumI(0, 70, 48);
    myGLCD.printNumI(temp2hora, 86, 48);
  }
  else
  {
    myGLCD.printNumI(temp2hora, 70, 48);
  }

  if (temp2minuto < 10)
  {
    myGLCD.printNumI(0, 120, 48);
    myGLCD.printNumI(temp2minuto, 136, 48);
  }
  else
  {
    myGLCD.printNumI(temp2minuto, 120, 48);
  }

  if (temp2duracionmximacpa < 10)
  {
    myGLCD.printNumI(0, 275, 48);
    myGLCD.printNumI(temp2duracionmximacpa, 291, 48);
  }
  else
  {
    myGLCD.printNumI(temp2duracionmximacpa, 275, 48);
  }
}

void confLeds ()
{
  printHeader("CONFIGURAR LEDS");        //imprime cabecera de pantalla
  printButton ("GUARDAR", savE[0], savE[1], savE[2], savE[3]);
  printButton ("INICIO", iniC[0], iniC[1], iniC[2], iniC[3]);
  printButton ("MENU", menU[0], menU[1], menU[2], menU[3]);
}

void confTemp (boolean refreshAll = false)
{
  if (refreshAll)
  {
    if (setTempC == 0)
    {
      setTempC = tempC;           //carga temperatura actual
    }
    tempteS = setTempC;
    tempteO = offTempC;
    tempteA = alarmTempC;

    printHeader("CONTROL DE TEMPERATURA");        //imprime cabecera de pantalla

    setFont(SMALL, 255, 255, 255, 12, 6, 140);

    myGLCD.print(String("TEMPERATURA DESEADA"), 85, 20);
    myGLCD.print(String("VARIACION PERMITIDA"), 90, 70);
    myGLCD.print(String("VARIACION PARA ACCIONAR ALARMA"), 50, 120);

    printButton("-", temD[0], temD[1], temD[2], temD[3], true);
    printButton("+", temU[0], temU[1], temU[2], temU[3], true);
    printButton("-", offD[0], offD[1], offD[2], offD[3], true);
    printButton("+", offU[0], offU[1], offU[2], offU[3], true);
    printButton("-", almD[0], almD[1], almD[2], almD[3], true);
    printButton("+", almU[0], almU[1], almU[2], almU[3], true);

    printButton ("GUARDAR", savE[0], savE[1], savE[2], savE[3]);
    printButton ("INICIO", iniC[0], iniC[1], iniC[2], iniC[3]);
    printButton ("MENU", menU[0], menU[1], menU[2], menU[3]);
  }

  setFont(LARGE, 255, 255, 255, 12, 6, 140);
  myGLCD.printNumF(tempteS, 1, 130, 40);
  myGLCD.printNumF(tempteO, 1, 140, 90);
  myGLCD.printNumF(tempteA, 1, 140, 140);
}

void graphicsScreen ()
{
  printHeader("ESCOJA UN GRAFICO");        //imprime cabecera de pantalla
  printButton ("TEMPERATURA", temG[0], temG[1], temG[2], temG[3]);
  printButton ("TEMP. AMBIENTE", temAG[0], temAG[1], temAG[2], temAG[3]);
  printButton ("HUMEDAD AMBIENTE", humA[0], humA[1], humA[2], humA[3]);
  printButton ("GUARDAR", savE[0], savE[1], savE[2], savE[3]);
  printButton ("INICIO", iniC[0], iniC[1], iniC[2], iniC[3]);
  printButton ("MENU", menU[0], menU[1], menU[2], menU[3]);
}
