#include "print.h"

void main_menu();


/*Forces the user to type an integer. @param result : The number that the user typed*/
int select_option()
{
    bool sucess = 0;
    int num;
    while(!sucess)
    {
        if(std::cin >> num)
        {
            if(std::cin.peek() == '.') // ver se o prox char na stream é um . (foi digitado float, a parte inteira foi para num)
            {
                continue;
            }
            // Sucess!
            sucess = 1;
        }
        else // (char, cin << x failed)
        {
            std::cout << "Por favor insira um inteiro valido!\n";
            std::cin.clear();
            std::cin.ignore(1000, '\n');
        }
    }

    return(num);
}

void manage_clients(std::vector <Cliente> &lista_clientes, std::vector <PactoteTuristico> &lista_pacotes)
{
    int option = 0;
    do
    {
        clear_screen();
        printf("Selecione uma opcao para gestao de clientes:\n\n");
        printf("1. Criar um novo cliente\n");
        printf("2. Modificar um cliente existente\n");
        printf("3. Eliminar um cliente\n");
        printf("4. Efetuar a compra de pacote turistico por um cliente\n");
        printf("0. Menu principal\n");

        option = select_option();
        clear_screen();

        std::cin.clear(); std::cin.ignore(1000, '\n');
        switch (option)
        {
            case 1:
            {
                try
                {
                    create(lista_clientes);  // creates new client

                    /*The program doesn't check for invalid package that have been purchased, and if a new client has purchased a package that
                    is full, there will be no exception and the total profit will take into account the new client
                      To fix this an easy solution would be to add to the read function a new parameter that would be the package list
                    and check if any of the purchased packages is already overbooked with the is_overbooked function, and throw an exception
                    from there. A verification check for packages purchased by the clients that are invalid (aren't registed in the program)
                    could also be easily implemented with the find_id function,
                      This wasn't done due to time restrictions and because it was simply too overkill in my opinion.*/
                }
                catch(const std::string e)
                {
                    std::cout << e << '\n';
                }

                break;
            }

            case 2:
            {
                try
                {
                    change(lista_clientes);  // changes an existing client
                }
                catch(const std::string e)
                {
                    std::cout << e << '\n';
                }

                break;
            }

            case 3:
            {
                try
                {
                    del(lista_clientes);  // deletes an existing client
                }
                catch(const std::string e)
                {
                    std::cout << e << '\n';
                }

                break;
            }

            case 4:
            {
                int cliente_index = select_id(lista_clientes);
                if(cliente_index != -1)
                {
                    int packet_id = select_id(lista_pacotes);
                    std::cin.ignore();
                    if((packet_id != -1))
                        if(find_index(lista_pacotes[packet_id].id, lista_clientes[cliente_index].pacotes_turisticos_adquiridos) == -1)  
                        // if packet isn't already purchased
                            lista_clientes[cliente_index].pacotes_turisticos_adquiridos.push_back(lista_pacotes[packet_id].id);
                        else
                            std::cout << "Esse pacote ja foi adquirido.\n";
                }
                break;
            }

            case 0:
            {
                break;
            }
        }

        std::cout << "\n\nPressione qualquer tecla para sair\n";
        std::getchar();
    } while (option != 0);  // goes to main menu when user types 0
}


void manage_packs(std::vector <PactoteTuristico> &lista_pacotes)
{
    int option = 0;
    do
    {
        clear_screen();
        printf("Selecione uma opcao para gestao de clientes:\n\n");
        printf("1. Criar um novo pacote\n");
        printf("2. Modificar um pacote existente\n");
        printf("3. Eliminar um pacote\n");
        printf("0. Menu principal\n");

        option = select_option();
        clear_screen();

        std::cin.clear(); std::cin.ignore(1000, '\n');
        switch (option)
        {
            case 1:
            {
                try
                {
                    create(lista_pacotes);  // creates a new package
                }
                catch(const std::string e)
                {
                    std::cout << e << '\n';
                    std::cin.ignore();
                }

                break;
            }

            case 2:
            {
                try
                {
                    change(lista_pacotes);  // changes an existing package
                }
                catch(const std::string e)
                {
                    std::cout << e << '\n';
                }

                break;
            }

            case 3:
            {
                try
                {
                    del(lista_pacotes);  // deletes an existing package
                }
                catch(const std::string e)
                {
                    std::cout << e << '\n';
                }

                break;
            }

            case 0:
            {
                break;
            }
        }

        std::cout << "\n\nPressione qualquer tecla para sair\n";
        std::getchar();
    } while (option != 0);  // goes to main menu when user types 0
}

