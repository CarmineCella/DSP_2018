#include "WavFile.h"

#include <iostream> // libreria input/output su console
#include <fstream>
#include <vector>
#include <complex>
#include <cmath>

using namespace std;

typedef complex<float> Complex;
const float TWOPI = 2. * M_PI;

void dft (vector<float>& data, vector<Complex>& t1) {
	int N = data.size ();
	
	for (int n = 0; n < N; n = n + 1) {
		t1[n] = 0.;
		for (int k = 0; k < N; k = k + 1) {
			float omega = TWOPI * (float) n / N * (float) k;
			t1[n] += data[k] * Complex (cos (omega), -sin (omega));
		}
	}
}

int main (int argc, char* argv[]) {
	cout << "[manual_stft, ver. 1.00]" << endl;
	if (argc != 4) {
		cout << "invalid syntax" << endl;
		exit (1);
	}
	
	WavInFile input (argv[1]); // aperto il file di input
	ofstream output (argv[2]); // creato il file di ouput
	int WINDOWSIZE = atoi (argv[3]); // taglia DFT
	
	vector<float> data(WINDOWSIZE, 0);
	vector<Complex> t1(WINDOWSIZE, 0);
	
	int frame = 0;
	while (!input.eof ()) {
		input.read (&data[0], WINDOWSIZE);
		dft (data, t1);
		for (int i = 0; i < WINDOWSIZE; i = i + 1) {
			output << abs (t1[i]) << " ";
		}
		output << endl;
		cout << "frame: " << frame << endl;
		frame = frame + 1;
	}
	return 0;
}