test_array = [
  ['dot_test','dot_exe','dot.cpp'],
]

foreach test : test_array
  test(test.get(0),
       executable(test.get(1),
		  test.get(2),
		  include_directories : inc, 
		  dependencies
 		  : [ LinearAlgebra_dep, gtest_dep, ]))
endforeach


