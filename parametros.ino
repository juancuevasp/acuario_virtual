void revisar_temperaturas() //Revisa temperaturas
{
  sensors.requestTemperatures();                                       //llamada para todos los sensores
  tempC = (sensors.getTempC(aquarium_sensor));            //lee temperatura del agua
  tempD = (sensors.getTempC(deposit_sensor));   //lee temperatura del agua del deposito
/*
  if (contador_temp == 5)
  {
    tempC = temperatura_agua_temp / 5;
    tempD = temperatura_desposito_temp / 5;
    contador_temp = 0;
    temperatura_agua_temp = 0;
    temperatura_desposito_temp = 0;
  }*/

  if (tempC < (setTempC + offTempC + alarmTempC) && tempC > (setTempC - offTempC - alarmTempC))
  {
    bitWrite(status_parametros, 1, 0);
  }

  if (alarmTempC > 0)             //acciona alarma
  {
    if ((tempC >= (setTempC + offTempC + alarmTempC)) || (tempC <= (setTempC - offTempC - alarmTempC)))
    {
      bitWrite(status_parametros, 1, 1);
    }
  }

  if (outlets_changed[0] == true)
  {
    outlets_changed[0] = false;
    bitWrite(status_parametros, 0, 0);
    myDigitalWrite(heater, LOW);
  }

  if (outlets[0] == 0)
  {
    if ((tempC < (setTempC + offTempC)) || (tempC > (setTempC - offTempC)))      //desconecta calefactor
    {
      bitWrite(status_parametros, 0, 0);
      myDigitalWrite(heater, LOW);
    }

    if (offTempC > 0)
    {
      if (tempC < (setTempC -offTempC))     //conecta calefactor
      {
        bitWrite(status_parametros, 0, 1);
        myDigitalWrite(heater, HIGH);
      }
    }

    if ((tempC > 40) || (tempC < 10))
    {
      bitWrite(status_parametros, 0, 0);
      myDigitalWrite(heater, LOW);
    }
  }

  if (outlets[0] == 1)
  {
    bitWrite(status_parametros, 0, 1);
    myDigitalWrite(heater, HIGH);
  }
  else if (outlets[0] == 2)
  {
    bitWrite(status_parametros, 0, 0);
    myDigitalWrite(heater, LOW);
  }
}

void temp_hum()                         //mide temperatura y humedad ambiente
{
  DHT.read(temhum);                     //llamada para el sensor
  room_temp = (DHT.temperature);   //lee temperatura ambiente
  ambient_hum = (DHT.humidity);       //lee humedad ambiente
}

void revisar_nivel()
{
  if ((myAnalogRead(aquaLevel) > 400) && (bitRead(cpa_status, 1) == false))
  {
    nivel_status1 = true;           //señliza nivel bajo en el acuario
  }
  else
  {
    nivel_status2 = false;          //señaliza nivel normal en el acuario
  }
}
