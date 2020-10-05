// David Barrios Portales
// davidbarrios@usal.es
// Ranas saltarinas.


	//COMPILAR     gcc -o rana rana.c

	//EJECUTAR     ./rana



/*
	EXPLICACION TEORICA.

	Se inspira en el comportamiento de las ranas en busca de alimento. Busca la ubicacion con la cantidad maxima de alimento disponible.

	Hay un conjunto de R ranas, cada una representa una solucion al problema, La calidad o fitness.

	La poblacion de RANAS se divide en m subconjuntos, denominados memeplexes, del mismo tamanio.

	Cada memeplex realiza una busqueda propia de los algoritmos memeticos.
	 ( Un algoritmo memetico es aqui el realiza una busqueda heuristica de la solucion de un conjunto de agentes que alteranan etapas de auto-mejora, con etapas de cooperacion y competicion)
	
	las ranas de cada memeplex mejoran sus posiciones para tener mas alimento (mejor solucion)

	Tras un numero dado de pasos de evolucion memetica, se recombinan todos los memeplex

	Se utiliza la info obtenida por los distintos memeplex para mejorar la solucion global encontrada por el conjunto ranas.





*/






	/*
	Ejemplo  >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
	int NM = 5;		// Ranas en cada memeplex
	int M = 2;		// Número de memeplexes.
	int R = 2;
	int I = 10;		// Iteracciones
	float minima_distancia = -5.12;
	float maxima_distancia = 5.12;
	int Jmax = 10;
	float Dmax = 1;
	*/




/*
FUNDAMENTOS DEL ALGORITMO:

Combina:
    -Busqueda local

    -Busqueda global (Intercambio global de informacion)
*/

/*
ALGORITMO:

REPETIR
    Calcular el fitness de cada rana
    Ordenar la población por fitness dereciente
    Dividir en m memeplexes
    Procesar cada memeplax
    Combinar todos los memeplex
HASTA (condicion de parada)

Devolver la mejor solución de parada.
*/



/*


Crear la poblacion >>> Se crea aleatoriamente la poblacion de ranas.

Calcular el fitness de cada rana >>>  Se calcula en funcion al objetivo del problema.

Ordenar la poblacion en funcion del fitness decreciente >>> 

Dividir la poblacion en m memeplexes >>> 

Procesar cada memeplex >>> Se realiza una busqueda local en cada memeplex, intentado mejorar su peor rana de forma iterativa. Se determina la mejor y peor rana.

Combinar los memeplexes >>> Se vuelven a unir las ranas de todos los memeplexes en un solo grupo. 



*/


// |||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
// |||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
// |||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
// |||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||



// Librerías que se van a usar en el programa.
#include <stdio.h>
#include <stdlib.h>
#include <time.h>			// Para generar numeros aleatorios
#include <float.h>			// Para trabajar con float
// Definimos constantes de los datos por defecto.
#define NM_defecto 5
#define M_defecto 2
#define R_defecto 2
#define I_defecto 10
#define maxima_distancia_defecto 5.12
#define minima_distancia_defecto -5.12
#define Jmax_defecto 10
#define Dmax_defecto 1.0


	/*
	Ejemplo  >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
	int NM = 5;		// Ranas en cada memeplex
	int M = 2;		// Número de memeplexes.
	int R = 2;
	int I = 10;		// Iteracciones
	float minima_distancia = -5.12;
	float maxima_distancia = 5.12;
	int Jmax = 10;
	float Dmax = 1.0;
	*/


// Estructura que usamos para la RANA
struct rana {
	float *posicion;	//Puntero a la posicion
	float fitness;		//Fitness de cada rana
};

typedef struct rana RANA;	// Definicion la de estructura rana RANA


// Prototipos-----------------------------------------------------------------------------------------------------------------------

// Introducimos los datos por teclado:
int introducir_numero_ranas_en_memeplex ();		// El usuario introduce el numero de ranas en cada memeplex
int introducir_numero_de_memeplexes ();			// Introduce el numero de memeplexes
int introducir_numero_dimensiones ();			// El usuario introduce el numero de dimensiones 
int introducir_numero_iteracciones ();			// El usuario introduce el numero de iteracciones 
float introducir_minima_dimension ();
float introducir_maxima_dimension ();
int pasos_evolucion_Jmax ();					// SPasos de evolucion que se van a llevar a cabo en cada memeplex. 
float introducir_cambio_maximo_permitido ();	// cambio maximo permitido de cada memeplex

