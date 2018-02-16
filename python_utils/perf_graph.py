import numpy as np
import matplotlib.pyplot as plt
from matplotlib import rc
import matplotlib.patches as mpatches

if __name__=="__main__":
    rc('text', usetex=True)
    rc('font', family='serif')
    rc('xtick', labelsize=15)
    rc('ytick', labelsize=15)

    x = range(1,9)
    data_new = [63,74,68,48,40,36,32,30]
    data_old = [287,288,272,289,255,250,244,258]

    plt.plot(x, data_new, color="blue") 
    plt.plot(x, data_old, color="green")
    plt.xlabel("Number of threads", fontsize=18)
    plt.ylabel("Execution time (s)", fontsize=18)
    plt.title("Comparison of execution times between Kelbe \net al.'s algorithm and ours. 40 stems in each scan.", fontsize=20)
    old_patch = mpatches.Patch(color='green', label="Kelbe et al. imitation")
    new_patch = mpatches.Patch(color='blue', label="Our proposed method")
    plt.legend(handles=[new_patch,old_patch])
    plt.show()
