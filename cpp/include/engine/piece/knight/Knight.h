#ifndef __KNIGHT_H__
#define __KNIGHT_H__

#include "../Piece.h"

class Knight : public Piece {
    public:
        virtual PIECE _get_ID() const override;
        Knight(const Position starting_position, bool is_black);
    private:
        virtual void update_movements_and_attacks(Board* board) override;
};

#endif
