#include "http_tcpServer_linux.h"
#include <iostream>
#include <sstream>
#include <unistd.h>

namespace http
{

    const int BUFFER_SIZE = 30720;

    int TcpServer::startServer()
    {
        m_socket = socket(AF_INET, SOCK_STREAM, 0);
        if(m_socket < 0) {
            std::cerr << "Cannot create socket"; 
            return 1;
        }   

        if(bind(m_socket, (sockaddr *)&m_socketAddress, m_socketAddress_len) < 0) {
            std::cerr << "Cannot connect socket to address";
            return 1;
        }

        return 0;
    }

    int TcpServer::closeServer()
    {
        close(m_socket);
        close(m_new_socket);
        return 0;
    }

    void TcpServer::startListen()
    {
        if(listen(m_socket, 20) < 0) {
            std::cerr << "Socket listening failed";
            return;
        }

        std::ostringstream ss;
        ss << "\n*** Listening on ADDRESS: " 
        << inet_ntoa(m_socketAddress.sin_addr) 
        << " PORT: " << ntohs(m_socketAddress.sin_port) 
        << " ***\n\n";

        std::cout << ss.str() << std::endl;

        int bytesReceived;

        while(true)
        {
            std::cout << "====== Waiting for a new connection ======\n\n\n" << std::endl;
            acceptConnection(m_new_socket);

            char buffer[BUFFER_SIZE] = {0};

            bytesReceived = read(m_new_socket, buffer, BUFFER_SIZE);
            if(bytesReceived < 0)
            {
                std::cerr << "Failed to read bytes from client socket connection" << std::endl;
                return;
            }

            std::ostringstream ss;
            ss << "------ Received Request from client ------\n\n";
            std::cout << ss.str() << std::endl;

            sendResponse();

            close(m_new_socket);


        }
    }


    void TcpServer::acceptConnection(int &new_socket)
    {
        new_socket = accept(m_socket, (sockaddr *)&m_socketAddress, &m_socketAddress_len);
        if (new_socket < 0)
        {
            std::ostringstream ss;
            ss << "Server failed to accept incoming connection from ADDRESS: " << inet_ntoa(m_socketAddress.sin_addr) << "; PORT: " << ntohs(m_socketAddress.sin_port);
            std::cout << ss.str() << std::endl;
        }
    }

    std::string TcpServer::buildResponse()
    {
        std::string htmlFile = "<!DOCTYPE html><html lang=\"en\"><body><h1> HOME </h1><p> Hello from your Server :) </p></body></html>";
        std::ostringstream ss;
        ss << "HTTP/1.1 200 OK\nContent-Type: text/html\nContent-Length: " << htmlFile.size() << "\n\n"
           << htmlFile;

        return ss.str();
    }

    void TcpServer::sendResponse() 
    {
        long bytesSent;

        bytesSent = write(m_new_socket, m_serverMessage.c_str(), m_serverMessage.size());

        if(bytesSent == m_serverMessage.size())
        {
            std::cout << "------ Server Response sent to client ------\n\n" << std::endl;
        }
        else
        {
            std::cerr << "Error sending response to client" << std::endl;
        }
    }

    TcpServer::TcpServer(std::string ip_address, int port) : m_ip_address(ip_address), m_port(port), m_socketAddress_len(sizeof(m_socketAddress)), m_serverMessage(buildResponse())
    {
        m_socketAddress.sin_family = AF_INET;
        m_socketAddress.sin_port = htons(m_port);
        m_socketAddress.sin_addr.s_addr = inet_addr(m_ip_address.c_str());
        startServer();
    }

    TcpServer::~TcpServer()
    {
        closeServer();
    }
}
