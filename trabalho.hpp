#ifndef LISTAS_H
#define LISTAS_H

#define Max_Tam 5

using namespace std;

typedef struct Projetos
{
    // Item
    int codigo;    // codigo do projeto
    char nome[20]; // nome do funcionario
    int horas;     // horas trabalhadas
};

typedef struct ListaDeProjetos
{
    // ponteiros para os projetos
    Projetos projetos[Max_Tam]; // Inclui os projetos
    int primeiro;               // primeiro da lista
    int ultimo;
};

typedef struct Endereco
{
    char rua[60];
    char bairro[30];
    char cidade[30];
    char estado[30];
    int numero;
};

typedef struct Funcionario
{
    // celula da lista encadeada
    int id;            // codigo
    char nome[20];     // nome
    int dependentes;   // dependentes
    Endereco endereco; // endereco
    ListaDeProjetos projetos; // projetos
};

typedef struct Elemento *Apontador;

typedef struct Elemento
{ // Aponta para a proxima celula
    Funcionario funcionario;
    struct Elemento *prox;
};

typedef struct ListaDeFuncionarios
{
    // ponteiros para os funcionarios
    Apontador primeiro; // primeira celula
    Apontador ultimo;   // ultima celula
    int tamanho;
};

void Menu();
void CriaListaEncadeadaVazia(ListaDeFuncionarios *lista);//Cria a lista de funcionarios
void CriaListaNormalVazia(ListaDeProjetos *lista);//Cria lista de projetos
bool VerificaListaEncadeadaVazia(ListaDeFuncionarios *lista);//Verifica se a lista de funcionarios esta vazia
bool VerificaListaNormalVazia(ListaDeProjetos *projeto);//Verifica se a lista de projetos esta vazia
void InsereListaEncadeadaUltimo(ListaDeFuncionarios *lista, Funcionario *funcionario);//Insere novo funcionario
bool VerificaListaNormalCheia(ListaDeProjetos *lista);//Verifica se a lista de projetos esta cheia
void InsereListaNormalUltimo(Projetos p, ListaDeProjetos *lista);//Insere novo projeto ao funcionario
int BuscaFuncionario(int codigo, ListaDeFuncionarios lista, Apontador *p);//Procura o funcionario desejado
void CadastraFuncionario(ListaDeFuncionarios *lista);//Faz o cadastro de um novo funcionario
void ImprimeProjetos(ListaDeProjetos lista);//Imprime todos os projetos de um funcionario
void ConsultaFuncionario(ListaDeFuncionarios *lista);//Exibe as informaçoes de determinado funcionario
void CadastraProjeto(ListaDeFuncionarios *lista);//Faz o cadastro de um novo projeto
void RemoveItemPorId(ListaDeFuncionarios *lista, int id);//Remove um item(projeto) usando um id informado
void RemoveFuncionarioSemProjeto(ListaDeFuncionarios *lista);//Remove funcionarios que nao tem nenhum projeto
void ImprimiContraCheque(ListaDeFuncionarios *lista);//Exibe na tela o contracheque de todos os funcionarios
int BuscaProjeto(int codigo, ListaDeProjetos *lista);//Procura o projeto desejado
void RemoveProjeto(ListaDeFuncionarios *lista);//Remove o projeto desejado usando a remove item por id

#endif