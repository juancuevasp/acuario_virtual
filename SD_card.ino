void select_SD()
{
  myDigitalWrite(ChipSelect_SD, LOW);
}

void writeCRLF(SdFile& f)
{
  f.write((uint8_t*) "\r\n", 2);
}

void logtemgraf()     //Escribe datos en la TARJETA SD para generar un gráfico de temperatura.
{
  if (NumMins(t.hour, t.min) == 1)
  {
    EEPROM.write(688, t.date);
  }

  select_SD();
  if (file.open("LOGTEMPDIA.TXT", O_CREAT | O_APPEND | O_WRITE))
  {
    if ((tempC <= 1.0) || (tempC > 99.9))
    {
      file.print("00.00");
      file.write((uint8_t*)"\0", 1);
      writeCRLF(file);
    }
    else
    {
      file.print(tempC);
      file.write((uint8_t*)"\0", 1);
      writeCRLF(file);
    }
    file.close();
  }

  if ((t.hour == 23) && (t.min > 58))
  {
    if(file.open("LOGTEMPDIA.TXT", O_WRITE))
    {
      file.remove();
    }
  }
}

void check_water_temp_file()
{
  int16_t n;
  char buf[8];
  int count = 0;
  byte k = EEPROM.read(688);
  select_SD();

  if (k != t.date)
  {
    if (file.open("LOGTEMPDIA.TXT", O_WRITE))
    {
      file.remove();
    }
  }

  if (file.open("LOGTEMPDIA.txt", O_CREAT | O_READ | O_APPEND | O_WRITE))
  {
    while((n = file.read(buf, sizeof(buf))) > 0)
    {
      if (strlen(buf) == 5)
      {
        count++;
      }
    }
    if (count < NumMins(t.hour, t.min))
    {
      for (int i = count; i < NumMins(t.hour, t.min) - 1; i++)
      {
        file.print("00.00");
        file.write((uint8_t*)"\0", 1);
        writeCRLF(file);
      }
    }
    file.close();
  }
}
