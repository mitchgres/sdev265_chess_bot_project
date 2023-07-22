#ifndef __BISHOP_H__
#define __BISHOP_H__

#include "../Piece.h"

class Bishop : public Piece {
public:
    Bishop(const Position position, bool is_black);
    virtual PIECE _get_ID() const override;
private:
    virtual void update_movements_and_attacks(Board* board) override;
};

#endif