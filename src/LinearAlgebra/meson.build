LinearAlgebra_headers = [
  'hello.hpp',
  'vector.hpp'
]
LinearAlgebra_sources = ['hello.cpp']

subdir('meta')
subdir('dense')
subdir('wraps')



LinearAlgebra_lib = library('LinearAlgebra',
			    include_directories : inc,
			    install : true,
			    sources: [LinearAlgebra_headers,LinearAlgebra_sources])

LinearAlgebra_dep = declare_dependency(include_directories : inc,
				       link_with : [LinearAlgebra_lib,],
				       dependencies : [blas_lib,])

install_headers(LinearAlgebra_headers,
		subdir : 'LinearAlgebra')

