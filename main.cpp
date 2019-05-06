#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <sys/stat.h>

#define brk() do { std::cout << "Press the 'enter' key to continue.." << '\n'; getchar(); } while (0); //break function used for waiting for the user
#define clr_screen() std::cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n"; //clear screen

std::string str_trim(const std::string& str){
    /*
        Trims a string of whitespaces in the beggining and end;
        Takes a string to trim as an argument;
        Returns the trimmed string;
    */
    return (str.substr(str.find_first_not_of(" "), str.find_last_not_of(" ") - str.find_first_not_of(" ") + 1));
}


#include "include/date.h"
#include "include/address.h"
#include "include/travelpack.h"


int main(){
    int a;
    std::cin >> a;
    /*
    Date date1, date2;
    std::cout << (date1 < date2);
    */
    return 0;
}

/*TODO:
Travel pack:
-----Private var is_overbooked() associada a um método para verificar isso
-----Verificar se startdate<endsate se não exception
Agency n e class
-----Is_unavailable var travel pack é método (nunca apagar mesmo)
-----Travel packs getters
Travel pack 1 string é destino
As cenas após o hífen são pontos de interesse (guardar em array)
Fim: dicionário keys são pontos de interesse para contar n de visitas

-----Travel pack ++ overload: Adiciona venda / Atualiza dicionário / Verifica overbooking
*/