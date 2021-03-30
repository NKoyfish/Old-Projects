 #include <stdio.h>
/*
Nicholas Koy CMSC216 Shankar
expand.c makes tabs translate better for lengthcheck.c by adding spaces
to an interval of 8 based on the inputs
 */
int expandInput()
{ /*"X 100: */
  char temp;
  int i = 0;
  int lineBlocksize = 0;
  int k =0;
  int count = 0;
  int currLinesize = 0;
  char lineBlock[999];
  int iter2 = 0;

  while (scanf("%c", &temp) != EOF){/* stores each character in a char array  */
    lineBlock[count] = temp;
    lineBlocksize++;
    count++;
  }
  i=0;

  while(i < lineBlocksize){ /*prints out every character stored unless it 
		   is \t where it would space out to the next multiple of 8 */
    if(lineBlock[iter2] != '\t'){
      printf("%c", lineBlock[iter2]);
      currLinesize++;
      iter2++;
      
    }
    else{
      for(k =0; k <=8-currLinesize%8+1;k++)
	{
	  printf(" ");
	}
      currLinesize = 0;
      iter2++;
    }
    i++;
}
  return 0;
}

int main(){
  expandInput();
    return 0;
}
