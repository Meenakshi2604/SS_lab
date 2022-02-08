#include<stdio.h>
#include<string.h>
#include<stdlib.h>

/*char * trimmed(char * str){
	while(*str == ' ')
		str++;
	return str;
}*/

void absLoader(){
  FILE *objP, *loadP;
  int i,j, startaddr, staddr1, staddr2;
  char progname[10],buff[100],tempname[10], staddr[10];

  printf("Enter the program name: ");
  scanf("%06s",progname);
  printf("%s",progname);
  objP = fopen("Object_Program.txt","r");
  loadP = fopen("Loaded_Program.txt","w");
  if(objP == NULL)
	{
		printf("Object file missing!!");
		return;
	}
  fgets(buff,100,objP);
  printf("%s",buff);
  if(buff[0] == 'H'){
  	for(int i=2,j=0; i<8;i++,j++){
  		tempname[j]=buff[i];
  	}
  }
  printf("%s \n",tempname);
  //tempname[j]='\0';
  if(strcmp(progname,tempname)==0){
  	printf("The names are equal \n");
  	char temp[] = {buff[9],buff[10],buff[11],buff[12],buff[13],buff[14],'\0'};
  	startaddr = atoi(temp);
  	printf("Program starting address: %d \n", startaddr);
  	for(int i = 0; i < 6; i++)
		temp[i] = buff[i+16];
	printf("Program Length: %s \n", temp);
	
	fgets(buff,100,objP);
	//printf("%s",buff);
  	while(buff[0] != 'E'){
  		buff[strlen(buff) -1] = '\0';
  		if(buff[0]=='T'){
  			for(i=2,j=0;i<8;i++,j++)
  				staddr[j]=buff[i];
  			//printf("%s \n",staddr);
  			staddr1 = strtol(staddr, NULL, 16);
  			printf("Starting address of the text record: %X \n",staddr1);
  			staddr2 = staddr1;
  			printf("%s",buff);
  			for(i=12; buff[i] != '\0'; i+=2){
  				if(buff[i] == '^'){
  					i--;
  					//printf(" Inside if block buff = %c \n",buff[i]);
  				}
  				else{
  					char temp1[2];
  					temp1[0] = buff[i];
  					if(buff[i+1] == '^'){
  						temp1[1] = ' ';
  					}
  					else
  						temp1[1]= buff[i+1];
  					printf("%X : %c%c \n",staddr2,temp1[0],temp1[1]);
  					fprintf(loadP,"%X : %c%c \n",staddr2,temp1[0],temp1[1]);
  					staddr2 = staddr2 + 1;
  				}		
  			}
  		}
  		fgets(buff,100,objP);
  	}
  }
  else{
  	printf("Names don't match \n");
  	fclose(objP);
	fclose(loadP);
	return;
  }
}

void main(){
  absLoader();
}
