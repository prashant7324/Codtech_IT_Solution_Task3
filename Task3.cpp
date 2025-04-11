#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

enum Direction { STOP = 0, LEFT, RIGHT, UP, DOWN };
Direction dir;

const int width = 20;
const int height = 20;
int x, y, fruitX, fruitY, score;
vector<pair<int, int>> tail;
int tailLength = 0;
bool gameOver;

void Setup() {
    dir = STOP;
    x = width / 2;
    y = height / 2;
    srand(time(0));
    fruitX = rand() % width;
    fruitY = rand() % height;
    score = 0;
}

void Draw() {
    cout << string(50, '\n'); // clear screen (fake clear)
    for (int i = 0; i < width + 2; i++) cout << "#";
    cout << endl;

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (j == 0) cout << "#";

            if (i == y && j == x)
                cout << "O";
            else if (i == fruitY && j == fruitX)
                cout << "F";
            else {
                bool print = false;
                for (auto t : tail) {
                    if (t.first == j && t.second == i) {
                        cout << "o";
                        print = true;
                        break;
                    }
                }
                if (!print) cout << " ";
            }

            if (j == width - 1) cout << "#";
        }
        cout << endl;
    }

    for (int i = 0; i < width + 2; i++) cout << "#";
    cout << endl;
    cout << "Score: " << score << endl;
    cout << "Move (WASD or X to quit): ";
}

void Input(char move) {
    switch (move) {
    case 'a':
    case 'A':
        if (dir != RIGHT) dir = LEFT;
        break;
    case 'd':
    case 'D':
        if (dir != LEFT) dir = RIGHT;
        break;
    case 'w':
    case 'W':
        if (dir != DOWN) dir = UP;
        break;
    case 's':
    case 'S':
        if (dir != UP) dir = DOWN;
        break;
    case 'x':
    case 'X':
        gameOver = true;
        break;
    default:
        break;
    }
}

void Logic() {
    if (tailLength > 0) {
        tail.insert(tail.begin(), {x, y});
        if (tail.size() > tailLength)
            tail.pop_back();
    }

    switch (dir) {
    case LEFT: x--; break;
    case RIGHT: x++; break;
    case UP: y--; break;
    case DOWN: y++; break;
    default: break;
    }

    if (x >= width || x < 0 || y >= height || y < 0)
        gameOver = true;

    for (auto segment : tail)
        if (segment.first == x && segment.second == y)
            gameOver = true;

    if (x == fruitX && y == fruitY) {
        score += 10;
        fruitX = rand() % width;
        fruitY = rand() % height;
        tailLength++;
    }
}

int main() {
    Setup();
    while (!gameOver) {
        Draw();
        char move;
        cin >> move;
        Input(move);
        Logic();
    }

    cout << "\nGame Over! Final Score: " << score << endl;
    return 0;
}
