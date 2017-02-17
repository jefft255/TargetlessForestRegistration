# Module pcFuncs, JF Tremblay le 29 juin 2016
# Ensemble de fonctions python pratiques pour le traitement de
# nuages de points.

import re
import numpy as np
import scipy.spatial
from math import sin, cos
import matplotlib.pyplot as plt

def updateStemMapWithMNT(pathMNT, pathOriginalStemMap, pathNewStemMap):
    MNT = loadAscFile(pathMNT, ';')
    MNT3dtree = scipy.spatial.KDTree(MNT[:,[0,1]])
    orginalFile = open(pathOriginalStemMap, 'r')
    transFile = open(pathNewStemMap, 'w')
    originalData = orginalFile.readlines()

    for rowOriginal in originalData:
        stemOriginal = rowOriginal.split(' ')
        coordsStem = np.array([float(stemOriginal[0]),
                                       float(stemOriginal[1]),
                                       float(stemOriginal[2])])
        distMNT, idMNT = MNT3dtree.query(coordsStem[[0,1]], 3)
        print("====================")
        print(MNT[idMNT[0],:])
        print(MNT[idMNT[1],:])
        print(coordsStem)
        newZ = min(MNT[idMNT[0],2], MNT[idMNT[1],2])
        print(newZ)
        transFile.write(str(coordsStem[0]) + ' ')
        transFile.write(str(coordsStem[1]) + ' ')
        transFile.write(str(newZ) + ' ')
        transFile.write(str(stemOriginal[3]))




# Load .ASC point cloud
def loadAscFile(inputFileString, sep=' '):
    inputFile = open(inputFileString, 'r')
    headerLinesSkipped = False
    lineCounter = 0
    inputMatrix = [[]]

    print("Reading the input file...\n")
    for line in inputFile:
        if re.search('[a-zA-Z]+', line):
            if headerLinesSkipped:
                # Si on encontre des lettres apres le header on cancel
                # car fichier invalide
                break
        elif line: # Si la ligne pas vide
            if not headerLinesSkipped:
                # La premiere ligne numerique marque la fin du header
                headerLinesSkipped = True
            contenuLigne = line.split(sep)
            x,y,z = contenuLigne[0], contenuLigne[1], contenuLigne[2]
            if x and y and z:
                # Si les 3 coordonnee sont rempli
                # sinon la ligne est invalide
                if lineCounter:
                    # pas ajouter de ligne la premiere fois sinon
                    # on fini avec une de trop
                    inputMatrix.append([])
                inputMatrix[lineCounter].append(float(x))
                inputMatrix[lineCounter].append(float(y))
                inputMatrix[lineCounter].append(float(z))
                lineCounter += 1

    return np.array(inputMatrix)

# Apply a 4x4 transformation matrix to a point cloud
def applyTransMatrixToPC(pointCloud, transMatrix):
    pointCloud = np.apply_along_axis(applyTransMatrixToVector, 1, pointCloud, transMatrix)
    return pointCloud

# Apply a 4x4 transformation matrix to a vector
def applyTransMatrixToVector(vector, transMatrix):
    vectorCopy = np.resize(vector, (1,4))
    vectorCopy[0,3] = 1
    vectorCopy = np.dot(transMatrix, np.transpose(vectorCopy))
    vectorCopy = np.transpose(vectorCopy)
    vector = np.resize(vectorCopy, (1,3))
    return vector[0]

# save in ASCII (x y z) a point cloud
def writeAscFile(outputFileString, pointCloud):
    outputFile = open(outputFileString, 'w')
    pointCloud = np.array(pointCloud)

    for i in range(0, pointCloud.shape[0]-1):
        outputFile.write(str(pointCloud[i,0]) + ' ' +
        str(pointCloud[i,1]) + ' ' + str(pointCloud[i,2]) + '\n')

# Return all point within a 3D range
def selectRange(pointCloud, xmin, xmax, ymin, ymax, zmin, zmax):
    lineCounter = 0
    pointCube = [[]]

    for i in range(0, pointCloud.shape[0]-1):
        if pointCloud[i,0] > xmin and pointCloud[i,0] < xmax and \
           pointCloud[i,1] > ymin and pointCloud[i,1] < ymax and \
           pointCloud[i,2] > zmin and pointCloud[i,2] < zmax:
            if lineCounter:
                pointCube.append([])
            pointCube[lineCounter].append(pointCloud[i,0])
            pointCube[lineCounter].append(pointCloud[i,1])
            pointCube[lineCounter].append(pointCloud[i,2])
            lineCounter += 1

    return np.array(pointCube)

