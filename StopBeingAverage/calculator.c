//
// Created by Fernando Rosales on 9/12/24.
//


#include <stdio.h>

int main(void)
{
    float number1, number2, operation;

    printf("Give me a number: ");
    scanf("%f", &number1);

    printf("Give me another number: ");
    scanf("%f", &number2);

    operation = number1 + number2;

    printf("%.0lf\n", operation);

    operation = number1 - number2;

    printf("%.0lf\n", operation);


    operation = number1 * number2;

    printf("%.0lf \n", operation);

    operation = number1 / number2;

    printf("%lf \n", operation);




    return 0;
}