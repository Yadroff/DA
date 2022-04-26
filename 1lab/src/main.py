from random import randrange

# key - +___-_______
# value - int


OUTPUT_DATA_SIZE = 100
MAX_VALUE = 2 ** 32 - 1
MIN_VALUE = -(2 ** 32)

result_data_file = open("data100.txt", "w")
empty_string = '\n'

for i in range(OUTPUT_DATA_SIZE):
    country_code_length = randrange(1, 4)

    result_string = '+'
    for j in range(country_code_length):
        result_string += str(randrange(0, 9))

    result_string += '-'
    for j in range(3):
        result_string += str(randrange(0, 9))

    result_string += '-'
    for j in range(7):
        result_string += str(randrange(0, 9))

    result_string += '\t'
    result_string += str(randrange(MIN_VALUE, MAX_VALUE))
    result_string += '\n'
    result_data_file.write(result_string)

result_data_file.close()
