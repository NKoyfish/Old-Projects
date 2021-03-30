/* I pledge on my honor that I have not recieved or given any 
 *assistance on this proj 
 *
 *Nicholas Koy : Shankar CMSC216 Project 8
 *This project acts as a unix simulator that makes
 * directories,files (represented by
 * structures) and prints them out in order with ls
 * file and directory are lists and contain references to various things
 * directories point to a parent,subdirectory, and next (used by its parent)
 * files just contain references to the next file in a directory. 
 * Unix structure represents its on independent system and must be init
 * before using and after rmfs is called to function again. Files and Dirs
 * are dynamically allocated and can be removed with no leaks
 */
#include "unix.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*#define DEBUG 1 */

static void deleteDirs(Unix *filesystem, Dir *myCurr, int mode);
static void deleteFiles(Unix *filesystem, Dir *myCurr,int mode);
static int hasNextDir(Unix *filesystem, Dir *myCurr);
static int hasSubDir(Unix *filesystem, Dir *myCurr);
static void pwdHelper(Unix *filesystem, Dir *myCurr);
static int doesDirExist(Unix *filesystem, const char arg[]);
static int doesFileExist(Unix *filesystem, const char arg[]);
			     
/*inits a Unix struct and some fields
*No longer uses dummy values. Improvement from proj8*/

void mkfs(Unix *filesystem){
  if (filesystem != NULL)
    {
      char *name = "root/";
      filesystem->root = malloc(sizeof(Dir));
      filesystem->curr = filesystem->root;
      filesystem->curr->parent = filesystem->root;
      filesystem->prev = filesystem->root;
      filesystem->root->name = malloc(strlen(name)+1);
      strcpy(filesystem->root->name,name);
      filesystem->root->subdir = NULL;
      filesystem->root->files = NULL;
      filesystem->root->next = NULL;
    }
}

/*looks in currents->files for file named arg ret 1 if exists*/

static int doesFileExist(Unix *filesystem, const char arg[])
{
  int answer = 0;
  
  if(filesystem && arg && filesystem->curr)
    {
      File *travel = filesystem->curr->files;
      
      while(travel && travel->name)
	{
	  if(strcmp(arg,travel->name) == 0)
	    answer = 1;
	  
	  travel = travel->next;
	}
    }
  
  return answer;
}

/*looks for a directory named args starting from curr>subdir ret 1 if found*/

static int doesDirExist(Unix *filesystem, const char arg[]){
  int answer = 0;
  Dir *current = filesystem->curr->subdir;
  if (filesystem != NULL && filesystem->curr->subdir != NULL)
    {
      /*loops in a subdir and changes answer to 1 if arg is found*/
      
      while (current)
	{
	  if (strcmp(current->name, arg) == 0)
	    answer = 1;
	  
	  current = current->next;
	}
    }
  
  return answer;
}

/*adds a Dir named arg in increasing order */

