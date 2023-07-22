#ifndef __ENGINE_H__
#define __ENGINE_H__

#include <string>

#include "board/Board.h"
#include "piece/Piece.h"

class Engine {
    public:
        static Board* get_random_move(Board* board);
        static Board get_simple_move(Board* board);
        static Board get_easy_move(Board* board);
        static Board get_medium_move(Board* board);
        static Board get_hard_move(Board* board);
    private:
        static double evaluate(Board* board);
};
#endif // __ENGINE_H__