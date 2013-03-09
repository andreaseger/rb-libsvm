require 'mkmf'

$CFLAGS << " -fopenmp "
$CFLAGS << " -save-temps -ggdb3 " if ENV['DEBUG']
$LDFLAGS << " -lstdc++ -lgomp "

HEADER_DIRS = []
LIB_DIRS = []

dir_config('libsvm', HEADER_DIRS, LIB_DIRS)

create_makefile('libsvm/libsvm_ext')
