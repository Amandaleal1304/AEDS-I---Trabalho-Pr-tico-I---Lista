#include <iostream>
#include <windows.h>
#include "trabalho.hpp"

bool ListaCriadaEncadeada = false;//Verifica se a lista de funcionarios foi criada
bool ListaCriadaNormal = false;//Verifica se a lista de projetos foi criada

#define Max_Tam 5//Maximo de projetos que podem ser criados
#define Inicio 0//Onde vai iniciar

void Menu()//Exibe as opcoes de operacoes
{
    cout << "**********************MENU**********************";
    cout << "\n"
         << "* 1- Cadastrar Novo Funcionario                *";
    cout << "\n"
         << "* 2- Cadastrar Novo Projeto                    *";
    cout << "\n"
         << "* 3- Excluir Projeto De Um Funcionario         *";
    cout << "\n"
         << "* 4- Excluir Funcionarios Sem Projeto          *";
    cout << "\n"
         << "* 5- Consultar Funcionario                     *";
    cout << "\n"
         << "* 6- Imprimir Contra-Cheque                    *";
    cout << "\n"
         << "* 7- Sair                                      *";
    cout << "\n"
         << "************************************************";
};

void CriaListaEncadeadaVazia(ListaDeFuncionarios *lista)//Vai criar a celula cabeça( iniciar a lista )
{
    lista->primeiro = new Elemento;
    lista->ultimo = lista->primeiro;
    lista->ultimo->prox = NULL;
    lista->tamanho = 0;
    ListaCriadaEncadeada = true;
};

void CriaListaNormalVazia(ListaDeProjetos *lista)//Vai criar a lista de projetos 
{
    lista->primeiro = 0;
    lista->ultimo = lista->primeiro;
};

bool VerificaListaEncadeadaVazia(ListaDeFuncionarios *lista)//Verifica se a lista de funcionarios esta vazia
{
    if (lista->primeiro == lista->ultimo)
    {
        return true;
    }
    else
    {
        return false;
    }
};

bool VerificaListaNormalVazia(ListaDeProjetos *projeto)//Verifica se a lista de projetos esta vazia(sem nenhum cadastro)
{
    if (projeto->primeiro == projeto->ultimo)
    {
        return true;
    }
    else
    {
        return false;
    }
};

void InsereListaEncadeadaUltimo(ListaDeFuncionarios *lista, Funcionario *funcionario)//Insere um funcionario(celula) depois do ultimo ja inserido
{
    lista->ultimo->prox = new Elemento;
    lista->ultimo = lista->ultimo->prox;
    lista->ultimo->prox = NULL;
    lista->ultimo->funcionario = *funcionario;
    lista->tamanho++;
    // vai receber o que esta apontado em funcionario
};

bool VerificaListaNormalCheia(ListaDeProjetos *lista)//Verifica se a lista de projetos ja tem o maximo de projetos cadastrados
{
    if (lista->ultimo == Max_Tam)
    {
        return true;
    }
    else
    {
        return false;
    };
}

void InsereListaNormalUltimo(Projetos p, ListaDeProjetos *lista)//Insere um novo projeto depois do ultimo criado
{
    if (lista->ultimo == Max_Tam)
    {
        cout << "Lista Cheia!\n";
    }
    else
    {
        lista->projetos[lista->ultimo] = p; // armazena os projetos do funcionario
        lista->ultimo++;                    // incrementacao dos projetos
    }
};

// retorna em "p" o funcionario encontrado e retorna em "ret" um inteiro para verificar se achou um funcionario ou não
int BuscaFuncionario(int codigo, ListaDeFuncionarios lista, Apontador *p)
{
    Apontador aux = lista.primeiro;

    while (aux->prox != NULL)
    {
        if (aux->prox->funcionario.id == codigo)
        {
            *p = aux;
            return 1;
        }
        else
        {
            aux = aux->prox;
        }
    }
    return 0;
}

