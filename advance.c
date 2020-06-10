
#include<lpc21xx.h>
#define PIN "9595"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

void delay(void);
void lcd(unsigned char,int b);
char keypad(void);

__irq void UART0_Interrupt(void);

void GSM_Begin(void);							
void GSM_Calling(char *);
void GSM_HangCall(void);
void GSM_Response(void);
void GSM_Response_Display(void);
void GSM_Msg_Read(int);
bool GSM_Wait_for_Msg(void);
void GSM_Msg_Display(void);
void GSM_Msg_Delete(unsigned int);
void GSM_Send_Msg(char* , char*);
void GSM_Delete_All_Msg(void);

char buff[160];		/* buffer to store responses and messages */
bool status_flag = false;	/* for checking any new message */
volatile int buffer_pointer;
char Mobile_no[14];		/* store mobile no. of received message */
char message_received[60];		/* save received message */
int position = 0;

char c;
unsigned int cnt=1;

void delay_ms(uint16_t j)
{
    uint16_t x,i;
	for(i=0;i<j;i++)
	{
    for(x=0; x<6000; x++);    /* loop to generate 1 milisecond delay with Cclk = 60MHz */
	}
}

void UART0_init(void)
{
	PINSEL0 = PINSEL0 | 0x00000005;	/* Enable UART0 Rx0 and Tx0 pins of UART0 */
	U0LCR = 0x83;	/* DLAB = 1, 1 stop bit, 8-bit character length */
	U0DLM = 0x00;	/* For baud rate of 9600 with Pclk = 15MHz */
	U0DLL = 0x61;	/* We get these values of U0DLL and U0DLM from formula */
	U0LCR = 0x03; /* DLAB = 0 */
	U0IER = 0x00000001; /* Enable RDA interrupts */
}

void UART0_TxChar(char ch) /* A function to send a byte on UART0 */
{
	U0IER = 0x00000000; /* Disable RDA interrupts */
	U0THR = ch;
	while( (U0LSR & 0x40) == 0 );	/* Wait till THRE bit becomes 1 which tells that transmission is completed */
	U0IER = 0x00000001; /* Enable RDA interrupts */
}

void UART0_SendString(char* str) /* A function to send string on UART0 */
{	uint8_t i1 = 0;
	U0IER = 0x00000000; /* Disable RDA interrupts */
	while( str[i1] != '\0' )
	{
		UART0_TxChar(str[i1]);
		i1++;
	}
	U0IER = 0x00000001; /* Enable RDA interrupts */
}

__irq void UART0_Interrupt(void)
{
	buff[buffer_pointer] = U0RBR;	/* copy UDR(received value) to buffer */
	buffer_pointer++;
	status_flag = true;						            /* flag for new message arrival */
	VICVectAddr = 0x00;
}

int main(void)
{	
		VICVectAddr0 = (unsigned) UART0_Interrupt;	/* UART0 ISR Address */
	VICVectCntl0 = 0x00000026;	/* Enable UART0 IRQ slot */
	VICIntEnable = 0x00000040;	/* Enable UART0 interrupt */
	VICIntSelect = 0x00000000;	/* UART0 configured as IRQ */
	UART0_init();
	//UART0_SendString("GSM Initializing...");
//	delay_ms(3000);
//	GSM_Begin();
	while(1)
	{
	char pin[4];
	int i=0;
	int PIN1=atoi(PIN);
	int pin2;
   PINSEL0=PINSEL2=0;
   IODIR0=0x00000ffd;
   IODIR1=0x00780000;
   lcd(0x38,0);
   lcd(0x0f,0);
     lcd('E',1);
	   lcd('n',1);
	   lcd('t',1);
	   lcd('e',1);
	   lcd('r',1);
	   lcd(' ',1);
	   lcd('y',1);
	   lcd('o',1);
	   lcd('u',1);
	   lcd('r',1);
	   lcd(' ',1);
	   lcd('P',1);
	   lcd('I',1);
	   lcd('N',1);
	  lcd(0xC0,0);
	while(i<4)
     {
       c=keypad();                            //Obtaining values from keypad
       lcd(c,1);
	   pin[i]=c;
	   i=i+1;
      }
	  
	  
	  pin2=atoi(pin);
	  lcd(0x01,0);
	  if(PIN1==pin2)
	  {
	   lcd('p',1);
	   lcd('i',1);
	   lcd('n',1);
	   lcd(' ',1);
	   lcd('i',1);
	   lcd('s',1);
	   lcd(' ',1);
	   lcd('c',1);
	   lcd('o',1);
	   lcd('r',1);
	   lcd('r',1);
	   lcd('e',1);
	   lcd('c',1);
	   lcd('t',1);
	   lcd(0xC0,0);
	   lcd('A',1);
	   lcd('/',1);
	   lcd('C',1);
	   lcd(' ',1);
	   lcd('i',1);
	   lcd('s',1);
	   lcd(' ',1);
		lcd('A',1);
		lcd('c',1);
	   lcd('t',1);
	   lcd('i',1);
	   lcd('v',1);
	   lcd('e',1);
	   GSM_Send_Msg("9173795958","A/C is Active");
	   goto stop;
	  }
	  
	  else
	  {	 
	  	if(cnt==3)
	  	{	
	  	lcd(0x01,0);
		lcd('A',1);
	   lcd('/',1);
	   lcd('C',1);
	   lcd(' ',1);
	   lcd('i',1);
	   lcd('s',1);
	   lcd(' ',1);
		lcd('B',1);
		lcd('l',1);
	   lcd('o',1);
	   lcd('c',1);
	   lcd('k',1);
	   lcd('e',1);
		lcd('d',1);
		GSM_Send_Msg("9173795958","A/C is Blocked");
		goto stop;
   	  	}	
	  	else
	  	{
		lcd(0x01,0);    
		lcd('p',1);
	   lcd('i',1);
	   lcd('n',1);
	   lcd(' ',1);
	   lcd('i',1);
	   lcd('s',1);
	   lcd(' ',1);
		lcd('i',1);
		lcd('n',1);
	   lcd('c',1);
	   lcd('o',1);
	   lcd('r',1);
	   lcd('r',1);
	   lcd('e',1);
	   lcd('c',1);
	   lcd('t',1);
	   cnt=cnt+1;
	   }
	}
	}
	stop: goto stop;
}

