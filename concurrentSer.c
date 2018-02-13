#include<stdio.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<stdlib.h>

int str_echo(int cs){
	char buf[50];
	recv(cs,buf,50,0);
	puts("Message from Client...");
	fputs(buf,stdout);
	send(cs,buf,50,0);

}
int main(){
	int ls,cs,len;
	struct sockaddr_in serv,cli;
	pid_t pid;
	puts("I am the Server!");
	//creating socket
	ls = socket(AF_INET,SOCK_STREAM,0);
	puts("socket created successfully");
	serv.sin_family = AF_INET;
	serv.sin_addr.s_addr=INADDR_ANY;
	serv.sin_port = htons(8080);
	
	bind(ls,(struct sockaddr*)&serv,sizeof(serv));
	puts("Binding done");
	
	listen(ls,3);
	puts("Listening for Clients");
	for(;;){
		len = sizeof(cli);
		cs = accept(ls,(struct sockaddr*)&cli,&len);
		puts("\n Connected to Client");
		//now the child process

		if((pid=fork())==0){
			puts("Child Process has been created");
			close(ls);
			str_echo(cs);
			close(cs);	
			exit(0);
		}
		
		close(cs);

	}
	
	return 0;


}
