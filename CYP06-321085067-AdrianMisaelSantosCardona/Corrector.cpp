/*****************************************************************************************************************
	UNIVERSIDAD NACIONAL AUTONOMA DE MEXICO
	FACULTAD DE ESTUDIOS SUPERIORES -ARAGON-

	Computadoras y programacion.
	(c) 
	Quiso decir: Programa principal de la aplicacion de la distancia de Levenstein.

******************************************************************************************************************/


#include "stdafx.h"
#include <string.h>
#include "corrector.h"
#include <stdlib.h>
#include <ctype.h>
#define DEPURAR 1
#define LONGITUD 32
char szLetras[] = "abcdefghijklmnopqrstuvwxyzáéíóú";

//Funciones publicas del proyecto
/*****************************************************************************************************************
	DICCIONARIO: Esta funcion crea el diccionario completo
	char *	szNombre				:	Nombre del archivo de donde se sacaran las palabras del diccionario
	char	szPalabras[][TAMTOKEN]	:	Arreglo con las palabras completas del diccionario
	int		iEstadisticas[]			:	Arreglo con el numero de veces que aparecen las palabras en el diccionario
	int &	iNumElementos			:	Numero de elementos en el diccionario
******************************************************************************************************************/
void Diccionario(char* szNombre, char szPalabras[][TAMTOKEN], int iEstadisticas[], int& iNumElementos)
{
	FILE* fpDicc;
	iNumElementos = 0;
	int i;
	char linea, palabraDetectada[TAMTOKEN];
	for (i = 0; i < NUMPALABRAS; i++) {
		iEstadisticas[i] = 0;
	}
	fopen_s(&fpDicc, szNombre, "r");
	int k = 0;
	char puntuacion[] = " \t\n\r.,;() ";
	if (fpDicc == NULL)
		return;
	while ((linea = fgetc(fpDicc)) != EOF) {
		bool bandera = true;
		linea = tolower(linea);
		for (i = 0; i < strlen(puntuacion); i++) {
			if (puntuacion[i] == linea) {
				bandera = false;
			}
		}
		if (k < TAMTOKEN && bandera) {
			palabraDetectada[k++] = linea;
			continue;
		}
		else if (k == 0) {
			continue;
		}
		else if (k == 1 && bandera) {
			k = 0;
			continue;
		}
		palabraDetectada[k] = '\0';
		for (i = 0; i < iNumElementos && !bandera; i++) {
			if (strcmp(szPalabras[i], palabraDetectada) == 0) {
				iEstadisticas[i]++;
				bandera = true;
			}
		}
		if (!bandera) {
			strcpy_s(szPalabras[iNumElementos], palabraDetectada);
			iEstadisticas[iNumElementos++]++;

		}
		k = 0;
	}
	fclose(fpDicc);
//burbujazo
	for (int j = 0; j < iNumElementos - 1; j++) {
		for (i = j + 1; i < iNumElementos; i++) {
			if (strcmp(szPalabras[j], szPalabras[i]) > 0) {
				strcpy_s(palabraDetectada, szPalabras[j]);
				strcpy_s(szPalabras[j], szPalabras[i]);
				strcpy_s(szPalabras[i], palabraDetectada);
				k = iEstadisticas[j];
				iEstadisticas[j] = iEstadisticas[i];
				iEstadisticas[i] = k;
			}
		}
	}
}

