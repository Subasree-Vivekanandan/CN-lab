#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <string.h>
#define PORT 8080

int main() {
         struct sockaddr_in sadr,cadr;
         
         int sockfd;
         int bal;
         char arr[100];
         
         sockfd = socket(AF_INET,SOCK_STREAM,0);
         
         if(sockfd < 0){
          printf("Socket not created..\n");
          }
          
         else {
          printf("Socket created..\n");
          }
          
          sadr.sin_family = AF_INET;
          sadr.sin_port = htons(PORT);
          sadr.sin_addr.s_addr = htonl(INADDR_ANY);
          
          if(connect(sockfd,(struct sockaddr*)&sadr,sizeof(sadr))!= 0){
           printf("Client not connected to socket..\n");
           }
           
           else{
            printf("Client connected to socket..\n");
            }
           
           while(1){
           
           printf("Enter the username : \n");
           fgets(arr,100,stdin);
           write(sockfd,&arr,sizeof(arr));
           
           printf("Enter the balance \n");
           scanf("%d",&bal);
           write(sockfd,&bal,sizeof(int));
           
           if((strncmp(arr,"exit",4) == 0) || bal==0){
              printf("Server exit\n");
              exit(0);
             
             }
         }
          close(sockfd);
 }
