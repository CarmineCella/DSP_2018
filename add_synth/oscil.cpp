#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>


using namespace std;

int main () {
	int N = 4096;
	vector<float> x (N + 1);

	for (int i = 0; i < N; i = i + 1) {
		x[i] = sin (2. * M_PI * (float)i / (N));
		cout << i << " " << x[i] << endl;
	}
	x[N] = x[0]; // guard point

	float fs = 44100; // Hz
	float fy = 440; // Hz
	float fn = fs / (float) N;

	float k = fy / fn;

	float phi = 0;  
	float dur = 3; // seconds
	int samples = (int) (dur * fs);

	ofstream out32 ("out32.pcm");
	ofstream out16 ("out16.pcm");
	ofstream out8 ("out8.pcm");
	ofstream phase ("phase.pcm");

	for (int i = 0; i < samples; i = i + 1) {
		int index = (int) phi;
		float frac = phi - index;
		
		float s32 = (1. - frac) * x[index] + frac * x[index + 1]; // linear interp
		short s16 = (short) (s32 * 32767);
		char s8 = (char) (s32 * 127);

		out32.write ((char*) &s32, sizeof (float));
		out16.write ((char*) &s16, sizeof (short));
		out8.write ((char*) &s8, sizeof (char));

		float phi_tmp = phi / N;
		phase.write ((char*) &phi_tmp, sizeof (float));

		phi = phi + k;
		if (phi > N) phi = phi - N; // phase wrap
	}

	out32.close ();
	out16.close ();
	out8.close ();
	phase.close ();

	return 0;
}