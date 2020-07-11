// [[file:call_assign_from_metaexpr.org]]
#pragma once

#include "LinearAlgebra/dense/vmt_crtp_fwd.hpp"
#include "LinearAlgebra/expr/assign_fallback.hpp"
#include "LinearAlgebra/expr/expr_tags.hpp"
#include "LinearAlgebra/metaexpr/metaexpr_crtp_fwd.hpp"
#include "LinearAlgebra/utils/crtp.hpp"

#include <tuple>
#include <type_traits>

namespace LinearAlgebra
{
  namespace Detail
  {
    // [BEGIN_from_metaexpr_to_reverse_Polish_tuple]
    //
    // These functions convert an
    // [[file:metaexpr_crtp.hpp][=MetaExpr=]] expression into a
    // reverse Polish expression (stored into a =std::tuple=) using a
    // *recursive* approach.
    //
    // *final node*
    //
    // Every object that does not inherit from =MetaExpr_Crtp= is
    // considered as a final node. The recursion is stopped.
    template <typename T>
    static inline std::enable_if_t<not Is_Crtp_Interface_Of<MetaExpr_Crtp, T>::value,
                                   std::tuple<const T&>>
    from_metaexpr_to_reverse_Polish_tuple(const T& t) noexcept
    {
      return {t};
    }

    // [DOC]
    //
    // *UnaryOP*
    //
    // Unary operators are expanded as =unary_op, arg=, where a
    // recursive call is performed from =arg=.
    //
    template <typename IMPL>
    static inline auto
    from_metaexpr_to_reverse_Polish_tuple(
        const MetaExpr_UnaryOp_Crtp<IMPL>& expression_tree) noexcept
    {
      return std::tuple_cat(std::make_tuple(typename IMPL::operator_type()),
                            from_metaexpr_to_reverse_Polish_tuple(expression_tree.arg()));
    }

    // [DOC]
    //
    // *BinaryOp*
    //
    // Binary operators are expanded as =binary_op, arg1, arg2=, where a
    // recursive call is performed from =arg1= then from =arg2=.
    //
    template <typename IMPL>
    static inline auto
    from_metaexpr_to_reverse_Polish_tuple(
        const MetaExpr_BinaryOp_Crtp<IMPL>& expression_tree) noexcept
    {
      return std::tuple_cat(std::make_tuple(typename IMPL::operator_type()),
                            from_metaexpr_to_reverse_Polish_tuple(expression_tree.arg_0()),
                            from_metaexpr_to_reverse_Polish_tuple(expression_tree.arg_1()));
    }
    // [END_from_metaexpr_to_reverse_Polish_tuple]

    // [BEGIN_call_assign_from_reverse_Polish]
    //
    // Given a reverse Polish expression stored in the =args_as_tuple=
    // argument, we extand all the arguments and call the =.impl()= method
    // to perform the final call to the *flat* =assign= function.
    //
    // *Note:* this is possible (calling =.impl()=) as everything
    //         (scalar, operator, vectors etc...) inherit from Crtp!
    //         And this was our motivation to do so (we have
    //         introduced XXX and XXX for this reason).
    template <typename DEST_IMPL, typename... ARGS>
    static inline auto
    call_assign_from_reverse_Polish(VMT_Crtp<DEST_IMPL>& dest,
                                    const std::tuple<ARGS...>& args_as_tuple)
    {
      return std::apply([&](const auto&... args) { return assign(dest.impl(), args.impl()...); },
                        args_as_tuple);
    }
    // [END_call_assign_from_reverse_Polish]

    // [BEGIN_call_assign_from_MetaExpr]
    //
    // This function is called to compute (lazy) Expression Template and
    // store the result into the =dest= argument.
    //
    template <typename DEST_IMPL, typename SRC_IMPL>
    static inline auto
    call_assign_from_MetaExpr(VMT_Crtp<DEST_IMPL>& dest, const MetaExpr_Crtp<SRC_IMPL>& metaExpr)
    {
      return call_assign_from_reverse_Polish(
          dest.impl(), from_metaexpr_to_reverse_Polish_tuple(metaExpr.impl()));
    }
    // [END_call_assign_from_MetaExpr]
  }  // namespace Detail
}  // namespace LinearAlgebra
