from random import randint
import os
import subprocess
from subprocess import Popen, PIPE

for iters in range(100):
    p = Popen('./main2', stdin=PIPE, stdout=PIPE)
    s = f"{randint(1,10**15)} {randint(1,10000)}"
    out, err = p.communicate(str.encode(s))

    p = Popen('./main3', stdin=PIPE, stdout=PIPE)
    out2, err = p.communicate(str.encode(s))
    if (str(out2) not in str(out)):
        print(s)
        print(out, out2)
        break
