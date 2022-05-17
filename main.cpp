#include <iostream>
#include <cstdlib>
#include <cstring>
#include <vector>
#include "Game.h"

using namespace std;

int main() {
    unsigned seed;seed=time(0);srand(seed);
    char rollDice;
    char ready;
    char gameStart;
    Game game;

    cout << "Start game? ";
    cin >> gameStart;

    if(gameStart == 'y') {
        do {
            while(game.getOuts() <= 2) {
                system("clear");

                game.scoreboard();
                
                if(!game.getFirstSwing()) {
                    game.rollDice();
                    game.rolling(game.diceRoll);
                } else {
                    cout << game.getSide() << " rolled: " << game.diceRoll[0] << " " << game.diceRoll[1] << endl;
                }
                cout << "Play on the field: " << game.playOnField(game.diceRoll, game.bases) << endl;
                cout << "Outs: " << game.getOuts() << endl;
                cout << "Runs for " << game.getSide() << " this inning: " << game.getRuns() << endl << endl;

                cout << "   " << game.bases[2] << "   " << endl;
                cout << " " << game.bases[3] << "   " << game.bases[1] << " " << endl;
                cout << "   " << game.bases[0] << "   " << endl << endl;

                if(game.getOuts() <= 2) {
                    cout << "Swing? ";
                    cin >> rollDice;
                    game.setFirstSwing();
                } else {
                    game.switchSides();
                    cout << "SWITCHING SIDES" << endl;
                    clock_t now = clock();
                    while(clock() - now < (3 * CLOCKS_PER_SEC));
                }
            }
        } while(rollDice == 'Y');
    }

    return 0;
}
