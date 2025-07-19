%{
    #include <stdio.h>
    #include <ctype.h>

    int yylex(void);
    void yyerror(const char *s);
%}

%token IDENTIFIER

%%
input:
	IDENTIFIER { printf("Valid identifier.\n"); exit(0); }
	;
%%

int main()
{
	printf("Enter an identifier:\n");
	if (yyparse() != 0)
	{
		printf("Invalid identifier.\n");
		return 1;
	}
	return 0;
}

void yyerror(const char *s)
{

}

int yylex(void)
{
	int c;
	char str[100];
	int i = 0;
	while ((c = getchar()) == ' ' || c == '\t' || c == '\n');
	if (isalpha(c))
	{
		str[i++] = c;
		while ((c = getchar()) != '\n' && c != EOF)
		{
			if (isalnum(c))
			{
				str[i++] = c;
			}
			else
			{
				ungetc(c, stdin);
				break;
			}
		}
		str[i] = '\0';
		return IDENTIFIER;
	}

	return 0;
}
