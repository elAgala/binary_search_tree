#include <stdio.h>
#include <string.h>
#include "abb.h"
#include "tester.h"

#define COLOR_MAGENTA "\x1b[35m\x1b[1m"
#define COLOR_CYAN "\x1b[36m\x1b[1m"
#define COLOR_AMARILLO "\x1b[33m\x1b[1m"
#define COLOR_ROJO "\x1b[31m\x1b[1m"
#define COLOR_VERDE "\x1b[32m\x1b[1m"
#define COLOR_NORMAL "\x1b[0m"

#define PASSED COLOR_VERDE"PASSED"COLOR_NORMAL
#define FAILED COLOR_ROJO"FAILED"COLOR_NORMAL

#define ERROR -1
#define EXITO 0

typedef struct tarea{
	int dia;
	int mes;
	char* desc;
}tarea_t;

tarea_t* crear_tarea(int dia, int mes, char* descripcion){
	tarea_t* nueva_tarea = calloc(1, sizeof(tarea_t));
	if(!nueva_tarea)
		return NULL;
	nueva_tarea->dia = dia;
	nueva_tarea->mes = mes;
	nueva_tarea->desc = descripcion;
	return nueva_tarea;
}

int comparar_tareas(void* a, void* b){
	if(!a && !b)
		return 0;
	if(!a)
		return 1;
	if(!b)
		return -1;
	tarea_t* tarea_1 = (tarea_t*)a;
	tarea_t* tarea_2 = (tarea_t*)b;
	if(tarea_1->mes > tarea_2->mes)
		return 1;
	else if(tarea_1->mes < tarea_2->mes)
		return -1;
	else{
		if(tarea_1->dia > tarea_2->dia)
			return 1;
		else if(tarea_1->dia < tarea_2->dia)
			return -1;
		else
			return 0;
	}
}

bool compareTasks(void* a, void* b){
	tarea_t* tarea_1 = (tarea_t*)a;
	tarea_t* tarea_2 = (tarea_t*)b;
	
	if(tarea_1->mes != tarea_2->mes)
		return false;
	if(tarea_1->dia != tarea_2->dia)
		return false;
	return true;
}

void destruir_tarea(tarea_t* tarea){
	free(tarea);
}

void destruir_tareas(void* elemento){
	if(!elemento)
		return;
	destruir_tarea((tarea_t*)elemento);
}

void mostrar_tareas(tarea_t* tarea){
	printf("\nFECHA: %i/%i ----->"COLOR_MAGENTA" %s\n"COLOR_NORMAL, tarea->dia, tarea->mes, tarea->desc);
}

void mostrar_array(tarea_t** tareas, int tope){
	for(int i = 0; i < tope; i++)
		mostrar_tareas((tarea_t*)tareas[i]);
}

bool mostrar_elemento_acumulado(void* elemento, void* extra){
	if(elemento && extra)
		(*(int*)extra) += 1;
	return false;
}

bool mostrar_hasta_tarea(void* elemento, void* extra){
	if(elemento && extra){
		if(*(int*)extra == 5)
			return true;
		(*(int*)extra)++;
	}
	return false;
}

int contador_nodos(nodo_abb_t* nodo){
	if(!nodo->izquierda && !nodo->derecha)
		return 1;
	int rama_izquierda = 0;
	if(nodo->izquierda)
		rama_izquierda = contador_nodos(nodo->izquierda);
	int rama_derecha = 0;
	if(nodo->derecha)
		rama_derecha = contador_nodos(nodo->derecha);
	return rama_izquierda + rama_derecha + 1;
}

