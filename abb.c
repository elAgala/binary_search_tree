#include <stdio.h>
#include "abb.h"
#include <stdbool.h>
#include <string.h>

#define ERROR -1
#define EXITO 0
#define MAYOR_O_IGUAL 0
#define MENOR -1
#define MAYOR 1
#define IGUAL 0
#define DERECHA 1
#define IZQUIERDA 0


/*Estructura auxiliar para poder reutilizar la funcion recorrido_inorden en abb_con_cada_elemento*/
typedef struct array{
	void** array;
	int size;
	int* inserted;
}array_t;

abb_t* arbol_crear(abb_comparador comparador, abb_liberar_elemento destructor){
	if(!comparador)
		return NULL;
	abb_t* abb = calloc(1, sizeof(abb_t));
	if(!abb)
		return NULL;
	abb->comparador = comparador;
	if(destructor)
		abb->destructor = destructor;
	return abb;
}

nodo_abb_t* crear_nodo(void* elemento){
	nodo_abb_t* nodo = calloc(1, sizeof(nodo_abb_t));
	if(!nodo)
		return NULL;
	nodo->elemento = elemento;
	return nodo;
}

bool es_hoja(nodo_abb_t* nodo){
	return !nodo->derecha && !nodo->izquierda;
}

nodo_abb_t* obtener_nodo_anterior(nodo_abb_t* nodo, void* elemento, abb_comparador comparador){
	if(!nodo || es_hoja(nodo))
		return nodo;
	int comparacion = comparador(elemento, nodo->elemento);
	if(comparacion > MAYOR_O_IGUAL && nodo->derecha)
		return obtener_nodo_anterior(nodo->derecha, elemento, comparador);
	else if(comparacion == MENOR && nodo->izquierda)
		return obtener_nodo_anterior(nodo->izquierda, elemento, comparador);
	else
		return nodo;
}

int arbol_insertar(abb_t* arbol, void* elemento){
	if(!arbol)
		return ERROR;
	if(!arbol->nodo_raiz){
		arbol->nodo_raiz = crear_nodo(elemento);
		if(!arbol->nodo_raiz)
			return ERROR;
		return EXITO;
	}
	nodo_abb_t* nodo_anterior = obtener_nodo_anterior(arbol->nodo_raiz, elemento, arbol->comparador);
	int comparacion = arbol->comparador(elemento, nodo_anterior->elemento);
	if(comparacion > MAYOR_O_IGUAL)
		nodo_anterior->derecha = crear_nodo(elemento);
	else
		nodo_anterior->izquierda = crear_nodo(elemento);
	return EXITO;		
}

nodo_abb_t* obtener_nodo_y_padre(nodo_abb_t* nodo, nodo_abb_t** padre, void* elemento, abb_comparador comparador){
	int comparacion = comparador(elemento, nodo->elemento);
	if(comparacion == IGUAL)
		return nodo;
	if(!nodo->izquierda && !nodo->derecha)
		return NULL;
	*padre = nodo;
	if(comparacion == MAYOR){
		if(!nodo->derecha)
			return NULL;
		return obtener_nodo_y_padre(nodo->derecha, padre, elemento, comparador);
	}
	else{
		if(!nodo->izquierda)
			return NULL;
		return obtener_nodo_y_padre(nodo->izquierda, padre, elemento, comparador);
	}
}

void* swap_elementos(nodo_abb_t* nodo, nodo_abb_t* padre){
	void* aux = nodo->elemento;
	if(nodo == padre->izquierda)
		padre->izquierda = nodo->izquierda;
	else
		padre->derecha = nodo->izquierda;
	free(nodo);
	return aux;
}

void* encontrar_elemento_max(nodo_abb_t* nodo, nodo_abb_t* padre){
	if(!nodo->derecha)
		return swap_elementos(nodo, padre);
	return encontrar_elemento_max(nodo->derecha, nodo);
}

void liberar_elemento(void* elemento, abb_liberar_elemento destructor){
	if(destructor)
		destructor(elemento);
}

void liberar_nodo(nodo_abb_t* nodo, abb_liberar_elemento destructor){
	liberar_elemento(nodo->elemento, destructor);
	free(nodo);
}

int arbol_borrar(abb_t* arbol, void* elemento){
	if(!arbol || !arbol->nodo_raiz)
		return ERROR;
	nodo_abb_t* padre = NULL;
	nodo_abb_t* nodo_borrar = obtener_nodo_y_padre(arbol->nodo_raiz, &padre, elemento, arbol->comparador);
	if(!nodo_borrar)
		return ERROR;
	if(!nodo_borrar->izquierda && nodo_borrar != arbol->nodo_raiz){
		if(padre->derecha == nodo_borrar)
			padre->derecha = nodo_borrar->derecha;
		else
			padre->izquierda = nodo_borrar->derecha;
		liberar_nodo(nodo_borrar, arbol->destructor);
	}
	else if(nodo_borrar->izquierda == NULL){
		nodo_abb_t* nodo_aux = arbol->nodo_raiz;
		arbol->nodo_raiz = nodo_borrar->derecha;
		liberar_nodo(nodo_aux, arbol->destructor);
	}
	else{
		void* elemento_max = encontrar_elemento_max(nodo_borrar->izquierda, nodo_borrar);
		liberar_elemento(nodo_borrar->elemento, arbol->destructor);
		nodo_borrar->elemento = elemento_max;
	}
	return EXITO;
}

