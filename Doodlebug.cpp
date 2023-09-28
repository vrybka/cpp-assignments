/*
The goal for this Project is to create a simple two-dimensional predator-prey simulation. In this simulation the prey are ants and the pred-ators are doodlebugs. 
These critters live in a world composed of a 20 � 20 grid of cells. Only one critter may occupy a cell at a time. 
The grid is  enclosed, so a critter is not allowed to move off the edges of the world. Time is simulated in time steps. 
Each critter performs some action every time step.

The ants behave according to the following model:
Move. Every time step, randomly try to move up, down, left, or right. 
If the neighboring cell in the selected direction is occupied or would move the ant off the grid, then the ant stays in the current cell.

Breed. If an ant survives for three time steps, then at the end of the time step (that is; after moving) the ant will breed. 
This is simulated by creat-ing a new ant in an adjacent (up, down, left, or right) cell that is empty. 
If there is no empty cell available, then no breeding occurs. 
Once an off-spring is produced, an ant cannot produce an offspring until three more time steps have elapsed.

The doodlebugs behave according to the following model:
Move. Every time step, if there is an adjacent ant (up, down, left, or right), then the doodlebug will move to that cell and eat the ant. 
Otherwise, the doodlebug moves according to the same rules as the ant. Note that a doodlebug cannot eat other doodlebugs.

Breed. If a doodlebug survives for eight time steps, then at the end of the time step it will spawn off a new doodlebug in the same manner as the ant.

Starve. If a doodlebug has not eaten an ant within the last three time steps, then at the end of the third time step it will starve and die. 
The doodlebug should then be removed from the grid of cells.

During one turn, all the doodlebugs should move before the ants do.

Draw the world using ASCII characters of �o� for an ant and �X� for a doodlebug or "-" for an empty space. 
Create a class named Organism that encapsulates basic data common to both ants and doodlebugs. 
This class should have a virtual function named move that is defined in the derived classes of Ant and Doodlebug. 
You may need additional data structures to keep track of which critters have moved.

Initialize the world with 5 doodlebugs and 100 ants. 
After each time step, prompt the user to press Enter to move to the next time step. 
You should see a cyclical pattern between the population of predators and prey, although random perturbations may lead to the elimination of one or both species.
*/

#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

const int SIZE = 20;
const int BUG = 1;
const int ANT = 2;

class Grid {
    friend class Organism;
    friend class Ant;
    friend class Bug;

public:
    Grid();
    void initializeGrid();
    void display();
    void oneTimeStep();
    Organism* getCords(int x, int y);
    void set(int x, int y, Organism* o);

protected:
    Organism* grid[SIZE][SIZE];
    int timeStep = 0;
};

class Organism {
public:
    Organism() : gridPos(nullptr), x(0), y(0), breedTime(0), timeStep(0) {}
    Organism(Grid* grid, int x, int y);
    virtual void move();
    virtual void breed() = 0;
    virtual bool starve() = 0;
    virtual int getType() = 0;
    void movePos(int& x, int& y);

protected:
    Grid* gridPos;
    int x, y, breedTime, timeStep;
};

class Ant : public Organism {
public:
    Ant(): Organism(){}
    Ant(Grid* grid, int x, int y); 
    int getType() { return ANT; }
    //void move(); //-> use organism's move 
    void breed();
    bool starve() { return false; }

};

class Bug : public Organism {
    friend class Grid;
    friend class Organism;
public:
    Bug(): Organism (), starveCount(0){}
    Bug(Grid* grid, int x, int y);
    int getType() { return BUG; }
    void move();
    void breed();
    bool starve();

private:
    int starveCount;
};

Grid::Grid() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            grid[i][j] = nullptr;
        }
    }
}

void Grid::initializeGrid() {
    int x, y;

    //initialize 100 ants 
    for (int i = 0; i < 100; i++) {
        x = rand() % 20;
        y = rand() % 20;
        grid[x][y] = new Ant(this, x, y);
    }

    //initialize 5 bugs
    for (int i = 0; i < 5; i++) {
        x = rand() % 20;
        y = rand() % 20;
        if (grid[x][y] == nullptr) {
            grid[x][y] = new Bug(this, x, y);
        }
    }
}

void Grid::display() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (grid[i][j] == nullptr) {
                cout << "-";
            }
            else if (grid[i][j] -> getType() == BUG) {
                cout << "X";
            }
            else {
                cout << "O";
            }
        }
        cout << endl;
    }
}

void Grid::oneTimeStep() {
    //move bugs 
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if ((grid[i][j] != nullptr) && (grid[i][j]->getType() == BUG)) {
                grid[i][j]->move();
            }
        }
    }

    //move ants
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if ((grid[i][j] != nullptr) && (grid[i][j]->getType() == ANT)) {
                grid[i][j]->move();
            }
        }
    }

    //breed 
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (grid[i][j] != nullptr) {
                grid[i][j]->breed();
            }

        }
    }

    //kill starved bugs
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if ((grid[i][j] != nullptr) && (grid[i][j]->getType() == BUG)) {
                if (grid[i][j]->starve()) {
                    delete (grid[i][j]);
                    grid[i][j] = nullptr;
                }
            }
        }
    }
    timeStep++;
}

