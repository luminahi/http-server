#ifndef _HTTP_H
#define _HTTP_H

int create_server(struct sockaddr_in* addr, int addr_len, int port);

int accept_connection(int server_fd, struct sockaddr_in* addr, int* addr_len);

void receive_request(int server_fd, int client_fd, char* buffer, int buffer_size);

void send_response(int new_socket);

#endif
