#include <string>

#include "../../piece/Piece.h"
#include "../../position/Position.h"

/// @brief Interpretation of the HTML Request sent by the chess client into our data classes. 
class Request {
    public:
        // The client can create a game with POST or get a move by the computer with GET method. 
        enum REQUEST_TYPE
        {
            GAME_CREATION, // POST 
            MOVE_REQUEST, // GET
        };

        Request(const std::string&);
        ~Request();
        // Used if GET method is called. 
        Position* _get_movement() const;
        Piece* _get_piece() const;
        int* _get_game_id() const; 

        // Used if POST method is called.
        bool* _is_engine_black();

    private:
        const Position* _move;
        const Piece::PIECE* _piece;
        const int* _game_id; // Used to access the game in the database.
        const bool*  _is_engine_black;
};