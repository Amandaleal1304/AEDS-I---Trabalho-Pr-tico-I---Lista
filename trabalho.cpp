#include <iostream>
#include <string.h>
#include <conio.h>
#include <fstream> //biblioteca para utilizar arquivo

#include "trabalhofunc.cpp" //acessar trabalhofunc.cpp na main

#define Max_Tam 5 //define tamanho maximo dos 
#define Inicio 0 //define inicio como 0

using namespace std;

int main()
{

    ListaDeFuncionarios listaF; // criou um ListaF do tipo ListaDeFuncionarios

    CriaListaEncadeadaVazia(&listaF); // cria uma lista vazia, passando o parametro criado listaF (TipoLista)

    FILE *arquivo; // cria uma variavel do tipo arquivo
    Funcionario func; //acessa os itens existentes na struct do funcionario (TipoItem)
    Apontador ret = listaF.primeiro; // cria um apontador para apontar para o primeiro item da lista
    int op;//variavel para opções no switch

    arquivo = fopen("funcionarios.bin", "rb");//abre o arquivo utilizando a função fopen
                                            //"r"(read): abertura de arquivo para leitura;
                                            //"w"(write): abertura de arquivo para escrita;
                                            //"a"(append): abertura de arquivo para acrescentar;
                                            // Usamos a letra t para configurar o arquivo como texto e a letra b para binário. 
                                            //Assim, rb é o modo de abertura para arquivo binário que permite leitura.
                                            // Analogamente, wb, ab, r+b, w+b e a+b.

    if (arquivo != NULL) //se o arquivo foi aberto, ou seja diferente de nulo
    {
        while (fread(&func, sizeof(Funcionario), 1, arquivo))//utiliza a função fread para retornar o número de itens completos realmente lidos
                                                             // sizeof percorre a lista junto com o while
        {
            InsereListaEncadeadaUltimo(&listaF, &func); // chama a fução para inderir os itens passados no arquivo
        }
        fclose(arquivo);//fechar o arquivo
    }
    else
    {
        cout << "O Arquivo Esta Vazio!\n";// se o arquivo nao for aberto (ELSE)
    }

    do
    {
        Menu();//abre o menu de opções
        cout << "\n\n";//pula duas linhas
        cout << "Escolha uma opcao: ";
        cin >> op; // ler a escolha do usuario

        system("cls");

        switch (op)
        {
        case 1://caso o usuario digitar 1
            CadastraFuncionario(&listaF); //chama a função cadastra funcionario
            break;//Forçar a saída 
        case 2:
            CadastraProjeto(&listaF);//chama a função cadastra projeto
            break;

        case 3:
            RemoveProjeto(&listaF);//chama a função remove projeto
            break;

        case 4:
            RemoveFuncionarioSemProjeto(&listaF);//chama a função remove funcionario sem projeto
            break;

        case 5:
            ConsultaFuncionario(&listaF);//chama a função de consulta de funcionarios
            break;

        case 6:
            ImprimiContraCheque(&listaF);//chama a função imprimi contracheque
        }
        system("pause"); // da uma pausa na tela até o usuario apertar algum comando
        system("cls");//limpa a tela

    } while (op != 7); //fecha

    arquivo = fopen("funcionarios.bin", "wb");//abre o arquivo
                                            // w"(write): abertura de arquivo para escrita;

    while (ret->prox != NULL) // pega o ret que foi definido como listaF.primeiro; e olha se tem itens na lista se tiver entra no while
    {
        func = ret->prox->funcionario;// o func(TipoItem), recebe os dados do funcionario
        fwrite(&func, sizeof(Funcionario), 1, arquivo);//fwrite retorna quantos itens são gravados o sizeof pega o tamanho e grava os dados
        ret = ret->prox;//retorna a lista
    }

    fclose(arquivo);//fecha o arquivo

    cout << endl;//pula uma linha
    return 0;
}
