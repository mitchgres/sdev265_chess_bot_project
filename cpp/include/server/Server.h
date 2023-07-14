#include <unordered_map>
#include <string>

#include "../engine/piece/Piece.h"
#include "../engine/position/Position.h"

class Server {
    public:
        std::unordered_map<Piece, Position> _get_client_move(); 
        int _send_client_move(const std::unordered_map<Piece, Position>&);
    private:
        const std::string IP_ADDRESS;
        const int PORT_NUMBER; // Standard is 80, but since OS can be tricky with who get's access should be else. 
        

};