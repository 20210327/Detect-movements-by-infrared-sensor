#include <REGX52.H>
#include <stdio.h>
/********Khai bao chan giao tiep************/
#define LCD_RS P0_0
#define LCD_RW P0_1
#define LCD_EN P0_2
#define LCD_D4 P0_4
#define LCD_D5 P0_5
#define LCD_D6 P0_6
#define LCD_D7 P0_7
#define in P1_0
#define out P2_0
/*************tao tre***********************/
void delay_us(unsigned int t){
        unsigned int i;
        for(i=0;i<t;i++);
}
void delay_ms(unsigned int t){
        unsigned int i,j;
        for(i=0;i<t;i++)
        for(j=0;j<125;j++);
}
/**************Ctr giao tiep LCD 16x2 4bit************/
void LCD_Enable(void){
        LCD_EN =1;
        delay_us(3);
        LCD_EN=0;
        delay_us(50);
}
void LCD_Send4Bit(unsigned char Data){              //Ham Gui 4 Bit Du Lieu Ra LCD
        LCD_D4=Data & 0x01;
        LCD_D5=(Data>>1)&1;
        LCD_D6=(Data>>2)&1;
        LCD_D7=(Data>>3)&1;
}
void LCD_SendCommand(unsigned char command){        // Ham Gui 1 Lenh Cho LCD
        LCD_Send4Bit(command >>4);/* Gui 4 bit cao */
        LCD_Enable();
        LCD_Send4Bit(command); /* Gui 4 bit thap*/
        LCD_Enable();
}
void LCD_Clear(){                                   // ham xoa man hinh
        LCD_SendCommand(0x01);
        delay_us(10);
}
void LCD_Init(){                                    // Ham Khoi Tao LCD
        LCD_Send4Bit(0x00);
        delay_ms(20);
        LCD_RS=0;
        LCD_RW=0;
        LCD_Send4Bit(0x03);
        LCD_Enable();
        delay_ms(5);
        LCD_Enable();
        delay_us(100);
        LCD_Enable();
        LCD_Send4Bit(0x02);
        LCD_Enable();
        LCD_SendCommand( 0x28 ); // giao thuc 4 bit, hien thi 2 hang, ki tu 5x8
        LCD_SendCommand( 0x0c); // cho phep hien thi man hinh
        LCD_SendCommand( 0x06 ); // tang ID, khong dich khung hinh
        LCD_SendCommand(0x01); // xoa toan bo khung hinh
}
void LCD_Gotoxy(unsigned char x, unsigned char y){  // ham tro toi ki tu
        unsigned char address;
        if(!y)address=(0x80+x);
        else address=(0xc0+x);
        delay_us(1000);
        LCD_SendCommand(address);
        delay_us(50);
}
void LCD_PutChar(unsigned char Data){               //Ham Gui 1 Ki Tu
        LCD_RS=1;
        LCD_SendCommand(Data);
        LCD_RS=0 ;
}
void LCD_Puts (char *s){                            //Ham gui 1 chuoi ky tu
        while (*s){
                LCD_PutChar(*s);
                s++;
        }
} 
/**************chuong trinh chinh*************/
void main(){
				LCD_Init();
				delay_ms(500);
				while(1){
					if (in == 1){
						out = 1;
						LCD_Gotoxy(0,0);
				    LCD_Puts("KTDL PIR");
						LCD_Gotoxy(0,1);
						LCD_Puts("                ");  // Xóa dòng bang cach hien thi 16 khoang trang
						LCD_Gotoxy(0,1);
						LCD_Puts("PHAT HIEN");
						delay_ms(2000);
					}
					else{
						out = 0;
						LCD_Gotoxy(0,0);
				    LCD_Puts("KTDL PIR");
						LCD_Gotoxy(0,1);
						LCD_Puts("KHONG PHAT HIEN");
						delay_ms(50);
					}	
				}				
}