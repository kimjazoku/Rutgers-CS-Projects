#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int top = -1;

char push(char value, char **stack)
{
    stack[++top] = &value;
    return value;
}

char pop(char value, char **stack)
{
    if (top == -1)
    {
        printf("Stack is empty.\n");
        return '\0';
    }
    else
    {
        value = *stack[top];
        stack[top] = NULL;
        top--;
        return value;
    }
}

void open(int top, char **stack)
{
    char **openStack = malloc((top + 1) * sizeof(char *));
    int match = 0; // 0 = false | 1 = true
    for (int i = 0; i <= top; i++)
    {
        if (*stack[i] == '(')
        {
            for (int j = i + 1; j <= top; j++) // this will iterate through the rest of the stack
            {
                if (*stack[j] == ')')
                {
                    match = 1;
                    break; // means that we found a matching closing delimiter
                }
            }
            if (match == 0)
            {
                char value = ')';
                push(value, openStack);
            }
        }
        if (*stack[i] == '[')
        {
            for (int j = i + 1; j <= top; j++) // this will iterate through the rest of the stack
            {
                if (*stack[j] == ']')
                {
                    match = 1;
                    break; // means that we found a matching closing delimiter
                }
            }
            if (match == 0)
            {
                char value = ']';
                push(value, openStack);
            }
        }
        if (*stack[i] == '{')
        {
            for (int j = i + 1; j <= top; j++) // this will iterate through the rest of the stack
            {
                if (*stack[j] == '}')
                {
                    match = 1;
                    break; // means that we found a matching closing delimiter
                }
            }
            if (match == 0)
            {
                char value = '}';
                push(value, openStack);
            }
        }
    }
    for (int i = 0; i <= top; i++)
    {
        printf("open: %c", openStack[i]);
    }
    free(openStack); // free the allocated memory
}

int main(int argc, char *argv[])
{
    /* balance will maintain a stack of open delimiters. Each time a (, [, or { is
    encountered in the input, it will push that delimiter onto the stack. Each time a ), ], or } is
    encountered, balance will pop the top delimiter off the stack and check whether it matches the
    delimiter encountered in the string. If the delimiters do not match, or the stack is empty, balance
    will print the index for the unexpected delimiter and the closing delimiter encountered.
    */
    // define stack
    char **stack = malloc((argc - 1) * sizeof(char *));

    for (int i = 1; i < argc; i++)
    {
        char *currentChar = argv[i];
        stack[i - 1] = currentChar;
        if (*currentChar == '(' || *currentChar == '[' || *currentChar == '{')
        {
            push(*currentChar, stack);
        }
        else if (*currentChar == ')' || *currentChar == ']' || *currentChar == '}')
        {
            pop(*currentChar, stack);
        }
    }

    // check to see if there are any unmatched delimiters
    if (top > -1)
    {
        open(top, stack);
    }

    free(stack); // free the allocated memory
    return 0;
}
