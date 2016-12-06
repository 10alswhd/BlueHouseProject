#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

/*******************************************************/
/*   This is a simple GA solving a TSP problem, which  */
/*   read in as a distance matrix.                     */
/*                                                     */
/*   Here are the parameter settings, hopefully        */
/*   most are self-explanatory                         */
/*                                                     */
/*   NB: this code has a fixed random seed and so it   */
/*   will always give the same results for the same    */
/*   problem;  change the random seed (below) and      */
/*   recompile to give another indpendent trial.       */
/*   Normally, you should do several (e.g. 20) runs    */
/*   with different random seeds, and look at the mean */
/*   and standard deviation of the results.            */
/*******************************************************/

#define MAX_CITIES       20
#define MAX_POPULATION 1000
#define INPUTNUM         20  // max length in characters of
                             // a number in the input file

int population_size   =  20;
int elitism           =   1;   
int max_generations   =  100;

long random_seed = 71213;  

/*******************************************************/
/*  Datastructures for holding information about the   */
/*  problem being solved.   In this case, the problem  */
/*  is defined only by a distance matrix.              */
/*                                                     */
/*  distance[x][y]  gives the distance from x to y     */
/*                                                     */
/*  NB:  you may be thinking of the cities as          */
/*       A, B, ..., L,  or as  1, 2, ..., 12           */
/*       but this code thinks of them as               */
/*       0, 1, 2, ..., 11                              */
/*******************************************************/
                      
int number_of_cities = 10;

double distance[MAX_CITIES][MAX_CITIES];

/******************************************************/
/* Datastructures used by the GA;  mainly to hold the */
/* population and to do bookkeeping                   */
/*                                                    */
/* The 7th city (or 'gene') in the 5th candidate      */
/* solution (or 'chromosome') in the current          */
/* population will be                                 */
/*     current_population[4][6]                       */
/*                                                    */
/* The fitness of the 5th candidate solution will be  */ 
/* stored in  fitness[4]                              */ 
/******************************************************/

int current_population[MAX_POPULATION][MAX_CITIES];

int intermediate_population[MAX_POPULATION][MAX_CITIES];

double fitness[MAX_POPULATION];

int best_solution_so_far;  // will give index of fittest
                           // solution in current pop

double best_fitness_so_far; // will give actual fitness
                            // of the above


// the array below is used when generating random 
// permutations for the initial population

int reference_solution[MAX_CITIES];

/*******************************************************/
/* The main loop.  For simplicity and ease of reading  */
/* this code, the program takes no arguments.          */
/*                                                     */
/* Parameters and similar are set up above, and can    */
/* of course be edited, but you must then remember to  */
/* recompile the code!                                 */
/*******************************************************/


int main(int argc, char *argv)
{

  int generation;

  read_the_distance_matrix();

  initialise_the_population();

  evaluate_the_population();

  generation = 1;

  while(generation < max_generations)
    { 
      printf("generation %d\n", generation);

      produce_the_next_generation();
      evaluate_the_population();
      generation++; 
   }
}

  
/****************************************************/
/* the code assumes that there is a distance matrix */
/* in a file called "distances.txt"                 */
/****************************************************/
int read_the_distance_matrix(void)
{
  FILE *f;
  int city1, city2;
  char input_number_string[INPUTNUM];
  double input_number_double;

  f = fopen("distances.txt","r");

  for(city1=0; city1 < number_of_cities; city1++)
    {
      for(city2=0;  city2 < number_of_cities; city2++)
	{
           fscanf(f,"%s",input_number_string);
	   input_number_double = (double)(atof(input_number_string));
           distance[city1][city2] = input_number_double;
	}
    }
  fclose(f);

  // did we read it correctly?

    for(city1=0; city1 < number_of_cities; city1++)
    {
      for(city2=0;  city2 < number_of_cities; city2++)
	printf("%g ", distance[city1][city2]);
      printf("\n");
    }
    printf("\n");
}


int initialise_the_population(void)
{

  int chromosome, i, this_city, ref_length;

  // this is a good place to initialise the random number generator

  //  srand(random_seed);

  // this is also a good place to initialse the "best so far" fitness,
  // set to 0, so that the first evaluated fitness is
  // sure to become best so far to begin with.

  best_fitness_so_far = 0.0;

  for(chromosome = 0; chromosome < population_size; chromosome++)
    {
      // we will now efficiently generate a random permutation of 
      // the integers  0, 1, ..., N-1  where N is number_of_cities

      // this starts with a 'reference' permutation that is simply
      // 0, 1, 2, ..., N-1

      for(i=0; i<number_of_cities; i++)  reference_solution[i] = i;

      // ref_length gives the current length of the ref solution; it 
      // will gradually reduce

      ref_length = number_of_cities;

      // now repeatedly take random genes from the reference population
      // and build the current chromosome

      for(i = 0; i < number_of_cities; i++)
        {
              this_city = rand()%ref_length;
              current_population[chromosome][i] = reference_solution[this_city];
              reference_solution[this_city] = reference_solution[ref_length-1];
              ref_length--;
	}
    }
}


