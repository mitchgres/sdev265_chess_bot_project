#ifndef __PAWN_H__
#define __PAWN_H__

#include "../Piece.h"

class Pawn : public Piece {
public:
    Pawn(const Position starting_position, bool is_black);
    ~Pawn();
    virtual PIECE _get_ID() const override;
    inline const Position* _get_previous_position();
    inline void _set_position(Position new_postion) override;

private:
    Position previous_position;

    virtual void update_movements_and_attacks(Board* board) override;
};


#endif