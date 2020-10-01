import sys
import os

def read_data(path):
    preds = []
    for filename in os.listdir(path):
        pred = []
        with open(os.path.join(path, filename)) as file:
            for line in file.readlines():
                pred.append(line.strip('\n'))
        preds.append(pred)
    return preds

def vote(preds):
    votes = []
    for i in range(0, len(preds[0])):
        vote = 0
        for j in range(0, len(preds)):
            vote += int(preds[j][i])
        votes.append(vote)

    with open("predicted-labels.txt", "w+") as file:
        for v in votes:
            if (v > 2):
                file.write("1\n")
            else:
                file.write("0\n")   
def main(argv):
    preds = read_data(argv[1])
    vote(preds)

if __name__ == '__main__':
        main(sys.argv)
