

#include <iostream>
#include <string>
using namespace std;

int lim_infx = 1, lim_supx = 8, lim_infy = 1, lim_supy = 8;
const int tableroWidth = 8;
const int tableroHeight = 8;
char tablero[tableroHeight][tableroWidth] = {},
letterToInt[8][2] = { {'a','1'},{'b','2'},{'c','3'},{'d','4'},{'e','5'},{'f','6'},{'g','7'},{'h','8'}};


void MovimientoReina(int x, int y, int i, int j, int torres[2][2]) {
	int movX, movY;
	bool paso = true;
	movX = x + i;
	movY = y + j;
	if (movX < lim_infx || movX > lim_supx || movY < lim_infy || movY > lim_supy) paso = false;
	if (movX == torres[0][0] || movX == torres[1][0] || movY == torres[0][1] || movY == torres[1][1]) {
		tablero[movX][movY] = 'X';
	}
	else {
		tablero[movX][movY] = 'V';
	}
}

void MostrarTablero() {
	cout << "    A   B   C   D   E   F   G   H" << endl;
	cout << "  +---+---+---+---+---+---+---+---+" << endl;
	for (int h = 0; h < tableroHeight; h++) {
		cout << h+1 << " | ";

		for (int w = 0; w < tableroWidth; w++) {
			if (tablero[h][w] == NULL) tablero[h][w] = ' ';
			cout << tablero[h][w] + " | ";
		}

		cout << endl << "  +---+---+---+---+---+---+---+---+" << endl;
	}
}

void stringToArray(string str, char arr[2]) {
	if (str.length() == 2 && isdigit(str[0]) == false && isdigit(str[1])) {
		arr[0] = str[0];
		arr[1] = str[1];
	}
	else {
		cout << "Formato invalido, asegurese de colocar primero la columna y luego la fila" << endl;
		return;
	}

	for (int i = 0; i < tableroWidth; i++) {
		if (letterToInt[i][0] == arr[0]) {
			arr[0] = letterToInt[i][1];
		}
	}
}



int main()
{

	int torres[2][2];
	char posTorre1[2], posTorre2[2], posReina[2];
	string input;

	MostrarTablero();

	cout << "Inserte la posicion de la primera torre (ej. d3, D3): ";
	cin >> input;
	//stringToArray(input, posTorre1);
	tablero[posTorre1[0]][posTorre1[1]] = 'T';
	system("CLS");
	MostrarTablero();

	cout << "Inserte la posicion de la segunda torre (ej. d3, D3): ";
	cin >> input;
	//stringToArray(input, posTorre2);

	

}

