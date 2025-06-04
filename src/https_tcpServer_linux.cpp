#include <http_tcpServer_linux.h>

namespace http
{

    int TcpServer::startServer()
    {
        m_socket = socket(AF_INET, SOCK_STREAM, 0);
        if(m_socket < 0) {
            cerr << "Cannot create socket"; 
            return 1;
        }

        return 0;   
    }

    void TcpServer::closeServer()
    {
        close(m_socket);
        close(m_new_socket);
        return 0;
    }

    TcpServer::TcpServer()
    {
        startServer();
    }

    TcpServer::~TcpServer()
    {
        
    }
}
