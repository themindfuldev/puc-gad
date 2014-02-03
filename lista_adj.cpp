/*============================================================================*/
/* OBJETIVO: Representacao de grafo atraves de uma Lista de Adjacencias
*/
//==============================================================================
//                       DECLARAÇÃO DE BIBLIOTECAS
//==============================================================================
#include<stdlib.h>                                                  // Rotinas de Biblioteca-Padrao usado para exit()
#include<fstream> using namespace std;                                                 // Abrir/Fechar arquivos, inclui Biblioteca iostream
#include<iostream> using namespace std;                                                // cout no C++ Builder 6
#include<conio.h>                                                   // Para getch()
#define arq "Grafos.txt"                                            // Definicao do nome do arquivo de informacoes do grafo
#include"fila.cpp";                                                 // onde está declarada a classe de implementação da fila
//---------------------------------------------------------------------------
;
/*============================================================================*/
/*                     DEFINIÇÃO / DECLARAÇÃO DE ESTRUTURA - S_ARESTA         */
/*============================================================================*/
typedef struct S_Aresta *Apont_s_aresta;
typedef struct S_Aresta
{
  int vertice, peso;
  S_Aresta *prox;
} Aresta;
/*============================================================================*/
/*                      DECLARAÇÃO DE ESTRUTURA - S_VETOR                     */
/*============================================================================*/
struct S_Vetor
{
  int vertice;
  int grau;
  S_Aresta *aresta, *ultimo;
};
/*============================================================================*/
/*      CLASSE GRAFO - C_GRAFO: Armazena e Pesquisa daos de um grafo          */
/*                              (vertices, arestas, grau, caminho             */
/*============================================================================*/
class C_Grafo
{
  private:
    int vertices;                                                   // Número de vertices do grafo
    S_Vetor *grafo;                                                 // Lista de adjacência do grafo
  public:
    C_Grafo();                                                      // Construtor da classe
    ~C_Grafo();                                                     // Destrutor da classe
    void insere_aresta(int v1, int v2, int p);                      // Procedimento para inserir aresta no grafo
    bool pesquisa_aresta(int v1, int v2);                           // Função para pesquisa de aresta
    bool pesquisa_vertice(int v1);                                  // Função para pesquisa de vértice
    int  informa_grau(int v1);                                      // Função para retornar o grau do vertice
    int  informa_vertice();                                         // Procedimento para retornar o número de vertices do grafo
    void carrega_arquivo();                                         // Procedimento para carregar um arquivo com as informações do grafo
    bool busca_extensao(int v1, int v2);                            // Pesquisa no gravo da diatancia de v1 a v2 utilizando o método da busca em profundidade
    void imprime_lista();                                           // Imprime lista de adjacencia completa
    void imprime_lista_v(int v);                                    // Imprime lista de adjacencia de um vértice
};
   /*============================================================
    Funcao: C_Grafo: Construtor_ Aloca memoria inicial conforme
                     valor obtido atraves de leitura da 1º linha
                     do arquivo texto. A 1ª linha informa qual a
					 quantidade de vertíces que o grafo terá. E
					 baseado nesta informação será criado um 
					 vetor com o valor informado e com a estru-
					 tura necessária 
   ============================================================*/
C_Grafo::C_Grafo()
{
   int i;

   ifstream fin(arq);
   fin >> i;
   grafo = new S_Vetor[i];
   for (int j = 0; j < i; j++)
   {
      grafo[j].grau = 0;
      grafo[j].vertice=j+1;
      grafo[j].aresta= (Apont_s_aresta) malloc(sizeof(Aresta));
      grafo[j].ultimo= grafo[j].aresta;
   }
   vertices = i;
   fin.close();
}
   /*============================================================
    Funcao: ~C_Grafo: Destrutor_ Desaloca memoria
   ============================================================*/
C_Grafo::~C_Grafo()
{
   delete grafo;
}
   /*============================================================
    Procedimento: insere_aresta: Identifica aresta do grafo
    Parametros  : v1: 1º vertice lido
                  v2: 2º vertice lido
   ============================================================*/
