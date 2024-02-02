#include "monty.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

/* Function to push an element onto the stack */
void push(stack_t **stack, unsigned int line_number)
{
    char *argument;
    int value;
    stack_t *new_node = malloc(sizeof(stack_t));

    /* Check if there is an argument */
    if (!stack || !line_number)
    {
        fprintf(stderr, "L%d: usage: push integer\n", line_number);
        exit(EXIT_FAILURE);
    }

    argument = strtok(NULL, " \n\t");

    /* Check if argument is provided */
    if (!argument || !isdigit(*argument))
    {
        fprintf(stderr, "L%d: usage: push integer\n", line_number);
        exit(EXIT_FAILURE);
    }

    value = atoi(argument);

    /* Create a new node */

    if (!new_node)
    {
        fprintf(stderr, "Error: malloc failed\n");
        exit(EXIT_FAILURE);
    }

    new_node->n = value;
    new_node->prev = NULL;
    new_node->next = *stack;

    if (*stack)
        (*stack)->prev = new_node;

    *stack = new_node;
}

/* Function to print all values on the stack */
void pall(stack_t **stack, unsigned int line_number)
{
    stack_t *temp = *stack;

    (void)line_number;

    while (temp)
    {
        printf("%d\n", temp->n);
        temp = temp->next;
    }
}
