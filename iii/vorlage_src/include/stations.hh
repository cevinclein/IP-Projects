#include "json.hh"
#include "request.hh"
#include <cmath>
#include <string> 
#include <sstream>
#include <vector>

namespace ipk
{
    namespace geo
    {
        class Coordinate 
        { 
            public:
                Coordinate(double latitude, double longitude) :lat(latitude), lon(longitude)
                {

                }

                Coordinate(std::string latitude, std::string longitude)
                {
                    lat = std::stod(latitude);
                    lon = std::stod(longitude);
                }

                double latitude() const
                {
                    return this->lat;
                }

                double longitude() const
                {
                    return this->lon;
                }

                double distance_to(const Coordinate &other) const
                {
                    std::pair<double, double> pair1 = std::make_pair(this->lat, this->lon);
                    std::pair<double, double> pair2 = std::make_pair(other.lat, other.lon);

                    double f = this->distance_between_coordinates(pair1, pair2);
                    return f;
                }

                private: 
                    double lat;
                    double lon;
                    
                    double deg_to_rad(double deg) const
                    {
                         return deg * M_PI / 180;
                    }

                    double distance_between_coordinates(
                    const std::pair<double, double> &first, 
                    const std::pair<double, double> &second) const
                    {
                        std::pair<double, double> pair1;
                        std::pair<double, double> pair2;
                        pair1.first = deg_to_rad(first.first);
                        pair1.second = deg_to_rad(first.second);
                        pair2.first = deg_to_rad(second.first);
                        pair2.second = deg_to_rad(second.second);
                        double R = 6371000; //meter
                        double del_phi = std::abs(pair1.first - pair2.first);
                        double del_lam = std::abs(pair1.second - pair2.second);
                        double a = (sin(del_phi / 2) * sin(del_phi / 2)) + cos(pair1.first) * cos(pair2.first) * (sin(del_lam / 2) * sin(del_lam / 2));
                        double c = 2 * atan2(sqrt(a), sqrt(1-a));
                        double d = R * c;
                        return d;
                    
                    }
        
        };
    }

    namespace vrn
    {
       class Station 
       {
            public:
                Station(long element_id, std::string long_name, std::string short_name, 
                geo::Coordinate coord) : _element_id(element_id), _long_name(long_name), _short_name(short_name), _coord(coord)
                {}

                geo::Coordinate coord() const {return this->_coord;}
                std::string short_name() const {return this->_short_name;}
                std::string long_name() const {return this->_long_name;} 
                long element_id() const {return this->_element_id;}
                std::string to_string() const 
                {
                    std::string str = "";
                    std::stringstream s1; s1 <<"Station" <<std::endl <<"{"<< std::endl << "\"longName:\"" << ": " << "\"" << _long_name << "\"" << std::endl;
                    std::stringstream s2; s2 << "\"shortName:\"" << ": " << "\"" << _short_name << "\"" << std::endl;;
                    std::stringstream s3; s3 << "\"latitude:\"" << ": " << "\"" << std::to_string(_coord.latitude()) << "\"" << std::endl;;
                    std::stringstream s4; s4 << "\"longtitude:\"" << ": " << "\"" << std::to_string(_coord.longitude()) << "\"" << std::endl;
                    std::stringstream s5; s5 << "\"elementID:\"" << ": " << std::to_string(_element_id) << std::endl << "}";

                    std::stringstream ss; ss << s1.str() << s2.str() << s3.str() << s4.str() << s5.str();
                    str = ss.str();
                    return str;
                } 

            private:
                long _element_id;
                std::string _long_name;
                std::string _short_name;
                geo::Coordinate _coord;


        };

        std::vector<Station> json_to_stations(const nlohmann::json &json)
        {
            std::vector<Station> stations;

            if(!json.contains("stations"))
            {
                return stations;
            }

            auto stations_json = json["stations"];
            for(auto it = stations_json.begin(); it != stations_json.end(); ++it)
            {
                std::string latitude = it.value()["latitude"];
                std::string longitude = it.value()["longitude"];
                double lat = std::stod(latitude);
                double lon = std::stod(longitude);

                auto coord = geo::Coordinate(lat, lon);
                auto stat = Station(it.value()["elementID"], it.value()["longName"], it.value()["shortName"], coord);

                stations.push_back(stat);
            }

            return stations;
        } 

        std::vector<Station> request_all_stations()
        {
            ipk::http::Request req;
            req.headers({{"RNV_API_TOKEN: dcqh99ct00frb38u9hevg9e3tt"},
                        {"content-type: test/json"}});
            req.perform(
                "rnv.the-agent-factory.de/easygo2/api/regions/rnv/modules/stations/packages/1", 8080
            );
            std::string output = req.result();
            nlohmann::json json = nlohmann::json::parse(output);
                    return json_to_stations(json);
        } 

        std::vector<std::pair<Station, double>> filter_nearby_stations(const std::vector<Station> &stations,
        const geo::Coordinate &target, double max_distance)
        {
            std::vector<std::pair<Station, double>> vec;
            for (auto it:request_all_stations())
            {
                if(target.distance_to(it.coord()) <= max_distance)
                {
                    vec.push_back(std::make_pair (it, target.distance_to(it.coord())));
                }
            }

            return vec;
        }
    }   
} 
