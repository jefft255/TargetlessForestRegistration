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
    # Formatting for matrix printing
    np.set_printoptions(precision=4)
    np.set_printoptions(suppress=True)

    answer_path = sys.argv[1]
    report_path = sys.argv[2]

    answer_file = open(answer_path, 'r')
    report_file_read = open(report_path, 'r', encoding='utf16')

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

    # Store the file's content and close it
    report = report_file_read.readlines()
    report_file_read.close()

    # Reopen the file for writing
    report_file_write = open(report_path, 'w')

    i = 0
    for line in report:
        if i >= 6 and i <= 9:
            matrix_line = line.split(' ')
            # Need this because there are multiple spaces
            # between elements
            matrix_line = list(filter(None, matrix_line))
            tlr_reg[i-6,0] = float(matrix_line[0])
            tlr_reg[i-6,1] = float(matrix_line[1])
            tlr_reg[i-6,2] = float(matrix_line[2])
            tlr_reg[i-6,3] = float(matrix_line[3])
        if i == 9:
            break
        i = i + 1
    
    reg_error = tlr_reg - answer_reg
    report.insert(10, "====== Registration Error ======\n")
    report.insert(11, str(reg_error) + "\n")
    report.insert(12, "====== Actual transform matrix ======\n")
    report.insert(13, str(answer_reg) + "\n")

    report_file_write.write("".join(report))
    report_file_write.close()
