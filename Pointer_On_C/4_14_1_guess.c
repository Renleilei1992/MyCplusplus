

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main()
{
	float new_guess;
	float last_guess;
	float number;

	/* 计算一个数的平方根 */
	printf("Plz input the number you want to calculate: ");
	scanf("%f", &number);

	if( number < 0 ){
		printf("Cannot compute the square root of a negative number!\n");
		return EXIT_FAILURE;
	}

	new_guess = 1;
	do{
		last_guess = new_guess;
		new_guess =  ( last_guess + number / last_guess ) / 2;
		printf("%.15e\n", new_guess);
	}while( new_guess != last_guess );

	printf("Square root of %g is %g\n", number, new_guess);

	printf("Square root of %g is %g\n", number, sqrt(number));

	return EXIT_SUCCESS;
}
