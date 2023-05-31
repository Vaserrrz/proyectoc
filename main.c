#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "PaintGraph.h"
#include "ReadFile_CreateGraph.h"

void vMostrar(void){
  struct Nodo *pstNodoAux = pstHeadGrafo;
  struct Vertice *pstVerticeAux = NULL;
  


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

 int main()
{
  int sOpcion;
  do
  {
    
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
