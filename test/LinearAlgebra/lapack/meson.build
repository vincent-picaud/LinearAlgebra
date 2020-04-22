test_array = [
    'cholesky',
    'is_lapack_supported_scalar',
    'to_lapack_uplo',
  ]

foreach test : test_array
  test(test+'_test',
       executable(test+'_exe',
		  test+'.cpp',
		  dependencies
 		  : [ LinearAlgebra_dep, gtest_dep ]))
endforeach
