
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




/*
int status -> 0 - Unpaid, 1 - Paid, 3 - Admin
int chooseAddr:
         Param < 0 - SAVE in a available address to CREATE 
         Param >= 0 - SAVE in a existing address to OVERWRITE (edit)
*/
void saveUser(int * id, int * pass, int status);
int getAddressByID(int * id);   
void searchUser(int * id);
int deleteUser(int * id);
void editUser();
void updateUser(int * id, int * pass, int status);

// int isIdAvailable(int id);    
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
int * inputId();
int * inputToKeyboard(char * msg, int max);
void inputKeyboardUser();