/**
 * @file oac_03.cpp
 * @author Adriano Grams e Lucas Becker
 * @brief Algoritmo para comparação de multiplicação de matrizes
 * de forma normal ou transposta
 * @version 0.1
 * @date 2019-06-20
 * 
 * @copyright Copyright (c) 2019
 * 
 * @compilation g++ oac_03.cpp -o oac_03
 * @execution ./oac_03 linhas colunas tipo('o' ou 't') vizualização('p') 
 */
#include <iostream>
#include <vector>
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h> 
#include <sstream>
#include <string>
#include <unistd.h>

using namespace std;

int tempo = 0;

/**
 * @brief Preenche a matriz com valores randomicos de 0 a 100
 * 
 * @param M Matriz que será preenchida
 * @param l numero de linhas dessa matriz
 * @param c numero de colunas dessa matriz
 */
void geraMatriz(double **M, int l, int c)
{ 
	int i, j; 
	srand( (unsigned)time(NULL) + tempo); 
	// seed 
	for(i = 0; i < l; i++)
	{ 
		for(j = 0; j < c; j++)
		{ 
			M[i][j] = (double)(rand() % 1000 + 1)/10; //(0~100 double) 
		} 
	} 
	tempo++;
	return;
}
	

/**
 * @brief Realiza a operação de transposição na matriz M
 * so funciona para matrizes quadradas
 * @param M Matriz que será transposta
 * @param l Numero de linhas da matriz M
 * @param c Numero de colunas da matriz M
 */
void transpostaM(double **M, int l, int c)
{ 
	int i, j; 
	double aux; 
	for (i = 0; i < l; i++) 
	{ 
		for (j = i+1; j < c; j++) 
		{ 
			aux     = M[i][j]; 
			M[i][j] = M[j][i]; 
			M[j][i] = aux;
		} 
	} 
	return; 
}

/**
 * @brief Aloca uma nova matriz com l linhas e c colunas
 * 
 * @param l numero de linhas da nova matriz
 * @param c numero de colunas da nova matriz
 * @return double** matriz gerada
 */
double **alocaMatriz(int l, int c)
{
	double **matriz = new double*[l];
	for(int i =0; i< l; i++) {
		matriz[i] = new double[c];
	} 
	return matriz;
}

/**
 * @brief Desaloca uma matriz M
 * 
 * @param M Matriz a ser desalocada
 * @param l Numero de linhas da matriz M
 * @param c NUmero de colunas da matriz M
 */
void desalocaMatriz(double **M, int l, int c) {
	for(int i =0; i< l; i++) 
		delete []M[i];
	delete []M;
}

/**
 * @brief Multiplica duas matrizes da forma convencional
 * 
 * @param M1 Matriz do lado direito da multiplicação
 * @param M2 Matriz do lado esquerdo da multiplicação
 * @param R Matriz resultado da multiplicação
 * @param l numero de linhas das duas matrizes
 * @param c numero de colunas das duas matrizes
 */
void MulM1M2(double **M1, double **M2, double **R, int l, int c)
{
	for(int i =0; i< l; i++) {
		for(int j =0; j< c; j++) {
			R[i][j] = 0;
			for(int k =0; k< c; k++) {
				R[i][j] += M1[i][k]*M2[k][j];
			}
		}
	}
}

/**
 * @brief Igual a MulM1M2 só que multiplica M1 pela transposta de M2
 * 
 * @param M1 Igual
 * @param M2T Matriz M2 tranposta
 * @param R Igual
 * @param l Igual
 * @param c Igual
 */
void MulM1M2T(double **M1, double **M2T, double **R, int l, int c)
{
	for(int i =0; i< l; i++) {
		for(int j = 0; j < l; j++) {
				R[i][j] = 0;
				for(int k =0; k< c; k++) {
					R[i][j] += M1[i][k]*M2T[j][k];
				}
		}
	}
}

/**
 * @brief Imprimi a matriz 
 * 
 * @param matriz Matriz a ser imprimida
 * @param linhas Numero de linhas da matriz
 * @param colunas Numero de colunas da matriz
 */
void imprimiMatriz(double **matriz, int linhas, int colunas) {

		for(int i =0;i < linhas; i++) {
				for(int j =0; j< colunas; j++) {
					cout << matriz[i][j] << "\t\t";
				}
				cout << endl;
		}
		cout << endl << endl << endl;
}

