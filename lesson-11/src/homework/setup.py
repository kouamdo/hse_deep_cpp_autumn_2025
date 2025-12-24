#!/usr/bin/env python3
from setuptools import setup, Extension

# Définition du module C
module_cjson = Extension(
    'cjson',
    sources=['cjson.c'],
)

# Configuration minimale
setup(
    name='cjson',
    version='1.0',
    description='Module C pour le parsing JSON',
    ext_modules=[module_cjson],
)