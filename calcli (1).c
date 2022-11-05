#include<netdb.h>
#include<stdio.h>
#include<stdlib.h>
#include <unistd.h>
#include<string.h>
#include<sys/socket.h>
#include <arpa/inet.h>
#define PORT 8082


int main() 
{ 
    int sockfd, connfd,n,choice; 
    float num1,num2,ans;
    char buff[256];
    struct sockaddr_in servaddr, cli;   

	sockfd = socket(AF_INET, SOCK_STREAM, 0); 
    
    if (sockfd == -1) { 
	printf("Socket creation failed....\n"); 
	exit(0); 
    } 
    else
    printf("Socket created successfully...\n"); 
	
	bzero(&servaddr, sizeof(servaddr)); 
	servaddr.sin_family = AF_INET; 
	servaddr.sin_addr.s_addr = inet_addr("127.0.0.1"); 
	servaddr.sin_port = htons(PORT); 

    if (connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) != 0) { 
	
		printf("Connection with the Calculator failed...\n"); 
		exit(0); 
    } 
    else
	printf("Connected to the Calculator..\n"); 
	
	
	
    A: bzero(buff,256);
    n= read(sockfd,buff,255);
    
    if(n<0)
        {
        printf("Error in reading socket...");
        }
        printf("Server - %s\n",buff);
        scanf("%f",&num1);
        write(sockfd, &num1, sizeof(int));
        bzero(buff,256);
        n= read(sockfd,buff,255);


    if(n<0)
        {
         printf("Error in reading socket...");
        }
        printf("Server -  %s\n",buff);
        scanf("%f",&num2);
        write(sockfd, &num2, sizeof(int));

        bzero(buff,256);
        n= read(sockfd,buff,255);
 

    if(n<0)
    {
        printf("Error in reading socket...");
    }
        printf("Server -  %s\n",buff);
        scanf("%d",&choice);
        write(sockfd, &choice, sizeof(int));

        if(choice ==6)
        {
        goto B;
        }

        read(sockfd, &ans, sizeof(int));
        printf("Server - The answer is : %.2f\n", ans);

        if(choice !=6)
        {
            goto A;
        }

    B:  
        printf("You have selected to exit.\nCalculator exit...");
        close(sockfd);;
        return 0;
} 

