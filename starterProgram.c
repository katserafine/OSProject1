#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>

int main(int argc, char *argv[])
{
   char value;
   char filename[100];
   int pipe1[2];
   int pipe2[2];
   int PC = 0, SP, IR, AC, X, Y;
   int memoryArr[2000];
   int i;
   int instructionCount = 0;
   time_t t;
   srand((unsigned) time(&t));
   bool interupt = false;
   
   //process command line arguements
   if (argc < 3)
   {
      printf("Too few arguments\n");
      return 0;
   }
   if (sizeof(argv[1]) >= 100)
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


       for(int i = 0; i < instructionCount; i++){

         //Switch case for the actions 
         IR = memoryArr[PC];
         int operand = 0;

         // TODO
         // stack processing within the memory array already created

         
         switch(IR)
         {
            case 1:

               PC++;

               AC = memoryArr[PC];

               if(timer == i){
                  print("timer has been met, exiting program");  
                  return 0;   
               }

               PC++;
               break;

            case 2:
               // load the calue at the address into AC
               PC++;

               operand = memoryArr[PC];

               AC = memoryArr[operand];

               if(timer == i){
                  print("timer has been met, exiting program");  
                  return 0;   
               }

               PC++;
               break;

            case 3:
               //load the value from address found in this address into the AC
               PC++;

               //get address of jump loading spot
               operand = memoryArr[PC];

               //get address found within given address
               operand = memoryArr[operand];

               //load value from address previously found
               AC = memoryArr[operand];
               
               if(timer == i){
                  print("timer has been met, exiting program");  
                  return 0;   
               }

               PC++;

               break;

            case 4:
               //load the calue address + X into the AC

               PC++;

               operand = memoryArr[PC];

               int offset = operand + X;

               AC = memoryArr[offset];

               if(timer == i){
                  print("timer has been met, exiting program");  
                  return 0;   
               }

               PC++;
               break;

            case 5:
               //load the value at address + Y into AC

               PC++;

               operand = memoryArr[PC];

               int offset = operand + Y;

               AC = memoryArr[offset];
               
               if(timer == i){
                  print("timer has been met, exiting program");  
                  return 0;   
               }
               PC++;
               break;

            case 6:
               //load from sp + X into the AC
               int offset = SP + X;
               AC = memoryArr[offset];

               if(timer == i){
                  print("timer has been met, exiting program");  
                  return 0;   
               }

               PC++;

               break;

            case 7:
               //store the value into the address

               PC++;

               //get address from memeory
               operand = memoryArr[PC];

               //put AC into address given
               memoryArr[operand] = AC;

               if(timer == i){
                  print("timer has been met, exiting program");  
                  return 0;   
               }

               PC++;

               break;

            case 8:
               //get a random int from 1 to 100 and put into AC

               AC = (rand() % 100); 

               if(timer == i){
                  print("timer has been met, exiting program");  
                  return 0;   
               }

               PC++;

               break;

            case 9:
               //put port 

               operand = memoryArr[PC];

               if(timer == i){
                  print("timer has been met, exiting program");  
                  return 0;   
               }

               if(operand == 1){

                  //WRITE AC as int
                  printf(AC);

               }
               else{

                  //write AC as char
                  char holder = (char) AC;
                  printf(holder);

               }

               PC++;

               break;

            case 10:
               //add the calue in X to AC

               AC = AC + X;

               if(timer == i){
                  print("timer has been met, exiting program");  
                  return 0;   
               }

               PC++;

               break;

            case 11:
               // add the vlaue in Y to AC

               AC = AC + Y;

               if(timer == i){
                  print("timer has been met, exiting program");  
                  return 0;   
               }

               PC++;

               break;

            case 12:
               //subtract the value in X from AC 

               AC = AC - X;

               if(timer == i){
                  print("timer has been met, exiting program");  
                  return 0;   
               }

               PC++;

               break;

            case 13:
               //subtract the value in Y from AC

               AC = AC - Y;

               if(timer == i){
                  print("timer has been met, exiting program");  
                  return 0;   
               }

               PC++;

               break;

            case 14:
               //copy the value in the AC to X

               X = AC;

               if(timer == i){
                  print("timer has been met, exiting program");  
                  return 0;   
               }

               PC++;

               break;

            case 15:
               //copy the value in X to AC

               AC = X;

               if(timer == i){
                  print("timer has been met, exiting program");  
                  return 0;   
               }

               PC++;

               break;
            
            case 16:
               //copy the value from AC to Y

               Y = AC;

               if(timer == i){
                  print("timer has been met, exiting program");  
                  return 0;   
               }

               PC++;

               break;

            case 17:
               //copy the value from Y to AC

               AC = Y;

               if(timer == i){
                  print("timer has been met, exiting program");  
                  return 0;   
               }

               PC++;

               break;

            case 18:
               //copy the value in AC to SP

               SP = AC;

               if(timer == i){
                  print("timer has been met, exiting program");  
                  return 0;   
               }

               PC++;

               break;

            case 19:
               //copy the value from SP to AC

               AC = SP;

               if(timer == i){
                  print("timer has been met, exiting program");  
                  return 0;   
               }

               PC++;

               break;

            case 20:
               //jump to the address

               PC++;

               operand = memoryArr[PC];

               PC = operand;

               if(timer == i){
                  print("timer has been met, exiting program");  
                  return 0;   
               }

               PC++;

               break;

            case 21:
               //jump to the address only if the value in the AC is zero

               PC++;

               //get address from memeory
               operand = memoryArr[PC];

               //if AC is zero then change PC to AC
               if(AC == 0){
                  PC = operand;
               }

               if(timer == i){
                  print("timer has been met, exiting program");  
                  return 0;   
               }

               PC++;

               break;

            case 22:
               //jump to the address only id the value in AC is not zero

               PC++;

               //get "Int" from memory
               operand = memoryArr[PC];

               //switch PC address to the new address
               if( AC != 0){
                  PC = operand;
               }

               if(timer == i){
                  print("timer has been met, exiting program");  
                  return 0;   
               }

               PC++;

               break;

            case 23:
               //push return address on to the stack and jump to the address

               PC++;

               if(timer == i){
                  print("timer has been met, exiting program");  
                  return 0;   
               }

               PC++;

               break;

            case 24:

               PC++;

               if(timer == i){
                  print("timer has been met, exiting program");  
                  return 0;   
               }

               PC++;
               
               break;

            case 25:

               PC++;

               if(timer == i){
                  print("timer has been met, exiting program");  
                  return 0;   
               }

               PC++;

               break;

            case 26:

               PC++;

               if(timer == i){
                  print("timer has been met, exiting program");  
                  return 0;   
               }

               PC++;

               break;

            case 27:
               //Push AC onto stack

               PC++;

               if(timer == i){
                  print("timer has been met, exiting program");  
                  return 0;   
               }

               PC++;

               break;

            case 28:
               //pop from stack into AC

               interupt = true;

               if(timer == i){
                  print("timer has been met, exiting program");  
                  return 0;   
               }

               PC++;

               break;

            case 29:
               //perform system call

               PC++;

               if(timer == i){
                  print("timer has been met, exiting program");  
                  return 0;   
               }

               PC++;

               break;

            case 30:
               //return from system call

               PC++;

               if(timer == i){
                  print("timer has been met, exiting program");  
                  return 0;   
               }

               PC++;

               break;

            case 50:

               PC++;

               if(timer == i){
                  print("timer has been met, exiting program");  
                  return 0;   
               }

               //continue because this is the end of an execution 
               //  but not the end of the enitre program
               continue;

               break;

         }

      }


      exit(3);

//Memory
     default:

      filename [ strcspn(filename, "\r\n") ] = 0;

      FILE *fp = fopen(filename + 3, "r");

      if(fp == NULL){

         printf("Error opening the file, exiting program");
         return 0;
      }

      int memCounter = 0;
      int *readInt = 0;
      char line[100 + 1] = "";

      while (fgets(line, sizeof(line), fp) != NULL) { 

         if(sizeof(line) == 0){
            continue;
         }

         char first = line[0];
         if(first == '.'){

            //get rid of period?

            //change index

            char *slash_slash = strstr(line, "//");

            if (slash_slash) {
               *slash_slash = '\0';
            }

            sscanf(slash_slash, "%d", readInt);

            memCounter = *(readInt);
            
         }
         else{
            char *slash_slash = strstr(line, "//");

            if (slash_slash) {
               *slash_slash = '\0';
            }

            sscanf(slash_slash, "%d", readInt);

            //input processed integer into array and increase address counter
            memoryArr[memCounter] = *(readInt);
            memCounter++;
         }
         instructionCount++;
      }

      // char buffer[100];
      // size_t nline = 0;

      // while ((fgets(buffer, sizeof(buffer), fp) != NULL)) {
      //    int temp;
      //    char isPer = getchar();
      //    if(isPer == "."){
      //       sscanf(buffer, "%d", temp);
      //       nline = temp;

      //    }
      //    else(sscanf(buffer, "%d", &memoryArr[nline]) != 1) {
      //       fprintf(stderr, "Line formatting error\n");
      //       exit(EXIT_FAILURE);
      //       ++nline;
      //    }
         



      //send file that has been read into an array to CPU
    

      //printf("Sent %c\n", memoryArr);     /* print it                  */
      write(pipe1[1], &memoryArr, 1);     /* send "A" to child         */
      read(pipe2[0], &memoryArr, 1);      /* read what child sends     */
      printf("Read");     /* print it                  */
   }
}
