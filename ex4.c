#include <stdio.h>
#include <string.h>


/***************************
******** Menu Items ********
****************************/

#define REVERSE 1
#define PALINDROME 2
#define SENTENCES 3
#define ZIP 4
#define SUDOKU 5
#define EXIT 6


/***************************
*** DIMENSION PARAMETERS ***
****************************/

#define LONGEST_TERM 20
#define LONGEST_SENTENCE 62
#define MAX_NUMBER_OF_TERMS 10

#define ZIP_MAX_GRID_SIZE 20

#define SUDOKU_GRID_SIZE 9
#define SUDOKU_SUBGRID_SIZE 3


/***************************
* USER INTEFACE PROTOTYPES *
****************************/

void task1ReversePhrase();
void task2CheckPalindrome();
void task3GenerateSentences();
void task4SolveZipBoard();
void task5SolveSudoku();


/****************************
* IMPLEMENTATION PROTOTYPES *
*****************************/

void task1ReversePhraseImplementation();
int task2CheckPalindromeImplementation(int);
void task3GenerateSentencesImplementation(char[][LONGEST_TERM+1], int, char[][LONGEST_TERM+1], int,
                                            char[][LONGEST_TERM+1], int);
int task4SolveZipBoardImplementation(int[ZIP_MAX_GRID_SIZE][ZIP_MAX_GRID_SIZE],
                                        char[ZIP_MAX_GRID_SIZE][ZIP_MAX_GRID_SIZE], int, int, int, int);
int task5SolveSudokuImplementation(int[SUDOKU_GRID_SIZE][SUDOKU_GRID_SIZE]);


/******************************
* HELPER FUNCTIONS PROTOTYPES *
*******************************/

int readTerms(char[][LONGEST_TERM+1], int, char[]);
void printSudoku(int[SUDOKU_GRID_SIZE][SUDOKU_GRID_SIZE]);
void readRec(char str[], int i, int length);
int palRec(char str[], int left, int right);
int objects(char subjects[][LONGEST_TERM+1], int s,
               char verbs[][LONGEST_TERM+1], int v,
               char objects[][LONGEST_TERM+1], int objectsCount,
               int o, int counter);
int verbs(char subjects[][LONGEST_TERM+1], int s,
             char verbs[][LONGEST_TERM+1], int verbsCount,
             char objects[][LONGEST_TERM+1], int objectsCount,
             int v, int counter);
int subjects(char subjects[][LONGEST_TERM+1], int subjectsCount,
                char verbs[][LONGEST_TERM+1], int verbsCount,
                char objects[][LONGEST_TERM+1], int objectsCount,
                int s, int counter);
int zipHelper(int grid[ZIP_MAX_GRID_SIZE][ZIP_MAX_GRID_SIZE],
                char solution[ZIP_MAX_GRID_SIZE][ZIP_MAX_GRID_SIZE],
                int size, int visited[ZIP_MAX_GRID_SIZE][ZIP_MAX_GRID_SIZE],
                int r, int c, int visitedCount, int nextNum, int highest);
int rowHasNum(int board[SUDOKU_GRID_SIZE][SUDOKU_GRID_SIZE], int row, int col, int num);
int colHasNum(int board[SUDOKU_GRID_SIZE][SUDOKU_GRID_SIZE], int col, int row, int num);
int cubeHasNum(int board[SUDOKU_GRID_SIZE][SUDOKU_GRID_SIZE], int startR, int startC, int idx, int num);
int isValidMove(int board[SUDOKU_GRID_SIZE][SUDOKU_GRID_SIZE], int row, int col, int num);
int solveFromPos(int board[SUDOKU_GRID_SIZE][SUDOKU_GRID_SIZE], int pos);
int tryNums(int board[SUDOKU_GRID_SIZE][SUDOKU_GRID_SIZE], int pos, int num);


/******************************
********** MAIN MENU **********
*******************************/