void lcd(unsigned char a,int b)         //LCD Subroutine
  {
    IOSET0=a<<2;
    IOSET0=b<<10;
    IOSET0=1<<11;
    delay();
    IOCLR0=1<<11;
    IOCLR0=b<<10;
    IOCLR0=a<<2;
  }
char keypad(void)                         //Keypad Scan
 {  
   while(1)
   {
      IOCLR1|=(1<<19);               //Making row1 LOW
      IOSET1|=(1<<20)|(1<<21)|(1<<22); //Making rest of the rows '1'
      if(!(IOPIN1&(1<<16)))             //Scan for key press
       {
        while(!(IOPIN1&(1<<16)));
        return '1';                           //Returning value to display
       }
      if(!(IOPIN1&(1<<17)))
       {
         while(!(IOPIN1&(1<<17)));
         return '2';
       }
      if(!(IOPIN1&(1<<18)))
       {
         while(!(IOPIN1&(1<<18)));
         return '3';
       }
      IOCLR1|=(1<<20);
      IOSET1|=(1<<21)|(1<<22)|(1<<19);
      if(!(IOPIN1&(1<<16)))
{
        while(!(IOPIN1&(1<<16)));
        return '4';
      }
      if(!(IOPIN1&(1<<17)))
{
        while(!(IOPIN1&(1<<17)));
        return '5';
     }
      if(!(IOPIN1&(1<<18)))
{
        while(!(IOPIN1&(1<<18)));
        return '6';
     }
      IOCLR1|=(1<<21);
      IOSET1|=(1<<22)|(1<<20)|(1<<19);
      if(!(IOPIN1&(1<<16)))
{
        while(!(IOPIN1&(1<<16)));
        return '7';
     }
      if(!(IOPIN1&(1<<17)))
{
       while(!(IOPIN1&(1<<17)));
       return '8';
    }
      if(!(IOPIN1&(1<<18)))
{
        while(!(IOPIN1&(1<<18)));
        return '9';
}
      IOCLR1|=(1<<22);
      IOSET1|=(1<<19)|(1<<20)|(1<<21);
      if(!(IOPIN1&(1<<16)))
{
        while(!(IOPIN1&(1<<16)));
        return '*';
}
      if(!(IOPIN1&(1<<17)))
{
        while(!(IOPIN1&(1<<17)));
        return '0';
}
      if(!(IOPIN1&(1<<18)))
{
        while(!(IOPIN1&(1<<18)));
        return '#';
} 
   }
}
 
void delay(void)                                    //Delay loop
{
  unsigned int i;
  for(i=0;i<=20000;i++);
}

void GSM_Begin(void)
{
	while(1)
	{
		UART0_SendString("ATE0\r\n");		/* send ATE0 to check module is ready or not */
		delay_ms(500);
		if(strstr(buff,"OK"))
		{
			GSM_Response();		/* get Response */
			memset(buff,0,160);
			break;
		}
		else
		{
			//UART0_SendString("Error");
		}
	}
	delay_ms(1000);

	//UART0_SendString("Text Mode");
	UART0_SendString("AT+CMGF=1\r\n");	/* select message format as text */
	GSM_Response();
	delay_ms(1000);
}

void GSM_Msg_Delete(unsigned int position)
{	char delete_cmd[20];
	buffer_pointer=0;
	
	sprintf(delete_cmd,"AT+CMGD=%d\r\n",position);	/* delete message at specified position */
	UART0_SendString(delete_cmd);
}

void GSM_Delete_All_Msg(void)
{
	UART0_SendString("AT+CMGDA=\"DEL ALL\"\r\n");	/* delete all messages of SIM */	
}

