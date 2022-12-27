//
// Created by Davide Teixeira on 27/12/2022.
//

#ifndef AED_PROJECT2_AIRPORT_H
#define AED_PROJECT2_AIRPORT_H

#include <string>

using namespace std;

class Airport {
    string cod;
    string name;
    string city;
    string country;
    float latitude;
    float longitude;

public:
    Airport(string cod, string name, string city, string country,float latitude, float longitude);
    string getCod() const;
    string getName() const;
    string getCity() const;
    string getCountry() const;
    float getLatitude() const;
    float getLongitude() const;
};

struct HashAirport
{
    // TODO
    int operator() (const Airport& b) const {
        string temp = "";
        for (unsigned i = 0; i < 3;i++){
            int num = int(b.getCod()[i]);
            temp = temp + to_string(num);
        }
        return stoi(temp);
    }

    // TODO
    bool operator() (const Airport& b1, const Airport& b2) const {
        return b1.getCod() == b2.getCod();
    }
};

#endif //AED_PROJECT2_AIRPORT_H
