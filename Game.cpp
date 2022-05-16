#include <iostream>
#include <string>
#include <ctime>
#include <thread>
#include "Game.h"

using namespace std;

Game::Game() {
    homeScore = 0;
    awayScore = 0;
    outs = 0;
    innings = 1;
    runs = 0;
    side = 0;   // 0 = home; 1 = away
    firstSwing = true;
    diceRoll[0] = 0;
    diceRoll[1] = 0;

    //  0 = home
    //  1 = first
    //  2 = second
    //  3 = third
    for(int i = 0; i <= 3; i++) {
        bases[i] = 0;
    }

    for(int i = 0; i <= 9; i++) {
        homeInnings[i] = 0;
        awayInnings[i] = 0;
    }
}

std::string Game::playOnField(int play[], int bases[]) {
    switch(play[0]) {
        case 1:
            switch(play[1]) {
                case 1: 
                    homerun(bases);
                    return "Home Run";
                case 2:
                    hitDouble(bases);
                    return "Double";
                case 3:
                    outs += 1;
                    return "Fly Out";
                case 4:
                    single(bases);
                    return "Walk";
                case 5:
                    outs += 1;
                    return "Pop Out";
                case 6:
                    singleRunnersAdvanceOne(bases);
                    return "Single, Runners Advance 1 Base";
            }
        case 2:
            switch(play[1]) {
                case 2:
                    if(getBaseRunners() > 1) {
                        outs += 2;
                    } else {
                        outs += 1;
                    }

                    return "Double Play";
                case 3:
                    outs += 1;
                    return "Ground Out";
                case 4:
                    outs += 1;
                    return "Out";
                case 5:
                    singleRunnersAdvanceTwo(bases);
                    return "Single, Runners Advance 2 Bases";
                case 6:
                    outs += 1;
                    return "Out";
            }
        case 3:
            switch(play[1]) {
                case 3:
                    single(bases);
                    return "Walk";
                case 4:
                    single(bases);
                    return "Single";
                case 5:
                    outs += 1;
                    return "Ground Out";
                case 6:
                    outs += 1;
                    return "Fly Out";
            }
        case 4:
            switch(play[1]) {
                case 4:
                    single(bases);
                    return "Walk";
                case 5:
                    outs += 1;
                    return "Pop Out";
                case 6:
                    outs += 1;
                    return "Out";
            }
        case 5:
            switch(play[1]) {
                case 5:
                    outs += 1;
                    return "Strike Out";
                case 6:
                    sacFly(bases);
                    outs += 1;
                    return "Sac Fly, Runners Advance 1 Base";
            }
        case 6:
            switch(play[1]) {
                case 6:
                    triple(bases);
                    return "Triple";
            }
    }

    return "";
}

void Game::rollDice() {
    int diceOne = (rand() % (6 - 1 + 1)) + 1;
    int diceTwo = (rand() % (6 - 1 + 1)) + 1;
    // diceOne = 2;
    // diceTwo = 5;

    diceRoll[0] = diceOne;
    diceRoll[1] = diceTwo;
    switchDice(diceRoll);
}
void Game::switchDice(int dice[]) {
    if(dice[0] > dice[1]) {
        int temp1 = dice[0];
        int temp2 = dice[1];
        dice[0] = temp2;
        dice[1] = temp1;
    }
}

void Game::rolling(int dice[]) {
    std::chrono::milliseconds dura(25);

    for(int i = 0; i < 25; i++) {
        int diceOne = (rand() % (6 - 1 + 1)) + 1;
        int diceTwo = (rand() % (6 - 1 + 1)) + 1;

        cout << getSide() << " rolled: " << diceOne << " " << diceTwo << endl;
        cout << "\x1b[A";
        std::this_thread::sleep_for(dura);
    }

    cout << getSide() << " rolled: " << dice[0] << " " << dice[1] << endl;
}

void Game::advanceRunners(int dice[], int bases[]) {
    switch(dice[0]) {
        case 1:
            switch(dice[1]) {
                case 6:
                    if(bases[0] == 0) {
                        bases[0] = 1;
                    }
            }
    }
}

int Game::getOuts() { return outs; }
int Game::getInnings() { return innings; }
int Game::getRuns() { return runs; }
std::string Game::getSide() { 
    if(side == 0) {
        return "Home";
    } else {
        return "Away";
    }
}
int Game::getHomeScore() { return homeScore; }
int Game::getAwayScore() { return awayScore; }
int Game::getBaseRunners() {
    int playersOnBase = 0;
    
    for(int i = 0; i < 4; i++) {
        if(bases[i] == 1) {
            playersOnBase += 1;
        }
    }

    return playersOnBase;
}
bool Game::getFirstSwing() { return firstSwing; }

void Game::setRuns(int r) {
    runs += r;
}
void Game::setFirstSwing() { firstSwing = false; }

