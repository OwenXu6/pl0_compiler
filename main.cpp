#include "pl.h"
#include <stdio.h>

void version()
{
	printf("PL/0 compiler/interpreter (%s %s)\n", __TIME__, __DATE__);
}

void help()
{
	printf("usage:\n");
	printf("  pl0 -exec [filename]  | execute file directly.\n");
	printf("  pl0 -debug [filename] | execute file in debug mode.\n");
}

int main(int argc, char* argv[])
{
	if (argc == 1) {
		version();
		help();
		return 0;
	}

	if (argc != 3)
	{
		printf("fatal error: no input file.\n");
		help();
		exit(-1);
	}

	if (strcmp(argv[1], "-exec") && strcmp(argv[1], "-debug"))
	{
		printf("error parameter: %s\n", argv[1]);
		help();
		exit(-1);
	}

	init();
	if (!read_file(argv[2]))
		exit(-1);
	ast result = parse();
	close_file();

	if (!compile_error)
	{

		// Save bytecode to a file
		FILE* bytecode_file = fopen("code.txt", "w");
		if (bytecode_file != NULL) {
			for (int i = 0; i < exec_code.size(); ++i)
				fprintf(bytecode_file, "0x%.8x %s 0x%.8x 0x%.8x\n", i, opcode_name[exec_code[i].opcode], exec_code[i].level, exec_code[i].opnum);
			fclose(bytecode_file);
		}
	}
	else
		exit(0);

	return 0;
}
