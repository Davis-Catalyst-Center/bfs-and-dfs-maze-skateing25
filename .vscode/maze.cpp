#include <iostream>
#include <queue>
#include <stack>

using namespace std;

const int ROWS = 5;
const int COLS = 5;
int maze[ROWS][COLS] = {
    {0, 1, 0, 0, 0},
    {0, 1, 0, 1, 0},
    {0, 0, 0, 1, 0},
    {0, 1, 1, 1, 0},
    {0, 0, 0, 0, 0}
};

struct Cell {
    int x;
    int y;
    Cell* parent;
};

bool isValid(int x, int y, bool visited[][COLS]) {
    return (x >= 0 && x < ROWS && y >= 0 && y < COLS && !visited[x][y] && maze[x][y] == 0);
}

bool solveMaze() {
    queue<Cell*> q;
    bool visited[ROWS][COLS] = { false };

    Cell* start = new Cell{ 0, 0, nullptr };
    q.push(start);
    visited[0][0] = true;

    while (!q.empty()) {
        Cell* current = q.front();
        q.pop();

        if (current->x == ROWS - 1 && current->y == COLS - 1) {
            stack<Cell*> path;
            Cell* temp = current;
            while (temp != nullptr) {
                path.push(temp);
                temp = temp->parent;
            }
            cout << "Path: ";
            while (!path.empty()) {
                Cell* cell = path.top();
                path.pop();
                cout << "(" << cell->x << "," << cell->y << ")";
            }
            cout << endl;

            // Clean up memory
            while (!q.empty()) {
                delete q.front();
                q.pop();
            }
            delete start;
            return true;
        }

        int dx[] = { -1, 1, 0, 0 };
        int dy[] = { 0, 0, 1, -1 };
        for (int i = 0; i < 4; i++) {
            int newX = current->x + dx[i];
            int newY = current->y + dy[i];
            if (isValid(newX, newY, visited)) {
                Cell* next = new Cell{ newX, newY, current };
                q.push(next);
                visited[newX][newY] = true;
            }
        }
    }

    cout << "No path found." << endl;
    while (!q.empty()) {
        delete q.front();
        q.pop();
    }
    delete start;

    return false;
}

int main() {
    solveMaze();
    return 0;
}
