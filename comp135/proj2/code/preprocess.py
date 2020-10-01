import sys
import numpy as np
from sklearn.feature_extraction.text import CountVectorizer

def read_data(filename):
    sentences = []
    labels = []
    with open(filename) as file:
        for line in file.readlines():
            instance = line.strip('\r\n').split('\t')
            labels.append(instance[1])
            sentences.append(instance[0])
    return (labels, sentences)

def print_to_file(filename, labels, features):
    with open(filename, "w+") as file:
        for i in range(0, len(labels)):
            file.write(labels[i])
            for f in features[i]:
                file.write("\t{}".format(f))
            file.write("\n")

def word_bag(trainY, trainX, testY, testX):
    vtrain = CountVectorizer(min_df = .005, max_df =.1)
    xtrain = vtrain.fit_transform(trainX)
    words = vtrain.get_feature_names()
    print_to_file("train_wordbag.txt", trainY, xtrain.toarray())

    vtest = CountVectorizer(vocabulary = words)
    xtest = vtest.fit_transform(testX)
    print_to_file("test_wordbag.txt", testY, xtest.toarray())
    


def open_glove(filename):
    glove = {}
    with open(filename) as file:
        for line in file.readlines():
            embedding = line.strip('\r\n').split(' ')
            vector = embedding[1:]
            word = embedding[0]
            glove[word] = map(float, vector)
    return glove

def word_embed(trainY, trainX, testY, testX, glove):
    vtrain = []
    for s in trainX:
        v = np.zeros(50)
        words = s.split(' ')
        for w in words:
            try:
                v += glove[w]
            except KeyError:
                v += np.zeros(50)
        vtrain.append(v)
    print_to_file("train_wordembed.txt",  trainY, vtrain)

    vtest = []
    for s in testX:
        v = np.zeros(50)
        words = s.split(' ')
        for w in words:
            try:
                v += glove[w]
            except KeyError:
                v += np.zeros(50)
        vtest.append(v)
        print_to_file("test_wordembed.txt", testY, vtest)

def main(argv):
    (trainY, trainX) = read_data(argv[1])
    (testY, testX) = read_data(argv[2])
    word_bag(trainY, trainX, testY, testX)
    glove = open_glove(argv[3])
    word_embed(trainY, trainX, testY, testX, glove)

if __name__ == '__main__':
        main(sys.argv)
