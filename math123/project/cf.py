import random
import pandas as pd

from surprise.prediction_algorithms.knns import KNNBasic as KNN
from surprise import Dataset
from surprise import accuracy
from surprise.model_selection import GridSearchCV

data = Dataset.load_builtin('jester')

raw_ratings = data.raw_ratings

random.shuffle(raw_ratings)

threshold = int(.9 * len(raw_ratings))

train_raw_ratings = raw_ratings[:threshold]
test_raw_ratings = raw_ratings[threshold:]

data.raw_ratings = train_raw_ratings

print('Grid Search...')
#param_grid = {'k': [1, 10, 100, 1000, 10000, 100000, 1000000], "sim_options['name']": ['MSD', 'cosine', 'pearson'], "sim_options['user_based']": [True, False]}
param_grid = {'k': [100], "sim_options['name']": ['MSD'], "sim_options['user_based']":  [True]}
grid_search = GridSearchCV(KNN, param_grid, measures=['rmse'], cv=3)
grid_search.fit(data)

df = pd.DataFrame(grid_search.cv_results)
df.to_csv(path_or_buf = 'results.csv')
algo = grid_search.best_estimator['rmse']

trainset = data.build_full_trainset()
algo.fit(trainset)

predictions = algo.test(trainset.build_testset())
print('Biased accuracy on train:')
accuracy.rmse(predictions)
accuracy.mae(predictions)

testset = data.construct_testset(test_raw_ratings)  # testset is now the set B
predictions = algo.test(testset)
print('Unbiased accuracy on test:')
accuracy.rmse(predictions)
accuracy.mae(predictions)
