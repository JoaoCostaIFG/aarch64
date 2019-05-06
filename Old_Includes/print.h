#include "modify.h"

void print_morada(const Morada &morada)
{
    std::cout << "\nRua: " << morada.nome << "\nNum_Porta: " << morada.num_porta << "\nNum_Andar: " << morada.num_andar << "\nCodigo_Postal: " << morada.codigo_postal << "\nLocalidade: " << morada.localidade << '\n';
}


void print_data(const Data &data)
{
    std::cout << "Ano: " << data.ano << "  Mês: " << data.mes << "  Dia: " << data.dia;
}

//Prints all info about the client
void print_cliente(const Cliente &cliente)
{
    std::cout << "Nome: " << cliente.nome << "\nNIF: "  << cliente.nif << "\nNumero agregado familiar: " << cliente.num_pessoas_agregado_familiar;
    print_morada(cliente.morada);
    std::cout << "Pacotes turisticos adquiridos: ";
    int n(cliente.pacotes_turisticos_adquiridos.size());
    for(int i=0;i<n-1;i++) std::cout << cliente.pacotes_turisticos_adquiridos[i] << " ; ";
    std::cout << cliente.pacotes_turisticos_adquiridos[n - 1];
    std::cout << "\n";
}
// Prints info about all clients from the index start to the end
void print_cliente(const std::vector<Cliente> &lista_clientes, const int start=0)
{
    int end = lista_clientes.size();
    for(int i=start;i<end;i++)
    {
        print_cliente(lista_clientes[i]);
        std::cout << "\n\n";
    }
}

// Prints info about a specific package
void print_pacote(const PactoteTuristico &pacote)
{
    std::cout << "\nID: " << pacote.id << "\nItenerario: " << pacote.locais_turisticos;
    std::cout << "\nData do Inicio-> ";print_data(pacote.data_inicio);
    std::cout << "\nData do Fim-> "; print_data(pacote.data_fim);
    std::cout << "\nPreco: " << pacote.preco << "\nNumero maximo de lugares: " << pacote.num_lugares_max;
    std::cout << "\nLugares vendidos: " << pacote.num_lugares_vendidos;
}
// Prints info about all packages
void print_pacote(const std::vector<PactoteTuristico> &lista_pacotes)
{
    for(int i=0;i<lista_pacotes.size();i++)
    {
        print_pacote(lista_pacotes[i]);
        std::cout << "\n\n";
    }
}
// Prints all packages that correspond to a given location
void print_pacote(const std::vector<PactoteTuristico> &lista_pacotes, const std::string destino)
{
    for(int i=0;i<lista_pacotes.size();i++)
    {
        std::string aux_string = lista_pacotes[i].locais_turisticos;
        aux_string = aux_string.substr(0, aux_string.find_first_of('-') - 1);  // select first string (the one that corresponds to the given location)
        if(aux_string == destino)
            print_pacote(lista_pacotes[i]);
        std::cout << "\n\n";
    }
}
/* Prints all packages between data_inicio and data_fim*/
void print_pacote(const std::vector<PactoteTuristico> &lista_pacotes, const std::string str_data_inicio, const std::string str_data_fim)
{
    Data data_inicio, data_fim;

    data_inicio = string_to_data(str_data_inicio);
    data_fim = string_to_data(str_data_fim);

    for(int i=0;i<lista_pacotes.size();i++)
    {
        //std::cout << "bef" << is_before(data_inicio, lista_pacotes[i].data_inicio)  << '\n';
        if(is_before(data_inicio, lista_pacotes[i].data_inicio) && !is_before(data_fim, lista_pacotes[i].data_fim))
            print_pacote(lista_pacotes[i]);

        std::cout << "\n\n";
    }
}
/* Prints all packages between data_inicio and data_fim which main location corresponds to a given destino.
The limits of dates work like the following: only the packages that start before or that have the same date than data_inicio while
also having its ending at least one day after data_fim are printed.*/
void print_pacote(const std::vector<PactoteTuristico> &lista_pacotes,const std::string destino, const std::string str_data_inicio, const std::string str_data_fim)
{
    Data data_inicio, data_fim;
    try
    {
        data_inicio = string_to_data(str_data_inicio);
        data_fim = string_to_data(str_data_fim);
    }
    catch(const char error[30])
    {
        std::cout << error << '\n';
        //TODO: VERIFY THIS
    }

    for(int i=0;i<lista_pacotes.size();i++)
    {
        if(is_before(data_inicio, lista_pacotes[i].data_inicio) && !is_before(data_fim, lista_pacotes[i].data_fim))
            {
                std::string aux_string = lista_pacotes[i].locais_turisticos;
                aux_string = aux_string.substr(0, aux_string.find_first_of('-') - 1); // select first string (the one that corresponds to the given location)
                if(aux_string == destino)
                    print_pacote(lista_pacotes[i]);
            }
        std::cout << "\n\n";
    }
}
// Prints info about all of the packages that correspond to the indexes in pacotes_turisticos_adquiridos
void print_pacote(const std::vector<PactoteTuristico> &lista_pacotes, const std::vector<int> pacotes_turisticos_adquiridos)
{
    int s(0);
    for(int i=0;i<pacotes_turisticos_adquiridos.size();i++)
    {
        int id = find_index(pacotes_turisticos_adquiridos[i], lista_pacotes);  // gets index in the vector of packages of the current id
        if(id != -1)
        {
            s++;
            print_pacote(lista_pacotes[i]);
            std::cout << "\n";
        }   
    }
    if(s == 0)  // if no package was found means that the client of the purchased_packets vector hasn't purchased any package
    {
        std::cout << "Este cliente nao adquiriu nenhum pacote\n";
    }
}
// prints all packages of all clients
void print_pacote(const std::vector<PactoteTuristico> &lista_pacotes, const std::vector<Cliente> lista_clientes)
{
    int s(0);
    for(int i=0;i<lista_clientes.size();i++)
    {
        std::cout << "Cliente " << lista_clientes[i].nome << ":\n";
        print_pacote(lista_pacotes, lista_clientes[i].pacotes_turisticos_adquiridos);
        std::cout << "____________________________//________________________________//______________\n\n\n";
    }

}

// prints the total packages sold and the overall profit
void print_total_profit(const std::vector<PactoteTuristico> &lista_pacotes_turisticos)
{
    int num_pacotes_vendidos_total(0), lucro_total(0);
    
    for(int i=0;i<lista_pacotes_turisticos.size();i++)
    {
        num_pacotes_vendidos_total += lista_pacotes_turisticos[i].num_lugares_vendidos;
        lucro_total += lista_pacotes_turisticos[i].preco * lista_pacotes_turisticos[i].num_lugares_vendidos;
    }

    clear_screen();
    std::cout << "Numero de pacotes vendidos no total: " << num_pacotes_vendidos_total << "\nLucro Total: " << lucro_total << "\n\n";
}
