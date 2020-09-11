#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


int main(int argc, char *argv[])
{
   char value;
   char filename[100];
   int pipe1[2];
   int pipe2[2];
   int PC, SP, IR, AC, X, Y;
   int memoryArr[2000];
   int i;
   
   //process command line arguements
   if (argc < 3)
   {
      printf("Too few arguments\n");
      return 0;
   }
   if (strlen(argv[1]) >= 100)
   {
      printf("File name too long\n");
      return 0;
   }


   //get filename
   strcpy(filename, argv[1]);
   int timer = atoi(argv[2]);

   //exit if timer is zero or less
   if (timer <= 0){

      printf("Timer is 0 or less, exiting program now");
      return 0;
   }



   if (pipe(pipe1) < 0 || pipe(pipe2) < 0)
   {
      write(STDERR_FILENO, "Pipe failed\n", 12);
      exit(1);
   }

   switch(fork())
   {
     case -1: 
      write(STDERR_FILENO, "Fork failed\n", 12);
      exit(2);
//CPU
     case 0: 
      dup2(pipe1[0], STDIN_FILENO);   /* repl stdin with pipe1[0]  */
      dup2(pipe2[1], STDOUT_FILENO);  /* repl stdout with pipe2[1] */
      close(pipe1[0]);                /* close these               */
      close(pipe1[1]);
      close(pipe2[0]);
      close(pipe2[1]);
      //execute program that is in memory that has been sent over
      exit(3);

//Memory
     default:

      //read file 
      FILE *fp;
      int readInInt;

      filename [ strcspn(filename, "\r\n") ] = 0;

      fp = fopen(filename + 3, "r");

      if(fp == NULL){

         printf("Error opening the file, exiting program");
         return 0;
      }

      int memCounter = 0;
      int readInt;
      char line[100 + 1] = "";

      while (fgets(line, sizeof(line), fp) != NULL) { 
    
         char *slash_slash = strstr(line, "//");

         if (slash_slash) {
            *slash_slash = '\0';
         }

         sscanf(slash_slash, "%d", readInt);

         //input processed integer into array and increase address counter
         memoryArr[memCounter] = readInt;
         memCounter++;
      }



      //send file that has been read into an array to CPU
    

      //printf("Sent %c\n", memoryArr);     /* print it                  */
      write(pipe1[1], &memoryArr, 1);     /* send "A" to child         */
      read(pipe2[0], &memoryArr, 1);      /* read what child sends     */
      printf("Read");     /* print it                  */
   }
}
