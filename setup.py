from distutils.core import setup, Extension

mingener = Extension('mingener',
    sources = ['mingener.c'])

setup(  name='mingener',
        version='0.1',
        description = 'an experimental CPython extension',
        ext_modules = [mingener],
)
