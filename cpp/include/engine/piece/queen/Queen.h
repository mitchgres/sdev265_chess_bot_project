#ifndef __QUEEN_H__
#define __QUEEN_H__

#include "../Piece.h"
#include "../../position/Position.h"

class Queen : public Piece {
    public:
        virtual PIECE _get_ID() const override;
        Queen(const Position position, bool is_black);
    private:
        virtual void update_movements_and_attacks(Board* board) override;
};

#endif
