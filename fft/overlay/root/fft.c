#include <complex.h>
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/types.h>

static inline uint32_t rdcyc() {
	  uint32_t val;
	    asm volatile("rdcycle %0 ;\n" : "=r"(val)::);
	      return val;
}

void linspace(int start, int stop, uint num, _Complex double *res) {
	  float interval = (stop - start + 1) / (float)num;

	    int counter = 0;
	      for (float i = start; i <= stop; i += interval) {
		          res[counter] = i;
			      counter++;
			        }
}

void genSineWave(int size, _Complex double *data) {
	  linspace(1, 10, size, data);
	    for (int i = 0; i < size; i++) {
		        data[i] = csin(data[i]);
			  }
}

const double PI = 3.141592653589793238460;

void splitEvenOddPositioned(complex double *data, int size,
		                            complex double *even, complex double *odd) {
	  int index = 0;
	    for (int i = 0; i < size; i++) {
		        if (i % 2 == 0) {
				      even[index] = data[i];
				          } else {
						        odd[index] = data[i];
							      index++;
							          }
			  }
}

void fft(complex double *data, int size) {
	  if (size <= 1) {
		      return;
		        }
	    complex double even[size / 2];
	      complex double odd[size / 2];
	        splitEvenOddPositioned(data, size, even, odd);

		  fft(even, size / 2);
		    fft(odd, size / 2);

		      for (int k = 0; k < size / 2; k++) {
			          complex double t = odd[k] * cexp(-2I * PI * k / size);
				      data[k] = even[k] + t;
				          data[k + size / 2] = even[k] - t;
					    }
}

int main(int argc, char const *argv[]) {
	  if (argc < 2) {
		      printf("needs an argument. int size\n");
		          exit(1);
			    }

	    int size = atoi(argv[1]);
	      complex double data[size];
	        genSineWave(size, data);

#ifdef RDCYCLE
		  t_beg = rdcyc();
#endif
		    clock_t start, end;
		      start = clock();
		        fft(data, size);
			  end = clock();
#ifdef RDCYCLE
			    t_end = rdcyc();
			      printf("Cycle count: %d\n", t_end - t_beg);
#endif

			        printf("FFT,%d,%.f µsec\n", size,
						         1000000 * (double)(end - start) / (double)CLOCKS_PER_SEC);
				  return 0;
}