int evaluate_the_population(void)
{
  int chromosome, city, city1, city2;
  double  total_distance;

  for(chromosome = 0; chromosome < population_size; chromosome++)
    {
      // evaluate this chromosome;
 
      total_distance = 0;

      for(city=0; city<number_of_cities; city++)
	{
	  city1 = current_population[chromosome][city];
	  city2 = current_population[chromosome][(city+1)%number_of_cities];
          total_distance += distance[city1][city2];
	}
      if(total_distance == 0)
	{printf("Something funny is going on - no solution should have a tour distance of 0\n");
	  exit(0);
	}
        
      // note that we are using Roulette Wheel selection in this GA. So, although we
      // are trying to minimize the TSP tour distance, fitness needs to be something
      // that we are trying to *maximize*. So, we take 1/distance to be fitness:

      fitness[chromosome] = 1.0/total_distance;
    
      // now some book-keeping to keep track of best so far
      
      if(fitness[chromosome] >= best_fitness_so_far)
	{best_fitness_so_far = fitness[chromosome]; 
	  best_solution_so_far = chromosome;
	}
    }

  // print the population and fitnesses
 
  for(chromosome=0; chromosome < population_size; chromosome++)
    {  
     if(chromosome==best_solution_so_far) printf(" best so far: ");
      for(city1=0; city1 < number_of_cities; city1++) 
	printf("%d ", current_population[chromosome][city1]);
      printf(" - %g  (distance:  %g) \n", fitness[chromosome], 1.0/fitness[chromosome]);
      
    }
  printf("\n");
}
            
int produce_the_next_generation(void)
{
 
  int new_candidate, parent1, parent2, child[MAX_CITIES], gene;

  // now we will generate a population of new chromosomes, using 
  // the current_population as parents

  // if elitism is set to 1, this means we make sure the best of
  // the current population survives into the new population

  if(elitism==1)
    {for (gene = 0; gene < number_of_cities; gene++)
	intermediate_population[0][gene] = current_population[best_solution_so_far][gene];}
    

  for(new_candidate=elitism; new_candidate < population_size; new_candidate++)
    {
      
      parent1 = roulette_wheel_select();

      parent2 = roulette_wheel_select();

      crossover(parent1, parent2, child);
  
      mutate(child);

      for(gene=0; gene < number_of_cities; gene++)
        intermediate_population[new_candidate][gene] = child[gene];
    }

  // we have the entire new population, so copy it over to the
  // current population which, in the next step, we evaluate

  for(new_candidate=0; new_candidate < population_size; new_candidate++)
    for(gene=0; gene <number_of_cities; gene++)
      current_population[new_candidate][gene] = intermediate_population[new_candidate][gene];
  
}
     

int roulette_wheel_select(void)
{
  double fit_total, pointer, accumulating_fitness, randreal; 
  int chromosome, randint, selected;
 
  // first we need to add up the total of the fitnesses in the population

  fit_total = 0.0;
  for(chromosome = 0; chromosome < population_size; chromosome++)
    fit_total += fitness[chromosome];

  // now generate a random real number between 0 and fit_total ;
  // this amounts to spinning the roulette wheel.

  // get a random integer between 0 and 1000000 inclusive
  randint = rand()%1000001;
 
  // scale it to a real number between 0 and fit_total
  randreal = (double)(randint)/1000000.0;
  pointer = fit_total * randreal;

  // now go through the population until we get to the section of
  // the wheel that contains this pointer

  selected = 0;
  accumulating_fitness = 0.0;

  while(selected < population_size)
    {accumulating_fitness += fitness[selected];
      if(pointer < accumulating_fitness) break;
      selected++;
    }

  return(selected);
}


/************************************************************/
/*  There are various ways to do crossover of permutations. */
/*  They tend to be fiddly - it's easy to get your i's and  */
/*  j's mixed up.  This code implements 'position-based'    */
/*  crossover.   First, select some random gene positions   */
/*  from parent1.                                           */
/*                                                          */
/*  e.g. parent1 might be  "3 7 1 2 4 6 5", and the rand    */
/*  positions might be the 2nd, 3rd and 5th.                */
/*                                                          */
/*  Then, start building the child by making it the same    */
/*  as parent1 in those positions.  So, the child starts    */
/*  out in this case as:  "x 7 1 x 4 x x", where "x" means  */
/*  we haven't decided what goes there yet.                 */
/*                                                          */
/*  Now, suppose parent2 is "3 4 5 1 2 6 7" -- we complete  */
/*  the child by filling in the remaining cities            */
/*  (in this case 2, 3, 5 and 6) in the same order that they*/
/*  are in parent2.  So the child becomes: "3 7 1 5 4 2 6"  */
/***********************************************************/

int crossover(int parent1, int parent2, int *child)
{
  int genes_present[MAX_CITIES], chosen[MAX_CITIES], i, thisgene, place;


  // first randomly choose about half the positions in parent1

  for(i=0; i<number_of_cities; i++)
    if ((rand()%1000) <500) chosen[i] = 1; else chosen[i] = 0;

  // set child to be same as parent1 in these positions

  for(i=0; i< number_of_cities; i++)
    if(chosen[i]==1) child[i] = current_population[parent1][i];

  // now record the genes that the child already has
     // (first need to initialise this array)
  for(i=0; i < number_of_cities; i++) genes_present[i] = 0;
  for(i=0; i < number_of_cities; i++) 
    if(chosen[i]==1) genes_present[child[i]] = 1;

  // now collect the remaining genes from parent2

  for(i=0; i < number_of_cities; i++) 
    { thisgene = current_population[parent2][i];
      if(genes_present[thisgene]==0)
	{ //place it in the next unchosen position of the child
          place = 0;
          while(chosen[place]==1) place++;
          child[place] = thisgene;
          genes_present[thisgene] = 1;
          chosen[place]=1;
	}
    }
}


/**************************************************************/
/*  There are several possible mutation methods that make     */
/*  sure you still get a permutation.    This is one of the   */
/*  the simplest.  Take any two adjacent genes, and swap them */
/**************************************************************/

int mutate(int *child)
{
  int g, temp;

  // choose a random gene

  g = rand()%number_of_cities;

  // we will now swap g with the one to its right

  temp = child[g];
  child[g] = child[(g+1)%number_of_cities];
  child[(g+1)%number_of_cities] = temp;
}
