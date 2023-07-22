#ifndef __ROOK_H__
#define __ROOK_H__

#include <list>

#include "../Piece.h"
#include "../../position/Position.h"

class Rook : public Piece {
    public:
    Rook(const Position position, bool is_black);
    virtual PIECE _get_ID() const override;
    private:
    virtual void update_movements_and_attacks(Board* board) override;
};

#endif