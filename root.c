#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>
#include <conio.h>
#include <stdbool.h>

// Function references

void capture();
double get_input(int position);
bool range_of_func_check(double x, double k);
double calculate_root(double num, double k, double e);
double custom_power(double a, double b);
bool continue_calculations();
int iteration_num(double num);
 
char* initial_data_exp[3] = {"x (root expresion)", "k (index of the root)", "e (precision, in 0.001 format)"};

bool input_check = false;

int main ()
{
    // Initial data

    double x = 0;
    double k = 0;
    double e = 0;

    int position;

    // Autor and title

    capture();

    // Run programm

    do
    {
        // Get initial data and check whether it is possible to calculate the root

        do
        {
            // Get x (root expression)

            do
            {
                position = 0;
                x = get_input(position);
            } 
            while (!input_check);
            
            // Get k (index of the root)

            do
            {
                position = 1;
                k = get_input(position);
            } 
            while (!input_check);
        } 
        while (!range_of_func_check(x, k) && continue_calculations());

        // Get e (precision)

        do
        {
            position = 2;
            e = get_input(position);
        } 
        while (!input_check);

        // Calculate root

        double y = calculate_root(x, k, e);
    } 
    while (continue_calculations());

    return 0;
}

void capture()
{
    // Author

    printf("\nNadiia Rybak 2023\n");

    // Title

    printf("\nROOT OF A NUMBER\n");

    // Decription

    printf("\nCalculate k-th root of a number with specified precision.\n\n");
}

double get_input(int position)
{
    // Get input

    char input[15];

    printf("\nEnter your %s: ", initial_data_exp[position]);

    scanf("%s", input);

    // Check input

    // Check is that a number

    for (int i = 0; input[i] != '\0'; i++)
    {
        if (isdigit(input[i]) == 0 && input[i] != '.' && input[i] != '-')
        {
            printf("\nYour input is invalid.\n");
            input_check = false;
            return -1;
        }
    }

    input_check = true;

    return atof(input);
}

bool range_of_func_check(double x, double k)
{
    if (k == 0)
    {
        printf("\nIndex of the root cannot be zero.\n");
        return false;
    }

    if (k > 0)
    {
        if (fmod(k, 2.0) == 0)
        {
            if (x < 0)
            {
                printf("\nx shoud be greater or equal to zero.\n");
                return false;
            }
        }
    }
    else
    {
        if (fmod(k, 2.0) == 0)
        {
            if (x <= 0)
            {
                printf("\nx shoud be less than zero.\n");
                return false;
            }
        }
        else
        {
            if (x == 0)
            {
                printf("\nx shoud not be zero.\n");
                return false;
            }
        }
    }

    return true;
}

double custom_power(double a, double b)
{
    double result = 1;

    for (int i = 0; i < b; i++)
    {
        result *= a;
    }

    return result;
}

int iteration_num(double num)
{
    int counter = 0;

    while(num < 1)
    {
        counter++;
        num *= 10;
    }

    return counter;
}

double calculate_root(double num, double k, double e)
{
    double x = num / k; // Initial guess
    double prevX;
    int n = iteration_num(e);

    do {
        prevX = x;
        x = ((k - 1) * x + num / pow(x, k - 1)) / k;
    } 
    while (fabs(x - prevX) > e);

    printf("y = %.*f", n, x);

    return x;
}

bool continue_calculations()
{
    printf("\nDo you want to enter initial data one more time? (enter/esc) \n");

    while(1)
    {
        char response = getch(); 

        if (response == 13)  
        {
            return true;
        }
        else if (response == 27)  
        {
            return false;
        }
    }
}