
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SUCCESS 1
#define ERROR 0
#define MAX_COLORS 4 // MAXIMA CANTIDAD DE CONBINACIONES ACEPTADAS
struct Vertice {

  char szNombre[10] ;
  struct Vertice *pstNextVertice ;
};
struct Nodo {

  char szNombre[10] ;
  struct Vertice *pstHeadVertice ;
  struct Nodo *pstNextNodo ;
};
struct Nodo *pstHeadGrafo = NULL ;

void vInserta_Vertice( char *pszNombreNodo, char *pszNombreVertice ){
  struct Nodo *pstNodo = NULL ;
  struct Vertice *pstVertice = NULL ;
  struct Vertice *pstVerticeAux = NULL ;
  pstNodo = pstHeadGrafo ;
  /* Busco el nodo que corresponde */
  do{
    if (strcmp(pstNodo ->szNombre, pszNombreNodo) == 0)
      break ;
    else
    pstNodo = pstNodo->pstNextNodo ; // sino corresponde busca el soguiente
  }
  while(pstNodo != NULL ); 
  {
    //insertar en la lista para ese nodo un nuevo vertice
    pstVertice = (struct Vertice *)malloc(sizeof(struct Vertice)); // SE RESERVA LA MEMORIA PARA EL SIGUIENTE VERTICE
    memset(pstVertice,0,sizeof(struct Vertice)); // inicializamos el aerea de memoria
    sprintf(pstVertice->szNombre,"%s",pszNombreVertice) ; // SE LE ASIGNA EL NOMBRE

    pstVerticeAux=pstNodo->pstHeadVertice;

    if (pstNodo->pstHeadVertice == NULL){
      pstNodo->pstHeadVertice = pstVertice;
      pstVertice->pstNextVertice = NULL ;
    }
    else{

      do{
        if (pstVerticeAux->pstNextVertice == NULL)
        {
        pstVerticeAux->pstNextVertice = pstVertice;
        break;
        }
        pstVerticeAux=pstVerticeAux->pstNextVertice;
      }
      while(1);
    }
    return ;
  };
}
