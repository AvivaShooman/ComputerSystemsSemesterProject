#include <stdio.h>
#include <stdlib.h>

int main(void){
  
        /* Declare all variables */
        FILE *pipe_read, *pipe_transform;
        char readbuf[80];
	int *ans;

        /* Create one way pipeline in with popen() that reads in the input file */
        if ((pipe_read = popen("cat supermarket_sales.csv", "r")) == NULL){
	  perror("popen");
	  exit(1);
        }

        /* Create one way pipeline out with popen() */
        if ((pipe_transform = popen("grep -i 'Fashion accessories' | cut -d ',' -f 10| awk '{s+=$1} END {print s}'", "w")) == NULL){
	  perror("popen");
	  exit(1);
        }

        /* Processing loop gets a line of input file, transforms it and prints to stdout*/
        while(fgets(readbuf, 80, pipe_read)){
	  if (fputs(readbuf, pipe_transform) == EOF){
	    perror("fputs");
	    exit(1);
	    
	  }
	}
	
	
        /* Close the pipes */
        pclose(pipe_read);
        pclose(pipe_transform);
	       
        return(0);
}
