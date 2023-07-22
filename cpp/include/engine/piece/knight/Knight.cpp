#include "Knight.h"

Piece::PIECE Knight::_get_ID() const { return Piece::PIECE::KNIGHT; }

void Knight::update_movements_and_attacks(Board* board)
{
    Position top_left_movement(
        _get_position()._horizontial - 1, 
        _get_position()._vertical + 2
    );

    Position top_middle_left_movement(
        _get_position()._horizontial - 2, 
        _get_position()._vertical + 1        
    );

    Position bottom_middle_left_movement(
        _get_position()._horizontial - 2, 
        _get_position()._vertical - 1
    );

    Position bottom_left_movement(
        _get_position()._horizontial - 1, 
        _get_position()._vertical - 2
    );

    Position top_right_movement(
        _get_position()._horizontial + 1, 
        _get_position()._vertical + 2
    );

    Position top_middle_right_movement(
        _get_position()._horizontial + 2, 
        _get_position()._vertical + 1
    );

    Position bottom_middle_right_movement(
        _get_position()._horizontial + 2, 
        _get_position()._vertical - 1
    );

    Position bottom_right_movement(
        _get_position()._horizontial + 1, 
        _get_position()._vertical - 2
    );
    // First we'll check for movements. 
    if (is_movement_valid(top_left_movement, board)) all_possible_movements.push_back(top_left_movement);
    if (is_movement_valid(top_middle_left_movement, board)) all_possible_movements.push_back(top_middle_left_movement);
    if (is_movement_valid(bottom_middle_left_movement, board)) all_possible_movements.push_back(bottom_middle_left_movement);
    if (is_movement_valid(bottom_left_movement, board)) all_possible_movements.push_back(bottom_left_movement);
    if (is_movement_valid(top_right_movement, board)) all_possible_movements.push_back(top_right_movement);
    if (is_movement_valid(top_middle_right_movement, board)) all_possible_movements.push_back(top_middle_right_movement);
    if (is_movement_valid(bottom_middle_right_movement, board)) all_possible_movements.push_back(bottom_middle_right_movement);
    if (is_movement_valid(bottom_right_movement, board)) all_possible_movements.push_back(bottom_right_movement);
    // All generated movements added. 

    // Then we'll check for attacks. 
    if (is_attack_valid(top_left_movement, board)) all_possible_attacks.push_back(top_left_movement);
    if (is_attack_valid(top_middle_left_movement, board)) all_possible_attacks.push_back(top_middle_left_movement);
    if (is_attack_valid(bottom_middle_left_movement, board)) all_possible_attacks.push_back(bottom_middle_left_movement);
    if (is_attack_valid(bottom_left_movement, board)) all_possible_attacks.push_back(bottom_left_movement);
    if (is_attack_valid(top_right_movement, board)) all_possible_attacks.push_back(top_right_movement);
    if (is_attack_valid(top_middle_right_movement, board)) all_possible_attacks.push_back(top_middle_right_movement);
    if (is_attack_valid(bottom_middle_right_movement, board)) all_possible_attacks.push_back(bottom_middle_right_movement);
    if (is_attack_valid(bottom_right_movement, board)) all_possible_attacks.push_back(bottom_right_movement);
}

Knight::Knight(const Position position, bool is_black): Piece(position, is_black)
{

}
