test_array = [
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


