#! /usr/bin/env python3

import time
import ctypes
from functools import lru_cache

import cffi

import cutils
import cyutils


MAX_N = 34

def fibonacci(n: int):
    if n < 2:
        return 1
    return fibonacci(n - 1) + fibonacci(n - 2)

def py_fibonacci(n: int):
    start_ts = time.time()
    res = fibonacci(n)
    end_ts = time.time()
    print(f"[python] Time of execution is {end_ts - start_ts:.5} seconds")
    return res

def ctypes_fibonacci(n: int):
    utils_lib = ctypes.CDLL('./ctypes/libutils.so')
    utils_lib.fibonacci.argstype = [ctypes.c_int]
    utils_lib.fibonacci.restype = ctypes.c_int
    start_ts = time.time()
    res = utils_lib.fibonacci(n)
    end_ts = time.time()
    print(f"[ctypes] Time of execution is {end_ts - start_ts:.5} seconds")
    return res

def cffi_fibonacci(n: int):
    ffi = cffi.FFI()
    ffi.cdef('''int fibonacci(int);''')
    ffi.set_source('cffi_utils', '''
    int fibonacci(int n)
    {
        if (n < 2)
            return 1;
        return fibonacci(n-1) + fibonacci(n-2);
    }
    ''')
    ffi.compile()
    import cffi_utils
    start_ts = time.time()
    res = cffi_utils.lib.fibonacci(n)
    end_ts = time.time()
    print(f"[cffi] Time of execution is {end_ts - start_ts:.5} seconds")
    return res

def capi_fibonacci(n: int):
    start_ts = time.time()
    res = cutils.fibonacci(n)
    end_ts = time.time()
    print(f"[capi] Time of execution is {end_ts - start_ts:.5} seconds")
    return res

def cython_fibonacci(n: int):
    start_ts = time.time()
    res = cyutils.fibonacci(n)
    end_ts = time.time()
    print(f"[cython] Time of execution is {end_ts - start_ts:.5} seconds")
    return res

def main():
    py_res = py_fibonacci(MAX_N)
    ctypes_res = ctypes_fibonacci(MAX_N)
    cffi_res = cffi_fibonacci(MAX_N)
    capi_res = capi_fibonacci(MAX_N)
    cython_res = cython_fibonacci(MAX_N)
    assert 9227465 == py_res == ctypes_res == cffi_res == capi_res == cython_res

if __name__ == "__main__":
    main()
