#include <http_tcpServer_linux.h>
#include <iostream>

namespace http
{

    int TcpServer::startServer()
    {
        m_socket = socket(AF_INET, SOCK_STREAM, 0);
        if(m_socket < 0) {
            std::cerr << "Cannot create socket"; 
            return 1;
        }

        return 0;   

        if(bind(m_socket, (sockaddr *)&m_socketAddress, m_socketAddress_len) < 0) {
            std::cerr << "Cannot connect socket to address";
            return 1;
        }
    }

    int TcpServer::closeServer()
    {
        close(m_socket);
        close(m_new_socket);
        return;
    }

    TcpServer::TcpServer(std::string ip_address, int port) : m_ip_address(ip_address), m_port(port), m_socketAddress_len(sizeof(m_socketAddress))
    {
        m_socketAddress.sin_family = AF_INET;
        m_socketAddress.sin_port = htons(m_port);
        startServer();
    }

    TcpServer::~TcpServer()
    {
        
    }
}
