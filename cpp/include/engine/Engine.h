#include "board/Board.h"
#include "piece/Piece.h"

// There is no internal state to the engine so all methods are static. 
class Engine {
    public:
        // Random -- Moves are randomly selected by the engine. 
        // Simple -- The engine will only take piece if possible. Other than that moves 
        //           are still random.
        // Easy -- 
        // Medium --
        // Hard
        enum LEVEL {
            RANDOM,
            SIMPLE,
            EASY,
            MEDIUM, 
            HARD
        };

        static double _evaluateBoard(const Board&);
        static Position _getBestMove(const Board&);
    private:
        LEVEL _level;
};