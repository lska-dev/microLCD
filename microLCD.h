/*
  microLCD.h - Library for LCD 1602 I2C (PCF8574)
  Разработана l$ka. 2026
  Легкая библиотека управления символьным ЖК-дисплеем 1602 с модулем PCF8574T
*/

#ifndef microLCD_h
#define microLCD_h

#include "Arduino.h"
#include "Wire.h"

// Команды LCD
#define LCD_LEDOFF 0x00
#define LCD_LEDON 0x08      
#define LCD_CLEAR 0x01
#define LCD_HOME 0x02
#define LCD_CONTROL 0x08
#define LCD_SHIFT 0x10    
#define LCD_DDRAMSET 0x80
#define LCD_CGRAMSET 0x40
#define LCD_FUNCTSET 0x20

// Режимы для FUNCTSET
#define LCD_8BITMODE  0x10
#define LCD_4BITMODE  0x00
#define LCD_2LINE     0x08
#define LCD_1LINE     0x00
#define LCD_5x10DOTS  0x04
#define LCD_5x8DOTS   0x00

//Управление
#define LCD_DISPLAY_ON 0x04 
#define LCD_CURSOR_ON 0x02
#define LCD_BLINK_ON 0x01
#define LCD_SCREEN 0x08
#define LCD_CURSOR 0x00
#define LCD_LEFT 1
#define LCD_RIGHT 0
#define LCD_ON true
#define LCD_OFF false

// Сигналы для управления
#define LCD_EN 0b00000100
#define LCD_RS 0b00000001

class microLCD {
private:
    uint8_t _adress;
    uint8_t _light;
    bool _display_on;
    bool _cursorState;
    bool _blkCursorState;
    
    inline void I2Csend(uint8_t data);
    inline void sendNibble(uint8_t data, uint8_t rs);
    void control();
    
public:
    // Конструктор
    microLCD(uint8_t addr = 0x27);
    
    // Инициализация
    void begin(uint8_t mode, uint8_t line, uint8_t font);
    
    // Управление
    void backlight(bool mode);
    void display(bool mode);
    void cursor(bool mode);
    void blinkCursor(bool mode);
    
    // Позиционирование
    void home();
    void clear();
    void setCursor(uint8_t col, uint8_t row);
    void shift(uint8_t mode, uint8_t dir);
    
    // Вывод
    void print(const char* str);
    void print(String s);
    void sendCommand(uint8_t cmd);
    void sendData(uint8_t data);
    
    // Специальные символы
    void write(uint8_t c);
    void createChar(uint8_t location, const uint8_t charmap[]);
};
#endif
