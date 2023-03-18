#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;

//functions prototypes
void getFile(ifstream& in_s);
void invert(int ar1[200][200], int rows, int columns);
void avg_row(int ar1[200][200], int rows, int columns, ofstream& outData);
void avg_column(int ar1[200][200], int rows, int columns, ofstream& outData);
void avg_image(int ar1[200][200], int rows, int columns, ofstream& outData);

int main() {
	int ar1[200][200];
	int arWhite[200][200];
	int rows, columns, maxGreyLevel;
	char line1[3];

	ifstream in_stream;
	ofstream out_stream("OutImage.pgm");
	ofstream outData("OutData.txt");
	if (out_stream.fail()) {
		cout << "output image file opening failed..." << endl;
		exit(1);
	}
	if (outData.fail()) {
		cout << "output data file opening failed..." << endl;
		exit(1);
	}
	getFile(in_stream);

	//takes in the first line, p2 in this case
	for (int i = 0; i < 3; i++) {
		in_stream.get(line1[i]);
	}
	in_stream >> rows >> columns >> maxGreyLevel;

	//maybe make this into a function to be more organized
	for (int j = 0; j < rows; j++) {
		for (int k = 0; k < columns; k++) {
			in_stream >> ar1[j][k];
		}
	}

	/*
	call the invert function before calculating whitespace needed
	*/
	invert(ar1,rows,columns);

	int temp;
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++) {
			if (ar1[i][j] < 10) {
				arWhite[i][j] = 1;
			}
			else if (ar1[i][j] >= 10 && ar1[i][j] < 100) {
				arWhite[i][j] = 2;
			}
			else if (ar1[i][j] >= 100) {
				arWhite[i][j] = 3;
			}
		}
	}

	cout << endl;

	//now print the array with whitespaces to file
	for (int i = 0; i < 3; i++) {
		out_stream << line1[i];
	}

	out_stream << rows << " " << columns << endl
		<< maxGreyLevel << endl;

	for (int j = 0; j < rows; j++) {
		int count(0);
		out_stream << "  ";
		for (int k = 0; k < columns; k++) {
			if (count == 0) {
				out_stream << ar1[j][k];
			}
			else {
				if (arWhite[j][k] == 1) {
					out_stream << "    ";
				}
				else if (arWhite[j][k] == 2) {
					out_stream << "   ";
				}
				else if (arWhite[j][k] == 3) {
					out_stream << "  ";
				}
				out_stream << ar1[j][k];
			}
			count++;
		}
		if (j < rows - 1)
			out_stream << endl;
	}

	avg_row(ar1, rows, columns, outData);
	avg_column(ar1, rows, columns, outData);
	avg_image(ar1, rows, columns, outData);

	in_stream.close();
	out_stream.close();
	outData.close();
	return 0;
}

void getFile(ifstream& in_s) {
	char inputName[30];
	cout << "Please enter the file name that you would like modified: ";
	cin >> inputName;
	in_s.open(inputName);

	if (in_s.fail()) {
		cout << "Input file opening failed..." << endl;
		exit(1);
	}
}

void invert(int ar1[200][200], int rows, int columns) {
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++) {
			ar1[i][j] = abs(255 - ar1[i][j]);
		}
	}
}

void avg_row(int ar1[200][200], int rows, int columns, ofstream& outData) {
	double avg(0);
	for (int i = 0; i < rows; i++) {
		int sum(0);
		for (int j = 0; j < columns; j++) {
			sum += ar1[i][j];
		}
		avg = sum / columns;
		outData << "Avg Row (" << i + 1 << ") : " << avg << endl;
	}
	outData << endl;
}

void avg_column(int ar1[200][200], int rows, int columns, ofstream& outData) {
	double avg(0);
	for (int i = 0; i < columns; i++) {
		int sum(0);
		for (int j = 0; j < rows; j++) {
			sum += ar1[j][i];
		}
		avg = sum / rows;
		outData << "Avg Column (" << i + 1 << ") : " << avg << endl;
	}
	outData << endl;
}

void avg_image(int ar1[200][200], int rows, int columns, ofstream& outData) {
	double avg(0);
	int sum(0);
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++) {
			sum += ar1[i][j];
		}
	}
	avg = sum / (rows * columns);
	outData << "Avg Pixel : " << avg << endl;
}