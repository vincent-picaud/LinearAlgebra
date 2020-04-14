subdir('LinearAlgebra/utils')
subdir('LinearAlgebra/dense')
subdir('LinearAlgebra/expr')
subdir('LinearAlgebra/metaexpr')
subdir('LinearAlgebra/scalar_functions')

if blas_lib.found()
  subdir('LinearAlgebra/blas')
endif 

if lapack_lib.found()
  subdir('LinearAlgebra/lapack')
endif
