
#include <16F877A.h>
#device ADC=8

#FUSES NOWDT                    //No Watch Dog Timer
#FUSES NOBROWNOUT               //No brownout reset
#FUSES NOLVP                    //No low voltage prgming, B3(PIC16) or B5(PIC18) used for I/O
#FUSES HS 

#use delay(crystal=20000000)
//#use rs232(baud=9600,parity=N,xmit=PIN_C6,rcv=PIN_C7,bits=8,stream=PORT1)

// -------Variables' Declaration
signed int8 address_data_delete;

typedef struct { 
   int id[2];
   int pass[4]; //password
   int status; //0 - Unpaid, 1 - Paid, 3 - Admin
}User;

#define RX_BUFFER_SIZE 10
#define BLOCK_SIZE sizeof(User) 
int8 rx_wr_index = 0;
int8 lock_pos = 0, rxd, read, valid_data_count;
unsigned int8 rx_buffer[RX_BUFFER_SIZE];
int data_avail = FALSE, got_id = FALSE;

// -------


// -----------------Functions
void saveUser(int * id, int * pass, int status);
void printUser();
int getAddressByID(int id);    
int isIdAvailable(int id);    
int deleteUser(int address);
void erase_program_eeprom(int addrr);
int incrementID();
int lastNewUserPosition();
void resetMemory();
void adminMenu();
unsigned char readKeyboard(); 
int * getAdminsID();
void listAdmins();
// ----------------
/*
// ---- MSG from serial communication
#int_RDA
void RDA_isr(void){
   rx_buffer[rx_wr_index] = getc();
   rxd = rx_buffer[rx_wr_index];
   rx_wr_index++;

   if(rx_wr_index > RX_BUFFER_SIZE){
      rx_wr_index = 0;
   }

   //Look for unique ID: "IFMT"
   if(rxd == 'I' && lock_pos == 0){
      lock_pos++;
   }
   else if(rxd == 'F' && lock_pos == 1){
      lock_pos++;
   }
   else if(rxd == 'M' && lock_pos == 2){
      lock_pos++;
   }
   else if(rxd == 'T' && lock_pos == 3){
      lock_pos=0; //Reset the "combination lock"
      got_id = TRUE;
      read = rxd;
      //get ready to count the number of data bytes
      valid_data_count = 0xff; 

      //buffer is reset to index 0
      rx_wr_index = 0;
   }else {
      lock_pos = 0;
   }

   if(got_id && ++valid_data_count >= 6){
      data_avail = TRUE;
      got_id = FALSE;
   }
   
}
*/

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


#int_TIMER1
void TIMER1_isr(void)
{
   // readKeyboard();
}

#int_RTCC
void RTCC_isr(void)
{


   
      
}

