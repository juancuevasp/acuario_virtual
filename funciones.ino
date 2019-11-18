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

void myPinMode(int pin, boolean mode)
{
  if ((pin >= 0) && (pin <= MAX_PIN_NUMBER))
  {
    pinMode(pin, mode);
  }
}

void drawFillRect(int x1, byte y1, int x2, byte y2, byte r, byte g, byte b)
{
  myGLCD.setColor(r, g, b);
  myGLCD.fillRect(x1, y1, x2, y2);
}
