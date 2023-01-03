#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "libprinc.h"
#define MAX 200 //Número máximo de jugadas entre la cpu y el jugador

int turnjugador=0,turncpu=0;
int counturnj=0,counturncpu=0;
int contconej=8,contconecpu=8;
int jugadasglobales=0;
char aux1;
char str[20];
char matriz[9][9];
int i,j,iref,jref,imov,jmov, limiteturn;

void imprimirtablero(char matrix[9][9]){ //LOCAL, una función muy básica que se usa siempre
	for (i=0;i<9;i++){
	if (i==1){
		printf ("\n");
	}
		for (j=0;j<9;j++){
			if (j==0){
				printf ("%c  ", matrix[i][j]);
			}
			else{
				printf (" %c", matrix[i][j]);
			}
		}
	printf ("\n");
	}
	printf ("\n");
}

void selectablero(){
	//int conejo=0,gato=0,perro=0,caballo=0,camello=0,elefante=0; para usarse en el área comentada más abajo
	/*
	 PLAYER (ABAJO SIEMPRE):
	 U -> CONEJO
	 V -> GATO
	 W -> PERRO
	 X -> CABALLO
	 Y -> CAMELLO
	 Z -> ELEFANTE
	 CPU (ARRIBA SIEMPRE):
	 I -> CONEJO
	 J -> GATO
	 K -> PERRO
	 L -> CABALLO
	 M -> CAMELLO
	 N -> ELEFANTE
	 = -> LUGARES TRAMPA
	 - -> ESPACIOS VACIOS
	 */
	char elec;
	char matriz1 [9][9]= { //ORDENADO FICHAS FUERTES DELANTE
		{' ','A','B','C','D','E','F','G','H'},
	    {'8','I','I','I','I','I','I','I','I'},
	    {'7','L','K','J','N','M','K','J','L'},
		{'6','-','-','=','-','-','=','-','-'},
		{'5','-','-','-','-','-','-','-','-'},
		{'4','-','-','-','-','-','-','-','-'},
		{'3','-','-','=','-','-','=','-','-'},
		{'2','X','W','V','Z','Y','W','V','X'},
		{'1','U','U','U','U','U','U','U','U'}
	 };
	char matriz2 [9][9]= { //ORDENADO FICHAS DÉBILES DELANTE
		{' ','A','B','C','D','E','F','G','H'},
	    {'8','L','K','J','N','M','K','J','L'},
	    {'7','I','I','I','I','I','I','I','I'},
		{'6','-','-','=','-','-','=','-','-'},
		{'5','-','-','-','-','-','-','-','-'},
		{'4','-','-','-','-','-','-','-','-'},
		{'3','-','-','=','-','-','=','-','-'},
		{'2','U','U','U','U','U','U','U','U'},
		{'1','X','W','V','Z','Y','W','V','X'}
	 };
	char matriz3 [9][9]= { // FICHAS AMONTONADAS
		{' ','A','B','C','D','E','F','G','H'},
	    {'8','I','I','I','I','I','J','K','L'},
	    {'7','I','I','I','N','M','L','K','J'},
		{'6','-','-','=','-','-','=','-','-'},
		{'5','-','-','-','-','-','-','-','-'},
		{'4','-','-','-','-','-','-','-','-'},
		{'3','-','-','=','-','-','=','-','-'},
		{'2','X','W','V','Y','Z','U','U','U'},
		{'1','V','W','X','U','U','U','U','U'}
	 };
	char matriz4 [9][9]= { // SIMÉTRICO
		{' ','A','B','C','D','E','F','G','H'},
	    {'8','I','I','K','L','L','J','I','I'},
	    {'7','I','I','K','N','M','J','I','I'},
		{'6','-','-','=','-','-','=','-','-'},
		{'5','-','-','-','-','-','-','-','-'},
		{'4','-','-','-','-','-','-','-','-'},
		{'3','-','-','=','-','-','=','-','-'},
		{'2','U','U','W','Z','Y','V','U','U'},
		{'1','U','U','W','X','X','V','U','U'}
	 };
	/*char matriz5[9][9]={
		{' ','A','B','C','D','E','F','G','H'},
		{'8','I','I','K','L','L','J','I','I'},
		{'7','I','I','K','N','M','J','I','I'},
		{'6','-','-','=','-','-','=','-','-'},
		{'5','-','-','-','-','-','-','-','-'},
		{'4','-','-','-','-','-','-','-','-'},
		{'3','-','-','=','-','-','=','-','-'},
		{'2','-','-','-','-','-','-','-','-'},
		{'1','-','-','-','-','-','-','-','-'}
	};
	Presenta problemas la matriz modificable, hace un loop infinito*/
	printf ("Tablero A :\n");
	imprimirtablero(matriz1);
	printf ("Tablero B :\n");
	imprimirtablero(matriz2);
	printf ("Tablero C:\n");
	imprimirtablero(matriz3);
	printf ("Tablero D :\n");
	imprimirtablero(matriz4);
	printf ("Posteriormente a este paso también se decidirá aleatorioamente qué jugador empezará la partida\n");
	printf ("Por favor inserte A,B,C o D según tablero que le gustaría utilizar:\n");
	elec = getchar();
	if(elec=='A'){
		for (i=0;i<9;i++){
			for (j=0;j<9;j++){
				matriz[i][j]=matriz1[i][j];
			}
		}
	}
	else if (elec=='B'){
		for (i=0;i<9;i++){
			for (j=0;j<9;j++){
				matriz[i][j]=matriz2[i][j];
			}
		}
	}
	else if (elec=='C'){
		for (i=0;i<9;i++){
			for (j=0;j<9;j++){
				matriz[i][j]=matriz3[i][j];
			}
		}
	}
	else if (elec=='D'){
		for (i=0;i<9;i++){
			for (j=0;j<9;j++){
				matriz[i][j]=matriz4[i][j];
			}
		}
	}
	/*else if (elec=='E'){
		for (i=0;i<9;i++){
			for (j=0;j<9;j++){
				matriz[i][j]=matriz5[i][j];
			}
		}
		while(conejo<8){
			printf("Escriba la posición de su conejo:\n");
			reordenarme(imov,jmov);
			while (imov<6||jmov<1||jmov>8||matriz[imov][jmov]=='U'){
				printf ("Escriba una posición legal:\n");
				reordenarme(imov,jmov);
			}
			conejo++;
			imprimirtablero(matriz);
		}
		while(gato<2){
			printf("Escriba la posición de su conejo:\n");
			reordenarme();
			while (imov<6||jmov<1||jmov>8||matriz[imov][jmov]!='U'||matriz[imov][jmov]!='V'){
				printf ("Escriba una posición legal:\n");
				reordenarme();
			}
		gato++;
		imprimirtablero(matriz);
		}
		while(perro<2){
			printf("Escriba la posición de su conejo:\n");
			reordenarme();
			while (imov<6||jmov<1||jmov>8||matriz[imov][jmov]!='U'||matriz[imov][jmov]!='V'||matriz[imov][jmov]!='W'){
				printf ("Escriba una posición legal:\n");
				reordenarme();
			}
		perro++;
		imprimirtablero(matriz);
		}
		while(caballo<2){
			printf("Escriba la posición de su conejo:\n");
			reordenarme();
			while (imov<6||jmov<1||jmov>8||matriz[imov][jmov]!='U'||matriz[imov][jmov]!='V'||matriz[imov][jmov]!='W'
					||matriz[imov][jmov]!='X'){
				printf ("Escriba una posición legal:\n");
				reordenarme();
			}
		caballo++;
		imprimirtablero(matriz);
		}
		while(camello<1){
			printf("Escriba la posición de su conejo:\n");
			reordenarme();
			while (imov<6||jmov<1||jmov>8||matriz[imov][jmov]!='U'||matriz[imov][jmov]!='V'||matriz[imov][jmov]!='W'
					||matriz[imov][jmov]!='X'||matriz[imov][jmov]!='Y'){
				printf ("Escriba una posición legal:\n");
				reordenarme();
			}
		camello++;
		imprimirtablero(matriz);
		}
		while(elefante<1){
			printf("Escriba la posición de su conejo:\n");
			reordenarme();
			while (imov<6||jmov<1||jmov>8||matriz[imov][jmov]!='U'||matriz[imov][jmov]!='V'||matriz[imov][jmov]!='W'
					||matriz[imov][jmov]!='X'||matriz[imov][jmov]!='Y'||matriz[imov][jmov]!='Z'){
				printf ("Escriba una posición legal:\n");
				reordenarme();
			}
		elefante++;
		imprimirtablero(matriz);
		}
	}
	La máquina se queda colgada, scanf no puede recibir el parámetro en reordernarme y no se ejecuta nunca la acción de posicionar. No sé por qué
	ocurre esto puesto que funciona sin problemas para hacer los movimientos con la cpu y el jugador, **el switch case**
	*/
	else{
		do{
			elec = getchar();
			printf ("Por favor escriba una letra válida:\n");
		}while((65>elec)||(elec>69));
		if(elec=='A'){
			for (i=0;i<9;i++){
				for (j=0;j<9;j++){
					matriz[i][j]=matriz1[i][j];
				}
			}
		}
		else if (elec=='B'){
			for (i=0;i<9;i++){
				for (j=0;j<9;j++){
					matriz[i][j]=matriz2[i][j];
				}
			}
		}
		else if (elec=='C'){
			for (i=0;i<9;i++){
				for (j=0;j<9;j++){
					matriz[i][j]=matriz3[i][j];
				}
			}
		}
		else if (elec=='D'){
				for (i=0;i<9;i++){
					for (j=0;j<9;j++){
						matriz[i][j]=matriz4[i][j];
				}
			}
		}
		/*else if (elec=='E'){
			imov=8;
			jmov=1;
			while(conejo<8){
				printf("Escriba la posición de su conejo:\n");
				reordenarme();
				while (imov<6||jmov<1||jmov>8||matriz[imov][jmov]!='U'){
					printf ("Escriba una posición legal:\n");
					reordenarme();
				}
				conejo++;
				imprimirtablero(matriz);
			}
			while(gato<2){
				printf("Escriba la posición de su conejo:\n");
				reordenarme();
				while (imov<6||jmov<1||jmov>8||matriz[imov][jmov]!='U'||matriz[imov][jmov]!='V'){
					printf ("Escriba una posición legal:\n");
					reordenarme();
				}
			gato++;
			imprimirtablero(matriz);
			}
			while(perro<2){
				printf("Escriba la posición de su conejo:\n");
				reordenarme();
				while (imov<6||jmov<1||jmov>8||matriz[imov][jmov]!='U'||matriz[imov][jmov]!='V'||matriz[imov][jmov]!='W'){
					printf ("Escriba una posición legal:\n");
					reordenarme();
				}
			perro++;
			imprimirtablero(matriz);
			}
			while(caballo<2){
				printf("Escriba la posición de su conejo:\n");
				reordenarme();
				while (imov<6||jmov<1||jmov>8||matriz[imov][jmov]!='U'||matriz[imov][jmov]!='V'||matriz[imov][jmov]!='W'
						||matriz[imov][jmov]!='X'){
					printf ("Escriba una posición legal:\n");
					reordenarme();
				}
			caballo++;
			imprimirtablero(matriz);
			}
			while(camello<1){
				printf("Escriba la posición de su conejo:\n");
				reordenarme();
				while (imov<6||jmov<1||jmov>8||matriz[imov][jmov]!='U'||matriz[imov][jmov]!='V'||matriz[imov][jmov]!='W'
						||matriz[imov][jmov]!='X'||matriz[imov][jmov]!='Y'){
					printf ("Escriba una posición legal:\n");
					reordenarme();
				}
			camello++;
			imprimirtablero(matriz);
			}
			while(elefante<1){
				printf("Escriba la posición de su conejo:\n");
				reordenarme();
				while (imov<6||jmov<1||jmov>8||matriz[imov][jmov]!='U'||matriz[imov][jmov]!='V'||matriz[imov][jmov]!='W'
						||matriz[imov][jmov]!='X'||matriz[imov][jmov]!='Y'||matriz[imov][jmov]!='Z'){
					printf ("Escriba una posición legal:\n");
					reordenarme();
				}
			elefante++;
			imprimirtablero(matriz);
			}
		}*/
	}
}

