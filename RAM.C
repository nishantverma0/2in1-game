#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>

#define WIDTH 20
#define HEIGHT 10

int spaceshipX, spaceshipY;
int laserX, laserY;
int asteroidX, asteroidY;

int score = 0;
int gameover = 0;

void setup();
void draw();
void input();
void update();

int main() {
    setup();

    while (!gameover) {
        draw();
        input();
        update();
        Sleep(100);  // Adjust the delay based on your desired game speed
        system("cls");
    }

    printf("Game Over! Your score: %d\n", score);
    return 0;
}

void setup() {
    spaceshipX = WIDTH / 2;
    spaceshipY = HEIGHT - 1;
    laserX = -1;
    laserY = -1;
    asteroidX = rand() % WIDTH;
    asteroidY = 0;
}

void draw() {
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            if ((i == spaceshipY) && (j == spaceshipX))
                printf("S");
            else if ((i == laserY) && (j == laserX))
                printf("|");
            else if ((i == asteroidY) && (j == asteroidX))
                printf("A");
            else
                printf(" ");
        }
        printf("\n");
    }
    printf("Score: %d\n", score);
}

void input() {
    if (_kbhit()) {
        switch (_getch()) {
            case 'a':
                spaceshipX = (spaceshipX - 1 + WIDTH) % WIDTH;
                break;
            case 'd':
                spaceshipX = (spaceshipX + 1) % WIDTH;
                break;
            case ' ':
                if (laserY == -1) {
                    laserX = spaceshipX;
                    laserY = spaceshipY - 1;
                }
                break;
            case 'x':
                gameover = 1;
                break;
        }
    }
}

void update() {
    if (asteroidY == HEIGHT - 1) {
        asteroidX = rand() % WIDTH;
        asteroidY = 0;
    } else {
        asteroidY++;
    }

    if (laserY >= 0) {
        if ((laserX == asteroidX) && (laserY == asteroidY)) {
            score += 10;
            laserX = -1;
            laserY = -1;
            asteroidX = rand() % WIDTH;
            asteroidY = 0;
        } else {
            laserY--;
        }
    }
}

