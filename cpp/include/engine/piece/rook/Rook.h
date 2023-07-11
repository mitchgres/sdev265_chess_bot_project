#ifndef __ROOK_H__
#define __ROOK_H__

#include "../Piece.h"

class Rook : public Piece {
public:
    Rook(Position);
    PIECE _getID() const override;
    Position* _getLegalMoves() const override;
    Position* _getLegalAttackMoves() const override;
    Position* _getAllLegalMoves() const override;

private:
    bool _canTake(const Piece&) const override;
    bool _canMove(const Position&) const override;
    Position* _getUnprocessedMoves() const override;
    Position* _getUnprocessedAttackMoves() const override;
    Position* _processMoves(const Position*&) const override;
};

#endif