void elegirjugador(int elegiremp){
	int t = (rand() %2);
	scanf ("%d", &elegiremp);
	if (elegiremp==1){
		turnjugador=1;
		printf ("Empieza el jugador\n");
	}
	else if(elegiremp==2){
		turncpu=1;
		printf ("Empieza la cpu\n");
	}
	else {
	if (t==1){
		 turnjugador=1;
		printf ("Empieza el jugador\n");
		}
	else{
		turncpu=1;
		printf("Empieza la cpu\n");
		}
	}

}

void reordenarme(){
	scanf ("%s", &str);
	imov = str[0];
	switch(imov){
	case 49:
		imov=8;
	break;
	case 50:
		imov=7;
	break;
	case 51:
		imov=6;
	break;
	case 52:
		imov=5;
	break;
	case 53:
		imov=4;
	break;
	case 54:
		imov=3;
	break;
	case 55:
		imov=2;
	break;
	case 56:
		imov=1;
	break;
		}
	jmov = str[1]-64;
}
void poscpu(){
	int t;
	t = (rand() %8)+1;
	iref = t;
	t = (rand() %8)+1;
	jref = t;
	while(iref>8||iref<1||jref>8||jref<1||matriz[iref][jref]=='-'||matriz[iref][jref]=='='||matriz[iref][jref]=='U'
	||matriz[iref][jref]=='V'||matriz[iref][jref]=='W'||matriz[iref][jref]=='X'||matriz[iref][jref]=='Y'||matriz[iref][jref]=='Z'){
		//si la posición elegida es equivocada que vuelva a hacer
		t = (rand() %8)+1;
		iref = t;
		t = (rand() %8)+1;
		jref = t;
	}
}
void ordenarcpu(){
	int t;
	t = (rand() %8)+1;
	imov = t;
	t = (rand() %8)+1;
	jmov = t;
}
void posjugador(){
		printf ("La pieza que desea mover(ejemplo 2B):\n");
		scanf ("%s", &str);
		iref = str[0];
		switch(iref){
		case 49:
			iref=8;
		break;
		case 50:
			iref=7;
		break;
		case 51:
			iref=6;
		break;
		case 52:
			iref=5;
		break;
		case 53:
			iref=4;
		break;
		case 54:
			iref=3;
		break;
		case 55:
			iref=2;
		break;
		case 56:
			iref=1;
		break;
		}
	jref = str[1]-64;
	while(iref>8||iref<1||jref>8||jref<1||matriz[iref][jref]=='-'||matriz[iref][jref]=='='||matriz[iref][jref]=='I'
		||matriz[iref][jref]=='J'||matriz[iref][jref]=='K'||matriz[iref][jref]=='L'||matriz[iref][jref]=='M'||matriz[iref][jref]=='N'){
		//condiciones necesarias para que deje de repetirse indefinidamente el pedido de una ficha correcta"
		printf ("Reescriba su comando(ficha suya que pueda mover):\n");
		scanf ("%s", &str);
		iref = str[0];
		switch(iref){
		case 49:
			iref=8;
		break;
		case 50:
			iref=7;
		break;
		case 51:
			iref=6;
		break;
		case 52:
			iref=5;
		break;
		case 53:
			iref=4;
		break;
		case 54:
			iref=3;
		break;
		case 55:
			iref=2;
		break;
		case 56:
			iref=1;
		break;
		}
	jref = str[1]-64;
	}
}

