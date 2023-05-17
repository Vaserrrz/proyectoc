#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SUCCESS 1
#define ERROR 0
#define MAX_COLORS 4 // MAXIMA CANTIDAD DE CONBINACIONES ACEPTADAS

//ESTRUCTURAS
struct Vertice {

  char szNombre[10] ;
  struct Vertice *pstNextVertice ;
};
struct Nodo {

  char szNombre[10] ;
  struct Vertice *pstHeadVertice ;
  struct Nodo *pstNextNodo ;
};
/*Lista donde se van a guardar el Grafo ordenado */
struct Colores {
  char szNombre[20];
  struct Nodo *pstHeadNodo ; // Lista de Nodos del color
  struct Vertice *pstHeadVertice ; // lista de vertices que llegan o salen de ese color
};
struct Nodo *pstHeadGrafo = NULL ;
struct Colores stColores[MAX_COLORS] ;

//FUNCION
sBusca_Vertices_En_Lista_Nodos(struct Nodo *pstListaNodos,struct Vertice *pstListaVertices){
  struct Nodo *pstAuxNodo = pstListaNodos ;

  // recorre la lista de los nodos hasta el final
  while( pstAuxNodo != NULL ){
    // hace la buscada del nodo en la lista de vertices
    if( sBusca_Nodo_En_Lista_Vertices(pstAuxNodo->szNombre, pstListaVertices) == SUCCESS )
    return(SUCCESS);
    pstAuxNodo = pstAuxNodo->pstNextNodo ;
  }
  // si salio hasta el fnal de la lista sin encontrar ningun nodo
  // en la lista de vertices
  return(ERROR);
}