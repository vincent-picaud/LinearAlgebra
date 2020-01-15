# See: https://mesonbuild.com/Configuration.html
#
blas_config = configuration_data({
				  'HAS_BLAS' : 'false',
				  'BLAS_INCLUDE' : '""'
				})


#################################################################
# TODO:
#
# for the moment only one attempt (=OpenBlas), would be nice to have a
# list of candidate BLAS lib (MKL...)
#################################################################
#
# find cblas lib 
#----------------------------------------------------------------
# Note: a priori for Debian, one has to search blas.so lib and NOT
# cblas.so lib.
#
cpp = meson.get_compiler('cpp')

blas_lib = cpp.find_library('blas', required: false, disabler: true)
blas_include = '#include <cblas.h>'

# try to compile and link with it
#----------------------------------------------------------------
# important: use ''' and not simply ' as we want to take into account
# end line jumps
#
if cpp.links(blas_include+'''
   int main()
   {
     double v[6] = {1, 3, 5, 2, 4, 6};
     cblas_dnrm2(6,v,1);
     return 0;
   }''', dependencies: blas_lib, name: 'CBLAS')

  blas_config.set('HAS_BLAS','true')
  blas_config.set('BLAS_INCLUDE',blas_include)
else
  blas_lib = disabler() # link failed -> creset flag
endif

#################################################################
# Generate configure file
#################################################################
#
configure_file(input : 'blas_config.hpp.in',
               output : 'blas_config.hpp',
               configuration : blas_config)


# if not found, done...
if not blas_lib.found()
  subdir_done()
endif

# here other stuff depending on blas_lib

# NOTE: for the moment, blas_lib is used in
#
# LinearAlgebra/src/LinearAlgebra/meson.build
#
# LinearAlgebra_dep = declare_dependency(include_directories : inc,
# 				       link_with : [LinearAlgebra_lib,],
# 				       dependencies : [blas_lib,])
#
# However It must certainly be better to use:
# https://mesonbuild.com/Reference-manual.html#declare_dependency
#
# I guess something like:
#
# blas_dep=dependency_object declare_dependency(include_directories : ???,
#    	                                        link_with : [blas_lib,])
#
# but I do know how to fill the ???
#
