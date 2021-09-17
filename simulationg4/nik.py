import shutil
import os

from srim import Ion, Layer, Target, TRIM, SR


print("Hello world again")

# Construct a 5.3MeV He ion
#ion = Ion('He', energy=20e6)
ion = Ion('C', energy=20e6)
# ion = Ion('C', energy=20e6)

# Construct a layer of nick 20um thick with a displacement energy of 30 eV
# Ar:CH4 (98%:2%) 1.1bar
# E_d, lattive and surface in eV taken from SRIM windows
# density [g/cm^3]
# width [Ang]


# Ar 98% CH4 2%
# layer = Layer({
#     'Ar': {'stoich': 49.0, 'E_d': 5.0, 'lattice': 1.0, 'surface': 2.0},
#     'H': {'stoich': 4.0, 'E_d': 10.0, 'lattice': 3.0, 'surface': 2.0}, 
#     'C': {'stoich': 1.0, 'E_d': 28.0, 'lattice': 3.0, 'surface': 7.4}}, density=1.760e-3*1/1.1, width=600000000.0, phase=1)

# N2
layer = Layer({
    'N': {'stoich': 1.0, 'E_d': 28.0, 'lattice': 3.0, 'surface': 2.0}}, density=5.744e-4, width=600000000.0, phase=1)

# CH4 
# layer = Layer({
#     'C': {'stoich': 1.0, 'E_d': 28.0, 'lattice': 3.0, 'surface': 7.4},
#     'H': {'stoich': 4.0, 'E_d': 10.0, 'lattice': 3.0, 'surface': 2.0}}, density=6.565E-4, width=600000000.0, phase=1)


print("Hello world!")

# Construct a target of a single layer of Nickel
# target = Target([layer])
# Specify the directory of SRIM.exe
# For windows users the path will include C://...
srim_executable_directory = '/tmp/srim'

srim = SR(layer, ion, output_type=5)
results0=srim.run()
print(results0.ion)
print(results0.target)
print(results0.data)
# # Initialize a TRIM calculation with given target and ion for 25 ions, quick calculation
# trim = TRIM(target, ion, number_ions=10, calculation=1)


# print("Hello world!")
# # takes about 10 seconds on my laptop
# results = trim.run(srim_executable_directory)
# # If all went successfull you should have seen a TRIM window popup and run 25 ions!
# # results is `srim.output.Results` and contains all output files parsed
# print("Hello world?")

os.makedirs('/tmp/output', exist_ok=True)
# srim.copy_output_files('/tmp/srim', '/tmp/output')
os.system('pwd')
if (os.path.isfile(os.path.join('/tmp/srim', 'SR Module', 'SR_OUTPUT.txt'))):
    shutil.move(os.path.join('/tmp/srim', 'SR Module', 'SR_OUTPUT.txt'), '/tmp/output')
else:
    print('did not find file')

