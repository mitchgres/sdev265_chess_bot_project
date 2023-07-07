#include "../Piece.h"

class Bishop: public Piece {
    public:
        Position* _getNextPossiblePositions() const;
        inline PIECE _getID() const;
    private:
};