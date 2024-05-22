#include <stdio.h>
#include <wiringPi.h>
#include <softPwm.h>

#define IN1 8
#define IN2 9
#define IN3 10
#define IN4 11

int main(void){
	
	if(wiringPiSetup() == -1)
		return 1;
	
	int IN[4]={IN1,IN2,IN3,IN4};
	int ST[4]={IN4,IN3,IN2,IN1};
	
	for(int i=0;i<4;i++){
		pinMode(IN[i],OUTPUT);
		digitalWrite(IN[i],0);
	}
	
	while(1){
		for(int i=0;i<3;i++){
			digitalWrite(IN[i],1);
			delay(10);
			digitalWrite(IN[i],0);
		}
	}
	
	return 0;
}
