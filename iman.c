#include "header.h"

#define MAX_BUFFER_SIZE 8192

void remove_html_tags(char* source, char* destination) {
    int in_tag = 0;
    char* src = source;
    char* dst = destination;
    
    while (*src) {
        if (*src == '<') {
            in_tag = 1;
        } else if (*src == '>') {
            in_tag = 0;
        } else if (!in_tag) {
            *dst++ = *src;
        }
        src++;
    }
    *dst = '\0';
}
int create_socket(const char *host, struct sockaddr_in *server_addr) {
    //creates a socket and returns a socket file descriptor
    int sockfd = socket(AF_INET, SOCK_STREAM, 0); //AF_INET means ipv4, SOCK_STREAM means TCP connection
    if (sockfd < 0) {
        return -1;
    }
    //gethostbyname() returns a hostent structure for server
    struct hostent *server = gethostbyname(host);
    if (server == NULL) {
        return -1;
    }

    server_addr->sin_family = AF_INET;
    server_addr->sin_port = htons(80);
    //copies the server address to the server_addr structure
    memcpy(&server_addr->sin_addr.s_addr, server->h_addr, server->h_length);

    if (connect(sockfd, (struct sockaddr *)server_addr, sizeof(*server_addr)) < 0) {
        return -1;
    }

    return sockfd;
}
void iman(char *command_name) {

    const char *host = "man.he.net";
    struct sockaddr_in server_addr;

    // Create the socket
    int sockfd = create_socket(host, &server_addr);
    if (sockfd < 0) {
        perror("Socket creation error");
        return;
    }

    //send the GET request
    char request[MAX_BUFFER_SIZE];
    snprintf(request, sizeof(request), "GET /?topic=%s&section=all HTTP/1.1\r\nHost: %s\r\n\r\n", command_name, host);

    if (send(sockfd, request, strlen(request), 0) < 0) {
        perror("Request sending error");
        return;
    }

    //receive the response
    char clean_response[MAX_BUFFER_SIZE];
    char response[MAX_BUFFER_SIZE];
    ssize_t bytes_received;
    int body_started = 0;

    //read the response and store in response array
    while ((bytes_received = recv(sockfd, response, sizeof(response) - 1, 0)) > 0) {
        response[bytes_received] = '\0';

        char *body = strstr(response, "<html>");
        if (body) {
            body += 6;
            body_started = 1;
        } else if (body_started) {
            body = response;
        }

        if (body_started) {
           remove_html_tags(body, clean_response);
        printf("%s", clean_response);
        }
    }

    if (bytes_received < 0) {
        perror("Response receiving error");
    }

    close(sockfd);
}