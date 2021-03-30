/*Nicholas Koy Project 5 10/8/19
 *
 *I pledge on my honor that I have not been given or recieved any
 *unauthorized assistance on this assignment
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "student.h"

typedef struct Student{
  char* name;
  unsigned int id;
  float shoe_size;
}myStudent;

Student *new_student(const char name[],unsigned int id, float shoe_size){
  Student *newStudent;
  if(name != NULL)
    {/*if the name isnt null point to a new memadrs dedicated to student*/
      newStudent = malloc(sizeof(Student)); 
      newStudent->name = malloc(sizeof(name)*strlen(name));
     
      strcpy(newStudent->name,name);
    }
  else
    {
      newStudent = malloc(sizeof(Student));
      newStudent->name = malloc(sizeof(char));
      strcpy(newStudent->name,"");
    }

  (*newStudent).id = id;
  (*newStudent).shoe_size = shoe_size;
    
  return newStudent;
}

unsigned int get_id(Student *const student){
  unsigned int id = 0;
  if(student)
    id = (*student).id;
  return id;
}
unsigned int has_id(Student *const student, unsigned int id){
  unsigned int answer = 0;
  if(student && (*student).id == id)
    answer = 1;
  return answer;
}
unsigned int has_name(Student *const student,const char name[]){
  int answer = 0;

  if(student && name != NULL)
    if(strcmp((*student).name,name) == 0) answer = 1;
  return answer;  
}
float get_shoe_size(Student *const student){
  float shoe_size = 0.0;
  if(student)
    shoe_size = (*student).shoe_size;
  return shoe_size;
}
void change_shoe_size(Student *const student,float shoe_size){
  if(student)
    {
      student->shoe_size = shoe_size;
    }
}
void change_name(Student *const student,const char name[]){
  if(student)
    {
      if(name)
	{
	  free(student->name);
	  student->name = malloc(sizeof(name));
	  strcpy(student->name,name);
	}
      else strcpy(student->name,"");
    }
}
void copy_student(Student *student1, Student *const student2){
  if(student1 && student2){
    free(student1->name);
    student1->name = malloc(sizeof(student2->name)*strlen(student2->name));
    strcpy(student1->name,student2->name);
    student1->shoe_size = student2->shoe_size;
    student1->id = student2->id;
  }
}
