#include <iostream>
#include <vector>
#include <cmath>

#include "WavFile.h"

using namespace std;

int main () {
  	WavInFile in ("Vox.wav");
  	int samples = in.getNumSamples ();
  	float sr = in.getSampleRate();
  	cout << samples << " " << sr << endl;

  	vector<float> x (samples);
  	vector<float> y (samples);

  	in.read (&x[0], samples);

  	float cutoff = 20.;
  	float omega = (2. * M_PI * cutoff) / sr;
  	float det = 2. - cos (omega);

  	float a1 = cos (omega) - 2. + sqrt (det * det - 1.);
  	float b0 = 1. + a1;

  	cout << "a1 = " << a1 << endl;
  	cout << "b0 = " << b0 << endl;


  	float z1 = 0.;

  	for (int i = 0; i < samples; i = i + 1) {
  		y[i] = b0 * x[i] - a1 * z1;
  		z1 = y[i];
  	}

  	WavOutFile out("filter.wav", sr, 16, 1);
  	out.write (&y[0], samples);


  	return 0;
}