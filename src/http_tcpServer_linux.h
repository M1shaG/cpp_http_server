#ifndef INCLUDED_HTTP_TSCPSERVER_LINUX
#define INCLUDED_HTTP_TSCPSERVER_LINUX
#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>

namespace http
{
    class TcpServer
    {
        public:
            TcpServer(std::string, int port);
            ~TcpServer();
            void startListen();
        private:
            std::string m_ip_address;
            int m_port;
            int m_socket;
            int m_new_socket;
            struct sockaddr_in m_socketAddress;
            unsigned int m_socketAddress_len; 
            std::string m_serverMessage;

            int startServer();
            int closeServer();
            void acceptConnection(int &new_socket);
            std::string buildResponse();
            void sendResponse();
    };
}

#endif