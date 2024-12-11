/**
 * Originally taken from https://stackoverflow.com/questions/22077802/simple-c-example-of-doing-an-http-post-and-consuming-the-response
 */

#include <errno.h>
#include <stdio.h> /* printf, sprintf */
#include <stdlib.h> /* exit */
#include <unistd.h> /* read, write, close */
#include <string.h> /* memcpy, memset */
#include <sys/socket.h> /* socket, connect */
#include <netinet/in.h> /* struct sockaddr_in, struct sockaddr */
#include <netdb.h> /* struct hostent, gethostbyname */
#include <arpa/inet.h> /* inet_addr */

void error(const char *msg) { perror(msg); exit(1); }

int main(int argc,char *argv[])
{
    /* first what are we going to send and where are we going to send it? */
    int portno = 80;
    char *host = "192.168.10.20";
    char *message = "GET / HTTP/1.0\r\n\r\n";

    struct hostent *server;
    struct sockaddr_in serv_addr;
    int sockfd, bytes, sent, received, total;
    char response[4096];

    /* create the socket */
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) error("ERROR opening socket");

    printf("sockfd is: %d\n", sockfd);

    /* fill in the structure */
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(portno);
    serv_addr.sin_addr.s_addr = inet_addr(host);

    printf("about to connect\n");

    /* connect the socket */
    if (connect(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
        error("ERROR connecting");

    printf("connected\n");

    /* send the request */
    total = strlen(message);
    sent = 0;
    printf("writing %s (%lu characters)\n", message, strlen(message));
    do {
        bytes = write(sockfd, message + sent, total - sent);
        printf("written %d bytes to socket\n", bytes);
        if (bytes < 0)
            error("ERROR writing message to socket");
        if (bytes == 0)
            break;
        sent+=bytes;
    } while (sent < total);

    /* receive the response */
    memset(response, 0, sizeof(response));
    total = sizeof(response) - 1;
    received = 0;
    do {
      errno = 0;
      bytes = read(sockfd, response + received, total - received);
      if (errno == EAGAIN) {
        printf("EAGAIN\n");
        continue;
      }
      printf("read %d bytes\n", bytes);
      if (bytes < 0)
        error("ERROR reading response from socket");
      if (bytes == 0)
        break;
      received += bytes;
    } while (received < total);

    /*
     * if the number of received bytes is the total size of the
     * array then we have run out of space to store the response
     * and it hasn't all arrived yet - so that's a bad thing
     */
    if (received == total)
        error("ERROR storing complete response from socket");

    /* close the socket */
    close(sockfd);

    /* process response */
    printf("Response:\n%s\n",response);

    return 0;
}
