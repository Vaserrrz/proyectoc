#include <stdlib.h>
#define SUCCESS 1
#define ERROR 0

struct Vertice {

  char szNombre[10] ;
  struct Vertice *pstNextVertice ;
};

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