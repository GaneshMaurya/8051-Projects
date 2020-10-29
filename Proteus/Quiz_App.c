#include <reg51.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

//Function declarations
void cct_init(void);
void delay(int);
void high_delay(int);
void lcdinit(void);
void writecmd(int);
void writedata(char);
void Return(void);
void writeline_lcd(char []);
char READ_SWITCHES(void);
char get_key(void);
int Ask_Question(void);
int Check_Answer(char, char);

void writeline_serial(char []);
void SerialInitialize(void);
void SendByteSerially(unsigned char);
void uart_tx(unsigned char);
void receive();

#define Baud_rate 0xFD  // BAUD RATE 9600

int corrects = 0;

//*******************
//Pin description
/*
P2 is data bus
P3.7 is RS
P3.6 is E
P1.0 to P1.3 are keypad row outputs
P1.4 to P1.7 are keypad column inputs
*/
//********************
// Define Pins
//********************
sbit RowA = P1^0;     //RowA
sbit RowB = P1^1;     //RowB
sbit RowC = P1^2;     //RowC
sbit RowD = P1^3;     //RowD

sbit C1   = P1^4;     //Column1
sbit C2   = P1^5;     //Column2
sbit C3   = P1^6;     //Column3
sbit C4   = P1^7;     //Column4

sbit E    = P3^6;     //E pin for LCD
sbit RS   = P3^7;     //RS pin for LCD

int qno = 0;

// ***********************************************************
// Main program
//
int main(void)
{
	 char mode;
	 char ansl;
	 int correctl = 0;

   cct_init();              // Make input and output pins as required
   lcdinit();               // Initilize LCD  
	 SerialInitialize();

   EA = 1;
   ES = 1;

   writecmd(0x80);
	 writecmd(0x01);
   writeline_lcd("Quiz App");
	 writeline_serial("Quiz App");
 
   writecmd(0xc0);
	 writeline_lcd("Select Mode");
	 uart_tx(0x0d);
	 writeline_serial("Select Mode");
   
	 writecmd(0x94);
   writeline_lcd("1-Single Player");
	 uart_tx(0x0d);
	 writeline_serial("1-Single Player");
 
   writecmd(0xd4);
   writeline_lcd("2-Two Players");
	 uart_tx(0x0d);
	 writeline_serial("2-Two Players");

	 mode = get_key();                                 // Get pressed key
	 RI = 1;
	 RI = 0;
	 
	 writecmd(0x01);                                  // Clear screen
	 lcdinit();                                       // Initilize LCD
	 SerialInitialize();                              // Initialize Serial
	 
	 if (mode == '1')
	 {
		 writecmd(0x01);
		 writeline_lcd("Single Player Mode");           //write
		 P3 = 0x00;
		 high_delay(250);
	 }
	 else if (mode == '2')
	 {
		 writecmd(0x01);
		 writeline_lcd("Two Player Mode");              //write
		 uart_tx(0x0d);
		 writeline_serial("Two Player Mode"); 
		 high_delay(250);
	 }
		 
		 
	 writecmd(0x01);
	 writeline_lcd("Q. 5,11,17,23,29,__");
	 uart_tx(0x0d);
	 writeline_serial("Q. 5,11,17,23,29,__");
	 writecmd(0xc0);
	 writeline_lcd("a.40  b.35  c.36");
	 uart_tx(0x0d);
	 writeline_serial("a.40  b.35  c.36");
	 qno++;
	 receive();
	 
	 ansl = get_key();
	 
	 if (ansl == '2')
	 {
		 //correctl++;
		 writecmd(0x01);
		 writeline_lcd("Correct");
		 high_delay(250);
	 }
	 else 
	 {
		 writecmd(0x01);
		 writeline_lcd("Wrong");
		 high_delay(250);
	 }
	 
	 writecmd(0x01);
	 writeline_lcd("Q. 12,16,20,__,28");
	 uart_tx(0x0d);
	 writeline_serial("Q. 12,16,20,__,28");
	 writecmd(0xc0);
	 writeline_lcd("a.22  b.26  c.24");
	 uart_tx(0x0d);
	 writeline_serial("a.22  b.26  c.24");
	 qno++;
	 receive();
	 
	 ansl = get_key();
	 
	 if (ansl == '3')
	 {
		 //correctl++;
		 writecmd(0x01);
		 writeline_lcd("Correct");
		 high_delay(250);
	 }
	 else 
	 {
		 writecmd(0x01);
		 writeline_lcd("Wrong");
		 high_delay(250);
	 }
	 
	 writecmd(0x01);
	 writeline_lcd("Q. 3,8,15,24,35,__");
	 uart_tx(0x0d);
	 writeline_serial("Q. 3,8,15,24,35,__");
	 writecmd(0xc0);
	 uart_tx(0x0d);
	 writeline_lcd("a.48  b.52  c.51");
	 writeline_serial("a.48  b.52  c.51");
	 qno++;
	 receive();
	 
	 ansl = get_key();
	 
	 if (ansl == '1')
	 {
		 //correctl++;
		 writecmd(0x01);
		 writeline_lcd("Correct");
		 high_delay(250);
	 }
	 else 
	 {
		 writecmd(0x01);
		 writeline_lcd("Wrong");
		 high_delay(250);
	 }
	 
	 writecmd(0x01);
	 writeline_lcd("Q. -1,4,1,6,3,__");
	 uart_tx(0x0d);
	 writeline_serial("Q. -1,4,1,6,3,__");
	 writecmd(0xc0);
	 writeline_lcd("a.7  b.8  c.0");
	 uart_tx(0x0d);
	 writeline_serial("a.7  b.8  c.0");
	 qno++;
	 receive();
	 
	 ansl = get_key();
	 
	 if (ansl == '2')
	 {
		 //correctl++;
		 writecmd(0x01);
		 writeline_lcd("Correct");
		 high_delay(250);
	 }
	 else 
	 {
		 writecmd(0x01);
		 writeline_lcd("Wrong");
		 high_delay(250);
	 }
	 
	 writecmd(0x01);
	 writeline_lcd("Q. 10,21,33,46,60,__");
	 uart_tx(0x0d);
	 writeline_serial("Q. 10,21,33,46,60,__");
	 writecmd(0xc0);
	 writeline_lcd("a.73  b.88  c.75");
	 uart_tx(0x0d);
	 writeline_serial("a.73  b.88  c.75");
	 qno++;
	 receive();
	 
	 ansl = get_key();
	 
	 if (ansl == '3')
	 {
		 //correctl++;
		 writecmd(0x01);
		 writeline_lcd("Correct");
		 high_delay(250);
	 }
	 else 
	 {
		 writecmd(0x01);
		 writeline_lcd("Wrong");
		 high_delay(250);
	 }
	 
	 /*
	 writecmd(0x01);
	 writeline_lcd("Marks:");
	 
	 if (correctl == 0)
	 {
		 writecmd(0xc0);
		 writeline_lcd("-10/25");
	 }
	 else if (correctl == 1)
	 {
		 writecmd(0xc0);
		 writeline_lcd("-3/25");
	 }
	 else if (correctl == 2)
	 {
		 writecmd(0xc0);
		 writeline_lcd("4/25");
	 }
	 else if (correctl == 3)
	 {
		 writecmd(0xc0);
		 writeline_lcd("11/25");
	 }
	 else if (correctl == 4)
	 {
		 writecmd(0xc0);
		 writeline_lcd("18/25");
	 }
	 else if (correctl == 5)
	 {
		 writecmd(0xc0);
		 writeline_lcd("25/25");
	 }*/
	 
	 /*
	 uart_tx(0x0d);
	 writeline_serial("Marks:");
	 
	 if (corrects == 0)
	 {
		 uart_tx(0x0d);
		 writeline_serial("-10/25");
	 }
	 else if (corrects == 1)
	 {
		 uart_tx(0x0d);
		 writeline_serial("-3/25");
	 }
	 else if (corrects == 2)
	 {
		 uart_tx(0x0d);
		 writeline_serial("4/25");
	 }
	 else if (corrects == 3)
	 {
		 uart_tx(0x0d);
		 writeline_serial("11/25");
	 }
	 else if (corrects == 4)
	 {
		 uart_tx(0x0d);
		 writeline_serial("18/25");
	 }
	 else if (corrects == 5)
	 {
		 uart_tx(0x0d);
		 writeline_serial("25/25");
	 }*/
	 
	 high_delay(500);
	 return 0;

}


