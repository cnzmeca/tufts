import numpy as np
from sklearn.metrics import mean_absolute_error as mae

TRAIN = "../../data/trainset.csv"
TEST = "../../data/testset.csv"
YEAR = "../../data/release-year.csv"
SIM = "sim_matrix.npy"

ROW = 943
COL = 1681

def read_csv(filename):
    data = []
    with open(filename, "r") as file:
        for line in file.readlines():
            try:
                data.append(map(int, line.strip().split(",")))
            except:
                pass
    return data

def make_matrix(l):
    matrix = np.full((ROW, COL), 0)
    for d in l:
        matrix[d[0]][d[1]] = d[2]
    return matrix

def year_prefs(X, Y):
    avg_years = np.zeros(ROW)
    for i in range(0, ROW):
        year_sum = 0
        weight_sum = 0
        for j in range(0, COL):
            year_sum += X[i][j] * Y[j]
            weight_sum += X[i][j]
        avg_years[i] = year_sum/float(weight_sum)
    return avg_years

def year_weights(avg_year, Y):
    year_weights = np.zeros(COL)
    for i in range(0, COL):
        year_weights[i] = (1 - abs(avg_year - Y[i])/float(76))
    return year_weights

def make_recs(X, sim, avg_years):
    recs = []
    ratings = []
    nb = 100
    for i in range(0, ROW):
        usim = sim[i]
        weights = year_weights(avg_years[i], Y)
        rated = np.nonzero(X[i])
    
        best = np.argpartition(usim, -nb)[-nb:]
        rating = np.zeros(COL)
        comb = np.zeros(COL)
        for j in range(0, COL):
            tot = 0
            div = 0
            num = 0
            for k in range(0, nb):
                temp = X[best[k]][j]
                if temp != 0:
                    scale = usim[best[k]] * weights[j]
                    tot += temp * scale
                    div += scale
                    num += 1
            try:
                rating[j] = tot/float(div)
            except:
                rating[j] = 2.5
    
            try:    
                comb[j] = (1 - 1/float(num)) * rating[j]
            except:
                pass

        for j in range(0, len(rated)):
            rating[rated[j]] = X[i][rated[j]]
            comb[rated[j]] = 0  
        rec = np.flip(np.argpartition(comb, -5)[-5:], 0)
        recs.append(rec)
        ratings.append(rating)

    return recs, ratings

def evaluate(ratings, test):
    preds = []
    true = []
    for t in test:
        preds.append(ratings[t[0]][t[1]])
        true.append(t[2])
    print("MAE: {}\n".format(mae(preds, true)))
    print("AVG: {}\n".format(np.mean(ratings)))

def to_file(recs):
    with open("recommendations.txt", "w+") as file:
        for i in range(0, ROW):
            file.write("{}".format(i))
            for j in range(0, 5):
                file.write("\t{}".format(recs[i][j]))
            file.write("\n")

if __name__ == "__main__":
    train = read_csv(TRAIN)
    test = read_csv(TEST)
    year = read_csv(YEAR)
    sim = np.load(SIM)

    X = make_matrix(train)
    Y = np.asarray(year).T[0]
    avg_years = year_prefs(X, Y)

    recs, ratings = make_recs(X, sim, avg_years)

    evaluate(ratings, test)
    to_file(recs)
