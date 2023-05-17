#include <stdio.h>
#define MAX_COLORS 4 

//ESTRUCTURAS
struct Colores stColores[MAX_COLORS] ;
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

//FUNCION
void vAgrega_Nodo_y_Vertices_Al_Color(short sCont, struct Nodo *pstNodo){
  struct Nodo *pstAuxNodo ;
  struct Vertice *pstAuxVer ;

  pstAuxNodo = stColores[sCont].pstHeadNodo ;
  pstAuxVer = stColores[sCont].pstHeadVertice ;
  // SI ES LA PRIMERA VEZ INICIALIZA LA ESTRUCTURA DE COLORES
  // ASIGANANDO POR PRIMERA VEZ EL PRIMER NODO y su lista de vertices
  if( pstAuxNodo == NULL){

    stColores[sCont].pstHeadNodo = pstNodo ;
    stColores[sCont].pstHeadVertice = pstNodo->pstHeadVertice ;
  }
  else{
    //Se Busca el FInal de la lista de Nodos
    while(pstAuxNodo->pstNextNodo != NULL ) {
      pstAuxNodo = pstAuxNodo->pstNextNodo ;
      // Se agrega el Nodo al Color
      pstAuxNodo->pstNextNodo = pstNodo ;
      // Busca el apuntador hasta el final de la lista e Vertices
    }
    while(pstAuxVer->pstNextVertice != NULL ){
      pstAuxVer = pstAuxVer->pstNextVertice ;
      //se adiciona la lista al final de la lista de vertices
      pstAuxVer->pstNextVertice = pstNodo->pstHeadVertice ;
    }
  }
  return ;
}