void cct_init(void)
{
	P0 = 0x00;   //used for RS and E
	P1 = 0xf0;   //used for generating outputs and taking inputs from Keypad
	P2 = 0x00;   //used as data port for LCD
	P3 = 0x03;   //used for serial
}


void delay(int a)
{
  int i;
  for(i=0;i<a;i++);   //null statement
}


void high_delay (int d)
{
	unsigned char i;
	for(;d>0;d--)
	{
		for(i=250;i>0;i--);
		for(i=248;i>0;i--);
	}
}


void writedata(char t)
{
   RS = 1;             // This is data
   P2 = t;             //Data transfer
   E  = 1;             // => E = 1
   delay(150);
   E  = 0;             // => E = 0
   delay(150);
}


void writecmd(int z)
{
   RS = 0;             // This is command
   P2 = z;             //Data transfer
   E  = 1;             // => E = 1
   delay(150);
   E  = 0;             // => E = 0
   delay(150);
}


void lcdinit(void)
{
  ///////////// Reset process from datasheet /////////
   delay(15000);
   writecmd(0x30);
   delay(4500);
   writecmd(0x30);
   delay(300);
   writecmd(0x30);
   delay(650);
  /////////////////////////////////////////////////////
   writecmd(0x38);    //function set
   writecmd(0x0c);    //display on,cursor off,blink off
   writecmd(0x01);    //clear display
   writecmd(0x06);    //entry mode, set increment
}


