import os
import shutil

gen = True

num_case = 100
os.makedirs("case", exist_ok=True)
os.makedirs("ans", exist_ok=True)

for i in range(num_case):
    os.system(f"./build/g1 > case/0_{i}")
    os.system(f"./build/dlist < case/0_{i} > ans/0_{i}")

for i in range(num_case):
    os.system(f"./build/g2 > case/1_{i}")
    os.system(f"./build/rpn < case/1_{i} > ans/1_{i}")

for i in range(num_case):
    os.system(f"./build/g3 > case/2_{i}")
    os.system(f"./build/cache < case/2_{i} > ans/2_{i}")
