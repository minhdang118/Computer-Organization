#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

extern int errno;

int main(int argc, char *argv[])
{
    struct addrinfo hints;
    struct addrinfo *result, *rp;
    FILE *header_write_ptr;
    FILE *body_write_ptr;
    char *server, *port_str, *remote_file, *output_file;
    char response_code[4];
    unsigned char temp_buf[1];
    unsigned char check[5];
    ssize_t nwrite, nread;
    int s, sfd, char_count, port_num, code_num;
    bool is_header, is_jpg_marker;


    /* Argument errors */
    if (argc < 5)
    {
        fprintf(stderr, "Incorrect usage\n");
	    exit(1);
    }
    if (argc > 5)
    {
        fprintf(stderr, "Incorrect usage\n");
	    exit(1);
    }
    

    /* Get IP address */
    server = argv[1];
    port_num = atoi(argv[2]);
    if ((port_num < 1) || (port_num > 65535))
    {
        fprintf(stderr, "Incorrect usage\n");
	    exit(1);
    }
    port_str = argv[2];
    remote_file = argv[3];
    output_file = argv[4];

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = 0;
    hints.ai_protocol = 0;

    s = getaddrinfo(server, port_str, &hints, &result);
    if (s != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(s));
        exit(2);
    }


    /* Create socket and connect */
    sfd = socket(result->ai_family, result->ai_socktype, result->ai_protocol);

    if (connect(sfd, result->ai_addr, result->ai_addrlen) == -1)
    {
        fprintf(stderr, "Connection failed\n");
        exit(3);
    }


    /* Write request */
    char request[26 + strlen(remote_file) + strlen(server)];

    sprintf(request, "GET %s HTTP/1.1\r\nHost: %s\r\n\r\n", remote_file, server);
    
    request[sizeof(request) - 1] = '\0';

    do
    {
        nwrite = write(sfd, request, sizeof(request));
        // fprintf(stdout, "errno: %d\n", errno);
        if (nwrite == -1)
        {
            if (errno == EINTR)
                continue;
            else
            {
                fprintf(stderr, "Encountered OS error\n");
                exit(4);
            }
        }
        else 
            break;
    } while (true);


    /* Read response & Write to files - UPDATED */
    check[4] = '\0';
    is_header = true;
    char_count = 0;
    is_jpg_marker = false;

    char output_header_file[8 + strlen(output_file)];
    sprintf(output_header_file, "%s.header", output_file);
    header_write_ptr = fopen(output_header_file,"wb");
    body_write_ptr = fopen(output_file,"wb");

    response_code[3] = '\0';

    do
    {
        temp_buf[0] = 0;
        nread = read(sfd, temp_buf, 1);
        if (nread == -1)
        {
            if (errno == EINTR) continue;
            else
            {
                fprintf(stderr, "Encountered OS error\n");
                exit(4);
            }
        }
        else if (is_header)
        {
            fputc(temp_buf[0], header_write_ptr);
            // fprintf(stdout, "At header\n");
            // fprintf(stdout, "nread: %d\n", nread);
            // fprintf(stdout, "errno: %d\n", errno);

            check[0] = check[1];
            check[1] = check[2];
            check[2] = check[3];
            check[3] = temp_buf[0];
            
            if (strcmp(check, "\r\n\r\n") == 0)
            {
                is_header = false;
            }

            char_count++;

            if ((char_count == 10) || (char_count == 11) || (char_count == 12))
                response_code[char_count - 10] = temp_buf[0];

            continue;
        }
        else
        {
            if (nread == 0)
                break;
            fputc(temp_buf[0], body_write_ptr);
        }
    } while (true);
    
    fclose(header_write_ptr);
    fclose(body_write_ptr);


    /* Handling response code */
    // fprintf(stdout, "%s\n", response_code);
    // fprintf(stdout, "%d\n", code_num);
    code_num = atoi(response_code);
    if ((code_num < 200) || (code_num > 299)) exit(5);
    else exit(0);


    /* Close connection, free IP address and pointers */
    close(sfd);
    freeaddrinfo(result);

    free(result);
    free(rp);
    free(header_write_ptr);
    free(body_write_ptr);
    free(server);
    free(port_str);
    free(remote_file);
    free(output_file);
    free(response_code);
    free(temp_buf);
    free(check);
    free(request);
    free(output_header_file);
    
    

    // struct addrinfo *result, *rp;
    // FILE *header_write_ptr;
    // FILE *body_write_ptr;
    // char *server, *port_str, *remote_file, *output_file;
    // char response_code[4];
    // unsigned char temp_buf[1];
    // unsigned char check[5];

    return 0;
}