#include <stdio.h>
#define SUCCESS 1

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