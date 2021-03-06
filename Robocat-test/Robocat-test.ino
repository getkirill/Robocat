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

void setup(){
  matrix.setRotation(3, 1);
  matrix.setRotation(2, 1);
  matrix.setRotation(1, 1);
  matrix.setRotation(0, 1);
  Serial.begin(9600);
  irrecv.enableIRIn();
  pinMode(1, INPUT);
  matrix.setIntensity(7); // яркость
}

void changeTextOfMatrix(String tape){
    for ( int i = 0 ; i < width * tape.length() + matrix.width() - 1 - spacer; i++ ) {
        matrix.fillScreen(LOW);

        int letter = i / width;
        int x = (matrix.width() - 1) - i % width;
        int y = (matrix.height() - 8) / 2; // center the text vertically

        while ( x + width - spacer >= 0 && letter >= 0 ) {
            if ( letter < tape.length() ) {
                matrix.drawChar(x, y, tape[letter], HIGH, LOW, 1);
            }
            letter--;
            x -= width;
        }

        matrix.write();
        delay(wait);
    }
}

void loop(){
  float temperature = analogRead(A0) / (6.8);
  Serial.println("\nTerm: ");
  Serial.print(temperature);
  changeTextOfMatrix("Term: " + String(temperature));
  float light = 0.512 * (1024 - analogRead(A1));
  Serial.println("\nLight: ");
  Serial.print(light);
  changeTextOfMatrix("Light: " + String(light));
  float sound = analogRead(A2);
  Serial.println("\nSound: ");
  Serial.print(sound);
  changeTextOfMatrix("Sound: " + String(sound));
  
  if (irrecv.decode(&results))
  {
    Serial.println("\nButton code: ");
    Serial.print(results.value);
  }
  delay(1000);
}