// Generamos la poblacion de ranas:
RANA *generar_poblacion (int n, int R, float minima_distancia, float maxima_distancia);			// Genera la poblacion de ranas
void repartir_ranas (RANA *poblacion, int n, int R, float minima_distancia, float maxima_distancia);		// reparte a las ranas 
void calcular_fitness (RANA *poblacion, int n, int R, float minima_distancia, float maxima_distancia);		// Calcula el fitness de cada rana en funcion de la funcion objetivo
void ordenar_funcion_mejor_fitness (RANA *poblacion, int N, int R, RANA *mejor);		// Ordena en funcion de un fitness mejor
void ordenar_fitness (RANA *poblacion, int N, int R);
void encontrar_mejor_rana (RANA *poblacion, int N, int R, RANA *mejor);			// Encuentra la mejor rana (Y las coordenadas de esta.)
void funcion_memeplexizadora (RANA *poblacion, int N, int M, RANA **memeplexes);			// divide a la poblacion de ranas en tantos memeplexes 
void procesar_memeplexes (RANA **memeplexes, int N, int R, int M, float minima_distancia, float maxima_distancia, RANA *mejor, int Jmax, float Dmax);	// Procesa los memeplexes para buscar una mejor solucion al problema general.
void determinar_mejor_peor_rana (int R, RANA *memeplex, int tamano, float minima_distancia, float maxima_distancia, RANA *mejor, float Dmax);  // Determina la mejor y la peor RANA que le pasemos como parametro.
void mejorar_peor_rana (int R, RANA *memeplex, int tamano, float minima_distancia, float maxima_distancia, RANA *mejor, float Dmax, RANA mejor_memeplex, RANA peor_memeplex, int posicion_peor_memeplex);
void combinar_memeplexes (RANA *poblacion, int N, int M, RANA **memeplexes, int R, RANA *mejor);	// Vuelve a combinar a las ranas para que formen parte de una poblacion. Muestra la solucion en la ultima iteraccion.
void liberar_memoria (RANA *poblacion, int N, int M, RANA **memeplexes);		// liberamos memoria
float genera_real_random (float min, float max);		// Generamos un real
void mensaje_ultimo();			// muestra un mensaje de que se ha encontrado una solucion



