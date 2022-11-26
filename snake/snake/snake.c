#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define TEST false   // If true run tests (only), else run program, change to "false" only after

#define EQUALS(v1, v2) printf( (v1) == (v2) ? "Ok\n" : "Not ok\n")
// implementing functions

#define X_SIZE 78    // Horizontal size, not including walls
#define Y_SIZE 18    // Vertical size, not including walls

#define APPLE_SYMBOL '@'
#define GRASS_SYMBOL '.'
#define SNAKE_BODY_SYMBOL '#'
#define SNAKE_HEAD_SYMBOL 'O'
#define WALL_SYMBOL '+'

#define UP_ARROW 'u'
#define LEFT_ARROW 'h'
#define DOWN_ARROW 'n'
#define RIGHT_ARROW 'j'

#define START_WAIT 0.3 // s
#define SPEEDUP_FACTOR 0.9

#ifdef _WIN32
//Windows Libraries
	#include <conio.h>
    #include <windows.h>
	void clrscr(){
        // Clears the screen, disabling the cursor
		system("cls");
        HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
        CONSOLE_CURSOR_INFO cursorInfo;
        GetConsoleCursorInfo(out, &cursorInfo);
        cursorInfo.bVisible = false;
        SetConsoleCursorInfo(out, &cursorInfo);
		return;
	}
    void gotoxy(int x, int y){
        // Sets the cursor at position (x,y)
        COORD coord;
        coord.X = 0;
        coord.Y = 0;
        SetConsoleCursorPosition(
            GetStdHandle(STD_OUTPUT_HANDLE),
            coord
		);
    }


#else
//Linux-macOS Libraries
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>

//http://cboard.cprogramming.com/c-programming/63166-kbhit-linux.html
int kbhit(void) {
    struct termios oldt, newt;
    int ch;
    int oldf;

    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

    ch = getchar();

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    fcntl(STDIN_FILENO, F_SETFL, oldf);

    if(ch != EOF) {
        ungetc(ch, stdin);
        return 1;
    }

    return 0;
}

//http://www.experts-exchange.com/Programming/Languages/C/Q_10119844.html - posted by jos
char getch() {
    char c;
    system("stty raw");
    c=getchar();
    printf("\r "); // Typed character replaced, stty raw -echo doesn't fix it
    system("stty sane");
    return(c);
}

void clrscr() {
    // Clears the screen
    system("clear");
    return;
}
void gotoxy(int x,int y){
    // Sets the cursor at position (x,y)
    printf("%c[%d;%df",0x1B,y,x);
}
//End linux-macOS functions
#endif

// Testing of functions, see far below
void test();

// ----- The test methods ----------------------------
void test_snake_init();
void test_insertSnakeBodyUnit();
void test_snake_move();
void test_snake_turn();
void test_snake_hit_self();
void test_snake_eat_apple();

// --- Things needed (nothing to do for you) ---
typedef struct {
    int x, y;
} apple_t;

typedef enum {
    UP, RIGHT, DOWN, LEFT
} dir_t;

// The snake
typedef struct {
    int x[X_SIZE*Y_SIZE];
    int y[X_SIZE*Y_SIZE];
    int length;
    dir_t dir;
} snake_t;

void apple_new(apple_t *apple, snake_t *snake) {
    // Draw random positions until position not hitting snake found
    bool ready = false;
    int x_try, y_try;
    while (!ready)
    {
        x_try = 1 + rand()%(X_SIZE);
        y_try = 1 + rand()%(Y_SIZE);
        ready = true;
        for (int i=0; i<snake->length && ready; ++i)
        {
            if (x_try == snake->x[i] && y_try == snake->y[i])
                ready = false;
        }
    }
    apple->x = x_try;
    apple->y = y_try;
}

void world_field(char world[X_SIZE+2][Y_SIZE+2], apple_t *apple, snake_t *snake) {
    for (int y=1; y<Y_SIZE+1; ++y) {
        for (int x=1; x<X_SIZE+1; ++x) {
            world[x][y] = GRASS_SYMBOL;
        }
    }
    world[apple->x][apple->y] = APPLE_SYMBOL;
    world[snake->x[0]][snake->y[0]] = SNAKE_HEAD_SYMBOL;
    for (int i=1; i<snake->length; ++i) {
        world[snake->x[i]][snake->y[i]] = SNAKE_BODY_SYMBOL;
    }
}

