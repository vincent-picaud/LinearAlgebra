test_array = [
  ['dot_vector_test','dot_vector_exe','dot_vector.cpp'],
  ['norm_2_vector_test','norm_2_vector_exe','norm_2_vector.cpp'],
  ['dist_2_vector_test','dist_2_vector_exe','dist_2_vector.cpp'],
]

foreach test : test_array
  test(test.get(0),
       executable(test.get(1),
		  test.get(2),
		  include_directories : inc, 
		  dependencies
 		  : [ LinearAlgebra_dep, gtest_dep, ]))
endforeach