void CadastraFuncionario(ListaDeFuncionarios *lista)//Vai pedir as informaçoes e salvar de um funcionario
{
    // cria um novo funcionario e preenche as informações
    Funcionario func;
    Apontador ret = lista->primeiro;

    cout << "\tCadastro De Funcionario\t";
    cout << "\n\n";
    cout << "Codigo: ";
    cin >> func.id;
    cout << "\n";

    while (ret->prox != NULL)
    {
        if (ret->prox->funcionario.id == func.id)
        {
            cout << "Esse codigo ja existe!";
            cout << "\nInforme outro codigo:";
            cin >> func.id;
            ret = lista->primeiro;
        }
        else
        {
            ret = ret->prox;
        }
    }
    cin.ignore();//Usado para nao dar erro no getline a baixo
    cout << "Nome: ";
    cin.getline(func.nome, 60);//Usado para juntar os caracteres digitados

    cout << "\n"
         << "Endereco "
         << "\n";
    cout << "Estado: ";
    cin.getline(func.endereco.estado, 30);
    cout << "\n"
         << "Cidade: ";
    cin.getline(func.endereco.cidade, 30);
    cout << "\n"
         << "Bairro: ";
    cin.getline(func.endereco.bairro, 30);
    cout << "\n"
         << "Rua: ";
    cin.getline(func.endereco.rua, 60);
    cout << "\n"
         << "Numero: ";
    cin >> func.endereco.numero;
    while ((cout << "\n"
                 << "Dependentes: ") &&
           !(cin >> func.dependentes))
    {
        cout << "Erro! Informe um valor numerico.\n"; // Exibe mensagem em caso de divergência encontrada
        cin.clear();                                  // Apaga o sinalizador de erro cin para que futuras operações funcionem corretamente
        cin.ignore();                                 // Pula para a próxima linha ignorando caracteres para o buffer de entrada
    }

    
    ListaDeProjetos projetos;        
    CriaListaNormalVazia(&projetos); // cria uma lista de projetos vazia e insere ela em funcionario
    func.projetos = projetos;        

    InsereListaEncadeadaUltimo(lista, &func); // insere o funcionario na lista de funcionarios

    cout << "\n"
         << "Funcionario cadastrado com sucesso!";
    system("cls");
}

void ImprimeProjetos(ListaDeProjetos lista)//Vai imprimir os projetos buscados por codigo do funcionario
{
    for (int i = 0; i < lista.ultimo; i++)
    {
        cout << "\n"
             << "Codigo do projeto: " << lista.projetos[i].codigo;
        cout << "\n"
             << "Nome: " << lista.projetos[i].nome;
        cout << "\n"
             << "Horas Trabalhadas: " << lista.projetos[i].horas;
        cout << "\n";
    }
}

void ConsultaFuncionario(ListaDeFuncionarios *lista)//Vai buscar e exibir as informacoes cadastradas de um funcionario
{
    int codigo;
    //auxiliares
    Apontador p;
    int ret;

    cout << "\tConsulta De Funcionario\t"
         << "\n\n";
    cout << "Digite o codigo do funcionario: ";
    cin >> codigo;
    cout << "\n\n";

    ret = BuscaFuncionario(codigo, *lista, &p);//Busca o funcionario por id

    if (ret == 1)
    {
        //Pede as informacoes necessarias e salva
        cout << "Codigo: " << p->prox->funcionario.id << "\n";
        cout << "Nome: " << p->prox->funcionario.nome << "\n";
        cout << "Endereco";
        cout << "Cidade: " << p->prox->funcionario.endereco.cidade << "\n";
        cout << "Estado: " << p->prox->funcionario.endereco.estado << "\n";
        cout << "Bairro: " << p->prox->funcionario.endereco.bairro << "\n";
        cout << "Rua: " << p->prox->funcionario.endereco.rua << "\n";
        cout << "Numero: " << p->prox->funcionario.endereco.numero << "\n\n";

        cout << "Projetos: "
             << "\n";

        ImprimeProjetos(p->prox->funcionario.projetos);
    }
    else
    {
        cout << "Funcionario nao existe!";
    }
}

void CadastraProjeto(ListaDeFuncionarios *lista)
{
    Projetos proj;
    Apontador p;
    int codigo;
    int ret;
//Busca o funcionario e insere um novo projeto para ele
    cout << "\n"
         << "Digite o codigo do funcionario: ";
    cin >> codigo;

    ret = BuscaFuncionario(codigo, *lista, &p);

    if (ret == 1)
    {
        cout << "\tCadastro De Projetos\t";
        cout << "\nCodigo: ";
        cin >> proj.codigo;
        cin.ignore();
        cout << "\nNome do projeto: ";
        cin.getline(proj.nome, 30);
        cout << "\nNumero de Horas Semanais: ";
        cin >> proj.horas;

        if (VerificaListaNormalCheia(&p->prox->funcionario.projetos))
        {
            cout << "\nNumero maximo de projetos cadastrados!";
        }
        else
        {
            p->prox->funcionario.projetos.projetos[p->prox->funcionario.projetos.ultimo] = proj;
            p->prox->funcionario.projetos.ultimo++;
        }
    }
    else
    {
        cout << "Funcionario nao existe!";
    }
}

