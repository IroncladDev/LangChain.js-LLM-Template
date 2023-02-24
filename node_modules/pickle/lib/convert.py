import sys
try:
    import simplejson as json
except ImportError:
    import json
try:
    import cPickle as pickle
except ImportError:
    import pickle

def main(argv):
    try:
        if argv[0] == '--loads':
            json.dump(pickle.load(sys.stdin), sys.stdout)
        elif argv[0] == '--dumps':
            pickle.dump(json.load(sys.stdin), sys.stdout)
    except:
        sys.stdout.write('-1')

if __name__ == '__main__':
    main(sys.argv[1:])