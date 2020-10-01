import sys
import numpy as np
from sklearn.neighbors import KNeighborsClassifier
from sklearn.naive_bayes import MultinomialNB
from sklearn.linear_model import LogisticRegression
from sklearn.model_selection import cross_val_score

def read_data(filename):
    Y = []
    X = []
    with open(filename) as file:
        for line in file.readlines():
            instance = line.strip('\r\n').split('\t')
            Y.append(instance[0])
            X.append(map (float, instance[1:]))
    return (Y, X)

def score(scores):
    mean = np.mean(scores)
    std = np.std(scores)
    print("Mean: {}\tStd: {}\n".format(1 - mean, std))

def cv_knn(Y, X, k):
    knn = KNeighborsClassifier(n_neighbors=k)
    knn.fit(X, Y)
    scores = cross_val_score(knn, X, Y, cv = 10)
    print("K Nearest Neighbors:")
    score(scores)

def cv_mnb(Y, X, a):
    mnb = MultinomialNB(alpha=a)
    mnb.fit(X, Y)
    scores = cross_val_score(mnb, X, Y, cv = 10)
    print("Multinomial Naive Bayes:")
    score(scores)

def cv_logreg(Y, X, c):
    logreg = LogisticRegression(C=c)
    logreg.fit(X, Y)
    scores = cross_val_score(logreg, X, Y, cv = 10)
    print("Logistic Regression:")
    score(scores)
    
def pred_knn(trainY, trainX, testY, testX, k):
    knn = KNeighborsClassifier(n_neighbors=k)
    knn.fit(trainX, trainY)
    predY = knn.predict(testX)
    with open("knn.txt", "w+") as file:
        for i in predY:
            file.write("{}\n".format(i))

def pred_mnb(trainY, trainX, testY, testX, a):
    mnb = MultinomialNB(alpha=a)
    mnb.fit(trainX, trainY)
    predY = mnb.predict(testX)
    with open("mnb.txt", "w+") as file:
        for i in predY:
            file.write("{}\n".format(i))

def pred_logreg(trainY, trainX, testY, testX, c):
    logreg = LogisticRegression(C=c)
    logreg.fit(trainX, trainY)
    predY = logreg.predict(testX)
    with open("logreg.txt", "w+") as file:
        for i in predY:
            file.write("{}\n".format(i))
    
def main(argv):
    (trainY, trainX) = read_data(argv[1])
    (testY, testX) = read_data(argv[2])
    k = int(argv[3])
    a = float(argv[4])
    c = float(argv[5])
    
    cv_knn(trainY, trainX, k)   
    pred_knn(trainY, trainX, testY, testX, k)

    cv_logreg(trainY, trainX, c)    
    pred_logreg(trainY, trainX, testY, testX, c)
    
    # IMPORTANT!!!
    # When running this file with word embedding inputs, the negative
    # weights will cause Multinomial Naive Bayes to trigger an error.
    # This is not a mistake in the code, and if the code is to run without
    # error for word embedded inputs, the following 2 lines must be omitted:
    cv_mnb(trainY, trainX, a)   
    pred_mnb(trainY, trainX, testY, testX, a)

if __name__ == '__main__':
        main(sys.argv)