void probar_insercion(abb_t* arbol, tarea_t** tareas){
	
	printf("\nInserto tarea 1: %s\n", arbol_insertar(arbol, tareas[0])==EXITO?PASSED:FAILED);
	printf("\nInserto tarea 2: %s\n", arbol_insertar(arbol, tareas[1])==EXITO?PASSED:FAILED);
	printf("\nInserto tarea 3: %s\n", arbol_insertar(arbol, tareas[2])==EXITO?PASSED:FAILED);
	printf("\nInserto tarea 4: %s\n", arbol_insertar(arbol, tareas[3])==EXITO?PASSED:FAILED);
	printf("\nInserto tarea 5: %s\n", arbol_insertar(arbol, tareas[4])==EXITO?PASSED:FAILED);
	printf("\nInserto tarea 6: %s\n", arbol_insertar(arbol, tareas[5])==EXITO?PASSED:FAILED);
	printf("\nInserto tarea 7: %s\n", arbol_insertar(arbol, tareas[6])==EXITO?PASSED:FAILED);
	printf("\nInserto tarea 8: %s\n", arbol_insertar(arbol, tareas[7])==EXITO?PASSED:FAILED);
	printf("\nInserto tarea 9: %s\n", arbol_insertar(arbol, tareas[8])==EXITO?PASSED:FAILED);
	printf("\nInserto tarea 10: %s\n", arbol_insertar(arbol, tareas[9])==EXITO?PASSED:FAILED);
	printf("\nAhora el arbol tiene 10 elementos: %s\n", contador_nodos(arbol->nodo_raiz)==10?PASSED:FAILED);
}

void probar_busqueda(abb_t* arbol, tarea_t** tareas){
	printf(COLOR_CYAN"\n/***BUSCO TAREAS Y LAS MUESTRO***\\\n"COLOR_NORMAL);
	printf("\nBusco tarea 1: %s\n", arbol_buscar(arbol, tareas[0])!=NULL?PASSED:FAILED);
	mostrar_tareas((tarea_t*)arbol_buscar(arbol, tareas[0]));
	printf("\nBusco tarea 2: %s\n", arbol_buscar(arbol, tareas[1])!=NULL?PASSED:FAILED);
	mostrar_tareas((tarea_t*)arbol_buscar(arbol, tareas[1]));
	printf("\nBusco tarea 3: %s\n", arbol_buscar(arbol, tareas[2])!=NULL?PASSED:FAILED);
	mostrar_tareas((tarea_t*)arbol_buscar(arbol, tareas[2]));
	printf("\nBusco tarea 4: %s\n", arbol_buscar(arbol, tareas[3])!=NULL?PASSED:FAILED);
	mostrar_tareas((tarea_t*)arbol_buscar(arbol, tareas[3]));
	printf("\nBusco tarea 5: %s\n", arbol_buscar(arbol, tareas[4])!=NULL?PASSED:FAILED);
	mostrar_tareas((tarea_t*)arbol_buscar(arbol, tareas[4]));
	printf("\nBusco tarea 6: %s\n", arbol_buscar(arbol, tareas[5])!=NULL?PASSED:FAILED);
	mostrar_tareas((tarea_t*)arbol_buscar(arbol, tareas[5]));
	printf("\nBusco tarea 7: %s\n", arbol_buscar(arbol, tareas[6])!=NULL?PASSED:FAILED);
	mostrar_tareas((tarea_t*)arbol_buscar(arbol, tareas[6]));
	printf("\nBusco tarea 8: %s\n", arbol_buscar(arbol, tareas[7])!=NULL?PASSED:FAILED);
	mostrar_tareas((tarea_t*)arbol_buscar(arbol, tareas[7]));
	printf("\nBusco tarea 9: %s\n", arbol_buscar(arbol, tareas[8])!=NULL?PASSED:FAILED);
	mostrar_tareas((tarea_t*)arbol_buscar(arbol, tareas[8]));
	printf("\nBusco tarea 10: %s\n", arbol_buscar(arbol, tareas[9])!=NULL?PASSED:FAILED);
	mostrar_tareas((tarea_t*)arbol_buscar(arbol, tareas[9]));
	printf("\nMuestro la raiz: %s\n", arbol_raiz(arbol)!=NULL?PASSED:FAILED);
	mostrar_tareas((tarea_t*)arbol_raiz(arbol));
}