int ganador(){
	int contjug=0, contcpu=0;
	int finalj=0, finalcpu=0;
	for (i=0;i<9;i++){
		for(j=0;j<9;j++){
			if (matriz[i][j]=='I'){
				contcpu++;
			}
			else if (matriz[i][j]=='U'){
				contjug++;
			}
			else if (matriz[1][j]=='U'){
				return 1;
			}
			else if (matriz[8][j]=='I'){
				return 2;
			}
		}
	}
	if (contjug==0){
		return 2;
	}
	else if(contcpu==0){
		return 1;
	}
	else{
		return 0;
	}
	if(jugadasglobales==MAX){
		for (i=0;i<9;i++){
			for(j=0;j<9;j++){
				if (matriz[i][j]=='I'||matriz[i][j]=='J'||matriz[i][j]=='K'||
						matriz[i][j]=='L'||matriz[i][j]=='M'||matriz[i][j]=='N'){
					finalcpu++;
				}
				else if(matriz[i][j]=='U'||matriz[i][j]=='V'||matriz[i][j]=='W'||
					matriz[i][j]=='X'||matriz[i][j]=='Y'||matriz[i][j]=='Z'){
						finalj++;
				}
			}
		}
		if (finalcpu>finalj){
			return 2;
		}
		else{
			return 1;
		}
	}
}

