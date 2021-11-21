
#include <16F877A.h>
#device ADC=8

#FUSES NOWDT                    //No Watch Dog Timer
#FUSES NOBROWNOUT               //No brownout reset
#FUSES NOLVP                    //No low voltage prgming, B3(PIC16) or B5(PIC18) used for I/O
#FUSES HS 

#use delay(crystal=20000000)
//#use rs232(baud=9600,parity=N,xmit=PIN_C6,rcv=PIN_C7,bits=8,stream=PORT1)


// -------Variables' Declaration
#define RX_BUFFER_SIZE 10
#define BLOCK_SIZE sizeof(User) 
signed int8 address_data_delete;
int8 rx_wr_index = 0;
int8 lock_pos = 0, rxd, read, valid_data_count;
int data_avail = FALSE, got_id = FALSE;
unsigned int8 rx_buffer[RX_BUFFER_SIZE];
#include "functions.c"

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




#int_TIMER1
void TIMER1_isr(void)
{
}

#int_RTCC
void RTCC_isr(void)
{

      
}

void main()
{
   //VARIAVEIS
   byte result;
   unsigned char option;
   
   eeprom_address address = 0;

   // unsigned char tmp_result;
   setup_timer_0(RTCC_INTERNAL|RTCC_DIV_256|RTCC_8_bit);      //13.1ms overflow
   setup_timer_1(T1_INTERNAL|T1_DIV_BY_8); //Overflow in 104ms | Resolution 1.6 us

   init_ext_eeprom();

   enable_interrupts(INT_TIMER0);
   enable_interrupts(INT_TIMER1);

   enable_interrupts(GLOBAL);


   lcd_ini();
   delay_us(50);
   printf(lcd_escreve, "\f  iniciando... ");
   delay_ms(200);

   // printf(lcd_escreve, "\fIFMT - Serial");
   // delay_ms(50);

   // int size = BLOCK_SIZE;
   // printf(lcd_escreve, "\fBlock_Size:%u", size);
   // delay_ms(500);

   // resetmemory();

   // int id [2] = {12,34};
   // int pass [4] = {1,2,3,4};
   // saveuser(id, pass, 1);
   // int id1 [2] = {14,0};
   // saveuser(id1, pass, 0);
   // int id2 [2] = {70,10};
   // saveuser(id2, pass, 1);
   // int id3 [2] = {0,10};
   // saveuser(id3, pass, 1);
   // int id4 [2] = {99,99};
   // saveuser(id4, pass, 3);//admin
   
   
   // getAddressByID(id2);
   adminMenu();



   // char keyboard_buffer[]= '6';
   // char n = '9';
   // unsigned char temp_pass[2];
   // unsigned int * buffer;
   // unsigned int pass[4];
   // strfromchar(temp_pass,n);
   // buffer = strToInt(temp_pass);
   // pass[0] = buffer[0];

   // printf(lcd_escreve,"\foutside:%u", pass[0]);
   // delay_ms(800);


   // int index = 2;
   // if(index>0){//for testing purposes
   //    for(int i=0; i < index; i++){
   //       printf(lcd_escreve,"\foutside:%u", buffer[i]);
   //       delay_ms(800);
   //    }
   // }
 
 
  // address_data_delete = getAddressByID(6);
  // printf(lcd_escreve, "\f Address ID = %d", address_data_delete);
 //  deleteBlock(address_data_delete);
   delay_ms(50);
   
   while(TRUE)
   {
   }

}

