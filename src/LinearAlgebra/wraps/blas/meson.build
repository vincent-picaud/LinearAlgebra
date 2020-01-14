cpp = meson.get_compiler('cpp')


#################################################################
# Here define a list of candidate blas lib...
# Here we currently only check one 
#################################################################
# find cblas lib 
# 
# Note: a priori for Debian, one has to search blas.so lib and NOT
# cblas.so lib.
#
blas_lib = cpp.find_library('blas', required: false, disabler: true)
cpp_code = '#include <cblas.h>'

# important: use ''' and not simply ' as we want to take into account
# end line jumps
#
if not cpp.links(cpp_code+'''
   int main()
   {
     double v[6] = {1, 3, 5, 2, 4, 6};
     cblas_dnrm2(6,v,1);
     return 0;
   }''', dependencies: blas_lib, name: 'CBLAS')

  blas_lib = disabler() # reset flag
endif

#################################################################
# If not found we are done...
#################################################################

if not blas_lib.found()
  subdir_done()
endif
