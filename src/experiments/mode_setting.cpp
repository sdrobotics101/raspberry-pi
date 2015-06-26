#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <bitset>
#include <iostream>

int main(int argc, char *argv[])
{
	std::bitset < 8 > mode;
	mode[5] = 1;
	mode[2] = 1;
	mode[0] = 1;
	uint8_t mode8 = mode.to_ulong();
	printf("%d", mode8);
	return EXIT_SUCCESS;
}
