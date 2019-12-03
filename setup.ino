void setup()
{
  // Configura la conexión serie
  Serial.begin(38400);

  configpins();     //define las funciones de los pines

  myGLCD.InitLCD();                         //inicia pantalla
  clrscreen();                              //Borra pantalla

  myTouch.InitTouch();                      //inicia touch screen
  myTouch.setPrecision(PREC_MEDIUM);        //define precision de touch screen

  sensors.begin();                          //inicia la lectura de las sondas de temperatura_agua_tempatura
  sensors.setResolution(aquarium_sensor, 10);   //establece la resolucion en 10 bit
  sensors.setResolution(deposit_sensor, 10);    //establece la resolucion en 10 bit

  sensors.requestTemperatures();            //llamada a todos los Sensores
  tempC = (sensors.getTempC(aquarium_sensor));  //lee la tamperatura del agua
  tempD = (sensors.getTempC(deposit_sensor));   //lee la temperatura del deposito

  // coloca el reloj en modo de ejecución
  rtc.halt(false);
  t = rtc.getTime();
  check_water_temp_file();    //corrige registro de temperatura

  select_SD();
  while (!SD.begin(ChipSelect_SD, SPI_QUARTER_SPEED))     //inicia comunicacion con tarjeta SD
  {
    setFont(LARGE, 255, 0, 0, 0, 0, 0);
    myGLCD.print(String("INSERTE UNA TARJETA SD"), CENTER, 115);
  }

  //revisar archivo de temperatura de agua(insertar funcion)

  myGLCD.fillScr(12,6,140);                //Define color de pantalla
  myGLCD.setColor(255,255,255);            //Difine color general
  myGLCD.setBackColor(12,6,140);           //Define color fondo letras
  myGLCD.setFont(RusFont1);                //Define fuente de los textos
  clrscreen();
  draw_screen(true);                       //imprime pantalla inicial


}

void configpins()
{
  myPinMode(ledWhite1, OUTPUT);            //pin 8
  myPinMode(ledWhite2, OUTPUT);            //pin 9
  myPinMode(ledWhite3, OUTPUT);            //pin 10
  myPinMode(heater, OUTPUT);            //pin 42
  myPinMode(ChipSelect_SD, OUTPUT);     //pin 53/*
  myPinMode(aquaLevel, INPUT);                 //pin A4
  myPinMode(depoLevel, INPUT);                 //pin A5
}
