/*
 *Low-level command interface to a running MyRobotLab instance
 *
 */

#ifndef MCOMMAND_H
#define MCOMMAND_H
#define ASIO_STANDALONE

#include <string>


#include <websocketpp/config/asio_no_tls_client.hpp>

#include <websocketpp/client.hpp>

#include <iostream>
//Shorthand to refer to a Websocket++ client
typedef websocketpp::client<websocketpp::config::asio_client> client;

using websocketpp::lib::placeholders::_1;
using websocketpp::lib::placeholders::_2;
using websocketpp::lib::bind;
using namespace std;


// pull out the type of messages sent by our config
typedef websocketpp::config::asio_client::message_type::ptr message_ptr;

class MCommand {
	public:
		client wsClient;

		MCommand();
		void sendCommand(string service, string method, void* data);
		void* callService(string service, string method, void* data);
		bool connect(string host, int port);
};



#endif
