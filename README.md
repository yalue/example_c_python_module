Example Python C Module
=======================

This contains only a simple Python C module definition, largely to serve as a
reminder to myself when I need to create one.

_This requires Python 3_.  On the whole, a Python 2 module will look nearly
identical, but Python 2 has some very slight differences in its C API that will
prevent this from compiling under python 2.

Both `example_library.c` and `setup.py` contain abundant comments. Start by
looking at `example_library.c`; `setup.py` is only relevant when you're ready
to compile and use the library.

If you're confused by this example, the
[official tutorial](https://docs.python.org/3/extending/extending.html) is
a good starting point.

Usage
-----

To set this up, clone the repository and run `python setup.py install`. (Or, if
necessary, `python3 setup.py install`.)

After installing it you, can use it in your python code as follows:

```python
import example_library

# View the docstrings we defined in C.
help(example_library)

# Make sure our function works properly.
example_library.print_number(1337)

# Every one of these should raise an exception for a different reason.
example_library.print_number()
example_library.print_number("hi!")
example_library.print_number(-1)
```

