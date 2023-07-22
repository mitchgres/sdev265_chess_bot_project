#include <netinet/in.h>  
#include <stdio.h>  
#include <stdlib.h>  
#include <string.h>  
#include <sys/socket.h>  
#include <unistd.h>  
#include <boost/algorithm/string.hpp> // For boost::trim

#include "../engine/Engine.h"
#include "../engine/board/Board.h"
#include "Server.h"

int Server::start(const int PORT, const int MESSAGE_BUFFER_SIZE)
{
    int file_descriptor_socket, connected_socket, value_read_from_socket;
    struct sockaddr_in address;
    int opt = 1;
    int address_length = sizeof(address);
    char buffer[MESSAGE_BUFFER_SIZE] = {0}; // This is the buffer that will be used to store the message that's sent from the client. It should never get bigger than 50
    // since we're only working with FEN notation.

    // Created File Descriptor Socket...
    if ((file_descriptor_socket = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        perror("[ERROR]: Socket Creation Failure");
        exit(EXIT_FAILURE);
    }

    // Bind Socket on 8080... There shouldn't be much traffic on this port which is why it's used over a more common port like 80.
    if (setsockopt(file_descriptor_socket, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)))
    {
        perror("[ERROR]: Socket Binding Failure");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    // Listen to see if the client tries to connect with us...
    if (listen(file_descriptor_socket, 1) < 0) // There should never be more than one client in this version of application.
    {
        perror("[ERROR]: Socket Listening Failure");
        exit(EXIT_FAILURE);
    }

    // Accept Connection
    if ((connected_socket = accept(file_descriptor_socket, (struct sockaddr*)&address, (socklen_t*)&address_length)) < 0)
    {
        perror("[ERROR]: Socket Accepting Failure");
        exit(EXIT_FAILURE);
    }

    // Read the message from the client.
    value_read_from_socket = read(connected_socket, buffer, MESSAGE_BUFFER_SIZE);
    // We'll need to change this into a std::string and then use boost::trim to trim it so it can be read by the engine.
    std::string message_from_client = buffer;
    boost::trim(message_from_client);

    // Now let's get the move made by the engine in responce to the message from the client.
    Board board = Board(message_from_client);

    // Display the fen from client.
    std::cout << "[INFO]: Client Board: " << message_from_client << std::endl;
    board._print_board();

    Engine* engine = new Engine();
    Board* board_with_move = engine->get_random_move(&board);
    std::string message_to_client = board_with_move->_as_fen();

    // Display the fen to client.
    std::cout << "[INFO]: Server Board: " << message_to_client << std::endl;
    board_with_move->_print_board();
    
    // Send the message to the client.
    send(connected_socket, message_to_client.c_str(), strlen(message_to_client.c_str()), 0);
    std::cout << "[INFO]: Client Responce Has Been Sent." << std::endl;

    // Close & Shutdown.
    close(connected_socket);
    shutdown(file_descriptor_socket, SHUT_RDWR);
    return 0;
}