void empujejugador(){
	int iaux, jaux;
	iaux=imov; //son los valores que en caso de entrar al while, representan la posición de la FICHA ENEMIGA
	jaux=jmov;
	while(matriz[iaux][jaux]=='I'||matriz[iaux][jaux]=='J'||matriz[iaux][jaux]=='K'
		||matriz[iaux][jaux]=='L'||matriz[iaux][jaux]=='M'||matriz[iaux][jaux]=='N'){
		/*si se escoje una ficha oponente, si se usase imov,jmov aquí al ejecutarse
		reordenarme() saldria ya del while, por eso se hizo el cambio de variable*/
		if (counturnj<=(limiteturn-2)){
			printf ("Se ha seleccionado una pieza a empujar/estirar.\n");
			printf ("Ahora seleccione el lugar respecto a LA PIEZA DEL ADVERASRIO.\nSi escoje la posición de su pieza ya seleccionada, empezará el empuje:\n");
			reordenarme(); //ahora imov y jmov simbolizan los espacios adyascentes a la FICHA ENEMIGA que se seleccionó
			if (((imov==(iaux+1))&&(jmov==jaux)&&(matriz[imov][jmov]=='-'))||((imov==(iaux-1))&&(jmov==jaux)&&(matriz[imov][jmov]=='-'))||
			((imov==iaux)&&(jmov==(jaux+1))&&(matriz[imov][jmov]=='-'))||((imov==iaux)&&(jmov==(jaux-1))&&(matriz[imov][jmov]=='-'))){ //inicia empuje
				//condiciones para que sea "legal" la jugada
				if (matriz [iref][jref] > matriz[iaux][jaux]-12){ //solo si el valor ASCII de la pieza del jugador es mayor este podrá empujar
					matriz[imov][jmov] = matriz [iaux][jaux];
					matriz[iaux][jaux] = matriz [iref][jref];
					matriz[iref][jref] = '-';
					counturnj=counturnj+2;
				break;
				}
				else{
					printf("Su pieza es de menor valor que la que quiere mover, vuelva a introducir sus comandos");
					break;
				}
			}
			else if ((imov==iref)&&(jmov==jref)){ //Inicia accion de estirar
				printf ("Ha iniciado el comando estirar, seleccione el lugar respecto a SU PIEZA donde desea moverse:\n");
				reordenarme();
				if (((imov==iref+1)&&(jmov==jref)&&(matriz[imov][jmov]=='-'))||((imov==iref-1)&&(jmov==jref)&&(matriz[imov][jmov]=='-'))||
					((imov==iref)&&(jmov==jref+1)&&(matriz[imov][jmov]=='-'))||((imov==iref)&&(jmov==jref-1)&&(matriz[imov][jmov]=='-'))){
					// condiciones necesarias para que sea "legal" la jugada
					if (matriz [iref][jref] >= matriz[iaux][jaux]-12){ //solo si el valor ASCII de la pieza del jugador es mayor este podrá empujar
						if (matriz[imov][jmov]=='-'){
							matriz[imov][jmov] = matriz[iref][jref];
							matriz[iref][jref] = matriz[iaux][jaux];
							matriz[iaux][jaux] = '-';
							counturnj=counturnj+2;
							break;
						}
						else{
							printf ("Lugar introducido no vacío o incorrecto, vuelva a introducir sus comandos :\n");
							break;
							}
						}
					else{
						printf("Su pieza es de menor valor que la que quiere mover, vuelva a introducir sus comandos\n");
						break;
					}
				}
			}
			else{
				printf ("El comando introducido es incorrecto, vuelva a introducir sus comandos:\n");
				break;
			}
		}
		else{
			printf ("Empujar o estirar requiere de dos movimientos y usted tiene solo uno, vuelva a introducir sus comandos:\n");
			break;
		}
	}
}

