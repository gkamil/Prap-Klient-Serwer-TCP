#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

int main(int argc , char *argv[]) {

	int  socket_desc;
	struct sockaddr_in server;
    int def_port = 8888;
    char def_ip[]="127.0.0.1";
    char server_reply[200], message[200] = "klient";
    memset (server_reply, 0, sizeof (server_reply));

    if((socket_desc = socket(AF_INET , SOCK_STREAM , 0))==-1)
    {
    	perror("Nie moge utworzyc gniazda ");
    }
    else{
    	printf("Utworzono gniazdo\n ");
    }

    //adres serwera zdalnego
    server.sin_family = AF_INET;
    if(argc == 1)
    {
    	server.sin_addr.s_addr = inet_addr(def_ip);
    	server.sin_port = htons(def_port);
    }
    else if(argc == 2)
    {
    	server.sin_addr.s_addr = inet_addr(argv[1]);
    	server.sin_port = htons(def_port);
    }
    else
    {
    	server.sin_addr.s_addr = inet_addr(argv[1]);
    	server.sin_port = htons(atoi(argv[2]));
    }

    //Polacz z serwerem zdalnym (TCP)
    if (connect(socket_desc , (struct sockaddr *)&server , (socklen_t)sizeof(server)) < 0)
    {
        puts("Blad polaczenia");
        return 1;
    }
    puts("Polaczono");
    sleep (5);

    //Wyslij dane
    if( send(socket_desc , message , strlen(message) , 0) < 0)
    {
            puts("Blad wyslania danych");
            return 1;
    }
    puts("Dane wyslano\n");

    while (1)
    {
        	//Nasluchiwanie i odbior danych z serwera (TCP)
        	if( recv(socket_desc, server_reply , 200 , 0) < 0)
        	{
                puts("Blad odbioru danych");
        	}
        	puts("Dane odebrano\n");
        	puts(server_reply);
        	memset (server_reply, 0, sizeof (server_reply));
        	gets(message);
        	if(!strcmp(message,"koniec"))
        	{
        		close(socket_desc);
        		return 0;
        	}
        	//wysylanie
            if( send(socket_desc , message , strlen(message) , 0) < 0)
            {
                    puts("Blad wyslania danych");
                    return 1;
            }
            puts("Dane wyslano\n");
    }


	return EXIT_SUCCESS;
}
