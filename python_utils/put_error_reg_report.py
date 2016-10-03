# put_error_reg_report.py
# By Jean-Francois Tremblay, September 29 2016
#
# Update a previously done registration report with the
# alignement error, which is determined using another mean of
# registration. The error is represented by the term by term
# error on the 4x4 transform matrix.

import numpy as np
import sys

if __name__ == "__main__":
    answer_path = sys.argv[1]
    report_path = sys.argv[2]

    answer_file = open(answer_path, 'r')
    report_file_read = open(report_file, 'r')

    answer_reg = np.ndarray(shape=(4,4), dtype=float)
    tlr_reg = np.ndarray(shape=(4,4), dtype=float)
    reg_error = np.ndarray(shape=(4,4), dtype=float)

    i = 0
    for line in answer_file:
        if i == 4:
            break
        matrix_line = line.split(' ')
        answer_reg[i,0] = float(matrix_line[0])
        answer_reg[i,1] = float(matrix_line[1])
        answer_reg[i,2] = float(matrix_line[2])
        answer_reg[i,3] = float(matrix_line[3])
        i = i + 1

    report = report_file_read.readlines()

    i = 0
    for line in report:
        if i >= 6 and i <= 9:
            matrix_line = line.split(' ')
            tlr_reg[i,0] = float(matrix_line[0])
            tlr_reg[i,1] = float(matrix_line[1])
            tlr_reg[i,2] = float(matrix_line[2])
            tlr_reg[i,3] = float(matrix_line[3])
        if i == 9:
            break
        i = i + 1
    
    reg_error = tlr_reg - answer_reg