void world_print(char world[X_SIZE+2][Y_SIZE+2], int points) {
    gotoxy(0,0);
    for (int y=0; y<Y_SIZE+2; ++y) {
        for (int x=0; x<X_SIZE+2; ++x) {
            printf("%c", world[x][y]);
        }
        printf("\n");
    }
    printf("Points: %d\n", points);
}

void world_walls(char world[X_SIZE+2][Y_SIZE+2]) {
    for (int y=0; y<Y_SIZE+2; ++y) {
        for (int x=0; x<X_SIZE+2; ++x) {
            if (y==0 || y==Y_SIZE+1 || x==0 || x==X_SIZE+1)
                world[x][y] = WALL_SYMBOL;
        }
    }
}


// -----------------------------------------------------------------------------------------------
// --- Your stuff below
// -----------------------------------------------------------------------------------------------

// Creation of the snake with default parameters
// direction RIGHT, head at the center of the map and
// length = 2 (1 head + 1 body unit)
void snake_init(snake_t *snake) {
    // Reason f
    snake->dir = RIGHT;
    snake->length = 2;
    snake->x[0] = 39; // 39 is center bcs i need to take into account the border that was created otherwiese it should be 38
    snake->y[0] = 9; // same thing here gotta add 2 to 
    snake->x[1] = 38;  
    snake->y[1] = 9;
}

// set the snake direction
// So to get this to be "correct" remove the second condition in each statement but thats not real snake 
void snake_turn(snake_t *snake) {

    if (kbhit()) { // user hits key
        char input = getch(); // fetch the key value to input
        //printf("%c\n", input);
        switch (input)
        {
        case 'u':
            snake->dir = UP;
            break;
        case 'h':
            snake->dir = LEFT;
            break;
        case 'n':
            snake->dir = DOWN;
            break;
        case 'j':
            snake->dir = RIGHT;
            break;
        default:
            break;
        }
    }
    // TODO
}

// Update the position of the snake according
// to its direction.
void snake_move(snake_t *snake) 
{
    for (int i = snake->length - 0; i > 0; i--)
    {
        snake->x[i] = snake->x[i - 1];
        snake->y[i] = snake->y[i - 1];
        
    }
    switch (snake->dir)
        {
        case UP:
            snake->y[0]--;
            break;
        case DOWN:
            snake->y[0]++;
            break;
        case LEFT:
            snake->x[0]--;
            break;
        default:
            snake->x[0]++;
            break;
        }
    
}

// Did the snake eat the apple
bool snake_eat_apple(apple_t *apple, snake_t *snake) {
    if (snake->x[0] == apple->x && snake->y[0] == apple->y)
    {
        // Can't increase the length of the snake.
        apple_new(apple, snake);
        snake->length++;
        int new = snake->length - 1;
        
        switch (snake->dir)
        {
        case UP:
            snake->x[new] = snake->x[new - 1];
            snake->y[new] = snake->x[new - 1] + 1;
        case DOWN:
            snake->x[new] = snake->x[new - 1];
            snake->y[new] = snake->x[new - 1] - 1;
        case LEFT:
            snake->x[new] = snake->x[new - 1] - 1;
            snake->y[new] = snake->x[new - 1];
            break;
        default:
            snake->x[new] = snake->x[new - 1] + 1;
            snake->y[new] = snake->x[new - 1];
            break;
        }

        return true;
    }
    return false;
}

// If the snake length is greater than 2,
// the snake can hit itself
bool snake_hit_self(snake_t *snake) {
    
    if (snake->length > 2)
    {
        for (int i = 1; i < snake->length; i++)
        {
            if (snake->x[0] == snake->x[i] && snake->y[0] == snake->y[i])
            {
                return true;
            }
        }
        
    }
    return false;
}

// The snake must stay within the
// boundaries of the world.
bool snake_hit_wall(snake_t *snake) {
    for (int i = 0; i < X_SIZE; i++)
    {
        if (snake->x[0] == i && (snake->y[0] == 0 || snake->y[0] == 19))
        {
            return true;
        }
    }
    for (int j = 0; j < Y_SIZE; j++)
    {
        if (snake->y[0] == j && (snake->x[0] == 0 || snake->x[0] == 79))
        {
            return true;
        }
    }
    return false;
}

