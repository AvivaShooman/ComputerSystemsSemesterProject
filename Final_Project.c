#include <stdio.h>
#include <stdlib.h>
#define MAX_LEN 10

int main(void){
  /* Declare all variables */
  FILE *pipe_read, *pipe_transform, *test_file1, *test_file2;
  char *filename1 = "./output1.txt";
  char *filename2 = "./output2.txt";
  char readbuf[80];
  char *ans1, *ans2;
  int pipe_test, number1, number2;

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

  /* Check that the pipe implemented above has the same output*/
  if ((pipe_test = system("cat supermarket_sales.csv | grep -i 'Fashion accessories' | cut -d ',' -f 10| awk '{s+=$1} END {printf \"%0.2f\", s}'> output2.txt")) != -1){
    perror("system");
    exit(1);
  }

   /* open input file for reading */
  test_file1 = fopen(filename1, "r");
  if (test_file1 == NULL) {
    printf("could not open input file %s\n", filename1);
    perror(filename1);
    return(1);
  }

  else
    printf("Opened");
  
   /* open input file for reading */
  test_file2 = fopen(filename2, "r");
  if (filename2 == NULL) {
    printf("could not open input file %s\n", filename2);
    perror(filename2);
    return(1);
  }

  else
    printf("Opened");
  
  fgets(ans1, MAX_LEN, test_file1);
  fgets(ans2, MAX_LEN, test_file2);

  printf("We are here1");
  
  printf("%s", ans1);
  printf("%s", ans2);

  /* Do I have to use getchar or getstr method here? */

  printf("We are here2");
  
  if (ans1 == ans2)
    printf("The results matched!");
  else
    printf("There is an error, the results aren't the same.");

  fclose(test_file1);
  fclose(test_file2);

  printf("We are here3");
  
  return(0);
}
