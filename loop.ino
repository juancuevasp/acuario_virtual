void loop()
{
  t = rtc.getTime();        //Actualiza los tiempos del sistema
  nivel_leds();             //actualiza la potencia de salida de los leds                   //actualiza hora en pantalla
  if (myTouch.dataAvailable())
  {
  processMyTouch();         //verifica si el lcd esta siendo tocado
  }

  if (millis() - previomillis > 5000)           //verifica funciones cada 5 seg
  {
    revisar_temperaturas();                     //verifica las revisar_temperaturas
    temp_hum();
    min_cnt = NumMins(t.hour, t.min);           //actualiza intervalo para determinar potencia de los leds
    previomillis = millis();
  }

  if (pantallaNo == 0)
  {
    draw_screen();
    reloj();
  }
}
