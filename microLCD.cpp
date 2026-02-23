/* 
microLCD i2c for lcd1602 on PCF8574T 
Легкая библиотека управления Символьным ЖК-дисплеем 1602 с модулем
PCF8574T.
разработана l$ka. 2026
*/

#include "microLCD.h"

// Конструктор
microLCD::microLCD(uint8_t addr) {
    _adress = addr;
    _light = LCD_LEDON;
    _display_on = true;
    _cursorState = false;
    _blkCursorState = false;
}

//отправить байт по I2C 
void microLCD::I2Csend(uint8_t data){
  Wire.beginTransmission(_adress);
  Wire.write(data | _light);  
  Wire.endTransmission();
}
//отправить полубайт
void microLCD::sendNibble(uint8_t data, uint8_t rs_value){
  //datasheet page 7 "Timing diagram"
  uint8_t nubble = data << 4; 
  //EN high
  I2Csend(nubble | rs_value | LCD_EN);
  delayMicroseconds(1);
  //EN low
  I2Csend(nubble | rs_value);
  delayMicroseconds(50);
}
//Отправить комманду RS = 0
void microLCD::sendCommand(uint8_t cmd){
  sendNibble(cmd >> 4,0);
  sendNibble(cmd & 0x0f,0);
  delay(2);
}
//отправить данные RS = 1
void microLCD::sendData(uint8_t data){
  sendNibble(data >> 4,LCD_RS);
  sendNibble(data & 0x0f,LCD_RS);
  delay(2);
}
//
//Команда Control
void microLCD::control(){
  uint8_t dsp = (_display_on? LCD_DISPLAY_ON : 0);
  uint8_t crs = (_cursorState? LCD_CURSOR_ON : 0);
  uint8_t blk = (_blkCursorState? LCD_BLINK_ON : 0);
  sendCommand(LCD_CONTROL | dsp | crs | blk);
}
//инициализация(i2c Инициализировать отдельно)
void microLCD::begin(uint8_t mode, uint8_t line, uint8_t font){
  delay(50);  //Не трогать
  /*
  Последовательность инициализации 
  datasheet page 14 "[4 - B it Interface]"
  */

  sendNibble(0x03, 0);  //Function set(Interface is 8 bits length.)
  delayMicroseconds(4500);

  sendNibble(0x03, 0);  //Function set(Interface is 8 bits length.)
  delayMicroseconds(150);

  sendNibble(0x03, 0);  //Function set(Interface is 8 bits length.)
  delayMicroseconds(150);

  sendNibble(0x02, 0);  //Перейти в 4-х битный режим
  delay(5);

  uint8_t function = LCD_FUNCTSET | mode | line | font;
  sendCommand(function);

  //Подготовка дисплея для пользователя
  sendCommand(LCD_CONTROL | 0x04);  
  sendCommand(LCD_CLEAR);   //clear
    
  delay(2);
  sendCommand(0x06);//авто сдвиг курсора
}
//Высокоуровневые операции
//Включение/Выключение подсветки {mode}
void microLCD::backlight(bool mode){
  _light = (mode ? LCD_LEDON : LCD_LEDOFF);
  I2Csend(0);//обновить подсветку
}
//Переместить курсор в (0:0)
void microLCD::home(){
  sendCommand(LCD_HOME);
}
//Очистить экран
void microLCD::clear(){
  sendCommand(LCD_CLEAR);
}
//Поместить курсор в (row,col)
void microLCD::setCursor(uint8_t col, uint8_t row){
  const uint8_t rows[] = {0x0, 0x40}; //Адреса строк 
  if (row > 1) row = 1;
  if (col > 15) col = 15;
  sendCommand(LCD_DDRAMSET | (rows[row] + col));
}
/*
Сдвинуть экран(mode = SCREEN) или курсор (mode = CURSOR)
на одно знако-место в направлении der(LEFT,RIGHT) 
*/
void microLCD::shift(uint8_t mode, uint8_t der){
  sendCommand(LCD_SHIFT | mode | der);
}
//Вывести строку от позиции курсора к правому краю
void microLCD::print(const char* str) {
  while (*str) {
    sendData(*str++);
  }
}
void microLCD::print(String s) {
    for (unsigned int i = 0; i < s.length(); i++) {
        sendData(s[i]);
    }
}
//Вставить символ на позицию курсора
void microLCD::write(uint8_t index){
  sendData(index);
}
/*
Создание пользовательского символа с индексом {location}
конвертер-https://maxpromer.github.io/LCD-Character-Creator 
*/
void microLCD::createChar(uint8_t location, const uint8_t charmap[]) {
  if (location > 7) return;  // защита от дурака
    
  sendCommand(LCD_CGRAMSET | (location << 3));
  for (uint8_t i = 0; i < 8; i++) {
      sendData(charmap[i]);
  }
  setCursor(0, 0);  // возврат в DDRAM
}
//Видимость курсора
void microLCD::cursor(bool mode){
  _cursorState = mode;
  control();
}
//Видимость мигающего курсора
void microLCD::blinkCursor(bool mode){
  _blkCursorState = mode;
  control();
}
//Включение/Выключение дисплея
void microLCD::display(bool mode){
  _display_on = mode;
  control();
}

