//
// Created by xyk on 19-7-3.
//

#ifndef TESTTCP_SERVER_H
#define TESTTCP_SERVER_H

#include <boost/asio.hpp>
#include <boost/scoped_ptr.hpp>
#include <boost/shared_array.hpp>
#include <boost/thread.hpp>
#include <boost/thread/mutex.hpp>
#include <iostream>
#include <queue>

using boost::asio::ip::tcp;
using namespace std;

typedef struct {
    boost::shared_array<char> buffer;
    int length;
} TransportData;

class Server_Client {
    typedef tcp::socket socket_type;
    typedef std::shared_ptr <socket_type> sock_ptr;
    typedef std::shared_ptr <tcp::acceptor> acceptor_ptr;

public:
    static queue<TransportData>m_receiveQueue;
    static boost::mutex m_receiveQueueMutex;

    void listento(int minPort,int maxPort);
    void connect(const char *address,int port);
    int getListeningPort();

    void sendData(char* buf,int len);
    
    Server_Client(size_t initialBufferSize = 1600, bool tag = true);

private:
    void receiveData();
    void accept_handler(const boost::system::error_code &ec, sock_ptr sock);
    void readHandler(const boost::system::error_code& ec,std::size_t bytes);
    void connect_handler(const boost::system::error_code &ec, sock_ptr sock);
    void readPacketHandler(const boost::system::error_code& ec, std::size_t bytes);

    
    void doSend();
    void write_handler(const boost::system::error_code &);

private:

    boost::asio::io_service m_io;
    acceptor_ptr m_acceptor;
    sock_ptr sock;
    bool m_tag;
    bool m_isClosing;
    char m_readHeader[4];
    size_t m_bufferSize;
    TransportData m_receiveData;
    uint32_t m_receivedBytes;

    std::queue<TransportData> m_sendQueue;
    boost::mutex m_sendQueueMutex;
};


#endif //TESTTCP_SERVER_H




























