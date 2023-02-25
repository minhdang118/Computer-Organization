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
  ssize_t nwrite;
  int s, sfd;

  if (argc != 3)
  {
    fprintf(stderr, "Usage: %s decimal-port hexadecimal-address\n", argv[0]);
    exit(1);
  }

  char *end;
  long int port = strtol(argv[1], &end, 10);
  if (!(argv[1][0] != '\0' && end[0] == '\0'))
  {
    fprintf(stderr, "Invalid port '%s' (must be decimal)\n", argv[1]);
    exit(1);
  }

  unsigned long int address = strtoul(argv[2], &end, 16);
  if (!(argv[2][0] != '\0' && end[0] == '\0'))
  {
    fprintf(stderr, "Invalid address '%s' (must be hexadecimal)\n", argv[2]);
    exit(1);
  }

  printf("%lx\n", address);

  /* construct request, connect to server at port, and send it */

  /* Get IP address */
  memset(&hints, 0, sizeof(hints));
  hints.ai_family = AF_INET;
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_flags = 0;
  hints.ai_protocol = 0;

  s = getaddrinfo("localhost", argv[1], &hints, &result);
  if (s != 0)
  {
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

  /* Generate and send request */
  unsigned long int to_char = address;
  char addr_temp[17];
  for (int i = 0; i < 16; i++)
  {
   addr_temp[i] =  to_char % 256;
   to_char /= 256;
  }
  // addr_temp
  char buffer[10000] = "GET add_in";
  for (int i = 0; i < 1024; i++)
    strcat(buffer, addr_temp);
  strcat(buffer, "\n\r\n");

  send(sfd, buffer, sizeof(buffer), 0);

  int receive = 1;
  while (receive != 0)
  {
    receive = recv(sfd, buffer, 255, 0);
    buffer[receive] = '\0';
    // printf("Received %s\n", buffer);
  }

  close(sfd);

  return 0;
}
