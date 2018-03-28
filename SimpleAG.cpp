/*
	Simple AG
	Author: Bruno Vieira - github.com/brunovieira97
	Artificial Intelligence - Unisnios - 2018/1
*/

// Dependencies
#include <time.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

// Constants
static const int population_size = 10
static const int generations = 10

static const double PROB_MUT = 0.0;             // percentual (0..1)
static const double ag_range = 20.0;            // teste com 1?
static const double ag_range_offset = 10.0;     // teste com 0?

/*
	0, 1: 	function variables
	2: 		fitness storage
*/
float population[population_size][3];   

// Creates population
int CreatePopulation() {
	for (int i = 0; i < population_size; i++) {
		/*
			pop[i][0] = (float) rand();  
			pop[i][1] = (float) rand(); 
			pop[i][0] = (float) rand() / (float) RAND_MAX; 
			pop[i][1] = (float) rand() / (float) RAND_MAX; 
	 	*/

		pop[i][0] = (((float) rand() / (float) RAND_MAX) * ag_range) - ag_range_offset;
3		pop[i][1] = (((float) rand() / (float) RAND_MAX) * ag_range) - ag_range_offset;
	}
	return 0;
}

// Prints population on screen
int ShowPopulation() {
	for (int i = 0; i < population_size; i++) {
		printf("%d %.3f %.3f\n",i, pop[i][0],pop[i][1]);
	}
	return 0;
}

// Prints population and fitness on screen
int ShowPopulationWithFitness() {
	for (int i = 0; i < population_size; i++) {
		printf("%d %.3f %.3f fit: %.3f\n",i, pop[i][0],pop[i][1],pop[i][2]);
	}
	return 0;
}

// Calculates fitness
int CalculateFitness() {
	for (int i = 0; i < population_size; i++) {
		pop[i][2] = (pop[i][0] * pop[i][0]) + (pop[i][1] * pop[i][1]); 
	}
	return 0;
}

int GetMinor() {
	float menor = (float) RAND_MAX;
	int minor_index = 0;

	for (int i = 0; i < population_size; i++) {
		if (menor > pop[i][2]) {
			menor = pop[i][2];
			minor_index = i;
		}
	}
	return minor_index;
}

int Crossover(int minor_index) {
	for (int i = 0; i < population_size; i++) {
		pop[i][0] = (pop[i][0] + pop[minor_index][0]) / 2.0;
		pop[i][1] = (pop[i][1] + pop[minor_index][1]) / 2.0;
	}
	return 0;
}

int UniformMutationWithoutElitism() {
	for (int i = 0; i < population_size; i++) {
		for (int j = 0; j < 2; j++) {
			float r = rand() / (float) RAND_MAX;
			if (r < PROB_MUT) {
				pop[i][j] = (((float) rand() / (float) RAND_MAX) * ag_range) - ag_range_offset;
			}
		}
	}
	return 0;
}

int UniformMutationWithElitism(int minor_index) {
	for (int i = 0; i < population_size; i++) {
		if (i != minor_index) {
			for (int j = 0; j < 2; j++) {
				float r = rand() / (float) RAND_MAX;
				if (r < PROB_MUT) {
					pop[i][j] = (((float) rand() / (float) RAND_MAX) * ag_range) - ag_range_offset;
				}
			}
		}
	}
	return 0;
}

int GaussMutationWithoutElitism() {
	for (int i = 0; i < population_size; i++) {
		for (int j = 0; j < 2;j++) {
			float r = rand() / (float) RAND_MAX;
			if (r < PROB_MUT) {
				float q;
				q = rand() / (float) RAND_MAX;     // valor entre 0 e 1
				q = (q * 2.0) - 1.0;               // valor entre -1 e 1
				q = q / 4.0;                       // valor entre + 0.25 e -0.25
				q = 1.0 + q;                       // valor entre 0.75 e 1.25  

				pop[i][j] = pop[i][j] * q;
			}
		}
	}
	return 0;
}

int GaussMutationWithElitism(int minor_index) {
	for (int i = 0; i < population_size; i++) {
		if (i != minor_index) {
			for (int j = 0; j < 2; j++) {
				float r = rand() / (float) RAND_MAX;
				if (r < PROB_MUT) {
					float q;
					q = rand() / (float) RAND_MAX;     // valor entre 0 e 1
					q = (q * 2.0) - 1.0;               // valor entre -1 e 1
					q = q / 4.0;                       // valor entre + 0.25 e -0.25
					q = 1.0 + q;                       // valor entre 0.75 e 1.25  

					pop[i][j] = pop[i][j] * q;
				}
			}
		}
	}
	return 0;
}

int main() {
	srand(time(NULL));       

	CreatePopulation();

	printf("Created population:\n");
	ShowPopulation();
	getchar();

	CalculateFitness();

	printf("Created population with fitness:\n");
	ShowPopulationWithFitness();
	getchar();

	int g = 1;  // discutir

	while (g < generations) {
		// Selection
		int minor_index = GetMinor(); 
			
		// Crossover
		Crossover(minor_index);

		// Mutation
		//UniformMutationWithElitism(minor_index);
		//UniformMutationWithoutElitism();
		GaussMutationWithElitism(minor_index);
		//GaussMutationWithoutElitism();

		// Fitness
		CalculateFitness();

		printf("Generation: %d \n\n",g);
		ShowPopulationWithFitness();
		
		// View only
		minor_index = GetMinor(); 
		printf("\nBest: %d %.3f\n",minor_index, pop[minor_index][2]);
		
		getchar();

		g++;
	}
	printf("That's all, Folks!");
	getchar();
}