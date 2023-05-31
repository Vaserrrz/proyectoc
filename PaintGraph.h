#define MAX_COLORS 4
#define SUCCESS 1
#define ERROR 0



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
struct Colores stColores[MAX_COLORS] ;

//FUNCIONES
void vRespuesta(struct Nodo *pstHeadGrafo);
void vAgrega_Nodo_y_Vertices_Al_Color(short sCont, struct Nodo *pstNodo);
short sBusca_Nodo_En_Lista_Vertices(char *pszNombreNodo, struct Vertice *pstListaVertices);
short sBusca_Vertices_En_Lista_Nodos(struct Nodo *pstListaNodos,struct Vertice *pstListaVertices);


