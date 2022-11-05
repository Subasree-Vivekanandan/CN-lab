#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<netdb.h>
#include<netinet/in.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<unistd.h>
#define PORT 8080
#define MAX 100


void findInfile(char buffer[],char *output){
	FILE *fp = fopen("dns.txt","r");
	int i;
	i=0;
	char domain[100],ip[100];

	while(fgets(domain,100,fp)!=NULL){        //reads the file line by line

		int index = 0;
		while(index < strlen(domain) && domain[index]!=' ') index++;
		int i=0;
		for(i = index+1;domain[i]!='\n';i++){
		       
			ip[i-index-1] = domain[i];
		}
		domain[index] = '\0';		
		if(strcmp(domain,buffer)==0){
			strcpy(output,ip);
			fclose(fp);
			return;
		}
		
	}

	 strcpy(output,"Requested domain name not found");
        fclose(fp);
}

void dns(int server_socket){
	char buffer[MAX];
	struct sockaddr_in client_address;
	int i ;

	char domain[MAX], ip[MAX];
	
	while(1){
		
		char output[MAX];
              bzero(buffer,MAX);
		bzero(&client_address,sizeof(client_address));
		
		int len = sizeof(client_address);
		
		recvfrom(server_socket,buffer,MAX,0,(struct sockaddr*)&client_address,&len);

		buffer[strlen(buffer)-1] = '\0';
		printf("\nRequest from Client : %s\n",buffer);
		
		if(strncmp(buffer,"exit",4)==0){
			printf("\nServer has successfully exited the network\n");
			return;
		
		}
		
		findInfile(buffer,(char*)output);
		
		sendto(server_socket,output,strlen(output),0,(struct sockaddr*)&client_address,len);
		
	}
}

int main(){

	int server_socket;
	
	server_socket = socket(AF_INET,SOCK_DGRAM,0);
	
	if(server_socket<0){
		printf("\nError creating socket ...");
		exit(1);
	}
	else{
		printf("\nSocket created successfully ...\n");
	}
	

	struct sockaddr_in server_address;
	bzero(&server_address,sizeof(server_address));
	
	server_address.sin_family = AF_INET;           
	server_address.sin_port = htons(PORT);       
	server_address.sin_addr.s_addr = htonl(INADDR_ANY);
	
	if(bind(server_socket,(struct sockaddr*)&server_address, sizeof(server_address))== 0){
		printf("\nSocket binded successfully ...\n");

	} 
	else{
		printf("\nUnable to bind server... An error occured\n");
		exit(1);		
	}
	
	dns(server_socket);
	close(server_socket);
}

