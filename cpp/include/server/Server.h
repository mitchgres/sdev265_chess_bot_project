#include <string>

#include "../engine/piece/Piece.h"
#include "../engine/position/Position.h"

class Server {
    public:
        static int start(const int PORT, const int MESSAGE_BUFFER_SIZE);     
};