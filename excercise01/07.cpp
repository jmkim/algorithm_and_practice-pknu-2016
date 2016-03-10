#include <stdio.h>

#define MAX_INPUT_SIZE 100

int compare(const char *str1, const char *str2)
{
    /* base case */
    if(str1[0] < str2[0]) return -1; /* str1 is earlier than str2 */
    if(str1[0] > str2[0]) return 1;
    if(str1[1] == '\0' && str2[1] == '\0') return 0; /* str(s) have only one character */

    /* recursive case */
    return compare(str1 + 1, str2 + 1);
}

int main(void)
{
    printf("dictionary compare\n");

    char word_one[MAX_INPUT_SIZE], word_two[MAX_INPUT_SIZE];
    printf("Enter word one= "); scanf("%s", word_one);
    printf("Enter word two= "); scanf("%s", word_two);

    printf("Result is %d\n", compare(word_one, word_two));
    return 0;
}