// ---------------------------------------------------------------------------------------------------------------------------------------------
// FUNCION MAIN
void main (){


	srand (time (NULL));	// Semilla para generar numeros aleatorios.



	// Variables -------------------------------------------------------------

	// Solicitamos al usuario que introduzca sus valores. 
	int NM = introducir_numero_ranas_en_memeplex ();
	int M = introducir_numero_de_memeplexes ();
	int R = introducir_numero_dimensiones ();
	int I = introducir_numero_iteracciones ();
	float maxima_distancia = introducir_maxima_dimension ();
	float minima_distancia = introducir_minima_dimension ();
	int Jmax = pasos_evolucion_Jmax ();
	int Dmax = introducir_cambio_maximo_permitido ();



	int num_ranas= M * NM;		// Numero total de ranas en la poblacion
								// Es el numero de memeplexes multiplicado por el numero de ranas por cada memeplex.
	//Imprimimos el numero de ranas totales.


	printf("\n\n\n ========================================================\n");

	printf("\n El numero total de ranas es de: %d\n", num_ranas);		// Mostramos el numero total de ranas.

	printf("\n ========================================================\n\n\n");


	// Iniciamos y reservamos memoria para la mejor rana. -----------------------------------------------------------------------------
	RANA mejor;	// Mejor rana
	mejor.fitness = FLT_MAX;	// Iniciamos el fitness de la mejor rana (estructura mejor, campo fitness)
	// Usamos FLT_MAX para cargar en el fitness el mayor valor posible y asi al compararlo la primera vez, guardar el primer fitness para luego ya seguir comparando.
	mejor.posicion = (float *) malloc (R * sizeof (float));  // Reservamos memoria
	if (mejor.posicion == NULL)		// Si no es posible reservar memoria entonces salimos del programa
	{
		printf ("\n Error. No se ha podido reservar memoria");	// Mostramos mensaje por pantalla
		exit (0);	// Salimos.
	}



	// Inicializamos los memeplexes
	RANA **memeplexes = (RANA **) malloc (M * sizeof (RANA *));	// Inicialización de los memeplexes.

	if (memeplexes == NULL)		// Si no reserva memoria correctamente 
	{
		printf ("\n Error . No se ha podido reservar memoria.");	// mostramos un mensaje de error
		exit (1);	// Salimos
	}

	// Vamos reservando memoria desde 0 hasta M para los memeplexes
	for (int i = 0; i < M; i++)
	{
		memeplexes[i] = (RANA *) malloc (NM * sizeof (RANA));
		if (memeplexes[i] == NULL)
		{
			printf ("\n Error . No se ha podido reservar memoria.");
			exit (2);	// Mostramos un codigo de error
		}
	}

	// Por ultimo reservamos memoria desde 0 hasta M
	for (int h = 0; h < M; h++)
	{
		// para (num_ranas) ranas
		for (int i = 0; i < num_ranas; i++)
		{
			memeplexes[h][i].posicion = (float *) malloc (R * sizeof (float));

			if (memeplexes[h][i].posicion == NULL)		// Comprobamos cada posicion cada vez que reservamos memoria y si no se ha reservado correctamente imprimimos un mensaje de error y salimos con un codigo de error diferente.
			{
				printf ("\n Error . No se ha podido reservar memoria.");
				exit (3);
			}
		}
	}



	// Generamos la poblacion de ranas de tipo RANA

	// Generamos la poblacion
	RANA *poblacion = generar_poblacion (num_ranas, R, minima_distancia, maxima_distancia);


	int contador = 0;
	int contador_2 = 0;

// Recorremos desdes 0 hasta el numero de ranas maximo

	for (int i = 0; i < num_ranas; i++)
	{
		memeplexes[contador][contador_2] = poblacion[i];

		contador++;

		// Para que en cada ronda una rana vaya a distinto grupo de la anterior.

		if (contador == M)		// sin contador es igual al numero de memeplexes
		{
			contador = 0;		// ponemos el contador a 0
		}

		// Para ir poniendo las ranas en cada posicion de cada memeplexe.
		if (((i + 1) % M) == 0)		// si el resto del contador + 1 entre el numero de memeplexes es 0 entonces incrementamos el contador 2
		{
			contador_2++;
		}

		
	}


	//      RESOLUCION DEL PROBLEMA: 
	//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
	//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
	//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
	//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
	//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
	//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
	//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
	//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>



	do{		// Hacemos esto I veces (numero maximo de iteraciones)
		

		// Calculamos el fitness

		calcular_fitness (poblacion, num_ranas, R, minima_distancia, maxima_distancia);		// Se le pasa como parametros la poblacion, el numero de ranas, numero de dimensiones, y las distancias minimas y maximas

		// Ordenamos el fitness 
		ordenar_funcion_mejor_fitness (poblacion, num_ranas, R, &mejor);	// le pasamos la poblacion, el numero de ranas, la dimension y la posicion en memoria de la mejor.

		// Divide la poblacion de ranas en M memeplexes.

		funcion_memeplexizadora (poblacion, num_ranas, M, memeplexes);	// Le pasamos la poblacion, el numero de ranas, el numero de memeplexes y los memeplexes

		// Procesa los memeplexes para buscar una mejor solucion al problema general.

		procesar_memeplexes (memeplexes, NM, R, M, minima_distancia, maxima_distancia, &mejor, Jmax, Dmax);

		// Modulo que combina los memeplexes para que todas las ranas vuelvan a ser de una misma poblacion.
		// Al final de este modulo se muestra la mejor solución encontrada hasta ahora.

		combinar_memeplexes (poblacion, num_ranas, M, memeplexes, R, &mejor);

		I--;	// Decrementamos 1 a I

	} while (I > 0);	// Repetimos esto esta que I>0, es decir el numero de iteracciones que hemos puesto al comienzo del programa.




	//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
	//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
	//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
	//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
	//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
	//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
	//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
	//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
	


	printf ("\n\n");

	mensaje_ultimo();


	liberar_memoria (poblacion, num_ranas, M, memeplexes);




}





















