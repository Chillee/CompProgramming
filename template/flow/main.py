from scipy import stats
import math
import time
import matplotlib.pyplot as plt
import subprocess

# no scaling: 3.149058889251307
# scaling: 1.9994004817225839
# someone else's scaling: 2.01
# pushrelabel: 2.023
vals = []
vals += [100*i for i in range(20, 30)]
results = []
iters = 10
for v in vals:
    total = 0
    for i in range(iters):
        subprocess.Popen(f"./gen {v} > input.txt", shell=True).wait()
        begin = time.time()
        subprocess.Popen(f"./pushrelabel < input.txt", shell=True).wait()
        total += time.time()-begin
    results.append(total/iters)
vals, results = [math.log(i) for i in vals], [math.log(i) for i in results]
print(vals, results)
plt.plot(vals, results)
slope, _, _, _, _ = stats.linregress(vals, results)
print(slope)
plt.show()
