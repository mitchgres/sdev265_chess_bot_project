#include <boost/asio.hpp>
#include <boost/algorithm/string.hpp>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>

#include "../engine/board/Board.h"
#include "../engine/Engine.h"

namespace asio = boost::asio;
using tcp = asio::ip::tcp;

// Custom URL-decode function
std::string url_decode(const std::string& encoded) {
    std::string result;
    char ch;
    int i, hex;
    for (i = 0; i < encoded.length(); i++) {
        if (encoded[i] == '%') {
            if (sscanf(encoded.substr(i + 1, 2).c_str(), "%x", &hex) != 1) {
                return "";
            }
            ch = static_cast<char>(hex);
            result += ch;
            i += 2;
        } else if (encoded[i] == '+') {
            result += ' ';
        } else {
            result += encoded[i];
        }
    }
    return result;
}

// Function to parse the FEN notation received in the HTTP request
std::string parse_fen(const std::string& request_line) {
    std::vector<std::string> tokens;
    std::istringstream iss(request_line);
    std::string token;
    while (std::getline(iss, token, ' ')) {
        tokens.push_back(token);
    }

    if (tokens.size() >= 2) {
        // The FEN notation is expected to be in the second token
        std::string fen_notation = tokens[1];
        // Decode the URL-encoded FEN notation
        return url_decode(fen_notation);
    }

    // Return an empty string if the FEN notation is not found
    return "";
}

// Function to handle incoming HTTP requests
void handle_request(tcp::socket& socket) {
    try {
        asio::streambuf buffer;
        asio::read_until(socket, buffer, "\r\n");

        // Read the request line from the buffer
        std::istream request_stream(&buffer);
        std::string request_line;
        std::getline(request_stream, request_line);

        // Process only GET requests for this simple example
        if (request_line.find("GET") != std::string::npos) {
            // Get the FEN notation from the request
            std::string fen_notation = parse_fen(request_line);
            boost::trim(fen_notation);
            std::cout << "FEN notation: " << fen_notation << std::endl;
            fen_notation.erase(0, 6);
            std::cout << "FEN notation: " << fen_notation << std::endl;
            Board board(fen_notation);
            std::string fen_responce = Engine::get_random_move(&board)->_as_fen();

            // Send HTTP response headers
            std::string response = "HTTP/1.1 200 OK\r\n";
            response += "Content-Type: application/json\r\n";
            response += "Connection: close\r\n\r\n";

            // Prepare JSON response with the FEN notation
            std::string json_response = "{\"fen\": \"" + fen_responce  + "\"}";

            // Send the response
            response += json_response;
            asio::write(socket, asio::buffer(response));

            // Output the received FEN notation to console
            std::cout << "Received FEN notation: " << fen_notation << std::endl;
        }

        // Close the socket after responding to the request
        socket.close();
    } catch (std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}

int main() {
    try {
        asio::io_context io_context;
        tcp::acceptor acceptor(io_context, tcp::endpoint(tcp::v4(), 8080));

        std::cout << "Server started. Listening on port 8080..." << std::endl;

        while (true) {
            tcp::socket socket(io_context);
            acceptor.accept(socket);
            handle_request(socket);
        }
    } catch (std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}
