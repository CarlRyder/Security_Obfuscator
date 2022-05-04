// Made by Y. Sendov. May 2022

#define _CRT_SECURE_NO_WARNINGS
#define DEFAULT_ERROR -1
#define PASSWORD_SIZE 64
#define CONSTANT 9
#define TRUE 1
#define FALSE 0

#include <stdio.h>
#include <windows.h>
#include <string.h>

struct lines
{
	char* input;
	char* password;
};

int correct_pass(struct lines* strings)
{
	if (strcmp(strings->input, strings->password) == 0) return 1;
	else return 0;
}

int get_size(FILE* pointer)
{
	fseek(pointer, 0, SEEK_END);
	int size = ftell(pointer);
	rewind(pointer);
	return size;
}

void xor_pass(struct lines* strings, int flag)
{
	if (flag == FALSE)
	{
		for (int i = 0; i < strlen(strings->password); i++) strings->password[i] ^= CONSTANT;
	}
	else
	{
		for (int i = 0; i < strlen(strings->input); i++) strings->input[i] ^= CONSTANT;
	}
}

void read_pass(struct lines* strings)
{
	FILE* file = fopen("pass.txt", "r");
	if (file == NULL)
	{
		system("cls");
		printf("File Opening error.\nFile was expected: \"pass.txt\".\nCheck the source directory!\n");
		exit(DEFAULT_ERROR);
	}
	int pass_size = get_size(file);
	char* pass = (char*)malloc(sizeof(char) * pass_size);
	if (pass != NULL)
	{
		for (int i = 0; i < pass_size; i++) pass[i] = fgetc(file);
		pass[pass_size] = '\0';
	}
	fclose(file);
	strings->password = pass;
	xor_pass(strings, FALSE);
}

void input_pass(struct lines* strings)
{
	char input[PASSWORD_SIZE] = { 0 };
	printf("Enter the password: ");
	fgets(input, PASSWORD_SIZE, stdin);
	input[strcspn(input, "\n")] = 0;
	fseek(stdin, 0, SEEK_END);
	strings->input = input;
}

void check_pass(struct lines* strings)
{
	input_pass(strings);
	xor_pass(strings, TRUE);
	if (correct_pass(strings) == 1)
	{
		printf("The password is correct. Access is allowed.\n");
	}
	else
	{
		printf("The password is incorrect. Try again!\n");
		check_pass(strings);
	}
}

int main()
{
	struct lines strings = { NULL, NULL };
	read_pass(&strings);
	check_pass(&strings);
	system("pause");
}