void probar_recorridos(abb_t* arbol){
	int tope_menor = 4;
	int tope_igual = 10; 
	int tope_mayor = 12;
	tarea_t** array_menor = calloc(tope_menor, sizeof(tarea_t**));
	tarea_t** array_mayor = calloc(tope_mayor, sizeof(tarea_t**));
	tarea_t** array_igual = calloc(tope_igual, sizeof(tarea_t**));
	
	printf(COLOR_CYAN"\n/***INORDEN***\\\n"COLOR_NORMAL);
	printf("\nInorden: elementos > tope_vector: %s\n", arbol_recorrido_inorden(arbol, (void*)array_menor, tope_menor)==tope_menor?PASSED:FAILED);
	printf("\nInorden: elementos < tope_vector: %s\n", arbol_recorrido_inorden(arbol, (void*)array_mayor, tope_mayor)<tope_mayor?PASSED:FAILED);
	printf("\nInorden: elementos = tope_vector: %s\n", arbol_recorrido_inorden(arbol, (void*)array_igual, tope_igual)==tope_igual?PASSED:FAILED);

	printf(COLOR_CYAN"\n/***PREORDEN***\\\n"COLOR_NORMAL);
	printf("\nPreorden: elementos > tope_vector: %s\n", arbol_recorrido_preorden(arbol, (void*)array_menor, tope_menor)==tope_menor?PASSED:FAILED);
	printf("\nPreorden: elementos < tope_vector: %s\n", arbol_recorrido_preorden(arbol, (void*)array_mayor, tope_mayor)<tope_mayor?PASSED:FAILED);
	printf("\nPreorden: elementos = tope_vector: %s\n", arbol_recorrido_preorden(arbol, (void*)array_igual, tope_igual)==tope_igual?PASSED:FAILED);
	
	printf(COLOR_CYAN"\n/***POSTORDEN***\\\n"COLOR_NORMAL);
	printf("\nPostorden: elementos > tope_vector: %s\n", arbol_recorrido_postorden(arbol, (void*)array_menor, tope_menor)==tope_menor?PASSED:FAILED);
	printf("\nPostorden: elementos < tope_vector: %s\n", arbol_recorrido_postorden(arbol, (void*)array_mayor, tope_mayor)<tope_mayor?PASSED:FAILED);
	printf("\nPostorden: elementos = tope_vector: %s\n", arbol_recorrido_postorden(arbol, (void*)array_igual, tope_igual)==tope_igual?PASSED:FAILED);

	printf(COLOR_CYAN"\n/***INORDEN CON CADA ELEMENTO***\\\n"COLOR_NORMAL);
	int acumulador = 0;
	abb_con_cada_elemento(arbol, ABB_RECORRER_INORDEN, mostrar_elemento_acumulado, &acumulador);
	printf("\nRecorro inorden contando los elementos: %s\n", acumulador==10?PASSED:FAILED);
	
	acumulador = 0;
	abb_con_cada_elemento(arbol, ABB_RECORRER_INORDEN, mostrar_hasta_tarea, &acumulador);
	printf("\nRecorro inorden hasta tarea especifica: %s\n", acumulador==5?PASSED:FAILED);
	
	printf(COLOR_CYAN"\n/***PREORDEN CON CADA ELEMENTO***\\\n"COLOR_NORMAL);
	acumulador = 0;
	abb_con_cada_elemento(arbol, ABB_RECORRER_PREORDEN, mostrar_elemento_acumulado, &acumulador);
	printf("\nRecorro preorden contando los elementos: %s\n", acumulador==10?PASSED:FAILED);
	
	acumulador = 0;
	abb_con_cada_elemento(arbol, ABB_RECORRER_PREORDEN, mostrar_hasta_tarea, &acumulador);
	printf("\nRecorro preorden hasta tarea especifica: %s\n", acumulador==5?PASSED:FAILED);

	printf(COLOR_CYAN"\n/***POSTORDEN CON CADA ELEMENTO***\\\n"COLOR_NORMAL);
	acumulador = 0;
	abb_con_cada_elemento(arbol, ABB_RECORRER_POSTORDEN, mostrar_elemento_acumulado, &acumulador);
	printf("\nRecorro postorden contando los elementos: %s\n", acumulador==10?PASSED:FAILED);
	
	acumulador = 0;
	abb_con_cada_elemento(arbol, ABB_RECORRER_POSTORDEN, mostrar_hasta_tarea, &acumulador);
	printf("\nRecorro postorden hasta tarea especifica: %s\n", acumulador==5?PASSED:FAILED);

	free(array_menor);
	free(array_mayor);
	free(array_igual);
}

