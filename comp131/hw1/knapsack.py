import random
import numpy as np

# Finds fitness given weights and importances
def calc_fitness(individual):
	weights = [20, 30, 60, 90, 50, 70, 30]
	importances = [6, 5, 8, 7, 6, 9, 4]
	total_weight = 0
	total_importance = 0
	for gene in range(len(individual)):
		if individual[gene]:
			total_weight += weights[gene]
			total_importance += importances[gene]

	if total_weight <= 120:
		return total_importance

	else:
		return total_importance - (total_weight - 120) / 5

# Initializes a random population
def initialize_pop(pop_size):
	population = []
	for i in range(pop_size):
		individual = []
		for j in range(7):
			individual.append(bool(random.randint(0, 1)))	
		population.append(individual)
	return population

# Takes an individual and returns a mutated version
def mutate(individual):
	gene = random.randint(0, 6)
	new_individual = individual[:]
	new_individual[gene] = not individual[gene]
	return new_individual

# Takes an individual and returns a crossed over version
def crossover(individual):
	gene1 = random.randint(0, 6)
	gene2 = random.randint(0, 6)
	new_individual = individual[:]
	new_individual[gene1] = individual[gene2]
	new_individual[gene2] = individual[gene1]
	return new_individual

# Params
pop_size = 100
num_gens = 100
mut_rate = .05
cross_rate = .05

# Genetic algorithm on population
population = initialize_pop(pop_size)
for gen in range(num_gens):
	fitnesses = []
	for individual in population:
		fitnesses.append(calc_fitness(individual))
	fitnesses = np.array(fitnesses)
	survivors = [population[i] for i in fitnesses.argsort()[-(pop_size/2):][::-1]]
	new_population = []
	for i in range(pop_size/2):
		num = random.uniform(0, 1)
		if (num <= mut_rate):
			new_population.append(survivors[i])
			new_population.append(mutate(survivors[i]))
		elif (num <= mut_rate + cross_rate):
			new_population.append(survivors[i])
			new_population.append(crossover(survivors[i]))
		else:
			new_population.append(survivors[i])
			new_population.append(survivors[i])
	population = new_population

# Population is sorte by fitness, so first individual is most fit.
print("Optimal solution: ")
print(population[0])

