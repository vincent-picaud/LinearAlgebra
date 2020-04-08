// Call assign from metaexpr
//
#pragma once

#include "LinearAlgebra/dense/vmt_crtp_fwd.hpp"
#include "LinearAlgebra/expr/expr_tags.hpp"
#include "LinearAlgebra/metaexpr/metaexpr_crtp_fwd.hpp"
#include "LinearAlgebra/utils/crtp.hpp"

#include <tuple>
#include <type_traits>

namespace LinearAlgebra
{
  namespace Detail
  {
    //////////////////////////////////////////////////////////////////

    // Everything that's not a Detail::MetaExpr_Crtp is considered as a
    // final node
    template <typename T>
    static inline std::enable_if_t<not Is_Crtp_Interface_Of<Detail::MetaExpr_Crtp, T>::value,
                                   std::tuple<const T&>>
    from_metaexpr_to_argument_tuple(const T& t) noexcept
    {
      return {t};
    }

    // UnaryOP
    template <typename IMPL>
    static inline auto
    from_metaexpr_to_argument_tuple(
        const Detail::MetaExpr_UnaryOp_Crtp<IMPL>& expression_tree) noexcept
    {
      return std::tuple_cat(std::make_tuple(typename IMPL::operator_type()),
                            from_metaexpr_to_argument_tuple(expression_tree.arg()));
    }

    // BinaryOp
    template <typename IMPL>
    static inline auto
    from_metaexpr_to_argument_tuple(
        const Detail::MetaExpr_BinaryOp_Crtp<IMPL>& expression_tree) noexcept
    {
      return std::tuple_cat(std::make_tuple(typename IMPL::operator_type()),
                            from_metaexpr_to_argument_tuple(expression_tree.arg_0()),
                            from_metaexpr_to_argument_tuple(expression_tree.arg_1()));
    }

    //////////////////////////////////////////////////////////////////
    // Functions to use in Vector/Matrix interface
    //////////////////////////////////////////////////////////////////
    //
    // -> we use VMT_Crtp to have a generic solution
    //
    template <typename DEST_IMPL, typename... ARGS>
    static inline auto
    call_assign_from_argument_tuple(VMT_Crtp<DEST_IMPL>& dest,
                                    const std::tuple<ARGS...>& args_as_tuple)
    {
      // CAVEAT: not args.impl()... as args can be integer,double etc...
      return std::apply([&](const auto&... args) { return assign(dest.impl(), args...); },
                        args_as_tuple);
    }

    template <typename DEST_IMPL, typename SRC_IMPL>
    static inline auto
    call_assign_from_metaexpr(VMT_Crtp<DEST_IMPL>& dest,
                              const Detail::MetaExpr_Crtp<SRC_IMPL>& metaExpr)
    {
      return call_assign_from_argument_tuple(dest.impl(),
                                             from_metaexpr_to_argument_tuple(metaExpr.impl()));
    }
  }
}
