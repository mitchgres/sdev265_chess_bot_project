#include <string>

#include "board/Board.h"
#include "piece/Piece.h"
#include "move/Move.h"

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


        inline static int _set_level(LEVEL);
        inline static LEVEL _get_level();
        static double _evaluate_board(const Board&);
        static Move _get_best_move(const Board&);
        static std::string _as_FEN(const Move&);
        static Move _as_engine_data_types(const std::string&);
    private:
        static LEVEL LEVEL;
};