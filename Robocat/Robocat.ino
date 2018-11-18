#include <Adafruit_GFX.h>
#include <Adafruit_SPITFT.h>
#include <Adafruit_SPITFT_Macros.h>
#include <gfxfont.h>

#include <Max72xxPanel.h>

#include <SPI.h>

#include <boarddefs.h>
#include <IRremote.h>
#include <IRremoteInt.h>
#include <ir_Lego_PF_BitStreamEncoder.h>

IRrecv irrecv(0);
decode_results results;

int satiety = 100;
int health = 100;
int mood = 100;
int timer = 0;

float temperature;
float light;
int sound;

int pinCS = 9;
int numberOfHorizontalDisplays = 4; // количество матриц по-горизонтали
int numberOfVerticalDisplays = 1; // количество матриц по-вертикали

Max72xxPanel matrix = Max72xxPanel(pinCS, numberOfHorizontalDisplays, numberOfVerticalDisplays); //инициализация матрицы

int spacer = 1; // расстояние между буквами
int width = 5 + spacer; // размер шрифта

//String tape = "TEST"; //тест дисплея
int wait = 50; // время между крайними перемещениями букв
//byte smile[8] = {
//    0x01111110,
//    0x10000001,
//    0x10100101,
//    0x10000001,
//    0x10100101,
//    0x10011001,
//    0x10000001,
//    0x01111110
//};
//byte coldy[8] = {
//    0x01111110,
//    0x10100101,
//    0x10011001,
//    0x10100101,
//    0x10000001,
//    0x10111101,
//    0x10000001,
//    0x01111110
//};
//byte hot[8] = {
//    0x01111110,
//    0x10000001,
//    0x10100101,
//    0x10000001,
//    0x10111101,
//    0x10011001,
//    0x10000001,
//    0x01111110
//};
//byte loud[8] = {
//    0x01111110,
//    0x10000001,
//    0x10100101,
//    0x10000001,
//    0x10011001,
//    0x10100101,
//    0x10000001,
//    0x01111110
//};
//byte sleep[8] = {
//    0x01111110,
//    0x10000001,
//    0x10111101,
//    0x10000001,
//    0x10100101,
//    0x10011001,
//    0x10000001,
//    0x01111110
//};
void info(float a, int b, int c);
void pet();
void feed();
void tablet();
void bath();
void cookie();
void punishment();
void Sansukumi_ken();
void emotion(float one, int two, int three, int four, int five, int six);
void proc();
void Text(String tape){
    for ( int i = 0 ; i < width * tape.length() + matrix.width() - 1 - spacer; i++ ) {
        matrix.fillScreen(LOW);

        int letter = i / width;
        int x = (matrix.width() - 1) - i % width;
        int y = (matrix.height() - 8) / 2; // center the text vertically

        while ( x + width - spacer >= 0 && letter >= 0 ) {
            if ( letter < tape.length() ) {
                matrix.drawChar(x, y, tape[letter], HIGH, LOW, 1);
            };
            letter--;
            x -= width;
        };

        matrix.write();
        delay(wait);
    };
};
//void DrawMatrix(byte data[8]){
//  matrix.fillScreen(LOW); // очистка матрицы
//  for ( int y = 0; y < 8; y++ ) {
//      for ( int x = 0; x < 8; x++ ) {
//          matrix.drawPixel(x, y, data[y] & (1<<x));  // зажигаем x-й пиксель в y-й строке
//      };
//  };
//  matrix.write(); // вывод всех пикселей на матрицу
//};
void setup(){
  matrix.setRotation(3, 1);
  matrix.setRotation(2, 1);
  matrix.setRotation(1, 1);
  matrix.setRotation(0, 1);
  Serial.begin(9600);
  irrecv.enableIRIn();
  pinMode(1, INPUT);
  matrix.setIntensity(7); // яркость
  randomSeed(100);
  Text("Robocat/TOMODACHI 1.0");
  Text("By Kirill");
};



void loop(){
//  Text(":)");
//  DrawMatrix(smile);
//  delay(1000);
//  DrawMatrix(coldy);
//  delay(1000);
//  DrawMatrix(hot);
//  delay(1000);
//  DrawMatrix(loud);
//  delay(1000);
//  DrawMatrix(sleep);
//  delay(1000);
  temperature = analogRead(A0);
  temperature /= (6.8);
  light = analogRead(A1);
  light = 0.512 * (1024-light);
  sound = analogRead(A2);
  if (irrecv.decode(&results)){
    Serial.print("CODE OF BTN ");
    Serial.println(results.value, HEX);
    if (results.value == 0xD7E84B1B){
      info(temperature, light, sound);
    };
    if (results.value == 0x511DBB){
      feed();
    };
    if(results.value == 0xA3C8EDDB){
      Sansukumi_ken();
    };
    if(results.value == 0x52A3D41F){
      tablet();
    };
    if(results.value == 0x20FE4DBB){
      bath();
    };
    if(results.value == 0xC101E57B){
      cookie();
    };
    if(results.value == 0x97483BFB){
      punishment();
    };
    if(results.value == 0xF0C41643){
      pet();
    };
    irrecv.resume();
  };
  timer = int(millis() / 1000);
  
  if (timer % 10 == 0){
    satiety -= 1;
    health -= 1;
    mood -= 1;
    if (satiety <= 0) health -= 5;
    if (mood <= 0) health -= 2;
  };
  emotion(temperature, light, sound, health, satiety, mood);
};