void empujecpu(){
	int iaux, jaux;
	iaux=imov; //posición de la FICHA ENEMIGA
	jaux=jmov;
	while(matriz[iaux][jaux]=='U'||matriz[iaux][jaux]=='W'||matriz[iaux][jaux]=='X'
		||matriz[iaux][jaux]=='V'||matriz[iaux][jaux]=='Y'||matriz[iaux][jaux]=='Z'){
		/*si se escoje una ficha oponente, si se usase imov,jmov aquí al ejecutarse
		reordenarme() saldria ya del while, por eso se hizo el cambio de variable*/
		if (counturncpu<=(limiteturn-2)){
			ordenarcpu(); //ahora imov y jmov simbolizan los espacios adyascentes a la FICHA ENEMIGA que se seleccionó
			if (((imov==(iaux+1))&&(jmov==jaux)&&(matriz[imov][jmov]=='-'))||((imov==(iaux-1))&&(jmov==jaux)&&(matriz[imov][jmov]=='-'))||
			((imov==iaux)&&(jmov==(jaux+1))&&(matriz[imov][jmov]=='-'))||((imov==iaux)&&(jmov==(jaux-1))&&(matriz[imov][jmov]=='-'))){ //inicia empuje
				//condiciones para que sea "legal" la jugada
				if (matriz [iref][jref] > matriz[iaux][jaux]-12){ // valor ASCII correcto p/ cpu
					matriz[imov][jmov] = matriz [iaux][jaux];
					matriz[iaux][jaux] = matriz [iref][jref];
					matriz[iref][jref] = '-';
					counturncpu=counturncpu+2;
					imprimirtablero(matriz);
					break;
					}
			}
			else if ((imov==iref)&&(jmov==jref)){ //Inicia accion de estirar
					ordenarcpu();
					if (((imov==iref+1)&&(jmov==jref)&&(matriz[imov][jmov]=='-'))||((imov==iref-1)&&(jmov==jref)&&(matriz[imov][jmov]=='-'))||
					((imov==iref)&&(jmov==jref+1)&&(matriz[imov][jmov]=='-'))||((imov==iref)&&(jmov==jref-1)&&(matriz[imov][jmov]=='-'))){
					// condiciones necesarias para que sea "legal" la jugada
					if (matriz [iref][jref] >= matriz[iaux][jaux]-12){ //valor ASCII correcto p/ cpu
						if (matriz[imov][jmov]=='-'){
							matriz[imov][jmov] = matriz[iref][jref];
							matriz[iref][jref] = matriz[iaux][jaux];
							matriz[iaux][jaux] = '-';
							counturncpu=counturncpu+2;
							break;
							imprimirtablero(matriz);
								}
							}
						}
					}
					else{
						break;
					}
			}
		else{
			break;
		}
		}
}

