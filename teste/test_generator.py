
#%%
import os
os.chdir("E:/II/S2/SD/proiect/binomialHeapFinal")

import random 

randomSmallData = random.sample(range(-1000, 1000), 100)

f = open("randomSmallData.txt", "w")

for i in randomSmallData:
    f.write(str(i))
    f.write('\n')
   
f.close()

#%%
randomMediumData = random.sample(range(-1000000000, 1000000000), 10000)

f = open("randomMediumData.txt", "w")

for i in randomMediumData:
    f.write(str(i))
    f.write('\n') 

f.close()

#%%
randomLargeData = random.sample(range(-2147483648, 2147483648), 2000000)

f = open("randomLargeData.txt", "w")

for i in randomLargeData:
    f.write(str(i))
    f.write('\n') 

f.close()

#%%
tree4096 = random.sample(range(-1000000, 1000000), 4096)

f = open("tree4096.txt", "w")

for i in tree4096:
    f.write(str(i))
    f.write('\n') 

f.close()

#%%
sortedNumbers = range(1, 2000001)

f = open("sortedNumbers.txt", "w")

for i in sortedNumbers:
    f.write(str(i))
    f.write('\n') 

f.close()

#%%
reverseSorted = range(2000000, 0, -1)

f = open("reverseSorted.txt", "w")

for i in reverseSorted:
    f.write(str(i))
    f.write('\n') 

f.close()


