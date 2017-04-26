/* This page contains a client program that can request a file from the server program * on the next page. The server responds by sending the whole file.
*/
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <time.h>

#define SERVER_PORT 12345         /* arbitrary, but client & server must agree */
#define BUF_SIZE 4096             /* block transfer size */

void fatal(char string[]){
  printf("%s\n", string);
  exit(1);
}

int countBuffer(char* csv){
  int iterator = 0;
  for(int i = 0; csv[i] != '\0'; i++){
    iterator++;
  }
  return iterator;
}

int* csvToIntArray(char* csv, int csvLength){
	int* rtn = (int*) malloc(sizeof(int)*4);
	char* buffer = (char*) malloc(sizeof(char) * 64);
	int rtnIndex = 0;
	int bufIndex = 0;
	for(int i = 0; i < csvLength; i++){
		if(csv[i] == ','){
			rtn[rtnIndex] = atoi(buffer);
			rtnIndex++;
			for(int j = 0; j<64;j++){
				buffer[j] == '\0';
			}
			bufIndex = 0;
		}
		else{
			buffer[bufIndex] = csv[i];
			bufIndex++;
		}
	}
	free(buffer);
	return rtn;
}

int main(int argc, char **argv)
{
  int c, s, bytes;
  char buf[BUF_SIZE];             /* buffer for incoming file */		
  struct hostent *h;              /* info about server */
  struct sockaddr_in channel;     /* holds IP address */    
						 
  if (argc != 3)
    fatal("Usage: client server-name file-name");

  h = gethostbyname(argv[1]); /* look up host’s IP address */
  if (!h)
    fatal("gethostbyname failed");

  s = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

  if (s < 0)
    fatal("socket");

  memset(&channel, 0, sizeof(channel));
  channel.sin_family = AF_INET;
  memcpy(&channel.sin_addr.s_addr, h->h_addr, h->h_length);
  channel.sin_port = htons(SERVER_PORT);

  c = connect(s, (struct sockaddr *)&channel, sizeof(channel));
  if (c < 0)
    fatal("connect failed");
  /* Connection is now established. Send file name including 0 byte at end. */
  write(s, argv[2], strlen(argv[2]) + 1);

  /* Go get the file and write it to standard output. */
  while (true)
  {
    bytes = read(s, buf, BUF_SIZE);     /* read from socket */
    if (bytes <= 0)                     /* check for end of file */
      exit(0);

    int bufferSize = countBuffer(buf);
	 printf("%i", bufferSize);
    int* array = csvToIntArray(buf, bufferSize);

    for(int j = 0; j < 4; j++){
      printf("%i\n", array[j]);
    }

    write(1, buf, bytes);               /* write to standard output */

    free(array);
  }
}
