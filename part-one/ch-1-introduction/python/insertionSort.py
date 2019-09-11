'''
Author: Trinity Lundgren
Date: 2019-09-10
Description: Python implementation of insertion sort. Accepts a string of comma-
separated numbers at the command line, creates a sorted list of integers based
on that list and sorts it. Prints the sorted list to the console.
'''

import sys

def insertion_sort(array):
    for j in range(1, len(array)):
        key = array[j]
        i = j - 1
        while i >= 0 and array[i] > key:
            array[i + 1] = array[i]
            i = i - 1
        array[i + 1] = key

# Accept comma-separated list of numeric strings at command line, convert to int
a = list(map(int,sys.argv[1].split(',')))

insertion_sort(a)
print(a)
