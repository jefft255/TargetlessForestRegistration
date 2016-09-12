# -*- coding: utf-8 -*-
"""
Created on Fri Aug  5 12:38:01 2016

@author: Jean-Francois Tremblay

Create a proper stem map file from the 2 file outputted by Computree
Format:
ID X Y Z DBH
"""

def createTLRStemMap(pathDBH, pathStemMap):
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
            result[i-1].append(contenuLigneDBH[2])
            result[i-1].append(contenuLigneDBH[3])
            result[i-1].append(contenuLigneDBH[4])
            result[i-1].append(contenuLigneDBH[5])
        i = i + 1

    
    for row in result:
        if row:
            resultFile.write(str(row[0]) + ' ')
            resultFile.write(str(row[1]) + ' ')
            resultFile.write(str(row[2]) + ' ')
            resultFile.write(str(row[3]) + '\n')
                