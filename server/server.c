/* A simple server in the internet domain using TCP The port number is passed as an argument */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include <netdb.h>
#include <arpa/inet.h>
#include <pthread.h>

#include <mysql.h>
#include <stdio.h>

struct info_connection
{
        int sockfd;
        char * IP_Address;
};

/* Display error message and quit the program */
void error(const char *msg)
{
        perror(msg);
        exit(1);
}


void * connection_handler(void* arg){
        struct info_connection * info = (struct info_connection *) arg;
        int newsockfd = info->sockfd;
        char buffer[256];
        bzero(buffer, 256);
        int n;
        n = read(newsockfd, buffer, 255);
        if (n < 0){
                perror("ERROR reading from socket");
        }

        printf(" Data: [%s]\n", buffer);
        printf(" ok : %d vs ko : %d\n", ok, ko);
        free(info);
        close(newsockfd);
        return 0;
}

/* arg[1] <-- PORT NO */
int main(int argc, char *argv[])
{
        int sockfd, newsockfd, portno;
        socklen_t clilen;
        char buffer[256];
        struct sockaddr_in serv_addr, cli_addr;

        pthread_t vote;

        if (argc < 2) {
                fprintf(stderr, "ERROR, no port provided\n");
                exit(1);
        }

        // 1) on crée la socket, SOCK_STREAM signifie TCP

        sockfd = socket(AF_INET, SOCK_STREAM, 0);
        if (sockfd < 0)
                error("ERROR opening socket");

        // 2) on réclame au noyau l'utilisation du port passé en paramètre 
        // INADDR_ANY dit que la socket va être affectée à toutes les interfaces locales

        bzero((char *) &serv_addr, sizeof(serv_addr));
        portno = atoi(argv[1]);// convert the portno as string to an int
        serv_addr.sin_family = AF_INET;//IPv4
        serv_addr.sin_addr.s_addr = INADDR_ANY;//Takes one of the available interfaces
        serv_addr.sin_port = htons(portno);// convert the port number to bigendian
        if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) // if not bound correctly
                error("ERROR on binding"); // display error


        // On commence à écouter sur la socket. Le 5 est le nombre max
        // de connexions pendantes

        listen(sockfd, 5); 
        while (1) {
                //accept a connection to server from client pending list
                newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
                if (newsockfd < 0)
                    error("ERROR on accept");
                //display the client IP address and its port number 
                printf("Received packet from %s:%d\n\n",
                inet_ntoa(cli_addr.sin_addr), ntohs(cli_addr.sin_port));

                struct info_connection *to_thread = malloc(sizeof(struct info_connection));
                char * addr = inet_ntoa(cli_addr.sin_addr);

                to_thread->IP_Address = addr;
                to_thread->sockfd = newsockfd;
                if (pthread_create(&vote, NULL, connection_handler, to_thread))
                {
                        perror("pthread_create failed");
                }
                pthread_detach(vote);
        }

        close(sockfd);
        return 0;
}