// -----------------------------------------------------------------------------------------------------------------------------
// Solicitamos el numero de ranas al usuario
int introducir_numero_ranas_en_memeplex ()
{
	int NM;

	printf ("\n Introduzca el numero de ranas de cada memeplex: ");
	scanf ("%d", &NM);

	if(NM==0){		// si introducimos un dato no valido se aplica el valor por defecto.
		
		printf("\n\t Se aplica el valor por defecto %d\n\n", NM_defecto);		
	
		return NM_defecto;
	}

	return NM;
}

// -----------------------------------------------------------------------------------------------------------------------------
// Solicitamos el numero de memeplexes
int introducir_numero_de_memeplexes ()
{
	int M;

	printf (" Introduzca el numero de memeplexes en el que se va a dividir la poblacion: ");
	scanf ("%d", &M);


		if(M==0){		// si introducimos un dato no valido se aplica el valor por defecto.
		
		printf("\n\t Se aplica el valor por defecto %d\n\n", M_defecto);		
	
		return M_defecto;
	}

	return M;
}

// -----------------------------------------------------------------------------------------------------------------------------
//Solicitamos el numero dimensiones en el que se va a trabajar.
int introducir_numero_dimensiones ()
{
	int R;

	printf (" Introduzca el numero de dimensiones del problema: ");
	scanf ("%d", &R);


	if(R==0){		// si introducimos un dato no valido se aplica el valor por defecto.
		
		printf("\n\t Se aplica el valor por defecto %d\n\n", R_defecto);		
	
		return R_defecto;
	}


	return R;
}

// -----------------------------------------------------------------------------------------------------------------------------
// Solicitamos el numero de iteracciones.
int introducir_numero_iteracciones ()
{
	int I;

	printf (" Introduzca el numero de iteraciones del problema: ");
	scanf ("%d", &I);

	if(I==0){		// si introducimos un dato no valido se aplica el valor por defecto.
		
		printf("\n\t Se aplica el valor por defecto %d\n\n", I_defecto);		
	
		return I_defecto;
	}



	return I;
}

// -----------------------------------------------------------------------------------------------------------------------------
// Minimo espacio que puede tomar cada dimension.
float introducir_minima_dimension ()
{
	float minima_distancia;

	printf (" Introduzca el mínimo espacio de operación de cada una de las dimensiones: ");
	scanf ("%f", &minima_distancia);

	if(minima_distancia==0){		// si introducimos un dato no valido se aplica el valor por defecto.
		
		printf("\n\t Se aplica el valor por defecto %f\n\n", minima_distancia_defecto);		
	
		return minima_distancia_defecto;
	}



	return minima_distancia;
}

// -----------------------------------------------------------------------------------------------------------------------------
// Lo mismo pero para la maxima
float introducir_maxima_dimension ()
{
	float maxima_distancia;

	printf (" Introduzca el máximo espacio de operación de cada una de las dimensiones: ");
	scanf ("%f", &maxima_distancia);

	if(maxima_distancia==0){		// si introducimos un dato no valido se aplica el valor por defecto.
		
		printf("\n\t Se aplica el valor por defecto %f\n\n", maxima_distancia_defecto);		
	
		return maxima_distancia_defecto;
	}

	return maxima_distancia;
}

// -----------------------------------------------------------------------------------------------------------------------------

int pasos_evolucion_Jmax ()
{
	int Jmax;

	// Pasos de evolucion que se van a llevar a cabo en cada memeplex.
	printf (" Introduzca los pasos de evolución de cada memeplex: ");
	scanf ("%d", &Jmax);


	if(Jmax==0){		// si introducimos un dato no valido se aplica el valor por defecto.
		
		printf("\n\t Se aplica el valor por defecto %d\n\n", Jmax_defecto);		
	
		return Jmax_defecto;
	}

	return Jmax;
}


// -----------------------------------------------------------------------------------------------------------------------------
// Se pide el cambio maximo permitido de cada memeplex

float introducir_cambio_maximo_permitido ()
{
	float Dmax;

	printf (" Introduzca el cambio maximo permitido de cada memeplex: ");
	scanf ("%f", &Dmax);

	if(Dmax==0){		// si introducimos un dato no valido se aplica el valor por defecto.
		
		printf("\n\t Se aplica el valor por defecto %f\n\n", Dmax_defecto);		
	
		return Dmax_defecto;
	}

	return Dmax;
}




