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

// Gera Matriz 
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
	

// Transposta M 
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

// Aloca Matriz lxc
double **alocaMatriz(int l, int c)
{
	double **matriz = new double*[l];
	for(int i =0; i< l; i++) {
		matriz[i] = new double[c];
	} 
	return matriz;
}

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

void imprimiMatriz(double **matriz, int linhas, int colunas) {

		for(int i =0;i < linhas; i++) {
				for(int j =0; j< colunas; j++) {
					cout << matriz[i][j] << "\t";
				}
				cout << endl;
		}
		cout << endl << endl << endl;
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
			double **M1 = alocaMatriz(linhas, colunas);
			geraMatriz(M1, linhas, colunas);
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
				MulM1M2(M1,M2,resultado, linhas, colunas);
			}
			else if(tipo == 't') {
				transpostaM(M2, linhas, colunas);
				MulM1M2T(M1,M2,resultado,linhas,colunas);
			}
			
			if(imprimi != 0) {
				imprimiMatriz(resultado, linhas, linhas);
			}
			
		}

		
	}
	else 
	{
		cout << "Argumentos Invalidos!" << endl;
	}

}
