//
// Created by Davide Teixeira on 27/12/2022.
//

#ifndef AED_PROJECT2_AIRLINE_H
#define AED_PROJECT2_AIRLINE_H

#include <string>

using namespace std;

class Airline {

    string cod;
    string name;
    string callSign;
    string country;

public:
    Airline(string cod, string name, string callSign, string country);
    string getCod() const;
    string getName() const;
    string getCallSign() const;
    string getCountry() const;
};

struct betAirline
{
    // TODO
    int operator() (const Airline& b) const {
        string temp = "";
        for (unsigned i = 0; i < 3;i++){
            int num = int(b.getCod()[i]);
            temp = temp + to_string(num);
        }
        return stoi(temp);
    }

    // TODO
    bool operator() (const Airline& b1, const Airline& b2) const {
        return b1.getCod() == b2.getCod();
    }
};


#endif //AED_PROJECT2_AIRLINE_H
