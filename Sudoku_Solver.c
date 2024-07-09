#include <stdio.h> //SEMESTER WORK
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <conio.h> 
#define n 9 //field size 

typedef struct Field {//struct that represents a field
    int num;
    int predefined;//to mark ones which are defined as a default input values
} Field;

typedef struct Queue { //struct to make a field without repetitions in 3x3 blocks (it marks a number and whether it is already used or not)
    int num;
    int used;
} Queue;

void RandomCreation (Field ** field) {//creates a random field without repetitions in 3x3 blocks
    int random;
    int space;//dimension of small blocks (3x3)
    space = (int)sqrt(n); 
    Queue queue[n];
    int flag;
    for (int i = 0; i < n; i++) 
        queue[i].num = i+1;
    for (int i = 0; i < space; i++) { //these 2 loops help us moving in small 3x3 blocks ('i' is the vertical position and 'j' is horizontal)
        for (int j = 0; j < space; j++) {
            for (int x = 0; x < 2; x++) {// when x is 0 we only go through numbers in a block and mark predefined values as "used" ones, when x is 1 we insert new values
                if (x == 0) {
                    for (int g = 0; g < n; g++)//cleaning "used" values befor inserting new
                    queue[g].used = 0;
                }
            for (int a = 0; a < space; a++) {//in these 2 loops we move in a block row by row ('a' represents vertical position and 'b' horizontal)
                for (int b = 0; b < space; b++) {
                    if (field[i*space+a][j*space+b].predefined == 1 && x == 0) //here we mark predefined values
                        queue[field[i*space+a][j*space+b].num-1].used = 1;
                    else  if (x == 1){
                        flag = 0;
                        while (flag == 0) {
                        random = rand() % (n+1);//random number generation
                        for (int k = 0; k < n; k++) {// here we start to look through a queue to find whether a random number is already used or not
                        if (field[i*space+a][j*space+b].predefined == 1) {//in case of predefined value is met, move to the next position in a block
                            flag = 1;
                            break;
                        }
                        if (random == 0 || (queue[k].used == 1 && random == queue[k].num)) {//if random value is already used, try to generate another one
                            break;
                        }
                        if (random == queue[k].num) {//insert random value into field and mark this value as used one
                            queue[k].used = 1;
                            field[i*space+a][j*space+b].num = random;
                            flag = 1;
                            break;
                        }
                        }
                        }
                    }
                    }
                }
            }
        }
    }
}

int FindChosenOne (Field ** field) {//counts total amount of number's vertical an horiaontal repetitions
    int TotalCount = 0;
for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
        //Check repetitions in all directions
        for (int a = 0; a < n; a++) {
            for (int b = 0; b < n; b++) {
                if (field[a][b].num == field[i][j].num && (a == i || b == j) && !(a == i && b == j)) {
                    if (field[a][b].predefined == 1)//if a number is in the same row or column with it's predefined value, then mark it with bigger value to terminate it first
                        TotalCount+=7;
                    else
                        TotalCount++;
                }
            }
        }
    }
}
return TotalCount;
}

int SwapFunc (Field ** field, int y, int x, int PartX, int PartY, int space) { //function that swaps randomly chosen element in a 3x3 block
    int BestRes = FindChosenOne(field);//best number of total repetitions
    int FirstRes = FindChosenOne(field);//default number of total repetitions
    int BestOptionX;//best coordinates to swap with
    int BestOptionY;
    int res;
    int tmp;

for (int i = 0; i < space; i++) {//go through all positions in a block, trying to swap a chosen number with a number in this position
        for (int j = 0; j < space; j++) {
        if (field[PartY*space+i][PartX*space+j].predefined == 1 || (i == y && j == x)) continue;//if a number is predefined-continue
            tmp = field[PartY*space+y][PartX*space+x].num;//do a swap
            field[PartY*space+y][PartX*space+x].num = field[PartY*space+i][PartX*space+j].num;
            field[PartY*space+i][PartX*space+j].num = tmp;
            res = FindChosenOne(field);//find total number of repetitions with a new numbers positions
            field[PartY*space+i][PartX*space+j].num = field[PartY*space+y][PartX*space+x].num;//return numbers in their old places
            field[PartY*space+y][PartX*space+x].num = tmp;

            if (res < BestRes) {//compare new res value with the best one
                BestOptionX = j;
                BestOptionY = i;
                BestRes = res;
            }
        }
    }

    if (BestRes < FirstRes) {//if a better number positions is found, do a swap
        tmp = field[PartY*space+y][PartX*space+x].num;
            field[PartY*space+y][PartX*space+x].num = field[PartY*space+BestOptionY][PartX*space+BestOptionX].num;
            field[PartY*space+BestOptionY][PartX*space+BestOptionX].num = tmp;
            return 0;
    }

return 1;
}





int main () { 
srand(time(NULL));
int x;//horizontal
int y;//vertical
int ResCounter = n*n;//reset counter->marks when to do the reset
int TotalCounter;
int space;
    space = (int)sqrt(n);
int PartX;
int PartY;
Field ** field = (Field **)malloc(n*sizeof(Field*));
for (int r = 0; r < n; r++) {
  field[r] = (Field*)malloc (n*sizeof(Field)); 
} 
int FakeField[n][n] = {{0, 0, 0, 0, 0, 0, 0, 9, 0}, //input field
                      {1, 9, 0, 4, 7, 0, 6, 0, 8},
                      {0, 5, 2, 8, 1, 9, 4, 0, 7},
                      {2, 0, 0, 0, 4, 8, 0, 0, 0},
                      {0, 0, 9, 0, 0, 0, 5, 0, 0},
                      {0, 0, 0, 7, 5, 0, 0, 0, 9},
                      {9, 0, 7, 3, 6, 4, 1, 8, 0},
                      {5, 0, 6, 0, 8, 1, 0, 7, 4},
                      {0, 8, 0, 0, 0, 0, 0, 0, 0}};
for (int i = 0; i < n; i++) { //copy input field to the struct Field and mark predefined values
    for (int j = 0; j < n; j++) {
        field[i][j].num = FakeField[i][j];
        if (FakeField[i][j] != 0) 
            field[i][j].predefined = 1;
        else
            field[i][j].predefined = 0;
    }
}

//MAIN PART 
RandomCreation(field);
while (FindChosenOne(field) != 0) {
    do {//create a random coordinates of a number to pass it to the SwapFunction
    PartX = rand() % (space);//block position
    PartY = rand() % (space);
    x = rand() % (space);//number's position in a block
    y = rand() % (space);
    } while (field[PartY*space+y][PartX*space+x].predefined == 1);
if (SwapFunc(field, y, x, PartX, PartY, space) == 1) {//if there is no good swap, decrease reset counter
ResCounter--;
} else {
    ResCounter = n*n;//if there is a good swap, return starting value to reset counter
}
if (ResCounter == 0) {//reset time!
    RandomCreation(field);
    ResCounter = n*n;
} 
}


printf ("Done!\n");
for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
        printf ("%d ", field[i][j].num);
    }
    printf ("\n");
}

    return 0;
}