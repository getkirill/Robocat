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

int pinCS = 9;
int numberOfHorizontalDisplays = 4; // количество матриц по-горизонтали
int numberOfVerticalDisplays = 1; // количество матриц по-вертикали

//Max72xxPanel matrix = Max72xxPanel(pinCS, numberOfHorizontalDisplays, numberOfVerticalDisplays); //инициализация матрицы

void setup(){
  Serial.begin(9600);
  irrecv.enableIRIn();
  pinMode(1, INPUT);
}

void loop(){
  Serial.println("Term: ");
  Serial.print(analogRead(A0) / (6.8));
  Serial.println("Light: ");
  Serial.print(0.512 * (1024 - analogRead(A1)));
  Serial.println("Sound: ");
  Serial.print(analogRead(A2));
  if (irrecv.decode(&results)){
    Serial.println("Button code: ");
    Serial.print(results.value);
  }
  delay(1000);
}