// -----------------------------------------------------------------------------------------------------------------------------
// Se genera la poblacion inicial de RANAS
//num_ranas--> Número de ranas de la población.


RANA *generar_poblacion (int n, int R, float minima_distancia, float maxima_distancia)	
{
	RANA *poblacion = (RANA *) malloc (n * sizeof (RANA));
	if (poblacion == NULL)
	{
		printf ("\n Error al intentar reservar memoria.");
		exit (4);
	}

	// Se distribuyen las luciérnagas en el espacio posible del problema.
	repartir_ranas (poblacion, n, R, minima_distancia, maxima_distancia);						

	return poblacion;
}



// -----------------------------------------------------------------------------------------------------------------------------

// Se distribuyen las ranas en el espacio posible del problema.
// R --> numero de dimensiones predefinido
void repartir_ranas (RANA *poblacion, int n, int R, float minima_distancia, float maxima_distancia)
{
	// Se declaran los arrays para la posición de cada una de las ranas.
	for (int i = 0; i < n; i++)
	{
		poblacion[i].posicion = (float *) malloc (R * sizeof (float));
		if (poblacion[i].posicion == NULL)
		{
			printf ("\n Error. No se ha podido reservar memoria.");
			exit (5);
		}
	}

	// A cada una de las dimensiones de cada rana se le asigna un valor aleatorio comprendido dentro del espacio del problema.
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < R; j++)
		{
			// Se pasa un real aleatorio en el espacio comprendido.
			poblacion[i].posicion[j] = genera_real_random (minima_distancia, maxima_distancia);
		}
	}
}




// -----------------------------------------------------------------------------------------------------------------------------
// Se calcula el firness del programa en funcion del objetivo del problema.
void calcular_fitness (RANA *poblacion, int n, int R, float minima_distancia, float maxima_distancia)
{
	float contador;

	// Primer bucle para recorrer toda la poblacion de ranas.
	for (int i = 0; i < n; i++)
	{
		contador = 0;

		for (int j = 0; j < R; j++)
		{
			// Para calcular el fitness de cada rana se hace el cuadrado de la posicion de la primera dimension en este caso.
			contador = contador + (poblacion[i].posicion[j] * poblacion[i].posicion[j]);
		}

		poblacion[i].fitness = contador;
	}
}



// -----------------------------------------------------------------------------------------------------------------------------
// Modulo para ordenar en funcion del fitness
void ordenar_funcion_mejor_fitness (RANA *poblacion, int num_ranas, int R, RANA *mejor)
{
	ordenar_fitness (poblacion, num_ranas, R);					// LLama a una funcion que ordena el fitness de las ranas.
	encontrar_mejor_rana (poblacion, num_ranas, R, mejor);	// Encuentra la rana con mejor fitness
	// Tambien guarda la posicion de la mejor rana		
}



// -----------------------------------------------------------------------------------------------------------------------------
// Modulo para ordenar el fitness

void ordenar_fitness (RANA *poblacion, int num_ranas, int R)
{
	// Declaración de variables.
	int i;
	int j;	// Auxiliares
	RANA t;	

	// Recorremos todas las ranas de forma inversa y vamos ordenando por el fitness
	for (j = num_ranas+ 1; j > 2; j--)
	{
		for (i = 0; i < j - 1 - 1; i++)
		{
			if (poblacion[i].fitness > poblacion[i + 1].fitness)
			{
				t = poblacion[i];
				poblacion[i] = poblacion[i + 1];
				poblacion[i + 1] = t;
			}
		}
	}
}


// -----------------------------------------------------------------------------------------------------------------------------
// Una vez ordenados los fitness el mejor fitness es el que nos interesa

void encontrar_mejor_rana (RANA *poblacion, int n, int R, RANA *mejor)
{
	if (mejor->fitness > poblacion[0].fitness)
	{
		mejor->fitness = poblacion[0].fitness;		
		for (int v = 0; v < R; v++)
		{
			mejor->posicion[v] = poblacion[0].posicion[v]; // Es lo mismo que escribir: (*PUNTERO).ATRIBUTO
			// En este caso guardamos el valor de mejor en el puntero posicion[v]
		}		
	}
}


// -----------------------------------------------------------------------------------------------------------------------------
// Divide la poblacion de ranas en M memeplexes.