void main()
{
   //VARIAVEIS
   byte result;
   unsigned char tmp;
   unsigned char tmp_result;
   
   eeprom_address address = 0;

   // unsigned char tmp_result;
   setup_timer_0(RTCC_INTERNAL|RTCC_DIV_256|RTCC_8_bit);      //13.1ms overflow
   setup_timer_1(T1_INTERNAL|T1_DIV_BY_8); //Overflow in 104ms | Resolution 1.6 us

   init_ext_eeprom();

   // enable_interrupts(INT_TIMER0);
   // enable_interrupts(INT_TIMER1);

   // enable_interrupts(GLOBAL);


   lcd_ini();
   delay_us(50);
   printf(lcd_escreve, "\f  iniciando... ");
   delay_ms(500);

   printf(lcd_escreve, "\fIFMT - Serial");
   delay_ms(50);

   int size = BLOCK_SIZE;
   printf(lcd_escreve, "\fBlock_Size:%u", size);
   delay_ms(500);

   // resetMemory();
   
   // data_avail = FALSE;
   // int pass [4] = {1,2,3,4};
   // int id [2] = {12,12};
   // saveUser(id, pass, 1);
   // int id1 [2] = {14,0};
   // saveUser(id1, pass, 0);
   // int id2 [2] = {5,5};
   // saveUser(id2, pass, 1);
   // int id3 [2] = {70,00};
   // saveUser(id3, pass, 1);
   // int id4 [2] = {254,254};
   // saveUser(id4, pass, 3);//admin

   int * admins;

   admins = getAdminID();
   for (int16 i=0; i < sizeof(admins); i+=2){
      printf(lcd_escreve, "\fid:%u%u",admins[i], admins[i+1]);
      delay_ms(1000);
   } 
   
   
   // isIdAvailable(254);
   // isIdAvailable(200);

 
  // address_data_delete = getAddressByID(6);
  // printf(lcd_escreve, "\f Address ID = %d", address_data_delete);
 //  deleteBlock(address_data_delete);
   delay_ms(50);
   // printUser();
   delay_ms(1000);
   
   while(TRUE)
   {
   
   }

}
/*
int incrementID(){
   int greatest_id = 0 ,address = 0;   
   
   erase_program_eeprom(0); 
   int id_temp = read_ext_eeprom(address);   

   while( id_temp  != -1){
      
      if(id_temp > greatest_id ){
         greatest_id = id_temp;
      }     
     
      address += BLOCK_SIZE;
      id_temp = read_ext_eeprom(address);
      
   }
  
   
   return ++greatest_id;
    
}
*/
void saveUser(int * id, int * pass, int status){

   if( id[0] < 256 && id[1] < 256 && getAddressByID(id) > -1 ){
      int address = lastNewUserPosition();
      //recebe os parâmetros do usuário
      User user;
      user.id[0] = id[0];
      user.id[1] = id[1];
      user.pass[0] = pass[0];
      user.pass[1] = pass[1];
      user.pass[2] = pass[2];
      user.pass[3] = pass[3];
      user.status = status;
      

      //Corrigir isso, o endereço tem que ser "dinâmico"
      
      write_ext_eeprom(address, user.id[0]);
      write_ext_eeprom(address+1, user.id[1]);
      write_ext_eeprom(address+2, user.pass[0]);
      write_ext_eeprom(address+3, user.pass[1]);
      write_ext_eeprom(address+4, user.pass[2]);
      write_ext_eeprom(address+5, user.pass[3]);       
      write_ext_eeprom(address+6, user.status);
   

      printf (lcd_escreve,"\fUsuario Cadastrado");
      delay_ms(500);

   }else{
      printf (lcd_escreve,"\fID incompativel");
      printf (lcd_escreve,"\r\nTente novamente");
      delay_ms(1000);

   }
}

void printUser(){
   //delay_ms(50);
   int tmp_result = read_ext_eeprom(0);  
   
   delay_ms(50);  
   
   printf (lcd_escreve,"\f Button: %d", tmp_result);
   printf(lcd_escreve, "\r\nPw:%d%d%d%d St:%d %d", read_ext_eeprom(1), read_ext_eeprom(2), read_ext_eeprom(3), read_ext_eeprom(4), read_ext_eeprom(5), read_ext_eeprom(6));
   
   //printf(lcd_escreve, "\f Client () else´{}{}
   // printf(lcd_escreve, "\r\nPw:%c%c%c%c St:%c %c", U1.pass[0], U1.pass[1], U1.pass[2], U1.pass[3], U1.status, U1.type_usr);
}

int getAddressByID(int * id){
   int id_temp[2];
   int address = 0;
   
   while( read_ext_eeprom(address) != -1){
      id_temp[0] = read_ext_eeprom(address);
      id_temp[1] = read_ext_eeprom(address+1);
      
      if (id_temp[0] == id[0] && id_temp[1] == id[1]){
         printf (lcd_escreve,"\fID Encontrado:%u%u", id_temp[0],id_temp[1]);
         delay_ms(1000);
         return address;
      }

      address += BLOCK_SIZE; 
   }
   printf (lcd_escreve,"\f ID N Encontrado");
   return -1;
   
}

