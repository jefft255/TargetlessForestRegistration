def loadAscFile(file):
	nbrHeaderLinesSkipped = 0
	lineCounter = 0
	inputMatrix = [[]]
	
	print "Reading the input file...\n"
	for line in inputFile:
		if re.search('[a-zA-Z]+',line):
			nbrHeaderLinesSkipped += 1
			break
		x,y,z = line.split(' ')
		z.replace('\n','') # We remove the new line symbol before converting to float
		inputMatrix.append([])
		inputMatrix[lineCounter].append(x)
		inputMatrix[lineCounter].append(y)
		inputMatrix[lineCounter].append(z)
		lineCounter += 1
	
	return inputMatrix, nbrHeaderLinesSkipped