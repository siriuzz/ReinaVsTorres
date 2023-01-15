

#include <iostream>
#include <string>
#include <cstring>
using namespace std;

int lim_infx = 0, lim_supx = 7, lim_infy = 0, lim_supy = 7;
const int tableroWidth = 8;
const int tableroHeight = 8;
char tablero[tableroHeight][tableroWidth],
letterToInt[8][2] = { {'a','1'},{'b','2'},{'c','3'},{'d','4'},{'e','5'},{'f','6'},{'g','7'},{'h','8'} };


void MovimientoReina(int x, int y, int i, int j, int torres[2][2]) {
	int movX, movY;
	bool paso = true;
	movX = x + i;
	movY = y + j;
	if (movX < lim_infx || 
		movX > lim_supx || 
		movY < lim_infy ||
		movY > lim_supy || 
		(movX == torres[0][0] && movY == torres[0][1]) || 
		(movX == torres[1][0] && movY == torres[1][1])) return;

	if (movX == torres[0][0] || movX == torres[1][0] || movY == torres[0][1] || movY == torres[1][1]) {
		tablero[movY][movX] = 'X';
	}
	else {
		tablero[movY][movX] = 'V';
	}
	if (paso != false) MovimientoReina(movX, movY, i, j, torres);
}

void MostrarTablero() {
	cout << "    A   B   C   D   E   F   G   H" << endl;
	cout << "  +---+---+---+---+---+---+---+---+" << endl;
	for (int h = 0; h < tableroHeight; h++) {
		cout << h + 1 << " | ";

		for (int w = 0; w < tableroWidth; w++) {
			if (tablero[h][w] != ' ') {
				cout << tablero[h][w] << " | ";
				continue;
			}
			cout << "  | ";
		}

		cout << endl << "  +---+---+---+---+---+---+---+---+" << endl;
	}
}

void ReiniciarTablero() {
	for (int h = 0; h < tableroHeight; h++) {
		for (int w = 0; w < tableroWidth; w++) {
			tablero[h][w] = ' ';
		}
	}
}

bool stringToArray(string str, char arr[2]) {
	str[0] = tolower(str[0]);
	bool a = int(str[0]) < 105;
	if (str.length() == 2 && (isdigit(str[0]) == false) && isdigit(str[1]) && int(str[0]) > 96 && int(str[0]) < 105 && (str[1] - '0') > 0 && (str[1] - '0') < 9) {
		arr[0] = str[0];
		arr[1] = str[1];
	}
	else {
		cout << "Fomato incorrecto, asegurese de insertar primero una letra de la A a la H y numeros del 1 al 8" << endl;
		ReiniciarTablero();
		system("PAUSE");
		return false;
	}

	for (int i = 0; i < tableroWidth; i++) {
		if (letterToInt[i][0] == arr[0]) {
			arr[0] = letterToInt[i][1];
		}
	}
	return true;
}



void recorridosReina(int reina[2], int torres[2][2]) {
	for (int i = -1; i < 2; i++) {
		for (int j = -1; j < 2; j++) {
			if (j == 0 && i == 0) continue;
			MovimientoReina(reina[0], reina[1], i, j, torres);
		}
	}
	//MovimientoReina(reina[0], reina[1], -1, -1, torres); //arriba, izquierda
	//MovimientoReina(reina[0], reina[1], -1, 0, torres); //arriba
	//MovimientoReina(reina[0], reina[1], -1, 1, torres); //arriba, derecha
	//MovimientoReina(reina[0], reina[1], 0, -1, torres); //izquierda
	//MovimientoReina(reina[0], reina[1], 0, 1, torres); // derecha
	//MovimientoReina(reina[0], reina[1], 1, -1, torres); //abajo, izquierda
	//MovimientoReina(reina[0], reina[1],1, 0, torres); //abajo
	//MovimientoReina(reina[0], reina[1], 1, 1, torres); // abajo, derecha
}

int main()
{
	ReiniciarTablero();
	do {
		system("CLS");
		int torres[2][2];
		int reina[2];
		char posTorre1[2], posTorre2[2], posReina[2];
		string input;

		MostrarTablero();

		cout << "Inserte la posicion de la primera torre (ej. d3, D3): ";
		cin >> input;
		if(!stringToArray(input, posTorre1)) continue;

		torres[0][0] = int(posTorre1[0] - '0') - 1;
		torres[0][1] = int(posTorre1[1] - '0') - 1;
		tablero[torres[0][1]][torres[0][0]] = 'T';

		cout << "Inserte la posicion de la segunda torre (ej. d3, D3): ";
		cin >> input;
		if(!stringToArray(input, posTorre2)) continue;
		torres[1][0] = int(posTorre2[0] - '0') - 1;
		torres[1][1] = int(posTorre2[1] - '0') - 1;

		if (torres[0][0] == torres[1][0] && torres[0][1] == torres[1][1]) {
			cout << "Dos torres no pueden ocupar el mismo lugar" << endl;
			system("PAUSE");
			ReiniciarTablero();
			continue;
		}
		tablero[torres[1][1]][torres[1][0]] = 'T';

		cout << "Inserte la posicion de la Reina (ej. d3,D3): ";
		cin >> input;
		if(!stringToArray(input, posReina)) continue;
		reina[0] = int(posReina[0] - '0') - 1;
		reina[1] = int(posReina[1] - '0') - 1;
		tablero[reina[1]][reina[0]] = 'R';

		if ((torres[0][0] == reina[0] && torres[0][1] == reina[1]) || (torres[1][0] == reina[0] && torres[1][1] == reina[1])) {
			cout << "La reina no puede ocupar el mismo lugar de una torre" << endl;
			system("PAUSE");

			ReiniciarTablero();
			continue;
		}

		recorridosReina(reina,torres);
		MostrarTablero();
		cout << "Desea reiniciar el tablero?\n(1)Si\n(2)No" << endl;
		cin >> input;
		if (input == "1") continue;
		else if (input == "2") break;
		else {
			cout << "Valor invalido, reiniciando el programa" << endl;
			ReiniciarTablero();
			system("PAUSE");
		}
	} while (true);





}

