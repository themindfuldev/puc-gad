#include "stdafx.h"


/*============================================================================*/
/*                     DEFINIÇÃO / DECLARAÇÃO DE ESTRUTURA - TIPOITEM         */
/*============================================================================*/
typedef int Apont_fila;
typedef struct
{
  int chave;
}TipoItem;

/*============================================================================*/
/*                     DEFINIÇÃO / DECLARAÇÃO DE ESTRUTURA - TIPOFILA         */
/*============================================================================*/
typedef struct
{
  TipoItem *item;
  Apont_fila frente, tras;
}TipoFila;
/*============================================================================*/
/*      CLASSE FILA - C_FILA: Enfileira e desenfileira numero inteiros        */
/*============================================================================*/
class C_Fila
{
  private:
    int tamanho;                                 // Tamanho da fila
    TipoFila fila;                               // Estrutura da fila
  public:
    C_Fila(int tam);                             // Construtor da fila (vazia)
    void Cria_Vazia();                           // Cria fila vazia
    bool Vazia();                                // Testa se a fila está vazia
    void Enfileira(int x);                       // Enfileira um item
    void Desenfileira(int *x);                   // desenfileira um item
};
   /*============================================================
    Proceidmento: C_Fila: Construtor Aloca memoria inicial conforme
                    valor de tam
   ============================================================*/
C_Fila::C_Fila(int tam)
{
  fila.item = new TipoItem[tam - 1];
  Cria_Vazia();
  tamanho = tam;
  for (int i = 0; i < tam; i++)
     fila.item[i].chave = 0;
}
   /*============================================================
    Funcao: Vazia: Retorna true se a fila estiver vazia
   ============================================================*/
bool C_Fila::Vazia()
{
  return (fila.frente == fila.tras);
}

   /*============================================================
    Procedimento: Cria_Vazia: Cria uma fila vazia
   ============================================================*/
void C_Fila::Cria_Vazia()
{
  fila.frente = 1;
  fila.tras = fila.frente;
}
   /*================================================================
    Procedimento: Enfileira: Enfileira um item passado por parametro
   =================================================================*/
void C_Fila::Enfileira(int x)
{
  if (fila.tras % tamanho + 1 == fila.frente)
  {
     printf("Fila cheia.\n");
  }
  else
  {
    fila.item[fila.tras - 1].chave = x;
    fila.tras = fila.tras % tamanho + 1;
  }
}
   /*================================================================
    Procedimento: Desenfileira: Desenfileira um item da fila
   =================================================================*/
void C_Fila::Desenfileira(int *x)
{
  if (Vazia())
     printf("Fila esta vazia.\n");
  else
  {
     *x = fila.item[fila.frente - 1].chave;
     fila.frente = fila.frente % tamanho +1;
  }
}

