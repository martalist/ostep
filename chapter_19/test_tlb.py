#!/usr/bin/env python 

import subprocess

if __name__ == "__main__":
    print("Pages\tTrials\tMicroSeconds")
    for i in range(1, 2050, 2):
        subprocess.call(["./tlb.out", str(i), "10000"])
