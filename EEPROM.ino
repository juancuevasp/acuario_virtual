//**********************************************************************************************
//************************ Funciones EEPROM ****************************************************
//**********************************************************************************************
struct config_t                         // Temperatura
{
  int tempset;
  byte tempoff;
  byte tempalarm;
}
tempSettings;

void SaveTempToEEPROM()
{
  byte k = 66;
  EEPROM.write(693, k);
  tempSettings.tempset = int(setTempC * 10);
  tempSettings.tempoff = int(offTempC * 10);
  tempSettings.tempalarm = int(alarmTempC * 10);
  EEPROM_writeAnything (482, tempSettings);
}