void erase_program_eeprom(int addrr){
   for(int i=0; i < BLOCK_SIZE; i++){
         write_ext_eeprom(addrr + i, -1);
   }  
   printf (lcd_escreve,"\f User erased ");
   delay_ms(500);
}

int deleteUser(int8 address){
   
   int data_temp;
   int previous_block = address;
   int next_block = address + BLOCK_SIZE;

   //Case 1: without next block
   if (read_ext_eeprom(next_block) == -1){
      erase_program_eeprom(previous_block);      
      return 1;
   }

   //Case 2: Check whether the data in the address is empty
   while(read_ext_eeprom(next_block) != -1){
      //data_temp[index] = read_ext_eeprom(address);
      for(int i=0; i < BLOCK_SIZE; i++){
         data_temp = read_ext_eeprom(next_block + i);           
         write_ext_eeprom(previous_block + i, data_temp);    //overwrite delete block
      }  

      previous_block = next_block;
      next_block += BLOCK_SIZE;
   }
   
   next_block -= BLOCK_SIZE;
   
   //Erase last block  
   erase_program_eeprom(next_block);
   
   return 1;

}

int lastNewUserPosition(){
   int address = 0;
   int id_temp;

   while( read_ext_eeprom(address) != -1){
      address += BLOCK_SIZE; 
   }
   printf (lcd_escreve,"\fAddress: %d", address);
   delay_ms(1000);
   
   return address;

}

int isIdAvailable(int id){
   unsigned int address = 0;
   int id_temp;
   while( read_ext_eeprom(address) != -1){
      id_temp = read_ext_eeprom(address);
      if (id_temp == id){
          printf (lcd_escreve,"\fID:%u, Existe", id_temp);
          delay_ms(1000);
         return 0;//Sucessful
      }

      address += BLOCK_SIZE; 
   }
   printf (lcd_escreve,"\fID:%u, N Existe", id_temp);
   delay_ms(1000);
   return -1;
}

void resetMemory(){
   int address = 0;
   for(; read_ext_eeprom(address) != -1;
    erase_program_eeprom(address), address += BLOCK_SIZE);
}

// void adminMenu(){

//    option = readKeyboard();

//    switch (option)
//    {
//    case 1:
//       /* code */
//       break;
   
//    default:
//       break;
//    }
   

   
// }

unsigned char readKeyboard(){
   unsigned char tmp;
   unsigned char tmp_result;

   tmp = tc_tecla(1500); // ms
   if(tmp != 255){
      write_ext_eeprom(0, tmp);
      delay_ms(50);
      tmp_result = read_ext_eeprom(0);
      delay_ms(50);
      // tmp_result = tmp;
      printf(lcd_escreve,"\f Button: %c", tmp_result);
   }else{ 
      printf(lcd_escreve,"\f   TECLADO  ");
   }
   return tmp;
}


int * getAdminsID(){

   int address = 0;
   int temp_status;
   int index= 0;
   static int admins[BLOCK_SIZE];
   admins[0] = -1;
   while( read_ext_eeprom(address) != -1){
      temp_status = read_ext_eeprom(address + (BLOCK_SIZE - 1));//status of the user
      if (temp_status == 3){
         printf (lcd_escreve,"\fAdmin Encontrado");
         delay_ms(1000);
         for(int i=0; i < 2; i++){
            int id = read_ext_eeprom(address+i);   
            admins[index] = id;
            index++;
         }

      }

      address += BLOCK_SIZE; 
   }

   return admins;

}

void listAdmins(){
   int * admins;

   admins = getAdminID();
   if(admins[0] > -1){
      for (int16 i=0; i < sizeof(admins); i+=2){
         printf(lcd_escreve, "\fid:%u%u",admins[i], admins[i+1]);
         delay_ms(1000);
      } 
   }
}