tarea_t inicializar_tarea(tarea_t* tarea, tarea_t* t){
	tarea->dia = t->dia;
	tarea->mes = t->mes;
	tarea->desc = t->desc;
	return *tarea;
}

void probar_borrado(abb_t* arbol, tarea_t** tareas){
	tarea_t tarea_1 = inicializar_tarea(&tarea_1, tareas[0]);
	tarea_t tarea_2 = inicializar_tarea(&tarea_2, tareas[1]);
	tarea_t tarea_3 = inicializar_tarea(&tarea_3, tareas[2]);
	tarea_t tarea_4 = inicializar_tarea(&tarea_4, tareas[3]);
	tarea_t tarea_5 = inicializar_tarea(&tarea_5, tareas[4]);
	tarea_t tarea_6 = inicializar_tarea(&tarea_6, tareas[5]);
	tarea_t tarea_7 = inicializar_tarea(&tarea_7, tareas[6]);
	tarea_t tarea_8 = inicializar_tarea(&tarea_8, tareas[7]);
	tarea_t tarea_9 = inicializar_tarea(&tarea_9, tareas[8]);
	tarea_t tarea_10 = inicializar_tarea(&tarea_10, tareas[9]);
	
	printf("\nBorro nodo con rama derecha: %s\n", arbol_borrar(arbol, tareas[3])==EXITO&&arbol_buscar(arbol, &tarea_4)==NULL?PASSED:FAILED);
	printf("\nBorro nodo-hoja : %s\n", arbol_borrar(arbol, tareas[8])==EXITO&&arbol_buscar(arbol, &tarea_9)==NULL?PASSED:FAILED);
	printf("\nAhora el arbol tiene 8 elementos: %s\n", contador_nodos(arbol->nodo_raiz)==8?PASSED:FAILED);
	printf("\nBorro nodo con rama izquierda: %s\n", arbol_borrar(arbol, tareas[5])==EXITO&&arbol_buscar(arbol, &tarea_6)==NULL?PASSED:FAILED);
	printf("\nBorro nodo-raiz: %s\n", arbol_borrar(arbol, tareas[0])==EXITO&&arbol_buscar(arbol, &tarea_1)==NULL?PASSED:FAILED);
	printf("\nAhora el arbol tiene 6 elementos: %s\n", contador_nodos(arbol->nodo_raiz)==6?PASSED:FAILED);
	printf("\nBorro nodo-hoja: %s\n", arbol_borrar(arbol, tareas[6])==EXITO&&arbol_buscar(arbol, &tarea_7)==NULL?PASSED:FAILED);
	printf("\nBorro nodo-hoja: %s\n", arbol_borrar(arbol, tareas[7])==EXITO&&arbol_buscar(arbol, &tarea_8)==NULL?PASSED:FAILED);
	printf("\nAhora el arbol tiene 4 elementos: %s\n", contador_nodos(arbol->nodo_raiz)==4?PASSED:FAILED);
	printf("\nBorro nodo con rama derecha: %s\n", arbol_borrar(arbol, tareas[2])==EXITO&&arbol_buscar(arbol, &tarea_3)==NULL?PASSED:FAILED);
	printf("\nBorro nodo-raiz: %s\n", arbol_borrar(arbol, tareas[1])==EXITO&&arbol_buscar(arbol, &tarea_2)==NULL?PASSED:FAILED);
	printf("\nAhora el arbol tiene 2 elementos: %s\n", contador_nodos(arbol->nodo_raiz)==2?PASSED:FAILED);
		
}

