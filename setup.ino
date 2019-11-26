void setup()
{
  // Configura la conexión serie
  Serial.begin(38400);

  configpins();     //define las funciones de los pines

  // Las siguientes líneas se pueden comentar para usar los valores ya almacenados en el DS1307
  //rtc.setDOW(DOMINGO);        // Set Day-of-Week to SUNDAY
  //rtc.setTime(18, 0 , 0);     // Set the time to 12:00:00 (24hr format)
  //rtc.setDate(3, 10, 2010);   // Set the date to October 3th, 2010

  myGLCD.InitLCD();                         //inicia pantalla
  clrscreen();                              //Borra pantalla

  myTouch.InitTouch();                      //inicia touch screen
  myTouch.setPrecision(PREC_MEDIUM);        //define precision de touch screen

  sensors.begin();                          //inicia la lectura de las sondas de temperatura_agua_tempatura
  sensors.setResolution(sensor_agua, 10);   //establece la resolucion en 10 bit

  sensors.requestTemperatures();            //llamada a todos los Sensores
  tempC = (sensors.getTempC(sensor_agua));  //lee la tamperatura del agua

  // coloca el reloj en modo de ejecución
  rtc.halt(false);
  t = rtc.getTime();

  myGLCD.fillScr(12,6,140);                //Define color de pantalla
  myGLCD.setColor(255,255,255);            //Difine color general
  myGLCD.setBackColor(12,6,140);           //Define color fondo letras
  myGLCD.setFont(RusFont1);                //Define fuente de los textos
  clrscreen();
  draw_screen(true);                       //imprime pantalla inicial


}

void configpins()
{
  myPinMode(ledblanco1, OUTPUT);            //pin 8
  myPinMode(ledblanco2, OUTPUT);            //pin 9
  myPinMode(ledblanco3, OUTPUT);            //pin 10
  myPinMode(calefactor, OUTPUT);            //pin 42
  myPinMode(nivel1, INPUT);                 //pin A4
  myPinMode(nivel2, INPUT);                 //pin A5
}
