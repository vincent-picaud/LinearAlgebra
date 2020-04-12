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

TEST(Memory_Chunck, move_dynamic)
{
  //
  // Dynamic Memory Chunk Move Operation
  //
  // ... as the underlying type is a std::vector, a true move operation copy is
  // performed
  //
  // -> we must check that the moved object remains in a consistent
  // -> state null data ptr WITH null size
  //
  Default_Memory_Chunk<double, std::size_t> mem{10};

  EXPECT_EQ(mem.capacity(), 10);
  EXPECT_TRUE(mem.data() != nullptr);

  auto p_mem = mem.data();

  auto mem2(std::move(mem));

  EXPECT_EQ(mem2.capacity(), 10);
  EXPECT_TRUE(mem2.data() == p_mem);

  EXPECT_EQ(mem.capacity(), 0);
  EXPECT_TRUE(mem.data() == nullptr);
}

TEST(Memory_Chunck, move_static)
{
  //
  // Static Memory Chunk Move Operation...
  //
  // ... as the underlying type is a std::array, a deep copy is
  // performed
  //
  Default_Memory_Chunk<double, std::integral_constant<std::size_t, 10>> mem{
      std::integral_constant<std::size_t, 10>()};

  EXPECT_EQ(mem.capacity(), 10);
  EXPECT_TRUE(mem.data() != nullptr);

  auto p_mem = mem.data();

  auto mem2(std::move(mem));

  EXPECT_EQ(mem2.capacity(), 10);
  EXPECT_FALSE(mem2.data() == p_mem);  // <- ! dynamic
  EXPECT_EQ(mem.capacity(), 10);       // <- ! dynamic
  EXPECT_TRUE(mem.data() == p_mem);    // <- ! dynamic
}
