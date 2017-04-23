#include <stdio.h>
#include <sys/types.h>
#include <sys/fcntl.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

/* This is the server code */
#define SERVER PORT 12345 #define BUF SIZE 4096 #define QUEUE SIZE 10
    int
    main(int argc, char *argv[])
{
  int s, b, l, fd, sa, bytes, on = 1;
  char buf[BUF SIZE];
  struct sockaddr in channel;
  /* arbitrary, but client & server must agree */ /* block transfer size */
  /* buffer for outgoing file */                  /* holds IP address */
  /* Build address structure to bind to socket. */ memset(&channel, 0, sizeof(channel));
  channel.sin family = AF INET;
  channel.sin addr.s addr = htonl(INADDR ANY);
  channel.sin port = htons(SERVER PORT);
  /* Passive open. Wait for connection. */
  s = socket(AF INET, SOCK STREAM, IPPROTO TCP);
  if (s < 0)
    fatal("socket failed");
  setsockopt(s, SOL SOCKET, SO REUSEADDR, (char *)&on, sizeof(on));
  b = bind(s, (struct sockaddr *)&channel, sizeof(channel));
  if (b < 0)
    fatal("bind failed");
  l = listen(s, QUEUE SIZE); /* specify queue size */
  if (l < 0)
    fatal("listen failed");
  /* Socket is now set up and bound. Wait for connection and process it. */ while (1)
  {
    /* zero channel */
    /* create socket */
  }
}
sa = accept(s, 0, 0);
if (sa < 0)
  fatal("accept failed");
read(sa, buf, BUF SIZE);
/* Get and return the file. */ fd = open(buf, O RDONLY);
if (fd < 0)
  fatal("open failed");
/* block for connection request */ /* read file name from socket */ /* open the file to be sent back */
while (1)
{
  bytes = read(fd, buf, BUF SIZE); /* read from file */
  if (bytes <= 0)
    break;
  write(sa, buf, bytes);
}
close(fd);
close(sa);
/* check for end of file */ /* write bytes to socket */
                            /* close file */
                            /* close connection */