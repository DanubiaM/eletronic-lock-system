
//Define the default pins before calling the LCD driver
#ifndef lcd_enable 
   #define lcd_enable     pin_e1
   #define lcd_rs         pin_e2
   //#define lcd_rw       pin_e2  
   #define lcd_d4         pin_d4
   #define lcd_d5         pin_d5
   #define lcd_d6         pin_d6
   #define lcd_d7         pin_d7
#endif

#include "mod_lcd.c"

#include "2401.c"
#include "kbd_board4.c"




// -----------------Functions
void saveUser(int * id, int * pass, int status);
int getAddressByID(int * id);   
int deleteUser(int address);

int isIdAvailable(int id);    
void printUser();
void erase_program_eeprom(int addrr);
int incrementID();
int lastNewUserPosition();
void resetMemory();
void adminMenu();
unsigned char readKeyboard(); 
int * getAdminsID();
void listAdmins();
int * strToInt(char * str);

char * strfromchar(char destination[], char source);