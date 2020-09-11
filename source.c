#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
   int pfds[2];
   char buf[30];
   int result;

   //create a timer -- comes in as imnput from command line

   result = pipe(pfds);
   if (result == -1)
      exit(1);

   result = fork();
   if (result == -1)
      exit(1);

   if (result == 0) 
   {

      //Memory reads the file

      printf("CHILD (MEMORY): writing to the pipe\n");
      write(pfds[1], "test", 5);
      printf("CHILD: exiting\n");
      _exit(0);
   }
   else
   {
      printf("PARENT (CPU): reading from pipe\n");
      read(pfds[0], buf, 5);
      printf("PARENT: read \"%s\"\n", buf);
      waitpid(-1, NULL, 0);
   }
}