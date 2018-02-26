#include<stdio.h>
#define paster( n ) printf( "token" #n " = %d", token  ##  n )  

int token9 = 100;  
  
int main()  
{  
   paster(9);  
}  
