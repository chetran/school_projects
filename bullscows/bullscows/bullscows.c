/*
 *     The bulls and cows game
 *
 *     (Read ASSIGNMENT1.txt carefully before you start coding)
 *
 *     NOTE: Only int's, if, while and functions needed!
 */

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

#define TEST false     // If true run tests (only), else run program, change to "false" only after
                      // implementing functions
#define DEBUG false    // If true, print number to guess to make debugging easier

// ----------- Declare functions used in main ----------

// Generates a 4-digit random number with no repeated digits
// (digits in range 1-9)
int get_random_4digit();

// Returns number of bulls in guessed number
int count_bulls(int guess, int answer);

// Returns number of bulls and cows in guessed number
// Comment: Counting both bulls and cows together is simpler to implement,
// instead of just counting cows. The number of cows you get by combining
// this function and count_bulls
int count_cows_and_bulls(int guess, int answer);

// Get input from player
int get_player_guess();

// Testing of functions, see far below
void test();

bool duplicates(int number);
int occurrences(int number, int digit);
int n_digits(int number);
bool digit_is_in(int number, int digit);
bool valid_guess(int guess);
void game();
int play_again();
void game_instruction();
void built_in_debugger(int answer);



/*
 *  Program starts here
 */
int main(void) {
  
    srand((unsigned int) time(NULL));     // Init random number generator
    
    game_instruction();
    
    // ----- The game loop ------
    int selection = 1;
    while (selection != 0)
    {
        game();
        selection = play_again();
    }

    return 0;
}

// ------- Functions definitions --------------------------------

// This one's for free...
int get_player_guess() {
    bool valid = false;
    int guess;
    while (valid == false)
    {
        printf("Guess > ");
        scanf("%d", &guess);
        valid = valid_guess(guess);
    }
    return guess;
}


// Put the remaining function definitions here
int get_random_4digit()
{
    int number;
    bool done = false;

    while (!done)
    {
        // Get a random number
        number = rand() % 10000;
        //printf("I got this number: %i\n", number);

        // We want 4 digits and no zeros
        if (n_digits(number) == 4 && occurrences(number, 0) == 0)
        {
            // Makes sure its not the same, if there are duplicates the function will return true but we dont want "done" to be done. The exclationmark inverts the return of duplicates.
            done = !duplicates(number);
        }
    }

    return number;
}

bool duplicates(int number)
{
    int buffer = number;
    int i = 0;
    while(i < 4)
    {
        // Loops through each digit in number
        int digit = buffer % 10;

        if (occurrences(number, digit) > 1)
        {
            return true;
        }
        buffer /= 10;
        i++;
    }

    return false;
}

// Remake of "is digit in number" but with while and returning amount
int occurrences(int number, int digit)
{
    int count = 0;
    int length = n_digits(number);
    int i = 0;

    while(i < length)
    {
        if (number % 10 == digit)
        {
            count++;
        }
        number /= 10;
        i++;
    }

    return count;
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
        //printf("digit_guess : %i\n", digit_guess);
        digit_answer = buffer % 10;
        //printf("digit_answer : %i\n", digit_answer);
        if (digit_guess != digit_answer)
        {
            //printf("Is the number in it? : %i\n", digit_is_in(answer, digit_guess));
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

bool valid_guess(int guess)
{
    if (guess == -1)
    {
        return true;
    }
    else if (digit_is_in(guess, 0) == true)
    {
        printf("You cant have zeros in your guess\n");
        return false;
    }
    else if (n_digits(guess) != 4)
    {
        printf("Please insert a 4 digit number to continue\n");
        return false;
    }
    else if (duplicates(guess) == true)
    {
        printf("No repeating digits\n");
        return false;
    }
    else
    {
        return true;
    }
}

void game()
{
    int answer = get_random_4digit();
    // TODO Use functions (and more) to implement the game
    // TODO Try to sketch one round, then surround with a loop.
    bool aborted = false;
    int n_guess = 0;
    int guess = 0;
    int bulls = 0;
    int cows = 0;
    //printf("Answer is %d\n", answer);

    while (aborted == false)
    {
        guess = get_player_guess();
        if (guess == -1)
        {
            aborted = true;
        }
        else
        {
            bulls = count_bulls(guess, answer);
            cows = count_cows_and_bulls(guess, answer);
            if (guess == answer)
            {
                break;
            }
            printf("There are %i bulls and %i cows\n", bulls, cows);
            n_guess++;
        }
    }

    // --- End game loop --------

    if (aborted) {
        printf("Game aborted\n");
    } else {
        printf("Done, number was %d and you needed %d guesses\n", answer, n_guess);
    }

}

int play_again()
{
    int selection = -1;
    while (selection != 0 && selection != 1)
    {
        printf("\n");
        printf("Select 0 or 1 to quit game or to play again: ");
        scanf("%i", &selection);
    }

    printf("\n");

    return selection;

}

void game_instruction()
{
    printf("\n");
    printf("Welcome to Bulls and Cows\n");
    printf("Try to guess a 4 digit number with digits 1-9\n");
    printf("and no repeating digits (-1 to abort).\n\n");
    printf("Bulls = correct digit(s) in correct positions.\n");
    printf("Cows = correct digit(s).\n\n");
}

void built_in_debugger(int answer)
{
    
    if (TEST) {
        test();
    }

    if (DEBUG) {
        printf("Answer is %d\n", answer);
    }
    
}


// ---------------- The function to do all tests --------------------

// This macro is used for testing. It expects v1 and v2 shall be equal and print OK or Not OK
#define CHECK_IF_EQUALS(v1, v2) printf((v1) == (v2) ? "OK\n" : "Not OK!!!\n")

void test() {

    // TODO Uncomment on at the time and test

    /*
    // if you intend to check if the guess was correct, use and test the n_digits-function
    CHECK_IF_EQUALS(n_digits(123), 3);
    CHECK_IF_EQUALS(n_digits(12345), 5);
    CHECK_IF_EQUALS(n_digits(1623945), 7);
    */
  
    /*
    CHECK_IF_EQUALS(get_digit_at_position(4321, 1), 1);
    CHECK_IF_EQUALS(get_digit_at_position(4321, 3), 3);
    CHECK_IF_EQUALS(get_digit_at_position(4321, 4), 4);

    CHECK_IF_EQUALS(digit_is_in(2637, 2), true);
    CHECK_IF_EQUALS(digit_is_in(2637, 4), false);

    printf("Random answer %d\n", get_random_4digit());
    printf("Random answer %d\n", get_random_4digit());
    printf("Random answer %d\n", get_random_4digit());

    CHECK_IF_EQUALS(count_bulls(1827, 7812), 1);
    CHECK_IF_EQUALS(count_bulls(2647, 2837), 2);

    CHECK_IF_EQUALS(count_cows_and_bulls(1827, 7812), 4);
    CHECK_IF_EQUALS(count_cows_and_bulls(2647, 2837), 2);
    */
}
