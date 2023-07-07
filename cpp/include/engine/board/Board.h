#ifndef __BOARD_H__
#define __BOARD_H__

#include "../piece/Piece.h"

class Board {
    public:
        Board();
        ~Board();
        inline Piece* _get() const;
        // Set isn't inline because you'll have a decent amount of processing with it. 
        void _reset();
        void _update(const Piece&);
        void _print() const;
        void _printRaw() const;
    private:
        // Two-Dimensional Array Representation
        Piece* _board;  
};
#endif // __BOARD_H__