void funcion_memeplexizadora (RANA *poblacion, int N, int M, RANA **memeplexes)
{
	int contador = 0;
	int contador_2 = 0;


	for (int i = 0; i < N; i++)
	{
		memeplexes[contador][contador_2].fitness = poblacion[i].fitness;
		for (int j = 0; j < 3; j++)
		{
			memeplexes[contador][contador_2].posicion[j] = poblacion[i].posicion[j];
		}


		contador++;

		// Para que en cada ronda una rana vaya a distinto grupo de la anterior.
		if (contador == M)
		{
			contador = 0;
		}

		// Para ir poniendo las ranas en cada posicion de cada memeplexe.
		if (((i + 1) % M) == 0)
		{
			contador_2++;
		}

		
	}
}



// -----------------------------------------------------------------------------------------------------------------------------
// Procesa los memeplexes para buscar una mejor solucion al problema general.

void procesar_memeplexes (RANA **memeplexes, int NM, int R, int M, float minima_distancia, float maxima_distancia, RANA *mejor, int Jmax, float Dmax)
{
	for (int i = 0; i < M; i++)
	{
		do
		{
			determinar_mejor_peor_rana (R, memeplexes[i], NM, minima_distancia, maxima_distancia, mejor, Dmax);

			Jmax--;
		} while (Jmax > 1);
	}
}


// -----------------------------------------------------------------------------------------------------------------------------

// Modulo para determinar la mejor y la peor rana del memeplex pasado como parametro

void determinar_mejor_peor_rana (int R, RANA *memeplex, int NM, float minima_distancia, float maxima_distancia, RANA *mejor, float Dmax)
{
	RANA mejor_memeplex;
	RANA peor_memeplex;
	int posicion_peor_memeplex;

	mejor_memeplex.fitness = FLT_MAX;
	peor_memeplex.fitness = 0;

	for (int i = 0; i < NM; i++)
	{
		if (memeplex[i].fitness < mejor_memeplex.fitness)
		{
			mejor_memeplex = memeplex[i];
		}

		else
		{
			if (memeplex[i].fitness > peor_memeplex.fitness)
			{
				peor_memeplex = memeplex[i];
				posicion_peor_memeplex = i;
			}
		}
	}

	mejorar_peor_rana (R, memeplex, NM, minima_distancia, maxima_distancia, mejor, Dmax, mejor_memeplex, peor_memeplex, posicion_peor_memeplex);
}


// -----------------------------------------------------------------------------------------------------------------------------

// Esta es la funcion de mover las ranas (actualizar la posicion).
void mejorar_peor_rana (int R, RANA *memeplex, int NM, float minima_distancia, float maxima_distancia, RANA *mejor, float Dmax, RANA mejor_memeplex, RANA peor_memeplex, int posicion_peor_memeplex)
{
	RANA peor_prima;
	peor_prima.posicion = (float *) malloc (R * sizeof (float));	// Reservamos memoria
	if (peor_prima.posicion == NULL)
	{
		printf ("\n ERROR. No se ha podido reservar memoria.");
		exit (5);
	}

	peor_prima.fitness = 0;
	for (int t = 0; t < R; t++)
	{
		peor_prima.posicion[t] = 0;
	}


	float d = 0;

	for (int s = 0; s < R; s++)
	{
		d = genera_real_random (0.5, 1) * (mejor_memeplex.posicion[s] - peor_memeplex.posicion[s]);
		peor_prima.posicion[s] = peor_memeplex.posicion[s] + d;
	}

	float contador_fitness = 0;
	for (int s = 0; s < R; s++)
	{
		contador_fitness = contador_fitness + (peor_prima.posicion[s] * peor_prima.posicion[s]);
	}
	peor_prima.fitness = contador_fitness;




	if (peor_prima.fitness < peor_memeplex.fitness)
	{
		peor_memeplex = peor_prima;
	}

	else
	{
		d = genera_real_random (0, 1) * (mejor->fitness - peor_memeplex.fitness);
		peor_prima.fitness = peor_memeplex.fitness + d;

		if (peor_prima.fitness < peor_memeplex.fitness)
		{
			peor_memeplex = peor_prima;
		}

		else
		{
			// Una nueva solución aleatoria sustituye a la peor_memeplex (en las posiciones y se calcula luego el fitness a partir de las posiciones).
			for (int i = 0; i < R; i++)
			{
				peor_memeplex.posicion[i] = genera_real_random (minima_distancia, maxima_distancia);
			}

			int contador = 0;
			for (int j = 0; j < R; j++)
			{
				// Para calcular el fitness de cada rana se hace el cuadrado de la posición de la primera dimensión en este caso.
				contador = contador + (peor_memeplex.posicion[j] * peor_memeplex.posicion[j]);
			}
			peor_memeplex.fitness = contador;
		}
	}

	memeplex[posicion_peor_memeplex] = peor_memeplex;	
}



