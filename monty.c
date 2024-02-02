#define _POSIX_C_SOURCE 200809L

#include "monty.h"
#include <string.h>

int main(int argc, char *argv[])
{
    FILE *file;
    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    unsigned int line_number = 0;
    stack_t *stack = NULL;
    instruction_t instruction = {"push", push};

    /* Check for correct number of arguments */
    if (argc != 2)
    {
        fprintf(stderr, "USAGE: monty file\n");
        exit(EXIT_FAILURE);
    }

    /* Open the file */
    file = fopen(argv[1], "r");
    if (!file)
    {
        fprintf(stderr, "Error: Can't open file %s\n", argv[1]);
        exit(EXIT_FAILURE);
    }

    /* Read the file line by line */
    while ((read = getline(&line, &len, file)) != -1)
    {
        line_number++;
        /* Call function based on opcode */
        strtok(line, "\n");

        if (strcmp(line, "pall") == 0)
            instruction.f(&stack, line_number);
        else if (strcmp(line, "push") == 0)
            push(&stack, line_number);
        else
        {
            fprintf(stderr, "L%d: unknown instruction %s\n", line_number, line);
            exit(EXIT_FAILURE);
        }
    }

    /* Clean up and close the file */
    free(line);
    fclose(file);

    return 0;
}
