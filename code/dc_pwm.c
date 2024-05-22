#include <stdio.h>
#include <wiringPi.h>
#include <pthread.h>

#define IP1 1
#define IP2 2
#define DC 3

void *control(void* n){
	
	while(1){
		digitalWrite(IP1,1);
		digitalWrite(IP2,0);
		delay(1000);
		digitalWrite(IP1,1);
		digitalWrite(IP2,1);
		delay(1000);
		digitalWrite(IP1,0);
		digitalWrite(IP2,1);
		delay(1000);
		digitalWrite(IP1,0);
		digitalWrite(IP2,0);
		delay(1000);
	}

}

int main(void){

	int time,i1,i2;
	pthread_t con;

	if(wiringPiSetup()==-1)
		return 1;
	pinMode(IP1,OUTPUT);
	pinMode(IP2,OUTPUT);
	pinMode(DC,OUTPUT);

	pthread_create(&con,0,control,0);

	pthread_join(con,0);

	digitalWrite(DC,1);
	/*
	while(1){
		digitalWrite(DC,1);
		delayMicroseconds(10000);
		digitalWrite(DC,0);
		delayMicroseconds(10000);

	}
	*/
	return 0;
}
