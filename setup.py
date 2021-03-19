# Using distutils is probably the easiest way to distribute a python C module.
# See https://docs.python.org/3/extending/building.html#building-c-and-c-extensions-with-distutils
# for more information about how this works, though the simplest example should
# be something like this:

from distutils.core import setup, Extension

example_library = Extension(
    "example_library",
    sources=["example_library.c"]
)

description = "Just an example of how to create a python C library."
setup(name="Example Library", version="1.0", description=description,
    ext_modules=[example_library])

