#ifndef __KING_H__
#define __KING_H__

#include <list>
#include <stdio.h>


#include "../Piece.h"

class King : public Piece {
    public:
        King(const Position position, bool is_black);
        virtual PIECE _get_ID() const override;
    private:
        virtual void update_movements_and_attacks(Board* board) override;
};


#endif