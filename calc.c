#include <stdio.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#define PORT 8082

int main() 
{ 
    int sockfd, connfd, len,n,choice; 
    float num1,num2,ans;
    char buff[256];
    struct sockaddr_in servaddr, cli;
    sockfd = socket(AF_INET, SOCK_STREAM, 0); 
	
    if (sockfd == -1) 
    { 
		printf("Socket creation failed...\n"); 
		exit(0); 
    } 
    else
		printf("Socket created successfully...\n"); 

	bzero(&servaddr, sizeof(servaddr));
 
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(PORT); 
	
	
    if ((bind(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr))) != 0) 
    { 
		printf("Socket bind failed...\n"); 
		exit(0); 
    } 
    else
		printf("Socket binded successfully...\n");
	
    if ((listen(sockfd, 5)) != 0) 
    { 
		printf("Listen failed...\n"); 
		exit(0); 
    } 
    else            	
    	printf("Calculator listening..\n"); 

	len = sizeof(cli);
	connfd = accept(sockfd, (struct sockaddr *)&cli, &len); 
	
    if (connfd< 0) 
    { 
		printf("Calculator acccept failed...\n"); 
		exit(0); 
    } 
    else
		printf("Calculator acccept the client...\n"); 
		
		
    
    A:n= write(connfd, "Enter first number: ",strlen("Enter first number :"));

    if(n < 0 ) printf("Error in writing to socket");
    {
        read(connfd, &num1, sizeof(int));
        printf("Client - Number 1 is %f\n", num1);
       
    }
    n= write(connfd, "Enter second number: ",strlen("Enter second number : "));
    if(n<0) printf("Error in writing to socket");
    {
        read(connfd, &num2, sizeof(int)); 
        printf("Client - Number 2 is %f\n", num2);
    }
    
    n= write(connfd,"Enter your choice : \n1.Addition\n2.Modulo\n3.Multiplication\n4.Division\n5.Subtraction\n6.Exit\n",strlen("Enter your choice : \n1.Addition\n2.Modulo\n3.Multiplication\n4.Divsion\n5.Subtarction\n6.Exit\n"));

    if(n<0) printf("Error in writing to socket");
    {
        read(connfd, &choice, sizeof(int));
        printf("Client - Choice is %d\n", choice);
    }
        switch(choice)
        {
            case 1:
            ans= num1+num2;
            break;
            
            case 2:
            ans =(int)num1% (int)num2;
            break;

            case 3:
            ans= num1*num2;
            break;

            case 4:
            ans= num1/num2;
            break;
            
            case 5:
            ans =num1-num2;
            break;
            
            case 6:
            goto B;
            break;
            
        }

        write(connfd, &ans, sizeof(int));
        if(choice !=6)
        {
            goto A;
        }

        B:close(connfd);
          close(sockfd);

        return 0;

}