Organism* Grid::getCords(int x, int y) {
    if ((x >= 0) && (x < SIZE) && (y >= 0) && (y < SIZE)) {
        return grid[x][y];
    }
    else {
        return nullptr;
    }
}

void Grid::set(int x, int y, Organism* o) {
    if ((x >= 0) && (x < SIZE) && (y >= 0) && (y < SIZE)) {
        grid[x][y] = o;
    }
}

Organism::Organism(Grid* grid, int x, int y) {
    this->gridPos = grid;
    this->x = x;
    this->y = y;
    breedTime = 0;
    timeStep = gridPos->timeStep;
}

void Organism::movePos(int& x, int& y) {
    int move = rand() % 4;
    if (move == 0) { //up
        y++;
    }
    else if (move == 1) { //down
        y--;
    }
    else if (move == 2) { //right
        x++;
    }
    else { //left
        x--;
    }
}

void Organism::move() {
    int x1 = x;
    int y1 = y;
    movePos(x1, y1);

    if (gridPos->grid[x1][y1] != nullptr) {
        return;
    }
    else {
        gridPos->grid[x][y] = nullptr;
        gridPos->grid[x1][y1] = this;
        x = x1;
        y = y1;
    }

    timeStep++;
}

Ant::Ant(Grid* grid, int x, int y) : Organism(grid, x, y) {
    breedTime = 3;
}

void Ant::breed() {
    breedTime++;
    if (breedTime == 3) {
        breedTime = 0;
        if ((x < SIZE - 1) && (gridPos->getCords(x + 1, y) == nullptr)) {
            Ant *ant = new Ant(gridPos, x + 1, y);
        }
        else if ((x > 0) && (gridPos->getCords(x - 1, y) == nullptr)) {
            Ant *ant = new Ant(gridPos, x - 1, y);
        }
        else if ((y < SIZE - 1) && (gridPos->getCords(x, y + 1) == nullptr)) {
            Ant *ant = new Ant(gridPos, x, y + 1);
        }
        else if ((y > 0) && (gridPos->getCords(x, y - 1) == nullptr)) {
            Ant *ant = new Ant(gridPos, x, y - 1);
        }
    }
}

Bug::Bug(Grid* grid, int x, int y) : Organism(grid, x, y) {
    breedTime = 8;
    starveCount = 0;
}

void Bug::move() {
    //eat nearby ants
    if ((x<SIZE - 1)&&(gridPos->getCords(x + 1, y)!=nullptr)&&(gridPos->getCords(x + 1, y)->getType() == ANT)) {
        delete (gridPos->grid[x + 1][y]);
        gridPos->grid[x + 1][y] = this;
        gridPos->set(x, y, nullptr);
        starveCount = 0;
        x++;
        return;
    }
    else if ((x >0) && (gridPos->getCords(x - 1, y) != nullptr) && (gridPos->getCords(x - 1, y)->getType() == ANT)) {
        delete (gridPos->grid[x - 1][y]);
        gridPos->grid[x - 1][y] = this;
        gridPos->set(x, y, nullptr);
        starveCount = 0;
        x--;
        return;
    }
    else if ((y < SIZE - 1) && (gridPos->getCords(x, y + 1) != nullptr) && (gridPos->getCords(x, y + 1)->getType() == ANT)) {
        delete (gridPos->grid[x][y+1]);
        gridPos->grid[x][y+1] = this;
        gridPos->set(x, y, nullptr);
        starveCount = 0;
        y++;
        return;
    }
    else if ((y > 0) && (gridPos->getCords(x, y - 1) != nullptr) && (gridPos->getCords(x, y - 1)->getType() == ANT)) {
        delete (gridPos->grid[x][y - 1]);
        gridPos->grid[x][y - 1] = this;
        gridPos->set(x, y, nullptr);
        starveCount = 0;
        y--;
        return;
    }
    else { //if no ants nearby move like organism 
        Organism::move();
        starveCount++;
    }
}

void Bug::breed() {
    breedTime++;
    if (breedTime == 8) {
        breedTime = 0;
        if ((x < SIZE - 1) && (gridPos->getCords(x + 1, y) == nullptr)) {
            Bug *bug = new Bug(gridPos, x + 1, y);
        }
        else if ((x > 0) && (gridPos->getCords(x - 1, y) == nullptr)) {
            Bug *bug = new Bug(gridPos, x - 1, y);
        }
        else if ((y < SIZE - 1) && (gridPos->getCords(x, y + 1) == nullptr)) {
            Bug *bug = new Bug(gridPos, x, y + 1);
        }
        else if ((y > 0) && (gridPos->getCords(x, y - 1) == nullptr)) {
            Bug *bug = new Bug(gridPos, x, y - 1);
        }
    }
}

bool Bug::starve() {
    if (starveCount < 3) {
        return false;
    }
    else {
        return true;
    }
}

int main()
{
    Grid g;
    char userInput;
    bool seenEnd = false;

    cout << "Welcome to the predator-prey simulation!" << endl;
    cout << "Initializing critters world:" << endl;
    cout << endl;

    g.initializeGrid();
    g.display();

    while (seenEnd == false) {
        cout << endl;
        cout << "Press 'enter' to advance one time step or any other character to exit." << endl;
        userInput = cin.get();

        if (userInput == '\n') {
            g.oneTimeStep();
            g.display();

        }
        else {
            seenEnd = true;
        }
    }

    return 0;
}
