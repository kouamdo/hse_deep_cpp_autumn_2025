#include <iostream>
#include <Python.h>

uint64_t fibonacci(int64_t n)
{
    if (n < 2)
        return 1;
    return fibonacci(n-1) + fibonacci(n-2);
}

PyObject* cutils_fibonacci(PyObject* self, PyObject* args)
{
    size_t n = 0;
    if (!PyArg_ParseTuple(args, "l", &n))
    {
        PyErr_Format(PyExc_TypeError, "Failed to parse arguments");
        return nullptr;
    }

    uint64_t res = fibonacci(n);
    return PyLong_FromLong(res);
}

PyObject* cutils_sum(PyObject* self, PyObject* args)
{
    PyObject* list_obj;
    if (!PyArg_ParseTuple(args, "O", &list_obj))
    {
        std::cerr << "Failed to parse arguments" << std::endl;
        PyErr_Format(PyExc_TypeError, "Failed to parse arguments");
        return nullptr;
    }

    size_t n = PyList_Size(list_obj);
    int64_t res = 0;
    for (size_t i = 0; i < n; ++i)
    {
        PyObject* tmp = PyList_GetItem(list_obj, i);
        int64_t num = PyLong_AsLong(tmp);
        res += num;
    }
    return Py_BuildValue("i", res);
}

static PyMethodDef methods[] = {
    {"sum", cutils_sum, METH_VARARGS, "Считаем сумму элементов в массиве"},
    {"fibonacci", cutils_fibonacci, METH_VARARGS, "Возвращает i-ый элемент последовательности Фибоначи"},
    {nullptr, nullptr, 0, nullptr}
};

static PyModuleDef cutilsmodule = {
    PyModuleDef_HEAD_INIT,
    "cutils",
    "Примеры написания модуля расширения на C++ для Python",
    -1,
    methods
};

PyMODINIT_FUNC PyInit_cutils(void)
{
    return PyModule_Create(&cutilsmodule);
}