char READ_SWITCHES(void)	
{	
	RowA = 0; RowB = 1; RowC = 1; RowD = 1; 	//Test Row A

	if (C1 == 0) { delay(10000); while (C1==0); return '7'; }
	if (C2 == 0) { delay(10000); while (C2==0); return '8'; }
	if (C3 == 0) { delay(10000); while (C3==0); return '9'; }
	if (C4 == 0) { delay(10000); while (C4==0); return '/'; }

	RowA = 1; RowB = 0; RowC = 1; RowD = 1; 	//Test Row B

	if (C1 == 0) { delay(10000); while (C1==0); return '4'; }
	if (C2 == 0) { delay(10000); while (C2==0); return '5'; }
	if (C3 == 0) { delay(10000); while (C3==0); return '6'; }
	if (C4 == 0) { delay(10000); while (C4==0); return 'x'; }
	
	RowA = 1; RowB = 1; RowC = 0; RowD = 1; 	//Test Row C

	if (C1 == 0) { delay(10000); while (C1==0); return '1'; }
	if (C2 == 0) { delay(10000); while (C2==0); return '2'; }
	if (C3 == 0) { delay(10000); while (C3==0); return '3'; }
	if (C4 == 0) { delay(10000); while (C4==0); return '-'; }
	
	RowA = 1; RowB = 1; RowC = 1; RowD = 0; 	//Test Row D

	if (C1 == 0) { delay(10000); while (C1==0); return 'C'; }
	if (C2 == 0) { delay(10000); while (C2==0); return '0'; }
	if (C3 == 0) { delay(10000); while (C3==0); return '='; }
	if (C4 == 0) { delay(10000); while (C4==0); return '+'; }

	return 'n';           	// Means no key has been pressed
}


char get_key(void)           //get key from user
{
	char key = 'n';              //assume no key pressed

	while(key=='n')              //wait untill a key is pressed
		key = READ_SWITCHES();   //scan the keys again and again

	return key;                  //when key pressed then return its value
}


void writeline_lcd(char line[])
{
		int i;
		for(i=0;i<strlen(line);i++)
		{ writedata(line[i]); } //write to lcd
}


void writeline_serial(char line1[])
{  
   int i;
   EA = 0; ES = 0;
   for(i=0;i<strlen(line1);i++)
   { SendByteSerially(line1[i]); } // SEND DATA TO PC 
   EA = 1; ES = 1;
}


void SerialInitialize(void)                   // INITIALIZE SERIAL PORT
{
    TMOD = 0x20;                           // Timer 1 IN MODE 2 -AUTO RELOAD TO GENERATE BAUD RATE
    SCON = 0x50;                           // SERIAL MODE 1, 8-DATA BIT 1-START BIT, 1-STOP BIT, REN ENABLED
    TH1 = Baud_rate;                       // LOAD BAUDRATE TO TIMER REGISTER
    TR1 = 1;                               // START TIMER
}


void SendByteSerially(unsigned char serialdata)
{
    SBUF = serialdata;                        // LOAD DATA TO SERIAL BUFFER REGISTER
    while(TI == 0);                            // WAIT UNTIL TRANSMISSION TO COMPLETE
    TI = 0;                                    // CLEAR TRANSMISSION INTERRUPT FLAG
}


void uart_tx(unsigned char serialdata)
{
    SBUF = serialdata;                        //Load Data to Serial Buffer Register
    while(TI == 0);                               //Wait Until Transmission To Complete
    TI = 0;                                                //Clear Transmission Interrupt Flag
}


/*void serial_ISR (void) interrupt 4
{
    //receive character
    char chr;
    if(RI==1)
    {
        chr = SBUF;
        RI = 0;
    }

    P0 = ~P0;    //Show the data has been updated

    RI = 0;
}*/


void receive()        //Function to receive serial data
{
	unsigned char value;
	while(RI==0);       //wait till RI flag is set
	value=SBUF;     
	
	if (qno == 1)
	{
		if (value == 'b')
		{
			//corrects++;
			uart_tx(0x0d);
			writeline_serial("Correct");
		}
		else 
		{
			uart_tx(0x0d);
			writeline_serial("Wrong");
		}
	}
	else if (qno == 2)
	{
		if (value == 'c')
		{
			//corrects++;
			uart_tx(0x0d);
			writeline_serial("Correct");
		}
		else 
		{
			uart_tx(0x0d);
			writeline_serial("Wrong");
		}
	}
	else if (qno == 3)
	{
		if (value == 'a')
		{
			//corrects++;
			uart_tx(0x0d);
			writeline_serial("Correct");
		}
		else 
		{
			uart_tx(0x0d);
			writeline_serial("Wrong");
		}
	}
	else if (qno == 4)
	{
		if (value == 'b')
		{
			//corrects++;
			uart_tx(0x0d);
			writeline_serial("Correct");
		}
		else 
		{
			uart_tx(0x0d);
			writeline_serial("Wrong");
		}
	}
	else if (qno == 5)
	{
		if (value == 'c')
		{
			//corrects++;
			uart_tx(0x0d);
			writeline_serial("Correct");
		}
		else 
		{
			uart_tx(0x0d);
			writeline_serial("Wrong");
		}
	}
	
	RI=0;                    //Clear the RI flag
}