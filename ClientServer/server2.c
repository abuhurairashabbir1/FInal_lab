// server(multiple clients).c
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>

void error(const char *msg)
{
    perror(msg);
    exit(1);
}

int main(int argc, char *argv[])
{
    int sockfd, newsockfd, portno;
    socklen_t clilen;
    char ch;
    struct sockaddr_in serv_addr, cli_addr;
    int n;
    pid_t pid; // 1st change

    if (argc < 2)
    {
        fprintf(stderr, "Usage %s port\n", argv[0]);
        exit(1);
    }

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
        error("Error opening socket");

    bzero((char *)&serv_addr, sizeof(serv_addr));

    portno = atoi(argv[1]);

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(portno);

    if (bind(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
        error("Error on binding");

    listen(sockfd, 5);
    clilen = sizeof(cli_addr);

    while (1)
    {
        newsockfd = accept(sockfd, (struct sockaddr *)&cli_addr, &clilen);

        if (newsockfd < 0)
            error("Failed to accept request");
        // changes
        pid = fork();
        if (pid < 0)
            error("Failed to fork");
        if (pid == 0)
        {
            do
            {
                n = read(newsockfd, &ch, 1);
                if (n < 0)
                    error("Read error");

                printf("I got %c from client\n", ch);

                if (ch == 'Q')
                    break;

                ch++;

                n = write(newsockfd, &ch, 1);
                if (n < 0)
                    error("Write error");

            } while (1);

            close(newsockfd);
            exit(0);
        }
        else
        {
            close(newsockfd);
        }
    }
    return 0;
}