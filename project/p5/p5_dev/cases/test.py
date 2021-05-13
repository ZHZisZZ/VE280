import os
import subprocess
import shutil

gen = True

num_case = 100
os.makedirs("out", exist_ok=True)

for i in range(num_case):
    os.system(f"./build/dlist < case/0_{i} > out/0_{i}")
    p = subprocess.run(["diff", f"out/0_{i}", f"ans/0_{i}"])
    if p.returncode == 0 :
        print("pass: 0_" + str(i))
    else :
        print("fail: 0_" + str(i))
        assert (0)

for i in range(num_case):
    os.system(f"./build/rpn < case/1_{i} > out/1_{i}")
    p = subprocess.run(["diff", f"out/1_{i}", f"ans/1_{i}"])
    if p.returncode == 0 :
        print("pass: 1_" + str(i))
    else :
        print("fail: 1_" + str(i))
        assert (0)

for i in range(num_case):
    os.system(f"./build/cache < case/2_{i} > out/2_{i}")
    p = subprocess.run(["diff", f"out/2_{i}", f"ans/2_{i}"])
    if p.returncode == 0 :
        print("pass: 2_" + str(i))
    else :
        print("fail: 2_" + str(i))
        assert (0)
