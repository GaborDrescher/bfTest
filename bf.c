#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

extern void emulate(const uint8_t *restrict convprog, const uint32_t *restrict brackets, uint16_t *restrict memory);

#define N_STACKS (1<<16)
static uint16_t memory[N_STACKS];

//// hello world
//static const char *program =
//"++++++++[>++++[>++>+++>+++>+<<<<-]>+>+>->>+[<]<-]>>.>---.+++++++..+++.>>.<-."
//"<.+++.------.--------.>>+.>++.";

// long-running benchmark programm
static const char *program =
">+>+>+>+>++<[>[<+++>->>>>>>+>+>+>+>++<[>[<+++>->>>>>>+>+>+>+>++<[>[<+++>->>>>"
">>+>+>+>+>++<[>[<+++>->>>>>+++[->+++++<]>[-]<<<<<<]<<]>[-]<<<<<]<<]>[-]<<<<<]"
"<<]>[-]<<<<<]<<]>.";

int main(int argc, char *argv[])
{
	(void)argc;
	(void)argv;

	const uint32_t inputlen = strlen(program);

	// count real programm length
	uint32_t proglen = 0;
	for(uint32_t i = 0; i != inputlen; ++i) {
		switch(program[i])
		{
			case '>':
			case '<':
			case '+':
			case '-':
			case '.':
			case ',':
			case '[':
			case ']':
				proglen += 1;
				break;
			default:
				break;
		}
	}

	uint8_t *convprog = malloc(sizeof(uint8_t) * (proglen+1));
	if(convprog == NULL) {
		fprintf(stderr, "malloc failed\n");
		exit(-1);
	}

	// convert program to range 0 - 7
	uint32_t idx = 0;
	for(uint32_t i = 0; i != inputlen; ++i) {
		uint32_t inc = 1;
		switch(program[i])
		{
			case '>':
				convprog[idx] = 0;
				break;
			case '<':
				convprog[idx] = 1;
				break;
			case '+':
				convprog[idx] = 2;
				break;
			case '-':
				convprog[idx] = 3;
				break;
			case '.':
				convprog[idx] = 4;
				break;
			case ',':
				convprog[idx] = 5;
				break;
			case '[':
				convprog[idx] = 6;
				break;
			case ']':
				convprog[idx] = 7;
				break;
			default:
				inc = 0;
				break;
		}
		idx += inc;
	}

	// end of program symbol
	convprog[proglen] = 8;

	// precompute jump table for loops
	uint32_t *brackets = (uint32_t*)malloc(sizeof(uint32_t) * proglen);
	uint32_t *stack = (uint32_t*)malloc(sizeof(uint32_t) * (proglen+1));
	if(brackets == NULL || stack == NULL) {
		fprintf(stderr, "malloc failed\n");
		exit(-1);
	}

	uint32_t stack_idx = 1;
	for(uint32_t i = 0; i != proglen; ++i) {
		brackets[i] = 0xffffffff;
		if(convprog[i] == 6) {
			stack[stack_idx] = i;
			stack_idx += 1;
		}
		else if(convprog[i] == 7) {
			stack_idx -= 1;
			if(stack_idx == 0) {
				fprintf(stderr, "too many closing brackets\n");
				exit(-1);
			}

			brackets[i] = stack[stack_idx];
			brackets[stack[stack_idx]] = i;
		}
	}

	if(stack_idx != 1) {
		fprintf(stderr, "too few closing brackets\n");
		exit(-1);
	}

	free(stack);

	emulate(convprog, brackets, memory);
	putchar('\n');

	free(brackets);
	free(convprog);

	return 0;
}
