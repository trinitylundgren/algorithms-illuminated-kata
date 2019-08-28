'''
Author: Trinity Lundgren
Date: 2019-08-27
Description: Python implementation of the "third grade multiplication" example
algorithm from Algorithms Illuminated: Part I by Tim Roughgarden.
'''

import sys

def third_grade_multiply(a, b):
    string_a = str(a)
    string_b = str(b)

    # Pad shorter string with leading zeros if needed
    if len(string_a) < len(string_b):
        string_a = "0" * (len(string_b) - len(string_a)) + string_a
    elif len(string_b) < len(string_a):
        string_b = "0" * (len(string_a) - len(string_b)) + string_b

    # Perform multiplication of individual digits, store intermediate products
    num_int_products = len(string_b)
    intermediate_products = []
    for i in range(num_int_products):
        carry = 0
        int_result = ""
        result = 0
        a_digit = int(string_a[len(string_a) - 1 - i])
        for j in range(len(string_b)):
            big_result = a_digit * int(string_b[len(string_b) - 1 - j])
            big_result += carry
            result = big_result % 10
            carry = big_result // 10
            int_result = str(result) + int_result
        int_result = str(carry) + int_result
        intermediate_products.append(int_result)

    # Generate list of padded intermediate products, indent previous
    # list of intermediate products for printing
    padded_int_products = []
    padded_length = 2 *  len(string_b)
    for i in range(num_int_products):
        with_lag = intermediate_products[i] + i * "0"
        diff = padded_length - len(with_lag)
        intermediate_products[i] = ((padded_length - len(with_lag)) * " " +
                                    intermediate_products[i])

        # Remove single leading zero from intermediate products
        j = 0
        while intermediate_products[i][j] == ' ':
            if intermediate_products[i][j + 1] == "0":
                intermediate_products[i] = (intermediate_products[i][0:j + 1] +
                                            intermediate_products[i][j + 2:])
            j += 1

        # Pad padded_int_products with leading zeros
        with_lead = (diff + 1) * "0" + with_lag
        padded_int_products.append(with_lead)

    # Add intermediate products
    final_product = ""
    carry = 0
    for i in range(padded_length, -1, -1):
        big_sum = 0
        for j in range(num_int_products):
            big_sum += int(padded_int_products[j][i])
        big_sum += carry
        small_sum = big_sum % 10
        carry = big_sum // 10
        final_product = str(small_sum) + final_product

    slice_index = 0
    for i in range(len(final_product)):
        if final_product[i] == '0':
            slice_index += 1
        else:
            break


    # Print visual element
    print((padded_length - len(str(b))) * " " + str(b))
    print((padded_length - len(str(a)) - 2) * " " + "\u2715" + " " +  str(a))
    line = padded_length * "\u2500"
    print(line)
    if len(str(a)) > 1:
        for i in range(len(str(a))):
            print(intermediate_products[i])
        print(line)
    print((padded_length - len(final_product[slice_index:])) * " " +
            final_product[slice_index:])

a = sys.argv[1]
b = sys.argv[2]

third_grade_multiply(a,b)
