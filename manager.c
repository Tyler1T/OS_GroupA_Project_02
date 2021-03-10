#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>	// for fork
#include <sys/types.h>	// for pid_t
#include <sys/stat.h>  //for mkfifo
#include <stdlib.h>	// for exit(1)
#include <string.h>	// for strlen
#include <sys/wait.h>	// for wait
#include <fcntl.h> //for file stuff

int main() {
  char temp[30];
  char toSend[93];
  int fd;
  char pipe[] = "./tmp/pipe";

  /* create the FIFO (named pipe) */
  mkfifo(pipe, 0666);
  // Open pipe as write only for the manager
  fd = open(pipe, O_WRONLY | O_CREAT);


  while(1==1){ //Get user info and put in a single character array
    printf("Hello, What employee would you like information on?\n");
    scanf("%[^\n]%*c", temp);
    printf("%s\n", temp);
    strcat(toSend,  temp);
    strcat(toSend, ",");

    printf("What is their job title?\n", temp);
    scanf("%[^\n]%*c", temp);
    strcat(toSend,  temp);
    strcat(toSend, ",");

    printf("What is their job status?\n", temp);
    scanf("%[^\n]%*c", temp);
    strcat(toSend,  temp);
    strcat(toSend, ",");

    printf("You are looking for: %s\n", toSend);
    printf("The assistant will report back to you shortly in their terminal\n\n");

    //writing info to pipe for the assistant
    write(fd, toSend, sizeof(toSend) + 1);
  }

  // Close plpe
  close(fd);

  /* remove the FIFO */
  unlink(pipe);
  return 0;
}