int main() {


    if (TEST) {
        test();
        
        return 0;
    }

    // Initalizations
    struct timespec ts;
    ts.tv_sec = (long) START_WAIT;
    ts.tv_nsec = (long) (START_WAIT * 1000000000) % 1000000000;

    srand(time(0));

    // Clear the screen, disabling the cursor if platform is Windows
    clrscr();

    // Create world
    char world[X_SIZE+2][Y_SIZE+2];
    world_walls(world);

    // Create initial snake
    bool snake_dead = false;
    snake_t snake;
    snake_init(&snake);

    // Create initial apple
    apple_t apple;
    apple_new(&apple, &snake);

    while (!snake_dead) {
        snake_turn(&snake);
        snake_move(&snake);
        world_field(world, &apple, &snake);
        world_print(world, snake.length-2);
        if (snake_eat_apple(&apple, &snake)) {
            ts.tv_nsec = ((long) (((ts.tv_sec * 1000000000) + ts.tv_nsec) * SPEEDUP_FACTOR)) % 1000000000;
            ts.tv_sec = (long) ts.tv_sec * SPEEDUP_FACTOR;

        }
        snake_dead = snake_hit_wall(&snake) || snake_hit_self(&snake);
        if (snake_dead) {
            printf("Game over!!!\n");
        }
        nanosleep(&ts, NULL);
    }

    return(0);
}

void test() {

    printf("do test");

    // TODO for testing
    // Run one at the time until all works
    // Then possibly run all at once.
    // -- uncomment what you want to test --

    test_snake_init();
    test_snake_move();
    test_snake_turn();
    test_snake_hit_self(); // to pass, this needs snake_turn to be working too
    test_snake_eat_apple();

    exit(0);
}

// ------------ Test functions definitions -----------------


void test_snake_init(){
    printf("Test_snake_init\n");
    snake_t snake;
    snake_init(&snake);
    EQUALS(snake.dir, RIGHT);
    EQUALS(snake.x[0]*1000000+snake.y[0]*10000+snake.y[1]*100+snake.x[1], 39090938);
    EQUALS(snake.length, 2);
    
    //printf("%i\n", snake.x[0]*1000000+snake.y[0]*10000+snake.y[1]*100+snake.x[1]);
    //printf("%i\n", 39090938);
}

void test_snake_move(){
    printf("Test_snake_move\n");
    snake_t snake;

    snake_init(&snake);
    snake.dir = UP;
    snake_move(&snake);
    if (snake.x[0] != 39 || snake.x[1] != 39 || snake.y[0] != 8 || snake.y[1] != 9){
        printf("Not ok\n");
    } else {
        printf("Ok\n");
    }

    snake_init(&snake);
    snake.dir = DOWN;
    snake_move(&snake);
    if (snake.x[0] != 39 || snake.x[1] != 39 || snake.y[0] != 10 || snake.y[1] != 9){
        printf("Not ok\n");
    } else {
        printf("Ok\n");
    }

    snake_init(&snake);
    snake.dir = LEFT;
    snake_move(&snake);
    if (snake.x[0] != 38 || snake.x[1] != 39 || snake.y[0] != 9 || snake.y[1] != 9){
        printf("Not ok\n");
    } else {
        printf("Ok\n");
    }

    snake_init(&snake);
    snake.dir = RIGHT;
    snake_move(&snake);
    if (snake.x[0] != 40 || snake.x[1] != 39 || snake.y[0] != 9 || snake.y[1] != 9){
        printf("Not ok\n");
    } else {
        printf("Ok\n");
    }
}


void test_snake_eat_apple(){
    snake_t snake;
    snake_init(&snake);
    printf("Test_check_eat_apple\n");

    apple_t *apple = malloc(sizeof(apple_t));
    if (apple == NULL) {
        perror("Couldn't create apple, giving up");
        exit(EXIT_FAILURE);
    }

    apple->x = 14;
    apple->y = 12;
    EQUALS(snake_eat_apple(apple, &snake), 0);

    apple->x = 39;
    apple->y = 9;
    EQUALS(snake_eat_apple(apple, &snake), 1);
}

