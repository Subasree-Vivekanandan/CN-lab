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
          
         
         int bindsa = bind(sockfd,(struct sockaddr*)&sadr,sizeof(sadr));
         
         if(bindsa != 0){
          printf("Socket not binded..\n");
          }
          
         else {
          printf("Scoket binded..\n");
          }
          
          if(listen(sockfd,5)!=0){
           printf("Socket not listening..\n");
           }
           else{
            printf("Socket listening..\n");
            }
            
          int len = sizeof(sadr);
          int clifd = accept(sockfd,(struct sockaddr*)&sadr,&len);
          
          if(clifd < 0){
           printf("Client not connected..\n");
           }
           else{
            printf("Client connected..\n");
            }
            
          while(1){
           
            read(clifd,&arr,sizeof(arr));
           
            read(clifd,&bal,sizeof(int));
           
            
             if((strncmp(arr,"exit",4) == 0) || bal==0){
              printf("Server exit\n");
              exit(0);
             
             }
             printf("The username is %s \n",arr);
             printf("The balance is %d \n",bal);
             
             
            
         
 }
  close(sockfd);
  }
