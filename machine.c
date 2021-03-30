/*
Nicholas Koy Project 2
I pledge on my honor that I did not recieve or distribute any 
unauthorized assistance on this assessment

These methods are used by a Coffee Cake program that dissassembles
instructions and stores values in registers r0 - r6.
 */
#include <stdio.h>
#include "machine.h"
const int max = 0xEFFFFFC0; /*opcode 14 registry has 19 ones and reg 1 7 */
/* Word is defined as an int (4 bytes) */
int print_instruction(Word instruction){
  int reg1mask = 0x1C0,reg2mask =0x38,reg3mask =0x7;
  /*111000000  111000  111*/
  int opcode = instruction >> 28;
  int reg1 = (instruction & reg1mask) >> 6;
  int reg2= (instruction & reg2mask) >> 3;
  int reg3 = (instruction & reg3mask);
  /*this condition checks instr where R0 or R6 are being changed*/
  int registry = (instruction << 4) >> 13;
  if(is_valid_instruction(instruction)) /*max possible*/
    {
      if(opcode == 0)
	printf("plus  R%d  R%d  R%d",reg1,reg2,reg3);
      else if(opcode == 1)
	printf("diff  R%d  R%d  R%d",reg1,reg2,reg3);
      else if(opcode == 2)
	printf("mult  R%d  R%d  R%d",reg1,reg2,reg3);
      else if(opcode == 3)
	printf("quot  R%d  R%d  R%d",reg1,reg2,reg3);
      else if(opcode == 4)
	printf("mod   R%d  R%d  R%d",reg1,reg2,reg3);
      else if(opcode == 5)
	printf("and   R%d  R%d  R%d",reg1,reg2,reg3);
      else if(opcode == 6)
	printf("or    R%d  R%d  R%d",reg1,reg2,reg3);
      else if(opcode == 7)
	printf("not   R%d  R%d",reg1,reg2);
      else if(opcode == 8)
	printf("br    R%d  %05d",reg1, registry);
      else if(opcode == 9)
	printf("read  R%d",reg1);
      else if(opcode == 10)
	printf("wrt   R%d",reg1);
      else if(opcode == 11)
	printf("move  R%d  R%d",reg1,reg2);
      else if(opcode == 12)
	printf("lw    R%d  %05d",reg1,registry);
      else if(opcode == 13)
	printf("sw    R%d  %05d",reg1,registry);
      else if(opcode == 14)
	printf("li    R%d  %05d",reg1,registry);
    }
  return 0;
}
int disassemble(const Word program[], unsigned int instr_num,
                unsigned int data_num)
{
  int answer = 1;
  int data = 0x0;
  int size = instr_num + data_num;
  int i;
  if(program != NULL && instr_num >= 1 && size < 3072){
    for(i = 0; i < size; i++)
      {
	if(i < instr_num && is_valid_instruction(program[i]))
	  {
	    printf("%04x: ",data);
	    data+=4;
	    print_instruction(program[i]);
	    printf("\n");
	  }
	if(i >= instr_num)
	  {
	    printf("%04x: %08x\n",data, program[i]);
	    data+=4;
	  }
      }
  }
  else answer = 0;
  return answer;
}

int is_valid_instruction(Word word){
  int answer = 0;
  int opcode = word >> 28;
  int reg1mask = 0x1C0,reg2mask =0x38,reg3mask =0x7;
  int reg1 = (word & reg1mask) >> 6;
  int reg2= (word & reg2mask) >> 3;
  int reg3 = (word & reg3mask);
  int memory = (word & 0xFFFFE00) >> 9;
  int memcond = (memory%4 == 0 && memory < 12288); /* 1 if valid */
  int cond1 = (reg1 != 0 && reg1 != 6); /* 1 if both reg1 not 1 or 6 */
  int instrcond = (reg1 != 7 && reg2 != 7 && reg3 !=7 && opcode != 15
		   && word < 0xEFFFFFC0);

  if(instrcond)
    {
      if((opcode == 0 || opcode == 1||opcode == 2 || opcode == 3 ||opcode == 4
	  || opcode == 5 || opcode == 6 || opcode == 7 || opcode == 9) && cond1)
	answer = 1;
      /*no attempts to change R0 or R6 above */
      /*ops below access memory with 8,10,13 canuse r1 regardls of val*/
      if(opcode == 8 && memcond) answer = 1;
      if(opcode == 10 && memcond) answer = 1;
      if(opcode == 11 && cond1 ) answer = 1;
      if(opcode == 12 && memcond && cond1) answer = 1;
      if(opcode == 13 && memcond) answer = 1;
      if(opcode == 14 && memcond && cond1) answer = 1;
    }

  return answer;
}
int relocate(const Word program[], unsigned int instr_num,
             unsigned int data_num, int offset, Word relocated_program[],
             unsigned short *const instrs_changed)
{
  int answer = 0;
  int k;
  int count = 0;
  int memory = 0;
  int memory2 = 0;
  if(program != NULL && relocated_program != NULL && instrs_changed
     && instr_num >= 1 && offset%4 == 0 && instr_num + data_num < 3072)
    {
      for(k = 0; k < instr_num+data_num;k++) /* iterate thru program*/
	{
	  if( k < instr_num)
	    {
	      if(is_valid_instruction(program[k]))
		{
		  /*instruction at k is valid  */
		  int opcode = program[k] >> 28;
	  
		  if(opcode != 8 && opcode != 12 && opcode != 13 && opcode != 14) 
		    { /*instructions that dont involve memory just get copied */
		      relocated_program[k] = program[k];
		    }
		  else
		    {
		      memory = ((program[k] & 0xFFFFE0) + (offset << 9));
		      memory2 = ((program[k] & 0xFFFFE0) >> 9) + offset;
		      if((memory >> 9) < 12288 && memory2 >= 0)
			{
			/* memory is less than 12288 and adding offset to memory2 is >= 0  */
			relocated_program[k] = (opcode << 28);
			relocated_program[k] |= memory;
		   
			count++;
			*instrs_changed = count;
			answer = 1;
		        }
		      else
			{
			  k = instr_num + data_num;
			  answer = 0;
			}
		    }
		}
	      else k= 3073;
	    }
	  else relocated_program[k] = program[k];
	}
    }
  return answer;

}
