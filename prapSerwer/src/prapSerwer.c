#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/types.h>
#include "lista.h"

extern struct lista *pierwszy;
extern struct lista *ostatni;

int main(int argc , char *argv[])
{

	int socket_desc, new_socket;
	struct sockaddr_in server , client;
    int read_size, size_sockaddr_in;
    int def_port = 8888;
    char message[300] , client_message[300];
    pid_t pid;
    int wyslana_liczba;

    if((socket_desc = socket(AF_INET , SOCK_STREAM , 0))==-1)
    {
    	perror("Problem z utworzeniem gniazda ");
    	exit (23);
    }

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    if(argc == 1)
    	server.sin_port = htons(def_port);
    else
    	server.sin_port = htons(atoi(argv[1]));

    if((bind(socket_desc,(struct sockaddr *)&server ,(socklen_t)sizeof(server))) == -1)
    {
    	perror("Problem dolaczenia gniazda ");
    	exit (23);
    }

    //Nasluchiwanie na gniezdzie (serwer)
    listen(socket_desc , 100);
    puts("SERWER TCP: Czekam na polaczenie...");
    size_sockaddr_in = sizeof(struct sockaddr_in);
    while(1)
    {
    	new_socket = accept(socket_desc, (struct sockaddr *)&client, (socklen_t*)&size_sockaddr_in);
    	if (new_socket<0)
    	{
    		perror("Problem z akceptacja poloczenia");
    		exit (23);
    	}
    	pid = fork();
    	if(pid == -1)
    	{
    		perror ("Blad w utworzeniu procesu \n");
    		exit (23);
    	}
    	else if(pid == 0)//proces potomny
    	{
    		puts("Polaczenie zaakceptowane");
    		//Odpowiedz do klienta
    		strcpy(message,"Witam, poloczeyles sie z serwerem TCP. Czekam na dane...\n");
    		write(new_socket , message , strlen(message));
    		bzero(message, (size_t)300);
    		while (1)
    		{
    			while( (read_size = recv(new_socket, client_message , 300 , 0)) > 0 )
    		    {
    				if(read_size == 0)// zamkniecie klienta
    				{
    					close(new_socket);
    					exit (0);
    				}
    				puts("SERWER: Dane odebrano");
    				puts (client_message);
    				if((wyslana_liczba = atoi(client_message)) != 0 || client_message[0] == '0')
    				{
    					sprintf(message, "%d\n",wyslana_liczba);
    					dodajElement(wyslana_liczba);
    					wypiszListe();
    					write(new_socket , message , strlen(message));
    					bzero(message, (size_t)300);
    				}
    				else if(!strcmp(client_message,"suma"))
    				{
    					sprintf(message, "%d\n",sumaListy());
    					puts (message);
    					write(new_socket , message , strlen(message));
    					bzero(message, (size_t)300);
    				}
    				else if(!strcmp(client_message,"roznica"))
    				{
    					sprintf(message, "%d\n",roznicaListy());
    					puts (message);
    					write(new_socket , message , strlen(message));
    					write(new_socket , message , strlen(message));
    					bzero(message, (size_t)300);
    				}
    				else if(!strcmp(client_message,"sortujMalejaco"))
    				{
    					sortujMalejaco();
    					zapiszListe(message);
    					puts (message);
    					write(new_socket , message , strlen(message));
    					bzero(message, (size_t)300);
    				}
    				else if(!strcmp(client_message,"sortujRosnaco"))
    				{
    					sortujRosnaco();
    					zapiszListe(message);
    					puts (message);
    					write(new_socket , message , strlen(message));
    					bzero(message, (size_t)300);
    				}
    				else
    				{
    					//Wyslij echo
    					write(new_socket , client_message , strlen(client_message));
    				}
    				bzero(client_message, (size_t)300);
    		    }//while( (read_size = recv(new_socket, client_message , 300 , 0)) > 0 )
    		}//while (1)
    	}//if(pid == 0)
    	else
    	{
    		continue;
    	}

	}

	return EXIT_SUCCESS;
}

