import random

print("Generate random linear function (ax+b)")
a_lower = float(input("Input lower value for a: "))
a_upper = float(input("Input upper value for a: "))
b_lower = float(input("Input lower value for b: "))
b_upper = float(input("Input upper value for b: "))

rnd_a = random.random()
a = rnd_a * (a_upper - a_lower) + a_lower
rnd_b = random.random()
b = rnd_b * (b_upper - b_lower) + b_lower

points_num = input("Input number of points to be evaluated\n")
try:
    points_num = int(points_num)
except:
    print("Invalid value")
    exit()

x_err = random.randint(1, 5)
y_err = random.randint(1, 5)
input_file = open("data/input_file", "w")
input_file.write(str(a) + "\n" + str(b) + "\n")
input_file.write(str(points_num) + "\n" + str(x_err) + "\n" + str(y_err) + "\n" + str(0) + "\n" + str(5))



for i in range(1, 5):
    cutoff = points_num // pow(2, i)
    input_file.write("\n" + str(cutoff))

input_file.close()
input_file = open("data/file_test", "w")
input_file.write(str(1))