void probar_null(){
	int i = 1;
	int* array[5];

	printf(COLOR_CYAN"\n/***CREACION***\\\n"COLOR_NORMAL);
	
	abb_t* arbol_destructor_null;
	printf("\nCreo arbol con destructor NULL: %s\n", (arbol_destructor_null = arbol_crear(comparar_tareas, NULL))!=NULL?PASSED:FAILED);
	
	abb_t* arbol_comparador_null;
	printf("\nCreo arbol con comparador NULL: %s\n", (arbol_comparador_null = arbol_crear(NULL, NULL))==NULL?PASSED:FAILED);
	
	printf(COLOR_CYAN"\n/***INSERCION***\\\n"COLOR_NORMAL);

	printf("\nInserto elemento en arbol NULL: %s\n", arbol_insertar(NULL, &i)==ERROR?PASSED:FAILED);
	
	abb_t* arbol_prueba;
	printf("\nInserto elemento NULL: %s\n", arbol_insertar((arbol_prueba = arbol_crear(comparar_tareas, destruir_tareas)), NULL)==EXITO?PASSED:FAILED);
	
	printf(COLOR_CYAN"\n/***BUSQUEDA***\\\n"COLOR_NORMAL);
	
	printf("\nBusco elemento en arbol NULL: %s\n", arbol_buscar(NULL, &i)==NULL?PASSED:FAILED);
	printf("\nBusco elemento NULO: %s\n", arbol_buscar(arbol_prueba, NULL)==NULL?PASSED:FAILED);
	
	printf(COLOR_CYAN"\n/***BORRADO***\\\n"COLOR_NORMAL);
	
	printf("\nBusco elemento de arbol NULL: %s\n", arbol_buscar(NULL, &i)==NULL?PASSED:FAILED);
	printf("\nBorro elemento NULL: %s\n", arbol_borrar(arbol_prueba, NULL)==EXITO&&arbol_buscar(arbol_prueba, NULL)==NULL?PASSED:FAILED);
	
	printf(COLOR_CYAN"\n/***RECORRIDOS***\\\n"COLOR_NORMAL);
	
	printf("\nRecorro inorden en arbol NULL: %s\n", arbol_recorrido_inorden(NULL, (void**)array, 5)==0?PASSED:FAILED);
	printf("\nRecorro preorden en arbol NULL: %s\n", arbol_recorrido_preorden(NULL, (void**)array, 5)==0?PASSED:FAILED);
	printf("\nRecorro postorden en arbol NULL: %s\n", arbol_recorrido_postorden(NULL, (void**)&array, 5)==0?PASSED:FAILED);

	arbol_destruir(arbol_prueba);
	free(arbol_destructor_null);
}

tarea_t** generar_tareas(int cantidad){
	tarea_t** prueba = calloc(cantidad, sizeof(tarea_t**));
	int i = 0;
	int j = cantidad;
	while(i < cantidad){
		prueba[i] = crear_tarea(i+1, j-i, "Prueba");
		i++;
		j--;
	}
	return prueba;
}


void probar_volumen(){
	abb_t* arbol_volumen = arbol_crear(comparar_tareas, destruir_tareas);
	int cantidad = 1000;
	tarea_t** volumen = generar_tareas(cantidad);
	int tope = cantidad;

	bool ok = true;	
	for(int i = 0; i < tope; i++){
		if(arbol_insertar(arbol_volumen, volumen[i])==ERROR)
			ok = false;
	}

	printf("\nInserto %i elementos: %s\n", cantidad, ok==true?PASSED:FAILED);
	
	ok = true;
	for(int i = 0; i < cantidad; i+=2){
		if(arbol_borrar(arbol_volumen, volumen[tope - 1 - i])==ERROR)
			ok = false;
	}
	printf("\nElimino %i elementos: %s\n", cantidad/2, ok==true&&contador_nodos(arbol_volumen->nodo_raiz)==cantidad/2?PASSED:FAILED);

	arbol_destruir(arbol_volumen);
	free(volumen);
}

