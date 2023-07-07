#ifndef __PIECE_H__
#define __PIECE_H__

#include "../position/Position.h"

class Piece {
    public:
        // Used when making descions where different pieces will result in different outcomes.
        // Like in next move descion planning. 
        enum PIECE {
            BISHOP,
            KING,
            KNIGHT,
            PAWN,
            QUEEN,
            ROOK
        };
    
        Piece(Position);
        inline Position _getPosition() const;
        inline void _setPosition(const Position&);
        // Unique for each piece. 
        inline virtual PIECE _getID() const = 0;
        virtual Position* _getLegalMoves() const = 0;
        virtual Position* _getLegalAttackMoves() const = 0;
        // Combination of both attack and regular moves. 
        virtual Position* _getAllLegalMoves() const = 0;
        inline bool _isBlack() const; 
    private:
        Position _position; 
        bool _isBlack;

        virtual bool _canTake(const Piece&) const = 0;
        virtual bool _canMove(const Position&) const = 0;
        virtual Position* _getUnprocessedMoves() const = 0;
        virtual Position* _getUnprocessedAttackMoves() const = 0;
        virtual Position* _processMoves(const Position*&) const = 0;
};
#endif // __PIECE_H__