/* I pledge on my honor that I have not recieved or given any
 * unauthorized assistance on this project.
 *
 * Nicholas Koy
 * Shankar 216
 *
 *This program simulates UNIX's xargs function where you can 
 *call defined programs in two different modes, line by line
 *which has a -i in argv[1] or standard mode (without "-i")
 *this program looks in stdin and determines what command is to
 *be run and if they are valid. The program forks children 
 * for every line in line by line mode otherwise only 1 fork is
 * called. If a child execs the determined command and it fails
 * the parent will return 1 or 0 accordingly. 0 is no error
 * 1 means an error occured with the command.
 */
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <err.h>
#include <sysexits.h>
#include "safe-fork.h"
#include "split.h"
#include <string.h>

int contains_i(char **argv);

int contains_i(char **argv)
{
  int answer = 0;
  int i = 0;

  while(argv && argv[i])
    {
      if(strcmp(argv[i],"-i") == 0)
	answer = 1;
      i++;
    }
  
  return answer;
  
}


int main(int argc,char **argv) {
  
  int answer = 0, stop = 0, status = 0;
  pid_t child_pid;
  char line[1000] = {""}, lineBefore[1000] = {""};

  if (argc == 1) /*default option echo one big line*/
    {
      
      while (scanf("%s",line) != EOF && stop == 0)
	{
	  strcpy(lineBefore,line);
	  child_pid = safe_fork();
	  
	  if (child_pid > 0)
	    {     
	     waitpid(child_pid,&status,0);
	     if (!WIFEXITED(status))
	       answer = 1;
	   }
	  
	  else

	    if (child_pid == 0)
	      {
		stop = 1;
		if (scanf("%s",line) != EOF)
		  {
		    execlp("/bin/echo","echo","-n",lineBefore,"",NULL);
		  }
		
		else execlp("/bin/echo","echo",line,NULL); 
	      }
	 

	}

      
   
    }

  else if (argc == 2 && strcmp(argv[1],"-i") == 0)
    /*default echo but mult lines*/
    {
      
      while (fgets(line,sizeof(line),stdin))
	{
	  
	  child_pid = safe_fork();
	  
	  if (child_pid > 0)
	    {
	      
	      waitpid(child_pid,&status,0);
	      
		  if(!WIFEXITED(status))
		    answer = 1;
	    }
	  
	  else
	    
	    if (child_pid == 0)
	      {
		stop = 1;
		execlp("/bin/echo","echo","-n",line,NULL);
		exit(1);
	      }
	}	
      
    }
  else if (argc == 2 && strcmp(argv[1],"-i") != 0)
    {
      
       while(scanf("%s",line) != EOF && stop == 0)
	{
	
	 child_pid = safe_fork();

	 if (child_pid > 0)
	   {
	     waitpid(child_pid,&status,0);
	     if(WIFEXITED(status))
	       answer = 1;
	   }
	 else
	 if (child_pid == 0)
	   {
	     stop = 1;
	     execlp(argv[1],argv[1],line,NULL);
	     exit(1);
	   }   
	}
    }

   else if (argc > 2)
    {

      if (contains_i(argv))
	{
	  
	  while (scanf("%s",line) != EOF && stop == 0)
	    {
	      
	      child_pid = safe_fork();
	      
	      if (child_pid > 0)
		{
		  
		  waitpid(child_pid,&status,0);
		  
		  if(WIFEXITED(status))
		    answer = 1;
		
		}
	      
	      else
		
		if (child_pid == 0)
		  {
		  
		    stop = 1;
		    execlp(argv[1],argv[1],line,NULL);
		  }
	      
	    }
	  
	}
      
    }
  
  return answer;
}

