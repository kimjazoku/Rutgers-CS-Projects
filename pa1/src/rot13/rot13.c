#include <stdio.h>
#include <stdlib.h>
int main (int argc, char *argv[]) {
    /* Write a program rot13 that encodes its argument using rot-13 and prints the results, followed by
a newline character. You MAY assume that rot13 will receive exactly one argument, but it is good
practice to check whether the number of arguments is correct. Only scenarios with one argument
may be tested */
    char *input = argv[1];
    for(int i = 0; input[i]!= '\0'; i++) {
        if(input[i] >= 'A' && input[i] <= 'Z') {
            input[i] = (input[i] -'A' + 13) % 26 + 'A'; //wraparound for uppercase letters
        } else if(input[i] >= 'a' && input[i] <= 'z') {
            input[i] = (input[i] - 'a' + 13) % 26 + 'a'  ; //wraparound for lowercase letters
        }
    }
    printf("%s\n", input);
    return 0;
    }