/**
 * @brief Calcula a media do vetor de valores
 * 
 * @param valores Valor de vetores a ser calculada a media
 * @return float Resultado da media
 */
float media(float *valores) {
	float media = 0;
	for(int i =0; i<5; i++) {
		media += valores[i];
	}
	return media/5;
}

int main(int argc, char *argv[]) {
	
	if(argv[1] != NULL && argv[2] != NULL && argv[3] != NULL) {
		stringstream ss1, ss2, ss3, ss4;
		ss1 << argv[1];
		ss2 << argv[2];
		ss3 << argv[3];
		double linhas, colunas;
		char tipo;
		if(ss1 >> linhas && ss2 >> colunas && ss3 >> tipo) {
			float *tempo_transposta;
			float *tempo_total;
			if(tipo == 't') {
				tempo_transposta = new float[5];
				tempo_total = new float[5];
			}
			float *tempo_mult = new float[5];
			float *tempo_aloc = new float[5];
			float *tempo_desaloc = new float[5];
			float *tempo_prenc = new float[5];
			for(int i =0; i< 5; i++) {
				clock_t begin_time_aloc = clock();
				double **M1 = alocaMatriz(linhas, colunas);
				tempo_aloc[i] = float(clock() - begin_time_aloc)/CLOCKS_PER_SEC;
				clock_t begin_time_gera = clock();
				geraMatriz(M1, linhas, colunas);
				tempo_prenc[i] = float(clock() - begin_time_gera)/CLOCKS_PER_SEC;
				double **M2 = alocaMatriz(colunas, linhas);
				geraMatriz(M2, colunas, linhas);
				double **resultado = alocaMatriz(linhas, linhas);
				char imprimi = 0;
				if(argv[4] != NULL && ss4 << argv[4] && ss4 >> imprimi 
						&& imprimi == 'p') {
					imprimiMatriz(M1, linhas, colunas);
					imprimiMatriz(M2, colunas, linhas);
				}
				if(tipo == 'o') 
				{
					cout << endl;
					clock_t begin_time = clock();
					MulM1M2(M1,M2,resultado, linhas, colunas);
					float resultado_mult = float(clock() - begin_time) / CLOCKS_PER_SEC;
					tempo_mult[i] = resultado_mult;
					cout << "Tempo para Multiplicar as matrizes (Normal): " << resultado_mult << endl;
				}
				else if(tipo == 't') {
					clock_t begin_time = clock();
					transpostaM(M2, linhas, colunas);
					float resultado_transposta = float(clock() - begin_time) / CLOCKS_PER_SEC;
					cout << endl;
					cout << "Tempo para gerar transposta: " << resultado_transposta << endl;
					begin_time = clock();
					MulM1M2T(M1,M2,resultado,linhas,colunas);
					float resultado_mult = float(clock() - begin_time) / CLOCKS_PER_SEC;
					cout << "Tempo para Multiplicar as matrizes (transposta): " << resultado_mult << endl;
					cout << "Tempo total: " << resultado_transposta + resultado_mult << endl;
					tempo_mult[i] = resultado_mult;
					tempo_transposta[i] = resultado_transposta;
					tempo_total[i] = resultado_mult + resultado_transposta;
				}
				
				if(imprimi != 0) {
					imprimiMatriz(resultado, linhas, linhas);
				}
				desalocaMatriz(resultado, linhas, linhas);
				clock_t begin_time_desaloc = clock();
				desalocaMatriz(M1, linhas, colunas);
				tempo_desaloc[i] = float(clock() - begin_time_desaloc)/CLOCKS_PER_SEC;
				if(tipo == 't')
					desalocaMatriz(M2, linhas, colunas);
				else
					desalocaMatriz(M2, colunas, linhas);
				
			}
			cout << endl;
			if(tipo == 't') {
				cout << "Media de executar a transposta: " << media(tempo_transposta) << endl;
				cout << "Media do tempo total: " << media(tempo_total) << endl;
			}
			cout << "Media da multiplicação da matriz: " << media(tempo_mult) << endl;
			cout << "Media da alocação da matriz M1: " << media(tempo_aloc) << endl;
			cout << "Media do prenchimento da matriz M1: " << media(tempo_prenc) << endl;
			cout << "Media da desalocação da matriz M1: " << media(tempo_desaloc) << endl;
			
		}

		
	}
	else 
	{
		cout << "Argumentos Invalidos!" << endl;
	}

}
