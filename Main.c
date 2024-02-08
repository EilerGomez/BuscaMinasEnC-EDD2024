#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<stdbool.h>
#include<time.h>


void imprimirMapa(char mapa[6][6]){
    int x,y;
    for(y=0;y<6;y++){
        for(x=0;x<6;x++){
            printf("%c  ",mapa[y][x]);
        }
        printf("\n");
    }
}

char elejirNickName(char mapa[6][6]){
	bool elegido = false;
	int jugador=0;
	char simbolos[5];
	simbolos[0]='#';
	simbolos[1]='*';
	simbolos[2]='^';
	simbolos[3]='$';
	simbolos[4]='@';
	while(!elegido){
		printf(" 0. #\n");
		printf(" 1. *\n");
		printf(" 2. ^\n");
		printf(" 3. $\n");
		printf(" 4. @\n");
		printf("Elije uno de los jugadores:\n");
		scanf("%d", &jugador);
		if(jugador<5){
			//simbolo=simbolos[jugador];
			mapa[0][0]=simbolos[jugador];
			elegido=true;
		}else{
			elegido=false;
		}
	}
	return simbolos[jugador];
}

void inicializarMapa(char mapa[6][6]){
    for (int i = 0; i < 6; ++i) {
        for (int j = 0; j < 6; ++j) {
            mapa[i][j]='X';
        }
    }
}
void mostrarContenidoDelMapa(int posX, int posY, char mapa[6][6], char tableroConMinas[6][6]){
    mapa[posY][posX]=tableroConMinas[posY][posX];
    if(tableroConMinas[posY][posX]=='X'){
        mapa[posY][posX]='-';
    }
}

void mostrarEspaciosEnElMapa(int posX, int posY, char mapa[6][6], char tableroConMinas[6][6]){
    int aleatorio=rand()%2;
    if(aleatorio==1){
        int randomI=2;
        int randomJ=2;;
        for (int i = -1; i < randomI; ++i) {
            for (int j = -1; j < randomJ; ++j) {
                int nuevaFila=posY+i;
                int nuevaColumna=posX+j;
                if(nuevaFila>=0 && nuevaFila < 6 && nuevaColumna>=0 && nuevaColumna<6){
                    //mapa[nuevaFila][nuevaColumna]=tableroConMinas[nuevaFila][nuevaColumna];
                    mostrarContenidoDelMapa(nuevaColumna, nuevaFila,mapa,tableroConMinas);
                }
            }
        }
    }
}

bool metodoParaganar1(char mapa[6][6]){
    bool haGanado=true;
    for (int i = 0; i < 6; ++i) {
        for (int j = 0; j < 6; ++j) {
            if(mapa[i][j]=='X'){
                haGanado=false;
                j=6; i=6;
            }
        }
    }
    return haGanado;
}

bool metodoParaGanar2(char mapa[6][6]){
    bool haGanado=false;
    int contadorQ=0;
    int contadorX=0;
    for (int i = 0; i < 6; ++i) {
        for (int j = 0; j < 6; ++j) {
            if(mapa[i][j]=='Q'){
                contadorQ++;
            }else if(mapa[i][j]=='X'){
                contadorX++;
            }
        }
    }
    if(contadorQ+contadorX==6){
        haGanado=true;
    }

    return haGanado;
};
void preguntarMovimiento(int posX, int posY, char mapa[6][6], char simbolo, char mapaConMinas[6][6]){
    int movimiento=0;
    int y;
    int x;
    char auxSimb='X';
    while(movimiento>=0){
        printf("Jugador: %c, minas: Q, espacio vacio: - ",simbolo);
        printf("0-6: Cantidad de minas al rededor\n");
        printf("1: SELECCIONAR\n");
        printf("4: Izquierda\n");
        printf("8: Arriba\n");
        printf("2: Abajo\n");
        printf("6: Derecha\n...");
        //auxSimb = mapa[posY][posX];

        x=posX;
        y=posY;
        scanf("%d", & movimiento);

        if(movimiento==4){
            x=x-1;
            if(x>=0){
                mapa[posY][posX]=auxSimb;
                posX=x;
                posY=y;
                auxSimb=mapa[posY][posX];
                mapa[posY][posX]=simbolo;
            }

        }else if(movimiento == 8){
            y=y-1;
            if(y>=0){
                mapa[posY][posX]=auxSimb;
                posX=x;
                posY=y;
                auxSimb=mapa[posY][posX];
                mapa[posY][posX]=simbolo;
            }

        }else if(movimiento==2){
            y=y+1;
            if(y<6){
                mapa[posY][posX]=auxSimb;
                posX=x;
                posY=y;
                auxSimb=mapa[posY][posX];
                mapa[posY][posX]=simbolo;
            }


        }else if(movimiento==6){
            x=x+1;
            if(x<6){
                mapa[posY][posX]=auxSimb;
                posX=x;
                posY=y;
                auxSimb=mapa[posY][posX];
                mapa[posY][posX]=simbolo;
            }

        }
        if(movimiento==1){
            if(auxSimb=='X'){
                mostrarContenidoDelMapa(posX, posY,mapa,mapaConMinas);
                if(mapa[posY][posX]=='Q'){
                    printf("\nHAS PERDIDO, PISASTE UNA MINA, INTENTA DE NUEVO!!!!!!!!!!\n\nMAPA CON MINAS:\n");
                    imprimirMapa(mapaConMinas);
                    printf("\nMAPA ORIGINAL: \n");
                    movimiento=-1;
                }else{
                    if(posX==0 && posY==0){
                        auxSimb=mapa[posY][posX];
                    }else{
                        auxSimb=mapa[0][0];
                    }
                    if(mapa[posY][posX]=='-'||mapa[posY][posX]=='1' ){
                        mostrarEspaciosEnElMapa( posX,  posY,  mapa, mapaConMinas);
                    }
                    imprimirMapa(mapa);
                    system("pause");

                    posX=0;
                    posY=0;
                    mapa[posX][posY]=simbolo;
                    printf("\n");
                    if(metodoParaganar1(mapa)|| metodoParaGanar2(mapa)){
                        printf("\nFELICIDADES HAS GANADO EL JUEGO!!!!!!!!!!!!!!!!!!!!!!!\n\n");
                        imprimirMapa(mapaConMinas);
                        system("pause");
                        movimiento=-1;
                    }
                }
                //logica para haber ganado

            }

        }
        imprimirMapa(mapa);
    }

}