int main()
{
    int task;
    do
    {
        printf("Please choose a task (1-5) or 6 to exit:\n");
        printf("%d. Reverse a phrase\n", REVERSE);
        printf("%d. Check Palindrome\n", PALINDROME);
        printf("%d. Generate sentences\n", SENTENCES);
        printf("%d. Solve Zip Board\n", ZIP);
        printf("%d. Solve Sudoku\n", SUDOKU);
        printf("%d. Exit\n", EXIT);

        scanf(" %d", &task);
        scanf("%*c");
        switch (task)
        {
        case REVERSE:
            task1ReversePhrase();
            break;
        case PALINDROME:
            task2CheckPalindrome();
            break;
        case SENTENCES:
            task3GenerateSentences();
            break;
        case ZIP:
            task4SolveZipBoard();
            break;
        case SUDOKU:
            task5SolveSudoku();
            break;
        case EXIT:
            printf("Goodbye!\n");
            break;
        default:
            printf("Please choose a task number from the list.\n");
            break;
        }
        printf("\n=============================\n\n");
    } while (task != EXIT);

    return 0;
}


/***************************
****** USER INTERFACE ******
****************************/


void task1ReversePhrase()
{
    printf("Please insert the phrase to reverse:\n");
    task1ReversePhraseImplementation();
    printf("\n");
}


void task2CheckPalindrome()
{
    printf("Please insert the phrase length:\n");
    int n;
    scanf("%d", &n);
    printf("Please insert the phrase to check:\n");
    scanf(" ");
    if (task2CheckPalindromeImplementation(n))
        printf("The phrase is a palindrome.\n");
    else
        printf("The phrase is not a palindrome.\n");
}


void task3GenerateSentences()
{
    char subjects[MAX_NUMBER_OF_TERMS][LONGEST_TERM+1];
    char verbs[MAX_NUMBER_OF_TERMS][LONGEST_TERM+1];
    char objects[MAX_NUMBER_OF_TERMS][LONGEST_TERM+1];
    int subjectsCount, verbsCount, objectsCount;

    subjectsCount=readTerms(subjects, MAX_NUMBER_OF_TERMS, "subjects");
    verbsCount=readTerms(verbs, MAX_NUMBER_OF_TERMS, "verbs");
    objectsCount=readTerms(objects, MAX_NUMBER_OF_TERMS, "objects");
    printf("List of Sentences:\n");
    task3GenerateSentencesImplementation(subjects, subjectsCount, verbs, verbsCount, objects, objectsCount);
}


void task4SolveZipBoard()
{
    int size;
    int board[ZIP_MAX_GRID_SIZE][ZIP_MAX_GRID_SIZE] = {0};
    char solution[ZIP_MAX_GRID_SIZE][ZIP_MAX_GRID_SIZE] = {0};
    int row, col;
    int highest=0;
    printf("Please enter the board size:\n");
    scanf("%d", &size);
    if (size < 1 || size > ZIP_MAX_GRID_SIZE)
    {
        printf("Invalid board size.\n");
        return;
    }

    printf("Please enter the grid:\n");
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            scanf("%d", &board[i][j]);
            if (board[i][j] == 1)
            {
                row = i;
                col = j;
            }
            if(board[i][j]>highest){
                highest=board[i][j];
            }
        }
    }
    if (task4SolveZipBoardImplementation(board, solution, size, row, col, highest))
    {
        printf("Solution:\n");
        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < size; j++)
            {
                printf("%c ", solution[i][j] ? solution[i][j] : 'X');
            }
            printf("\n");
        }
    }
    else
    {
        printf("No solution exists.\n");
    }
}


