#include <string>

using namespace std;

//Class containing all the info of an accident in the database
class TrafficAccident {
public:
    std::string ID;
    int severity;
    double distance;
    std::string city;
    std::string state;
    std::string zipcode;

    TrafficAccident() : severity(0), distance(0.0) {}

    TrafficAccident(std::string id, int severity, double distance, std::string city, std::string state, std::string zipcode)
            : ID(std::move(id)), severity(severity), distance(distance), city(std::move(city)), state(std::move(state)), zipcode(std::move(zipcode)) {}
};