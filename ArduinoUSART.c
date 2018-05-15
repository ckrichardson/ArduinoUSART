
#define RDA 0x80
#define TBE 0x20
volatile unsigned char* myUCSR0A = (unsigned char*) 0xC0; 
volatile unsigned char* myUCSR0B = (unsigned char*) 0xC1;
volatile unsigned char* myUCSR0C = (unsigned char*) 0xC2;
volatile unsigned int* myUBRR0 = (unsigned int*) 0xC4;
volatile unsigned char* myUDR0 = (unsigned char*) 0xC6;


void setup() {
  U0init(9600);
}

void loop() {
  unsigned char cs1;
  while (U0kbhit() == 0){};
  cs1 = U0getchar();
  //Decode the number into hexadecimal value
  unsigned char first_digit = (cs1/16) + '0';
  unsigned char second_digit = (cs1%16) + '0';
  if(first_digit > '9'){
    first_digit = first_digit + 7; 
  }
  if(second_digit > '9'){
    second_digit = second_digit + 7; 
  }
  U0putchar('0');
  U0putchar('x');
  U0putchar(first_digit);
  U0putchar(second_digit);
  U0putchar('\n');
  
}

//
// function to initialize USART0 to "int" Baud, 8 data bits,
// no parity, and one stop bit. FCPU = 16MHz.
//
void U0init(int U0baud)
{

//
  unsigned long FCPU = 16000000;
  unsigned int tbaud;
  tbaud = (FCPU / 16 / U0baud - 1);
  *myUCSR0A = 0x20;
  *myUCSR0B = 0x18;
  *myUCSR0C = 0x06;
  *myUBRR0 = tbaud;
  //*myUBRR0H = (tbaud>>8);
  //*myUBRR0L = (tbaud & 0xFF);
}
//
// Read USART0 RDA status bit and return non-zero true if set
//
unsigned char U0kbhit()
{
  if(*myUCSR0A & RDA){
    return 1;
  }
  else{
    return 0;
  }
}
//
// Read input character from USART0 input buffer
//
unsigned char U0getchar()
{
   return *myUDR0;
}
//
// Wait for USART0 TBE to be set then write character to
// transmit buffer
//
void U0putchar(unsigned char U0pdata)
{
  while(!(*myUCSR0A & TBE)){
  }
  *myUDR0 = U0pdata;
}
