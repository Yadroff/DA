import random
import string


def random_word(length: int):
    letters = string.ascii_lowercase
    return ''.join(random.choice(letters) for i in range(length))


if __name__ == "__main__":
    for i in range(1, 9):
        with open("tests/{}.in".format(i), "w") as test_file:
            test_file.write(random_word(10 ** i) + '\n')
