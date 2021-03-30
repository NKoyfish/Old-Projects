 #include <stdio.h>
/*
Nicholas Koy CMSC216 Shankar
lengthcheck.c reads each line of an input and evaluates whether
if each input goes over 80 characters and puts an X
followed by the input's length, a colon, and a whitespace
"X 100: pretend this is 100 chars long" for example 
 */
int readLine()
{ /*"X 100: */
  char temp = 'a';
  int chkline = 0;
  int charSize[999] = { 0 }; 
  int i = 0;
  int lineBlocksize = 0;
  int practicalSize = 0;
  int count = 0;
  char lineBlock[99999]; /* Aware this is bad just didnt
			      know how recycle the values */
  int totalLine = 0;
  int iter2 = 0;
 

  while (scanf("%c", &temp) != EOF)
    {/* stores each character in a char array  */
    if(temp == '\n')
      {
	i++;/*if new line is found we increase the total
	      number of lines for later purposes
	      and we move to a new spot in the charSize
	      array to store the next input's size */
	totalLine++;
      }
    else
      {
	charSize[i]++;
	practicalSize++;
      }
    lineBlock[count] = temp;
    lineBlocksize++;
    count++;
  }
  i=0;
  while(chkline < totalLine){ /*prints the "X ####: "
				structure for each input */
    if(charSize[chkline] >= 100) /*3 spaces need to be dedicated for number  */
      {
	printf("X %d: ",charSize[chkline]);
      }
    else if(charSize[chkline] > 80) /* size greater than 80
				       but not quite 3 digits */
      {
	printf("X  %d: ",charSize[chkline]);
      }
    else if(charSize[chkline] < 80 && charSize[chkline] >= 10)
      /*size between 80 and two decimals  */
      {
	printf("   %d: ",charSize[chkline]);
      }
    else 
      {
	printf("    %d: ", charSize[chkline]); /* the last case where
						  the size of the input is less than 10  */
      }
   
    
    while(i < charSize[chkline])
      { /*prints out every character stored except for \n
	  and skips over \n if found increments chkline by 1 
	  to correctly print the size of the nextinput  */
	printf("%c", lineBlock[iter2]);
	iter2++;
	i++;
      }
    iter2++;
    chkline++;
    i = 0;
    printf("\n");
  }
  return 0;
}

int main(){
  readLine();
    return 0;
}
