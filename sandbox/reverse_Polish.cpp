
#include "LinearAlgebra/expr/expr_tags.hpp"
#include "LinearAlgebra/matrix.hpp"

#include <tuple>
#include <type_traits>

namespace LinearAlgebra
{
  template <typename IMPL>
  std::string
  print_item(const Matrix_Crtp<IMPL>&)
  {
    return " M";
  }
  template <typename IMPL>
  std::string
  print_item(const Vector_Crtp<IMPL>&)
  {
    return " v";
  }
  std::string
  print_item(const _product_t_&)
  {
    return " *";
  }
  std::string
  print_item(const _plus_t_&)
  {
    return " +";
  }
    std::string
  print_item(const _unary_minus_t_&)
  {
    return " -";
  }
  // template<typename IMPL>
  // std::string print(const Matrix_Crtp<IMPL>&) {
  //   return "M";
  // }
  template <typename D, typename... T>
  void
  print(D& d, const T&... t)
  {
    // std::cout << __PRETTY_FUNCTION__ << std::endl;
    std::cout << print_item(d);
    ((std::cout << print_item(t)), ...);
    std::cout << std::endl;
  }

  //////////////////////////////////////////////////////////////////

  namespace Detail
  {
    // Everything that's not a Detail::MetaExpr_Crtp is considered as a
    // final node
    template <typename T>
    static inline std::enable_if_t<not Is_Crtp_Interface_Of<Detail::MetaExpr_Crtp, T>::value,
                                   std::tuple<const T&>>
    from_metaexpr_to_reverse_Polish_tuple(const T& t) noexcept
    {
      return {t};
    }

    // UnaryOP
    template <typename IMPL>
    static inline auto
    from_metaexpr_to_reverse_Polish_tuple(
        const Detail::MetaExpr_UnaryOp_Crtp<IMPL>& expression_tree) noexcept
    {
      return std::tuple_cat(std::make_tuple(typename IMPL::operator_type()),
                            from_metaexpr_to_reverse_Polish_tuple(expression_tree.arg()));
    }

    // BinaryOp
    template <typename IMPL>
    static inline auto
    from_metaexpr_to_reverse_Polish_tuple(
        const Detail::MetaExpr_BinaryOp_Crtp<IMPL>& expression_tree) noexcept
    {
      // // Attention: our convention is to not explicitly write down "_product_"
      // if constexpr (std::is_same_v<typename Detail::MetaExpr_BinaryOp_Crtp<IMPL>::operator_type,
      //                              _product_t_>)
      // {
      //   return std::tuple_cat(from_metaexpr_to_reverse_Polish_tuple(expression_tree.arg_0()),
      //                         from_metaexpr_to_reverse_Polish_tuple(expression_tree.arg_1()));
      // }
      // else
      // {
      //   return std::tuple_cat(from_metaexpr_to_reverse_Polish_tuple(expression_tree.arg_0()),
      //                         std::make_tuple(typename IMPL::operator_type()),
      //                         from_metaexpr_to_reverse_Polish_tuple(expression_tree.arg_1()));
      // }

      return std::tuple_cat(std::make_tuple(typename IMPL::operator_type()),
                            from_metaexpr_to_reverse_Polish_tuple(expression_tree.arg_0()),
                            from_metaexpr_to_reverse_Polish_tuple(expression_tree.arg_1()));
    }

    //////////////////////////////////////////////////////////////////
    // Functions to use in Vector/Matrix interface
    //////////////////////////////////////////////////////////////////
    //
    // -> we use VMT_Crtp to have a generic solution
    //
    template <typename DEST_IMPL, typename... ARGS>
    static inline auto
    call_assign_from_reverse_Polish(VMT_Crtp<DEST_IMPL>& dest,
                                    const std::tuple<ARGS...>& args_as_tuple)
    {
      // CAVEAT: not args.impl()... as args can be integer,double etc...
      return std::apply([&](const auto&... args) { return print(dest.impl(), args...); },
                        args_as_tuple);
    }

    template <typename DEST_IMPL, typename SRC_IMPL>
    static inline auto
    call_assign(VMT_Crtp<DEST_IMPL>& dest, const Detail::MetaExpr_Crtp<SRC_IMPL>& metaExpr)
    {
      return call_assign_from_reverse_Polish(
          dest.impl(), from_metaexpr_to_reverse_Polish_tuple(metaExpr.impl()));
    }
  }
}
using namespace LinearAlgebra;
int
main()
{
  Tiny_Matrix<int, 2, 2> M;

  call_assign(M, M * (M + M));
  call_assign(M, -(M + M) * M);

  return 0;
}
