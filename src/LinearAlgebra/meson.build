LinearAlgebra_headers = ['hello.hpp']
LinearAlgebra_sources = ['hello.cpp']

LinearAlgebra_lib = library('LinearAlgebra',
				include_directories : inc,
				install : true,
				sources: [LinearAlgebra_headers,LinearAlgebra_sources])

LinearAlgebra_dep = declare_dependency(include_directories : inc,
					   link_with : LinearAlgebra_lib)

install_headers(LinearAlgebra_headers,
		 subdir : 'LinearAlgebra')

