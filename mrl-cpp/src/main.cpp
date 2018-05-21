#define ASIO_STANDALONE

#include <iostream>
#include <string>
#include <websocketpp/config/asio_no_tls.hpp>
#include <websocketpp/server.hpp>
#include "MCommand.hpp"

typedef websocketpp::server<websocketpp::config::asio> server;

void on_message(websocketpp::connection_hdl hdl, server::message_ptr msg) {
        std::cout << msg->get_payload() << std::endl;
}

int main() {
    MCommand* m = new MCommand();
    m->connect("localhost", 8888);
    server print_server;

    print_server.set_message_handler(&on_message);

    print_server.init_asio();
    print_server.listen(9002);
    print_server.start_accept();

    print_server.run();
}
