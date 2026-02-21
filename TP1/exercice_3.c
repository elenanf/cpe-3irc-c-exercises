#include <stdio.h>
#define TAB_SIZE 512


float coefficient(float* p1, float* p2)
{
    return (p2[1] - p1[1]) / (p2[0] - p1[0]);
}

int main()
{
    float p1[2] = {-5, -4}; 
    float p2[2] = {13.2, 15.2};

    printf("%f \n", coefficient(p1, p2));
}