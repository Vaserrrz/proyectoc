#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ReadFile_CreateGraph.h"
#include "PaintGraph.h"

short sLeerArchivo(void){

  char szNombreArchivo[100] ; // Guarda el nombre del archivo dado por el usuario en pantalla
  char szDato[100]; // almacena datos que no se usan
  char szNodo[10]; // almacena el nombre del nodo
  char szVertice[10]; // almacena el nombre del vertice
  short sCantCruces, sCont ; // almacena la cantodda de cruces
  FILE *pFConfig = NULL ; // Puntero donde se lee el archivo
  struct Nodo *pstNodo = NULL ; //nodo que se va agragando

  /* Se ABRE EL ARCHIVO */
  system("clear") ;
  memset(szNombreArchivo,0,sizeof(szNombreArchivo));
  printf(" POR FAVOR DIGITE EL NOMBRE DEL ARCHIVO :") ;
  scanf("%s",szNombreArchivo) ;
  getchar() ;

  if( (pFConfig = fopen(szNombreArchivo, "r")) == NULL )
  {
    printf( " EL ARCHIVO NO SE PUDO ABRIR");
    getchar() ;
    return(ERROR);
  }

  /*Se lee la cantidad de Nodos */
  memset(szDato,0,sizeof(szDato));
  fscanf(pFConfig, "%s",szDato);
  sCantCruces = atoi(szDato); // guarda el dato de cant de cruces
  /* Se recorre la linea guardando los NODOS */
  // se pide memoria para el primer nodo
  pstHeadGrafo = (struct Nodo *)malloc(sizeof( struct Nodo));
  pstNodo = pstHeadGrafo ;

  // se recorre el archivo \ segun lo indicado en configuracion
  // de la primera linea que nos indico cuantas cruces se iban a leer
  for ( sCont = 0; sCont < sCantCruces; sCont++){
    //Se inicializa el nodo
    memset(pstNodo,0,sizeof(struct Nodo));
    fscanf(pFConfig,"%5s", pstNodo->szNombre);

    if(sCont + 1 < sCantCruces){
      // Se pide la memoria y se agrga el siguiente nodo
      pstNodo->pstNextNodo = (struct Nodo *)malloc(sizeof( struct Nodo));
      pstNodo = pstNodo->pstNextNodo ;
    }
    else
    // Se le pone Null al final de la lista de nodos
    pstNodo->pstNextNodo = NULL ;
  }

  /*se Reccorre el resto del archivo
  Buscando los Cruces que no se deben hacer */
  while( !feof(pFConfig)){
    // se leen los 4 caracteres
    // correspondde al Nodo
    memset(szNodo,0,sizeof(szNodo));
    fscanf(pFConfig,"%4s",szNodo);
    if( strlen(szNodo) == 0)
    break ;
    // se lee los espacios y la ralla
    memset(szDato,0,sizeof(szDato));
    fscanf(pFConfig,"%3s",szDato);
    // Se lee la segunda parte que es el vertice
    memset(szVertice,0,sizeof(szVertice));
    fscanf(pFConfig,"%4s", szVertice);
    // Adiciona el vertice a lista de vertices el nodo indicado
    vInserta_Vertice(szNodo,szVertice) ;
  }

  /* Se cierra el archivo de configuracion */
  fclose(pFConfig) ;
  return(SUCCESS);
}
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