void trampa(){
	if(matriz[3][3]>=85){ //si la posición de trampa posee una ficha del jugador para [3][3]
		if (((matriz[4][3]>=85)&&(matriz[2][3]>=85))||((matriz[3][4]>=85)&&(matriz[3][2]>=85))){
			//si las posiciones adyascentes poseen fichas de la cpu en vertical o horizontal
			printf ("La ficha no fue comida porque hay fichas adyascentes que la protegen\n");
		}
		else{
			if (matriz[3][3]=='U'){ //si murió un conejo jugador
				contconecpu--;
			}
			matriz[3][3]='=';
		}
	}
	if((matriz[3][3]>=73)&&(matriz[3][3]<=78)){ //si la posición de trampa posee una ficha de la cpu para [3][3]
		if (((matriz[4][3]>=73)&&(matriz[2][3]>=73)&&(matriz[4][3]<=78)&&(matriz[2][3]<=78))
			||((matriz[3][4]>=73)&&(matriz[3][2]>=73)&&(matriz[3][4]<=78)&&(matriz[3][2]<=78))){
			printf ("La ficha no fue comida porque hay fichas adyascentes que la protegen\n");
		}
		else{
			if (matriz[3][3]=='I'){ //si murió un conejo cpu
				contconej--;
			}
			matriz[3][3]='=';
		}
	}
	if(matriz[3][6]>=85){ //si la posición de trampa posee una ficha del juegador para [3][6]
		if (((matriz[4][6]>=85)&&(matriz[2][6]>=85))||((matriz[3][5]>=85)&&(matriz[3][7]>=85))){
			printf ("La ficha no fue comida porque hay fichas adyascentes que la protegen\n");
		}
		else{
			if (matriz[3][6]=='U'){
				contconecpu--;
			}
			matriz[3][6]='=';
		}
	}
	if((matriz[3][6]>=73)&(matriz[3][6]<=78)){ //si la posición de trampa posee una ficha de la cpu para [3][6]
		if (((matriz[3][7]>=73)&&(matriz[3][5]>=73)&&(matriz[3][7]<=78)&&(matriz[3][5]<=78))
			||((matriz[2][6]>=73)&&(matriz[4][6]>=73)&&(matriz[2][6]<=78)&&(matriz[4][6]<=78))){
			printf ("La ficha no fue comida porque hay fichas adyascentes que la protegen\n");
		}
		else{
			if (matriz[3][6]=='I'){
				contconej--;
			}
			matriz[3][6]='=';
		}
	}
	if(matriz[6][3]>=85){ //si la posición de trampa posee una ficha del jugador para [6][3]
		if (((matriz[6][4]>=85)&&(matriz[6][2]>=85))||((matriz[5][3]>=85)&&(matriz[7][3]>=85))){
			printf ("La ficha no fue comida porque hay fichas adyascentes que la protegen\n");
		}
		else{
			if (matriz[6][3]=='U'){
				contconecpu--;
			}
			matriz[6][3]='=';
		}
	}
	if((matriz[6][3]>=73)&(matriz[6][3]<=78)){ //si la posición de trampa posee una ficha de la cpu para [6][3]
		if (((matriz[6][2]>=73)&&(matriz[6][4]>=73)&&(matriz[6][2]<=78)&&(matriz[6][4]<=78))
			||((matriz[5][3]>=73)&&(matriz[7][3]>=73)&&(matriz[5][3]<=78)&&(matriz[7][3]<=78))){
			printf ("La ficha no fue comida porque hay fichas adyascentes que la protegen\n");
		}
		else{
			if (matriz[6][3]=='I'){
				contconej--;
			}
			matriz[6][3]='=';
		}
	}
	if(matriz[6][6]>=85){ //si la posición de trampa posee una ficha del jugador para [6][6]
		if (((matriz[7][6]>=85)&&(matriz[5][6]>=85))||((matriz[6][7]>=85)&&(matriz[6][5]>=85))){
			printf ("La ficha no fue comida porque hay fichas adyascentes que la protegen\n");
		}
		else{
			if (matriz[6][6]=='U'){
				contconecpu--;
			}
			matriz[6][6]='=';
		}
	}
	if((matriz[6][6]>=73)&(matriz[6][6]<=78)){ //si la posición de trampa posee una ficha de la cpu dor para [6][6]
		if (((matriz[6][5]>=73)&&(matriz[6][7]>=73)&&(matriz[6][5]<=78)&&(matriz[6][7]<=78))
			||((matriz[5][6]>=73)&&(matriz[7][6]>=73)&&(matriz[5][6]<=78)&&(matriz[7][6]<=78))){
			printf ("La ficha no fue comida porque hay fichas adyascentes que la protegen\n");
		}
		else{
			if (matriz[6][6]=='I'){
				contconej--;
			}
			matriz[6][6]='=';
		}
	}
}
void movjugador(){
	printf ("Por favor ingrese el lugar donde desea mover su ficha o si quiere seleccionar una ficha enemiga a empujar/estirar\n");
	reordenarme();
	while(imov>8||imov<1||jmov>8||jmov<1||matriz[imov][jmov]=='U'||matriz[imov][jmov]=='V'||((iref==imov)&&(jref==jmov))
		||matriz[imov][jmov]=='W'||matriz[imov][jmov]=='X'||matriz[imov][jmov]=='Y'||matriz[imov][jmov]=='Z'){
		/*condiciones necesarias para que se acepte el movimiento de la ficha, no puede ser en el lugar de ninguna pieza enemiga
		o contraria, tampoco puede superar las dimensiones de la matriz, si no se cumplen estas condiciones, se seguirá pidiendo
		un comando correcto por teclado*/
		printf ("Reescriba un lugar al que es posible moverse o elija una pieza enemiga a empujar/estirar\n");
		printf ("De no ser posible puede ingresar la coordenada de una ficha adyascente aliada para rehacer toda la jugada\n");
		reordenarme();
	}
	empujejugador(); //ojo acá está el llamado a la función de empujar
	if (((imov==(iref+1))&&(jmov==jref)&&(matriz[imov][jmov]=='-'))||((imov==(iref-1))&&(jmov==jref)&&(matriz[imov][jmov]=='-'))||
		((imov==iref)&&(jmov==(jref-1))&&(matriz[imov][jmov]=='-'))||((imov==iref)&&(jmov==(jref+1))&&(matriz[imov][jmov]=='-'))){
		// condiciones necesarias para que sea "legal" la jugada
		aux1 = matriz[iref][jref];
		matriz [iref][jref] = '-';
		matriz [imov][jmov] = aux1;
		counturnj++;
	}
	if (((imov==(iref+1))&&(jmov==jref)&&(matriz[imov][jmov]=='='))||((imov==(iref-1))&&(jmov==jref)&&(matriz[imov][jmov]=='='))||
			((imov==iref)&&(jmov==(jref-1))&&(matriz[imov][jmov]=='='))||((imov==iref)&&(jmov==(jref+1))&&(matriz[imov][jmov]=='='))){
		// se metió en la trampa por depresivo (hagase la distinción para saber qué ocurre en este caso, el algoritmo es igual que el de arriba)
		aux1 = matriz[iref][jref];
		matriz [iref][jref] = '-';
		matriz [imov][jmov] = aux1;
		counturnj++;
	}
}

