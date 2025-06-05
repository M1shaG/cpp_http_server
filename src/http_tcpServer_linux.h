#ifndef INCLUDED_HTTP_TSCPSERVER_LINUX
#define INCLUDED_HTTP_TSCPSERVER_LINUX
#include <sys/socket.h>
#include <arpa/inet.h>

namespace http
{
    class TcpServer
    {
        public:
            TcpServer(std::string, int port);
            ~TcpServer();
        private:
            std::string m_ip_address;
            int m_port;
            int m_socket;
            struct sockaddr_in m_socketAddress;
            unsigned int m_socketAddress_len; 


            int startServer();
            int closeServer();
    };
}

#endif