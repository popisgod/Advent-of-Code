# Advent of Code solution day 02
import re
import math 


if __name__ == "__main__":
    game_data = []
    with open('02/input.txt', 'r') as input_file:
        game_data = input_file.readlines()

    game_power = []

    for game in game_data:
        cube_collection = re.findall(r'(\d+)\s(red|blue|green)', game)
        
        colors = {'red': 0, 'blue': 0, 'green': 0}
        
        for quantity, color in cube_collection:
            if int(quantity) > colors[color]:
                colors[color] = int(quantity)

        game_power.append(math.prod(colors.values()))

    print(sum(game_power))
