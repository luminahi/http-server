#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>

int accept_connection(int server_fd, struct sockaddr_in* addr, int* addr_len) {
    int client_fd;

    if ((client_fd = accept(server_fd, (struct sockaddr*)addr, (socklen_t*)addr_len)) < 0) {
        perror("accept");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    printf("[connection established]\n\n");
    return client_fd;
}

void receive_request(int server_fd, int client_fd, char* buffer, int buffer_size) {
    int bytes_read = read(client_fd, buffer, buffer_size);
    if (bytes_read < 0) {
        perror("read failed");
        close(client_fd);
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    buffer[bytes_read] = '\0';
    
    printf("[Request]: \n\n%s\n\n", buffer);
}

int create_server(struct sockaddr_in* addr, int addr_len, int port) {
    int opt = 1;

    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd <= 0) {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt))) {
        perror("setsockopt");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    addr->sin_family = AF_INET;
    addr->sin_addr.s_addr = INADDR_ANY;
    addr->sin_port = htons(port);

    if (bind(server_fd, (struct sockaddr*)addr, addr_len) < 0) {
        perror("bind");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 3) < 0) {
        perror("listen");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    return server_fd;
}

void send_response(int new_socket) {
    char* response = "HTTP/1.1 200 OK\nContent-Type: text/plain\n\nHello From C Server!";
    send(new_socket, response, strlen(response), 0);
}
