#include <microLCD.h>
/*
#################################################################
Все функции библиотеки для LCD1602 c I2C
#################################################################

Ппдключение:
I2C: SDA ---> A4
I2C: SCL ---> A5

адрес устройства (используйте i2c scaner для определения):*/
const uint8_t adress = 0x27;

//Кастомный символ смайлика
const byte smile[] = {
    B00000, // . . . . .
    B01010, // . # . # .
    B01010, // . # . # .
    B01010, // . # . # .
    B00000, // . . . . .
    B10001, // # . . . #
    B01110, // . # # # .
    B00000  // . . . . .
};

microLCD lcd(adress);  //Создаем объект для дисплея

void setup() {
    //Инициализация дисплея
    lcd.begin(LCD_4BITMODE, LCD_2LINE, LCD_5x8DOTS);
    
    //Создаем пользовательский символ
    lcd.createChar(0, smile);
    
    //Включаем подсветку
    lcd.backlight(LCD_ON);
    lcd.clear();
    
    //Приветственное сообщение
    lcd.setCursor(0, 0);       //курсор на (0, 0)
    lcd.print("hello from:");  //Вывод текста
    lcd.setCursor(0, 1);
    lcd.print("microLCD");
    lcd.write(0);              //Выводим смайлик
    
    delay(1000);
    
    //Демонстрация управления курсором
    lcd.blinkCursor(LCD_ON);          //Включаем мигаюший курсор
    delay(1000);              
    lcd.blinkCursor(LCD_OFF);         //Выключаем мигаюший курсор
    lcd.cursor(LCD_ON);               //Включаем курсор
    delay(1000);
    
    //Демонстрация сдвигов
    lcd.shift(LCD_CURSOR, LCD_RIGHT); //Сдвиг курсора вправо
    delay(1000);
    lcd.shift(LCD_CURSOR, LCD_LEFT);  //Сдвиг курсора влево
    delay(1000);
    lcd.shift(LCD_SCREEN, LCD_RIGHT); //Сдвиг экрана вправо
    delay(1000);
    lcd.shift(LCD_SCREEN, LCD_LEFT);  //Сдвиг экрана влево
    delay(1000);
    
    //Мигание подсветкой
    lcd.backlight(LCD_OFF);           //Выключить подсветку
    delay(1000);
    lcd.backlight(LCD_ON);            //Включить подсветку
    
    //Финальные настройки
    lcd.cursor(LCD_OFF);
    lcd.clear();
}

void loop() {
    lcd.home();  // курсор в начало
    lcd.print("Timer 1:");           //Вывод 1 строки
    
    lcd.setCursor(0, 1);
    lcd.print(String(millis()) + " mS");//Вывод 2 сроки
    
    delay(100);  // обновление 10 раз в секунду
}