/*****************************************************************************************************************
	ClonaPalabras: toma una palabra y obtiene todas las combinaciones y permutaciones requeridas por el metodo
	char *	szPalabraLeida,						// Palabra a clonar
	char	szPalabrasSugeridas[][TAMTOKEN], 	//Lista de palabras clonadas
	int &	iNumSugeridas)						//Numero de elementos en la lista
******************************************************************************************************************/
void	ClonaPalabras(
	char* szPalabraLeida,						// Palabra a clonar
	char	szPalabrasSugeridas[][TAMTOKEN], 	//Lista de palabras clonadas
	int& iNumSugeridas)						//Numero de elementos en la lista
{
	int i, j, k;
	char aux[TAMTOKEN];
	char iNumSugeridas = 0;
	//char szLetras[] = "abcdefghijklmnopqrstuvwxyzáéíóú";

	strcpy_s(aux, szPalabraLeida);

	if (DEPURAR == 1) {
		printf("palabra leida: %s", aux);
	}

	//Pasar el abecedario en cada caracter
	for (i = 0; i < strlen(szPalabraLeida); i++) {

		for (j = 0; j < strlen(szLetras); j++) {
			aux[i] = szLetras[j];
			strcpy_s(szPalabrasSugeridas[iNumSugeridas++], aux);
		}
		aux[i] = szPalabraLeida[i];
	}
	//Pasar el abecedario entre los caracteres
	for (k = 1; k < strlen(szPalabraLeida) + 1; k++) {
		aux[k] = szPalabraLeida[k - 1];

		/*Para asignar espacios*/
	}
	aux[k] = '\0';

	for (int i = 0; i < strlen(szPalabraLeida) + 1; i++) {

		for (int j = 0; j < strlen(szLetras); j++) {
			aux[i] = szLetras[j];
			strcpy_s(szPalabrasSugeridas[iNumSugeridas++], aux);
		}
		aux[i] = szPalabraLeida[i];
	}

	//Para suprimir los caracteres
	k = 0;
	for (i = 0; i < strlen(szPalabraLeida) && strlen(szPalabraLeida) != 1; i++) {
		for (j = 0; j < strlen(szPalabraLeida); j++) {
			if (j != i)
				aux[k++] = szPalabraLeida[j];
		}
		aux[k] = '\0';
		strcpy_s(szPalabrasSugeridas[iNumSugeridas++], aux);
		strcpy_s(aux, szPalabraLeida);
		k = 0;
	}

	//Transposición de los caracteres.
	for (i = 0; i < strlen(szPalabraLeida) - 1; i++) {
		aux[i] = szPalabraLeida[i + 1];
		aux[i + 1] = szPalabraLeida[i];
		strcpy_s(szPalabrasSugeridas[iNumSugeridas++], aux);
		strcpy_s(aux, szPalabraLeida);
	}
	strcpy_s(szPalabrasSugeridas[iNumSugeridas++], szPalabraLeida);

	//burbujazo 
	for (j = 0; j < iNumSugeridas - 1; j++) {
		for (i = j + 1; i < iNumSugeridas; i++) {
			if (strcmp(szPalabrasSugeridas[j], szPalabrasSugeridas[i]) > 0) {
				strcpy_s(aux, szPalabrasSugeridas[j]);
				strcpy_s(szPalabrasSugeridas[j], szPalabrasSugeridas[i]);
				strcpy_s(szPalabrasSugeridas[i], aux);
			}
		}
	}
}


/*****************************************************************************************************************
	ListaCandidatas: Esta funcion recupera desde el diccionario las palabras validas y su peso
	Regresa las palabras ordenadas por su peso
	char	szPalabrasSugeridas[][TAMTOKEN],	//Lista de palabras clonadas
	int		iNumSugeridas,						//Lista de palabras clonadas
	char	szPalabras[][TAMTOKEN],				//Lista de palabras del diccionario
	int		iEstadisticas[],					//Lista de las frecuencias de las palabras
	int		iNumElementos,						//Numero de elementos en el diccionario
	char	szListaFinal[][TAMTOKEN],			//Lista final de palabras a sugerir
	int		iPeso[],							//Peso de las palabras en la lista final
	int &	iNumLista)							//Numero de elementos en la szListaFinal
******************************************************************************************************************/
void	ListaCandidatas(
	char	szPalabrasSugeridas[][TAMTOKEN],	//Lista de palabras clonadas
	int		iNumSugeridas,						//Lista de palabras clonadas
	char	szPalabras[][TAMTOKEN],				//Lista de palabras del diccionario
	int		iEstadisticas[],					//Lista de las frecuencias de las palabras
	int		iNumElementos,						//Numero de elementos en el diccionario
	char	szListaFinal[][TAMTOKEN],			//Lista final de palabras a sugerir
	int		iPeso[],							//Peso de las palabras en la lista final
	int& iNumLista)							//Numero de elementos en la szListaFinal
{
	int iAux;
	char szAux[TAMTOKEN];
	iNumLista = 0;
	int i, j, k;
	for (i = 0; i < iNumSugeridas; i++) {
		for (j = 0; j < iNumElementos; j++) {
			if (strcmp(szPalabrasSugeridas[i], szPalabras[j]) == 0) {
				bool bandera = false;
				for (k = 0; k < iNumLista && !bandera; k++)
					if (strcmp(szListaFinal[k], szPalabras[j]) == 0)
						bandera = true;
				if (bandera) continue;
				strcpy_s(szListaFinal[iNumLista], szPalabrasSugeridas[i]);
				iPeso[iNumLista++] = iEstadisticas[j];
			}
		}
	}
	for (i = 0; i < iNumLista; i++) {
		for (j = 0; j < iNumLista - 1; j++) {
			if (iPeso[j] < iPeso[j + 1]) {
				strcpy_s(szAux, szListaFinal[j + 1]);
				iAux = iPeso[j + 1];
				strcpy_s(szListaFinal[j + 1], szListaFinal[j]);
				iPeso[j + 1] = iPeso[j];
				strcpy_s(szListaFinal[j], szAux);
				iPeso[j] = iAux;
			}
		}
	}
}

