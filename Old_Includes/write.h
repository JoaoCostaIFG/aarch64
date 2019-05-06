#include "read.h"

// save the info of a given agencia to a file
void save_agency(const std::string agency_file_name, const std::string client_file_name,const std::string packs_file_name, const Agencia &agencia)
{
    std::ofstream file_output;
    file_output.open (agency_file_name);
    file_output << agencia.name << '\n' << agencia.nif << '\n' << agencia.url << '\n';
    file_output << morada_to_string << '\n';
    file_output << client_file_name << '\n';
    file_output << packs_file_name;
    file_output.close();
}
// save the info of a given vector of clients to a file
void save_clients(const std::string clients_file_name, const std::vector<Cliente> &lista_clientes)
{
    std::ofstream file_output;
    file_output.open (clients_file_name);
    int client_len = lista_clientes.size();
    for(int i=0;i<client_len-1;i++)
    {
        file_output << lista_clientes[i].nome << '\n' << lista_clientes[i].nif
        << '\n' << lista_clientes[i].num_pessoas_agregado_familiar 
        << '\n' << morada_to_string(lista_clientes[i].morada) << '\n';
        int packet_len = lista_clientes[i].pacotes_turisticos_adquiridos.size();
        
        for(int j=0;j<packet_len-1;j++)
        {
            file_output << lista_clientes[i].pacotes_turisticos_adquiridos[j] << " ; ";
        }

        file_output << lista_clientes[i].pacotes_turisticos_adquiridos[packet_len-1] << '\n';
        file_output << "::::::::::\n";
    }
    int i = client_len-1;

    file_output << lista_clientes[i].nome << '\n' << lista_clientes[i].nif
        << '\n' << lista_clientes[i].num_pessoas_agregado_familiar 
        << '\n' << morada_to_string(lista_clientes[i].morada) << '\n';
    int packet_len = lista_clientes[i].pacotes_turisticos_adquiridos.size();

    for(int j=0;j<packet_len-1;j++)
    {
        file_output << lista_clientes[i].pacotes_turisticos_adquiridos[j] << " ; ";
    }

    file_output << lista_clientes[i].pacotes_turisticos_adquiridos[packet_len-1] << '\n';
    // done because file doesn't end with ::::::::::\n
    file_output.close();
}
// save the info of a given vector of packages to a file
void save_packs(const std::string packs_file_name, const std::vector<PactoteTuristico> &lista_pacotes_turisticos)
{
    std::ofstream file_output;
    file_output.open (packs_file_name);
    int packet_size = lista_pacotes_turisticos.size();

    file_output << lista_pacotes_turisticos[packet_size-1].id;  // add last package id to the top of the file
    for(int i=0;i<packet_size-1;i++)
    {
        file_output << '\n' << lista_pacotes_turisticos[i].id
        << '\n' << lista_pacotes_turisticos[i].locais_turisticos
        << '\n' << data_to_string(lista_pacotes_turisticos[i].data_inicio) 
        << '\n' << data_to_string(lista_pacotes_turisticos[i].data_fim)
        << '\n' << lista_pacotes_turisticos[i].preco 
        << '\n' << lista_pacotes_turisticos[i].num_lugares_max
        << '\n' << lista_pacotes_turisticos[i].num_lugares_vendidos
        << '\n' << "::::::::::";
    }

    int i=packet_size-1;
    file_output << '\n' << lista_pacotes_turisticos[i].id
    << '\n' << lista_pacotes_turisticos[i].locais_turisticos
    << '\n' << data_to_string(lista_pacotes_turisticos[i].data_inicio) 
    << '\n' << data_to_string(lista_pacotes_turisticos[i].data_fim)
    << '\n' << lista_pacotes_turisticos[i].preco 
    << '\n' << lista_pacotes_turisticos[i].num_lugares_max
    << '\n' << lista_pacotes_turisticos[i].num_lugares_vendidos;
    // done because file doesn't end with ::::::::::\n

    file_output.close();
}

// saves all of the info of an agency into a set of files specified by the user
void save_files(const Agencia &agencia)
{
    std::string agency_file, clients_file, packs_file;
    std::cout << "Digite -1 a qualquer momento para sair\n";
    std::cout << "Insira o nome do ficheiro da agencia\n"; std::cin >> agency_file;
    if(agency_file == "-1") return;

    std::cout << "Insira o nome do ficheiro dos clientes\n"; std::cin >> clients_file;
    if(clients_file == "-1") return;
    if(agency_file == clients_file)
        throw(std::string("Os ficheiros de agencia e clientes nao podem ter o mesmo nome!\n"));
    
    std::cout << "Insira o nome do ficheiro dos pacotes\n"; std::cin >> packs_file;
    if(packs_file == "-1") return;
    if(packs_file == agency_file)
        throw(std::string("Os ficheiros de agencia e pacotes nao podem ter o mesmo nome!\n"));
    if(packs_file == clients_file)
        throw(std::string("Os ficheiros de pacotes e clientes nao podem ter o mesmo nome!\n"));

    save_agency(agency_file,clients_file, packs_file, agencia);
    save_clients(clients_file, agencia.lista_clientes);
    save_packs(packs_file, agencia.lista_pacotes_turisticos);
}
