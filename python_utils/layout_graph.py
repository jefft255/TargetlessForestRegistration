import numpy as np
import matplotlib.pyplot as plt
from matplotlib import rc

if __name__=="__main__":
    rc('text', usetex=True)
    rc('font', family='serif')
    rc('xtick', labelsize=15)
    rc('ytick', labelsize=15)

    scans_valcartier1 = np.array([[0,0],
                                  [-10.133,-6.0960],
                                  [-5.183, 5.953],
                                  [6.06, 4.39],
                                  [1.51, -10.88]])
    connections_valcartier1 = [[0,2], [0,3], [0,1], [4,0]]

    scans_valcartier2 = np.array([[0,0],
                                  [-0.945, 11.42],
                                  [13.41, 1.46],
                                  [-0.327,-12.58],
                                  [-11.92,-0.84]])
    connections_valcartier2 = [[0,2], [0,3], [0,1], [4,0]]

    scans_sequoia = np.array([[0,0],
                              [-7.51, -5.11],
                              [-12.29, -11.89],
                              [-22.68,-18.76],
                              [-32.50,-14.92],
                              [-24.28, -8.02],
                              [-18.46, -4.39],
                              [-12.24, 1.67]])
    connections_sequoia = [[0,7],[0,1],[6,1],[6,5],[5,2],[2,3],[3,4]]
    sites = [("Valcartier 1", scans_valcartier1, connections_valcartier1),
             ("Valcartier 2", scans_valcartier2, connections_valcartier2),
             ("Sequoia", scans_sequoia, connections_sequoia)]
    for site in sites:
        title = site[0]
        scans = site[1]
        connections = site[2]
        if title == "Sequoia":
            xytext=(5,15)
        else:
            xytext=(-20,0)
        for connection in connections:
            plt.plot([scans[connection[0],0], scans[connection[1],0]],
                     [scans[connection[0],1], scans[connection[1],1]],
                     color="blue")
        for i, xy in enumerate(scans):
            plt.annotate("Scan {}".format(i+1),
                         xy=xy, xytext=xytext,
                         textcoords='offset points', ha='right', va='bottom',
                         fontsize=16,
                         arrowprops=dict(arrowstyle = '->', connectionstyle='arc3,rad=0'))
        plt.scatter(scans[:,0], scans[:,1], s=90)
        plt.xlabel("$x$ position of scan", fontsize=22)
        plt.ylabel("$y$ position of scan", fontsize=22)
        plt.show()
