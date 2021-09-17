from __future__ import print_function
import ROOT
import sys

try:
    fname = sys.argv[1]
except IndexError:
    raise IndexError("Must supply file name as argument")


variables = ("Amplitude", "PulseIntegral", "Risetime")
max_ = max(map(len, variables))

title_format = "\t".join("{:<%s}" % max_ for _ in variables)
float_format = "\t".join("{:<%s.4f}" % max_ for _ in variables)

f = ROOT.TFile.Open(fname)
buff = '-' * min(10, max_)
print(title_format.format(*variables))
print(title_format.format(*['-' * max_] * len(variables)))
for event in f.simul:
    try:
        print(float_format.format(*(getattr(event, i)[0] for i in variables)))
    except IndexError:
        print("-- No Garfield interations --")
