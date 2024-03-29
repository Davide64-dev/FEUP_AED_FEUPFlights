#include <iostream>
#include <vector>
#include "FeupFlights.h"
char p(FeupFlights& feup);
void info(FeupFlights& feup);
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
        cout << "q - Sair" << "\n";

        cout << "" << "\n";
        cout << "p - Pesquisar Voo" << "\n";

        cout << "" << "\n";
        cout << "i - Pesquisar informacoes sobre um aeroporto" << '\n';

        cout << "" << "\n";
        cout << "?";

        cin >> op;
        cout << "" << "\n";

        if (op == 'p'){
            char part = p(feup);
            if (part == 'q') op = ' ';
        }

        if (op == 'i'){
            info(feup);
        }

    }
    return 0;

}

void info(FeupFlights& feup){
    string temp;
    char t;
    cout << "  Inserir codigo do aeroporto: ";
    cin >> temp;
    Airport airport = Airport(temp, "fsc", "dwsc", "wvdscx", 34,34);
    if (feup.airports.find(airport) == feup.airports.end()){
        cout << "Inserir aeroporto valido!" << endl;
        return;
    }

    cout << "\n";
    cout  << "   v - Quantos voos existem a partir do "<< temp << "?" << endl;

    cout << "\n";
    cout << "   a - Quantas companhias aereas diferentes tem voos que comecam no "<< temp <<"?" << endl;

    cout << '\n';
    cout << "   d - Para quantos destinos diferentes vao os voos do "<< temp <<"?" << endl;

    cout << '\n';
    cout << "   p - Para quantos paises diferentes vao os voos do " << temp << "?" << endl;

    cout << '\n';
    cout << "   r - Quantos aeroportos sao atingiveis com um maximo de Y voos? " << endl;

    cout << '\n';
    cout << "   c- Quantas cidades sao atingiveis com um maximo de Y voos? " << endl;

    cout << "\n";
    cout << "   z - Quantos paises sao atingiveis com um maximo de Y voos? " << endl;

    cout << "\n";
    cout << "   q - Recuar" << endl;

    cout << "?";
    cin >> t;

    if (t == 'v'){
        int num = feup.manyFlights(temp);
        cout << "\n" << "Existem " << num << " voos a partir de " << temp << endl;
        cout << "\n";
    }

    if (t == 'a'){
        int num = feup.differentAirlines(temp);
        cout << "\n" << "Existem " << num << " companhias aereas diferentes a voar a partir de "
        << temp << endl;
        cout << "\n";
    }

    if (t == 'd'){
        int num = feup.differentDestenies(temp);
        cout << '\n' << "Com exatamente 1 voo, e possivel chegar a exatamente " << num
        << " destinos(cidades) diferentes"<< endl;
        cout << "\n";
    }

    if (t == 'p'){
        int num = feup.differentCountries(temp);
        cout << '\n' << "Com exatamente 1 voo, e possivel chegar a exatamente " << num
             << " paises diferentes"<< endl;
        cout << "\n";
    }

    if (t == 'r'){
        int y;
        cout << '\n' << "       Inserir parametro Y: ";
        cin >> y;

        int num = feup.airportsLessThanY(temp, y);
        cout << '\n' << "Com exatamente "<< y <<" voos, e possivel chegar a exatamente " << num
             << " aeroportos diferentes"<< endl;
        cout << "\n";
    }

    if (t == 'c'){
        int y;
        cout << '\n' << "       Inserir parametro Y: ";
        cin >> y;

        int num = feup.citiesLessThanY(temp, y);
        cout << '\n' << "Com exatamente "<< y <<" voos, e possivel chegar a exatamente " << num
             << " cidades diferentes"<< endl;
        cout << "\n";
    }

    if (t == 'z'){
        int y;

        cout << '\n' << "       Inserir parametro Y: ";
        cin >> y;

        int num = feup.countriesLessThanY(temp, y);

        cout << '\n' << "Com exatamente "<< y <<" voos, e possivel chegar a exatamente " << num
             << " paises diferentes"<< endl;
        cout << "\n";
    }

    if (t == 'q'){
        return;
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
    cout  << '\n' <<"  Companhias Aereas - Deseja usar alguma companhia aerea em especifico (s/n)? ";
    cin >> answer;
    while(answer != 'n'){
            cout << '\n' << "Codigo da companhia aerea a ser adicionada: ";
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
                cout << '\n' << "Inserir uma companhia aerea valida!" << '\n';
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
        cout << '\n' << iguais << '\n';
    }
    list<string> temp;
    temp = feup.flights.leastFlights(partidas, chegadas, airlines);
    list<string>::iterator it = temp.begin();

    if (airlines.empty()) {
        if (!temp.empty()) {
            cout << '\n';
            while (*it != temp.back()) {
                cout << feup.findAirport(*it).getName() << '\n';
                cout << "   |              ";
                list<string>::iterator rt = it;
                rt++;
                list<string> toPrint = feup.flights.allFlights(*it, *rt);
                for (auto i: toPrint) cout << feup.findAirline(i).getName() << "     ";
                cout << '\n' << "   V" << endl;
                it++;
            }
            cout << feup.findAirport(*it).getName() << '\n';
        }
        else{
            cout << "Nao foi possivel encontrar voos" << endl;
        }
    }
    else{
        if (!temp.empty()) {
            cout << '\n';
            while (*it != temp.back()) {
                cout << feup.findAirport(*it).getName() << '\n';
                cout << "   |              ";
                list<string>::iterator rt = it;
                rt++;
                list<string> toPrint = feup.flights.allFlightsFrom(*it, *rt, airlines);
                for (auto i: toPrint) cout << feup.findAirline(i).getName() << "     ";
                cout << '\n' << "   V" << endl;
                it++;
            }
            cout << feup.findAirport(*it).getName() << '\n';
        }
        else{
            cout << "Nao foi possivel encontrar voos" << endl;
        }
    }
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
    string cidade;
    string pais;
    cout<< "Inserir nome da cidade (Se a cidade tiver espacos, deve substitui-los por '_'): ";
    cin >> cidade;

    for (int i = 0; i < cidade.size();i++){
        if (cidade[i] == '_') cidade[i] = ' ';
    }


    cout << "Inserir nome do pais (Se o pais tiver espacos, deve substitui-los por '_'): ";
    cin >> pais;

    for (int i = 0; i < pais.size();i++){
        if (pais[i] == '_') pais[i] = ' ';
    }


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
