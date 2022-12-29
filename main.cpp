#include <iostream>
#include "FeupFlights.h"

int main() {
    FeupFlights feup = FeupFlights();
    feup.readAirlines();
    feup.readAirports();
    feup.readFlights();
    feup.showEdgesTest();
}
