#include <iostream>
#include "include/stations.hh"

//API-Key für VRN Start.Info: dcqh99ct00frb38u9hevg9e3tt

int main(int argc, char **argv)
{
    ipk::geo::Coordinate coordinates(49.418572, 8.675596);
    auto stations = ipk::vrn::request_all_stations();
 
    auto f = ipk::vrn::filter_nearby_stations(stations, coordinates, 300);
    std::cout << f[1].first.to_string() << std::endl << f[1].second;

    return 0;
}
