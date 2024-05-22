#include <stdio.h>
#include <wiringPi.h>

#define PS 4

int Setup(void){
	if(wiringPiSetup()==-1)
		return 1;
	pinMode(PS,INPUT);
	
}

int main(void)
{
	
	Setup();
	
	int i;
	
	while(1)
	{
		i = digitalRead(PS);
		printf("%d\n", i);
		delay(100);
	}
	
	
	
	
	
	
}