void movcpu(){
	ordenarcpu();
	while(imov>8||imov<1||jmov>8||jmov<1||matriz[imov][jmov]=='I'||matriz[imov][jmov]=='J'||((iref==imov)&&(jref==jmov))
		||matriz[imov][jmov]=='K'||matriz[imov][jmov]=='L'||matriz[imov][jmov]=='M'||matriz[imov][jmov]=='N'){
		//condiciones para que inicie el movimiento
		ordenarcpu();
	}
	empujecpu(); //ojo acá está el llamado a la función de empujar
	if (((imov==(iref+1))&&(jmov==jref)&&(matriz[imov][jmov]=='-'))||((imov==(iref-1))&&(jmov==jref)&&(matriz[imov][jmov]=='-'))||
		((imov==iref)&&(jmov==(jref-1))&&(matriz[imov][jmov]=='-'))||((imov==iref)&&(jmov==(jref+1))&&(matriz[imov][jmov]=='-'))){
		// condiciones necesarias para que sea "legal" la jugada
		aux1 = matriz[iref][jref];
		matriz [iref][jref] = '-';
		matriz [imov][jmov] = aux1;
		printf("Eligió la pieza: %d %d \n", iref, jref);
		printf("Se movió a : %d %d\n", imov, jmov);
		counturncpu++;
		imprimirtablero(matriz);
	}
	if (((imov==(iref+1))&&(jmov==jref)&&(matriz[imov][jmov]=='='))||((imov==(iref-1))&&(jmov==jref)&&(matriz[imov][jmov]=='='))||
		((imov==iref)&&(jmov==(jref-1))&&(matriz[imov][jmov]=='='))||((imov==iref)&&(jmov==(jref+1))&&(matriz[imov][jmov]=='='))){
		// se metió en la trampa por depresivo (hagase la distinción para saber qué ocurre en este caso, el algoritmo es igual que el de arriba)
		aux1 = matriz[iref][jref];
		matriz [iref][jref] = '-';
		matriz [imov][jmov] = aux1;
		printf("Eligió la pieza: %d %d \n", iref, jref);
		printf("Se movió a : %d %d\n", imov, jmov);
		counturncpu++;
		imprimirtablero(matriz);
	}
	printf("Quiere la pieza: %d %d \n", iref, jref);
	printf("Intenta moverse a: %d %d\n", imov, jmov);
}

