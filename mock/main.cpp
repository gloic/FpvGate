#include "crow_all.h"
#include "GateIP.h"

int main() {
    crow::SimpleApp app;
    std::vector<std::shared_ptr<GateIP>> gateIps;

    CROW_ROUTE(app, "/")([](){
        auto page = crow::mustache::load_text("index.html");
        return page;
    });

    CROW_ROUTE(app, "/api/gate/register")([&](const crow::request &req){
        std::string client_ip = req.get_header_value("X-Forwarded-For");
        if (client_ip.empty()) {
            client_ip = req.remote_ip_address;
        }

        int index = -1;
        bool found = false;
        for (size_t i = 0; i < gateIps.size(); ++i) {
            if (gateIps[i]->ip == client_ip) {
                index = static_cast<int>(i);
                found = true;
                break;
            }
        }

        if (!found) {
            gateIps.push_back(std::make_shared<GateIP>(client_ip));
            index = static_cast<int>(gateIps.size() - 1);
        }

        return std::to_string(index);
    });

    CROW_ROUTE(app, "/api/gate/passed")([](){
        return "ok";
    });

    CROW_ROUTE(app, "/listen-all") ([](const crow::request&){
        for (auto const& ip : gateIps) {
            std::string url = "http://" + ip->ip + "/api/gate/start";
            // call the URL (GET)
        }
        return crow::response{};
    });

    CROW_ROUTE(app, "/stop-listen-all") ([](const crow::request&){
        for (auto const& ip : gateIps) {
            std::string url = "http://" + ip->ip + "/api/gate/stop";
            // call the URL (GET)
        }
        return crow::response{};
    });

    CROW_ROUTE(app, "/user-listen") ([](const crow::request&){
        return crow::response{""};
    });

    app.port(8008).run();
}
