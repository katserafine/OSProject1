#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <sys/wait.h>


int main(int argc, char *argv[])
{

    int pipe1[2];

    int PC = 0, SP = 0, IR = 0, AC = 0, X = 0, Y = 0;
    int memoryArr[2000];
    int instructionCount = 0;
    time_t t;
    srand((unsigned) time(&t));
    bool interupt = false;
    int offset;
    bool userMode = true;
    
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

    int timer = atoi(argv[2]);
    
    //exit if timer is zero or less
    if (timer <= 0)
    {    
        printf("Timer is 0 or less, exiting program now");
        return 0;
    }
    
    if (pipe(pipe1) < 0)
    {
        write(STDERR_FILENO, "Pipe failed\n", 12);
        exit(1);
    }
    
    int result = fork();

    if(result == -1){
        write(STDERR_FILENO, "Fork failed\n", 12);
        exit(1);
    }
        
    if(result == 0)
    {

        close(pipe1[1]);

        printf("We are in the CPU \n");

        read(pipe1[0], memoryArr, 2000);
            
        /*

            USER STACK memoryArr[1999]

            SYSTEM STACK memoryArr[999]


        */

        //loop only as far the as the timer will allow you :)
        for(int i = 0; i < 1000; i++){
 
            //read in IR from memory/ initialize operand for safety
            IR = memoryArr[PC];
            int operand = 0;

            //if statement to catch interrupt occurance 
            if(i % timer == 0){

                //timer execution

                //move to 1000 because it says to in insructions for execution
                //  But what do we execute? no body knows 


                //moce stacker pointer to system stack

                //set interupt to true because timer is occurring
                interupt = true;
                userMode = false;
            }

            //Bracketing has been down for testing clarity -- can be removed later   
            switch(IR)
            {
                case 1:
                {
                    //load value into AC   
                    PC++;
                    AC = memoryArr[PC];

                    PC++;
                }
                    break;
                        
                case 2:
                {
                    // load the calue at the address into AC
                    PC++;  
                    operand = memoryArr[PC];    
                    AC = memoryArr[operand];
                        
                    PC++;
                }
                    break;
                        
                case 3:
                {
                    //load the value from address found in this address into the AC
                    PC++;
                        
                    //get address of jump loading spot
                    operand = memoryArr[PC];
                        
                    //get address found within given address
                    operand = memoryArr[operand];
                        
                    //load value from address previously found
                    AC = memoryArr[operand];
 
                    PC++;
                }     
                    break;
                        
                case 4:
                {
                    //load the value address + X into the AC
                        
                    PC++;    
                    operand = memoryArr[PC];
                        
                    offset = operand + X;    
                    AC = memoryArr[offset];
                        
                    PC++;
                }
                    break;
                        
                case 5:
                {
                    //load the value at address + Y into AC
                        
                    PC++;
                        
                    operand = memoryArr[PC];
                    
                    offset = operand + Y;
                    AC = memoryArr[offset];
                    

                    PC++;
                }
                    break;
                        
                case 6:
                {
                    //load from sp + X into the AC
                    offset = SP + X;
                    AC = memoryArr[offset];
                        
                    PC++;
                } 
                    break;
                        
                case 7:
                {
                    //store the value into the address
                        
                    PC++;
                        
                    //get address from memeory
                    operand = memoryArr[PC];
                        
                    //put AC into address given
                    memoryArr[operand] = AC;
                        
                    PC++;
                }
                    break;
                        
                case 8:
                {
                    //get a random int from 1 to 100 and put into AC
                        
                    AC = (rand() % 100);
                        
                    PC++;
                }
                    break;
                        
                case 9:
                {
                    //put port
                    PC++;

                    operand = memoryArr[PC];
                        
                    if(operand == 1){
                              
                        //WRITE AC as int
                        printf("%d", AC);
                            
                    }
                    else{
                            
                        //write AC as char
                        char holder = (char) AC;
                        printf("%c", holder);
                            
                    }
                        
                    PC++;
                }
                    break;
                        
                case 10:
                {
                    //add the calue in X to AC
                        
                    AC = AC + X;
                        
                    PC++;
                }
                    break;
                        
                case 11:
                {
                    // add the vlaue in Y to AC
                        
                    AC = AC + Y;
                        
                    PC++;
                }  
                    break;
                        
                case 12:
                {
                    //subtract the value in X from AC
                        
                    AC = AC - X;
                        
                    PC++;
                }
                    break;
                        
                case 13:
                {
                    //subtract the value in Y from AC
                        
                    AC = AC - Y;
                        
                    PC++;
                }
                    break;
                        
                case 14:
                {
                    //copy the value in the AC to X
                        
                    X = AC;
                        
                    PC++;
                }
                    break;
                        
                case 15:
                {
                    //copy the value in X to AC
                        
                    AC = X;
                        
                    PC++;
                }
                    break;
                        
                case 16:
                {
                    //copy the value from AC to Y
                        
                    Y = AC;
                        
                    PC++;
                }
                    break;
                        
                case 17:
                {
                    //copy the value from Y to AC
                        
                    AC = Y;
                        
                    PC++;
                }
                    break;
                        
                case 18:
                {
                    //copy the value in AC to SP
                        
                    SP = AC;
                        
                    PC++;
                }
                    break;
                        
                case 19:
                {
                    //copy the value from SP to AC
                        
                    AC = SP;
                        
                    PC++;
                }
                    break;
                        
                case 20:
                {
                    //jump to the address
                        
                    PC++;
                        
                    operand = memoryArr[PC];
                        
                    PC = operand;

                }
                    break;
                        
                case 21:
                {
                    //jump to the address only if the value in the AC is zero
                        
                    PC++;
                        
                    //get address from memeory
                    operand = memoryArr[PC];
                        
                    //if AC is zero then change PC to AC
                    if(AC == 0){
                        PC = operand;
                    }
                    else{    
                        PC++;
                    }
                }
                    break;
                        
                case 22:
                {
                    //jump to the address only id the value in AC is not zero
                        
                    PC++;
                        
                    //get "Int" from memory
                    operand = memoryArr[PC];
                        
                    //switch PC address to the new address
                    if( AC != 0){
                        PC = operand;
                    }
                        
                    PC++;
                }
                    break;
                        
                case 23:
                {
                    //push return address on to the USER stack and jump to the address
                        
                    PC++;
                        
                    operand = memoryArr[PC];

                    SP = 999;
                        
                    //push operand (address on to the stack)
                    memoryArr[SP] = operand; //save return address

                    PC++;
                }
                    break;
                        
                case 24:
                {
                    //pop return address from the stack, jump to address
                        
                    PC++;
                        
                    PC = memoryArr[SP];

                    PC++;
                }
                    break;
                        
                case 25:
                {    
                    //increment the value in x

                    PC++;

                    X = X + 1;    

                }
                    break;
                        
                case 26:
                {
                    //Decrement the value in X
                        
                    PC++;
                        
                    X = X - 1;

                    PC++;
                }  
                    break;
                        
                case 27:
                {
                    //Push AC onto stack
                        
                    PC++;

                    memoryArr[SP] = AC;
                        
                    PC++;
                }
                    break;
                        
                case 28:
                {
                    //pop from stack into AC
                        
                    interupt = true;
                        
                    PC++;
                }
                    break;
                        
                case 29:
                {
                    //perform system call
                        
                    PC++;

                    interupt = true;

                    //save PC and PS to SYSTEM stack -- we are in Kernel mode
                    memoryArr[1999] = PC;
                    memoryArr[1998] = SP;

                    PC++;
                }
                    break;
                        
                case 30:
                {
                    //return from system call
                        
                    PC++;

                    //get SP first becasue it is saved second
                    //      holder values for now

                    SP = memoryArr[1998];
                    PC = memoryArr[1999];
                        
                    PC++;
                }
                    break;
                        
                case 50:
                {
                        
                    PC++;
                        
                    //continue because this is the end of an execution
                    //  but not the end of the enitre program
                    continue;
                } 
                    break;
                        
                }
                
            }
            exit(0);
        }
        else{
            FILE *fp;
            fp = fopen(argv[1], "r");
            
            //TODO
            //  process a "." at the beginning of a line
            
            if(fp == NULL){
                
                printf("Error opening the file, exiting program");
                return 0;
            }
            
            int memCounter = 0;
            char line[100 + 1] = "";
            
            while (fgets(line, sizeof(line), fp) != 0) {


                if(sizeof(line) == 0){
                    continue;
                }
                //make temp int variable to get integer
                int number;        
                sscanf(line, "%d", &number);

                //input processed integer into array and increase address counter
                memoryArr[memCounter] = number;

                memCounter++;
                instructionCount++;
            }

            //send file that has been read into an array to CPU
            
            
            printf("writing to pipe \n");
            close(pipe1[0]);
            write(pipe1[1], &memoryArr, 2000);    
            close(pipe1[1]);

            waitpid(-1, NULL, 0);



            
        }
    
}
