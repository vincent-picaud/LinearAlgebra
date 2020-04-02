// A predicate that checks if two Memory_Chunks are (possibly) aliased
//
// Note: to avoid time consuming computation (arbitrary stride, mask
//       etc...) this is only a necessary condition:
//
//       if "are_not_aliased_p()" is TRUE then for sure they are NOT
//                                             aliased.
//
#pragma once

#include "LinearAlgebra/dense/matrix_crtp_fwd.hpp"
#include "LinearAlgebra/dense/memory_chunk.hpp"
#include "LinearAlgebra/dense/vector_crtp_fwd.hpp"

namespace LinearAlgebra
{
  template <typename MEM_CHUNK_0, typename MEM_CHUNK_1>
  std::enable_if_t<
      Detail::Is_Memory_Chunk_v<MEM_CHUNK_0> and Detail::Is_Memory_Chunk_v<MEM_CHUNK_1>, bool>
  are_not_aliased_p(const MEM_CHUNK_0& mem_chunk_0, const MEM_CHUNK_1& mem_chunk_1) noexcept
  {
    // The idea is to check if:
    // * mem_chunk_0 < mem_chunk_1 or
    // * mem_chunk_1 < mem_chunk_0 or
    //
    if constexpr (std::is_same_v<typename MEM_CHUNK_0::element_type,
                                 typename MEM_CHUNK_1::element_type>)
    {
      if (mem_chunk_0.data() + mem_chunk_0.capacity() < mem_chunk_1.data()) return true;
      if (mem_chunk_1.data() + mem_chunk_1.capacity() < mem_chunk_0.data()) return true;
      return false;
    }
    // 
    return true;
  }
  template <typename MEM_CHUNK_0, typename MEM_CHUNK_1>
  std::enable_if_t<
      Detail::Is_Memory_Chunk_v<MEM_CHUNK_0> and Detail::Is_Memory_Chunk_v<MEM_CHUNK_1>, bool>
  are_possibly_aliased_p(const MEM_CHUNK_0& mem_chunk_0, const MEM_CHUNK_1& mem_chunk_1) noexcept
  {
    return not are_not_aliased_p(mem_chunk_0, mem_chunk_1);
  }

  //////////////////////////////////////////////////////////////////
  // Dense Vector wrapper
  //////////////////////////////////////////////////////////////////
  //
  template <typename VECTOR_0, typename VECTOR_1>
  bool
  are_not_aliased_p(const Dense_Vector_Crtp<VECTOR_0>& vector_0,
                    const Dense_Vector_Crtp<VECTOR_1>& vector_1) noexcept
  {
    return are_not_aliased_p(vector_0.memory_chunk(), vector_1.memory_chunk());
  }
  template <typename VECTOR_0, typename VECTOR_1>
  bool
  are_possibly_aliased_p(const Dense_Vector_Crtp<VECTOR_0>& vector_0,
                         const Dense_Vector_Crtp<VECTOR_1>& vector_1) noexcept
  {
    return are_possibly_aliased_p(vector_0.memory_chunk(), vector_1.memory_chunk());
  }

  //////////////////////////////////////////////////////////////////
  // Dense Matrix wrapper
  //////////////////////////////////////////////////////////////////
  //
  template <typename MATRIX_0, typename MATRIX_1>
  bool
  are_not_aliased_p(const Dense_Matrix_Crtp<MATRIX_0>& matrix_0,
                    const Dense_Matrix_Crtp<MATRIX_1>& matrix_1) noexcept
  {
    return are_not_aliased_p(matrix_0.memory_chunk(), matrix_1.memory_chunk());
  }
  template <typename MATRIX_0, typename MATRIX_1>
  bool
  are_possibly_aliased_p(const Dense_Matrix_Crtp<MATRIX_0>& matrix_0,
                         const Dense_Matrix_Crtp<MATRIX_1>& matrix_1) noexcept
  {
    return are_possibly_aliased_p(matrix_0.memory_chunk(), matrix_1.memory_chunk());
  }

  //////////////////////////////////////////////////////////////////
  // Dense Matrix & Dense Vector (aliasing with row/col view)
  //////////////////////////////////////////////////////////////////
  //
  template <typename VECTOR_0, typename MATRIX_1>
  bool
  are_not_aliased_p(const Dense_Vector_Crtp<VECTOR_0>& vector_0,
                    const Dense_Matrix_Crtp<MATRIX_1>& matrix_1) noexcept
  {
    return are_not_aliased_p(vector_0.memory_chunk(), matrix_1.memory_chunk());
  }
  template <typename VECTOR_0, typename MATRIX_1>
  bool
  are_possibly_aliased_p(const Dense_Vector_Crtp<VECTOR_0>& vector_0,
                         const Dense_Matrix_Crtp<MATRIX_1>& matrix_1) noexcept
  {
    return are_possibly_aliased_p(vector_0.memory_chunk(), matrix_1.memory_chunk());
  }
  // reverse args order
  template <typename MATRIX_0, typename VECTOR_1>
  bool
  are_not_aliased_p(const Dense_Matrix_Crtp<MATRIX_0>& matrix_0,
                    const Dense_Vector_Crtp<VECTOR_1>& vector_1) noexcept
  {
    return are_not_aliased_p(matrix_0.memory_chunk(), vector_1.memory_chunk());
  }
  template <typename MATRIX_0, typename VECTOR_1>
  bool
  are_possibly_aliased_p(const Dense_Matrix_Crtp<MATRIX_0>& matrix_0,
                         const Dense_Vector_Crtp<VECTOR_1>& vector_1) noexcept
  {
    return are_possibly_aliased_p(matrix_0.memory_chunk(), vector_1.memory_chunk());
  }
}
