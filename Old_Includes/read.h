/*@input_stream: Where the received input comes from*/
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

typedef struct
{
    std::string nome;
    int num_porta; // not set to string because it is a mandatory variable that can only take positive values
    std::string num_andar;
    std::string codigo_postal;
    std::string localidade;
} Morada;


typedef struct
{
    unsigned int ano;
    unsigned short int mes;
    unsigned short int dia;
} Data;

typedef struct
{
    int id;
    std::string locais_turisticos;
    Data data_inicio;
    Data data_fim;
    unsigned int preco;
    unsigned int num_lugares_max;
    unsigned int num_lugares_vendidos;
} PactoteTuristico;

typedef struct
{
    std::string nome;
    unsigned int nif;
    unsigned int num_pessoas_agregado_familiar;
    Morada morada;
    std::vector<int> pacotes_turisticos_adquiridos; //equal to the maximum pacote_turistico.id
} Cliente;

typedef struct
{
    std::string name;
    unsigned int nif;
    Morada morada;
    std::string url;
    std::vector<PactoteTuristico> lista_pacotes_turisticos;
    std::vector<Cliente> lista_clientes;
} Agencia;

bool is_before(Data data_inicio, Data data_fim);

/* Seperates a string into a vector according to a separator.
@param string: String to be separated.
@param sep: Separator filter to be used when separating strings
@param result: Vector where the seperated strings will be inserted
*/
void separate_string_to_vector(std::string string, std::vector<std::string> &result, std::string sep=" ")
{
    int i(0), next_pos(string.find(sep)), sep_size(sep.size()); 

    while(next_pos != -1)  // do until you can't find a new seperator
    {
        result.push_back(string.substr(0, next_pos));  // push back everything before the seperator
        string = string.substr(next_pos + sep_size, string.length());  // destroy everything before (and including) the seperator
        next_pos = string.find(sep);  // next_position will be the next seperator
        i++;
    }
    result.push_back(string);  // pushback the remainder of the string 
}
/* Seperates a string into a vector according to a separator. The string must only have numbers separated by the separator.
Mainly used to seperate the purchased packages
@param string: String to be separated.
@param sep: Separator filter to be used when separating strings
@param result: Vector where the seperated integers will be inserted
*/
void separate_string_to_vector(std::string string, std::vector<int> &result, std::string sep=";")
{
    //TODO: REMOVE WHITESPACES BEFORE SEPERATING THE STRINGS
    int i(0), next_pos(string.find(sep)), sep_size(sep.size()), aux_num;

    while(next_pos != -1) // while a separator exists
    {
        std::string aux_string = string.substr(0, next_pos);
        try  // see if the number is an integer
        {
            aux_num = std::stoi(aux_string);
        }
        catch(const std::invalid_argument e)
        {
            throw(std::string("FORMATACAO DOS PACOTES ADQUIRIDOS ERRADA! (Use o formato:[n1 ; n2 ; n3... ; n]"));
        }

        result.push_back(aux_num);
        string = string.substr(next_pos + sep_size, string.length());
        next_pos = string.find(sep);
        i++;
    }

    try
    {
        aux_num = std::stoi(string);
    }
    catch(const std::invalid_argument e)
    {
        throw(std::string("FORMATACAO DOS PACOTES ADQUIRIDOS ERRADA! (Use o formato:[n1 ; n2 ; n3... ; n]"));
    }
    result.push_back(aux_num);
}

void clear_screen()
{
    std::cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
}


/*Converts a given string to a Data*/
Data string_to_data(std::string string)
{
    std::vector <std::string> aux_vector;
    separate_string_to_vector(string, aux_vector, "/");

    if(aux_vector.size() != 3)
        throw(std::string("TAMANHO INCORRETO INSERIDO, DIGITE NO FORMATO Ano/Mes/Dia"));
    
    unsigned int ano(std::stoi(aux_vector[0]));
    unsigned short int mes(std::stoi(aux_vector[1])), dia(std::stoi(aux_vector[2]));

    if((mes < 1) || (mes > 12))
        throw(std::string("DIGITE UM MES ENTRE 1 E 12"));
    
    if((dia < 1) || (dia > 31))
        throw(std::string("DIGITE UM DIA ENTRE 1 e 31"));

    return((Data){
        ano,
        mes,
        dia
    });
}
/*Converts a given data to a string*/
std::string data_to_string(const Data &data)
{
    std::string mes, dia;
    mes = std::to_string(data.mes);
    dia = std::to_string(data.dia);
    
    if(data.mes < 10)
        mes = '0' + mes;
    if(data.dia < 10)
        dia = '0' + dia;
    
    return(std::to_string(data.ano) + '/' + mes + '/' + dia);
}