void probar_tester(){
	/*Esto es un invento que estoy probando como hacer*/
	tester_t* tester = createNewTester();
	
	
	abb_t* arbol_tester = arbol_crear(comparar_tareas, destruir_tareas);

	tarea_t* tarea_1 = crear_tarea(5, 6, "Crear un tester");
	tarea_t* tarea_2 = crear_tarea(11, 5, "Andara bien esto?");
	tarea_t* tarea_3 = crear_tarea(12, 12, "Espero que si");
	
	/*Ver como hacer para no tener que declarar las variables resultado y exito siempre*/
	
	createNewCategory(tester, "PRUEBAS DE INSERCION");	
	
	int exito = 0;
	int error = -1;

	int result = arbol_insertar(arbol_tester, tarea_1);
	test(tester, "Inserto tarea 1", &result, &exito, compareInt);
	result = arbol_insertar(arbol_tester, tarea_2);
	test(tester, "Inserto tarea 2", &result, &exito, compareInt);
	result = arbol_insertar(arbol_tester, tarea_3);
	test(tester, "Inserto tarea 3", &result, &exito, compareInt);

	createNewCategory(tester, "PRUEBAS DE BUSQUEDA");	
	
	tarea_t* result_2;
	result_2 = (tarea_t*)arbol_buscar(arbol_tester, tarea_1);
	test(tester, "Busco tarea 1", result_2, tarea_1, compareTasks);
	result_2 = (tarea_t*)arbol_buscar(arbol_tester, tarea_2);
	test(tester, "Busco tarea 2", result_2, tarea_2, compareTasks);
	result_2 = (tarea_t*)arbol_buscar(arbol_tester, tarea_3);
	test(tester, "Busco tarea 3", result_2, tarea_3, compareTasks);

	createNewCategory(tester, "PRUEBAS DE BORRADO");	
	

	result = arbol_borrar(arbol_tester, tarea_1);
	test(tester, "Borro tarea 1", &result, &exito, compareInt);
	result = arbol_borrar(arbol_tester, tarea_2);
	test(tester, "Borro tarea 2", &result, &exito, compareInt);
	result = arbol_borrar(arbol_tester, tarea_3);
	test(tester, "Borro tarea 3", &result, &exito, compareInt);
	
	createNewCategory(tester, "PRUEBAS CON NULL");	
	

	result = arbol_borrar(NULL, tarea_1);
	test(tester, "Borro de arbol NULL", &result, &error, compareInt);
	result = arbol_insertar(NULL, tarea_2);
	test(tester, "Inserto en arbol NULL", &result, &error, compareInt);
	
	showResults(tester);

	arbol_destruir(arbol_tester);
	freeTester(tester);
}
	
int main(){
	abb_t* arbol = arbol_crear(comparar_tareas, destruir_tareas);
	tarea_t** tareas = calloc(10, sizeof(tarea_t));
	
	tareas[0] = crear_tarea(12, 4, "Pasear al perro");
	tareas[1] = crear_tarea(28, 2, "Arreglar la heladera");
	tareas[2] = crear_tarea(1, 1, "Ir al super");
	tareas[3] = crear_tarea(30, 7, "Retirar plata");
	tareas[4] = crear_tarea(3, 2, "Comprar verdura");
	tareas[5] = crear_tarea(17, 12, "Hacer una pizza");
	tareas[6] = crear_tarea(28, 8, "Examen de Algo2");
	tareas[7] = crear_tarea(14, 10, "Tomar unos mates");
	tareas[8] = crear_tarea(25, 8, "Hacer el asado");
	tareas[9] = crear_tarea(13, 3, "Pasar la aspiradora");

	printf(COLOR_AMARILLO"\n\n<--------PRUEBAS DE INSERCION--------->\n\n"COLOR_NORMAL);
	probar_insercion(arbol, tareas);

	printf(COLOR_AMARILLO"\n\n<--------PRUEBAS DE BUSQUEDA--------->\n\n"COLOR_NORMAL);
	probar_busqueda(arbol, tareas);

	printf(COLOR_AMARILLO"\n\n<--------PRUEBAS DE RECORRIDOS--------->\n\n"COLOR_NORMAL);
	probar_recorridos(arbol);

	printf(COLOR_AMARILLO"\n\n<--------PRUEBAS DE BORRADO--------->\n\n"COLOR_NORMAL);
	probar_borrado(arbol, tareas);
	
	printf(COLOR_AMARILLO"\n\n<--------PRUEBAS CON NULL--------->\n\n"COLOR_NORMAL);
	probar_null(arbol, tareas);
	
	printf(COLOR_AMARILLO"\n\n<--------PRUEBAS DE VOLUMEN--------->\n\n"COLOR_NORMAL);
	probar_volumen();
	
	printf(COLOR_AMARILLO"\n\n<--------PRUEBAS MIXTAS (con el tester)--------->\n\n"COLOR_NORMAL);
	probar_tester();

	arbol_destruir(arbol);
	free(tareas);
	return 0;
}
