void loop()
{
  t = rtc.getTime();        //Actualiza los tiempos del sistema
  nivel_leds();             //actualiza la potencia de salida de los leds

  if ((millis() - log_SD_millis) > 60000)
  {
    select_SD();
    logtemgraf();
    log_SD_millis = millis();
  }

  if (myTouch.dataAvailable())
  {
  processMyTouch();         //verifica si el lcd esta siendo tocado
  }

  if (millis() - previomillis > 5000)           //verifica funciones cada 5 seg
  {
    revisar_temperaturas();                     //verifica las temperaturas
    temp_hum();
    min_cnt = NumMins(t.hour, t.min);           //actualiza intervalo para determinar potencia de los leds
    previomillis = millis();
  }

  if (NoScreen == 0)
  {
    draw_screen();
    clockFooter();
  }
}
