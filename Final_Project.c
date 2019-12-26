#include <stdio.h>
#include <stdlib.h>

int main(void){
  /* Declare all variables */
  FILE *pipe_read, *pipe_transform, *test_file1, *test_file2;
  char *filename1 = "./output1.txt";
  char *filename2 = "./output2.txt";
  char readbuf[80];
  int pipe_test, number1, number2, ans1, ans2;

  /* Create one way pipeline in with popen() that reads in the input file */
  if ((pipe_read = popen("cat supermarket_sales.csv", "r")) == NULL){
    perror("popen");
    exit(1);
  }

  /* Create one way pipeline out with popen() */
  if ((pipe_transform = popen("grep -i 'Fashion accessories' | cut -d ',' -f 10| awk '{s+=$1} END {print s}'> output1.txt", "w")) == NULL){
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
  if ((pipe_test = system("cat supermarket_sales.csv | grep -i 'Fashion accessories' | cut -d ',' -f 10| awk '{s+=$1} END {print s}'> output2.txt")) != -1){
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

   /* open input file for reading */
  test_file2 = fopen(filename2, "r");
  if (filename2 == NULL) {
    printf("could not open input file %s\n", filename2);
    perror(filename2);
    return(1);
  }

  ans1 = fscanf(test_file1, "%d", &number1);
  ans2 = fscanf(test_file2, "%d", &number2);

  printf("%d", number1);
  printf("%d", number2);

  /* Do I have to use getchar or getstr method here? */
  
  if (number1 == number2)
    printf("The results matched!");
  else
    printf("There is an error, the results aren't the same.");

  fclose(test_file1);
  fclose(test_file2);
  
  return(0);
}
