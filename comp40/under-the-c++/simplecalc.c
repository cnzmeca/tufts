#include <stdio.h>

int main(int argc, char *argv[])
{
	int num1;
	int num2;
	char operator;
	int result;

	sscanf(argv[1], "%d %c %d", &num1, &operator, &num2);
	if (operator != '+' && operator != 'x')
		printf("Invalid expression: %s", argv[1]);
	else
	{
		if (operator == '+')
			result = num1 + num2;
		else
			result = num1 * num2;
		printf("%s = %d", argv[1], result);
	}
}
