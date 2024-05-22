#include <wiringPi.h>
#include <lirc/lirc_client.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
 
int main() 
{
	struct lirc_config *config;
 
	int buttonTimer = millis();
	int l1,l2,l3,la = 0;
	char *code;
 
	if (lirc_init("lirc", 1) == -1)	return(-1);
	
	if (lirc_readconfig(NULL, &config, NULL) == 0) 
	{
		while (lirc_nextcode(&code) == 0) 
		{
			if (code == NULL)	continue;
 
			if (strstr(code, "KEY_1")){
				printf("KEY_1\n");
				
				
			}
			else if (strstr(code, "KEY_2")){
				printf("KEY_2\n");
				
			}
			else if (strstr(code, "KEY_3")){
				printf("KEY_3\n");
				
			}
			else if (strstr(code, "KEY_0")){
				printf("KEY_0\n");

			}
 
			free(code);
		}
 
		lirc_freeconfig(config);
	}
 
	lirc_deinit();
	return(0);
}