void C_Grafo::insere_aresta(int v1, int v2, int p)
{
  if (!(pesquisa_vertice(v1)) || !(pesquisa_vertice(v2)))
  {
     cout << "\n\nProblemas com a aresta " << v1 << " a " << v2 << ". Verifique o arquivo carregado.";
  }
  else
  {
     grafo[v1 - 1].ultimo->prox= (Apont_s_aresta) malloc(sizeof(Aresta));
     grafo[v2 - 1].ultimo->prox= (Apont_s_aresta) malloc(sizeof(Aresta));
     grafo[v1 - 1].ultimo = grafo[v1 - 1].ultimo->prox;
     grafo[v2 - 1].ultimo = grafo[v2 - 1].ultimo->prox;
     grafo[v1 - 1].ultimo->vertice= v2;
     grafo[v2 - 1].ultimo->vertice= v1;
     grafo[v1 - 1].ultimo->peso= p;
     grafo[v2 - 1].ultimo->peso= p;
     grafo[v1 - 1].ultimo->prox= NULL;
     grafo[v2 - 1].ultimo->prox= NULL;
     grafo[v1 - 1].grau++;
     grafo[v2 - 1].grau++;
  }
}
   /*============================================================
    Funcao    : pesquisa_aresta
    Parametros: v1: 1º vertice informado
                v2: 2º vertice informado
    Retorno   : true : aresta existe
                false: aresta inexistente
   ============================================================*/
bool C_Grafo::pesquisa_aresta(int v1, int v2)
{
  S_Aresta *apont;
  apont= grafo[v1 - 1].aresta->prox;
  while (!(apont == NULL))
  {
     if (apont->vertice == v2)
        return true;
     apont = apont->prox;
  }
  return false;
}
   /*============================================================
    Funcao    : pesquisa_vertice
    Parametros: v1: 1º vertice informado
    Retorno   : true : vértice existe
                false: vértice inexistente
   ============================================================*/
bool C_Grafo::pesquisa_vertice(int v1)
{
  if (v1 > vertices)
     return false;
  return true;
}
   /*============================================================
    Funcao    : informa_grau
    Parametros: v1: vertice informado
    Retorno   : grau[v1-1]: grau do vertice
   ============================================================*/
int C_Grafo::informa_grau(int v1)
{
   return grafo[v1 - 1].grau;
}
   /*============================================================
    Procedimento: carrega_arquivo: Le arquivo de informacoes
                                   para construcao do grafo
   ============================================================*/
void C_Grafo::carrega_arquivo()
{
   char ch[20];
   int v1, v2, p; //v1- vertice 1 / v2- vertice 2 / p- peso da aresta
   ifstream arquivo(arq);
   arquivo.getline(ch, 20);
   arquivo >> v1;
   while (!arquivo.eof())
   {
      arquivo >> v2;
      arquivo >> p;
      insere_aresta( v1, v2, p);
      arquivo >> v1;
   }
}
   /*============================================================
    Funcao    : informa_vertice
    Retorno   : número de vértices do grafo
   ============================================================*/
int C_Grafo::informa_vertice()
{
  return vertices;
}
   /*============================================================
    Procedimento: Busca na extensão
    Retorno     : faz a busca em profundidade de
   ============================================================*/
bool C_Grafo::busca_extensao(int v1, int v2)
{
  typedef struct BFS
  {
    char cor;
    int dist;
    int predecessor;
  }S_BFS;

  int u;
  int i;
  C_Fila fila(vertices * 2 - vertices);
  S_Aresta *apont;
  BFS *dados_vertice;
  dados_vertice = new BFS[(vertices - 1) * 2];

  for (int i = 0; i < ((vertices -1) * 2); i++)
  {
     dados_vertice[i].cor = 'B';
     dados_vertice[i].dist = 999999999;
     dados_vertice[i].predecessor = NULL;
  }
  dados_vertice[v1 - 1].cor = 'C';
  dados_vertice[v1 - 1].dist = 0;
  dados_vertice[v1 - 1].predecessor = NULL;
  fila.Enfileira(v1);
  while (!(fila.Vazia()))
  {
     fila.Desenfileira(&u);
     apont= grafo[u - 1].aresta->prox;
     while (!(apont == NULL))
     {
        if (dados_vertice[apont->vertice - 1].cor == 'B')
        {
           dados_vertice[apont->vertice - 1].dist = dados_vertice[u - 1].dist + apont->peso;
           dados_vertice[apont->vertice - 1].predecessor = u;
           fila.Enfileira(apont->vertice);
        }
        if (apont->vertice == v2)
        {
           cout << "\n\n\tO custo do caminho entre o vertice " << v1
              << " ao vertice " << v2 << " e de " << dados_vertice[apont->vertice - 1].dist << " unidade(s).";
           cout << "\n\tCaminho: " << v2;
           i = v2;
           while (!(dados_vertice[i - 1].predecessor == NULL))
           {
              cout << " - " << dados_vertice[i - 1].predecessor;
              i = dados_vertice[i - 1].predecessor;
           }
           getch();
           return true;
        }
        else
           apont = apont->prox;
     }
     dados_vertice[u - 1].cor = 'P';
  }
  return false;
}
   /*====================================================================
    Procedimento: imprime_lista: imprime na tela a lista de adjacencia
   =====================================================================*/
