#include <xc.h>

#pragma config FOSC = XT, WDTE = OFF, PWRTE = OFF, BOREN = ON, LVP = OFF, CPD = OFF, WRT = OFF, CP = OFF
#define _XTAL_FREQ 4000000UL

#define LCD_RS   PORTCbits.RC0
#define LCD_EN   PORTCbits.RC1
#define LCD_D4   PORTCbits.RC2
#define LCD_D5   PORTCbits.RC3
#define LCD_D6   PORTCbits.RC4
#define LCD_D7   PORTCbits.RC5

static void lcd_pulse_enable(void){ LCD_EN=1; __delay_us(2); LCD_EN=0; __delay_us(50); }
static void lcd_write_nibble(unsigned char n){ LCD_D4=(n>>0)&1; LCD_D5=(n>>1)&1; LCD_D6=(n>>2)&1; LCD_D7=(n>>3)&1; lcd_pulse_enable(); }
static void lcd_send(unsigned char v, unsigned char isData){ LCD_RS=isData; lcd_write_nibble(v>>4); lcd_write_nibble(v&0x0F); }
static void lcd_cmd(unsigned char c){ lcd_send(c,0); if(c==0x01||c==0x02) __delay_ms(2); }
static void lcd_data(unsigned char d){ lcd_send(d,1); }
static void lcd_init(void){
	__delay_ms(20); LCD_RS=0; LCD_EN=0;
	lcd_write_nibble(0x03); __delay_ms(5);
	lcd_write_nibble(0x03); __delay_us(150);
	lcd_write_nibble(0x03); lcd_write_nibble(0x02);
	lcd_cmd(0x28); lcd_cmd(0x0C); lcd_cmd(0x06); lcd_cmd(0x01);
}
static void lcd_set_cursor(unsigned char row, unsigned char col){ lcd_cmd(0x80 | ((row?0x40:0x00)+col)); }
static void lcd_write_string(const char* s){ while(*s) lcd_data(*s++); }

static void self_test(void){
	unsigned char i;
	lcd_cmd(0x01);
	lcd_set_cursor(0,0);
	lcd_write_string("aqui funciona");
	lcd_set_cursor(1,0);
	lcd_write_string("tudo   Cnt:00");
	for(i=0;i<100;i++){
		lcd_set_cursor(1,11);
		lcd_data('0'+(i/10));
		lcd_data('0'+(i%10));
		__delay_ms(250);
	}
}

void main(void){
	TRISCbits.TRISC0=0; TRISCbits.TRISC1=0; TRISCbits.TRISC2=0;
	TRISCbits.TRISC3=0; TRISCbits.TRISC4=0; TRISCbits.TRISC5=0;
	PORTC=0x00;
	ADCON1=0x06;
	lcd_init();
	lcd_set_cursor(0,0); lcd_write_string("aqui funciona");
	lcd_set_cursor(1,0); lcd_write_string("tudo");
	__delay_ms(1500);
	self_test();
	while(1){}
}

