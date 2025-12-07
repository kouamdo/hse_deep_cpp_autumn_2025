#! /usr/bin/env python3

import ctypes


def main():
    utils_lib = ctypes.CDLL('./libutils.so')
    utils_lib.sum.argstype = [ctypes.POINTER(ctypes.c_int), ctypes.c_int]
    utils_lib.sum.restype = ctypes.c_int

    arr = list(range(0, 10))
    arr_len = len(arr)
    arr_type = ctypes.c_int * arr_len
    result = utils_lib.sum(arr_type(*arr), ctypes.c_int(arr_len))
    print(f"Result is {result}")

    utils_lib.fibonacci.argstype = [ctypes.c_int]
    utils_lib.fibonacci.restype = ctypes.c_int
    print(utils_lib.fibonacci(3))

    utils_lib = ctypes.cdll.LoadLibrary('/lib64/libc-2.17.so')
    utils_lib.strstr.argstype = [ctypes.c_char_p, ctypes.c_char_p]
    utils_lib.strstr.restype = ctypes.c_char_p

    res = utils_lib.strstr(b'bombaleia', b'ale')
    print(res)
    res = utils_lib.strstr(b'bombaleio', b'123')
    print(res)

if __name__ == "__main__":
    main()
