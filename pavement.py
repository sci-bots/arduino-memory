import sys

from paver.easy import task, needs, path, sh, cmdopts, options
from paver.setuputils import setup, install_distutils_tasks
from distutils.extension import Extension
from distutils.dep_util import newer

sys.path.insert(0, path('.').abspath())
import version

setup(name='arduino-memory',
      version=version.getVersion(),
      description='Simple Arduino library for querying amount of free RAM '
                  'memory.',
      keywords='arduino memory',
      author='Christian Fobel',
      author_email='christian@fobel.net',
      url='https://github.com/wheeler-microfluidics/arduino-memory',
      license='GPL',
      packages=['arduino_memory', ],
      # Install data listed in `MANIFEST.in`
      include_package_data=True)


@task
def build_arduino_library():
    import os
    import tarfile

    arduino_lib_dir = path('arduino_memory').joinpath('lib')
    if not arduino_lib_dir.isdir():
        arduino_lib_dir.mkdir()
    tf = tarfile.TarFile.bz2open(arduino_lib_dir
                                 .joinpath('Memory-Arduino.tar.gz'), 'w')
    for s in path('arduino_memory').joinpath('Arduino', 'Memory').files():
        tf.add(s, os.path.join('Memory', s.name))
    tf.close()


@task
@needs('generate_setup', 'minilib', 'build_arduino_library',
       'setuptools.command.sdist')
def sdist():
    """Overrides sdist to make sure that our setup.py is generated."""
    pass
