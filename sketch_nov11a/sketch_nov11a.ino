#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Max72xxPanel.h>

int pinCS = 9;
int numberOfHorizontalDisplays = 4; // теперь у нас по-горизонтали 6 матриц
int numberOfVerticalDisplays = 1; // а по-вертикали, по-прежнему, одна

Max72xxPanel matrix = Max72xxPanel(pinCS, numberOfHorizontalDisplays, numberOfVerticalDisplays);

String tape = "Aa Bb Cc D E F G H I J K L M O P Q R S T U V W X Y Z"; // текст, который будет плыть
int wait = 50; // время между крайними перемещениями букв

int spacer = 1; // расстояние между буквами
int width = 5 + spacer; // размер шрифта

void setup() {
    matrix.setIntensity(7); // яркость
    /*matrix.setPosition(0, 0, 1);
    matrix.setPosition(1, 0, 8);
    matrix.setPosition(2, 0, 16);
    matrix.setPosition(3, 0, 32);*/
    matrix.setRotation(3, 1);
    matrix.setRotation(2, 1);
    matrix.setRotation(1, 1);
    matrix.setRotation(0, 1);
    //matrix.setRotation(matrix.getRotation() + 1 );
}

void loop() {
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
