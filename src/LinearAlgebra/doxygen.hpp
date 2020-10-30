/**
   @mainpage

   A library for linear algebra (work in progress)
 */

/** 
    @defgroup Group_Vector Vector related
*/

/** 
    @defgroup Group_Matrix Matrix related
*/

/**
   @defgroup Group_Patterns Known patterns
   
   A pattern is an expression, like \f$ v=\alpha M w + \beta v \f$
   which is understood by the library.

   Whenever possible such expressions are computed in an efficient
   way, here by a direct call to Blas.

   @note for the moment we have not defined a lot of "alias". Alias
   allow to branch to the "master" pattern from another equivalent
   expression like \f$ v=\beta v + \alpha M w \f$. As a consequence,
   by now you must write \f$ v0 = v1+1*v2 \f$ to compute \f$ v0 =
   v1+v2 \f$.

   @todo fix that by introducing more alias or by introducing more
   specific expressions (not urgent, do that once everything is
   stabilized).
*/

/**
   @ingroup Group_Patterns
   @defgroup Group_Vector_Patterns Patterns only involving Group_Vector
*/

/**
   @ingroup Group_Patterns
   @defgroup Group_Matrix_Patterns Patterns only involving Group_Matrix
*/

