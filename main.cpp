#include "include/agency.h"
#include <sstream>
int main()
{
    Agency a;
    std::istringstream input_string;
    input_string.str("Rui Manuel\n2349871564\n4\nRua Sem Fim / 200 / 5Esq / 1200‐001 / Lisboa\n1 ; 36 ; 2\n350");
    
    Client b(input_string);
    // a.client_list.push_back(b);
    // clr_screen();
    // std::cout << client_exists(a.client_list, b.getName());
    // std::cout << client_exists(a.client_list, b.getName(), b.getNif());
    // a.client_list[0].print(std::cout);
}