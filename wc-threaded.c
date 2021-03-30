#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <string.h>
/* (c) Larry Herman, 2019.  You are allowed to use this code yourself, but
 * not to provide it to anyone else.
 */

/* Similar to wc.c in regards that it
 *  Counts the number of words, lines, and characters in the files whose
 * names are given as command-line arguments.  If there are no command-line
 * arguments then the line, word, and character counts will just be 0.
 * Mimics the effects of the UNIX "wc" utility 
 * but uses threads to quickly calculate
 */


typedef struct arg_pass
{
  int wc_lines;
  int wc_chars;
  int wc_words;
}Arg_pass;

static void* wc(void* arg)
{
  char ch, next_ch, *filename = NULL;
  Arg_pass *argreturn = malloc(sizeof(Arg_pass));
  int lines = 0, words = 0, chars = 0;
  
  FILE *fp = NULL;

  /* sem_wait(&mutex); */
  filename= (char *)arg;
    fp= fopen(filename, "r");  /* open that file */
    
    /* silently ignore any problems trying to open files */
    if (fp != NULL) {
      lines= words= chars= 0;

      /* read each file one character at a time, until EOF */
      ch= fgetc(fp);
      while (!feof(fp)) {
        next_ch= fgetc(fp);  /* look ahead and get the next character */
        ungetc(next_ch, fp);  /* unread the next character (see Chapter 15) */

        /* update the counts as needed every time a character is read */

        /* a newline means the line count increases */
        if (ch == '\n')
          lines++;

        /* if the current character is not whitespace but the next character
           is, or if the current character is not whitespace and it is the
           last character in the input, the word count increases */
        if (!isspace(ch) && (isspace(next_ch) || feof(fp)))
          words++;

        /* increasing the character count is a no-brainer */
        chars++;

        ch= fgetc(fp);
      }

      argreturn->wc_lines = lines;
      argreturn->wc_words = words;
      argreturn->wc_chars = chars;

      
      fclose(fp);
      
    }
   
    
    pthread_exit ((void *)argreturn);
    free(argreturn);
}

int main(int argc, char *argv[]) {

  pthread_t *wc_threads = NULL;
  int words = 0, lines = 0, chars = 0;
  void *pthreadcount = malloc(sizeof(Arg_pass));
  int count2 = 1;
 
  wc_threads = malloc((argc-1)*(sizeof(pthread_t)));
  
  if (wc_threads == NULL)
    {
      return -1; /*malloc failed so we quit*/
    }
  
  for (count2 = 1; count2 < argc; count2++)
    {
      pthread_create(&wc_threads[count2-1],NULL,wc,(void *)argv[count2]);
    }

   for (count2 = 1; count2 < argc; count2++)
    {
      pthread_join(wc_threads[count2-1],&pthreadcount);

      /*join the threads and update our mainthread structure by adding each
       *field of pthread's returned structure
       */
      lines += ((Arg_pass *)pthreadcount)->wc_lines;
      chars += ((Arg_pass *)pthreadcount)->wc_chars;
     words += ((Arg_pass *)pthreadcount)->wc_words;
      free(pthreadcount);
     
    }

   for (count2 = 0; count2 < argc;count2++)
     free(&wc_threads[count2]);
  
   printf("%4d %4d %4d\n",lines,words,chars);
   
  
   
   return 0;
}
