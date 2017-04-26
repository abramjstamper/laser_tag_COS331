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

int secondsUntilTime(int t){
	time_t currentTime = time(NULL);
	if(currentTime > t){
		return 0;
	} else {
		return (t - currentTime);
	}
}

int* csvToIntArray(char* csv){
	int* rtn = (int*) malloc(sizeof(int)*4);
	char* buffer = (char*) malloc(sizeof(char) * 64);
	int rtnIndex = 0;
	int bufIndex = 0;
	for(int i = 0; rtnIndex < 4; i++){
		if(csv[i] == ','){
			rtn[rtnIndex] = atoi(buffer);
			rtnIndex++;
			
			free(buffer);
			buffer = (char*) malloc(sizeof(char) * 64);
			
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

void output(int* input){
	printf("Team ID: %d\n", input[0]);
	printf("Gun ID:  %d\n", input[1]);
	time_t contestStart = input[2];
	printf("Contest Starts: %s", ctime(&contestStart));
	printf("Contest Length: %d minutes\n", (input[3]/60));
	printf("Time Until Contest Starts: %d minutes %d seconds\n",secondsUntilTime(input[2])/60, secondsUntilTime(input[2])%60);
	printf("Time Until Contest Ends:   %d minutes %d seconds\n",secondsUntilTime(input[2] + input[3])/60, secondsUntilTime(input[2] + input[3])%60);
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

    int* array = csvToIntArray(buf);
	 
	 output(array);

   // write(1, buf, bytes);               /* write to standard output */

    free(array);
  }
}
