//#include <40_save_client.h>
#include <16F877A.h>
#device ADC=8

#FUSES NOWDT                    //No Watch Dog Timer
#FUSES NOBROWNOUT               //No brownout reset
#FUSES NOLVP                    //No low voltage prgming, B3(PIC16) or B5(PIC18) used for I/O
#FUSES HS 

#use delay(crystal=20000000)
//#use rs232(baud=9600,parity=N,xmit=PIN_C6,rcv=PIN_C7,bits=8,stream=PORT1)

// -------Variables' Declaration
unsigned char tmp;
unsigned char tmp_result;
signed int8 address_data_delete;

typedef struct { //7Bytes
   int id;
   int pass[4]; //password
   int status;
   int type_usr;
}User;

#define RX_BUFFER_SIZE 10
#define BLOCK_SIZE 7
int8 rx_wr_index = 0;
int8 lock_pos = 0, rxd, read, valid_data_count;
unsigned int8 rx_buffer[RX_BUFFER_SIZE];
int data_avail = FALSE, got_id = FALSE;

User U1;
User U2;
// -------


// -----------------Functions
void saveUser();
void printUser();
int getAddressByID(int id);    
int deleteBlock(int address);
void erase_program_eeprom(int addrr);
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

    // //-------------------------------------------
    // tmp = tc_tecla(1000); // ms
    // //-------------------------------------------
    // if(tmp!=255){
     
    //    write_ext_eeprom(0, tmp);
    //    delay_ms(50);
    //    tmp_result = read_ext_eeprom(0);
    //    delay_ms(50);
    //    // tmp_result = tmp;
    //    printf (lcd_escreve,"\f Button: %c", tmp_result);

    //   }else{ 

    //    printf (lcd_escreve,"\f   TECLADO  ");
    //  }

}

#int_RTCC
void RTCC_isr(void)
{


   
      
}

void main()
{
   //VARIAVEIS
   byte result;
   
   eeprom_address address;

   // unsigned char tmp_result;
   setup_timer_0(RTCC_INTERNAL|RTCC_DIV_256|RTCC_8_bit);      //13.1ms overflow
   setup_timer_1(T1_INTERNAL|T1_DIV_BY_8); //Overflow in 104ms | Resolution 1.6 us

   // init_ext_eeprom();

   // enable_interrupts(INT_TIMER0);
   // enable_interrupts(INT_TIMER1);

   // enable_interrupts(GLOBAL);


   lcd_ini();
   delay_us(50);
   printf(lcd_escreve, "\f  iniciando... ");
   delay_ms(1000);

   printf(lcd_escreve, "\fIFMT - Serial");

   
  
   delay_ms(50);
   // if(data_avail){
   output_high(PIN_D3);
   data_avail = FALSE;
   saveUser();
   address_data_delete = getAddressByID(6);
   printf(lcd_escreve, "\f Address ID = %d", address_data_delete);
   deleteBlock(address_data_delete);
   delay_ms(50);
   // printUser();
   delay_ms(1000);
   
   while(TRUE)
   {
   
   }

}



void saveUser(){
   rx_buffer[0] = 5;
   rx_buffer[1] = 6;
   rx_buffer[2] = 6;
   rx_buffer[3] = 7;
   rx_buffer[4] = 7;
   rx_buffer[5] = 1;
   rx_buffer[6] = 1;

   U1.id = rx_buffer[0];
   U1.pass[0] = rx_buffer[1];
   U1.pass[1] = rx_buffer[2];
   U1.pass[2] = rx_buffer[3];
   U1.pass[3] = rx_buffer[4];
   u1.status = rx_buffer[5];
   u1.type_usr = rx_buffer[6];    
   

   write_ext_eeprom(0, U1.id);
   write_ext_eeprom(1, U1.pass[0]);
   write_ext_eeprom(2, U1.pass[1]);
   write_ext_eeprom(3, U1.pass[2]);
   write_ext_eeprom(4, U1.pass[3]);       
   write_ext_eeprom(5, U1.status);
   write_ext_eeprom(6, U1.type_usr);

 //-------------
   rx_buffer[0] = 6;
   rx_buffer[1] = 1;
   rx_buffer[2] = 2;
   rx_buffer[3] = 3;
   rx_buffer[4] = 4;
   rx_buffer[5] = 1;
   rx_buffer[6] = 1;

   U1.id = rx_buffer[0];
   U1.pass[0] = rx_buffer[1];
   U1.pass[1] = rx_buffer[2];
   U1.pass[2] = rx_buffer[3];
   U1.pass[3] = rx_buffer[4];
   u1.status = rx_buffer[5];
   u1.type_usr = rx_buffer[6];    
   

   write_ext_eeprom(7, U1.id);
   write_ext_eeprom(8, U1.pass[0]);
   write_ext_eeprom(9, U1.pass[1]);
   write_ext_eeprom(10, U1.pass[2]);
   write_ext_eeprom(11, U1.pass[3]);       
   write_ext_eeprom(12, U1.status);
   write_ext_eeprom(13, U1.type_usr);
 
//----------
   rx_buffer[0] = 7;
   rx_buffer[1] = 6;
   rx_buffer[2] = 5;
   rx_buffer[3] = 4;
   rx_buffer[4] = 3;
   rx_buffer[5] = 2;
   rx_buffer[6] = 1;

   U1.id = rx_buffer[0];
   U1.pass[0] = rx_buffer[1];
   U1.pass[1] = rx_buffer[2];
   U1.pass[2] = rx_buffer[3];
   U1.pass[3] = rx_buffer[4];
   u1.status = rx_buffer[5];
   u1.type_usr = rx_buffer[6];    
   

   write_ext_eeprom(14, U1.id);
   write_ext_eeprom(15, U1.pass[0]);
   write_ext_eeprom(16, U1.pass[1]);
   write_ext_eeprom(17, U1.pass[2]);
   write_ext_eeprom(18, U1.pass[3]);       
   write_ext_eeprom(19, U1.status);
   write_ext_eeprom(20, U1.type_usr);
   
  
}

void printUser(){
   //delay_ms(50);
   tmp_result = read_ext_eeprom(0);  
   
   delay_ms(50);  
   
   printf (lcd_escreve,"\f Button: %d", tmp_result);
   printf(lcd_escreve, "\r\nPw:%d%d%d%d St:%d %d", read_ext_eeprom(1), read_ext_eeprom(2), read_ext_eeprom(3), read_ext_eeprom(4), read_ext_eeprom(5), read_ext_eeprom(6));
   
   //printf(lcd_escreve, "\f Client ID = %d", U1.id);
  // printf(lcd_escreve, "\r\nPw:%c%c%c%c St:%c %c", U1.pass[0], U1.pass[1], U1.pass[2], U1.pass[3], U1.status, U1.type_usr);
}

int getAddressByID(int id){
   int id_temp;
   int address = 0;
   
   while( read_ext_eeprom(address) != -1){
      id_temp = read_ext_eeprom(address);
      if (id_temp == id){
          printf (lcd_escreve,"\fID Encontrado:%d", id_temp);
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
   delay_ms(2000);
}

int deleteBlock(int8 address){
   
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