void task5SolveSudoku()
{
    printf("Please enter the sudoku board:\n");
    int board[SUDOKU_GRID_SIZE][SUDOKU_GRID_SIZE] = {0};
    for (int i = 0; i < SUDOKU_GRID_SIZE; i++)
    {
        for (int j = 0; j < SUDOKU_GRID_SIZE; j++)
        {
            scanf("%d", &board[i][j]);
        }
    }
    if (task5SolveSudokuImplementation(board)) {
        printf("Solution found:\n");
        printSudoku(board);
    }
    else
    {
        printf("No solution exists.\n");
    }
}


/***************************
********* HELPERS **********
****************************/


int readTerms(char terms[][LONGEST_TERM+1], int maxNumOfTerms, char type[]){
    int termsCount;
    printf("Please insert number of %s:\n", type);
    scanf("%d", &termsCount);
    if(termsCount < 1 || termsCount > maxNumOfTerms){
        termsCount = maxNumOfTerms;
    }
    printf("Please insert the list of %s:\n", type);
    for(int i=0;i<termsCount;i++){
        printf("%d. ",i+1);
        scanf(" %[^\n]",terms[i]);
    }
    return termsCount;
}


void printSudoku(int board[SUDOKU_GRID_SIZE][SUDOKU_GRID_SIZE])
{
    printf("+-------+-------+-------+\n");
    for (int i = 0; i < SUDOKU_GRID_SIZE; i++)
    {
        printf("| ");
        for (int j = 0; j < SUDOKU_GRID_SIZE; j++)
        {
            if (board[i][j] == 0)
                printf(". ");
            printf("%d ", board[i][j]);

            if ((j + 1) % SUDOKU_SUBGRID_SIZE == 0)
                printf("| ");
        }
        printf("\n");
        if ((i + 1) % SUDOKU_SUBGRID_SIZE == 0)
            printf("+-------+-------+-------+\n");
    }
}

void readRec(char str[], int i, int length)
{ //reading the string
    if (i == length) {
        return;
    }
    str[i] = getchar();
    readRec(str, i + 1, length);
}
int palRec(char str[], int left, int right)
{//using the string that we read in an arr, basic pal checking
    if (left >= right) {
        return 1;
    }
    if (str[left] != str[right]) {
        return 0;
    }
    return palRec(str, left + 1, right - 1);
}
//using the objects in the list one by one
int objectsPlacer(char subjects[][LONGEST_TERM+1], int s,
               char verbs[][LONGEST_TERM+1], int v,
               char objects[][LONGEST_TERM+1], int objectsCount,
               int o, int counter)
{
    if (o == objectsCount) {
        return counter;
    }

    printf("%d. %s %s %s\n", counter, subjects[s], verbs[v], objects[o]);

    return objectsPlacer(subjects, s, verbs, v, objects, objectsCount, o + 1, counter + 1);
}
//using the verbs one by one and calling the objects's func
int verbsPlacer(char subjects[][LONGEST_TERM+1], int s,
             char verbs[][LONGEST_TERM+1], int verbsCount,
             char objects[][LONGEST_TERM+1], int objectsCount,
             int v, int counter)
{
    if (v == verbsCount) {
        return counter;
    }

    counter = objectsPlacer(subjects, s, verbs, v, objects, objectsCount, 0, counter);
    return verbsPlacer(subjects, s, verbs, verbsCount, objects, objectsCount, v + 1, counter);
}
//using the subjects one by one and calling the verbs's func
int subjectsPlacer(char subjects[][LONGEST_TERM+1], int subjectsCount,
                char verbs[][LONGEST_TERM+1], int verbsCount,
                char objects[][LONGEST_TERM+1], int objectsCount,
                int s, int counter)
{
    if (s == subjectsCount) {
        return counter;
    }

    counter = verbsPlacer(subjects, s, verbs, verbsCount, objects, objectsCount, 0, counter);
    return subjectsPlacer(subjects, subjectsCount, verbs, verbsCount, objects, objectsCount, s + 1, counter);
}

