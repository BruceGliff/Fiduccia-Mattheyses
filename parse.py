#!/bin/python3

class Experiment:
    file = ''
    edges = 0
    verts = 0
    cost = 0
    time = 0
    iters = 0
    def __init__(self, file, edges, verts, cost, time, iters):
        self.file = file
        self.edges = int(edges)
        self.verts = int(verts)
        self.cost = int(cost)
        self.time = int(time)
        self.iters = int(iters)
    def print(self):
        print('File-%s\n\bEdges-%d, Vertices-%d\n\bCost-%d, Time-%dms, Iters-%d\n' % (self.file, self.edges, self.verts, self.cost, self.time, self.iters))

def parseString(string):
    split = string.split(' ')
    return Experiment(split[0], split[1], split[2], split[3], split[4], split[5])

mf = open("ResultsMod.out", 'r')
of = open("ResultsOrg.out", 'r')

def parseFile(f):
  exprs = []
  for line in f:
    exprs.append(parseString(line))
  return exprs

exprs_m = parseFile(mf)
exprs_o = parseFile(of)

for x in exprs_m:
  x.print()
