/**
 * @file Board.cpp
 * @author Mitchell M. Gresham
 * @brief Representation of a Chess Board.
 * @version 0.1
 * @date 2023-07-07
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include <iostream>

#include "Board.h"
#include "../piece/Piece.h"
#include "../position/Position.h"
#include "../piece/bishop/Bishop.h"
#include "../piece/king/King.h"
#include "../piece/knight/Knight.h"
#include "../piece/pawn/Pawn.h"
#include "../piece/queen/Queen.h"
#include "../piece/rook/Rook.h"

Board::Board(): Board("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR") {} 


Board::~Board()
{
    for (Piece* piece: _board)
    {
        delete piece;
    } // Deallocate the memory that's reserved for those pieces. 
}

std::string Board::_as_fen()
{
    // Make a function that changes from the data types of the program back into FEN notation as a string. It'll do the opposite of the constructor.
    std::string fen_notation_output = "";
    int empty_space_counter = 0;

    for (int y = 7; y >= 0; y--)
    {
        for (int x = 0; x < 8; x++)
        {
            Piece* piece = get_piece_at(Position(x, y));
            if (piece == nullptr) empty_space_counter++;
            else
            {
                if (empty_space_counter != 0) fen_notation_output += std::to_string(empty_space_counter);
                empty_space_counter = 0;
                switch(piece->_get_ID())
                {
                    case Piece::PIECE::BISHOP:
                        if (piece->_is_black()) fen_notation_output += 'b';
                        else fen_notation_output += 'B';
                        break;
                    case Piece::PIECE::KING:
                        if (piece->_is_black()) fen_notation_output += 'k';
                        else fen_notation_output += 'K';
                        break;
                    case Piece::PIECE::KNIGHT:
                        if (piece->_is_black()) fen_notation_output += 'n';
                        else fen_notation_output += 'N';
                        break;
                    case Piece::PIECE::PAWN:
                        if (piece->_is_black()) fen_notation_output += 'p';
                        else fen_notation_output += 'P';
                        break;
                    case Piece::PIECE::QUEEN:
                        if (piece->_is_black()) fen_notation_output += 'q';
                        else fen_notation_output += 'Q';
                        break;
                    case Piece::PIECE::ROOK:
                        if (piece->_is_black()) fen_notation_output += 'r';
                        else fen_notation_output += 'R';
                }
            }
        }
        if (empty_space_counter != 0) fen_notation_output += std::to_string(empty_space_counter);
        empty_space_counter = 0;
        if (y != 0) fen_notation_output += '/';
    }

    if (_is_black_turn())
    {
        fen_notation_output += " w";
    }
    else
    {
        fen_notation_output += " b";
    }

    return fen_notation_output;
}

Board::Board(const std::string& fen_notation_input) // FEN Notation is the input that's the string.
{
    Position current_iteration_position(0, 7);
    bool break_loop = false;

    for(char letter: fen_notation_input)
    {
        // Note: The notation starts from top to bottom.
        switch(letter)
        {
            case ' ': // We have reached the end of the FEN that we care about.
                break_loop = true;
                if (fen_notation_input.find('w') != std::string::npos) // If the string contains w then it's white's turn.
                {
                    is_black_turn = false;
                }
                else
                {
                    is_black_turn = true;
                }
                break;
            case '/': // We have reached the end of the row, move up. 
                current_iteration_position._horizontial = 0;
                current_iteration_position._vertical--;
                break;
            case 'r': // Black Rook
                _board.push_back(new Rook(current_iteration_position, true));
                current_iteration_position._horizontial++;
                break;
            case 'n': // Black Knight
                _board.push_back(new Knight(current_iteration_position, true));
                current_iteration_position._horizontial++;
                break;
            case 'b': // Black Bishop
                _board.push_back(new Bishop(current_iteration_position, true));
                current_iteration_position._horizontial++;
                break;
            case 'q': // Black Queen
                _board.push_back(new Queen(current_iteration_position, true));
                current_iteration_position._horizontial++;
                break;
            case 'k': // Black King
                _board.push_back(new King(current_iteration_position, true));
                current_iteration_position._horizontial++;
                break;
            case 'p': // Black Pawn
                _board.push_back(new Pawn(current_iteration_position, true));
                current_iteration_position._horizontial++;
                break;
            // The capitalized ones are white...
            case 'R': // White Rook
                _board.push_back(new Rook(current_iteration_position, false));
                current_iteration_position._horizontial++;
                break;
            case 'N': // White Knight
                _board.push_back(new Knight(current_iteration_position, false));
                current_iteration_position._horizontial++;
                break;
            case 'B': // White Bishop
                _board.push_back(new Bishop(current_iteration_position, false));
                current_iteration_position._horizontial++;
                break;
            case 'Q': // White Queen
                _board.push_back(new Queen(current_iteration_position, false));
                current_iteration_position._horizontial++;
                break;
            case 'K': // White King
                _board.push_back(new King(current_iteration_position, false));
                current_iteration_position._horizontial++;
                break;
            case 'P': // White Pawn
                _board.push_back(new Pawn(current_iteration_position, false));
                current_iteration_position._horizontial++;
                break;
            default: // This should only run when we've encountered a digit. Dangerous assumption but one I'll make. 
                int as_number = letter - 48; // Will change it to an integer if ASCII. 
                current_iteration_position._horizontial += as_number;
        }
        if (break_loop)
        {
            break;
        }
    }
}

std::list<Piece*> Board::_get_all_pieces(){ return _board; }

std::list<Piece*> Board::_get_all_opposing_pieces(bool is_current_black)
{
    std::list<Piece*> opposing_piece_list;

    for(Piece* piece: _board)
    {
        if (!(piece->_is_black() == is_current_black)) opposing_piece_list.push_back(piece);
    }

    return opposing_piece_list;
}

Piece* Board::get_piece_at(Position search_target_location)
{
    // Simple iteration through all the pieces on the board until we find one that has the right value. 
    for (Piece* piece: _board)
    {
        if (search_target_location == piece->_get_position()) return piece;
    }

    return nullptr;
}


void Board::_update(Position& piece_current_position, Position& new_position)
{
    Piece* current_piece = get_piece_at(piece_current_position);
    Piece* target_piece = get_piece_at(new_position);

    if (target_piece != nullptr)
    {
        // So if there is a piece there. Then it's null now because we took it. 
        Position null_position(-1, -1);
        target_piece->_set_position(null_position);
    }

    current_piece->_set_position(new_position);
}

void Board::_print_board() const {
    // The function will print out a two-dimensional array of characters, declared here.
    char char_representation_board[8][8];

    // Initialize the char represention of the board so that by default the space is empty. 
    for (int i = 0; i < 8; i++){
        for (int e = 0; e < 8; e++){
            char_representation_board[i][e] = '#';
        }
    }
    
    // Change the single-dimensional array to two dimensional for output. 
    for (Piece* piece: _board)
    {
        int x = piece->_get_position()._horizontial;
        int y = piece->_get_position()._vertical;
        char char_representation_piece; 

        switch(piece->_get_ID()){
            case Piece::PIECE::BISHOP:
                char_representation_piece = 'B';
                break;
            case Piece::PIECE::KING:
                char_representation_piece = 'K';
                break;
            case Piece::PIECE::KNIGHT:
                char_representation_piece = 'N';
                break;
            case Piece::PIECE::PAWN:
                char_representation_piece = 'P';
                break;
            case Piece::PIECE::QUEEN:
                char_representation_piece = 'Q';
                break;
            case Piece::PIECE::ROOK:
                char_representation_piece = 'R';
        }

        // If the piece isn't taken then display it. 
        if (x >= 0 && y >= 0){
            char_representation_board[x][y] = char_representation_piece;
        }   

    }
    
    // Make a nested for-loop to iterate through the char_representation_board and print all the pieces.
    std::cout << "----------------- BOARD -----------------" << std::endl;
    for (int x = 0; x < 8; x++){
        for (int y = 0; y < 8; y++){
            std::cout << "| ";
            std::cout << char_representation_board[x][y];
            std::cout << " |";
        }
        std::cout << std::endl;
    }
    std::cout << "--------------- END BOARD ---------------" << std::endl;
}

void Board::_print_data() const
{
    std::cout << "=== START BOARD INFORMATION ===" << std::endl;
    std::cout << "Board Size: " << _board.size() << std::endl;
    for (Piece* piece: _board)
    {
        std::cout << "Piece: " << piece->_get_ID() << " Position: (" << piece->_get_position()._horizontial << ", " << piece->_get_position()._vertical << ")" << std::endl;
    }
    std::cout << "=== END BOARD INFORMATION ===" << std::endl;
}

Board Board::_get_copy()
{
    return Board(_as_fen()); // This will create a new board object with the current FEN as the main board. 
    // This method will be used to check for things that we can only determine after a move has taken place such as if taking a piece would put the king in check.    
}

bool Board::_is_black_turn() const { return is_black_turn; }

// bool Board::_is_stalemate(bool _is_black) // Is it stalemate for boolean (black or white).
// {
//     // TODO: Implement this function.
// }

// bool _is_checkmate(bool _is_black)
// {
//     //TODO: Implement this function.
// }

// bool _is_king_in_check(bool _is_black)
// {
//     //TODO: Implement this function.
// }