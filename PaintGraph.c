#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ReadFile_CreateGraph.h"
#include "PaintGraph.h"

void vRespuesta(void){
  struct Nodo *pstNodo = pstHeadGrafo ;
  struct Nodo *pstAntNodo = NULL ;
  short sCont ;
  // se inicializa el vector de estructuras donde van a quedar la respuesta
  memset(stColores,0,sizeof(struct Colores)*4) ;
  sprintf(stColores[0].szNombre,"AZUL    ");
  sprintf(stColores[1].szNombre,"ROJO    ");
  sprintf(stColores[2].szNombre,"VERDE   ");
  sprintf(stColores[3].szNombre,"AMARILLO");
  // se recorre el Grafo para asignar en la lista de los colores
  do {
    sCont = 0 ;
    do{
      if( sBusca_Nodo_En_Lista_Vertices(pstNodo->szNombre, stColores[sCont].pstHeadVertice ) != SUCCESS )
      if(sBusca_Vertices_En_Lista_Nodos(stColores[sCont].pstHeadNodo, pstNodo->pstHeadVertice) != SUCCESS )
      break ;
      sCont++ ;
    } 
    while(sCont < MAX_COLORS);{
      vAgrega_Nodo_y_Vertices_Al_Color(sCont, pstNodo);
      pstAntNodo = pstNodo ;
      pstNodo = pstNodo-> pstNextNodo ; // asigna el siguinte nodo
      pstAntNodo->pstNextNodo = NULL ;
    }   
  } 
  
  while(pstNodo != NULL);

  
  for( sCont = 0; sCont < MAX_COLORS ; sCont++ ){
    pstNodo = stColores[sCont].pstHeadNodo ;
    printf("[%s] =>",stColores[sCont].szNombre);

    while( pstNodo != NULL){
      printf("[%s] -> ",pstNodo->szNombre) ;
      pstNodo = pstNodo -> pstNextNodo ;
    }
    printf("\n");
  }
  getchar() ;
  return ;
}
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
short sBusca_Nodo_En_Lista_Vertices(char *pszNombreNodo, struct Vertice *pstListaVertices){
  struct Vertice *pstAuxVer = pstListaVertices ;
  // Recorre la lista hasta el final
  while( pstAuxVer != NULL ){
    // Compara el NOmbre del Nodo, con el Nombre del vertice
    if(strcmp(pszNombreNodo,pstAuxVer->szNombre) == 0){
      return(SUCCESS) ; // Si lo encontro retorna exito
    }
    pstAuxVer = pstAuxVer->pstNextVertice  ;  // El siguiente Vertive
  }
  return(ERROR); //Sino lo encontro salio por que encontro el final de la lista y retorna error
}
short sBusca_Vertices_En_Lista_Nodos(struct Nodo *pstListaNodos,struct Vertice *pstListaVertices){
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