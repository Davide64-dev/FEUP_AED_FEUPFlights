#include <iostream>
#include <vector>
#include "FeupFlights.h"
char p(FeupFlights& feup);
vector<string> pesquisaCidade(FeupFlights& feup);
vector<string> codAeroporto(FeupFlights& feup);
vector<string> pesquisaCoordenadas(FeupFlights& feup);


int main() {
    FeupFlights feup = FeupFlights();
    feup.readAirlines();
    feup.readAirports();
    feup.readFlights();
    char op = ' ';

    while (op != 'q'){
        cout << "" << '\n';
        cout << "q- Sair" << "\n";

        cout << "" << "\n";
        cout << "p - Pesquisar Voo" << "\n";

        cout << "" << "\n";
        cout << "?";

        cin >> op;
        cout << "" << "\n";

        if (op == 'p'){
            char part = p(feup);
            if (part == 'q') op = ' ';
        }

    }

}

char p(FeupFlights& feup){
    string iguais = "===============================================";
    char retorno;
    vector<string> partidas, chegadas;
    cout  << "  Partidas - Selecionar modo de pesquisa de aeroportos:" << endl;
    cout << "       a - Aeroporto em Especifico" << endl;
    cout << "       c - Cidade" << endl;
    cout << "       x - Aeroportos a menos de X km" << endl;
    cout << "       q - Recuar" << endl;
    cout << "" << "\n";
    cout << "?";
    cin >> retorno;
    cout << "" << "\n";

    if (retorno == 'a'){
        partidas = codAeroporto(feup);
    }

    else if (retorno == 'c'){
        partidas = pesquisaCidade(feup);
    }

    else if (retorno == 'x'){
        partidas = pesquisaCoordenadas(feup);
    }

    if (partidas.size() == 0){
        cout << "Nao existem aeroportos que satisfacam essas condicoes!\n" << endl;
        return 'q';
    }

    else{
        cout << iguais << '\n';
        cout << "Aeroportos Selecionados: " << '\n';
        cout << "IATA|Nome|Cidade|Pais|Latitude|Longitude" << '\n';
        for (auto i : partidas){
            Airport airport = Airport(i, "Hello", "World", "2", 42, 73);
            airport = *feup.airports.find(airport);
            cout << iguais << '\n';
            cout << airport.getCod() << ", " << airport.getName() << ", "<< airport.getCity()
            << ", " << airport.getCountry() << ", "<<
            airport.getLatitude() << ", " << airport.getLongitude() << '\n';
        }
        cout << iguais << '\n' << '\n';
    }

    cout  << "  Chegadas - Selecionar modo de pesquisa de aeroportos:" << endl;
    cout << "       a - Aeroporto em Especifico" << endl;
    cout << "       c - Cidade" << endl;
    cout << "       x - Aeroportos a menos de X km" << endl;
    cout << "       q - Recuar" << endl;
    cout << "" << "\n";
    cout << "?";
    cin >> retorno;
    cout << "" << "\n";

    if (retorno == 'a'){
        chegadas = codAeroporto(feup);
    }

    else if (retorno == 'c'){
        chegadas = pesquisaCidade(feup);
    }

    else if (retorno == 'x'){
        chegadas = pesquisaCoordenadas(feup);
    }

    if (chegadas.size() == 0){
        cout << "Nao existem aeroportos que satisfacam essas condicoes!\n" << endl;
        return 'q';
    }

    else{
        cout << '\n' << iguais << '\n';
        cout << "Aeroportos Selecionados: " << '\n';
        cout << "IATA|Nome|Cidade|Pais|Latitude|Longitude" << '\n';
        for (auto i : chegadas){
            Airport airport = Airport(i, "Hello", "World", "2", 42, 73);
            airport = *feup.airports.find(airport);
            cout << iguais << '\n';
            cout << airport.getCod() << ", " << airport.getName() << ", "<< airport.getCity()
                 << ", " << airport.getCountry() << ", "<<
                 airport.getLatitude() << ", " << airport.getLongitude() << '\n';
        }
        cout << iguais << '\n';
    }

    vector<string> airlines;
    string next;
    char answer;
    cout  << '\n' <<"  Companhias Aereas - Deseja usar alguma companhia aérea em específico (s/n)? ";
    cin >> answer;
    while(answer != 'n'){
            cout << '\n' << "Código da companhia aerea a ser adicionada: ";
            cin >> next;
            Airline airline = Airline(next, "nome", "callsign", "country");
            if (feup.airlines.find(airline) != feup.airlines.end()){
                airlines.push_back(next);
                cout << '\n'<<"Deseja adicionar mais companhias (s/n)? ";
                cin >> answer;
                cout << '\n';
            }
            else{
                char sair;
                cout << '\n' << "Inserir uma companhia aérea válida!" << '\n';
                cout << "Deseja cancelar o filtro de pesquisa? (s/n)? ";
                cin >> sair;
                if (sair == 's') answer = 'n';
            }
    }

    if (!airlines.empty()) {
        cout << '\n' << iguais << '\n';
        cout << "Companhias Selecionadas: " << '\n';
        cout << "ICAO|Nome|CallSign|Pais" << '\n';
        for (auto i: airlines) {
            Airline airline = Airline(i, "Hello", "World", "2");
            airline = *feup.airlines.find(airline);
            cout << iguais << '\n';
            cout << airline.getCod() << ", " << airline.getName() << ", " << airline.getCallSign()
                 << ", " << airline.getCountry()  << '\n';
        }
        cout << iguais << '\n';
    }

    list<string> temp = feup.flights.leastFlights(partidas, chegadas, airlines);
    list<string>::iterator it = temp.begin();

    cout << '\n';
    while (*it != temp.back()){
        cout << *it << "->";
        it++;
    }
    cout << *it << '\n';
    return retorno;
}

vector<string> codAeroporto(FeupFlights& feup){
    vector<string> aeroportos;
    string cod;
    cout << "Inserir Codigo do Aeroporto: ";
    cin >> cod;
    Airport airport = Airport(cod, "hello", "world", "i", 73, 42);
    if (feup.airports.find(airport) != feup.airports.end()) {
        aeroportos.push_back(cod);
    }
    return aeroportos;
}

vector<string> pesquisaCidade(FeupFlights& feup){
    string cidade, pais;
    cout<< "Inserir nome da cidade: ";
    cin >> cidade;
    cout << "Inserir nome do pais: ";
    cin >> pais;
    vector<string> aeroportos = feup.allAirportsCity(cidade, pais);
    return aeroportos;
}

vector<string> pesquisaCoordenadas(FeupFlights& feup){
    float latitude, longitude;
    int x;
    cout << "Inserir latitude: ";
    cin >> latitude;
    cout << "Inserir longitude: ";
    cin >> longitude;
    cout << "Aeroportos a menos de quantos km? ";
    cin >> x;
    vector<string> aeroportos = feup.allAirportsLessThan(x, latitude, longitude);
    return aeroportos;
}
