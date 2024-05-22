#include <stdio.h>
#include <wiringPi.h>
#include <pthread.h>
#include <softPwm.h>

#define DC 1
#define TRIG 2
#define ECHO 3
#define BTN1 4 //red button
#define BTN2 5 //yellow button
#define IP1 6
#define IP2 7

int Setup(){
	
	if(wiringPiSetup()==-1)
		return 1;
	
	pinMode(TRIG,OUTPUT);
	pinMode(ECHO,INPUT);
	pinMode(DC,OUTPUT);
	pinMode(BTN1,INPUT);
	pinMode(BTN2,INPUT);
	pinMode(IP1,OUTPUT);
	pinMode(IP2,OUTPUT);
	
	softPwmCreate(DC,0,100);
	
}

int main(void)
{
	Setup();
	
	softPwmWrite(DC,30);
	digitalWrite(IP1,1);
	digitalWrite(IP2,0);
	
	delay(5000);
	
	softPwmWrite(DC,50);
	
	delay(5000);
	
	softPwmWrite(DC,100);
	
	delay(5000);
	
	digitalWrite(DC,0);
	
	return 0;
}
