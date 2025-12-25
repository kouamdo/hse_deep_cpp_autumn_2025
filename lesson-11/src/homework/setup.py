#!/usr/bin/env python3
import sys
import os
from setuptools import setup, Extension

# Vérifier si Python.h est disponible
try:
    import sysconfig
    include_dirs = [sysconfig.get_path('include')]
except:
    # Fallback pour les anciennes versions
    import distutils.sysconfig
    include_dirs = [distutils.sysconfig.get_python_inc()]

# Débug : afficher les chemins d'inclusion
print(f"Include directories: {include_dirs}")

# Définition du module C
module_cjson = Extension(
    'cjson',
    sources=['cjson.c'],
    include_dirs=include_dirs,
    extra_compile_args=['-O2', '-Wall', '-Wextra'],
)

# Configuration
setup(
    name='cjson',
    version='1.0',
    description='Module C pour le parsing JSON',
    ext_modules=[module_cjson],
)