int mkdir(Unix *filesystem,const char arg[])
{
  int answer = 0;

  /*Error cases as defined (should be all)*/
  
  if(filesystem == NULL || arg == NULL || (strcmp(arg,"") == 0 ||
    strcmp(arg,".") == 0 || strcmp(arg,"..") == 0 || strcmp(arg,"/") == 0
    || strchr(arg,'/') != NULL ) || (filesystem->curr->subdir != NULL &&
   doesDirExist(filesystem,arg)))
    return answer;
  
  if (arg && filesystem && !doesDirExist(filesystem, arg)
      && !doesFileExist(filesystem,arg)){
    
    Dir *current = filesystem->curr->subdir;
    Dir *add = malloc(sizeof(Dir));
    Dir *travel = filesystem->curr->subdir;
    Dir *prev = NULL;
    add->next = NULL;
    add->subdir = NULL;
    add->files = NULL;
    add->parent = filesystem->curr;
    add->name = malloc(strlen(arg)+1);
    strcpy(add->name,arg);

    if (current == NULL)
      {
	filesystem->curr->subdir = add;
	answer = 1;
      }
     else if (filesystem != NULL && current->next == NULL)
       {
	 /*Aware this specific condition could be handled in the
	  *next else case but too lazy to change */
	 
	  /*File add's name comes before the first subdir*/
	 
	  if (strcmp(add->name,current->name) < 0)
	    {
	      add->next = current;
	      filesystem->curr->subdir = add;
	    }
	  
	  else
	    {
	      /*File add's name is after the first subdir*/

	      current->next = add;
	    }
	  
	  answer = 1;

	}
    
    else if (current != NULL)
      {
	/*Loop that locates the directory with a "higher ordered" name */
	
	travel = current;
	
	while (travel->next && strcmp(add->name,travel->name) > 0)
	  {
	    prev = travel;
	    travel = travel->next;
	  }
	
	if (prev != NULL && strcmp(prev->name,arg) < 0 && strcmp(travel->name,arg) > 0)
	  {
	    prev->next = add;
	    add->next = travel;
	    answer = 1;
	  }
	
	else /*prev is NULL*/
	  {
	    if (strcmp(travel->name,add->name) > 0)
	      {
		add->next = travel;
		filesystem->curr->subdir = add;
	      }
	    
	    else
	      {
		travel->next = add;
	      }
	    
	    answer = 1;
	  }
      }
   
  }
  
  return answer;
}

/*touch checks if a file named args already exists before 
 *adding a new file named args 
 *to the curr->subdirectory's list of files in order*/

int touch(Unix *filesystem, const char arg[])
{
  int answer = 0;
  File *add = NULL,*travel = NULL,*prev = NULL;
  
  /*Multiple return statements but TRYING to minimize it*/
  
  if (filesystem && arg &&
      (doesFileExist(filesystem,arg) ||
       strcmp(arg,".") == 0 ||  strcmp(arg,"..") == 0 ||
       strcmp(arg,"/") == 0)) return 1;
     
  if (filesystem && filesystem->curr && arg &&
     !doesDirExist(filesystem,arg) && !doesFileExist(filesystem,arg) &&
     strchr(arg,'/') == NULL && strcmp(arg,"") != 0 && strchr(arg,'.') == NULL)
    {
      /*safe to malloc a file since one named
       *arg is legal and doesnt exist yet*/
      
      add = malloc(sizeof(File));
      add->next = NULL;
      
      /* allocates mem for name and assigns add->name */
      
      if( arg[0] != '.' && strlen(arg) > 0){
	add->name = malloc(strlen(arg)+1);
	strcpy(add->name,arg);
      }

      /*case if no files in subdir*/
      
      if (filesystem != NULL && filesystem->curr->files == NULL)
	{
	  filesystem->curr->files = add;
	  answer = 1;
	}
      else if (filesystem != NULL &&
	       filesystem->curr->files->next == NULL)
	{
	  /*File add's name comes after the first file in FS->curr->files->next*/
	  
	  if (strcmp(arg,filesystem->curr->files->name) > 0)
	    filesystem->curr->files->next = add;
	  
	  else
	    {/*File add's name is before the first element*/
	      add->next = filesystem->curr->files;
	      filesystem->curr->files = add;
	    }
	  
	  answer = 1;
	  
	}
      
      else if (filesystem != NULL && filesystem->curr->files)
	{
	  /*Loop that locates the directory with a "higher ordered" name */
	  
	  travel = filesystem->curr->files;
	  
	  while(travel && strcmp(add->name,travel->name) > 0)
	    {
	      prev = travel;
	      travel = travel->next;
	    }
	  
	  if(prev == NULL)
	    {
	      add->next = filesystem->curr->files;
	      filesystem->curr->files = add;
	      answer = 1;
	    }
	  
	  if(prev != NULL)
	    {
	      prev->next = add;
	      add->next = travel;
	      answer = 1;
	    }
	  
	}
      
    }
  return answer;
}

/*returns 1 if successfully changed directories or if arg wasnt an error case*/

