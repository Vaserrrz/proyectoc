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

  system("clear");
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
