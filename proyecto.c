#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estructuras de datos del grafo
typedef struct sVertice {
    char nombre[10];
    struct sVertice *sig;
} tVertice;

typedef struct sNodo {
    char nombre[10];
    struct sVertice *pv;
    struct sNodo *sig;
} tNodo;

typedef struct sColores {
    char nombre[20];
    struct sNodo *pn;
    struct sVertice *pv;
    struct sColores *sig;
} tColores;

// Variables globales
tNodo *pstHeadGrafo = NULL;
tColores stColores[5];

// Prototipos de funciones
int sBusca_Nodo_En_Lista_Vertices(tVertice *pv, char *nombre);
int sBusca_Vertices_En_Lista_Nodos(tNodo *pn, char *nombre);
int sBusca_Nodo_En_Lista_Colores(tColores *pc, char *nombre);
int sBusca_Vertices_En_Lista_Colores(tColores *pc, char *nombre1, char *nombre2);
int sAgregar_Vertice(tNodo *pn, char *nombre);
int sAgregar_Nodo(char *nombre);
int sAgregar_Color(char *nombre);
void sMuestra_Nodo(tNodo *pn);
void sMuestra_Vertices(char *nombre1, char *nombre2);
void sMuestra_Colores(char *nombre);
void sImprime_Grafo();

// Función para cargar la configuración desde un archivo
void cargar_configuracion(char *nombre_archivo) {
    FILE *archivo = fopen(nombre_archivo, "r");

    if (archivo == NULL) {
        printf("Error al abrir el archivo %s\n", nombre_archivo);
        exit(1);
    }

    char nombre_nodo[10];
    char nombre_destino[10];
    char color[20];

    while (fscanf(archivo, "%s %s %s", nombre_nodo, nombre_destino, color) == 3) {
        // Busca si el nodo ya existe
        tNodo *pn = pstHeadGrafo;
        while (pn != NULL && strcmp(pn->nombre, nombre_nodo) != 0) {
            pn = pn->sig;
        }

        // Si no existe, lo agrega
        if (pn == NULL) {
            sAgregar_Nodo(nombre_nodo);
            pn = pstHeadGrafo;
        }

        // Agrega el vértice al nodo
        sAgregar_Vertice(pn, nombre_destino);

        // Busca si el color ya existe
        tColores *pc = stColores;
        while (pc != stColores + 5 && strcmp(pc->nombre, color) != 0) {
            pc++;
        }

        // Si no existe, lo agrega
        if (pc == stColores + 5) {
            sAgregar_Color(color);
            pc = stColores + 4;
        }

        // Agrega el nodo y el vértice al color
        if (sBusca_Nodo_En_Lista_Colores(pc, nombre_nodo) != 0) {
            pc->pn->sig = pn;
            pc->pn = pn;
        } else {
            pc->pn = (tNodo *)malloc(sizeof(tNodo));
            strcpy(pc->pn->nombre, nombre_nodo);
            pc->pn->pv = NULL;
            pc->pn->sig = pn;
        }
        if (sBusca_Vertices_En_Lista_Colores(pc, nombre_nodo, nombre_destino) != 0) {
            pc->pv->sig = pn->pv;
            pc->pv = pn->pv;
        } else {
            pc->pv = (tVertice *)malloc(sizeof(tVertice));
            strcpy(pc->pv->nombre, nombre_destino);
            pc->pv->sig = pn->pv;
        }
    }

    fclose(archivo);
}

// Función para mostrar la información cargada
void mostrar_configuracion() {
    printf("Intersección:\n");
    sImprime_Grafo();
    printf("Giros válidos:\n");
    sMuestra_Colores("giro_izquierda");
    sMuestra_Colores("giro_derecha");
    sMuestra_Colores("giro_recto");
    printf("Incompatibilidades:\n");
    sMuestra_Vertices("norte", "sur");
    sMuestra_Vertices("sur", "norte");
    sMuestra_Vertices("este", "oeste");
    sMuestra_Vertices("oeste", "este");
}

