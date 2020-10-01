#include <stdio.h>
#include <math.h>

int main(int argc, char *argv[])
{
        int num1 = -1;
        int num2 = -1;
        char op = 'q';
        int result;

        sscanf(argv[1], "%d %c %d", &num1, &op, &num2);
        
	if (num1 == -1 || op == 'q' || num2 == -1)
		printf("Invalid expression: %s", argv[1]);
	else {
		switch(op) {
			case '+':
				result = num1 + num2;
				printf("%s = %d", argv[1], result);
				break; 
			case '-':
				result = num1 - num2;
				printf("%s = %d", argv[1], result);
				break;
			case 'x':
				result = num1 * num2;
				printf("%s = %d", argv[1], result);
				break;
			default :
				printf("Invalid expression: %s", argv[1]);
    			break;
		}
	}
}
