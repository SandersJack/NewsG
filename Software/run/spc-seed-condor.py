"""
This script helps submitting mac files to condor. It attempts to find all
relevent environment variables and create the appropriate output directories.

Example usage:
```
python spc-condor.py simulation.mac --output /disk/moose/newsg/$USER -n 10
```
will submit `simulation.mac` to condor 10 times (note that `n` is not the number
of events) and put the output in `/disk/moose/newsg/$USER/simulation`. If the
directory already exists the script will raise an exception. Optionally, a tag
can be given e.g.
```
python spc-condor.py simulation.mac --output /disk/moose/newsg/$USER -n 10 --tag run1
```
in which case the output will be written to `/disk/moose/newsg/$USER/run1/`

Normal short forms of arguments are allowed e.g.
```
python spc-condor.py simulation.mac -o /disk/moose/newsg/$USER -n 10 -t run1
```
A file will be produced in your submisson directory, called
`.run_simulation_SOMELONGNUMBER.sh`. I think you should leave this while your
job is running but can safely be deleted once all jobs are complete.
"""
from __future__ import print_function

import argparse
import errno
import os
import subprocess

from distutils.spawn import find_executable


def get_lcg_path():
    """This attempts to work out which verson of LCG we are using so it can be
    setup on condor accordingly (not sure this is 100% needed)

    This code is certainly a little bit speculative and may not work in the
    future.
    """
    lcio = os.environ.get("LCIO")
    if lcio:
        return lcio

    def raise_error():
        raise ValueError("Can not work out what LCG version to source!")

    cmake_prefix_path = os.environ.get("CMAKE_PREFIX_PATH")
    if not cmake_prefix_path:
        raise_error()

    for i in cmake_prefix_path.split(os.pathsep):
        if "LCG" in i:
            return i

    raise_error()


SHELL_SCRIPT = """
#!/usr/bin/env bash

# LCG now includes Garfield++ and this can interfere without version
export TMP_GARFIELD=$GARFIELD_HOME
source {LCG_PATH}/setup.sh
export GARFIELD_HOME=$TMP_GARFIELD

# This is a bit tricky, but we try to replace a line containing
# /random/setSeeds with some random seeds.
#
# If there is no line with /random/setSeeds then we add one as the first
# line in the file

RANDOM1=1255490941#$RANDOM
RANDOM2=342544344#$RANDOM

#sed "s=/random/setSeeds.*=/random/setSeeds $RANDOM1 $RANDOM2=" $1 > my_simulation.mac
if [ ! $(grep -q "/random/resetEngineFrom" $1) ];
then
	sed "s=/random/setSeeds.*=/random/setSeeds $RANDOM1 $RANDOM2=" $1 > my_simulation.mac
	if [ ! $(grep -q "/random/setSeeds" $1) ];
	then
   	 sed -i "1s=^=/random/setSeeds $RANDOM1 $RANDOM2\\n=" my_simulation.mac
	fi
fi

#>&2 echo "RANDOM SEEDS = ${{RANDOM1}} ${{RANDOM2}}"

cat my_simulation.mac

./SPC_Simulation my_simulation.mac

# Finally, check it exists
test -f output.root
mkdir rndmseeds
mv *.rndm rndmseeds/.
""".format(LCG_PATH=get_lcg_path())

SUBMIT_FILE = """
universe = vanilla

Executable     = {shell_script_name}
input          = {mac_file}

#output       = {out_dir}/logs/out_$(Process).test
log            = {out_dir}/logs/condor.log
error          = {out_dir}/logs/error_$(Process).test

request_memory = 4GB
#stream_output=TRUE

# Copy the executable when submitting so that we can (in theory) recompile
# without breaking stuff
transfer_input_files = {spc_simulation_path}
transfer_output_files = output.root , rndmseeds
transfer_output_remaps = "output.root = {out_dir}/output/output_$(Process).root; rndmseeds = {out_dir}/rndmseeds_$(Process)"

arguments = $(input)

getenv = True

queue {njobs}
"""


def create_submit_script(mac_file, output_dir, njobs, tag=""):
    if not os.path.exists(mac_file):
        raise RuntimeError("%s can not be found!" % mac_file)

    mac_dir, _, _ = os.path.basename(mac_file).rpartition(".")

    out_dir = os.path.join(output_dir, mac_dir, tag)

    for i in ("logs", "output"):
        try:
            os.makedirs(os.path.join(out_dir, i))
        except OSError as e:
            if e.errno == errno.EEXIST:
                raise type(e)(
                    "{} already exists, please delete before "
                    "submitting or give a unique tag!".format(out_dir)
                )
            raise

    shell_script_name = ".run_simulation_{}.sh".format(hash(out_dir))

    return (
        SUBMIT_FILE.format(
            shell_script_name=shell_script_name,
            mac_file=os.path.abspath(mac_file),
            out_dir=os.path.abspath(out_dir),
            spc_simulation_path=find_executable("SPC_Simulation"),
            njobs=njobs,
        ),
        shell_script_name,
    )


def submit():
    parser = argparse.ArgumentParser(
        description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter
    )

    parser.add_argument("mac_file")
    parser.add_argument("--output", "-o", required=True)
    parser.add_argument("-n", type=int, required=True)
    parser.add_argument("--tag", "-t", default="")
    args = parser.parse_args()

    sub_file, script_name = create_submit_script(
        mac_file=args.mac_file, output_dir=args.output, njobs=args.n, tag=args.tag
    )

    with open("submit", "w") as f:
        print(sub_file, file=f)
    with open(script_name, "w") as f:
        print(SHELL_SCRIPT, file=f)

    # Now actually submit the jobs
    subprocess.call(["condor_submit", "submit"])


if __name__ == "__main__":
    submit()
