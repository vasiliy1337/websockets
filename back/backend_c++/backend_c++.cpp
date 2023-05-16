#include <websocketpp/config/asio_no_tls.hpp>
#include <websocketpp/server.hpp>
#include <iostream>
#include <set>
#include <map>

using websocketpp::server;
using websocketpp::config::asio;
using websocketpp::connection_hdl;
using std::set;
using std::map;

class ChatServer {
public:
    typedef server<asio> server_t;
    typedef std::map<connection_hdl, std::string, std::owner_less<connection_hdl>> connections;

    ChatServer() {
        m_server.init_asio();
        m_server.set_open_handler(websocketpp::lib::bind(&ChatServer::on_open, this, websocketpp::lib::placeholders::_1));
        m_server.set_close_handler(websocketpp::lib::bind(&ChatServer::on_close, this, websocketpp::lib::placeholders::_1));
        m_server.set_message_handler(websocketpp::lib::bind(&ChatServer::on_message, this, websocketpp::lib::placeholders::_1, websocketpp::lib::placeholders::_2));
    }

    void run(uint16_t port) {
        m_server.listen(port);
        m_server.start_accept();
        m_server.run();
    }

private:
    void on_open(connection_hdl hdl) {
        m_connections.insert(std::make_pair(hdl, ""));
        std::cout << "Client connected" << std::endl;
    }

    void on_close(connection_hdl hdl) {
        m_connections.erase(hdl);
        std::cout << "Client disconnected" << std::endl;
    }

    void on_message(connection_hdl hdl, server_t::message_ptr msg) {
        for (auto& it : m_connections) {
            m_server.send(it.first, msg->get_payload(), msg->get_opcode());
        }
    }

    server_t m_server;
    connections m_connections;
};

int main(int argc, char* argv[]) {
    ChatServer server;
    server.run(9002);
    return 0;
}