# advent of code day 1 solution
from enum import Enum


digit_string_representions = ['one', 'two', 'three', 'four', 'five',
                    'six', 'seven', 'eight', 'nine', 'ten']
numbers = Enum('Number', digit_string_representions)


def find_digits(line : str):
    digits = []
    for index, char in enumerate(line):
        for digit_string in digit_string_representions:
            if line.startswith(digit_string, index):
                digits.append(numbers[digit_string].value)
        if char.isdigit():
            digits.append(int(char))
    return digits
   
                
if __name__ == "__main__":
    calibration_data = []
    with open('01\input.txt', 'r') as input:
        calibration_data = input.readlines()

    calibration_values = []
    for line in calibration_data:
        digits = find_digits(line)
        calibration_values.append(digits[0]*10 + digits[-1])
    
    print(sum(calibration_values))
