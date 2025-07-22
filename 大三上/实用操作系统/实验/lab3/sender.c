#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/wait.h>
#define MAXMSG 512

struct my_msg{
long int my_msg_type;
char some_text[MAXMSG];
}msg;

int main(){
    int msgid;
    char buffer[BUFSIZ];
    msgid=msgget(1234,0666|IPC_CREAT);
    while(1){
        puts("Enter some text:");
        fgets(buffer,BUFSIZ,stdin);
        msg.my_msg_type=1;
        strcpy(msg.some_text,buffer);
	msgsnd(msgid,&msg,MAXMSG,0);
        if(strncmp(msg.some_text,"end",3)==0)
            break;
    }
    exit(0);
    return 0;
}