void menu_visualize_clients(const std::vector<Cliente> &lista_clientes)
{
    int option = 0;
    do
    {
        clear_screen();
        printf("Selecione uma opcao para visualizacao de clientes:\n\n");
        printf("1. Visualizar um cliente em especifico\n");
        printf("2. Visualizar todos os clientes\n");
        printf("0. Menu principal\n");

        option = select_option();
        clear_screen();

        switch (option)
        {
            case 1:
            {
                std::cin.clear();std::cin.ignore(1000, '\n');
                int client_index = select_id(lista_clientes);  // gets index in vector of the selected client by the user
                if (client_index != -1)  // if user hasn't opted out
                {
                    clear_screen();
                    print_cliente(lista_clientes[client_index]);
                }
                break;
            }

            case 2:
            {
                std::cin.ignore();
                print_cliente(lista_clientes);
                break;
            }

            case 0:
                break;
        }

        std::cout << "\n\nPressione qualquer tecla para sair\n";
        std::getchar();
    } while (option != 0);  // goes to main menu when user types 0

}

void menu_visualize_packs(const std::vector<PactoteTuristico> &lista_pacotes, const std::vector<Cliente> &lista_clientes)
{
    int option = 0;
    do
    {
        clear_screen();
        printf("Selecione uma opcao para visualizacao de clientes:\n\n");
        printf("1. Visualizar um pacote em especifico\n");
        printf("2. Visualizar todos os pacotes\n");
        printf("3. Visualizar todos os pacotes entre duas datas\n");
        printf("4. Visualizar todos os pacotes relativos a um destino\n");
        printf("5. Visualizar todos os pacotes relativos a um destino e entre duas datas\n");
        printf("6. Visualizar todos os pacotes vendidos a todos os clientes\n");
        printf("7. Visualizar todos os pacotes vendidos a um cliente\n");
        printf("0. Menu principal\n");

        option = select_option();
        clear_screen();

        switch (option)
        {
            case 1:
            {
                int packet_index = select_id(lista_pacotes);  // gets the index of the selected package by the user
                if (packet_index != -1)  // if user didn't opt out
                {
                    clear_screen();
                    print_pacote(lista_pacotes[packet_index]);
                }
                break;
            }

            case 2:
            {
                print_pacote(lista_pacotes);
                break;
            }

            case 3:
            {
                bool sucess = 0;
                std::string data_inicio, data_fim;
                do
                {
                    try
                    {
                        std::cout << "Insira a data de inicio\n"; std::cin >> data_inicio;
                        std::cout << "Insira a data de fim\n"; std::cin >> data_fim;
                        print_pacote(lista_pacotes, data_inicio, data_fim);  //FIXME: SOLVE 1/1/1 3000/3/3
                        sucess = 1; // if no exception then print was successfull
                    }
                    catch(const std::string e)
                    {
                        clear_screen();
                        std::cout << e << "\n\n";
                    }

                    std::cin.clear(); std::cin.ignore(1000, '\n');
                } while (!sucess);
                break;
            }

            case 4:
            {
                bool sucess = 0;
                std::string destino;
                do
                {
                    try
                    {
                        std::cout << "Insira o destino\n"; std::cin >> destino;
                        print_pacote(lista_pacotes, destino);
                        sucess = 1; // if no exception then print was successfull
                    }
                    catch(const std::string e)
                    {
                        clear_screen();
                        std::cout << e << '\n';
                    }
                } while (!sucess);
                break;
            }

            case 5:
            {
                bool sucess = 0;
                std::string data_inicio, data_fim, destino;
                do
                {
                    try
                    {
                        std::cout << "Insira a data de inicio\n"; std::cin >> data_inicio;
                        std::cout << "Insira a data de fim\n"; std::cin >> data_fim;
                        std::cout << "Insira o destino\n"; std::cin >> destino;
                        print_pacote(lista_pacotes, destino, data_inicio, data_fim);
                        sucess = 1; // if no exception then print was successfull
                    }
                    catch(const std::string e)
                    {
                        clear_screen();
                        std::cout << e << '\n';
                    }

                } while (!sucess);
                break;
            }

            case 6:
            {
                print_pacote(lista_pacotes, lista_clientes);
                break;
            }

            case 7:
            {
                std::cin.clear(); std::cin.ignore(1000, '\n');
                int cliente_index = select_id(lista_clientes);  // gets the index in vector of the client selected by the user
                if(cliente_index != -1)
                {
                    clear_screen();
                    print_pacote(lista_pacotes, lista_clientes[cliente_index].pacotes_turisticos_adquiridos);
                }
                break;
            }

            case 0:
                break;
        }

        std::cin.ignore();
        std::cout << "\n\nPressione qualquer tecla para sair\n";
        std::getchar();
    } while (option != 0);  // goes to main menu when user types 0
}

