%{
    #include <stdio.h>
    #include <stdlib.h>

    int yylex(void);
    void yyerror(const char *s);
%}

%token NUMBER
%left '+' '-'
%left '*' '/'
%left UMINUS

%%
expression:
	expression '+' expression
	| expression '-' expression
	| expression '*' expression
	| expression '/' expression
	| '-' expression %prec UMINUS
	| '(' expression ')'
	| NUMBER
	;
%%

int main()
{
	printf("Enter an arithmetic expression:\n");
	if (yyparse() == 0)
	{
		printf("Valid arithmetic expression.\n");
	}
	else
	{
		printf("Invalid arithmetic expression.\n");
	}
	return 0;
}

void yyerror(const char *s)
{
    
}

int yylex(void)
{
	int c;

	while ((c = getchar()) == ' ' || c == '\t' || c == '\n');

	if (c >= '0' && c <= '9')
	{
		ungetc(c, stdin);
		scanf("%d", &yylval);
		return NUMBER;
	}

	return c;
}
