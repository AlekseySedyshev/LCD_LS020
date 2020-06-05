#include "stm32f0xx.h"        // Device header
#include "LCD_LS020.h"
#include "main.h"

// PA4 - CS, PA5 - CLK, PA7 - MOSI

uint8_t i,tic=0,flag=0;
uint16_t counter;
uint16_t TimingDelay,led_count,mss;

uint8_t color,color1,color2,color3=255;


void TimingDelayDec(void) 										{
 if (TimingDelay			!=0x00) TimingDelay--;
 if (!led_count) {led_count=500; GPIOB->ODR ^=1;}
 if (!mss) {mss=500;tic=1;}
 led_count--;mss--;
 }

void TIM17_IRQHandler(void)										{
		if (TIM17->SR & TIM_SR_UIF) {
					TimingDelayDec();
  				TIM17->SR &=(~TIM_SR_UIF);
		}
}	
void delay_ms (uint16_t DelTime) 							{
    TimingDelay=DelTime;
  while(TimingDelay!= 0x00);
}

void initial (void)														{
	RCC -> APB2ENR |= RCC_APB2ENR_SYSCFGEN;
	RCC->CR2 |= RCC_CR2_HSI48ON; 				// turn ON HSI48
  while(!(RCC->CR2 & RCC_CR2_HSI48RDY)){}
	RCC->CFGR |=RCC_CFGR_SW;                                          							//Switch for HSI48
	while (!(RCC->CFGR & RCC_CFGR_SWS_HSI48));
	FLASH->ACR = FLASH_ACR_PRFTBE | FLASH_ACR_LATENCY;
	RCC->CFGR3 |=RCC_CFGR3_I2C1SW_SYSCLK;   																				//switch I2C to SYSCLOCK (HSI48)
	RCC->CR &=~RCC_CR_HSION;																												//HSI - Off
	 																							
	RCC->APB1ENR |= RCC_APB1ENR_CRSEN;																							//Enable Clock Recovery
	CRS->CFGR &= ~CRS_CFGR_SYNCSRC;																									//RESET sync source
  CRS->CFGR |= CRS_CFGR_SYNCSRC_1; 																								//USB SOF used as sync. source
  CRS->CR |= CRS_CR_AUTOTRIMEN; 																									//enable auto trim
  CRS->CR |= CRS_CR_CEN; 																													//enable freq counter & block CRS->CFGR as read-only
	
	//---------------TIM17------------------
  RCC->APB2ENR |= RCC_APB2ENR_TIM17EN;    																			//HSI 48 MHz - 1 msek
  TIM17->PSC = 48000-1;
  TIM17->ARR = 1;
  TIM17->CR1 |= TIM_CR1_ARPE | TIM_CR1_DIR | TIM_CR1_CEN; 											// 
	TIM17->DIER |=TIM_DIER_UIE;
	NVIC_EnableIRQ (TIM17_IRQn);
	NVIC_SetPriority(TIM17_IRQn,0x05);	

//-------------------GPIOB-Blinking Led		
	RCC->AHBENR  |= RCC_AHBENR_GPIOBEN; 																					//
	GPIOB->MODER |= GPIO_MODER_MODER0_0;																					//Pb0-Out 
	
//------------------------SPI-----------------------------------
	RCC->AHBENR 		|=RCC_AHBENR_GPIOAEN;
	GPIOA->OSPEEDR 	|=GPIO_OSPEEDER_OSPEEDR2	| GPIO_OSPEEDER_OSPEEDR3 | GPIO_OSPEEDER_OSPEEDR4  \
									| GPIO_OSPEEDER_OSPEEDR5	| GPIO_OSPEEDER_OSPEEDR6 | GPIO_OSPEEDER_OSPEEDR7;
	GPIOA->MODER 		|=GPIO_MODER_MODER2_0 | GPIO_MODER_MODER3_0 |	GPIO_MODER_MODER4_0							\
									| GPIO_MODER_MODER5_1 | GPIO_MODER_MODER6_1 | GPIO_MODER_MODER7_1; 	//Pa2..Pa4 - out,Pa5..Pa7 - Alt_mode 
									
	GPIOA->AFR[0] 	|=(0<<GPIO_AFRL_AFRL7_Pos) |(0<<GPIO_AFRL_AFRL6_Pos) | (0<<GPIO_AFRL_AFRL5_Pos);  // SPI - Alternative
		
	RCC->APB2ENR |=RCC_APB2ENR_SPI1EN;
	SPI1->CR1 |=SPI_CR1_SSM | SPI_CR1_SSI | SPI_CR1_MSTR |  (0<<SPI_CR1_BR_Pos);  // SPI ->24MHz.
	SPI1->CR2 |=SPI_CR2_FRXTH;
		SPI1->CR1 |=SPI_CR1_SPE;
} 


int main(void)																{
initial();	
delay_ms(100); 
setRotation(3);
LCD_Init();
LCD_FillScreen(BLACK);
LCD_FillRect (10, 10, LS020_HEIGHT-20, LS020_WIDTH-20, MAROON);
LCD_FillRect (38,78, 55, 25, YELLOW);
//-----------------------------initial data--------------------------------
while (1)  /* Main loop */				{
uint8_t temp_col=color1;	
color1=color2;color2=color3;color3=temp_col;
	if(tic) {counter++;tic=0;

}
color++;
LCD_DrawRect (0, 0, 132, 176,8, setcolor(color1,color2,color3));
LCD_Puts("Test", 50, 16,RED,GREEN, 1, 1, 0);

LCD_FillCircle (50, 90, 10, setcolor((255-color),color,16));
LCD_FillTriangle(70, 100, 90,80, 90,100, setcolor(color, (255-color),0));


LCD_PrintDec(counter, 20,50, BLUE, WHITE,1,1,0);
LCD_PrintHex(counter, 20,60, GREEN, BLACK,1,1,0);
LCD_PrintBin(counter, 20,70, PINK, BLACK,1,1,0);
LCD_Puts("Hack reality", 30, 40,WHITE,  RED, 1, 1, 0);


} // end - main loop 
} // end - Main  
	
#ifdef  USE_FULL_ASSERT
void assert_failed(uint8_t* file, uint32_t line)
{ while (1)  {  } }
#endif
