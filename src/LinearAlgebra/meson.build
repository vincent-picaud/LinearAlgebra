LinearAlgebra_headers = [
  'hello.hpp',
  # Dense vector/matrix user header 
  'vector.hpp',
  'matrix.hpp'
]
LinearAlgebra_sources = ['hello.cpp']

subdir('utils')
subdir('expr')
subdir('metaexpr')
subdir('dense')
subdir('blas')
subdir('scalar_functions')



LinearAlgebra_lib = library('LinearAlgebra',
			    include_directories : inc,
			    install : true,
			    sources: [LinearAlgebra_headers,LinearAlgebra_sources])

LinearAlgebra_dep = declare_dependency(include_directories : inc,
				       link_with : [LinearAlgebra_lib,],
				       dependencies : [blas_lib,])

install_headers(LinearAlgebra_headers,
		subdir : 'LinearAlgebra')

