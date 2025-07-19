%{
    #include <stdio.h>
    int vowels = 0;
    int consonants = 0;
%}

%%
[aeiouAEIOU] {vowels++;}
[\t ] {ECHO;}
. {consonants++;}
%%

int main()
{
	FILE *input_file = fopen("input.txt", "r");
	if (input_file == NULL)
	{
		fprintf(stderr, "Could not open input.txt\n");
		return 1;
	}

	yyin = input_file;
	yylex();

	printf("Vowels: %d\n", vowels);
	printf("Consonants: %d\n\n", consonants);

	fclose(input_file);

	return 0;
}

int yywrap()
{
	return 1;
}

