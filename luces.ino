int LedPorcentaje (int Led_out)           //devuelve la salida del led en %
{
  int result;

  if (Led_out == 0)
  {
    result = 0;
  }
  else
  {
    result = map(Led_out, 1, 255, 1, 100);
  }
  

  return result;
}

//-----------niveles de potencia de los leds-------------
void nivel_leds()
{
  int sector, sstep, t1, t2;

  if (NumMins(led_off_hora, led_off_minuto) > NumMins(led_on_hora, led_on_minuto))   //revisa en que periodo se encuentra
  {
    if ((NumMins(t.hour, t.min) >= (NumMins(led_on_hora, led_on_minuto) - amanecer_anochecer)) && (NumMins(t.hour, t.min) <= (NumMins(led_off_hora, led_off_minuto) + amanecer_anochecer)))
    {
      if ((NumMins(t.hour, t.min) >= (NumMins(led_on_hora, led_on_minuto) - amanecer_anochecer)) && (NumMins(t.hour, t.min) <= NumMins(led_on_hora, led_on_minuto)))
      {
        led_out1 = led_out2 = led_out3 = map(NumMins(t.hour, t.min), (NumMins(led_on_hora, led_on_minuto) - amanecer_anochecer), NumMins(led_on_hora, led_on_minuto), 0, pwm_definido);
      }
      else if ((NumMins(t.hour, t.min) >= NumMins(led_off_hora, led_off_minuto)) && (NumMins(t.hour, t.min) <= (NumMins(led_off_hora, led_off_minuto) + amanecer_anochecer)))
      {
        led_out1 = led_out2 = led_out3 = map(NumMins(t.hour, t.min), NumMins(led_off_hora, led_off_minuto), (NumMins(led_off_hora, led_off_minuto) + amanecer_anochecer), pwm_definido, 0);
      }
      else
      {
        led_out1 = led_out2 = led_out3 = pwm_definido;
      }
    }
  }
  else if (NumMins(led_off_hora, led_off_minuto) < NumMins(led_on_hora, led_on_minuto))
  {
    if (NumMins(t.hour, t.min) >= (NumMins(led_on_hora, led_on_minuto) - amanecer_anochecer))
    {
      if ((NumMins(t.hour, t.min) >= (NumMins(led_on_hora, led_on_minuto) - amanecer_anochecer)) && (NumMins(t.hour, t.min) <= NumMins(led_on_hora, led_on_minuto)))
      {
        led_out1 = led_out2 = led_out3 = map(NumMins(t.hour, t.min), (NumMins(led_on_hora, led_on_minuto) - amanecer_anochecer), NumMins(led_on_hora, led_on_minuto), 0, pwm_definido);
      }
      else
      {
        led_out1 = led_out2 = led_out3 = pwm_definido;
      }
    }
    else if (NumMins(t.hour, t.min) <= (NumMins(led_off_hora, led_off_minuto) + amanecer_anochecer))
    {
      if ((NumMins(t.hour, t.min) <= (NumMins(led_off_hora, led_off_minuto) + amanecer_anochecer)) && (NumMins(t.hour, t.min) >= NumMins(led_off_hora, led_off_minuto)))
      {
        led_out1 = led_out2 = led_out3 = map(NumMins(t.hour, t.min), (NumMins(led_off_hora, led_off_minuto) + amanecer_anochecer), NumMins(led_off_hora, led_off_minuto), pwm_definido, 0);
      }
      else
      {
        led_out1 = led_out2 = led_out3 = pwm_definido;
      }
    }
    else
    {
      led_out1 = led_out2 = led_out3 = 0;
    }
  }
  else
  {
    if (min_cnt > 1439)
    {
      min_cnt = 0;
    }
    sector = min_cnt / 15 ;       //divide los minutos en sectores de 15 minutos
    sstep = min_cnt % 15;         //el resto agrega el valor a el sectores

    t1 = sector;
    if (t1 == 95)
    {
      t2 = 0;
    }
    else
    {
      t2 = t1 + 1;
    }
    if (sstep == 0)
    {
      led_out1 = led_out2 = led_out3 = (wled[t1]);
    }
    else
    {
      led_out1 = led_out2 = led_out3 = (check(&wled[t1], &wled[t2], sstep));
    }
  }
  myAnalogWrite(ledblanco1, led_out1);
  myAnalogWrite(ledblanco2, led_out2);
  myAnalogWrite(ledblanco3, led_out3);
}

int check (byte *pt1, byte *pt2, int lstep)
{
  int result;
  float fresult;

  if (*pt1 == *pt2)
  {
    result = *pt1;
  }
  else if (*pt1 < *pt2)
  {
    fresult = ((float (*pt2 - *pt1) / 15.0) * float(lstep)) + float(*pt1);
    result = int(fresult);
  }
  else
  {
    fresult = -((float (*pt2 - *pt1) / 15.0) * float(lstep)) + float(*pt1);
    result = int(fresult);
  }
  return result;
}
