/* This page contains a client program that can request a file from the server program * on the next page. The server responds by sending the whole file.
*/
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#define SERVER PORT 12345 #define BUF SIZE 4096

int main(int argc, char **argv)
{

  int c, s, bytes;
  char buf[BUF SIZE];
  struct hostent *h;
  struct sockaddr in channel;

  /* arbitrary, but client & server must agree */ /* block transfer size */
  /* buffer for incoming file */		  /* info about server */
						  /* holds IP address */
  if (argc != 3)
    fatal("Usage: client server-name file-name");

  h = gethostbyname(argv[1]); /* look up host’s IP address */
  if (!h)
    fatal("gethostbyname failed");

  s = socket(PF INET, SOCK STREAM, IPPROTO TCP);

  if (s < 0)
    fatal("socket");

  memset(&channel, 0, sizeof(channel));
  channel.sin family = AF INET;
  memcpy(&channel.sin addr.s addr, h->h addr, h->h length);
  channel.sin port = htons(SERVER PORT);

  c = connect(s, (struct sockaddr *)&channel, sizeof(channel));
  if (c < 0)
    fatal("connect failed");
  /* Connection is now established. Send file name including 0 byte at end. */

  write(s, argv[2], strlen(argv[2]) + 1);
  /* Go get the file and write it to standard output. */ while (1)
  {
    bytes = read(s, buf, BUF SIZE);
    if (bytes <= 0)
      exit(0);

    write(1, buf, bytes);
    fatal(char *string)
    {
      printf("%s\n", string);
      /* read from socket */
      /* check for end of file */
      /* write to standard output */
    }
  }
  exit(1);
}