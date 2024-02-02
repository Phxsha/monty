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
	char *opcode;
	instruction_t instruction;

	if (argc != 2)
	{
		fprintf(stderr, "USAGE: monty file\n");
		exit(EXIT_FAILURE);
	}
	file = fopen(argv[1], "r");
	if (!file)
	{
		fprintf(stderr, "Error: Can't open file %s\n", argv[1]);
		exit(EXIT_FAILURE);
	}
	while ((read = getline(&line, &len, file)) != -1)
	{
		line_number++;
		opcode = strtok(line, " \t\n");

		if (opcode)
		{
			instruction.opcode = opcode;
			instruction.f = NULL;
			if (strcmp(opcode, "pall") == 0)
			{
				instruction.f = pall;
			}
			else if (strcmp(opcode, "push") == 0)
			{
				instruction.f = push;
			}
		}
		else
		{
			fprintf(stderr, "L%d: unknown instruction %s\n", line_number, opcode);
			exit(EXIT_FAILURE);
		}
		if (instruction.f)
		{
			instruction.f(&stack, line_number);
		}
	}
	free(line);
	fclose(file);

	return (0);
}