int cd(Unix *filesystem, const char arg[])
{
  int answer = 0;
  if (filesystem && filesystem->curr && arg)
    {
      char *twodot = "..",*root = "/", *onedot = ".",*empty = "";
      Dir *travel = NULL;

      /*the folloowing if else statements set curr and prev accordingly*/
      
      if (strcmp(arg,root) == 0)
	{
	  filesystem->curr = filesystem->root;
	  filesystem->prev = filesystem->root;
	  answer = 1;
	}
      
      else if (strcmp(arg,twodot) == 0)
	{
	  filesystem->curr = filesystem->curr->parent;
	  answer = 1;
	  #ifdef DEBUG
	  printf(" .. now The current dir is %s \n",filesystem->curr->name);
	  #endif
	}
      
      /*valid calls no need to change any ptrs*/
      
      else if (strcmp(arg,empty) == 0) answer = 1;
      else if (strcmp(arg,onedot) == 0) answer = 1;

      else if (doesDirExist(filesystem,arg) == 1)
	{
	  travel = filesystem->curr->subdir;
	  
	  while (travel)
	    {
	      if (strcmp(travel->name,arg) == 0)
		{ 
		  filesystem->prev = travel->parent;
		  filesystem->curr = travel;
		  answer =1;
		}
	      
	      travel = travel->next;
	      
	    }
	}
    }
  
  return answer;
  
}

static void pwdHelper(Unix *filesystem, Dir *myCurr)
{
 if(filesystem && filesystem->curr)
    {
      if(myCurr && strchr(myCurr->name,'/') == NULL)
	{
	  pwdHelper(filesystem,myCurr->parent);
	  printf("/%s",myCurr->name);	  
	}
      
    }
 
}
void pwd(Unix *filesystem)
{
  if (filesystem && filesystem->curr &&
      strchr(filesystem->curr->name,'/') == NULL)
    {
      pwdHelper(filesystem,filesystem->curr);
    }
  
  else if(filesystem->curr && strchr(filesystem->curr->name,'/') != NULL)
    printf("/");
  
  printf("\n");
}


/*returns 1 if legal name and filesystem. 0 if error case*/
/* prints out the current's subdirectory and files in order*/
int ls(Unix *filesystem, const char arg[])
{
  char *onedot = ".",*root = "/", *twodot = "..";
  int answer = 0,condition = 1;
  Dir *dirTrav = NULL;
  File *fileTrav = NULL;
  Dir *tempDir = NULL;
  if (filesystem != NULL && filesystem->curr != NULL && arg)
    {
      /*depending on arg dirTrav and fileTrav are set to various things*/
      if ((strcmp(arg,root) == 0))
	{
	  fileTrav = filesystem->root->files;
	  dirTrav = filesystem->root->subdir;
	  answer = 1;
	}
      
      else if (strcmp(arg,onedot) == 0 ||  strcmp(arg,"") == 0)
	{
	  fileTrav = filesystem->curr->files;
	  dirTrav = filesystem->curr->subdir;
	  answer = 1;
	}
      
      else if ((strcmp(arg,twodot) == 0))
	{
	  tempDir = filesystem->curr->parent;
	  fileTrav = tempDir->files;
	  dirTrav = tempDir->subdir;
	  answer = 1;
	  
	  #ifdef DEBUG
	  printf("The current dir is %s \n",tempDir->name);
	  #endif
	}
      
      else if (doesDirExist(filesystem,arg) == 1)
	{
     /*if arg is a subdirectory we go to that subdir and print contents*/
	  dirTrav = filesystem->curr->subdir;
	  tempDir = dirTrav;
	  
	  while (dirTrav && condition)
	    {
	      if (strcmp(dirTrav->name,arg) == 0)
		{
		  dirTrav=dirTrav->subdir;
		  fileTrav = tempDir->files;
		   
		  answer = 1;
		  condition = 0; /*exit the loop*/
		}
	      
	      else
		{
		  tempDir = tempDir->next;
		  dirTrav = dirTrav->next;
		}
	      
	    }
	  
	}
      
      else if (doesFileExist(filesystem,arg) == 1)
	{
	  printf("%s\n",arg);
	  return 1;
	  /*exit the function immediately after finding and printing a file named arg*/
	}

      /*My implementation necessitates a "slow" comparison sort / print*/
	while (dirTrav || fileTrav)
	  {
	    if (dirTrav && fileTrav)
	      {
		if (strcmp(dirTrav->name,fileTrav->name) < 0)
		  {
		    if (strchr(dirTrav->name,'/') == NULL && strlen(dirTrav->name) > 0)
		      printf("%s/\n",dirTrav->name);
		    
		    dirTrav = dirTrav->next;
		    answer = 1;
		}
		
		else 
		  {
		    if (strchr(fileTrav->name,'/') == NULL)
		      printf("%s\n",fileTrav->name);
		    fileTrav = fileTrav->next;
		    answer = 1;
		  }
		
	      }
	    else if (dirTrav && fileTrav == NULL)
	      {
		if (strchr(dirTrav->name,'/') == NULL && strlen(dirTrav->name) > 0)
		  printf("%s/\n",dirTrav->name);
		
		dirTrav = dirTrav->next;
		answer = 1;
		
	      }
	    
	  else if (dirTrav == NULL && fileTrav && fileTrav->name != NULL)
	    {
	      if (strchr(fileTrav->name,'/') == NULL)
		printf("%s\n",fileTrav->name);
	      
	      fileTrav = fileTrav->next;
	      answer = 1;
	    }
	    
	}
	
    }
  
  return answer;
}

