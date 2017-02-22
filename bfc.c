#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

char *brainfuckToC (int argc, char *argv[]);
void printUsage();
void checkArgs(int argc, char *argv[]);
void checkBrackets(int leftCount, int rightCount);

int main(int argc, char *argv[])
{	
	
	checkArgs(argc, argv);
	char *code = brainfuckToC(argc, argv);
	
	FILE *f = fopen("/tmp/bfctmp.c", "w");
	if (f == NULL)
	{
		printf("Error opening file!\n");
		exit(1);
	}
	fprintf(f, "%s", code);
	fclose(f);
	
	system("rm /tmp/bfctmp &> /dev/null; gcc -Wno-format -o /tmp/bfctmp /tmp/bfctmp.c;");
	
	FILE * exec;
	exec = fopen("/tmp/bfctmp", "r");
	
	if (exec){
		fclose(exec);
		system("/tmp/bfctmp");
	}else{
		printf ("\033[1m\033[31mError:\033[0m Unable to compile the translated C code. Check your .b file.\n");
		exit(EXIT_FAILURE);
	}
	
	
	return 0;
}

void checkArgs(int argc, char *argv[]) {
	if (argc == 1) {
		printf ("\033[1m\033[31mError:\033[0m No arguments passed\n");
		printUsage();
		exit(EXIT_FAILURE);
	} else if (argc > 2) {
		printf ("\033[1m\033[31mError:\033[0m Too many arguments passed\n");
		printUsage();
		exit(EXIT_FAILURE);
	}
}

void printUsage() {
	printf("Usage: ./bfc filename.b\n");
}

char *brainfuckToC (int argc, char *argv[]) {
	int leftBracketCount = 0;
	int rightBracketCount = 0;
	
	int iteration = 0;
	const int cellsize = 30000;
	static char cCode[cellsize];
	
	sprintf(cCode,
		"#include <stdio.h>\n"
		"#include <stdlib.h>\n\n"
		"int main(int argc, char **argv)\n{\n"
		"\tunsigned char *cell = calloc(%d, 1);\n"
		"\tunsigned char *cells = cell;\n"
		"\tif (!cell) {\n"
		"\t\tfprintf(stderr, \"Error allocating memory.\\n\");\n"
		"\t\treturn 1;\n"
		"\t}\n\n", cellsize
	);
	int c;
	FILE *bFile;
	bFile = fopen(argv[1], "r");
	if (bFile) {
		while ((c = getc(bFile)) != EOF) {
			switch (c) {
				printf("%c",c);
				case '>': strcat(cCode, "\t\t++cell;\n"); break;
				case '<': strcat(cCode, "\t\t--cell;\n"); break;
				case '+': strcat(cCode, "\t\t++*cell;\n"); break;
				case '-': strcat(cCode, "\t\t--*cell;\n"); break;
				case '.': strcat(cCode, "\t\tputchar(*cell);\n"); break;
				case '*': strcat(cCode, "\t\tprintf(\"%d\",*cell);\n"); break; // Allows printing the int stored in cell as an integer rather than char
				case '%': strcat(cCode, "\t\tscanf(\"%d\", cell);  \n"); break; // Allows input to be stored as int rather than attempting to convert to ascii
				case ',': strcat(cCode, "\t\t*cell = getchar();\n"); break;
				case '[': strcat(cCode, "\twhile (*cell) {\n"); leftBracketCount++; break;
				case ']': strcat(cCode, "\t}\n"); rightBracketCount++; break;
				case ' ': break;
				default: break;
			}
		}
		fclose(bFile);
	} else {
		printf ("\033[1m\033[31mError:\033[0m Unable to open %s\n", argv[1]);
		exit(EXIT_FAILURE);
	}
	checkBrackets(leftBracketCount, rightBracketCount);
	strcat(cCode, "\tputchar(\'\\n\');\t\n\tfree(cells);\n\treturn 0;\n}\n\n");
	return cCode;
}

void checkBrackets(int leftCount, int rightCount) {
	if (leftCount > rightCount) {
		printf ("\033[1m\033[31mError:\033[0m Extraneous '['\n");
		exit(EXIT_FAILURE);
	} else if (rightCount > leftCount) {
		printf ("\033[1m\033[31mError:\033[0m Extraneous ']'\n");
		exit(EXIT_FAILURE);
	}
}