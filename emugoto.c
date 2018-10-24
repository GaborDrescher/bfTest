#include <stdint.h>
#include <stdio.h>

void emulate(const uint8_t *restrict convprog, const uint32_t *restrict brackets, uint16_t *restrict memory)
{
	uint32_t di = 0;
	uint32_t ip = 0;

	void *array[] = {
		&&label_0,
		&&label_1,
		&&label_2,
		&&label_3,
		&&label_4,
		&&label_5,
		&&label_6,
		&&label_7,
		&&label_8
	};

	goto *array[convprog[ip]];

	label_0:
		di += 1;
		ip += 1;
		goto *array[convprog[ip]];
	label_1:
		di -= 1;
		ip += 1;
		goto *array[convprog[ip]];
	label_2:
		memory[di] += 1;
		ip += 1;
		goto *array[convprog[ip]];
	label_3:
		memory[di] -= 1;
		ip += 1;
		goto *array[convprog[ip]];
	label_4:
		putchar(memory[di]);
		ip += 1;
		goto *array[convprog[ip]];
	label_5:
		memory[di] = getchar();
		ip += 1;
		goto *array[convprog[ip]];
	label_6:
		if(memory[di] == 0) ip = brackets[ip];
		ip += 1;
		goto *array[convprog[ip]];
	label_7:
		if(memory[di] != 0) ip = brackets[ip];
		ip += 1;
		goto *array[convprog[ip]];
	label_8:
		return;
}