/*Converts string into morada*/
Morada string_to_morada(const std::string string)
{
    std::vector<std::string> morada_separated;

    separate_string_to_vector(string, morada_separated, " / ");

    if(morada_separated.size() != 5)
        throw(std::string("FORMATO DA MORADA INCORRETO! (Nome / Numero_Porta / Num_Andar / Cod_Postal / Localidade)\n"));

    return((Morada){morada_separated[0],
        std::stoi(morada_separated[1]),
        morada_separated[2],
        morada_separated[3],
        morada_separated[4],
    });
}
// Converts a morada to a string
std::string morada_to_string(const Morada &morada)
{
    std::string string;
    string = morada.nome + " / " + std::to_string(morada.num_porta) + " / " + morada.num_andar
    + " / " + morada.codigo_postal + " / " + morada.localidade;
    return(string);
}

// Check if a given package is overbooked
void verify_overbooking(PactoteTuristico &pacote)
{
    if((pacote.num_lugares_vendidos == pacote.num_lugares_max) && (pacote.id > 0)) //if packet isn't flaged as overbooked but is overbooked
        pacote.id = pacote.id * -1;  // overbook it :)
}
// reads input from a input stream to a given client
void read_client(Cliente &cliente, std::istream &input_stream)
{
    input_stream.clear();

    Morada morada;
    unsigned int nif;
    int num_agregado_familiar;
    std::string aux_string, nome;  //string auxiliar
    std::vector<int> pacotes_turisticos_adquiridos; 

    std::cout << "Nome?\n"; std::getline(input_stream, nome);
    if(nome == "-1")
        throw(std::string("-1 NAO PODE SER USADO COMO UM NOME VALIDO!\n"));
    //-1 is used in verification and so it can't be used

    std::cout << "NIF?\n"; input_stream >> nif;
    if(input_stream.fail()) 
    {
        input_stream.clear(); input_stream.ignore(1000, '\n');  // if failed then clear stream
        throw(std::string("NIF INCORRETO!"));
    }

    std::cout << "Numero do agregado familiar?\n"; input_stream >> num_agregado_familiar;
    if(input_stream.fail())
    {
        input_stream.clear(); input_stream.ignore(1000, '\n');
        throw(std::string("NUMERO AGREGADO INCORRETO!"));
    }
    else input_stream.ignore(); // used for getline used in next input

    std::cout << "Morada? (Nome / Numero_Porta / Num_Andar / Cod_Postal / Localidade) SEPARADO POR ESPACOS!!\n"; std::getline(input_stream, aux_string); morada = string_to_morada(aux_string);

    std::cout << "Pacotes adquiridos? (SEPARADOS POR \" ; \") \n"; std::getline(input_stream, aux_string);
    separate_string_to_vector(aux_string, pacotes_turisticos_adquiridos, " ; ");
    //Qualquer tipo de exceção criada por um mau input do utilizadora irá ser detetada pelo stoi na função separate_string_to_vector

    if(&input_stream != &std::cin) // Se a stream de input dos args da funcao tem o mesmo endereco de memoria que cin
    {
        input_stream.ignore('\n'); 
        input_stream.ignore(); // used to ignore "::::::::::", apenas está presente no ficheiro
    }

    //if no exceptions until here, set variables
    cliente.nome = nome;
    cliente.nif = nif; cliente.num_pessoas_agregado_familiar = num_agregado_familiar;
    cliente.morada = morada;
    cliente.pacotes_turisticos_adquiridos = pacotes_turisticos_adquiridos;
}

/*@input_stream: Where the received input comes from*/
void read_pack(PactoteTuristico &pacote, std::istream &input_stream)
{
    input_stream.clear();
    int id;
    unsigned int preco, num_lugares_max, num_lugares_vendidos;
    std::string aux_string, locais_turisticos;  //string auxiliar
    Data data_inicio, data_fim;


    std::cout << "ID?\n"; input_stream >> id;
    if(input_stream.fail()) 
    {
        input_stream.clear(); input_stream.ignore(1000, '\n');
        throw(std::string("ID INVALIDO!"));
    }
    else input_stream.ignore();
    if(id == -2000 || id == 2000)
        throw("-2000 NAO PODE SER USADO COMO UM ID VALIDO\n");
    // -2000 is used in verification, so it cant be used

    std::cout << "Locais Turisticos?\n"; std::getline(input_stream, locais_turisticos);

    std::cout << "Data Inicio? (Formato Ano/Mes/Dia)\n"; std::getline(input_stream, aux_string); data_inicio = string_to_data(aux_string);
    std::cout << "Data Fim? (Formato Ano/Mes/Dia)\n"; std::getline(input_stream, aux_string); data_fim = string_to_data(aux_string);
    // Verification for data is done in the string_to_data function
    if(is_before(data_fim, data_inicio))
        throw(std::string("A DATA DE FIM NAO PODE SER ANTES DA DATA DE INICIO"));

    std::cout << "Preco?\n"; input_stream >> preco; 
    if(input_stream.fail()) 
    {
        input_stream.clear(); input_stream.ignore(1000, '\n');
        throw(std::string("PRECO INVALIDO!"));
    }

    std::cout << "Lugares maximos?\n"; input_stream >> num_lugares_max;
    if(input_stream.fail()) 
    {
        input_stream.clear(); input_stream.ignore(1000, '\n');
        throw(std::string("LUGARES MAXIMOS INVALIDOS!"));
    }

    std::cout << "Lugares vendidos?\n"; input_stream >> num_lugares_vendidos;
    if(input_stream.fail()) 
    {
        input_stream.clear(); input_stream.ignore(1000, '\n');
        throw(std::string("LUGARES VENDIDOS INVALIDOS!"));
    }

    std::cout << "Digite algo para acabar o input\n";

    if(num_lugares_vendidos > num_lugares_max)
        throw(std::string("O NUMERO DE LUGARES VENDIDOS NAO DEVE EXCEDER O NUMERO DE LUGARES MAXIMOS!\n"));
    


    if(&input_stream != &std::cin) // Se a stream de input dos args da funcao tem o mesmo endereco de memoria que cin
    {
        input_stream.ignore('\n'); 
        input_stream.ignore(); // used to ignore "::::::::::", only used when reading from file
    }

    //if no exceptions until here, set variables

    pacote.id = id;
    pacote.locais_turisticos = locais_turisticos; 
    pacote.data_inicio = data_inicio; pacote.data_fim = data_fim;
    pacote.preco = preco; pacote.num_lugares_max = num_lugares_max; pacote.num_lugares_vendidos = num_lugares_vendidos;
    verify_overbooking(pacote); // check if pacote is overbooked

    clear_screen();
}

