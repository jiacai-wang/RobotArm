#include<stm32f10x.h>

//延时用于指示灯闪烁
void delay(int k)
{
	while(k--)
	{
		int i=1000;
		while(i--)
		{
			int j=100;
			while(j--);
		}
	}
}



//各舵机复位
void ServoInit()
{
	TIM3->CCR2=2100;
	delay(20);
	TIM2->CCR4=1000;
	delay(20);
	TIM2->CCR3=2300;
	delay(20);
	TIM2->CCR2=850;
	delay(20);
	TIM2->CCR1=1400;
	delay(50);									//各舵机复位
}

//初始化TIM2的四个通道为PWM模式1
void TIM2_Init()
{
	RCC->APB1ENR|=3;					//TIM2，TIM3时钟使能
	RCC->APB2ENR|=1<<2;				//GPIOA时钟使能
	
	GPIOA->CRL=0xB333BBBB;		//GPIOA.0-3,7复用推挽输出，GPIOA.4-6通用推挽输出

	TIM2->PSC=71;
	TIM3->PSC=71;							//CNT频率1MHz
	TIM2->ARR=20000;
	TIM3->ARR=20000;					//PWM周期20ms
	
	TIM2->CCMR1|=6<<4;				//CH1配置PWM1模式
	TIM2->CCMR1|=1<<3;				//CH1自动重装载预装载使能
	TIM2->CCER|=1;						//CH1比较使能
	TIM2->CCMR1|=6<<12;				//CH2配置PWM1模式
	TIM2->CCMR1|=1<<11;				//CH2自动重装载预装载使能
	TIM2->CCER|=1<<4;					//CH2比较使能
	TIM2->CCMR2|=6<<4;				//CH3配置PWM1模式
	TIM2->CCMR2|=1<<3;				//CH3自动重装载预装载使能
	TIM2->CCER|=1<<8;					//CH3比较使能
	TIM2->CCMR2|=6<<12;				//CH4配置PWM1模式
	TIM2->CCMR2|=1<<11;				//CH4自动重装载预装载使能
	TIM2->CCER|=1<<12;				//CH4比较使能
	TIM3->CCMR1|=6<<12;				//CH2配置PWM1模式
	TIM3->CCMR1|=1<<11;				//CH2自动重装载预装载使能
	TIM3->CCER|=1<<4;					//CH2比较使能
	
	TIM2->CR1|=1<<7;					//TIM2自动重装载预装载使能
	TIM3->CR1|=1<<7;					//TIM3自动重装载预装载使能
	TIM2->CR1|=1;							//TIM2使能
	TIM3->CR1|=1;							//TIM3使能
	
//		-90		530
//			0		1400
//		+90		2400
//大约100对应10度
	ServoInit();

}

//颜色识别模块初始化代码
void Color_Init()
{
	GPIOA->BSRR=1<<4;
	GPIOA->BSRR=1<<5;
	GPIOA->BSRR=1<<6;
	delay(50);
	GPIOA->BRR=1<<4;
	GPIOA->BRR=1<<5;
	GPIOA->BRR=1<<6;
	delay(20);
}

//初始化GPIOC用于工作指示灯
void GPIOC_Init()
{
	RCC->APB2ENR|=1<<4;				//GPIOC时钟使能
	GPIOC->CRH=0;
	GPIOC->CRH|=3<<20;				//配置PC.13口为通用推挽输出
}


//抓手释放
void release()
{
	TIM3->CCR2=1400;
	delay(10);
}

//抓手夹持
void hold()
{
	TIM3->CCR2=2100;
	delay(10);
}

void moveServo1(int i)
{
	if(i>2400||i<530) return;
	while(TIM2->CCR1>i)
	{
		TIM2->CCR1-=10;
		delay(1);
	}
	while(TIM2->CCR1<i)
	{
		TIM2->CCR1+=10;
		delay(1);
	}
}

void moveServo2(int i)
{
	if(i>2400||i<530) return;
	while(TIM2->CCR2>i)
	{
		TIM2->CCR2-=10;
		delay(1);
	}
	while(TIM2->CCR2<i)
	{
		TIM2->CCR2+=10;
		delay(1);
	}
}

void moveServo3(int i)
{
	if(i>2400||i<530) return;
	while(TIM2->CCR3>i)
	{
		TIM2->CCR3-=10;
		delay(1);
	}
	while(TIM2->CCR3<i)
	{
		TIM2->CCR3+=10;
		delay(1);
	}
}


void moveServo4(int i)
{
	if(i>2400||i<530) return;
	while(TIM2->CCR4>i)
	{
		TIM2->CCR4-=10;
		delay(1);
	}
	while(TIM2->CCR4<i)
	{
		TIM2->CCR4+=10;
		delay(1);
	}
}


void catch30()
{
	moveServo4(1200);	
	moveServo3(2000);
	moveServo1(820);
	release();
	moveServo2(1570);
	hold();
	moveServo2(850);
	moveServo1(2200);
	moveServo4(1300);
	moveServo3(2300);
	moveServo2(1400);
	release();
	delay(20);
	moveServo1(1950);
	delay(10);
	moveServo2(850);
	ServoInit();
}

void catch60()
{
	moveServo4(1000);	
	moveServo3(1600);
	moveServo1(1100);
	release();
	moveServo2(1770);
	hold();
	moveServo2(850);
	moveServo1(2270);
	moveServo4(1250);
	moveServo3(2100);
	moveServo2(1450);
	release();
	delay(20);
	moveServo1(2100);
	delay(10);
	moveServo2(850);
	ServoInit();
}
	
	
void catch135()
{
	moveServo4(1200);	
	moveServo3(2000);
	moveServo1(1900);
	release();
	moveServo2(1570);
	hold();
	moveServo2(850);
	moveServo1(2350);
	moveServo4(900);
	moveServo3(1600);
	moveServo2(1700);
	release();
	delay(20);
	moveServo1(2100);
	delay(10);
	moveServo2(850);
	ServoInit();
}


int main()
{
	TIM2_Init();
	GPIOC_Init();
	Color_Init();
	catch30();
	catch60();
	catch135();

	while(1)
	{
		GPIOC->BSRR=1<<13;			//开PC.13
		delay(5);
		GPIOC->BRR=1<<13;				//关PC.13
		delay(3);
	}
	
	
/*
	while(1)
	{
		while(TIM2->CCR4<1100)
		{
			TIM2->CCR4+=20;
			TIM2->CCR3+=20;
			TIM2->CCR2+=10;
			delay(1);
		}
		delay(3);
		while(TIM2->CCR4>530)
		{
			TIM2->CCR4-=20;
			TIM2->CCR3-=20;
			TIM2->CCR2-=10;
			delay(1);
		}
		delay(3);
	}
	
*/


}
