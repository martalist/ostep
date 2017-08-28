#!/usr/bin/env python 

import subprocess

if __name__ == "__main__":
    print("Pages\tTrials\tMicroSeconds")
    for i in range(1, 100, 2):
        subprocess.call(["./tlb.out", "{}".format(i), "10000"])