def fusePointCloud(pointCloud1, pointCloud2):
    return np.concatenate((pointCloud1, pointCloud2))

def getRotationMatrix(phi, theta, psi):
    # Convert degrees to radians
    phi = 0.0174533*phi
    theta = 0.0174533*theta
    psi = 0.0174533*psi
    
    Rx = np.matrix([[1,0,0],
                   [0,cos(phi),-sin(phi)],
                   [0,sin(phi),cos(phi)]], np.float64)
    Ry = np.matrix([[cos(theta),0,sin(theta)],
                   [0,1,0],
                   [-sin(theta),0,cos(theta)]], np.float64)
    Rz = np.matrix([[cos(psi),-sin(psi),0],
                   [sin(psi),cos(psi),0],
                   [0,0,1]], np.float64)
    return Rz*Ry*Rx

# Generate a 4x4 transform matrix from euler angles and translation params
def getTransformationMatrix(phi, theta, psi, tx, ty, tz):
    rot = getRotationMatrix(phi, theta, psi)

    result = np.array([[rot[0,0],rot[0,1],rot[0,2],tx],
                      [rot[1,0],rot[1,1],rot[1,2],ty],
                      [rot[2,0],rot[2,1],rot[2,2],tz],
                      [0,0,0,1]], np.float64)
    return result

# Reformat a stem map outputted by computree the following way :
# x y z dbh
# each line reprensenting a single stem.
def reformatStemMap(pathDBH, pathStemMap):
    DBHcsv = open(pathDBH, 'r')
    DBHdata = DBHcsv.readlines()

    resultFile = open(pathStemMap, 'w')

    result = [[]]
    i = 0

    for rowDBH in DBHdata:
        contenuLigneDBH = rowDBH.split(';')
        # Skip the header
        if i > 1:
            result.append([])
            result[i-1].append(contenuLigneDBH[0])
            result[i-1].append(contenuLigneDBH[1])
            result[i-1].append(contenuLigneDBH[2])
            result[i-1].append(contenuLigneDBH[3])
        i = i + 1

    for row in result:
        if row:
            resultFile.write(str(row[0]) + ' ')
            resultFile.write(str(row[1]) + ' ')
            resultFile.write(str(row[2]) + ' ')
            resultFile.write(str(row[3]))

# Apply a transformation matrix to a stem map file (x y z dbh)
def transformStemMap(pathOriginalStemMap, pathTransStemMap, transMatrix):
    orginalFile = open(pathOriginalStemMap, 'r')
    transFile = open(pathTransStemMap, 'w')
    originalData = orginalFile.readlines()

    for rowOriginal in originalData:
        stemOriginal = rowOriginal.split(' ')
        coordsStemOriginal = np.array([float(stemOriginal[0]),
                                       float(stemOriginal[1]),
                                       float(stemOriginal[2])])
        coordsStemTrans = applyTransMatrixToVector(coordsStemOriginal,
                                                   transMatrix)
        transFile.write(str(coordsStemTrans[0]) + ' ')
        transFile.write(str(coordsStemTrans[1]) + ' ')
        transFile.write(str(coordsStemTrans[2]) + ' ')
        transFile.write(str(stemOriginal[3]))

def plotStemMap(pathsStemMap, colors):
    fig, ax = plt.subplots() # note we must use plt.subplots, not plt.subplot
    circles = []
    i = 0

    for pathStemMap in pathsStemMap:
        file = open(pathStemMap, 'r')
        dataStemMap = file.readlines()
        for stemRow in dataStemMap:
            stem = stemRow.split(' ')
            circles.append(plt.Circle((float(stem[0]), float(stem[1])),
                                      float(stem[3]),
                                      color=colors[i]))
        i = i + 1

    fig, ax = plt.subplots() # note we must use plt.subplots, not plt.subplot

    for circle in circles:
        ax.add_artist(circle)

    ax.set_xlim((-30, 30))
    ax.set_ylim((-30, 30))
    plt.show()

def printMatrix(matrix):
    str = ""
    for row in matrix:
        i = 0
        for ele in row:
            str += '{:.5f}'.format(ele)
            if i != 3:
                str += ' '
            i += 1
        str += '\n'
    print(str)
