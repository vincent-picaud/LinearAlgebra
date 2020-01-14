test_array = [
  ['vector_test','vector_exe','vector.cpp'],
  ['matrix_storage_scheme_test','matrix_storage_scheme_exe','matrix_storage_scheme.cpp'],
  ['matrix_test','matrix_exe','matrix.cpp'],
  ['known_patterns_impl_test','known_patterns_impl_exe','known_patterns_impl.cpp'],
]

foreach test : test_array
  test(test.get(0),
       executable(test.get(1),
		  test.get(2),
		  include_directories : inc, 
		  dependencies
 		  : [ gtest_dep ]))
endforeach


