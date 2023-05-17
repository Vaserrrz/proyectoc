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


/*Lista donde se van a guardar el Grafo ordenado */
struct Colores {
  char szNombre[20];
  struct Nodo *pstHeadNodo ; // Lista de Nodos del color
  struct Vertice *pstHeadVertice ; // lista de vertices que llegan o salen de ese color
};
struct Nodo *pstHeadGrafo = NULL ;
struct Colores stColores[MAX_COLORS] ;


void vMostrar(void){
  struct Nodo *pstNodoAux = pstHeadGrafo;
  struct Vertice *pstVerticeAux = NULL;
  system("clear");


  printf("\n NODO ->  VERTICES .......\n");

  while (pstNodoAux != NULL){
    // recorre los vertices
    printf("\n[%s]",pstNodoAux->szNombre);
    pstVerticeAux = pstNodoAux->pstHeadVertice;
    while (pstVerticeAux != NULL)
    {
      // recorre los grafos
      printf("->[%s]",pstVerticeAux->szNombre);
      pstVerticeAux = pstVerticeAux->pstNextVertice;
    }
    pstNodoAux = pstNodoAux->pstNextNodo;
  }
  printf("\nPress enter para continuar");
  getchar();
}
main()
{
  short sOpcion;
  do
  {
    system("clear");
    printf(" ") ;
    printf("      MENU \n\n");
    printf(" 1) LEER CONFIGURACION\n") ;
    printf(" 2) MOSTRAR CONFIGURACION\n");
    printf(" 3) MOSTRAR RESPUESTA\n");
    printf(" 4) SALIR \n");
    printf("OPCION [  ]\b\b\b");
    scanf("%d",&sOpcion);
    getchar() ;
    
    if( sOpcion == 1)
    sLeerArchivo() ;
    if( sOpcion ==2)
    vMostrar();
    if( sOpcion == 3)
    vRespuesta();
    if(sOpcion == 4)
    break;
  }
  while(1) ;
  return (SUCCESS);
}
