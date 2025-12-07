#! /usr/bin/env python3

import cffi

def libc():
    ffi = cffi.FFI()
    lib = ffi.dlopen('/lib64/libc-2.17.so')
    ffi.cdef('char* strstr(char*, char*);')
    res = lib.strstr(b'bambaleio', b'le')
    print(ffi.string(res))

def main():
    libc()

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

if __name__ == "__main__":
    main()