int zipHelper(int grid[ZIP_MAX_GRID_SIZE][ZIP_MAX_GRID_SIZE],
                char solution[ZIP_MAX_GRID_SIZE][ZIP_MAX_GRID_SIZE],
                int size, int visited[ZIP_MAX_GRID_SIZE][ZIP_MAX_GRID_SIZE],
                int r, int c, int visitedCount, int nextNum, int highest) {
    // visited all cells
    if (visitedCount == size * size) {
        if (grid[r][c] == highest) {
            solution[r][c] = 'X';
            return 1;
        }
        return 0;
    }

    // up
    {
        int nr = r - 1, nc = c;
        if (nr >= 0 && !visited[nr][nc]) {
            int val = grid[nr][nc];
            if (val == 0 || val == nextNum) {
                int newNext = nextNum;
                if (val == nextNum) {
                    newNext++;
                }
                visited[nr][nc] = 1;
                solution[r][c] = 'U';
                if (zipHelper(grid, solution, size, visited, nr, nc,
                                visitedCount + 1, newNext, highest)) {
                    return 1;
                }
                visited[nr][nc] = 0;
                solution[r][c] = 0;
            }
        }
    }

    // down
    {
        int nr = r + 1, nc = c;
        if (nr < size && !visited[nr][nc]) {
            int val = grid[nr][nc];
            if (val == 0 || val == nextNum) {
                int newNext = nextNum;
                if (val == nextNum) {
                    newNext++;
                }
                visited[nr][nc] = 1;
                solution[r][c] = 'D';
                if (zipHelper(grid, solution, size, visited, nr, nc,
                                visitedCount + 1, newNext, highest)) {
                    return 1;
                }
                visited[nr][nc] = 0;
                solution[r][c] = 0;
            }
        }
    }

    // left
    {
        int nr = r, nc = c - 1;
        if (nc >= 0 && !visited[nr][nc]) {
            int val = grid[nr][nc];
            if (val == 0 || val == nextNum) {
                int newNext = nextNum;
                if (val == nextNum) {
                    newNext++;
                }
                visited[nr][nc] = 1;
                solution[r][c] = 'L';
                if (zipHelper(grid, solution, size, visited, nr, nc,
                                visitedCount + 1, newNext, highest)) {
                    return 1;
                }
                visited[nr][nc] = 0;
                solution[r][c] = 0;
            }
        }
    }

    // right
    {
        int nr = r, nc = c + 1;
        if (nc < size && !visited[nr][nc]) {
            int val = grid[nr][nc];
            if (val == 0 || val == nextNum) {
                int newNext = nextNum;
                if (val == nextNum) {
                    newNext++;
                }
                visited[nr][nc] = 1;
                solution[r][c] = 'R';
                if (zipHelper(grid, solution, size, visited, nr, nc,
                                visitedCount + 1, newNext, highest)) {
                    return 1;
                }
                visited[nr][nc] = 0;
                solution[r][c] = 0;
            }
        }
    }

    return 0;
}
//checking for said num in the row
int rowHasNum(int board[SUDOKU_GRID_SIZE][SUDOKU_GRID_SIZE], int row, int col, int num)
{
    if (col == SUDOKU_GRID_SIZE) {
        return 0;
    }
    if (board[row][col] == num) {
        return 1;
    }
    return rowHasNum(board, row, col + 1, num);
}
//checking for said num in the col
int colHasNum(int board[SUDOKU_GRID_SIZE][SUDOKU_GRID_SIZE], int col, int row, int num)
{
    if (row == SUDOKU_GRID_SIZE) {
        return 0;
    }
    if (board[row][col] == num) {
        return 1;
    }
    return colHasNum(board, col, row + 1, num);
}

