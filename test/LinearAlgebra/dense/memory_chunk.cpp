#include "LinearAlgebra/dense/memory_chunk.hpp"

#include <gtest/gtest.h>

using namespace LinearAlgebra;

TEST(Memory_Chunck, tag)
{
  struct A : Detail::Memory_Chunk_Tag
  {
  };
  struct B
  {
  };

  EXPECT_TRUE(Detail::Is_Memory_Chunk_v<A>);
  EXPECT_FALSE(Detail::Is_Memory_Chunk_v<B>);
  EXPECT_FALSE(Detail::Is_Memory_Chunk_v<int>);

  EXPECT_TRUE((Detail::Is_Memory_Chunk_v<
               Default_Memory_Chunk<int, std::integral_constant<std::size_t, 2>>>));
  EXPECT_TRUE((Detail::Is_Memory_Chunk_v<Default_Memory_Chunk<int, std::size_t>>));

   EXPECT_TRUE((Detail::Is_Memory_Chunk_v<
               View_Default_Memory_Chunk<int, std::integral_constant<std::size_t, 2>>>));
  EXPECT_TRUE((Detail::Is_Memory_Chunk_v<View_Default_Memory_Chunk<int, std::size_t>>));

   EXPECT_TRUE((Detail::Is_Memory_Chunk_v<
               Const_View_Default_Memory_Chunk<int, std::integral_constant<std::size_t, 2>>>));
  EXPECT_TRUE((Detail::Is_Memory_Chunk_v<Const_View_Default_Memory_Chunk<int, std::size_t>>));
}
