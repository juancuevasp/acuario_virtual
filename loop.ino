void loop()
{
  t = rtc.getTime();                          //Actualiza los tiempos del sistema
  nivel_leds();                               //actuliza la potencia de salida de los leds
  draw_hour();                                //imprime hora en pantalla
  draw_screen();

  if (millis() - previomillis > 5000)
  {
    revisar_temperaturas();                     //verifica las revisar_temperaturas
    temp_hum();
    min_cnt = NumMins(t.hour, t.min);           //actualiza intervalo para determinar potencia de los leds
    Serial.println(led_out1);
    Serial.println(LedPorcentaje(led_out1));
    previomillis = millis();
  }
}