bool GSM_Wait_for_Msg(void)
{
	char msg_location[4];
	int i;
	delay_ms(500);
	buffer_pointer=0;

	while(1)
	{
		if(buff[buffer_pointer]=='\r' || buff[buffer_pointer]== '\n')	/*eliminate "\r \n" which is start of string */
		{
			buffer_pointer++;
		}
		else
			break;
	}
		
	if(strstr(buff,"CMTI:"))		/* "CMTI:" to check if any new message received */
	{
		while(buff[buffer_pointer]!= ',')
		{
			buffer_pointer++;
		}
		buffer_pointer++;
		
		i=0;
		while(buff[buffer_pointer]!= '\r')
		{
			msg_location[i]=buff[buffer_pointer];		/* copy location of received message where it is stored */
			buffer_pointer++;
			i++;
		}

		/* convert string of position to integer value */
		position = atoi(msg_location);
		
		memset(buff,0,strlen(buff));
		buffer_pointer=0;

		return true;
	}
	else
	{
		return false;
	}
}

void GSM_Send_Msg(char *num,char *sms)
{
	char sms_buffer[35];
	buffer_pointer=0;
	sprintf(sms_buffer,"AT+CMGS=\"%s\"\r\n",num);
	UART0_SendString(sms_buffer);		/*send command AT+CMGS="Mobile No."\r */
	delay_ms(200);
	while(1)
	{
		if(buff[buffer_pointer]==0x3e)		/* wait for '>' character*/
		{
			buffer_pointer = 0;
			memset(buff,0,strlen(buff));
			UART0_SendString(sms);		/* send msg to given no. */
			UART0_TxChar(0x1a);		/* send Ctrl+Z then only message will transmit*/
			break;
		}
		buffer_pointer++;
	}
	delay_ms(300);
	buffer_pointer = 0;
	memset(buff,0,strlen(buff));
	memset(sms_buffer,0,strlen(sms_buffer));
}

void GSM_Calling(char *Mob_no)
{
	char call[20];
	sprintf(call,"ATD%s;\r\n",Mob_no);		
	UART0_SendString(call);		/* send command ATD<Mobile_No>; for calling*/
}

void GSM_HangCall(void)
{
	UART0_SendString("ATH\r\n");		/*send command ATH\r to hang call*/
	
}

void GSM_Response(void)
{	int i=0;
	unsigned int timeout=0;
	int CRLF_Found=0;
	char CRLF_buff[2];
	int Response_Length=0;
	while(1)
	{
		if(timeout>=60000)		/*if timeout occur then return */
		return;
		Response_Length = strlen(buff);
		if(Response_Length)
		{
			delay_ms(1);
			timeout++;
			if(Response_Length==strlen(buff))
			{
				for(i=0;i<Response_Length;i++)
				{
					memmove(CRLF_buff,CRLF_buff+1,1);
					CRLF_buff[1]=buff[i];
					if(strncmp(CRLF_buff,"\r\n",2))
					{
						if(CRLF_Found++==2)		/* search for \r\n in string */
						{
							GSM_Response_Display();		/* display response */
							return;
						}
					}

				}
				CRLF_Found = 0;

			}
			
		}
		delay_ms(1);
		timeout++;
	}
	//status_flag = false;
}

void GSM_Response_Display(void)
{
	buffer_pointer = 0;
	while(1)
	{
		if(buff[buffer_pointer]== '\r' || buff[buffer_pointer]== '\n')		/* search for \r\n in string */
		{
			buffer_pointer++;
		}
		else
			break;
	}
	

	while(buff[buffer_pointer]!='\r')		/* display response till "\r" */
	{
		UART0_TxChar(buff[buffer_pointer]);								
		buffer_pointer++;
	}
	buffer_pointer=0;
	memset(buff,0,strlen(buff));
}

void GSM_Msg_Read(int position)
{
	char read_cmd[10];
	sprintf(read_cmd,"AT+CMGR=%d\r\n",position);
	UART0_SendString(read_cmd);		/* read message at specified location/position */
	GSM_Msg_Display();		/* display message */
}

void GSM_Msg_Display(void)
{	int i=0;
	delay_ms(500);
	if(!(strstr(buff,"+CMGR")))		/*check for +CMGR response */
	{
		UART0_SendString("No message");
	}
	else
	{
		buffer_pointer = 0;
		
		while(1)
		{
			if(buff[buffer_pointer]=='\r' || buff[buffer_pointer]== 'n')		/*wait till \r\n not over*/
			{
				buffer_pointer++;
			}
			else
			break;
		}
		
		/* search for 1st ',' to get mobile no.*/
		while(buff[buffer_pointer]!=',')
		{
			buffer_pointer++;
		}
		buffer_pointer = buffer_pointer+2;

		/* extract mobile no. of message sender */
		for(i=0;i<=12;i++)
		{
			Mobile_no[i] = buff[buffer_pointer];
			buffer_pointer++;
		}
		
		do
		{
			buffer_pointer++;
		}while(buff[buffer_pointer-1]!= '\n');
		
		i=0;

		/* display and save message */
		while(buff[buffer_pointer]!= '\r' && i<31)
		{
				UART0_TxChar(buff[buffer_pointer]);
				message_received[i]=buff[buffer_pointer];
				
				buffer_pointer++;
				i++;
		}
		
		buffer_pointer = 0;
		memset(buff,0,strlen(buff));
	}
	status_flag = false;
}
