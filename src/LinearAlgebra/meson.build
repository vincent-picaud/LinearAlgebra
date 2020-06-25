LinearAlgebra_headers = [
  'vector.hpp',
  'matrix.hpp'
]
LinearAlgebra_sources = [

]

subdir('blas')
subdir('lapack')

subdir('utils')
subdir('expr')
subdir('metaexpr')
subdir('dense')
subdir('scalar_functions')

LinearAlgebra_lib = library('LinearAlgebra',
			    include_directories : inc,
			    install : true,
			    sources: [LinearAlgebra_headers,LinearAlgebra_sources])

LinearAlgebra_dep = declare_dependency(include_directories : inc,
				       link_with : [LinearAlgebra_lib,],
				       dependencies : [lapack_lib,blas_lib,])

install_headers(LinearAlgebra_headers,
		subdir : 'LinearAlgebra')

