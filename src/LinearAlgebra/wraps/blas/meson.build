# See: https://mesonbuild.com/Configuration.html
#
blas_config = configuration_data({
				  'HAS_BLAS' : 'false',
				  'BLAS_INCLUDE' : '""'
				})





#################################################################
# Here define a list of candidate blas lib...
# Here we currently only check one 
#################################################################
# find cblas lib 
# 
# Note: a priori for Debian, one has to search blas.so lib and NOT
# cblas.so lib.
#
cpp = meson.get_compiler('cpp')

blas_lib = cpp.find_library('blas', required: false, disabler: true)
blas_include = '#include <cblas.h>'

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
  blas_lib = disabler() # reset flag
endif

#################################################################
# If not found we are done...
#################################################################

configure_file(input : 'blas_config.hpp.in',
               output : 'blas_config.hpp',
               configuration : blas_config)


if not blas_lib.found()
  subdir_done()
endif
