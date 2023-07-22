#include <stdio.h>
#include <string.h>

#include "King.h"

Piece::PIECE King::_get_ID() const { return Piece::PIECE::KING; }

void King::update_movements_and_attacks(Board *board)
{
    // The actual implementation here goes counter-clockwise from the move right in-front of the King.
    Position top_movement(
        _get_position()._horizontial,
        _get_position()._vertical + 1);

    Position top_left_movement(
        _get_position()._horizontial - 1,
        _get_position()._vertical + 1);

    Position middle_left_movement(
        _get_position()._horizontial - 1,
        _get_position()._vertical);

    Position bottom_left_movement(
        _get_position()._horizontial - 1,
        _get_position()._vertical - 1);

    Position bottom_movement(
        _get_position()._horizontial,
        _get_position()._vertical - 1);

    Position bottom_right_movement(
        _get_position()._horizontial + 1,
        _get_position()._vertical - 1);

    Position middle_right_movement(
        _get_position()._horizontial + 1,
        _get_position()._vertical);

    Position top_right_movement(
        _get_position()._horizontial + 1,
        _get_position()._vertical + 1);

    // First we'll check for movements.
    if (is_movement_valid(top_movement, board))
        all_possible_movements.push_back(top_movement);
    if (is_movement_valid(top_left_movement, board))
        all_possible_movements.push_back(top_left_movement);
    if (is_movement_valid(middle_left_movement, board))
        all_possible_movements.push_back(middle_left_movement);
    if (is_movement_valid(bottom_left_movement, board))
        all_possible_movements.push_back(bottom_left_movement);
    if (is_movement_valid(bottom_movement, board))
        all_possible_movements.push_back(bottom_movement);
    if (is_movement_valid(bottom_right_movement, board))
        all_possible_movements.push_back(bottom_right_movement);
    if (is_movement_valid(middle_right_movement, board))
        all_possible_movements.push_back(middle_right_movement);
    if (is_movement_valid(top_right_movement, board))
        all_possible_movements.push_back(top_right_movement);
    // All generated movements added.

    // Then we'll check for attacks.
    if (is_attack_valid(top_movement, board))
        all_possible_attacks.push_back(top_movement);
    if (is_attack_valid(top_left_movement, board))
        all_possible_attacks.push_back(top_left_movement);
    if (is_attack_valid(middle_left_movement, board))
        all_possible_attacks.push_back(middle_left_movement);
    if (is_attack_valid(bottom_left_movement, board))
        all_possible_attacks.push_back(bottom_left_movement);
    if (is_attack_valid(bottom_movement, board))
        all_possible_attacks.push_back(bottom_movement);
    if (is_attack_valid(bottom_right_movement, board))
        all_possible_attacks.push_back(bottom_right_movement);
    if (is_attack_valid(middle_right_movement, board))
        all_possible_attacks.push_back(middle_right_movement);
    if (is_attack_valid(top_right_movement, board))
        all_possible_attacks.push_back(top_right_movement);

    // I think this is the most inefficent part of the program, but needed. We need to check whether the king is in check when you move to a new place.
    // This involves going through all the movements and deleting the move from the list if it puts the king in check.

    std::list<Position> all_movements_and_attacks;
    all_movements_and_attacks = all_possible_movements;

    for (Position position : all_possible_attacks)
    {
        all_movements_and_attacks.push_back(position);
    }

    // Now we'll implement it so the king cannot move or capture into a position where another piece can attack it.

    std::list<Piece *> all_opposing_pieces = board->_get_all_opposing_pieces(_is_black());
    for (Position position : all_movements_and_attacks)
    {
        for (Piece *enemy_piece : all_opposing_pieces)
        {
            // We'll need to check if the enemy piece is a king through an if-else statement and check if the two kings are close to each other. 
            // If we process it normally then we get infinite recursion.
            if (enemy_piece->_get_ID() == Piece::PIECE::KING)
            {
                // We'll need to check if the generated movements would generate a movement that would put the king next to the other king. 
                // If it does then we'll need to remove it from the list.
                if (position._horizontial == enemy_piece->_get_position()._horizontial + 1 && position._vertical == enemy_piece->_get_position()._vertical + 1)
                {
                    all_possible_movements.remove(position);
                }
                else if (position._horizontial == enemy_piece->_get_position()._horizontial + 1 && position._vertical == enemy_piece->_get_position()._vertical)
                {
                    all_possible_movements.remove(position);
                }
                else if (position._horizontial == enemy_piece->_get_position()._horizontial + 1 && position._vertical == enemy_piece->_get_position()._vertical - 1)
                {
                    all_possible_movements.remove(position);
                }
                else if (position._horizontial == enemy_piece->_get_position()._horizontial && position._vertical == enemy_piece->_get_position()._vertical + 1)
                {
                    all_possible_movements.remove(position);
                }
                else if (position._horizontial == enemy_piece->_get_position()._horizontial && position._vertical == enemy_piece->_get_position()._vertical - 1)
                {
                    all_possible_movements.remove(position);
                }
                else if (position._horizontial == enemy_piece->_get_position()._horizontial - 1 && position._vertical == enemy_piece->_get_position()._vertical + 1)
                {
                    all_possible_movements.remove(position);
                }
                else if (position._horizontial == enemy_piece->_get_position()._horizontial - 1 && position._vertical == enemy_piece->_get_position()._vertical)
                {
                    all_possible_movements.remove(position);
                }
                else if (position._horizontial == enemy_piece->_get_position()._horizontial - 1 && position._vertical == enemy_piece->_get_position()._vertical - 1)
                {
                    all_possible_movements.remove(position);
                }
                else
                {
                    // Do nothing because the king is not next to the other king.
                }
            }
            else 
            {
                // We'll need to check if the enemy piece can attack the king. If it can then we'll need to remove it from the list.
                Board board_copy = board->_get_copy();

                // Now update the board so that the king has moved to the position.
                Position starting_position = _get_position();
                board_copy._update(starting_position, position);

                // Now we'll iterate through all the enemy attacks for this board configuration and see if the king is in any of them.
                for (Position enemy_attack_square: enemy_piece->_get_attacks(&board_copy))
                {
                    if (position == enemy_attack_square)
                    {
                        if (is_attack_valid(position, board)){ all_possible_attacks.remove(position);}
                        else if (is_movement_valid(position, board)){ all_possible_movements.remove(position);}
                    }
                }
            }
        }
    }
}

King::King(const Position position, bool is_black) : Piece(position, is_black)
{
}