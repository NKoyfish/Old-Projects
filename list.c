/* I pledge on my honor that I did not give or recieve any
 * unauthorized assistance on this assessment
 *
 * Nicholas Koy CMSC216 Project 7 Shankar
 * This program defines methods that operate on a
 * list structure that stores an int, dummy head, and ptr to a
 * next node. If a list is passed in as NULL for any of the methods
 * 0 is returned.
 */
#include <stdio.h>
#include <stdlib.h>
#include "list.h"
/*Initializes a list struct and allocates space*/
/*list->head should be NULL*/
void init(List *const list)
{
  if (list != NULL)
    { 
      list->modhead = 0;
      /*modhead should only be 1 if a list has 1 element */
      /*modhead is essentially a dummy head that determines how*/
      /*other functions operate list*/
    }
}
/*Gets the size of a list*/
int size(List *const list)
{
  int answer = 0;
  if (list && list->head)
    {
      Node *temp = list->head;
      while (temp != NULL)
	{
	  answer++;
	  temp= temp->next;
	}
    }
  return answer;
}
/*Allocates a node for list->next to point to returns 1 if successful*/
int append(List *const list, int new_value)
{
  Node *newNode;
  if (list && size(list) == 0 && list->modhead == 0)
    {
/*Frees list's head ptr and pts it to a newly allocated head with new_val */
      free(list->head);
      newNode = malloc(sizeof(newNode));
      newNode->data = new_value;
      newNode->next = NULL;
      list->head = newNode;
      list->modhead = 1; /*For size to correctly work*/
      return 1;
    }
  else if(list && size(list) >= 1 && list->modhead == 1)
    {/*Otherwise just go to the end of a list and*/
     /* point the last elm to newly allc node */
      Node *temp = list->head;
      while (temp->next)
	{
	  temp = temp->next;
	}
      newNode = malloc(sizeof(newNode));
      newNode->data = new_value;
      newNode->next = NULL;
      temp->next = newNode;

      return 1;
    }
  else return 0;
}
/*allocates a newnode and sets the list's head to it returns 1 if success*/
int prepend(List *const list, int new_value)
{
  int answer = 0;
  Node *newNode,*temp;
  if (list && size(list) == 0 && list->modhead == 0)
    {/*Case 1 head not modified yet indicated by modhead */
      temp = list->head;
      free(list->head);
      newNode = malloc(sizeof(Node));
      newNode->data = new_value;
      list->head = newNode;
      list->head->next = temp;
      list->modhead= 1;/*Head is being modded*/
      newNode->next = list->head;
      list->head = newNode;
      list->head->next = NULL;
      answer = 1;
    }
  else if (list && list->head && size(list) >= 1 && list->modhead == 1)
    {/*Case 2 just pnt head to a new node after storing into temp*/
      newNode = malloc(sizeof(Node));
      temp = list->head;
      newNode->data = new_value;
      newNode->next = temp;
      list->head = newNode;
      answer = 1;
    }
   return answer;
}
/*prints the nodes of a list followed by a space and up until */
/* the second to last node. \n at the end  */
void print(List *const list)
{
  if (list && list->head)
    {
      Node *curr = list->head;
      while (curr->next != NULL)
	{
	  printf("%d ",curr->data);
	  curr = curr->next;
	}
      printf("%d\n", curr->data);
    }
}
/*Looks through a list and returns the pos of the node with value stored*/
/*Indexes starting at 0*/
int find(List *const list, int value)
{
  int count = 0;
  int foundat = -1;
  Node *curr;
  if (list)
    {
      curr = list->head;
      while(curr != NULL)
	{
	if (curr->data == value)
	  {
	    foundat = count;
	    curr = NULL;
	  }
	else
	  {
	    curr=curr->next;
	    count++;
	  }
      }
    } else foundat = 0;
  return foundat;
}

/*Deletes a node at a specified position and reassigns ptrs
 * if list is entered as NULL or invalid pos return 0
 * if successful return 1  */
int delete(List *const list, unsigned int position)
{
  int answer = -1;
  Node *temp;
  Node *store;
  int count = 0;
  if (list && position >= 0 && position <= size(list) -1)
    {
      if (position == 0 && size(list) == 1)/*Case 1*/
	{/*free the head and set list head ptr to null*/
	  free(list->head);
	  list->head = NULL;
	  answer = 1;
	  list->modhead = 0;/*Allow other fns to operate on head*/
	}
      else if (position == 0 && size(list) > 1 && position < size(list))
	{
	  temp = list->head;
	  store = temp->next;
	  temp->next = temp->next->next;
	  free(temp);
	  list->head = store;
	}

      else if (position > 0 && position <= size(list)-1)
	{
	  temp = list->head;
	  store = NULL;
	  if (position == size(list)-1)/*Case 3 delete last elm*/
	    {
	      while (temp->next->next != NULL) temp = temp->next;
	      free(temp->next);
	      temp->next = NULL;
	    }
	  else if (position > 0 && position < size(list) -1)
	    {/*Anything in between 1 (inlc) and size-1*/
	      while (count < position && temp->next)
		{
		  store = temp;
		  temp = temp->next;
		  count++;
		}
	      store->next = temp->next;
	      free (temp);
	    }
	  answer = 1;
	}
    } else answer = 0; /*list was null or pos < 0*/
  return answer;
}
