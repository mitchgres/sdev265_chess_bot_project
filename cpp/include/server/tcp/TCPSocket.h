#ifndef __TCPSOCKET_H__
#define __TCPSOCKET_H__

#include <string>
#include <iostream>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/enable_shared_from_this.hpp>

#include "../message/Message.h"
#include "../request/Request.h"

class TCPSocket 
{
    public:
        TCPSocket(short, const std::string&);
        int _send(const Message&);
        Request _get() const;
    private:
        short SOCKET_PORT;
        std::string IP_ADDRESS;

        boost::asio::ip::tcp::socket _socket;
};
#endif // __TCPSOCKET_H__