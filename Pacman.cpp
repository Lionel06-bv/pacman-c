#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define WIDTH 21 // Tambahkan 1 agar cukup untuk karakter null
#define HEIGHT 10

typedef struct {
    int x, y;
} Position;

char maze[HEIGHT][WIDTH] = {
    "####################",
    "# .  .  #  .  .  . #",
    "# ## # ## ## # ## # ",
    "# .  .  .  .  .  . #",
    "# ## ## # ## ## ## #",
    "# .  .  #  .  .  . #",
    "# ## # ## ## # ## # ",
    "# .  .  .  .  .  . #",
    "# ################# ",
    "####################"
};

Position pacman, ghost;
int score = 0;
int highscore = 0;

void loadHighScore() {
    FILE *file = fopen("highscore.txt", "r");
    if (file) {
        fscanf(file, "%d", &highscore);
        fclose(file);
    }
}

void saveHighScore() {
    if (score > highscore) {
        highscore = score;
        FILE *file = fopen("highscore.txt", "w");
        fprintf(file, "%d", highscore);
        fclose(file);
    }
}

void initializeGame() {
    pacman.x = 1;
    pacman.y = 1;
    ghost.x = WIDTH - 3;
    ghost.y = HEIGHT - 3; // Perbaiki posisi ghost agar berada di dalam pagar
    loadHighScore();
}

void drawMaze() {
    system("cls");
    printf("Score: %d  High Score: %d\n", score, highscore);
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            if (i == pacman.y && j == pacman.x)
                printf("P");
            else if (i == ghost.y && j == ghost.x)
                printf("G");
            else
                printf("%c", maze[i][j]);
        }
        printf("\n");
    }
}

void moveGhost() {
    int direction;
    Position next;
    do {
        direction = rand() % 4;
        next = ghost;
        if (direction == 0) next.x++;
        else if (direction == 1) next.x--;
        else if (direction == 2) next.y++;
        else if (direction == 3) next.y--;
    } while (maze[next.y][next.x] == '#' || next.x < 0 || next.x >= WIDTH - 1 || next.y < 0 || next.y >= HEIGHT);

    ghost = next;
}

void movePacman(char input) {
    Position next = pacman;
    if (input == 'w') next.y--;
    else if (input == 's') next.y++;
    else if (input == 'a') next.x--;
    else if (input == 'd') next.x++;

    if (maze[next.y][next.x] != '#') {
        if (maze[next.y][next.x] == '.') {
            score++;
            maze[next.y][next.x] = ' ';
        }
        pacman = next;
    }
}

int checkGameOver() {
    return (pacman.x == ghost.x && pacman.y == ghost.y);
}

int checkWin() {
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            if (maze[i][j] == '.') return 0;
        }
    }
    return 1;
}

void gameLoop() {
    char input;
    while (1) {
        drawMaze();
        input = getchar();

        movePacman(input);
        if (checkGameOver()) {
            pacman.x = -1; // Pacman menghilang dari labirin
            pacman.y = -1; // Pacman menghilang dari labirin
            drawMaze();
            printf("\nGame Over! Your Score: %d\n", score);
            saveHighScore();
            break;
        }

        moveGhost();
        if (checkGameOver()) {
            pacman.x = -1; // Pacman menghilang dari labirin
            pacman.y = -1; // Pacman menghilang dari labirin
            drawMaze();
            printf("\nGame Over! Your Score: %d\n", score);
            saveHighScore();
            break;
        }

        if (checkWin()) {
            drawMaze();
            printf("\nYou Win! Your Score: %d\n", score);
            saveHighScore();
            break;
        }
    }
}

int main() {
    srand(time(NULL));
    initializeGame();
    gameLoop();
    return 0;
}

