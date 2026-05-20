#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
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
    char c;
    int portno, sockfd, n = 0;
    struct sockaddr_in serv_addr;
    struct hostent *server;
    if (argc < 3)
    {
        fprintf(stderr, "usage %s hostname port\n", argv[0]);
        exit(1);
    }
    portno = atoi(argv[2]);
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
        error("Error Opening Socket");
    server = gethostbyname(argv[1]);
    if (server == NULL)
    {
        fprintf(stderr, "Error no such host\n");
        exit(1);
    }
    bzero((char *)&serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length);
    serv_addr.sin_port = htons(portno);
    if (connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
        error("Error connecting ");
    while (1)
    {
        printf("Please enter a single character: ");
        c = (char)getc(stdin);
        getc(stdin);

        n = write(sockfd, &c, 1);
        if (n < 0)
            error("Error writing to socket");
        if (c == 'Q')
        {
            close(sockfd);
            return 0;
        }
        n = read(sockfd, &c, 1);
        if (n < 0)
            error("Error reading from socket");
        printf("I got %c from server\n", c);
    }
    close(sockfd);
    return 0;
}