/*used by helper to det if a Dir has a Subdir
 * Returns 1 if subdir exists 0 otherwise*/

static int hasSubDir(Unix *filesystem, Dir *myCurr)
{
  int answer = 0;
  
  if (filesystem && myCurr && myCurr->subdir)
    answer = 1;

  return answer;
}

/*used by helper to det if a Dir has a next Dir
 * Returns 1 if ->next exists 0 otherwise
 */

static int hasNextDir(Unix *filesystem, Dir *myCurr)
{
  int answer = 0;
  
  if (filesystem && myCurr && myCurr->next)
    answer = 1;

  return answer;
}

/*  helper function which deletes ALL of Unix's files stemming root->subdir
 *  or ALL files stemming from myCurr (inclusive) and its subdirs
 *  logical steps for this function.
 *  Start at root->subdir, check if files exists and free/delete them
 *  immediately. And importantly set myCurr->files to NULL to eliminate
 *  ptr. THEN (not if else) check if a subdir exists, if so call the func
 *  again (using recursion but with muCurr->subdir as the location)
 *  THEN ( not if else) check if myCurr->next exists AND mode. If
 *  mode = 1 call func with myCurr->next as the location. Otherwise no more
 *  files to remove since it should only delete  curr files;
 */

static void deleteFiles(Unix *filesystem, Dir *myCurr,int mode)
{
  File *head = NULL;
  File *headDelete = NULL;
  if (hasSubDir(filesystem, myCurr))
    {
      deleteFiles(filesystem,myCurr->subdir,1);
    }
  
  if (mode)
    {
      /*shouldnt be deleting the next dir's file if 0*/
      
      if(hasNextDir(filesystem,myCurr))
	{
	  deleteFiles(filesystem,myCurr->next,1);
	}
    }
  if (filesystem && myCurr)
    {
      headDelete = myCurr->files;
    }
  if (head == NULL && headDelete != NULL)
    {
      while (headDelete)
	{
	  head = headDelete;
	  headDelete = headDelete->next;
	  #ifdef DEBUG
	  printf("freeing and nulling %s's file: %s\n",myCurr->name,head->name);
	  #endif
	  free(head->name);
	  free(head);
	}
      
      myCurr->files = NULL; /*In theory freed every file first
			     *and no longer a dangling pointer*/
    }
  
}

/* Depending on the mode will delete all dirs (1)
 * or a certain Dir (0) and free + reassign pointers
 * Deletes from subdir of myCurr and also ensures 
 * existing files are freed before deleting a dir
 */

