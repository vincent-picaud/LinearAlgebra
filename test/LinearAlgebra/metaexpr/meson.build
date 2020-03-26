test_array = [
  ['metaexpr_crtp_test','metaexpr_crtp_metaexe','metaexpr_crtp.cpp'],
]

foreach test : test_array
  test(test.get(0),
       executable(test.get(1),
		  test.get(2),
		  include_directories : inc, 
		  dependencies
 		  : [ LinearAlgebra_dep, gtest_dep ]))
endforeach


