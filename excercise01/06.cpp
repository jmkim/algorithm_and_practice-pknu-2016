#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_INPUT_SIZE 100

bool is_palindrome(const char *word)
{
    int length = strlen(word);
    char string[length]; /* Should not modify the value of ptr arg. */
    strcpy(string, word);

    /* base case */
    if(length <= 1) return true;
    if(string[0] != string[length - 1]) return false;

    /* recursive case */
    string[length - 1] = '\0';
    return is_palindrome(string + 1);
}

int main(void)
{
    printf("palindrome checker\n");

    char word[MAX_INPUT_SIZE];
    printf("Enter word= "); scanf("%s", word);

    printf("%s is %spalindrome.\n", word, is_palindrome(word) ? "" : "not " );
    return 0;
}
