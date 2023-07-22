#include<cstdlib>
#include <ctime>

#include "Engine.h"

struct Movement
{
    Position _from;
    Position _to;
};

// The RANDOM ENGINE will first determine all the possible movements that could be made. It'll then choose a random movement from that list. That movement will be put updated
// on a board and the FEN will be outputted as a updated board

// RANDOM
Board* Engine::get_random_move(Board* board)
{

    bool is_black_turn = board->_is_black_turn();
    std::cout << "[INFO]: Is Black Turn: " << is_black_turn << std::endl;
    std::list<Piece*> get_all_friendly_pieces = board->_get_all_opposing_pieces(!is_black_turn); // This will instead of getting the opposing get all friendly. 

    // We'll ignore the piece if it's null value to reduce computation time. 
    get_all_friendly_pieces.remove_if([](Piece* piece) { return piece->_get_position() == Position(-1, -1); });

    // We'll now iterate through all the pieces and get all the possible moves that could be made.
    std::list<Movement> all_possible_moves;

    for (Piece* piece: get_all_friendly_pieces)
    {
        for (Position position: piece->_get_movements(board))
        {
            Movement move;
            move._from = piece->_get_position();
            move._to = position;
            all_possible_moves.push_back(move);
        }
    }

    // We'll do the same thing but for attacks instead of movements.
    for (Piece* piece: get_all_friendly_pieces)
    {
        for (Position position: piece->_get_attacks(board))
        {
            Movement move;
            move._from = piece->_get_position();
            move._to = position;
            all_possible_moves.push_back(move);
        }
    }

    // We'll now choose a random move from the list of all possible moves.
    srand((int)time(0)); // Truly random number. 
    int random_number = rand() % all_possible_moves.size();

    // Update the board with the random move.
    std::list<Movement>::iterator it = all_possible_moves.begin();
    std::advance(it, random_number);
    board->_update(it->_from, it->_to);

    board->_print_board();

    return board;
}

