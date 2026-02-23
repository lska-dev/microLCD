#include <microLCD.h>
/*
#################################################################
Все функции библиотеки для LCD1602 c I2C
#################################################################

Ппдключение:
I2C 1: SDA ---> A4
I2C 1: SCL ---> A5
I2C 2: SDA ---> A4
I2C 2: SCL ---> A5

адресa устройств (используйте i2c scaner для определения):*/
const uint8_t adress1 = 0x27;
const uint8_t adress2 = 0x17;


microLCD lcd1(adress1);  //Создаем объект для 1 дисплея
microLCD lcd2(adress2);  //Создаем объект для 2 дисплея

void setup() {
    //Инициализация дисплея
    lcd1.begin(LCD_4BITMODE, LCD_2LINE, LCD_5x8DOTS); //Инициализировать 1
    lcd2.begin(LCD_4BITMODE, LCD_2LINE, LCD_5x8DOTS); //Инициализировать 2
 
    lcd1.clear(); //Очистить 1
    lcd2.clear(); //Очистить 2

    lcd1.home();  //Домой 1
    lcd2.home();  //Домой 2
    //Выводим имена
    lcd1.print("Display 1");
    lcd2.print("Display 2");


    
}

void loop() {
    
}