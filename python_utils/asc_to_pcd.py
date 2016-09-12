# .ASC to .PCD by Jean-Francois Tremblay
# May 30, 2016
# Anything other than xyz data will be ignored.

import pcFuncs
import numpy

if __name__ == "__main__":
	inputPath = raw_input("Enter the path to the .ASC input file : \n")
	outputPath = raw_input("Enter the path to the .PCD output file : \n")
	inputFile = open(inputPath, 'r')
	print inputFile
	outputFile = open(outputPath, 'w')
	
	inputMatrix = pcFuncs.loadAscFile(inputFile)
	
	print "Writing the output file...\n"
	
	outputFile.write('# .PCD v0.7 - Point Cloud Data file format\n')
	outputFile.write('VERSION 0.7\n')
	outputFile.write('FIELDS x y z\n')
	outputFile.write('SIZE 4 4 4\n')
	outputFile.write('TYPE F F F\n')
	outputFile.write('COUNT 1 1 1\n')
	outputFile.write('WIDTH ' + str(len(inputMatrix)) + '\n')
	outputFile.write('HEIGHT 1\n')
	outputFile.write('VIEWPOINT 0 0 0 1 0 0 0\n')
	outputFile.write('POINTS ' + str(len(inputMatrix)) + '\n')
	outputFile.write('DATA ASCII\n')
	for row in inputMatrix:
		if row: # Row might be empty.
			outputFile.write(str(row[0]) + ' ' + str(row[1]) + ' ' + str(row[2]) + '\n')
	
	inputFile.close()
	outputFile.close()
	print "Done!"
	