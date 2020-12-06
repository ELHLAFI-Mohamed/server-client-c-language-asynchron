#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/select.h>
int main(){

	int sd,sd2,n ;
char  buff[1024] ;
struct sockaddr_in  ad; 
ad.sin_family=AF_INET;
ad.sin_port=htons(2324);
inet_aton("127.0.0.1",&ad.sin_addr);

        if((sd=socket(PF_INET,SOCK_STREAM,IPPROTO_TCP))<0){
                printf("erreur socket : %s \n",strerror(errno));
                exit(1);

        }


if(connect(sd,(struct sockaddr *)&ad,sizeof(ad))<0){
        printf("erreur connect :%s\n",strerror(errno));
        exit(2);
}
fd_set readfs ;
while(1){
FD_ZERO(&readfs);
FD_SET(sd,&readfs);
FD_SET(0,&readfs);
while(select(sd+1,&readfs,NULL,NULL,NULL)==0);
if(FD_ISSET(sd,&readfs)){
n=recv(sd,buff,sizeof(buff),0);
buff[n]='\0';
printf("server -----> :%s\n",buff);
}
if(FD_ISSET(0,&readfs)){
gets(buff);
send(sd,buff,strlen(buff),0);

}
}

}

