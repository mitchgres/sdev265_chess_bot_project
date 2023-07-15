#include "King.h"
#include "../../board/Board.h"

King::King(const Position& starting_position, bool is_black): Piece(starting_position, is_black)
{
// No Implementation. 
}

Piece::PIECE King::_get_ID() const
{
    return PIECE::KING;
}

/// @brief All the possible movement the King could make in any position. Does light processing to assure that movements are on a 8x8 board, though no other legal checks are implemented. 
/// @return Unprocessed Potential Movements. 
std::list<Position> King::_get_unprocessed_movements() const
{
    // The King can move...
    // (1) Horizontial One Square.
    // (2) Vertical One Square.
    // (3) Diagonol One Square.

    std::list<Position> unprocessed_movements;

    // Define the directions in which the King can move.
    int directions[8][2] = {
        {1, 0}, 
        {-1, 0}, 
        {0, 1}, 
        {0, -1}, // Horizontial & Vertical Movements
        {1, 1},
        {1, -1},
        {-1, 1},
        {-1, -1} // Diagonol Movements
    };

    // Use iteration to generate the movements based on the changes (dy/dx) that the King could make.
    for (const auto &direction : directions)
    {
        int dx = direction[0];
        int dy = direction[1];
        int x = _get_position()._horizontial + dx;
        int y = _get_position()._vertical + dy;

        // Only some light processing is actually done here and the rest is done later.  
        // Here we'll just make sure that the move generated is one that can exist on 
        // and 8x8 board. We'll make sure it's legal later. 

        Position generated_movement(x, y);
        if (_is_in_bounds(generated_movement))
        {
            unprocessed_movements.push_back(generated_movement);
        }
        // Else: The move was outside of the board 8x8. 
    }

    return unprocessed_movements;
}

bool King::_can_take(const Piece* other_piece, Board* board) const
{
    // The logic for this is the same as it is for movement. We just want to make sure we aren't in check. 
    return _can_move(other_piece->_get_position(), board);
}

bool King::_can_move(const Position &position, Board* board) const
{
    // CONDITION TO BE CONSIDERED WHEN MOVING...
    // (1) Does this put the piece in check?
    return _is_in_check_at(position, board);
}

bool King::_is_in_check_at(const Position& position, Board* board) const
{   // Position is used as the location that th
    for (Piece* piece: board->_get_all()) // Iterate through all the pieces and see if in the new position any piece can attack
    {
        // Have a temporary variables that is passed for seeing if the king object can be taken. 
        King* moved_king = new King(position, _is_black());
         if (piece->_can_take(moved_king, board))
         {
            delete moved_king; // Regardless of outcome we must delete the dynamic variable. 
            return true;
         }
         else
         {
            delete moved_king;
         }
    }

    return false; // If no piece can take the king in that position then the king won't be in check there. 
}
