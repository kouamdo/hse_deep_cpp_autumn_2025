#! /usr/bin/env python3

import random

import cutils


def main():
    arr = [random.randint(0, 10) for _ in range(0, 10)]
    print(f'{arr=}, {sum(arr)}')
    print(f'cutils.sum={cutils.sum(arr)}')

if __name__ == "__main__":
    main()

