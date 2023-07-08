#include <iostream>

#include "Board.h"
#include "../position/Position.h"
#include "../piece/bishop/Bishop.h"
#include "../piece/king/King.h"
#include "../piece/knight/Knight.h"
#include "../piece/pawn/Pawn.h"
#include "../piece/queen/Queen.h"
#include "../piece/rook/Rook.h"

Board::Board(){
    _reset();
}

Board::~Board(){
    delete[] _board;
}

inline Piece* Board::_get() const {
    return _board;
}

void Board::_reset(){
    // Reference Documentation for BOARD PIECE INDEX GUIDE for information on interpretation.
    short index = 0;
    
    // Black Back Rank Added
    _board[index] = Rook(Position(0, 7)); index++;
    _board[index] = Knight(Position(1, 7)); index++;
    _board[index] = Bishop(Position(2, 7)); index++;
    _board[index] = Queen(Position(3, 7)); index++;
    _board[index] = King(Position(4, 7)); index++;
    _board[index] = Bishop(Position(5, 7)); index++;
    _board[index] = Knight(Position(6, 7)); index++;
    _board[index] = Rook(Position(7, 7)); index++;

    // Black Pawn Row Added
    _board[index] = Pawn(Position(0, 6)); index++;
    _board[index] = Pawn(Position(1, 6)); index++;
    _board[index] = Pawn(Position(2, 6)); index++;
    _board[index] = Pawn(Position(3, 6)); index++;
    _board[index] = Pawn(Position(4, 6)); index++;
    _board[index] = Pawn(Position(5, 6)); index++;
    _board[index] = Pawn(Position(6, 6)); index++;
    _board[index] = Pawn(Position(7, 6)); index++;

    // White Pawn Row Added
    _board[index] = Pawn(Position(0, 1)); index++;
    _board[index] = Pawn(Position(1, 1)); index++;
    _board[index] = Pawn(Position(2, 1)); index++;
    _board[index] = Pawn(Position(3, 1)); index++;
    _board[index] = Pawn(Position(4, 1)); index++;
    _board[index] = Pawn(Position(5, 1)); index++;
    _board[index] = Pawn(Position(6, 1)); index++;
    _board[index] = Pawn(Position(7, 1)); index++;

    // White Back Rank Added
    _board[index] = Rook(Position(0, 0)); index++;
    _board[index] = Knight(Position(1, 0)); index++;
    _board[index] = Bishop(Position(2, 0)); index++;
    _board[index] = Queen(Position(3, 0)); index++;
    _board[index] = King(Position(4, 0)); index++;
    _board[index] = Bishop(Position(5, 0)); index++;
    _board[index] = Knight(Position(6, 0)); index++;
    _board[index] = Rook(Position(7, 0));

    // Board has now been created with pieces in the correct starting positions. 
}

/// @brief Updates the board with the new location of a piece. 
/// @param Chess Piece w/ New Location 
void Board::_update(const Piece&){

}

/// @brief  Prints to the standard output a visual representation of the chess board.
void Board::_printBoard() const {
    // The function will print out a two-dimensional array of characters, declared here.
    char char_representation_board[8][8];

    // Initialize the char represention of the board so that by default the space is empty. 
    for (int i = 0; i < 8; i++){
        for (int e = 0; e < 8; e++){
            char_representation_board[i][e] = '#';
        }
        
    }
    
    // Change the single-dimensional array to two dimensional for output. 
    for(int i = 0; i < 32; i++){
        // Get the position of the piece in the array. 
        int x = _board[i]._getPosition()._horizontial;
        int y = _board[i]._getPosition()._vertical;
        char char_representation_piece; 

        // Get the char that will represent the piece. 
        switch(_board[i]._getID()){
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
                break;
        }
        char_representation_board[x][y] = char_representation_piece;
    }
}

/// @brief Prints to the standard output the state of all pieces in the game. 
void Board::_printData() const {
    for(int i = 0; i < 32; i++){
        std::cout <<  "ID: " << _board[i]._getID() << " isBlack: " << _board[i]._isBlack() << " Position: X-" << _board[i]._getPosition()._horizontial << " Y-" << _board[i]._getPosition()._horizontial << std::endl;
    }
}

