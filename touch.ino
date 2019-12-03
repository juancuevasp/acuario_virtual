
void processMyTouch()
{
  myTouch.read();
  int x, y;                   //coordenadas touch screen
  x = map((myTouch.getX()),399,0,0,399);
  y = map((myTouch.getY()),0,239,0,239);
  //x = myTouch.getX();
  //y = myTouch.getY();
  Serial.println(String("x: ") + x);
  Serial.println(String("y: ") + y);

  if ((checkButton(iniC[0], iniC[1], iniC[2], iniC[3]) == true) && NoScreen != 0)
  {
    NoScreen = 0;
    clrscreen();
    clockFooter();
    draw_screen(true);
  }
  else
  {
    switch (NoScreen)
    {
      case 0:
        NoScreen = 1;
        clrscreen();
        clockFooter();
        menus();

        break;

      case 1: //---------------------------pantalla de menus-------------------------------------
        if (checkButton(horM[0], horM[1], horM[2], horM[3]) == true)       //selecciona el menu de fecha y hora
        {
          NoScreen = 2;
          clrscreen();
          adjustClock(true);
        }
        else if (checkButton(ledM[0], ledM[1], ledM[2], ledM[3]) == true)       //selecciona el menu de configuracion de leds
        {
          NoScreen = 4;
          clrscreen();
          clockFooter();
          confLeds();
        }
        else if (checkButton(temP[0], temP[1], temP[2], temP[3]) == true)       //selecciona el menu de configuracion de control de temperatura
        {
          NoScreen = 3;
          clrscreen();
          clockFooter();
          confTemp(true);
        }
        else if (checkButton(cpaA[0], cpaA[1], cpaA[2], cpaA[3]) == true)       //selecciona el menu de configuracion de CPA
        {
          NoScreen = 6;
          clrscreen();
          cpa(true);
        }
        else if (checkButton(graF[0], graF[1], graF[2], graF[3]) == true)       //selecciona el menu de configuracion de graficos
        {
          NoScreen = 5;
          clrscreen();
          graphicsScreen();
        }
        break;

      case 2:   //---------------------pantalla configuracion hora y fecha---------------------
        if (checkButton(horU[0], horU[1], horU[2], horU[3]) == true)
        {
          t_temp.hour = (t_temp.hour + 1) % 24;
          adjustClock();
        }
        else if (checkButton(minU[0], minU[1], minU[2], minU[3]) == true)
        {
          t_temp.min = (t_temp.min + 1) % 60;
          adjustClock();

        }
        else if (checkButton(segU[0], segU[1], segU[2], segU[3]) == true)
        {
          t_temp.sec = (t_temp.sec + 1) % 60;
          adjustClock();
        }
        else if (checkButton(horD[0], horD[1], horD[2], horD[3]) == true)
        {
          t_temp.hour = (t_temp.hour + 23) % 24;
          adjustClock();
        }
        else if (checkButton(minD[0], minD[1], minD[2], minD[3]) == true)
        {
          t_temp.min = (t_temp.min + 59) % 60;
          adjustClock();
        }
        else if (checkButton(segD[0], segD[1], segD[2], segD[3]) == true)
        {
          t_temp.sec = (t_temp.sec + 59) % 60;
          adjustClock();
        }
        else if (checkButton(diaU[0], diaU[1], diaU[2], diaU[3]) == true)
        {
          t_temp.date += 1;
          if (t_temp.date > 31)
          {
            t_temp.date = 1;
          }
          t_temp.date =  validateDate(t_temp.date, t_temp.mon, t_temp.year);
          adjustClock();
        }
        else if (checkButton(mesU[0], mesU[1], mesU[2], mesU[3]) == true)
        {
          t_temp.mon +=1;
          if (t_temp.mon > 12)
          {
            t_temp.mon = 1;
          }
          t_temp.date = validateDateForMonth(t_temp.date, t_temp.mon, t_temp.year);
          adjustClock();
        }
        else if (checkButton(anoU[0], anoU[1], anoU[2], anoU[3]) == true)
        {
          t_temp.year +=1;
          t_temp.date = validateDateForMonth(t_temp.date, t_temp.mon, t_temp.year);
         adjustClock();
        }
        else if (checkButton(diaD[0], diaD[1], diaD[2], diaD[3]) == true)
        {
          t_temp.date -=1;
          if (t_temp.date < 1)
          {
            t_temp.date = 31;
          }
          t_temp.date = validateDate(t_temp.date, t_temp.mon, t_temp.year);
          adjustClock();
        }
        else if (checkButton(mesD[0], mesD[1], mesD[2], mesD[3]) == true)
        {
          t_temp.mon -= 1;
          if (t_temp.mon < 1)
          {
            t_temp.mon = 12;
          }
          t_temp.date = validateDateForMonth(t_temp.date, t_temp.mon, t_temp.year);
          adjustClock();
        }
        else if (checkButton(anoD[0], anoD[1], anoD[2], anoD[3]) == true)
        {
          t_temp.year -= 1;
          t_temp.date = validateDateForMonth(t_temp.date, t_temp.mon, t_temp.year);
          adjustClock();
        }
        else if (checkButton(savE[0], savE[1], savE[2], savE[3]) == true)
        {
          rtc.halt(true);
          rtc.setTime(t_temp.hour, t_temp.min, t_temp.sec);
          rtc.setDate(t_temp.date, t_temp.mon, t_temp.year);
          t_temp.dow = calcDOW(t_temp.date, t_temp.mon, t_temp.year);
          rtc.setDOW(t_temp.dow);
          rtc.halt(false);
          NoScreen = 1;
          clrscreen();
          menus();
          clockFooter();
        }

        else if (checkButton(menU[0], menU[1], menU[2], menU[3]) == true)
        {
          NoScreen = 1;
          clrscreen();
          menus();
          clockFooter();
        }
        break;

      case 3:   //---------------------configuracion de control de temperatura----------------------
        if (checkButton(savE[0], savE[1], savE[2], savE[3]) == true)
        {
          setTempC = tempteS;
          offTempC = tempteO;
          alarmTempC = tempteA;
          NoScreen = 3;
          SaveTempToEEPROM();
          clrscreen();
        }
        else if (checkButton(temD[0], temD[1], temD[2], temD[3]) == true)
        {
          tempteS -= 0.1;
          if (tempteS < 10)
          {
            tempteS = 40;
          }
          confTemp();
        }
        else if (checkButton(offD[0], offD[1], offD[2], offD[3]) == true)
        {
          tempteO -= 0.1;
          if (tempteO < 0.1)
          {
            tempteO = 9.9;
          }
          confTemp();
        }
        else if (checkButton(almD[0], almD[1], almD[2], almD[3]) == true)
        {
          tempteA -= 0.1;
          if (tempteA < 0.1)
          {
            tempteA = 9.9;
          }
          confTemp();
        }
        else if (checkButton(temU[0], temU[1], temU[2], temU[3]) == true)
        {
          tempteS += 0.1;
          if (tempteS > 40)
          {
            tempteS = 10;
          }
          confTemp();
        }
        else if (checkButton(offU[0], offU[1], offU[2], offU[3]) == true)
        {
          tempteO += 0.1;
          if (tempteO > 9.9)
          {
            tempteO = 0.1;
          }
          confTemp();
        }
        else if (checkButton(almU[0], almU[1], almU[2], almU[3]) == true)
        {
          tempteA += 0.1;
          if (tempteA > 9.9)
          {
            tempteA = 0.1;
          }
          confTemp();
        }
        else if (checkButton(menU[0], menU[1], menU[2], menU[3]) == true)
        {
          NoScreen = 1;
          clrscreen();
          menus();
          clockFooter();
        }
        break;

      case 4:   //---------------------configuracion control leds-----------------------------------
        break;

      case 5:   //---------------------pantalla seleccion de graficos-------------------------------
        if (checkButton(temG[0], temG[1], temG[2], temG[3]) == true)
        {
          NoScreen = 7;
          clrscreen();
          tempGrapScreen();
        }
        else if (checkButton(temAG[0], temAG[1], temAG[2], temAG[3]) == true)
        {
          NoScreen = 8;
        }
        else if (checkButton(humA[0], humA[1], humA[2], humA[3]) == true)
        {
          NoScreen = 9;
        }
        else if (checkButton(menU[0], menU[1], menU[2], menU[3]) == true)
        {
          NoScreen = 1;
          clrscreen();
          menus();
          clockFooter();
        }
        break;
    }

  }

}
