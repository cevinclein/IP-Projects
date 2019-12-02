#include <iostream>
#include "include/stations.hh"

//API-Key für VRN Start.Info: dcqh99ct00frb38u9hevg9e3tt

int main(int argc, char **argv)
{
    ipk::http::Request req;
    req.headers({{"RNV_API_TOKEN: dcqh99ct00frb38u9hevg9e3tt"},
                {"content-type: test/json"}});
    req.perform(
        "rnv.the-agent-factory.de/easygo2/api/regions/rnv/modules/stations/packages/1", 8080
        );
    std::string output = req.result();
    nlohmann::json json = nlohmann::json::parse(output);
    
    return 0;
}
