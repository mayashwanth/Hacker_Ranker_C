In this challenge, you will use logical bitwise operators. All data is stored in its binary representation. 
The logical operators, and C language, use  to represent true and  to represent false. T
he logical operators compare bits in two numbers and return true or false,  or , for each bit compared.

Bitwise AND operator & The output of bitwise AND is 1 if the corresponding bits of two operands is 1.
 If either bit of an operand is 0, the result of corresponding bit is evaluated to 0. It is denoted by &.

Bitwise OR operator | The output of bitwise OR is 1 if at least one corresponding bit of two operands is 1.
It is denoted by |.

Bitwise XOR (exclusive OR) operator ^ The result of bitwise XOR operator is 1 if the corresponding bits of two operands are opposite. 
It is denoted by .
Function Description

Complete the calculate_the_maximum function in the editor below.

calculate_the_maximum has the following parameters:

int n: the highest number to consider
int k: the result of a comparison must be lower than this number to be considered
Prints

Print the maximum values for the and, or and xor comparisons, each on a separate line.

Input Format

The only line contains  space-separated integers,  and .

Constraints

Sample Input 0

5 4
Sample Output 0

2
3
3
Explanation 0



All possible values of  and  are:


The maximum possible value of  that is also  is , so we print  on first line.

The maximum possible value of  that is also  is , so we print  on second line.

The maximum possible value of  that is also  is , so we print  on third line.

/*********************************************************************/

#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
//Complete the following function.


void calculate_the_maximum(int n, int k)
{
  //Write your code here.
  int cnt1=0,cnt2=0,cnt3=0;
    for(int i=1;i<=n;i++)
    {
        for(int j=i+1;j<=n;j++)
        {
           if((i&j)>cnt1 && (i&j)<k)
           cnt1=i&j;
           if((i|j)>cnt2 && (i|j)<k)
            cnt2=i|j;
            if((i^j)>cnt3 && (i^j)<k)
            cnt3=i^j;
            
        }
    }
    printf("%d\n%d\n%d\n",cnt1,cnt2,cnt3);
}

int main() {
    int n, k;
  
    scanf("%d %d", &n, &k);
    calculate_the_maximum(n, k);
 
    return 0;
}
