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
if(bind(sd,(struct sockaddr *)&ad,sizeof(ad))<0){
printf("erreur bind :%s \n",strerror(errno));
exit(2);
}
listen(sd,100);
int taille =sizeof(ad);

while(1){
printf("wait for a new client ......\n");
if((sd2=accept(sd,(struct sockaddr *)&ad,&taille))<0){
printf("erreur bind :%s \n",strerror(errno));
exit(2);
                }

printf("connexion d'un client:%s\n ",inet_ntoa(ad.sin_addr));

if(fork()==0){
close(sd);
fd_set readfs;
while(1){   
FD_ZERO(&readfs);
FD_SET(sd2,&readfs);
FD_SET(0,&readfs);
while(select(sd2+1,&readfs,NULL,NULL,NULL)==0);
printf("MSG:");
if(FD_ISSET(0,&readfs)){
gets(buff);
send(sd2,buff,strlen(buff),0);
}
if(FD_ISSET(sd2,&readfs)){
n=recv(sd2,buff,sizeof(buff),0);
buff[n]='\0';
printf("client ------>  :%s\n",buff);
}
}
}

close(sd2);


}

}
