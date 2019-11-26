int NumMins(uint8_t ScheduleHour, uint8_t ScheduleMinute)
{
  return (ScheduleHour * 60) + ScheduleMinute;
}

void myDigitalWrite(int pin, boolean level)
{
  if ((pin >= 0) && (pin <= MAX_PIN_NUMBER))
  {
    digitalWrite(pin, level);
  }
}

void myAnalogWrite(int pin, byte pwm)
{
  if ((pin >= 0) && (pin <= MAX_PIN_NUMBER))
  {
    analogWrite(pin, pwm);
  }
}

int myAnalogRead(int pin)
{
  int value = 6666;

  if ((pin >= 0) && (pin <= MAX_PIN_NUMBER))
  {
    value = analogRead(pin);
  }
  return value;
}

void myPinMode(int pin, boolean mode)
{
  if ((pin >= 0) && (pin <= MAX_PIN_NUMBER))
  {
    pinMode(pin, mode);
  }
}