//checking for said num in the cube
int cubeHasNum(int board[SUDOKU_GRID_SIZE][SUDOKU_GRID_SIZE], int startR, int startC, int idx, int num)
{
    if (idx == SUDOKU_GRID_SIZE) { // 9 cells in each cube
        return 0;
    }

    int r = startR + (idx / SUDOKU_SUBGRID_SIZE);
    int c = startC + (idx % SUDOKU_SUBGRID_SIZE);

    if (board[r][c] == num) {
        return 1;
    }
    return cubeHasNum(board, startR, startC, idx + 1, num);
}
//checking if the move is valid by the other funcs
int isValidMove(int board[SUDOKU_GRID_SIZE][SUDOKU_GRID_SIZE], int row, int col, int num)
{
    if (rowHasNum(board, row, 0, num)) {
        return 0;
    }
    if (colHasNum(board, col, 0, num)) {
        return 0;
    }

    int startR = (row / SUDOKU_SUBGRID_SIZE) * SUDOKU_SUBGRID_SIZE;
    int startC = (col / SUDOKU_SUBGRID_SIZE) * SUDOKU_SUBGRID_SIZE;

    if (cubeHasNum(board, startR, startC, 0, num)) {
        return 0;
    }

    return 1;
}

//trying the numbers and backtracking if necessary
int tryNums(int board[SUDOKU_GRID_SIZE][SUDOKU_GRID_SIZE], int pos, int num)
{
    if (num == 10) { // tried already 1-9
        return 0;
    }

    int row = pos / SUDOKU_GRID_SIZE;
    int col = pos % SUDOKU_GRID_SIZE;

    if (isValidMove(board, row, col, num)) {
        board[row][col] = num;

        if (solveFromPos(board, pos + 1)) {
            return 1;
        }

        //backtracking
        board[row][col] = 0;
    }

    return tryNums(board, pos, num + 1);
}
//going from cell to cell according to the order
int solveFromPos(int board[SUDOKU_GRID_SIZE][SUDOKU_GRID_SIZE], int pos)
{
    if (pos == SUDOKU_GRID_SIZE * SUDOKU_GRID_SIZE) { //81 in total
        return 1; // solved
    }

    int row = pos / SUDOKU_GRID_SIZE;
    int col = pos % SUDOKU_GRID_SIZE;

    if (board[row][col] != 0) {
        return solveFromPos(board, pos + 1); //next cell
    }

    // trying in ascending order
    return tryNums(board, pos, 1);
}
/***************************
*********** TODO ***********
****************************/

//all the implementations that execute the recursions

void task1ReversePhraseImplementation() {
    int c = getchar();

    if (c == '\n' || c == EOF) {
        printf("The reversed phrase is:\n");
        return;
    }

    task1ReversePhraseImplementation();
    printf("%c", c);//print the chars LIFO
}

int task2CheckPalindromeImplementation(int length) {
    char str[length];//arr determined by the length the user gave us

    readRec(str, 0, length);
    return palRec(str, 0, length - 1);
}

void task3GenerateSentencesImplementation(char subjects[][LONGEST_TERM+1], int subjectsCount,
                                         char verbs[][LONGEST_TERM+1], int verbsCount,
                                         char objects[][LONGEST_TERM+1], int objectsCount) {
    subjectsPlacer(subjects, subjectsCount, verbs, verbsCount, objects, objectsCount, 0, 1);
}


int task4SolveZipBoardImplementation(int grid[ZIP_MAX_GRID_SIZE][ZIP_MAX_GRID_SIZE],
                                     char solution[ZIP_MAX_GRID_SIZE][ZIP_MAX_GRID_SIZE],
                                     int size, int startR, int startC, int highest) {
    int visited[ZIP_MAX_GRID_SIZE][ZIP_MAX_GRID_SIZE] = {0};

    // mark start (tile 1) as visited
    visited[startR][startC] = 1;

    // start: visitedCount=1, nextNum=2
    return zipHelper(grid, solution, size, visited, startR, startC, 1, 2, highest);
}


int task5SolveSudokuImplementation(int board[SUDOKU_GRID_SIZE][SUDOKU_GRID_SIZE]) {
    return solveFromPos(board, 0);
}