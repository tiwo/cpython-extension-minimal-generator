import mingener

print(mingener.print_countdown(9))

try: mingener.print_countdown(1234)
except OverflowError: pass
else: 1/0

try: mingener.print_countdown(-10)
except OverflowError: pass
else: 1/0
