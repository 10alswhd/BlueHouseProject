#!/usr/bin/env python3

import random

NUMBERS = list(map(str, range(10)))

class BaseBall:
    def __init__(self, slot):
        self.slot = slot

    def generate_numbers(self):
        self.numbers = random.sample(NUMBERS, self.slot)

    def get_input(self):
        while True:
            numbers = input('Please input numbers:')
            # simple input verify
            numbers = list(filter(lambda x: x in NUMBERS, numbers))
            if len(numbers) == self.slot:
                break
            print ('wrong input, try again')

        return numbers

    def calculate_point(self, numbers):
        out, ball, strike = 0, 0, 0
        for i, n in enumerate(numbers):
            if not n in self.numbers:
                out += 1
                continue
            index = self.numbers.index(n)
            if i == index:
                strike += 1
            else:
                ball += 1
        return strike, ball, out

    def main(self):
        print('Play ball with %d slots'%self.slot)
        self.generate_numbers()
        while True:
            numbers = self.get_input()
            s, b, o = self.calculate_point(numbers)
            print('Strike: %d, Ball: %d, Out: %d'%(s, b, o))
            if s == self.slot:
                break

if __name__ == '__main__':
    slot = input('Please input number slot[3, 4]:')
    if slot != '3' or slot != '4':
        slot = '3'
    b = BaseBall(int(slot))
    b.main()
