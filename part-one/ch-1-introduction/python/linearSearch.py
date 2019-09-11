'''
Author: Trinity Lundgren
Date: 2019-09-10
Description: Implementation of linear sort in python. Accepts a comma-separated
string of numbers at the command line and a target value following a space.
Returns the index of the target value if it exists in the list, otheriwse it
returns None.
'''

import sys

def linear_search(array, target):
    for ele in enumerate(array):
        if ele[1] == target:
            return ele[0]
    return None

arr = list(map(int, sys.argv[1].split(',')))
target = int(sys.argv[2])

print(linear_search(arr, target))
