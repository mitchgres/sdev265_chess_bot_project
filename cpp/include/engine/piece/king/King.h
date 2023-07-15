#ifndef __KING_H__
#define __KING_H__

#include <list>

#include "../Piece.h"
#include "../../board/Board.h"

class King : public Piece {
public:
    King(const Position &, bool);
    inline PIECE _get_ID() const;
    inline void _set_position(const Position &);
    bool _can_take(const Piece *other_piece, Board *board) const;
    bool _can_move(const Position&, Board*) const;

private:
    bool _is_in_check_at(const Position&, Board*) const; // Only in the King class. 
    inline std::list<Position> _get_unprocessed_movements() const;
};

#endif
