#include <stdio.h>
#include <stdlib.h>

int main(void){
  /* Declare all variables */
  FILE *pipe_read, *pipe_transform, *test_file1, *test_file2;
  char *filename1 = "./output1.txt";
  char *filename2 = "./output2.txt";
  char readbuf[80];
  int Char1, Char2;
  int bool = 0;

  /* Create one way pipeline in with popen() that reads in the input file */
  if ((pipe_read = popen("cat supermarket_sales.csv", "r")) == NULL){
    perror("popen");
    exit(1);
  }

  /* Create one way pipeline out with popen() */
  if ((pipe_transform = popen("grep -i 'Fashion accessories' | cut -d ',' -f 10| awk '{s+=$1} END {printf \"%0.2f\", s}'> output1.txt", "w")) == NULL){
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

  /* Test Code: Make sure both files contain the same value */

  /* open output1.txt file for reading */
  test_file1 = fopen(filename1, "r");
  if (test_file1 == NULL) {
    printf("Could not open input file %s\n", filename1);
    perror(filename1);
    return(1);
  }

   /* open output1.txt file for reading */
  test_file2 = fopen(filename2, "r");
  if (test_file2 == NULL) {
    printf("Could not open input file %s\n", filename2);
    perror(filename2);
    return(1);
  }

  /* For each character check if they are equal, if they aren't equal print error message and break out of the loop */
  Char1 = fgetc(test_file1); /* get a character from the file */
  Char2 = fgetc(test_file2);
  while (Char1 != EOF || Char2 != EOF) { /* while there are still characters left from each file */
    if (Char1 != Char2){
      printf("There is an error, the results aren't the same.\n");
      bool = 0;
      break;
    }
    else
      bool = 1;
    
    Char1 = fgetc(test_file1); /* get a character from the file */
    Char2 = fgetc(test_file2);
  }

  /* only print if the results matched for all characters */
  if (bool == 1)
    printf("The results matched!\n");

  /* Close both files */
  fclose(test_file1);
  fclose(test_file2);
}
