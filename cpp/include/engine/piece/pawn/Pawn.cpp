#include <list>

#include "Pawn.h"

// Implementation of construction is difference for Pawn since because of En Passant condition we must keep the last recorded position of the Pawn.
Pawn::Pawn(const Position starting_position, bool is_black):  Piece(starting_position, is_black)
{
    Position null_position(-1, -1); // Set the initial position to the NULL position also used to determine whether a piece is off the board. 
    previous_position = null_position;
}

Piece::PIECE Pawn::_get_ID() const { return Piece::PIECE::PAWN; }

void Pawn::update_movements_and_attacks(Board* board)
{
    // Black/White Conversion Constant
    int BLACK_WHITE_CONVERSION_PRODUCT = (_is_black()) ? (-1) : (1); // Black moves down the board (-1) and white moves up (1).
    int EN_PASSANT_PREVIOUS_MOVE_CRITEA = (_is_black()) ? (1) : (6);
    int BLACK_WHITE_PAWN_STARTING_RANK = (_is_black()) ? (6) : (1);

    // First. We'll do movement...
    Position single_jump_up (_get_position()._horizontial, _get_position()._vertical + BLACK_WHITE_CONVERSION_PRODUCT);
    Position double_jump_up (_get_position()._horizontial, _get_position()._vertical + (2 * BLACK_WHITE_CONVERSION_PRODUCT));

    if (is_movement_valid(single_jump_up, board)){ all_possible_movements.push_back(single_jump_up); }

    if (is_movement_valid(double_jump_up, board) && _get_position()._vertical  == BLACK_WHITE_PAWN_STARTING_RANK){ all_possible_movements.push_back(double_jump_up); }

    // Next. We'll do attacks...
    Position left_capture_position(_get_position()._horizontial - 1, _get_position()._vertical + BLACK_WHITE_CONVERSION_PRODUCT);
    Position right_capture_position(_get_position()._horizontial + 1, _get_position()._vertical + BLACK_WHITE_CONVERSION_PRODUCT);

    // First in this step we'll need to see if there is a piece that can be taken regular. 
    if (is_attack_valid(left_capture_position, board)) all_possible_attacks.push_back(left_capture_position);
    if (is_attack_valid(right_capture_position, board)) all_possible_attacks.push_back(right_capture_position);

    // Now let's check for En Passant. 
    
    // Check the left side for En Passant.
    left_capture_position._vertical + BLACK_WHITE_CONVERSION_PRODUCT;
    right_capture_position._vertical + BLACK_WHITE_CONVERSION_PRODUCT;

    if (board->get_piece_at(left_capture_position) != nullptr)
    {
        if (board->get_piece_at(left_capture_position)->_get_ID() == PAWN)
        {
            if (board->get_piece_at(left_capture_position)->_get_ID() == PAWN)
            {
                // We know it's a pawn so let's cast it to one so that we can use Pawn-specific method for determination if it's last move was from starting rank.
                Pawn* other_pawn = static_cast<Pawn*>(board->get_piece_at(left_capture_position));
                if (other_pawn->_get_previous_position()->_vertical == EN_PASSANT_PREVIOUS_MOVE_CRITEA){ all_possible_attacks.push_back(left_capture_position); } 
            }
        }
    }

    // Now let's check the right side.
    if (board->get_piece_at(right_capture_position) != nullptr)
    {
        if (board->get_piece_at(right_capture_position)->_get_ID() == PAWN)
        {
            // We know it's a pawn so let's cast it to one so that we can use Pawn-specific method for determination if it's last move was from starting rank.
            Pawn* other_pawn = static_cast<Pawn*>(board->get_piece_at(right_capture_position));
            if (other_pawn->_get_previous_position()->_vertical == EN_PASSANT_PREVIOUS_MOVE_CRITEA){ all_possible_attacks.push_back(right_capture_position); } 
        }
    }
}

void Pawn::_set_position(const Position new_position)
{
    // We set the current position as the previous and then update the position to the new one. 
    previous_position = _get_position();
    Piece::_set_position(new_position);
}


const Position* Pawn::_get_previous_position()
{
    return &previous_position;
}