void mostrarMenu(char mapa[6][6],char simboloJugador, int posX, int posY,char mapaConMinas[6][6]){
	int valorMenu;
	printf("Bienvenido a mi juego Buscaminas\n");
	printf("1. Empezar juego\n");
	printf("2. Cerrar\n");
	printf("Elije una opcion:");
	scanf("%d",&valorMenu);
	if(valorMenu==1){
		inicializarMapa(mapa);
		simboloJugador=elejirNickName(mapa);
		imprimirMapa(mapa);
		preguntarMovimiento(posX, posY,mapa,simboloJugador,mapaConMinas);
	}else if(valorMenu==2){
		exit(-1);
	}
}

void crearMinas(int minasX[6], int minasY[6]){
	minasX[0]=0;minasX[1]=0;minasX[2]=0;minasX[3]=0;minasX[4]=0;minasX[5]=0;
	minasY[0]=0;minasY[1]=0;minasY[2]=0;minasY[3]=0;minasY[4]=0;minasY[5]=0;
	int i;
	for(i=0; i<6;i++){
		bool estaLaMina=true;
		while(estaLaMina){
			 int numX=rand() % 6;
			 int numY=rand() % 6;

			int j;
			for(j=0;j<6;j++){
				if(minasX[j]==numX && minasY[j]==numY){
					estaLaMina=true;
					j=6;
				}else{
					estaLaMina=false;
				}
			}
			if(estaLaMina==false){
				minasX[i]=numX;
				minasY[i]=numY;
			}

		}

	}
}

void crearMapaConMinas (char mapa[6][6], int minasX[6], int minasY[6]){
	int i;
	for(i=0; i<6; i++){
		mapa[minasY[i]][minasX[i]]='Q';
	}
}
//contar las minas que hay alrededeor
int contarMinasAlrededor(char tablero[6][6], int fila, int columna) {
    int contador = 0;
    int i;
    for ( i = -1; i <= 1; i++) {
    	int j;
        for ( j = -1; j <= 1; j++) {
            int nuevaFila = fila + i;
            int nuevaColumna = columna + j;
            if (nuevaFila >= 0 && nuevaFila < 6 && nuevaColumna >= 0 && nuevaColumna < 6) {
                if (tablero[nuevaFila][nuevaColumna] == 'Q') {
                    contador++;
                }
            }
        }
    }
    return contador;
}
// Calcular y asignar números a las casillas
void asignarNumerosALasCasillas(char tablero [6][6]){
	int i,j;
	for ( i = 0; i < 6; i++) {
        for ( j = 0; j < 6; j++) {
            if (tablero[i][j] != 'Q') {
                int minasAlrededor = contarMinasAlrededor(tablero, i, j);
                if (minasAlrededor > 0) {
                    tablero[i][j] = minasAlrededor + '0';
                }
            }
        }
    }
}


int main(){
	char simboloJugador='P';
	char mapa[6][6];
	char mapaConMinasYNums[6][6];
	int posX=0;
	int posY=0;
	int minasX[6];
	int minasY[6];
	srand(time(NULL));

	crearMinas(minasX,minasY);
	inicializarMapa(mapaConMinasYNums);
	crearMapaConMinas(mapaConMinasYNums,minasX,minasY);
	asignarNumerosALasCasillas(mapaConMinasYNums);
	//imprimirMapa(mapaConMinasYNums);
	mostrarMenu(mapa, simboloJugador, posX, posY,mapaConMinasYNums);
	system("pause");

	return 0;
}


