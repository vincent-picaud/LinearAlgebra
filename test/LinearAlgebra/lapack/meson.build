test_array = [['cholesky_test','cholesky_exe','cholesky.cpp']]

foreach test : test_array
  test(test.get(0),
       executable(test.get(1),
		  test.get(2),
		  dependencies
 		  : [ LinearAlgebra_dep, gtest_dep ]))
endforeach
