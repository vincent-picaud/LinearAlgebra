// Call assign from metaexpr
//
#pragma once

#include "LinearAlgebra/dense/matrix_crtp_fwd.hpp"
#include "LinearAlgebra/dense/vector_crtp_fwd.hpp"
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
    inline constexpr std::enable_if_t<not Is_Crtp_Interface_Of<Detail::MetaExpr_Crtp, T>::value,
                                      std::tuple<const T&>>
    from_metaexpr_to_argument_tuple(const T& t) noexcept
    {
      return {t};
    }

    // TODO add Unary op
    template <typename IMPL>
    inline constexpr auto
    from_metaexpr_to_argument_tuple(
        const Detail::MetaExpr_BinaryOp_Crtp<IMPL>& expression_tree) noexcept
    {
      // Attention: our convention is to not explicitly write down "_product_"
      if constexpr (std::is_same_v<typename Detail::MetaExpr_BinaryOp_Crtp<IMPL>::operator_type,
                                   _product_t_>)
      {
        return std::tuple_cat(from_metaexpr_to_argument_tuple(expression_tree.arg_0()),
                              from_metaexpr_to_argument_tuple(expression_tree.arg_1()));
      }
      else
      {
        return std::tuple_cat(from_metaexpr_to_argument_tuple(expression_tree.arg_0()),
                              std::make_tuple(typename IMPL::operator_type()),
                              from_metaexpr_to_argument_tuple(expression_tree.arg_1()));
      }
    }

    //////////////////////////////////////////////////////////////////
    // Functions to use in Vector/Matrix interface
    //////////////////////////////////////////////////////////////////
    //

    // Vector
    //
    template <typename M_DEST_IMPL, typename... ARGS>
    auto
    call_assign_from_argument_tuple(Vector_Crtp<M_DEST_IMPL>& M_dest,
                                    const std::tuple<ARGS...>& args_as_tuple)
    {
      return std::apply([&](const auto&... args) { return assign(M_dest, args...); },
                        args_as_tuple);
    }

    template <typename M_DEST_IMPL, typename SRC_IMPL>
    auto
    call_assign_from_metaexpr(Vector_Crtp<M_DEST_IMPL>& M_dest,
                              const Detail::MetaExpr_Crtp<SRC_IMPL>& metaExpr)
    {
      call_assign_from_argument_tuple(M_dest, from_metaexpr_to_argument_tuple(metaExpr.impl()));
    }

    // Matrix
    //
    template <typename M_DEST_IMPL, typename... ARGS>
    auto
    call_assign_from_argument_tuple(Matrix_Crtp<M_DEST_IMPL>& M_dest,
                                    const std::tuple<ARGS...>& args_as_tuple)
    {
      return std::apply([&](const auto&... args) { return assign(M_dest, args...); },
                        args_as_tuple);
    }

    template <typename M_DEST_IMPL, typename SRC_IMPL>
    auto
    call_assign_from_metaexpr(Matrix_Crtp<M_DEST_IMPL>& M_dest,
                              const Detail::MetaExpr_Crtp<SRC_IMPL>& metaExpr)
    {
      call_assign_from_argument_tuple(M_dest, from_metaexpr_to_argument_tuple(metaExpr.impl()));
    }
  }
}
