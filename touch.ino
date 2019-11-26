
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

  if ((revisarBoton(iniC[0], iniC[1], iniC[2], iniC[3]) == true) && pantallaNo != 0)
  {
    pantallaNo = 0;
    clrscreen();
    reloj();
    draw_screen(true);
  }
  else
  {
    switch (pantallaNo)
    {
      case 0:
        pantallaNo = 1;
        clrscreen();
        reloj();
        menus();

        break;
      case 1:
        if (revisarBoton(horM[0], horM[1], horM[2], horM[3]) == true)       //selecciona el menu de fecha y hora
        {
          pantallaNo = 2;
          clrscreen();
          reloj();
          setReloj(true);
        }
        else if (revisarBoton(ledM[0], ledM[1], ledM[2], ledM[3]) == true)
        {
          pantallaNo = 3;
          clrscreen();
          reloj();
          confLeds();
        }
        else if (revisarBoton(temP[0], temP[1], temP[2], temP[3]) == true)
        {
          pantallaNo = 4;
          clrscreen();
          reloj();
          cnTemp(true);
        }
        else if (revisarBoton(cpaA[0], cpaA[1], cpaA[2], cpaA[3]) == true)
        {
          pantallaNo = 5;
          clrscreen();
          cpa(true);
        }
        else if (revisarBoton(graF[0], graF[1], graF[2], graF[3]) == true)
        {
          pantallaNo = 6;
          clrscreen();
          reloj();
          graficos();
        }
      case 2:
        if (revisarBoton(horU[0], horU[1], horU[2], horU[3]) == true)
        {
          reloj();
        }
        else if (revisarBoton(menU[0], menU[1], menU[2], menU[3]) == true)
        {
          pantallaNo = 1;
          clrscreen();
          menus();
        }
    }
  }

}