nodo_abb_t* buscar_nodo(nodo_abb_t* nodo, void* elemento, abb_comparador comparador){
	int comparacion = comparador(elemento, nodo->elemento);
	if(comparacion == IGUAL)
		return nodo;
	if(!nodo->izquierda && !nodo->derecha)
		return NULL;
	if(comparacion == MAYOR){
		if(!nodo->derecha)
			return NULL;
		return buscar_nodo(nodo->derecha, elemento, comparador);
	}
	else{
		if(!nodo->izquierda)
			return NULL;
		return buscar_nodo(nodo->izquierda, elemento, comparador);
	}
}

void* arbol_buscar(abb_t* arbol, void* elemento){
	if(!arbol || !arbol->nodo_raiz)
		return NULL;
	nodo_abb_t* nodo = buscar_nodo(arbol->nodo_raiz, elemento, arbol->comparador);
	if(nodo)
		return nodo->elemento;
	return NULL;
}

void* arbol_raiz(abb_t* arbol){
	if(!arbol || !arbol->nodo_raiz)
		return NULL;
	return arbol->nodo_raiz->elemento;
}

bool arbol_vacio(abb_t* arbol){
	if(!arbol || !arbol->nodo_raiz)
		return true;
	return false;
}

array_t inicializar_vector(void** vector, int tamanio_array, int* contador){
	array_t array;
	array.array = vector;
	array.size = tamanio_array;
	array.inserted = contador;
	return array;
}

/*Inserta un elemento en el array devolviendo false, en caso de estar lleno el vector, devuelve true*/
bool insertar_elemento_array(void* elemento, void* vector){
	array_t* array = (array_t*)vector;
	if(*(array->inserted) < array->size){
		array->array[*(array->inserted)] = elemento;
		(*(array->inserted))++;
		return *(array->inserted) >= array->size;
	}
	return true;
}

bool recorrido_inorden(nodo_abb_t* nodo, bool (*continuar)(void*, void*), void* extra){
	if(!nodo)
		return false;
	if(recorrido_inorden(nodo->izquierda, continuar, extra))
		return true;
	if(continuar(nodo->elemento, extra))
		return true;
	if(recorrido_inorden(nodo->derecha, continuar, extra))
		return true;
	return false;
}

bool recorrido_preorden(nodo_abb_t* nodo, bool (*continuar)(void*, void*), void* extra){
	if(!nodo)
		return false;
	if(continuar(nodo->elemento, extra))
		return true;
	if(recorrido_preorden(nodo->izquierda, continuar, extra))
		return true;
	if(recorrido_preorden(nodo->derecha, continuar, extra))
		return true;
	return false;
}

bool recorrido_postorden(nodo_abb_t* nodo, bool (*continuar)(void*, void*), void* extra){
	if(!nodo)
		return false;
	if(recorrido_postorden(nodo->izquierda, continuar, extra))
		return true;
	if(recorrido_postorden(nodo->derecha, continuar, extra))
		return true;
	if(continuar(nodo->elemento, extra))
		return true;
	return false;
}

int arbol_recorrido_inorden(abb_t* arbol, void** array, int tamanio_array){
	if(!arbol || arbol_vacio(arbol) || !array)
		return 0;
	int contador_elementos_insertados = 0;
	array_t vector = inicializar_vector(array, tamanio_array, &contador_elementos_insertados);
	recorrido_inorden(arbol->nodo_raiz, insertar_elemento_array, &vector);
	return contador_elementos_insertados;
}

int arbol_recorrido_preorden(abb_t* arbol, void** array, int tamanio_array){
	if(!arbol || arbol_vacio(arbol) || !array)
		return 0;
	int contador_elementos_insertados = 0;
	array_t vector = inicializar_vector(array, tamanio_array, &contador_elementos_insertados);
	recorrido_preorden(arbol->nodo_raiz, insertar_elemento_array, &vector);
	return contador_elementos_insertados;
}

int arbol_recorrido_postorden(abb_t* arbol, void** array, int tamanio_array){
	if(!arbol || arbol_vacio(arbol) || !array)
		return 0;
	int contador_elementos_insertados = 0;
	array_t vector = inicializar_vector(array, tamanio_array, &contador_elementos_insertados);
	recorrido_postorden(arbol->nodo_raiz, insertar_elemento_array, &vector);
	return contador_elementos_insertados;
}

void destruir_nodo_recursivo(nodo_abb_t* nodo, abb_liberar_elemento destructor){
	if(nodo->izquierda)
		destruir_nodo_recursivo(nodo->izquierda, destructor);
	if(nodo->derecha)
		destruir_nodo_recursivo(nodo->derecha, destructor);
	if(destructor)
		destructor(nodo->elemento);
	free(nodo);
}

void arbol_destruir(abb_t* arbol){
	if(!arbol)
		return;
	if(arbol->nodo_raiz)
		destruir_nodo_recursivo(arbol->nodo_raiz, arbol->destructor);
	free(arbol);
}

void abb_con_cada_elemento(abb_t* arbol, int recorrido, bool (*funcion)(void*, void*), void* extra){
	if(!arbol || arbol_vacio(arbol))
		return;
	if(recorrido == ABB_RECORRER_INORDEN)
		recorrido_inorden(arbol->nodo_raiz, funcion, extra);
	if(recorrido == ABB_RECORRER_PREORDEN)
		recorrido_preorden(arbol->nodo_raiz, funcion, extra);
	if(recorrido == ABB_RECORRER_POSTORDEN)
		recorrido_postorden(arbol->nodo_raiz, funcion, extra);
}
