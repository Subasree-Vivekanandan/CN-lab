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

void request(int client_socket){
	char buffer[MAX];
	int i;
	
	struct sockaddr_in server_address;
	
	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(PORT);
	server_address.sin_addr.s_addr = htonl(INADDR_ANY);
	
	while(1){
	
		bzero(buffer,MAX);
		
		printf("\nEnter domain name : ");
		i=0;
		while((buffer[i++] = getchar())!='\n');	

		int len = sizeof(server_address);
		sendto(client_socket,buffer,MAX,0,(struct sockaddr*)&server_address,len);
		
		if(strncmp(buffer,"exit",4)==0){
			printf("\nClient has successfully exited the network\n");
			return;
		}
			
		bzero(buffer,MAX);
	
		recvfrom(client_socket,buffer,MAX,0,(struct sockaddr*)&server_address,&len);
		
		printf("\nResponse from the server : %s",buffer);
	}
}

int main(){
	int client_socket;
	
	client_socket = socket(AF_INET,SOCK_DGRAM,0);
	
	if(client_socket<0){
		printf("\nError creating socket");
		exit(1);
	}
	else{
		printf("\nSocket creation successful\n");
	}
	
	request(client_socket);
	
	close(client_socket);
	return 0;
	
	

	
}

