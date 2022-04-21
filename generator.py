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

input_file = open("input_file", "w")
input_file.write(str(a) + "\n" + str(b))
input_file.close()
