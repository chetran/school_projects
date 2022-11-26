#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

int count_bulls(int guess, int answer);
int count_cows_and_bulls(int guess, int answer);
bool digit_is_in(int number, int digit);
int n_digits(int number);

int main(void)
{
    srand((unsigned int) time(NULL));
    int x = 3;
    int *y = &x;

    printf("%p\n", y);
    
    
}

int count_bulls(int guess, int answer)
{
    int count = 0;
    int digit_guess;
    int digit_answer;
    int i = 0;
    
    // Change to the length i guess but later. 
    while (i < 4)
    {
        digit_guess = guess % 10;
        digit_answer = answer % 10;
        if (digit_guess == digit_answer)
        {
            count++;
        }
        guess /= 10;
        answer /= 10;
        i++;
    }

    return count;
}

int count_cows_and_bulls(int guess, int answer)
{
    int buffer = answer;
    int count = 0;
    int digit_guess;
    int digit_answer;
    int i = 0;
    
    // Change to the length i guess but later. 
    while (i < 4)
    {
        digit_guess = guess % 10;
        printf("digit_guess : %i\n", digit_guess);
        digit_answer = buffer % 10;
        printf("digit_answer : %i\n", digit_answer);
        if (digit_guess != digit_answer)
        {
            printf("Is the number in it? : %i\n", digit_is_in(answer, digit_guess));
            if (digit_is_in(answer, digit_guess) == true)
            {
                count++;
            }
        }
        guess /= 10;
        buffer /= 10;
        i++;
    }

    return count;

}

bool digit_is_in(int number, int digit)
{
    int length = n_digits(number);
    
    for (int i = 0; i < length; i++)
    {
        if (number % 10 == digit)
        {
            return true;
        }
        number /= 10;
        
    }
    
    return false;
}

int n_digits(int number) {
   int count = 0;

   while (number > 0)
   {
       number /= 10;
       count++;
   }

   return count;

}