from sys import argv, exit
from json import dump
from random import randint

if len(argv) < 4:
    print(
        "The required arguments don't match with the amount of given argument. "
        "Enter a width, a height and a rate of cells between 1 and 100"
    )
    exit()
elif int(argv[3]) > 100 or int(argv[3]) <= 0:
    print("The cell rate is out of bounds, enter a number between 1 and 100")
    exit()

width = int(argv[1])
height = int(argv[2])

cellRate = int(argv[3])

position: list[list[int]] = [
    [
         (1 if randint(1, 100) in range(1, cellRate + 1) else 0) for _ in range(width)
    ] 
    for _ in range(height)
]
file = open("./random.json", "w")

dump(position, file)