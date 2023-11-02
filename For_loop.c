Task

For each integer  in the interval  (given as input) :

If , then print the English representation of it in lowercase. That is "one" for , "two" for , and so on.
Else if  and it is an even number, then print "even".
Else if  and it is an odd number, then print "odd".
Input Format

The first line contains an integer, .
The seond line contains an integer, .

Constraints


Output Format

Print the appropriate English representation,even, or odd, based on the conditions described in the 'task' section.

Note: 

Sample Input

8
11
Sample Output

eight
nine
even
odd

/*****************************************************/

#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>



int main() 
{
    int a, b;
    char *arr[]={"","one","two","three","four","five","six","seven","eight","nine"};
    scanf("%d\n%d", &a, &b);
  	// Complete the code.
    for(int i=a;i<=b;i++)
    {
        if(i<=9)
        {
           for(int j=i;j<=i;j++)
           printf("%s\n",arr[i]);
        }
        else if(i>9) 
        {
        if(i%2==0)
        printf("even\n");
        else
        printf("odd\n");
        }
    }
    return 0;
}

