import pkg_resources


def get_library_path():
    return pkg_resources.resource_filename('arduino_memory',
                                           'Arduino/Memory')


def get_includes():
    r"""
    Return the directory that contains the `arduino_memory` Cython *.hpp and
    *.pxd header files.

    Extension modules that need to compile against `arduino_memory` should use
    this function to locate the appropriate include directory.

    Notes
    -----
    When using ``distutils``, for example in ``setup.py``.
    ::

        import arduino_memory
        ...
        Extension('extension_name', ...
                  include_dirs=[...] + arduino_memory.get_includes())
        ...

    """
    return [get_library_path()]
