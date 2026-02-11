#include <stdio.h>
#include <math.h>
#define NUMBER 1170701532

int find_smallest_divisor(int number)
{
    for (int i = 2; i <= sqrt(number); i++)
    {
        if (number%i == 0) {
            return i;
        }
    }
    return number;
};

int main(void)
{
    int result = NUMBER;
    while (result != 1)
    {
        printf("%i ", find_smallest_divisor(result));
        result = result / find_smallest_divisor(result);
    }

}
