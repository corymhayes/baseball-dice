#include <string>

class Game {
    private:
        int homeScore, awayScore, outs, innings, runs, side;
        bool firstSwing;
        void switchDice(int dice[]);

    public:
        Game();
        
        int diceRoll[2], bases[4], homeInnings[10], awayInnings[10];

        std::string playOnField(int play[], int bases[]);
        void rollDice();
        void rolling(int dice[]);
        int getOuts();
        int getInnings();
        int getRuns();
        std::string getSide();
        int getHomeScore();
        int getAwayScore();
        int getBaseRunners();
        bool getFirstSwing();
        void setRuns(int);
        void setFirstSwing();
        void scoreboard();
        
        void advanceRunners(int dice[], int bases[]);
        // void getTeamNames();
        void switchSides();

        void single(int bases[]);
        void singleRunnersAdvanceOne(int bases[]);
        void singleRunnersAdvanceTwo(int bases[]);
        void hitDouble(int bases[]);
        void triple(int bases[]);
        void homerun(int bases[]);
        void sacFly(int bases[]);
        
};