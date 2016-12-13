// clang nb-sp.c -o nb -lgsl -lgslcblas -O3 -DHAVE_INLINE

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <sys/time.h> 
#include <string.h>
#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>
#include <gsl/gsl_sf_exp.h>

#define FNSIZE 128

int ij_to_pos(int i, int j, int s){
	int pos = j + i * s;
	return pos;
}

int * nei_8(int i, int j, int s){
	int bi = i-1;
	int ai = i+1;
	int bj = j-1;
	int aj = j+1;
	// enforce boundary conditions on i
	bi  =  bi  <  0  ?  s   +  bi  :  bi;
	ai  =  ai  <  0  ?  s   +  ai  :  ai;
	bi  =  bi  >=  s  ?  bi  -  s   :  bi;
	ai  =  ai  >=  s  ?  ai  -  s   :  ai;
	// enforce boundary conditions on j
	bj  =  bj  <  0  ?  s   +  bj  :  bj;
	aj  =  aj  <  0  ?  s   +  aj  :  aj;
	bj  =  bj  >= s  ?  bj  -  s   :  bj;
	aj  =  aj  >=  s  ?  aj  -  s   :  aj;
	// return a list of matrix positions
	int *pos = (int*) malloc(8 * sizeof(int));
	pos[0] = ij_to_pos(bi, bj, s);
	pos[1] = ij_to_pos(bi, j, s);
	pos[2] = ij_to_pos(bi, aj, s);
	pos[3] = ij_to_pos(i, bj, s);
	pos[4] = ij_to_pos(i, aj, s);
	pos[5] = ij_to_pos(ai, bj, s);
	pos[6] = ij_to_pos(ai, j, s);
	pos[7] = ij_to_pos(ai, aj, s);
	return &(pos[0]);
}

int main(int argc, char *argv[]) {
	// Step 1: see the RNG
	clock_t start, stop;
	// Initiate the GSL random number generator
	gsl_rng *rng = gsl_rng_alloc(gsl_rng_taus2);
	struct timeval t1;
	gettimeofday(&t1, NULL);
	gsl_rng_set(rng, t1.tv_usec * t1.tv_sec);

	// Model parameters
	double Lh = 2.0;
	double Lp = 1.0;
	double a = 0.068;
	double dh = 0.05;
	double dp = 0.1;

	// Simulation parameters
	unsigned int SimTime = 250;
	unsigned int GridSize = 100;

	// We generate FOUR grids
	double *past_host = (double*) malloc( GridSize * GridSize * sizeof(double));
	double *past_para = (double*) malloc( GridSize * GridSize * sizeof(double));
	double *curr_host = (double*) malloc( GridSize * GridSize * sizeof(double));
	double *curr_para = (double*) malloc( GridSize * GridSize * sizeof(double));

	// We add some hosts and parasites at random in the grids
	for (int i = 0; i < GridSize; ++i)
	{
		for (int j = 0; j < GridSize; ++j)
		{
			int po = ij_to_pos(i, j, GridSize);
			past_host[po] = gsl_rng_uniform_int(rng, (int) 10);
			past_para[po] = gsl_rng_uniform_int(rng, (int) 10);
		}
	}

	// Text files
	FILE *hostout;
	FILE *paraout;

	// We can now start the simulation - yeah!
	for (int CurrentTime = 0; CurrentTime < SimTime; ++CurrentTime)
	{
		// We move along the grid
		for (int i = 0; i < GridSize; ++i)
		{
			for (int j = 0; j < GridSize; ++j)
			{
				int po = ij_to_pos(i, j, GridSize);
				// We get the neighbors
				int * nei = nei_8(i, j, GridSize);
				// Get the number of residents after imigration
				double Hstar = (1-dh)*past_host[po];
				double Pstar = (1-dp)*past_para[po];
				// Calculate influx of population
				for (int n = 0; n < 8; ++n)
				{
					Hstar += (dh/8)*past_host[nei[n]];
					Pstar += (dp/8)*past_para[nei[n]];
				}
				Pstar = Pstar < 0 ? 0 : Pstar;
				Hstar = Hstar < 0 ? 0 : Hstar;
				Pstar = Pstar > 300 ? 300 : Pstar;
				Hstar = Hstar > 300 ? 300 : Hstar;
				// Get the population sizes in the cell at the next time-step
				double ParSearch = -a * Pstar;
				curr_host[po] = Lh * Hstar * gsl_sf_exp(ParSearch);
				curr_para[po] = Lp * Hstar * (1 - gsl_sf_exp(ParSearch));
			}
		}
		// Finally, we write the current grids to a file
		char tfname[FNSIZE]; // The filename buffer.
		snprintf(tfname, sizeof(char) * FNSIZE, "grids/h_%05d.txt", CurrentTime);
		hostout = fopen(tfname, "w");
		for (int i = 0; i < GridSize; ++i)
		{
			for (int j = 0; j < GridSize; ++j)
			{
				int po = ij_to_pos(i, j, GridSize);
				fprintf(hostout, "%.4f ", curr_host[po]);
			}
			fprintf(hostout, "\n");
		}
		fclose(hostout);
		// Same for the parasites
		snprintf(tfname, sizeof(char) * FNSIZE, "grids/p_%05d.txt", CurrentTime);
		paraout = fopen(tfname, "w");
		for (int i = 0; i < GridSize; ++i)
		{
			for (int j = 0; j < GridSize; ++j)
			{
				int po = ij_to_pos(i, j, GridSize);
				fprintf(paraout, "%.4f ", curr_para[po]);
			}
			fprintf(paraout, "\n");
		}
		fclose(paraout);
		// We update the "old" grid
		for (int i = 0; i < GridSize; ++i)
		{
			for (int j = 0; j < GridSize; ++j)
			{
				int po = ij_to_pos(i, j, GridSize);
				past_host[po] = curr_host[po];
				curr_host[po] = 0.0;
				past_para[po] = curr_para[po];
				curr_para[po] = 0.0;
			}
		}
	}
}
