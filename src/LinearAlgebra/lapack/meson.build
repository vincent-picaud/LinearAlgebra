# Dependencies: aptitude install liblapacke-dev
#


# Note: whatever happen always include files
#================================================================
#
LinearAlgebra_headers += [
  'lapack/lapack.hpp',
  'lapack/subroutines.hpp',
  # 'lapack/to_clapack_transpose.hpp',
  # 'lapack/to_clapack_uplo.hpp',
  # 'lapack/to_clapack_diag.hpp',
  # 'lapack/is_clapack_supported_scalar.hpp',
]

# Prepare lapack_config.hpp.in
#================================================================
# See: https://mesonbuild.com/Configuration.html
#
lapack_config = configuration_data({
				  'HAS_LAPACK' : 'false',
				  'LAPACK_INCLUDE' : '""',
				  'LAPACK_COMPLEX' : '""'
				})


# Try to find system lapack library
#================================================================
#
cpp = meson.get_compiler('cpp')

#
# find lapack lib 
#----------------------------------------------------------------
#
lapack_lib = cpp.find_library('lapacke', required: false) 
lapack_include = '#include <lapacke.h>'

# try to compile and link with it
#----------------------------------------------------------------
# CAVEAT: important: use ''' and not simply ' as we want to take into
#         account end line jumps
#
if cpp.links(lapack_include+'''
   int main() 
   {
     // double v[6] = {1, 3, 5, 2, 4, 6};
     // lapack_dnrm2(6,v,1);
     return 0;
   }''', dependencies: lapack_lib, name: 'LAPACK') # note: name is used for printed message

  lapack_config.set('HAS_LAPACK','true')
  lapack_config.set('LAPACK_INCLUDE',lapack_include)
  lapack_config.set('LAPACK_COMPLEX','''
#define LAPACK_COMPLEX_CUSTOM
#include <ccomplex>
#define lapack_complex_float std::complex<float>
#define lapack_complex_double std::complex<double>
   	''')

endif

if not lapack_lib.found()
  message('try to find another lapack lib')
endif

#################################################################
# Generate configure file
#################################################################
#
if not lapack_lib.found()
  warning('Lapack library NOT found... compiling without it')
endif

configure_file(input : 'lapack_config.hpp.in',
               output : 'lapack_config.hpp',
               configuration : lapack_config)

# Note: to include lapack_lib dependency do not forget to modify 
#
# src/LinearAlgebra/meson.build
#
# as follows:
#
# LinearAlgebra_dep = declare_dependency(include_directories : inc,
#      				       link_with : [LinearAlgebra_lib,],
# 				       dependencies : [lapack_lib,blas_lib,])