int main(void){
	srand (time(NULL));
	int	elegiremp=1;
	printf ("Defina la cantidad de turnos para cada jugador:\n"); //definir cantidad de movimientos
	scanf ("%d", &limiteturn);
	while (limiteturn>8){ //tiene que ser un número limitado de movimientos sino no tiene sentido
		printf ("Demasiados movimientos, por favor ingrese una cantidad menor:\n");
		scanf ("%d", &limiteturn);
	}
	selectablero();
	imprimirtablero(matriz);
	printf ("Puede elegir si quiere empezar usted presionando 1, si quiere que la cpu lo haga presione 2\n");
	printf ("O también puede presionar cualquier otro valor para elegir al azar\n");
	elegirjugador(elegiremp);
	if (turnjugador==1){
		posjugador();
	}
	else if (turncpu==1){
		poscpu();
	}
	while (ganador()!=1||ganador()!=2){
		while (turnjugador==1&&turncpu==0){
			movjugador();
			trampa();
			imprimirtablero(matriz);
			printf("turnos: %d, limite de turnos:%d\n", counturnj, limiteturn);
			if (ganador()==1){
				printf("\nVICTORIA\n");
				return 1;
			}
			else if (ganador()==2){
				printf("\nDERROTA\n");
				return 0;
			}
			if (counturnj==limiteturn){
				printf ("Se acabó el turno del jugador ahora es el turno de la máquina\n");
				turnjugador=0;
				turncpu=1;
				counturnj=0;
				break;
				jugadasglobales=jugadasglobales+turnjugador;
			}
			else{
				posjugador();
			}
		}
		poscpu();
		while (turnjugador==0&&turncpu==1){
			movcpu();
			trampa(); /*si se movió a una trampa, se imprime en el siguiente ciclo porque los print de
			tablero de la cpu se hacen cuando se realiza una jugada correcta"*/
			printf("turnos: %d, limite de turnos:%d\n", counturncpu, limiteturn);
			if (ganador()==1){
				printf("\nVICTORIA\n");
				return 1;
			}
			else if (ganador()==2){
				printf("\nDERROTA\n");
				return 0;
			}
			if (counturncpu==limiteturn){
				printf ("Se acabó el turno de la cpu ahora es el turno del jugador\n");
				turnjugador=1;
				turncpu=0;
				counturncpu=0;
				break;
				jugadasglobales=jugadasglobales+turncpu;
			}
			else{
				poscpu();
			}
		}
		posjugador();
		}
}