void main_menu()
{
    int option;
    Agencia agencia;

    do
    {
        clear_screen();
        printf("Selecione uma opcao:\n\n");
        printf("1. Ler informacao de ficheiro\n");
        printf("2. Guardar informacao em ficheiro\n");
        printf("3. Gerir clientes\n");
        printf("4. Gerir pacotes\n");
        printf("5. Visualizar a informacao de clientes\n");
        printf("6. Visualizar a informacao pacotes\n");
        printf("7. Visualizar o numero e o valor total de pacotes vendidos\n");
        printf("0. Sair\n");

        option = select_option();
        clear_screen();

        switch (option)
        {
            case 1:
            {
                try
                {
                    std::cout << "Ler um novo ficheiro de agencia fara com que todos os dados nao guardados serao perdidos.\n";
                    read_agency_file(agencia);
                }
                catch(const std::string e)
                {
                    clear_screen();
                    std::cout << "ERRO NO FICHEIRO\n";
                    std::cout << e << '\n';
                }

                std::cout << "\n\nPressione qualquer tecla para sair\n";
                std::cin.clear();std::cin.ignore(1000, '\n');
                std::getchar();
                break;
            }

            case 2:
            {
                try
                {
                    save_files(agencia);
                }
                catch(std::string e)
                {
                    std::cout << e << '\n';
                }

                std::cout << "\n\nPressione qualquer tecla para sair\n";
                std::cin.clear();std::cin.ignore(1000, '\n');
                std::getchar();
                break;
            }

            case 3:
            {
                manage_clients(agencia.lista_clientes, agencia.lista_pacotes_turisticos);
                break;
            }

            case 4:
            {
                manage_packs(agencia.lista_pacotes_turisticos);
                break;
            }

            case 5:
            {
                menu_visualize_clients(agencia.lista_clientes);
                break;
            }

            case 6:
            {
                menu_visualize_packs(agencia.lista_pacotes_turisticos, agencia.lista_clientes);
                break;
            }

            case 7:
            {
                print_total_profit(agencia.lista_pacotes_turisticos);
                std::cin.ignore();std::cin.ignore(); // so that getchar() doesn't catch '\n
                break;
            }

            std::cout << "\n\nPressione qualquer tecla para sair\n";
            std::cin.clear();std::cin.ignore(1000, '\n');
            std::getchar();
        }

    } while (option != 0);
    

}


int main()
{
    main_menu();


    /*TODO: ESTRUTURA DO PROG
        - Antes de close programa, guardar das vars para o mesmo nome do ficheiro
        QD ABRES FICHEIROS PARA ESCRITE ISSO LIMPA FICHEIRO 
            Meaning que se tiveres a escrever e programa crashar, perdes ambos dados
             (as vars e o que ja estava no fiheiro)
        FIXME: Guardar em um ficheiro diferente temporario e dps mudar de nome para fich original.
    */
    return 0;
}