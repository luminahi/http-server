#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>
#include <arpa/inet.h>
#include "lib/http.h"

int main(int argc, char* argv[]) {
    const int port = 8080;
    const int buffer_size = 512;
    int server_fd;
    struct sockaddr_in addr;
    unsigned int addr_len = sizeof(addr);
    char buffer[buffer_size];

    server_fd = create_server(&addr, addr_len, port);

    printf("server is listening on port %d\n", port);

    while (true) {
        int client_fd = accept_connection(server_fd, &addr, &addr_len);
        receive_request(server_fd, client_fd, buffer, buffer_size);
        send_response(client_fd);
        close(client_fd);
    }

    close(server_fd);

    return 0;
}
