#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

typedef struct Node
{
	char identifier[100];
	struct Node *next;
}
Node;

char line[100];

int is_operator(char c)
{
	switch (c)
	{
		case '+':
			printf("%c - Addition Operator\n", c);
			return 1;
		case '-':
			printf("%c - Subtraction Operator\n", c);
			return 1;
		case '*':
			printf("%c - Multiplication Operator\n", c);
			return 1;
		case '/':
			printf("%c - Division Operator\n", c);
			return 1;
		case '=':
			printf("%c - Assignment Operator\n", c);
			return 1;
		case ',':
			printf("%c - Comma Operator\n", c);
			return 1;
		case ';':
			printf("%c - Semicolon\n", c);
			return 1;
	}

	return 0;
}

int is_keyword(char token[])
{
	if (strcmp(token, "void") == 0 || strcmp(token, "main") == 0 || strcmp(token, "int") == 0 || strcmp(token, "long") == 0 || strcmp(token, "float") == 0)
	{
		return 1;
	}

	return 0;
}

int is_integer(char token[])
{
	for (int i = 0; i < strlen(token); i++)
	{
		if (isdigit(token[i]))
		{
			return 1;
		}
	}

	return 0;
}

int is_identifier_in_list(Node *head, char token[])
{
	Node *current = head;
	while (current != NULL)
	{
		if (strcmp(current->identifier, token) == 0)
		{
			return 1;
		}
		current = current->next;
	}
	return 0;
}

void add_identifier(Node **head, char token[])
{
	Node *new_node = (Node *)malloc(sizeof(Node));
	strcpy(new_node->identifier, token);
	new_node->next = NULL;

	if (*head == NULL)
	{
		*head = new_node;
	}
	else
	{
		Node *current = *head;
		while (current->next != NULL)  // Traverse until the last node
		{
			current = current->next;
		}
		current->next = new_node;
	}
}


void main()
{
	char c;
	FILE *f = fopen("input.txt", "r");
	Node *head = NULL;

	while (fgets(line, sizeof(line), f))
	{
		int flag1 = 0;
		for (int i = 0; i < strlen(line); i++)
		{
			if (line[i] == '/' && line[i + 1] == '/')
			{
				flag1 = 1;
				break;
			}       
		}
		if (flag1)
		continue;        

		int flag2 = 0;
		for (int i = 0; i < strlen(line); i++)
		{
			if (line[i] == '/' && line[i + 1] == '*')
			{
				while (fgets(line, sizeof(line), f))
				{
					for (int j = 0; j < strlen(line); j++)
					{
						if (line[j] == '*' && line[j + 1] == '/')
						flag2 = 1;
					}

					if (flag2)
					break;
				}
			}
		}
		if (flag2)
		continue;

		char token[100];
		int index = 0;
		strcpy(token, "");

		for (int i = 0; i < strlen(line); i++)
		{
			if (is_operator(line[i]) || line[i] == ' ' || line[i] == '\t' || line[i] == '\n')
			{
				if (strcmp(token, "") != 0)
				{
					if (is_keyword(token))
					{
						printf("%s - Keyword\n", token);
					}
					else if (is_integer(token))
					{
						printf("%s - Number\n", token);
					}
					else
					{
						if (!is_identifier_in_list(head, token))
						{
							printf("%s - Identifier\n", token);
							add_identifier(&head, token);
						}
					}
					
					strcpy(token, "");
					index = 0;
				}
			}
			else  
			{
				token[index++] = line[i];
				token[index] = '\0';
			}
		}
	}

	fclose(f);
}