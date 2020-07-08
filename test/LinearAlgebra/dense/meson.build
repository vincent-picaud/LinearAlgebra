test_array = [
  ['vmt_crtp_test','vmt_crtp_exe','vmt_crtp.cpp'],
  
  ['vector_test','vector_exe','vector.cpp'],
  ['matrix_storage_scheme_test','matrix_storage_scheme_exe','matrix_storage_scheme.cpp'],
  ['matrix_test','matrix_exe','matrix.cpp'],

  ['vector_crtp_size_utils_test','vector_crtp_size_utils_exe','vector_crtp_size_utils.cpp'],
  ['vector_transform_test','vector_transform_exe','vector_transform.cpp'],
  ['vector_map_test','vector_map_exe','vector_map.cpp'],

  ['matrix_map_test','matrix_map_exe','matrix_map.cpp'],

  ['vector_are_compatible_test','vector_are_compatible_exe','vector_are_compatible.cpp'],
  ['matrix_are_compatible_test','matrix_are_compatible_exe','matrix_are_compatible.cpp'],

  ['vector_view_test','vector_view_exe','vector_view.cpp'],
  ['matrix_view_test','matrix_view_exe','matrix_view.cpp'],
  
  ['matrix_view_row_column_test','matrix_view_row_column_exe','matrix_view_row_column.cpp'],

  ['memory_chunk_test','memory_chunk_exe','memory_chunk.cpp'],
  ['memory_chunk_aliasing_p_test','memory_chunk_aliasing_p_exe','memory_chunk_aliasing_p.cpp'],

  # ---------
  ['vector_comparison_operators_test','vector_comparison_operators_exe','vector_comparison_operators.cpp'],
  ['matrix_comparison_operators_test','matrix_comparison_operators_exe','matrix_comparison_operators.cpp'],
  # ------
  ['vector_create_generic_view_test','vector_create_generic_view_exe','vector_create_generic_view.cpp'],
  ['matrix_create_generic_view_test','matrix_create_generic_view_exe','matrix_create_generic_view.cpp'],
]

foreach test : test_array
  test(test.get(0),
       executable(test.get(1),
		  test.get(2),
		  include_directories : inc, 
		  dependencies
 		  : [ LinearAlgebra_dep, gtest_dep, ]))
endforeach