// reads all clients from a file with the name clients_file_name to lista_clientes
void read_clients_file(const std::string clients_file_name, std::vector<Cliente> &lista_clientes)
{
    std::ifstream file_input(clients_file_name);
    
    while(!file_input.eof())
    {
        Cliente *cliente = new Cliente;
        read_client((*cliente), file_input);
        lista_clientes.push_back((*cliente));

        //TODO: verificar se pacote turistico existe. No need for this i think
                                
    }
    file_input.close();
}

// reads all packages from a file with the name packs_file_name to lista_pacotes_turisticos
void read_pacotesturisticos_file(const std::string packs_file_name, std::vector<PactoteTuristico> &lista_pacotes_turisticos)
{
    std::ifstream file_input(packs_file_name);

    int last_id;
    file_input >> last_id;
    PactoteTuristico *pacote = new PactoteTuristico;
    while((*pacote).id != last_id)
    {
        read_pack((*pacote), file_input);
        
        lista_pacotes_turisticos.push_back((*pacote));
        PactoteTuristico *pacote = new PactoteTuristico;
    }
    file_input.close();
}
#include <string.h>
// reads all of the info contained in a set files (which names will be specified by the user) to an agency
void read_agency_file(Agencia &agencia)
{
    std::string agency_file_name, clients_file_name, packs_file_name, url, name, aux_string;
    unsigned int nif;
    Morada morada;

    std::cout << "Insira o nome do ficheiro da agencia.\n"; std::cin >> agency_file_name;

    std::ifstream file_input(agency_file_name);
    if(!file_input.is_open())
    {
        aux_string = "ERRO: O ficheiro da agencia inserido (" + agency_file_name + ") nao existe!\n";
        throw(aux_string);
    }

    getline(file_input, name);

    file_input >> nif; if(file_input.fail()) throw("NIF INCORRETO NO FICHEIRO\n");   
    file_input.ignore(); // >> doesn't read '\n', which would conflict with getline

    getline(file_input, url);

    getline(file_input, aux_string);  // reads morada
    try
    {
        morada = string_to_morada(aux_string);
    }
    catch(const char e[30])
    {
        std::cout << e;
    }
    
    

    getline(file_input, clients_file_name);
    getline(file_input, packs_file_name);

    file_input.close();


    file_input.open(clients_file_name);
    if(!file_input.is_open())
    {
        aux_string = "ERRO: O ficheiro de agencia inserido (" + agency_file_name + ") nao existe!\n";
        throw(aux_string);
    }
    file_input.close();


    file_input.open(packs_file_name);
    if(!file_input.is_open())
    {
        aux_string = "ERRO: O ficheiro de clientes inserido (" + clients_file_name + ") nao existe!\n";
        throw(aux_string);
    }
    file_input.close();

    std::vector <Cliente> lista_clientes;
    std::vector <PactoteTuristico> lista_pacotes;

    try
    {
        read_clients_file(clients_file_name, lista_clientes);
    }
    catch(const char e[20])
    {
        std::cout << e << '\n' << "Por favor verifique a formatacao do ficheiro de clientes e tente de novo\n";
    }

    try
    {
        read_pacotesturisticos_file(packs_file_name, lista_pacotes);
    }
    catch(const char e[20])
    {
        std::cout << e << '\n' << "Por favor verifique a formatacao do ficheiro de pacotes turisticos e tente de novo\n";
    }

    // if no exceptions, all of the file names are correct and there aren't any input errors.
    agencia.name = name; agencia.url = url; agencia.nif = nif; agencia.morada = morada;
    agencia.lista_clientes = lista_clientes; agencia.lista_pacotes_turisticos = lista_pacotes;
}
