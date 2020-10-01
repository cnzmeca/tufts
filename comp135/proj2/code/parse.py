import sys
import string
import re

def parse_string(sentence):
    sentence = string.lower(sentence)
    pattern = re.compile('[^a-zA-Z\' ]')
    sentence = re.sub(pattern, '', sentence)
    return filter(None, sentence)

def read_data(filename):
    labels = []
    sentences = []
    with open(filename) as file:
        for line in file.readlines():
            instance = line.strip('\r\n').split('\t')
            labels.append(instance[1])
            sentences.append(parse_string(instance[0]))
    return (labels, sentences)

def print_to_file(filename, labels, sentences):
    with open(filename, "w+") as file:
        for i in range(0, len(labels)):
            file.write("{}\t".format(sentences[i]))
            file.write(labels[i])
        file.write("\n")

def main(argv):
    (labels, sentences) = read_data(argv[1])
    print_to_file("output.txt", labels, sentences)

if __name__ == '__main__':
    main(sys.argv)
