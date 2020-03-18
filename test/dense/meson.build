test_array = [
  ['vector_test','vector_exe','vector.cpp'],
  ['matrix_storage_scheme_test','matrix_storage_scheme_exe','matrix_storage_scheme.cpp'],
  ['matrix_test','matrix_exe','matrix.cpp'],

  ['vector_crtp_size_utils_test','vector_crtp_size_utils_exe','vector_crtp_size_utils.cpp'],
  ['vector_transform_test','vector_transform_exe','vector_transform.cpp'],
  ['vector_map_test','vector_map_exe','vector_map.cpp'],
]

foreach test : test_array
  test(test.get(0),
       executable(test.get(1),
		  test.get(2),
		  include_directories : inc, 
		  dependencies
 		  : [ LinearAlgebra_dep, gtest_dep, ]))
endforeach