static void deleteDirs(Unix *filesystem, Dir *myCurr, int mode)
{
  Dir *head = NULL;
  Dir *headTravel = NULL;
  if (filesystem && myCurr) {
    head = myCurr->subdir;
    headTravel = myCurr->subdir;
    
    if (hasSubDir(filesystem,myCurr))
      {
	#ifdef DEBUG
	printf("subdir found\n");
	#endif
	deleteFiles(filesystem,myCurr->subdir,1);
	deleteDirs(filesystem,myCurr->subdir,1);
      }
    
    if (mode)
      {
	if(hasNextDir(filesystem,myCurr))
	  {
	    #ifdef DEBUG
	    printf("next dir found\n");
	    #endif
	    deleteFiles(filesystem,myCurr->next,1);
	    deleteDirs(filesystem,myCurr->next,1);
	  }
      }
    
    while (headTravel)
      {
	#ifdef DEBUG
	printf("freeing a dir: %s\n",headTravel->name);
	#endif
	head = headTravel;
	headTravel = headTravel->next;
	free(head->name);
	free(head);
	myCurr->subdir = NULL;
      }
  }
}

/* removes a possibly existing file or directory named arg
 * from the curr->subdir->files or curr->subdir list. 
 * Importantly frees the file or dir
 * and reassigns pointers according to specified conditions
 * returns 1 if arg existed 
 */
int rm(Unix *filesystem, const char arg[])
{
  int  answer = 0;
  File *fileTrav,*prev = NULL;
  Dir * head = NULL,*temp = NULL;
  if (filesystem && arg)
    {
      if (strcmp(arg,"") == 0 || strcmp(arg,".") == 0 || strcmp(arg,"..") == 0
	 || strcmp(arg,"/") == 0) return answer;

      if (doesDirExist(filesystem,arg))
        {
	  head = filesystem->curr->subdir;
	  
	  if (strcmp(arg,head->name) == 0)
	    {
	      temp = head->next;
	      filesystem->curr->subdir = temp;
	      answer = 1;
	      deleteFiles(filesystem,head,0);
	      deleteDirs(filesystem,head,0);
	      free(head->name);
	      free(head);
	      head = NULL;
	    }
	  
	  else {
	    
	    head = filesystem->curr->subdir;
	    
	    while (strcmp(head->name,arg) != 0)
	      {
		temp = head;
		head = head->next;
	      }
	    
	    #ifdef DEBUG
	    printf("head is : %s\n",head->name);
	    #endif
	   
	    if (temp)
	      temp->next = head->next;
	    
	    answer = 1;
	    deleteFiles(filesystem,head,0);
	    deleteDirs(filesystem,head,0);
	    free(head->name);
	    free(head);
	    head = NULL;
	  }
	  
	}
      
      else if (doesFileExist(filesystem,arg))
	{
	  /*Due to the nature of a file its easier to remove it iteratively*/
	  fileTrav = filesystem->curr->files;
	  
	  while (strcmp(fileTrav->name,arg) != 0)
	    {
	      prev = fileTrav;
	      fileTrav = fileTrav->next;
	    }
	  
	  /*keep going thru loop until names match*/
	  
	    if (prev)
	      {
		prev->next = fileTrav->next;
		free(fileTrav->name);
		free(fileTrav);
	      }
	    
	    else if (prev == NULL)
	      {
		/*the file to be deleted was the first thing
		* so we need to reassign pointer*/
		
		filesystem->curr->files = fileTrav->next;
		free(fileTrav->name);
		free(fileTrav);
		fileTrav = NULL;
	      }
	    
	    answer = 1;
	    
	}
      

    }

  return answer;
}

void rmfs(Unix *filesystem)
{
  deleteFiles(filesystem,filesystem->root,1);
  deleteDirs(filesystem,filesystem->root,1);
  
  #ifdef DEBUG
  printf("freeing filesystem root name and root\n");
  #endif
  
  free(filesystem->root->name);
  free(filesystem->root);
  filesystem->curr = NULL;
  filesystem->prev = NULL;
  filesystem->root = NULL;
}