void RemoveItemPorId(ListaDeFuncionarios *lista, int id)
{
    if (VerificaListaEncadeadaVazia(lista))
    {
        cout << "\n"
             << "Lista Vazia!";
        return;
    }

    Apontador aux, anterior, x;

    x = lista->primeiro;

    // percorre a lista procurando o funcionario com o ID recebido
    while (x != NULL)
    {
        if (x->prox->funcionario.id == id)
        {
            anterior = x;
            break;
        }
        x = x->prox;
    }
    aux = anterior->prox;
    anterior->prox = aux->prox;
    delete aux;
    lista->tamanho--;
}

void RemoveFuncionarioSemProjeto(ListaDeFuncionarios *lista)
{
    Funcionario func;
    Apontador a = lista->primeiro->prox;
    int cont = 0;

    while (a != NULL)
    {
        // Passa por todos os funcionarios verificando se o ultimo projeto é o 0
        // que significa que o funcionario não tem projetos cadastrados
        if (a->funcionario.projetos.ultimo == 0)
        {
            RemoveItemPorId(lista, a->funcionario.id);
            cont++; // conta quantos funcionarios foram excluidos
        }
        a = a->prox;
    }

    cout << "\n"
         << cont << " Funcionario(s) excluido(s) com sucesso!";
    system("pause");
    system("cls");
}

void ImprimiContraCheque(ListaDeFuncionarios *lista)
{
    Apontador aux = lista->primeiro->prox;
    int HSemanais = 0;
    float SBruto = 0, SLiquido = 0, INSS = 0, IR = 0;

    cout << "\t Contra-Cheque \t"
         << "\n\n";

    while (aux != NULL)
    {
        // Verifica as horas semanais totais do funcionario 
        for (int i = 0; i < aux->funcionario.projetos.ultimo; i++)
        {
            HSemanais += aux->funcionario.projetos.projetos[i].horas;
        }

        SBruto = (HSemanais * 45) + (35 * aux->funcionario.dependentes);
        INSS = SBruto * 0.085;
        IR = SBruto * 0.15;
        SLiquido = SBruto - (INSS + IR);

        //Imprimi o contra cheque de cada funcionario cadastrado

        cout << "\n"
             << "Codigo: " << aux->funcionario.id;
        cout << "\n"
             << "Nome: " << aux->funcionario.nome;
        cout << "\n"
             << "Horas Trabalhadas Totais: " << HSemanais;
        cout << "\n"
             << "Salario Bruto: " << SBruto;
        cout << "\n"
             << "Desconto INSS: " << INSS;
        cout << "\n"
             << "Desconto Imposto de Renda(IR): " << IR;
        cout << "\n"
             << "Salario Liquido: " << SLiquido;
        cout << "\n";

        SBruto = 0;
        SLiquido = 0;
        INSS = 0;
        IR = 0;
        aux = aux->prox;
    }
}

int BuscaProjeto(int codigo, ListaDeProjetos *lista)//BUsca os projetos de acordo com o id informado
{

    for (int i = 0; i < lista->ultimo; i++)
    {
        if (codigo == lista->projetos[i].codigo)
        {
            return i;
        }
    }
    return -1;
}

void RemoveProjeto(ListaDeFuncionarios *lista)
{
    int codigo, posicao;
    Apontador p;
    int ret;

    cout << "Informe o codigo do funcionario que deseja excluir projetos: ";
    cin >> codigo;

    
    ret = BuscaFuncionario(codigo, *lista, &p);
    //BUsca o funconario e pergunta qual projeto dele deseja remover

    if (ret == 1)
    {

        ImprimeProjetos(p->prox->funcionario.projetos);
        cout << "Informe o codigo do projeto que deseja exluir: ";
        cin >> codigo;

        // retorna em "posicao" o indice que o projeto foi encontrado
        // retorna -1 se nenhum projeto foi encontrado
        posicao = BuscaProjeto(codigo, &p->prox->funcionario.projetos);
        
        if (posicao != -1)
        {
            // remove o projeto descendo todos os outros acima em uma posição
            for (int i = posicao; i < p->prox->funcionario.projetos.ultimo; i++)
            {
                p->prox->funcionario.projetos.projetos[i] = p->prox->funcionario.projetos.projetos[i + 1];
            }
            p->prox->funcionario.projetos.ultimo--;

            cout << "\n"
                 << "Projeto Excluido com sucesso!\n";
            return;
        } 
        else 
        {
            cout << "O projeto selecionado nao esta na lista!\n";
        }    
    }
    else
    {
        cout << "Funcionario nao existe!\n";
    }
}