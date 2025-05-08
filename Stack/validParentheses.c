#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#define MAX_STACK_SIZE 10000

// Stack pour stocker des caractères
typedef struct
{
    char content[MAX_STACK_SIZE];
    unsigned nb_values;
} stack;

stack *stack_new(void)
{
    stack *s = malloc(sizeof(stack));
    if (!s)
        return NULL;
    s->nb_values = 0;
    return s;
}

void stack_free(stack *s)
{
    free(s);
}

int stack_push(stack *s, char c)
{
    if (s->nb_values >= MAX_STACK_SIZE)
        return -1;
    s->content[s->nb_values++] = c;
    return 0;
}

char stack_pop(stack *s)
{
    if (s->nb_values == 0)
        return '\0';
    return s->content[--(s->nb_values)];
}

char stack_top(stack *s)
{
    if (s->nb_values == 0)
        return '\0';
    return s->content[s->nb_values - 1];
}

int stack_is_empty(stack *s)
{
    return s->nb_values == 0;
}

char getParentheseInverse(char c)
{
    switch (c)
    {
    case ')':
        return '(';
        break;
    case '}':
        return '{';
        break;
    case ']':
        return '[';
        break;
    default:
        return EOF;
    }
}

bool isValid(char *s)
{
    stack *stk = stack_new();
    if (!stk)
        return false;

    for (char *c = s; *c; c++)
    {
        if (*c == '(' || *c == '[' || *c == '{')
        {
            stack_push(stk, *c);
        }
        else if (*c == ')' || *c == ']' || *c == '}')
        {
            if (stack_is_empty(stk))
            {
                stack_free(stk);
                return false;
            }
            char top = stack_pop(stk);
            if (top != getParentheseInverse(*c))
            {
                stack_free(stk);
                return false;
            }
        }
    }

    bool valid = stack_is_empty(stk);
    stack_free(stk);
    return valid;
}