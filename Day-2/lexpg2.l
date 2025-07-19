%{
    #include <stdio.h>
    #include <string.h>
%}

%%
^[a-zA-Z0-9._]+@[a-zA-Z0-9]+\.[a-zA-Z]{2,4}	{ printf("\nEmail address is valid.\n\n"); }
.*	{ printf("\nEmail address invalid.\n\n"); }
%%

int main()
{
	char input[256];

	while (1)
	{
		printf("Enter an email address (or '0' to quit): ");
		fgets(input, sizeof(input), stdin);
		input[strcspn(input, "\n")] = '\0';
        
		if (strcmp(input, "0") == 0)
		{
			break;
		}
        
		YY_BUFFER_STATE buffer = yy_scan_string(input);
		yy_switch_to_buffer(buffer);
		yylex();
		yy_delete_buffer(buffer);
	}

	return 0;
}

int yywrap()
{
	return 1;
}

