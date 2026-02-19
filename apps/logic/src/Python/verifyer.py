import sys
import os

def verify(filePath) :
    path = os.path.normpath(os.path.join(os.path.dirname(os.path.abspath(__file__)), filePath))

    f = open(path)
    string = f.readline()
    f.close()
    
    #print(string)
    z = string.count("0")
    o = string.count("1")
    v = z != o
    #v = string.count("0") != string.count("1")
    print(v)
    if v == False : print(string)
verify(sys.argv[1])