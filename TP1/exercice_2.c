#include <stdio.h>
#include <stdlib.h>
#define TAB_SIZE 512
#define COUNT 7

void print_line(int* line)
{
    int i = 0;
    while(line[i] != 0)
    {
        printf("%i ", line[i]);
        i++;
    }
    printf("\n");
}

int* line_calc(int* line, int* new_line)
{
    int i = 0;
    int j = 0;
    int count = 1;
    while(line[i] != 0)
    {
        if (line[i] == line[i+1]) {
            count++;
        } else {
            new_line[j] = count;
            new_line[++j] = line[i];
            count = 1;
            j++;
        }

        i++;
    }
    return new_line;
}


int main(void)
{
    int start_line[TAB_SIZE] = {3};
    print_line(start_line);

    int* current_line = calloc(TAB_SIZE,sizeof(int));
    line_calc(start_line, current_line);
    print_line(current_line);

    for (int i = 0; i < (COUNT - 2); i++) {
        int* next_line = calloc(TAB_SIZE,sizeof(int));
        line_calc(current_line, next_line);
        print_line(next_line);

        free(current_line);
        current_line = next_line;
    }

    free(current_line);

    return 0;
}
