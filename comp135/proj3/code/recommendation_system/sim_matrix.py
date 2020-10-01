import numpy as np

TRAIN = "../../data/trainset.csv"
GENDER = "../../data/gender.csv"

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

def calc_score(user1, user2):
    score = 0
    for i in range(0, len(user1)):
        if (user1[i] != 0 and user2[i] != 0):
            score += (5 - abs(user1[i] - user2[i]))
    return score

def sim_matrix(X, Y):
    sim = np.zeros((ROW, ROW))
    for i in range(0, ROW):
        for j in range(i + 1, ROW):
            score = calc_score(X[i], X[j])
            if (Y[i] != Y[j]):
                score /= 2
            sim[i][j] = score
            sim[j][i] = score
        return sim

if __name__ == "__main__":
    train = read_csv(TRAIN)
    gender = read_csv(GENDER)

    X = make_matrix(train)
    Y = np.asarray(gender).T[0]

    np.save("sim_matrix", sim_matrix(X, Y))