void C_Grafo::imprime_lista()
{
  S_Aresta *apont;
  cout << "VERT.  ARESTAS";
  for (int i = 0; i < vertices; i++)
  {
     clrscr;
     cout << "\n  " << i + 1 << " ";
     apont = grafo[i].aresta->prox;
     while (!(apont == NULL))
     {
        cout << "   " << apont->vertice;
        apont = apont->prox;
     }
  }
}
/*============================================================
    Procedimento: imprime_lista_v: Exibe Lista de Adjacencias
                               do vertice
    Parametros: v: vertice informado
   ============================================================*/
void C_Grafo::imprime_lista_v(int v)
{
   cout << "\n" << "Vertice: " << grafo[v - 1].vertice;
   cout << "\n" << "Vertices adjacentes: ";
   S_Aresta *vet;
   vet = grafo[v - 1].aresta->prox;
   while (!(vet == NULL))
   {
      cout << " " << vet->vertice;
      vet = vet->prox;
   }
}


void main()
{
   cout << "\n\n    *** PROGRAMA - REPRESENTACAO DE UM GRAFO "
        << "USANDO LISTA DE ADJACENCIAS ***"
        << "\n\n\n\tArquivo para leitura de informacoes do grafo: Grafo.txt";
   C_Grafo grafo;
   grafo.carrega_arquivo();
   char consulta;
   int op, v1, v2;
   cout << "\n\n< Numero de vertices do grafo: " << grafo.informa_vertice()
           << " >";
   do
   {
      clrscr();
      cout << "\n\n\t    < Menu de Opcoes >"
           << "\n\n\n\t[1] - Pesquisa de aresta"
           << "\n\n\t[2] - Grau de vertice"
           << "\n\n\t[3] - Pesquisa em profundidade"
           << "\n\n\t[4] - Imprime lista de adjacencia"
           << "\n\n\t[5] - Imprime lista de adjacencia de um vértice"
           << "\n\n\tQualquer outra tecla - Sair\n\n\t>";
      cin>>op;
      clrscr();
      switch (op)
      {
         case 1:
         {
            cout << "\n\n\tInforme o primeiro vertice: ";
            cin >> v1;
            if (!(grafo.pesquisa_vertice(v1)))
               cout << "\nVertice " << v1 << " inexistente.";
            else
            {
               cout << "\n\n\tInforme o segundo vertice: ";
               cin >> v2;
               if (!(grafo.pesquisa_vertice(v2)))
                  cout << "\nVertice " << v2 << " inexistente.";
               else
               {
                  if (grafo.pesquisa_aresta(v1, v2))
                     cout << "\n\n\tOK! Aresta existente";
                  else
                     cout << "\n\n\tAresta inexistente";
               }
            }
         }break;
         case 2:
         {
            cout << "\n\n\tInforme o vertice: ";
            cin >> v1;
            cout << "\n\n\tGrau do vertice " << v1 << " = "
                 << grafo.informa_grau(v1);
         }break;
         case 3:
         {
            cout << "\n\n\tInforme o primeiro vertice: ";
            cin >> v1;
            if (!(grafo.pesquisa_vertice(v1)))
               cout << "\nVertice " << v1 << " inexistente.";
            else
            {
               cout << "\n\n\tInforme o segundo vertice: ";
               cin >> v2;
               if (!(grafo.pesquisa_vertice(v2)))
                  cout << "\nVertice " << v2 << " inexistente.";
               else
               {
                  if (!grafo.busca_extensao(v1, v2))
                     cout << "\n\n\tCaminho inexistente.";
               }
            }
         }break;
         case 4:
         {
            grafo.imprime_lista();
            getch();
         }break;
         case 5:
         {
            cout << "\n\n\tInforme o primeiro vertice: ";
            cin >> v1;
            if (!(grafo.pesquisa_vertice(v1)))
               cout << "\nVertice " << v1 << " inexistente.";
            else
               grafo.imprime_lista_v(v1);
         }break;
         default: exit(0);
      }
      cout << "\n\n\n\n\tDeseja voltar ao Menu Inicial (s/n)? ";
      cin >> consulta;
      clrscr();
   }while (consulta == 's' || consulta == 'S');
}
//-----------Fim de Programa----------------------------------------------------
