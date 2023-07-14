#include "TCPSocket.h"

#include <string>
#include <iostream>
#include <boost/asio.hpp>

#include "../message/Message.h"
#include "../request/Request.h"


TCPSocket::TCPSocket(short port, const std::string& ip_address)
{
    SOCKET_PORT = port;
    IP_ADDRESS = ip_address;
}


int TCPSocket::_send(const Message& return_message)
{
    // Error Code used for checking if error occured in the send method. 
    boost::system::error_code error_code;

    boost::asio::write
    (
        _socket,
        boost::asio::buffer(return_message._get_as_string()),
        error_code
    );

    // See if the server actually sent the message.
    if (!error_code)
    {
        std::cout << "[INFO]: Server Sent Message." << std::endl;
    }
    else
    {
        // Some error has occured. 
        std::cout << "[ERROR]: Server Failed Sending Message" << std::endl;
    }
}


Request TCPSocket::_get() const
{
    // Do a REGEX for the format that the data will be sent in as defined by the client.
    // If POST...
    // - Search for the word POST. 
    // - Search for "Is Engine Black: "
    // If GET...
    // - Search for the word GET. 
    // - Search for "Position: "
    // - Search for "Piece: "
    // Parse these and get the result, then return. 
}