// These last two test functions have slight differences for Win and linux-macOS
#ifdef _WIN32
void test_snake_turn(){  // Windows function
    
    struct timespec ts;
    ts.tv_sec = 5;
    ts.tv_nsec = 125;
    
    printf("Test_snake_turn\n");
      
    snake_t snake;
    snake_init(&snake);
    
    printf("Just type the requested letter and wait a few seconds, DO NOT type ENTER or any other key\n");

    printf("do left turn --> type h (you have 5 seconds): ");
    nanosleep(&ts, NULL);
    snake_turn(&snake);
    EQUALS(snake.dir, LEFT);

    printf("do right turn (j): ");
    nanosleep(&ts, NULL);
    snake_turn(&snake);
    EQUALS(snake.dir, RIGHT);

    printf("do up turn (u): ");
    nanosleep(&ts, NULL);
    snake_turn(&snake);
    EQUALS(snake.dir, UP);

    printf("do down turn (n): ");
    nanosleep(&ts, NULL);
    snake_turn(&snake);
    EQUALS(snake.dir, DOWN);

}

void test_snake_hit_self() {  // Windows function
    
    struct timespec ts;
    ts.tv_sec = 5;
    ts.tv_nsec = 125;
    
    printf("Test_snake_hit_self\n");
    snake_t snake;
    snake_init(&snake);

    printf("Just type the requested letter and wait a few seconds, DO NOT type ENTER or any other key\n");

    // Snake length is two and moving to the RIGHT (default at init)
    // Now turn the snake to the LEFT
    printf("type key h: ");
    nanosleep(&ts, NULL);
    snake_turn(&snake);
    snake_move(&snake);
    EQUALS(snake_hit_self(&snake), false);

    // same in the up/down
    snake.dir = UP;
    printf("type key n: ");
    nanosleep(&ts, NULL);
    snake_turn(&snake);    // Opposite direction
    snake_move(&snake);          // If length 2 never will collide!
    EQUALS(snake_hit_self(&snake), false);

    // If length > 2 possibly will collide!
    snake.dir = DOWN;
    snake.length = 3;
    printf("type key u: ");
    nanosleep(&ts, NULL);
    snake_turn(&snake);    // Opposite direction
    snake_move(&snake);
    EQUALS(snake_hit_self(&snake), true);
}

#else
void test_snake_turn(){  // Unix function
    printf("Test_snake_turn\n");
    int key;
    snake_t snake;
    snake_init(&snake);

    printf("do left turn (h): ");
    scanf("%d", &key);
    snake_turn(&snake);
    EQUALS(snake.dir, LEFT);

    printf("do right turn (j): ");
    scanf("%d", &key);
    snake_turn(&snake);
    EQUALS(snake.dir, RIGHT);

    printf("do up turn (u): ");
    scanf("%d", &key);
    snake_turn(&snake);
    EQUALS(snake.dir, UP);

    printf("do down turn (n): ");
    scanf("%d", &key);
    snake_turn(&snake);
    EQUALS(snake.dir, DOWN);

}

void test_snake_hit_self() {  // Unix function
    printf("Test_snake_hit_self\n");
    int key;
    snake_t snake;
    snake_init(&snake);

    // Snake length is two and moving to the RIGHT (default at init)
    // Now turn the snake to the LEFT
    printf("type key h: ");
    scanf("%d", &key);
    snake_turn(&snake);
    snake_move(&snake);
    EQUALS(snake_hit_self(&snake), false);

    // same in the up/down
    snake.dir = UP;
    printf("type key n: ");
    scanf("%d", &key);
    snake_turn(&snake);    // Opposite direction
    snake_move(&snake);          // If length 2 never will collide!
    EQUALS(snake_hit_self(&snake), false);

    // If length > 2 possibly will collide!
    snake.dir = DOWN;
    snake.length = 3;
    printf("type key u: ");
    scanf("%d", &key);
    snake_turn(&snake);    // Opposite direction
    snake_move(&snake);
    EQUALS(snake_hit_self(&snake), true);
}

//End linux-macOS functions
#endif
