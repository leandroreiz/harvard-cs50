from cs50 import get_int

# only accept numbers between 1-8
while True:
    height = get_int("Height: ")
    if height > 0 and height <= 8:
        break

# loop to create the pyramids
for i in range(height):
    print(" " * (height-(i+1)), end="")
    print("#" * (i+1), end="  ")
    print("#" * (i+1))