// -----------------------------------------------------------------------------------------------------------------------------



// Modulo que combina los memeplexes para que todas las ranas vuelvan a ser de una misma poblacion.
// Al final de este modulo se muestra la mejor solución encontrada hasta ahora.
// En la ultima iteraccion queda la solucion final.

void combinar_memeplexes (RANA *poblacion, int num_ranas, int M, RANA **memeplexes, int R, RANA *mejor)
{
	int NM =num_ranas/ M;


	int contador_1 = 0;
	int contador_2 = 0;

	for (int i = 0; i < num_ranas; i++)
	{

		poblacion[i].fitness = memeplexes[contador_1][contador_2].fitness;
		for (int j = 0; j < R; j++)
		{
			poblacion[i].posicion[j] = memeplexes[contador_1][contador_2].posicion[j];
		}


		contador_2++;


		// Para que en cada ronda una rana vaya a distinto grupo de la anterior.
		if (contador_2 == NM)
		{
			contador_2 = 0;
		}


		// Para ir poniendo las ranas en cada posicion de cada memeplexe.
		if ((i + 1) % (num_ranas / M) == 0)
		{
			contador_1++;
		}


	}

	for (int w = 0; w < num_ranas; w++)
	{
		if (mejor->fitness > poblacion[w].fitness)	// Si la solucion hasta el momento encontrada es peor, se cambia.
		{
			mejor->fitness = poblacion[w].fitness;
			for (int j = 0; j < R; j++)
			{
				mejor->posicion[R] = poblacion[w].posicion[R];
			}
		}
	}
	

	printf ("\n MEJOR FITNESS -->  %f  ", mejor->fitness);
	printf ("\n MEJOR POSICION --> ");
	for (int i = 0; i < R; i++)
	{
		printf (" %f ", mejor->posicion[i]);
	}
	printf("\n\n\n");
}






// Funcion para liberar la memoria dinamica -------------------------------------------------------------------------------------------------------------
void liberar_memoria (RANA *poblacion, int N, int M, RANA **memeplexes)
{
	// Se libera el array de posiciones de cada una de las ranas.
	for (int i = 0; i < N; i++)
	{
		free (poblacion[i].posicion);
	}

	// Se libera el array que contenía a las ranas.
	free (poblacion);


	// Se libera la matriz de memeplexes.
	// Se libera el array de posiciones de cada una de las ranas.
	for (int w = 0; w < M; w++)
	{
		for (int i = 0; i < M / N; i++)
		{
			free (memeplexes[w][i].posicion);
		}
	}

	// Se liberan cada uno de los memeplexes que hay.
	for (int i = 0; i < M / N; i++)
	{
		free (memeplexes[i]);
	}	

	// Se libera el puntero a los memeplexes.
	free (memeplexes);
}



//Fin de la funcion--------------------------------------------------------------------------------------------------------------------------------------------




// Retorna un numero real entre min y max---------------------------------------------------------------------------------------------------------------------
float genera_real_random (float min, float max)
{
	float num1 = RAND_MAX / (max - min);		// Generamos un aleatorio y lo guardamos 
	return min + (rand () / num1);				// Dividimos el numero obtenido entre otro numero aleatorio y lo retornamos a la funcion principal
												// De esta forma nos aseguramos la completa aleatoriedad del numero obtenido.

}
//Fin de la funcion--------------------------------------------------------------------------------------------------------------------------------------------



// ---------------------------------------------

//Muestra el ultimo mensaje del programa para indicar que la solucion es el ultimo fitness y posicion encontrada.
void mensaje_ultimo(){
	printf("\n\n");
	printf(" La solucion es el ultimo fitness / posicion encontrada.");
	printf("\n\n");
}
