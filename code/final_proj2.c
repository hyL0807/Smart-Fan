#include <stdio.h>
#include <wiringPi.h>
#include <pthread.h>
#include <softPwm.h>
#include <string.h>
#include <stdlib.h>
#include <lirc/lirc_client.h>
#include <time.h>

#define DC 1
#define TRIG 2
#define ECHO 3
#define PS 4
#define IP1 6
#define IP2 7
#define ST1 8
#define ST2 9
#define ST3 10
#define ST4 11

unsigned int start = 0;
unsigned int end = 0;
unsigned int dist = 0;
unsigned int ps = 0;

int AUTO = 1;
int on = 0;

int check = 0;

int Setup(){
	
	if(wiringPiSetup()==-1)
		return 1;
	
	pinMode(TRIG,OUTPUT);
	pinMode(ECHO,INPUT);
	pinMode(DC,OUTPUT);
	pinMode(PS,INPUT);
	pinMode(IP1,OUTPUT);
	pinMode(IP2,OUTPUT);
	
	int st[4]={ST1,ST2,ST3,ST4};
	
	for(int i=0;i<4;i++){
		pinMode(st[i],OUTPUT);
		digitalWrite(st[i],0);
	}
	
	
	digitalWrite(IP1,1);
	digitalWrite(IP2,0);
	
	softPwmCreate(DC,0,100);
	
}

void* distance(void* n){
	
	while(1){
		delay(60);
		digitalWrite(TRIG,1);
		delayMicroseconds(10);
		digitalWrite(TRIG,0);
	
		while(digitalRead(ECHO)==0);
		start = micros();
		while(digitalRead(ECHO)==1);
		end = micros();
		dist = (end-start)/58;		
		//printf("%d cm\n",(end-start)/58);
		delay(1000);
	}
		
}

void* isPerson(void* n){

	while(1){
		ps = digitalRead(PS);
		//printf("%d\n",ps);
		delay(500);
		
	}
}

void* stepMotor(void* n){
	
	int st[4]={ST1,ST2,ST3,ST4};
	int r_st[4]={ST4,ST3,ST2,ST1};
	
	while(1){
		if(check == 1){
			for(int i=0;i<3;i++){
				digitalWrite(st[i],1);
				delay(5);
				digitalWrite(st[i],0);
			}
		}
		else if(check == 2){
			for(int i=0;i<3;i++){
				digitalWrite(r_st[i],1);
				delay(5);
				digitalWrite(r_st[i],0);
			}
		}
		else{
			
		}
		
	}
}

void* remoteControl(void* n){
	
	struct lirc_config *config;
 
	int buttonTimer = millis();
	int l1,l2,l3,la = 0;
	char *code;
 
	if (lirc_init("lirc", 1) == -1) exit(0);
	
	if (lirc_readconfig(NULL, &config, NULL) == 0) 
	{
		while (lirc_nextcode(&code) == 0) 
		{
			if (code == NULL)	continue;
 
			if (strstr(code, "KEY_1")){
				printf("KEY_1\n");
				AUTO = 1;
				
			}
			else if (strstr(code, "KEY_2")){
				printf("KEY_2\n");
				on = 0;
				
			}
			else if (strstr(code, "KEY_3")){
				printf("KEY_3\n");
				on = 1;
			}
			else if (strstr(code, "KEY_0")){
				printf("KEY_0\n");
				AUTO = 0;
			}
 
			free(code);
		}
 
		lirc_freeconfig(config);
	}
 
	lirc_deinit();

}

int main(void){
	
	Setup();

	pthread_t ultra,body,step,remote;
	
	softPwmCreate(DC,0,100);

	pthread_create(&ultra,0,distance,0);
	pthread_create(&body,0,isPerson,0);
	pthread_create(&step,0,stepMotor,0);
	pthread_create(&remote,0,remoteControl,0);
	
	char p_data;
	FILE* fp;
	
	AUTO = 1;
	on = 0;
	
	while(1){
		
		fp = fopen("python_data.txt", "r");
	
		fscanf(fp,"%d",&check);
		
		fclose(fp);
		
		if(AUTO == 1){
			on = 0;
			if(ps == 1){
				if(dist < 30) softPwmWrite(DC,dist*5);
				else digitalWrite(DC,0);
			}
			else{
				digitalWrite(DC,0);
			}
		}
		else{
			
			if(on == 1) softPwmWrite(DC,80);
			else digitalWrite(DC,0);
		}
		
	}

	pthread_join(ultra,0);
	pthread_join(body,0);
	pthread_join(step,0);
	pthread_join(remote,0);

	return 0;
}
