from __future__ import print_function

import mingener

for k in mingener.CounterDowner(20):
    print(k, end=' ')

mingener.CounterDowner(1234)
mingener.CounterDowner(-10)
