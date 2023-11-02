User
Input Format

The first line of each test file contains a single integer n, the length of the string array s.

Each of the next  n lines contains a string s[i] . 
Constraints
2<=n<=9
1<=s[i]<=10
s[i] only contains lowercase English Alpabits 

Output Format

Print each permutation as a list of space-separated strings on a single line.

Sample Input 0

2
ab
cd
Sample Output 0

ab cd
cd ab
Sample Input 1

3
a
bc
bc
Sample Output 1

a bc bc
bc a bc
bc bc a
Explanation 1

This is similar to the note above. Only three of the six permutations are printed to avoid redundancy in output.
/******************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int next_permutation(int n, char **s) {
    // Find the first element from the right that is smaller than the element to its right
    int i = n - 2;
    while (i >= 0 && strcmp(s[i], s[i + 1]) >= 0) {
        i--;
    }
    
    // If no such element is found, this is the last permutation
    if (i < 0) {
        return 0;
    }
    
    // Find the smallest element to the right of the first element and greater than the first element
    int j = n - 1;
    while (j > i && strcmp(s[j], s[i]) <= 0) {
        j--;
    }
    
    // Swap the first and second elements
    char *temp = s[i];
    s[i] = s[j];
    s[j] = temp;
    
    // Reverse the elements to the right of the first element
    int left = i + 1;
    int right = n - 1;
    while (left < right) {
        temp = s[left];
        s[left] = s[right];
        s[right] = temp;
        left++;
        right--;
    }
    
    return 1; // Next permutation exists
}


int main()
{
	char **s;
	int n;
	scanf("%d", &n);
	s = calloc(n, sizeof(char*));
	for (int i = 0; i < n; i++)
	{
		s[i] = calloc(11, sizeof(char));
		scanf("%s", s[i]);
	}
	do
	{
		for (int i = 0; i < n; i++)
			printf("%s%c", s[i], i == n - 1 ? '\n' : ' ');
	} while (next_permutation(n, s));
	for (int i = 0; i < n; i++)
		free(s[i]);
	free(s);
	return 0;
}

