#include <stdint.h>
#include <stdio.h>

void emulate(const uint8_t *restrict convprog, const uint32_t *restrict brackets, uint16_t *restrict memory)
{
	uint32_t di = 0;
	uint32_t ip = 0;

	for(;;) {
		switch(convprog[ip]) {
			case 0:
				di += 1;
				ip += 1;
				break;
			case 1:
				di -= 1;
				ip += 1;
				break;
			case 2:
				memory[di] += 1;
				ip += 1;
				break;
			case 3:
				memory[di] -= 1;
				ip += 1;
				break;
			case 4:
				putchar(memory[di]);
				ip += 1;
				break;
			case 5:
				memory[di] = getchar();
				ip += 1;
				break;
			case 6:
				if(memory[di] == 0) ip = brackets[ip];
				ip += 1;
				break;
			case 7:
				if(memory[di] != 0) ip = brackets[ip];
				ip += 1;
				break;
			case 8:
				return;
		}
	}
}
