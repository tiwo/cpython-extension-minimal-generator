from __future__ import print_function

import mingener

for k in mingener.CounterDowner(20):
    print(k, end=' ')

try: mingener.CounterDowner(1234)
except OverflowError: pass
else: 1/0

try: mingener.CounterDowner(-10)
except OverflowError: pass
else: 1/0
