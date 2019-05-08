#include "write.h"

/*Finds index of a client with a given name in a <Cliente> vector. Returns -1 if no client has the given name.
@param nome: Name of the client to search
@param lista_clientes: Vector to search
@param i: The index of the client in the vector. Returns -1 if there is no client with the given name.*/
int find_index(const std::string nome, const std::vector<Cliente> &lista_clientes)
{
    for(int i=0;i<lista_clientes.size();i++)
        if(lista_clientes[i].nome == nome)
            return(i);
    
    return(-1);
}
/*Finds index of a package with a given ID in a <PactoteTuristico> vector. Returns -1 if no package has the given ID.
@param ID: ID of the package to search.
@param lista_pacotes: Vector to search.
@param i: The index of the package in the vector. Returns -1 if there is no package with the given ID.*/
int find_index(const int id, const std::vector<PactoteTuristico> &lista_pacotes)
{
    for(int i=0;i<lista_pacotes.size();i++)
    if((lista_pacotes[i].id == id) || (lista_pacotes[i].id == -id))  // check for the absolute value because the package can be unavailable
        return(i);
    
    return(-1);
}
/*Finds index of a package with a given ID in a <int> vector. Returns -1 if no package has the given ID.
@param ID: ID of the package to search.
@param lista_pacotes_adquiridos: Vector to search.
@param i: The index of the package in the vector. Returns -1 if there is no package with the given ID.*/
int find_index(const int id, const std::vector<int> &lista_pacotes_adquiridos)
{
    for(int i=0;i<lista_pacotes_adquiridos.size();i++)
    if((lista_pacotes_adquiridos[i] == id)|| (lista_pacotes_adquiridos[i] == -id))
        return(i);

    return(-1);
}


/*Returns true if data1 is before data2. Returns false if data2 is after data1.*/
bool is_before(const Data data1, const Data data2)
{
    if(data1.ano < data2.ano)
        return true;
    else
    {
        if(data1.ano == data2.ano)
        {
            if(data1.mes < data2.mes)
                return true;
            else
            {
                if((data1.mes == data2.mes) && (data1.dia < data2.dia))
                    return true;
            }
        }
    }

    return false;
}





/*Forces the user to enter a valid client name. Returns the index of the client with the name given by the user.
@param lista_clientes: Vector used to see if the given name exists.
@param result: The index of the client with the name given by the user. Returns -1 if the user opted-out*/
int select_id(const std::vector<Cliente> &lista_clientes)
{
    bool sucess=false;
    std::string name;
    int id = -1;
    std::cout << "Insira o nome do cliente.\n";

    while((!sucess)&(name != "-1"))
    {
        std::cout << "Para sair digite -1\n";
        getline(std::cin, name);
        id = find_index(name, lista_clientes);

        if(id != -1)
            sucess = true;
         else 
            {
            // sucess = false; not needed because sucess if by default set to false
            if(name != "-1")
                std::cout << "Nenhum cliente possui esse nome. Por favor tente novamente.\n";
        }
    }

    return id;
}
/*Forces the user to enter a valid client ID. Returns the index of the package with the ID given by the user.
@param lista_pacotes: Vector used to see if the given name exists.
@param result: The index of the package with the ID given by the user. Returns -1 if the user opted-out*/
int select_id(const std::vector<PactoteTuristico> &lista_pacotes)
{
    bool sucess=false;
    int index_of_packet;
    int id_in_vector=-1;

    while((!sucess)&(index_of_packet != -2000))
    {
        std::cout << "Insira o ID do pacote.\nDigite -2000 para sair\n";
        std::cin >> index_of_packet;
        if(std::cin.fail())
        {
            std::cout << "Por favor insira um inteiro válido\n";
            std::cin.clear(); std::cin.ignore(1000, '\n');
            continue; // re-iterates loop
        }

        id_in_vector = find_index(index_of_packet, lista_pacotes);

        if(id_in_vector != -1) // if found, sucess!
            sucess = true;
        else
        {
            // sucess = false; not needed because sucess if by default set to false
             std::cout << "Nenhum pacote possui esse id. Por favor tente novamente.\n";
        } 
    }

    return(id_in_vector);
    
}


