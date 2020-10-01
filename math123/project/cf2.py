import random
import pandas as pd

from surprise.prediction_algorithms.knns import KNNBasic as KNN
from surprise import Dataset
from surprise import accuracy
from surprise.model_selection import GridSearchCV
from surprise import SVD

data = Dataset.load_builtin('jester')

raw_ratings = data.raw_ratings

random.shuffle(raw_ratings)

threshold = int(.9 * len(raw_ratings))

train_raw_ratings = raw_ratings[:threshold]
test_raw_ratings = raw_ratings[threshold:]

data.raw_ratings = train_raw_ratings

print('Grid Search...')
param_grid = {'reg_all': [0.001, 0.005, 0.01, 0.05, 0.1, 0.5, 1, 5], 'lr_all': [0.00005, 0.0001, 0.0005, 0.001, 0.005, 0.01]}
grid_search = GridSearchCV(SVD, param_grid, measures=['rmse'], cv=3)
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
