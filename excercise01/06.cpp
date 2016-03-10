#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_INPUT_SIZE 100

bool is_palindrome(const char *string, const int begin = 0, int end = -1)
{
    /* initialise parameter */
    if(end == -1) end = strlen(string) - 1;

    /* base case */
    if(string[begin] != string[end]) return false;
    if(begin >= end) return true;

    /* recursive case */
    return is_palindrome(string, begin + 1, end - 1);
}

int main(void)
{
    printf("palindrome checker\n");

    char word[MAX_INPUT_SIZE];
    printf("Enter word= "); scanf("%s", word);

    printf("%s is %spalindrome.\n", word, is_palindrome(word) ? "" : "not " );
    return 0;
}