/* Makes changes to a client.*/
void change(std::vector<Cliente> &lista_clientes)
{
    bool sucess=false;

    int id = select_id(lista_clientes);
    if(id == -1)
        return; //user opted out

    while(!sucess)
    {
        try
        {
            read_client(lista_clientes[id], std::cin);  // change the given client. The input is given by the user (cin).
            sucess=true;  // program flow doesn't go here if something goes wrong when reading new client info
        }
        catch(const char error_message[30])  // Bad user input when reading new client
        {
            std::cout << error_message << '\n';
            bool bad_input = false;
            do
            {
                std::cout << "Deseja tentar novamente (Y/N)\n";
                char c;
                scanf("%c", &c);
                std::cout << c;
                bad_input = false;
                if((c == 'Y')||(c == 'y'))
                {
                    std::cin.ignore(); // clears '\n' from cin so that it doesnt conflict with getline of name in read_pack() 
                    continue;
                }else
                {
                    if((c == 'N')||(c == 'n'))
                    {
                        return;
                    }
                    else
                    {
                        bad_input = true; // user didn't type neither Y nor N
                    }   
                    std::cout << '\n';
                }
            } while (bad_input);    
        }
    }
}
/* Makes changes to a package.*/
void change(std::vector<PactoteTuristico> &lista_pacotes)
{
    bool sucess = false;
    int id = select_id(lista_pacotes);
    if(id == -1)
        return; //user opted out

    while(!sucess)
    {
        try
        {
            //std::istringstream test;
            //test.str("-2\n5\n1/1/1\n2/2/2\n120\n54\n10\n"); used to make debugging easier
            read_pack(lista_pacotes[id], std::cin);
            sucess=true;  // program flow doesn't go here if something goes wrong when reading new pack info
        }
        catch(const char error_message[30])  // Bad user input when reading new pack
        {
            std::cout << error_message << '\n';
            bool bad_input = false;
            do
            {
                std::cout << "Deseja tentar novamente? (Y/N)\n";
                //std::cin.clear(); std::cin.ignore(1000, '\n');
                char c;
                std::cin >> c;
                bad_input = false;
                if((c == 'Y')||(c == 'y'))
                {
                    continue;
                }else
                {
                    if((c == 'N')||(c == 'n'))
                    {
                        return;
                    }
                    else
                    {
                        bad_input = true; // user didn't type neither Y nor N
                    }   
                    std::cout << '\n';
                }
            } while (bad_input);    
        }
    }

}


/* Adds a new client to a given <Cliente> vector.
@param lista_clientes: vector in which the new client is inserted*/
void create(std::vector<Cliente> &lista_clientes)
{
    Cliente *cliente = new Cliente;
    read_client((*cliente), std::cin);
    if(find_index((*cliente).nome, lista_clientes) == -1)  // if client doesn't already exist
        lista_clientes.push_back((*cliente));
    else
        throw(std::string("JA EXISTE UM CLIENTE COM ESSE NOME!\n"));
}
/* Adds a new package to a given <PactoteTuristico> vector.
@param lista_pacotes: vector in which the new package is inserted*/
void create(std::vector<PactoteTuristico> &lista_pacotes)
{
    PactoteTuristico *pacote = new PactoteTuristico;
    read_pack((*pacote), std::cin);
    if(find_index((*pacote).id, lista_pacotes) == -1)
        lista_pacotes.push_back((*pacote));
    else
        throw(std::string("JA EXISTE UM PACOTE COM ESSE ID!\n"));
}

/*Deletes a client from the vector lista_clientes*/
void del(std::vector<Cliente> &lista_clientes)
{
    int id = select_id(lista_clientes);  // Gets the index
    if(id == -1)
        return; // User opted out
    lista_clientes.erase(lista_clientes.begin() + id); // Deletes the client. Thanks to stack overflow for this one
}
/*Deletes a package from the vector lista_pacotes*/
void del(std::vector<PactoteTuristico> &lista_pacotes)
{
    int id = select_id(lista_pacotes);  // Gets the index
    if(id == -1)
        return; // User opted out
    lista_pacotes.erase(lista_pacotes.begin() + id); // deletes the package
}

/*Adds a packet to a client
@param pacotes_turisticos_adquiridos: vector (of client) where the package id will be added
@param lista_pacotes: vector of all the packages (to check if the package that will be inserted exists and to increase the purchase of said packet)*/
void client_add_pack(std::vector<int> &pacotes_turisticos_adquiridos, std::vector<PactoteTuristico> &lista_pacotes)
{
    bool sucess = false;
    int index_of_packet = 0;

    while((!sucess)&(index_of_packet != -2000))
    {
        std::cout << "ID of packet to add?\nType -2000 to abort\n";
        std::cin >> index_of_packet;
        if(std::cin.fail())
        {
            std::cout << "Please write a valid integer\n";
            std::cin.clear(); std::cin.ignore(1000, '\n');
            continue; // re-iterates loop
        }

        if(index_of_packet < 0)  // if the packet id < 0 means that it is unavailable
        {
            std::cout << "That packet is full!\n";
            continue;
        }

        int index_in_vector_client = find_index(index_of_packet, pacotes_turisticos_adquiridos);  // index in vector stored in clients
        if(index_in_vector_client == -1) // if id wasn't already bought by the client, sucess!
        {
            pacotes_turisticos_adquiridos.push_back(index_of_packet);  // id is added to the purchased packages vector of the client
            int index_in_vector_packet = find_index(index_of_packet, lista_pacotes);  // gets index of the package that was in the vector packet
            lista_pacotes[index_in_vector_packet].num_lugares_vendidos++;  // adds a purchase to the package
            verify_overbooking(lista_pacotes[index_in_vector_packet]);  // sees if that new purchase made the package full
            sucess = true;

        }
        else
        {
            // sucess = false; not needed because sucess if by default set to false
             std::cout << "That client already purchased that packet!\n";
        } 
    }
}
