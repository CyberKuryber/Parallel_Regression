import random
import time

import numpy as np

# print("Generate random linear function (ax+b)")
# a_lower = float(input("Input lower value for a: "))
# a_upper = float(input("Input upper value for a: "))
# b_lower = float(input("Input lower value for b: "))
# b_upper = float(input("Input upper value for b: "))
start = time.time()

# rnd_a = random.random()
a = 1.5
# rnd_b = random.random()
b = 2

# points_num = input("Input number of points to be evaluated\n")
# try:
#     points_num = int(points_num)
# except:
#     print("Invalid value")
#     exit()
x_err = 5
y_err = 5

for i in range(1, 5):
    points_num = 100 * pow(10, i)
    input_file = open("data/input_file" + str(i), "w")
    input_file.write(str(a) + "\n" + str(b) + "\n")
    input_file.write(str(points_num) + "\n" + str(x_err) + "\n" + str(y_err) + "\n" + str(0) + "\n" + str(5))

    for j in range(1, 5):
        cutoff = points_num // pow(2, j)
        input_file.write("\n" + str(cutoff))

    x = np.linspace(0, 5, points_num)
    x = x+ (random.random()*2 -1)*x_err/100 *x
    f = lambda x: a * x + b
    y = f(x)

    for j in range(len(x)):
        input_file.write("\n" + str(x[j]))
        input_file.write("\n" + str(y[j]))

    input_file.close()

input_file = open("data/file_test", "w")
input_file.write(str(1))
end = time.time()
print(end - start)