// Función principal
int main(int argc, char **argv) {
    if (argc < 2) {
        printf("Debe especificar el archivo de configuración como argumento\n");
        return 1;
    }

    char *nombre_archivo = argv[1];

    cargar_configuracion(nombre_archivo);

    mostrar_configuracion();

    return 0;
}

// Implementación de las funciones del grafo
int sBusca_Nodo_En_Lista_Vertices(tVertice *pv, char *nombre) {
    while (pv != NULL && strcmp(pv->nombre, nombre) != 0) {
        pv = pv->sig;
    }
    return (pv != NULL);
}

int sBusca_Vertices_En_Lista_Nodos(tNodo *pn, char *nombre) {
    while (pn != NULL && sBusca_Nodo_En_Lista_Vertices(pn->pv, nombre) == 0) {
        pn = pn->sig;
    }
    return (pn != NULL);
}

int sBusca_Nodo_En_Lista_Colores(tColores *pc, char *nombre) {
    while (pc != NULL && sBusca_Vertices_En_Lista_Nodos(pc->pn, nombre) == 0) {
        pc = pc->sig;
    }
    return (pc != NULL);
}

int sBusca_Vertices_En_Lista_Colores(tColores *pc, char *nombre1, char *nombre2) {
    while (pc != NULL && sBusca_Nodo_En_Lista_Vertices(pc->pv, nombre1) == 0) {
        pc = pc->sig;
    }
    while (pc != NULL && sBusca_Nodo_En_Lista_Vertices(pc->pv, nombre2) == 0) {
        pc = pc->sig;
    }
    return (pc != NULL);
}

int sAgregar_Vertice(tNodo *pn, char *nombre) {
    if (sBusca_Nodo_En_Lista_Vertices(pn->pv, nombre) != 0) {
        return 0;
    }
    tVertice *pv = (tVertice *)malloc(sizeof(tVertice));
    strcpy(pv->nombre, nombre);
    pv->sig = pn->pv;
    pn->pv = pv;
    return 1;
}

int sAgregar_Nodo(char *nombre) {
    if (sBusca_Vertices_En_Lista_Nodos(pstHeadGrafo, nombre) != 0) {
        return 0;
    }
    tNodo *pn = (tNodo *)malloc(sizeof(tNodo));
    strcpy(pn->nombre, nombre);
    pn->pv = NULL;
    pn->sig = pstHeadGrafo;
    pstHeadGrafo = pn;
    return 1;
}

int sAgregar_Color(char *nombre) {
    if (sBusca_Nodo_En_Lista_Colores(stColores, nombre) != 0) {
        return 0;
    }
    tColores *pc = (tColores *)malloc(sizeof(tColores));
    strcpy(pc->nombre, nombre);
    pc->pn = NULL;
    pc->pv = NULL;
    pc->sig = stColores;
    stColores[4].sig = pc;
    return 1;
}

void sMuestra_Nodo(tNodo *pn) {
    tVertice *pv = pn->pv;
    printf("%s -> ", pn->nombre);
    while (pv != NULL) {
        printf("%s ", pv->nombre);
        pv = pv->sig;
    }
    printf("\n");
}

void sMuestra_Vertices(char *nombre1, char *nombre2) {
    tNodo *pn = pstHeadGrafo;
    while (pn != NULL) {
        tVertice *pv = pn->pv;
        while (pv != NULL) {
            if (strcmp(pv->nombre, nombre1) == 0 && sBusca_Nodo_En_Lista_Vertices(pn->pv, nombre2) != 0) {
                printf("%s %s -> %s %s\n", pn->nombre, nombre1, pn->nombre, nombre2);
            } else if (strcmp(pv->nombre, nombre2) == 0 && sBusca_Nodo_En_Lista_Vertices(pn->pv, nombre1) != 0) {
                printf("%s %s -> %s %s\n", pn->nombre, nombre2, pn->nombre, nombre1);
            }
            pv = pv->sig;
        }
    }
};