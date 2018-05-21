/*
 *Low-level command interface to a running MyRobotLab instance
 *
 */


#include <MCommand.hpp>


using namespace std;


// Handlers
void on_open(client* c, websocketpp::connection_hdl hdl) {
    std::string msg = "{\"name\":null, \"method\":\"register\",\"data\":[]}";
    //c->send(hdl,msg,websocketpp::frame::opcode::text);

    //c->get_alog().write(websocketpp::log::alevel::app, "Sent Message: "+msg);
}

void on_fail(client* c, websocketpp::connection_hdl hdl) {
    c->get_alog().write(websocketpp::log::alevel::app, "Connection Failed");
}

void on_message(client* c, websocketpp::connection_hdl hdl, message_ptr msg) {
    c->get_alog().write(websocketpp::log::alevel::app, "Received Reply: "+msg->get_payload());
    //c->close(hdl,websocketpp::close::status::normal,"");
}

void on_close(client* c, websocketpp::connection_hdl hdl) {
    c->get_alog().write(websocketpp::log::alevel::app, "Connection Closed");
}


MCommand::MCommand(){}
void MCommand::sendCommand(string service, string method, void* data){}
void* MCommand::callService(string service, string method, void* data){}
bool MCommand::connect(string host, int port) {
	cout << "Connecting to host " << host << " on port " << port << "..." << endl;
    
    string uri = "ws://" + host + ":" + to_string(port) + "/api/messages";
    
    try {
        // set logging policy if needed
        wsClient.clear_access_channels(websocketpp::log::alevel::frame_header);
        wsClient.clear_access_channels(websocketpp::log::alevel::frame_payload);
        //c.set_error_channels(websocketpp::log::elevel::none);
        
        // Initialize ASIO
        wsClient.init_asio();
        
        // Register our handlers
        wsClient.set_open_handler(bind(&on_open,&wsClient,::_1));
        wsClient.set_fail_handler(bind(&on_fail,&wsClient,::_1));
        wsClient.set_message_handler(bind(&on_message,&wsClient,::_1,::_2));
        wsClient.set_close_handler(bind(&on_close,&wsClient,::_1));
        
        // Create a connection to the given URI and queue it for connection once
        // the event loop starts
        websocketpp::lib::error_code ec;
        client::connection_ptr con = wsClient.get_connection(uri, ec);
        wsClient.connect(con);
        
        // Start the ASIO io_service run loop
        wsClient.run();
    } catch (const std::exception & e) {
        std::cout << e.what() << std::endl;
    } catch (websocketpp::lib::error_code e) {
        std::cout << e.message() << std::endl;
    } catch (...) {
        std::cout << "other exception" << std::endl;
    }

}