void Game::scoreboard() {
    cout << "           ---------------------------------------------------" << endl;
    cout << "           || 1 || 2 || 3 || 4 || 5 || 6 || 7 || 8 || 9 || T |" << endl;
    cout << "--------------------------------------------------------------" << endl;            
    cout << "|   Away   || " 
            << awayInnings[1] << " || "
            << awayInnings[3] << " || "
            << awayInnings[2] << " || "
            << awayInnings[4] << " || "
            << awayInnings[5] << " || "
            << awayInnings[6] << " || "
            << awayInnings[7] << " || "
            << awayInnings[8] << " || "
            << awayInnings[9] << " || "
            << awayScore << " |" << endl;
    cout << "--------------------------------------------------------------" << endl;

    cout << "|   Home   || " 
            << homeInnings[1] << " || "
            << homeInnings[2] << " || "
            << homeInnings[3] << " || "
            << homeInnings[4] << " || "
            << homeInnings[5] << " || "
            << homeInnings[6] << " || "
            << homeInnings[7] << " || "
            << homeInnings[8] << " || "
            << homeInnings[9] << " || " 
            << homeScore << " |" << endl;
    cout << "--------------------------------------------------------------" << endl;
}

void Game::single(int bases[]) {
    // nobody on
    if(bases[1] == 0 && bases[2] == 0 && bases[3] == 0) {
        bases[1] = 1;
    } 
    // runner on first
    else if(bases[1] == 1 && bases[2] == 0 && bases[3] == 0) {
        bases[2] = 1;
    }
    // runner on second
    else if(bases[1] == 0 && bases[2] == 1 && bases[3] == 0) {
        bases[1] = 1;
    }
    // runner on third
    else if(bases[1] == 0 && bases[2] == 0 && bases[3] == 1) {
        bases[1] = 1;
    }
    // runners on first & second
    else if(bases[1] == 1 && bases[2] == 1 && bases[3] == 0) {
        bases[3] = 1;
    }
    // runners on second & third
    else if(bases[1] == 0 && bases[2] == 1 && bases[3] == 1) {
        bases[1] = 1;
    }
    // runners on the corners
    else if(bases[1] == 1 && bases[2] == 0 && bases[3] == 1) {
        bases[2] = 1;
    }
    // bases loaded
    else if(bases[1] == 1 && bases[2] == 1 && bases[3] == 1) {
        setRuns(1);
    }
}
void Game::singleRunnersAdvanceOne(int bases[]) {
    // nobody on
    if(bases[1] == 0 && bases[2] == 0 && bases[3] == 0) {
        bases[1] = 1;
    } 
    // runner on first
    else if(bases[1] == 1 && bases[2] == 0 && bases[3] == 0) {
        bases[2] = 1;
    }
    // runner on second
    else if(bases[1] == 0 && bases[2] == 1 && bases[3] == 0) {
        bases[1] = 1;
        bases[2] = 0;
        bases[3] = 1;
    }
    // runner on third
    else if(bases[1] == 0 && bases[2] == 0 && bases[3] == 1) {
        bases[1] = 1;
        bases[3] = 0;
        setRuns(1);
    }
    // runners on first & second
    else if(bases[1] == 1 && bases[2] == 1 && bases[3] == 0) {
        bases[3] = 1;
    }
    // runners on second & third
    else if(bases[1] == 0 && bases[2] == 1 && bases[3] == 1) {
        bases[1] = 1;
        bases[3] = 0;
    }
    // runners on the corners
    else if(bases[1] == 1 && bases[2] == 0 && bases[3] == 1) {
        bases[1] = 1;
        bases[2] = 1;
        bases[3] = 0;
        setRuns(1);
    }
    // bases loaded
    else if(bases[1] == 1 && bases[2] == 1 && bases[3] == 1) {
        setRuns(1);
    }
}
void Game::singleRunnersAdvanceTwo(int bases[]) {
    // nobody on
    if(bases[1] == 0 && bases[2] == 0 && bases[3] == 0) {
        bases[1] = 1;
    } 
    // runner on first
    else if(bases[1] == 1 && bases[2] == 0 && bases[3] == 0) {
        bases[3] = 1;
    }
    // runner on second
    else if(bases[1] == 0 && bases[2] == 1 && bases[3] == 0) {
        bases[1] = 1;
        bases[2] = 0;
        setRuns(1);
    }
    // runner on third
    else if(bases[1] == 0 && bases[2] == 0 && bases[3] == 1) {
        bases[1] = 1;
        bases[3] = 0;
        setRuns(1);
    }
    // runners on first & second
    else if(bases[1] == 1 && bases[2] == 1 && bases[3] == 0) {
        bases[2] = 0;
        bases[3] = 1;
        setRuns(1);
    }
    // runners on second & third
    else if(bases[1] == 0 && bases[2] == 1 && bases[3] == 1) {
        bases[1] = 1;
        bases[2] = 0;
        bases[3] = 0;
        setRuns(2);
    }
    // runners on the corners
    else if(bases[1] == 1 && bases[2] == 0 && bases[3] == 1) {
        setRuns(1);
    }
    // bases loaded
    else if(bases[1] == 1 && bases[2] == 1 && bases[3] == 1) {
        bases[2] = 0;
        setRuns(2);
    }
}
void Game::hitDouble(int bases[]) {
    // nobody on
    if(bases[1] == 0 && bases[2] == 0 && bases[3] == 0) {
        bases[2] = 1;
    } 
    // runner on first
    else if(bases[1] == 1 && bases[2] == 0 && bases[3] == 0) {
        bases[1] = 0;
        bases[2] = 1;
        bases[3] = 1;
    }
    // runner on second
    else if(bases[1] == 0 && bases[2] == 1 && bases[3] == 0) {
        bases[2] = 1;
        setRuns(1);
    }
    // runner on third
    else if(bases[1] == 0 && bases[2] == 0 && bases[3] == 1) {
        bases[2] = 1;
        bases[3] = 0;
        setRuns(1);
    }
    // runners on first & second
    else if(bases[1] == 1 && bases[2] == 1 && bases[3] == 0) {
        bases[3] = 1;
        setRuns(1);
    }
    // runners on second & third
    else if(bases[1] == 0 && bases[2] == 1 && bases[3] == 1) {
        bases[3] = 0;
        setRuns(2);
    }
    // runners on the corners
    else if(bases[1] == 1 && bases[2] == 0 && bases[3] == 1) {
        bases[1] = 0;
        bases[2] = 1;
        setRuns(1);
    }
    // bases loaded
    else if(bases[1] == 1 && bases[2] == 1 && bases[3] == 1) {
        bases[1] = 0;
        bases[2] = 1;
        bases[3] = 1;
        setRuns(2);
    }
}
void Game::triple(int bases[]) {
    // nobody on
    if(bases[1] == 0 && bases[2] == 0 && bases[3] == 0) {
        bases[3] = 1;
    } 
    // runner on first
    else if(bases[1] == 1 && bases[2] == 0 && bases[3] == 0) {
        bases[1] = 0;
        bases[3] = 1;
        setRuns(1);
    }
    // runner on second
    else if(bases[1] == 0 && bases[2] == 1 && bases[3] == 0) {
        bases[2] = 0;
        bases[3] = 1;
        setRuns(1);
    }
    // runner on third
    else if(bases[1] == 0 && bases[2] == 0 && bases[3] == 1) {
        setRuns(1);
    }
    // runners on first & second
    else if(bases[1] == 1 && bases[2] == 1 && bases[3] == 0) {
        bases[1] = 0;
        bases[2] = 0;
        bases[3] = 1;
        setRuns(1);
    }
    // runners on second & third
    else if(bases[1] == 0 && bases[2] == 1 && bases[3] == 1) {
        setRuns(2);
    }
    // runners on the corners
    else if(bases[1] == 1 && bases[2] == 0 && bases[3] == 1) {
        bases[1] = 0;
        setRuns(2);
    }
    // bases loaded
    else if(bases[1] == 1 && bases[2] == 1 && bases[3] == 1) {
        bases[1] = 0;
        bases[2] = 0;
        bases[3] = 1;
        setRuns(3);
    }
}
void Game::homerun(int bases[]) {
    setRuns(1);

    for(int i = 1; i <= 3; i++) {
        if(bases[i] == 1) {
            setRuns(1);
        }

        bases[i] = 0;
    }
}
void Game::sacFly(int bases[]) {
    // nobody on
    // if(bases[1] == 0 && bases[2] == 0 && bases[3] == 0) {
    //     (1);
    // } 
    // runner on first
    if(bases[1] == 1 && bases[2] == 0 && bases[3] == 0) {
        bases[2] = 1;
    }
    // runner on second
    else if(bases[1] == 0 && bases[2] == 1 && bases[3] == 0) {
        bases[2] = 0;
        bases[3] = 1;
    }
    // runner on third
    else if(bases[1] == 0 && bases[2] == 0 && bases[3] == 1) {
        bases[3] = 0;
        setRuns(1);
    }
    // runners on first & second
    else if(bases[1] == 1 && bases[2] == 1 && bases[3] == 0) {
        bases[3] = 1;
    }
    // runners on second & third
    else if(bases[1] == 0 && bases[2] == 1 && bases[3] == 1) {
        bases[2] = 0;
        setRuns(1);
    }
    // runners on the corners
    else if(bases[1] == 1 && bases[2] == 0 && bases[3] == 1) {
        bases[1] = 0;
        bases[2] = 1;
        bases[3] = 0;
        setRuns(1);
    }
    // bases loaded
    else if(bases[1] == 1 && bases[2] == 1 && bases[3] == 1) {
        bases[1] = 0;
        setRuns(1);
    }
}

void Game::switchSides(){
    if(side == 0) {
        homeScore += runs;
        homeInnings[innings] = runs;
        firstSwing = true;
        side = 1;
    } else {
        awayScore += runs;
        awayInnings[innings] = runs;
        firstSwing = true;
        side = 0;
        innings += 1;
    }
    
    for(int i = 0; i <= 3; i++) {
        bases[i] = 0;
    }
    
    diceRoll[0] = 0;
    diceRoll[1] = 0;
    outs = 0;
    runs = 0;
}

