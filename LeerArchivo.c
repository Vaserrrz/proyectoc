#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// #include vInserta_Vertice.c
#define ERROR 0
#define SUCCESS 1


struct Nodo *pstHeadGrafo = NULL ;
struct Nodo {

  char szNombre[10] ;
  struct Vertice *pstHeadVertice ;
  struct Nodo *pstNextNodo ;
};
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