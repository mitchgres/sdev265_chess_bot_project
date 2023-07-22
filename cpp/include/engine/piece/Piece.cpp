#include <list>
#include <iostream>

#include "Piece.h"
#include "../position/Position.h"
#include "../board/Board.h"

// GENERAL STRUCTURE OF PROCESSING A MOVEMENT...
// (1): We get all of the spaces on the board. (64 Total)
// (2): We'll go through all the spaces with the function _can_move() if it can move to that space then it's put into a list. 
//      (2a): If horizontial & vertical movement iterate upward and if you run into a piece if it's a friend then don't add to list, but if not then add.
//      (2b): If diagonol do that same things but with the difference movement pattern. 
//      (2c): For the horse and other pieces we don't really have to worry about hitting pieces as we do with the other pieces. 
// (3): Called by the function _get_attacks() we'll find all the moves in the list that move to a position of a current enemy piece. That's an attack.

Piece::Piece(const Position starting_position, bool is_black)
{
    position = starting_position;
    this->is_black = is_black;
}

Position Piece::_get_position() const
{
    return position;
}


void Piece::_set_position(Position new_postion)
{
    position = new_postion;
}


std::list<Position> Piece::_get_movements(Board* board)
{
    all_possible_movements.clear();

    update_movements_and_attacks(board);
    return all_possible_movements;
}

std::list<Position> Piece::_get_attacks(Board* board)
{
    all_possible_attacks.clear();

    update_movements_and_attacks(board);
    return all_possible_attacks;
}

bool Piece::_is_black() const
{
    return is_black;
}

bool Piece::_is_in_bounds(const Position * position)
{
    return _is_in_bounds(position->_horizontial, position->_vertical);
}

bool Piece::_is_in_bounds(int horizontial, int vertical)
{
    if (horizontial > 7 || horizontial < 0 || vertical > 7 || vertical < 0){ return false; }
    else { return true; }
}

bool Piece::_is_square_blocked(const Position* target_position, Board* board)
{
    // We aren't checking if the piece itself is friendly or not all we care about is if it's blocking the square. 
    for (const Piece* piece: board->_get_all_pieces())
    {
        if (piece->_get_position() == *target_position){ return true; }
    }
    return false;
}

std::list<Position> Piece::get_legal_vertical_movement(Board* board)
{
    std::list<Position> legal_vertical_movements;

    short y = _get_position()._vertical;
    short x = _get_position()._horizontial;

    // Iterate up and down from the current postition until we hit a piece or we hit the end of the board. Add theses movements to the list.
    // UP
    do {
        y++;
        const Position current_position(x, y);
        if (_is_square_blocked(&current_position, board))
        {
            legal_vertical_movements.push_back(current_position);
            break;
        }
        else
        {
            legal_vertical_movements.push_back(current_position);
        }
    } while(_is_in_bounds(x, y));

    // Put y back to where it started. 
    y = _get_position()._vertical;

    // DOWN
    do {
        y--;
        const Position current_position(x, y);
        if (_is_square_blocked(&current_position, board))
        {
            legal_vertical_movements.push_back(current_position);
            break;
        }
        else
        {
            legal_vertical_movements.push_back(current_position);
        }
    } while(_is_in_bounds(x, y));
    
    return legal_vertical_movements;
}

std::list<Position> Piece::get_legal_horizontial_movement(Board* board)
{
    std::list<Position> legal_horizontial_movements;

    short y = _get_position()._vertical;
    short x = _get_position()._horizontial;

    // Iterate up and down from the current postition until we hit a piece or we hit the end of the board. Add theses movements to the list.
    // RIGHT
    do {
        x++;
        const Position current_position(x, y);
        if (_is_square_blocked(&current_position, board))
        {
            legal_horizontial_movements.push_back(current_position);
            break;
        }
        else
        {
            legal_horizontial_movements.push_back(current_position);
        }
    } while(_is_in_bounds(x, y));

    // Put y back to where it started. 
    y = _get_position()._vertical;

    // LEFT
    do {
        x--;
        const Position current_position(x, y);
        if (_is_square_blocked(&current_position, board))
        {
            legal_horizontial_movements.push_back(current_position);
            break;
        }
        else
        {
            legal_horizontial_movements.push_back(current_position);
        }
    } while(_is_in_bounds(x, y));

    return legal_horizontial_movements;
}

std::list<Position> Piece::get_legal_diagonal_movement(Board* board)
{
    std::list<Position> legal_diagonol_movements;

    short y = _get_position()._vertical;
    short x = _get_position()._horizontial;

    // UP & RIGHT
    do {
        x++;
        y++;
        const Position current_position(x, y);
        if (_is_square_blocked(&current_position, board))
        {
            legal_diagonol_movements.push_back(current_position);
            break;
        }
        else
        {
            legal_diagonol_movements.push_back(current_position);
        }
    } while(_is_in_bounds(x, y));

    y = _get_position()._vertical;
    x = _get_position()._horizontial;

    // UP & LEFT
    do {
        x--;
        y++;
        const Position current_position(x, y);
        if (_is_square_blocked(&current_position, board))
        {
            legal_diagonol_movements.push_back(current_position);
            break;
        }
        else
        {
            legal_diagonol_movements.push_back(current_position);
        }
    } while(_is_in_bounds(x, y));

    y = _get_position()._vertical;
    x = _get_position()._horizontial;

    // DOWN & RIGHT
    do {
        x++;
        y--;
        const Position current_position(x, y);
        if (_is_square_blocked(&current_position, board))
        {
            legal_diagonol_movements.push_back(current_position);
            break;
        }
        else
        {
            legal_diagonol_movements.push_back(current_position);
        }
    } while(_is_in_bounds(x, y));

    y = _get_position()._vertical; // These are used to relist the position back to where we were. So we can search another direction. 
    x = _get_position()._horizontial;

    // DOWN & RIGHT
    do {
        x--;
        y--;
        const Position current_position(x, y);
        if (_is_square_blocked(&current_position, board))
        {
            legal_diagonol_movements.push_back(current_position);
            break;
        }
        else
        {
            legal_diagonol_movements.push_back(current_position);
        }
    } while(_is_in_bounds(x, y));

    // We should have all the legal moves now, including moves that could take a friendly piece so we'll need to correct that later. 

    return legal_diagonol_movements;
}


bool Piece::is_movement_valid(Position new_position, Board* board) const
{
    // Let's check to make sure that the position that's being requested is even inside the board. As if no more processing would be dumb. 
    // Is the location that the piece moving occupied? Since movements are just movements that don't include attack we won't include these.
    if (_is_in_bounds(&new_position) && !(board->get_piece_at(new_position) != nullptr)) return true;

    return false;
}

bool Piece::is_attack_valid(Position target_square, Board* board) const
{
    if (board->get_piece_at(target_square) == nullptr) return false; 

    // We now know that the target square has a piece there. But we need to find out if we can even take it. For this we'll check...
    // Is the piece in the bounds of a board?
    // Is the piece the same color as we are?
    // If both are true then we can take the piece. 
    if (_is_in_bounds((board->get_piece_at(target_square)->_get_position()._horizontial), (board->get_piece_at(target_square)->_get_position()._vertical)) && !(board->get_piece_at(target_square)->_is_black() == _is_black())) return true;

    return false;
}
