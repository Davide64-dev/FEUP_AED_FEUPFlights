#include <iostream>
#include <tclTomMathDecls.h>
#include <vector>
#include "FeupFlights.h"
char p(string a);


int main() {
    FeupFlights feup = FeupFlights();
    feup.readAirlines();
    feup.readAirports();
    feup.readFlights();
    char op = ' ';
    /*
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
            char part = p("Partida");
            if (part == 'q') op = ' ';
            char cheg = p("Partida");
            if (cheg == 'q') op = ' ';
        }

    }
     */
    vector<string> temp = feup.allAirportsCity("London", "United Kingdom");
    for (string i : temp) cout << i << ", ";
}

char p(string a){
    char retorno;
    cout  << "  "<< a <<" - Selecionar modo de pesquisa de aeroportos:" << endl;
    cout << "       a - Aeroporto em Especifico" << endl;
    cout << "       c - Cidade" << endl;
    cout << "       x - Aeroportos a menos de X km" << endl;
    cout << "       q - Recuar" << endl;
    cout << "" << "\n";
    cout << "?";
    cin >> retorno;
    cout << "" << "\n";

    if (retorno == 'a'){
        string cod;
        cout << "Inserir Código do Aeroporto: ";
        cin >> cod;
    }
    return retorno;
}
