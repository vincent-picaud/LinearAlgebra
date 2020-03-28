test_array = [
  ['metaexpr_crtp_test','metaexpr_crtp_metaexe','metaexpr_crtp.cpp'],
  ['call_assign_from_metaexpr_test','call_assign_from_metaexpr_metaexe','call_assign_from_metaexpr.cpp'],
  ['some_expressions_test','some_expressions_metaexe','some_expressions.cpp'],
]

foreach test : test_array
  test(test.get(0),
       executable(test.get(1),
		  test.get(2),
		  include_directories : inc, 
		  dependencies
 		  : [ LinearAlgebra_dep, gtest_dep ]))
endforeach


