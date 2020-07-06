#pragma once

#ifdef VMT_ASSIGNMENT_OPERATOR
#error "Maybe we are overloading something...."
#endif

// [BEGIN_vmt_assignment_operator_define]
#define VMT_ASSIGNMENT_OPERATOR(THIS_TYPE)                                               \
  /* Meta expression etc... */                                                           \
  template <typename OTHER_IMPL>                                                         \
  THIS_TYPE& operator=(const Crtp<OTHER_IMPL>& other)                                    \
  {                                                                                      \
    return this->impl_assign(other.impl());                                              \
  }                                                                                      \
                                                                                         \
  /* Scalar */                                                                           \
  THIS_TYPE& operator=(const element_type& scalar) { return this->impl_assign(scalar); } \
                                                                                         \
  /* Be sure that we have a deep copy semantic, even for view */                         \
  THIS_TYPE& operator=(const THIS_TYPE& other) { return this->impl().impl_assign(other); }
// [END_vmt_assignment_operator_define]

// [BEGIN_delete_vmt_assignment_operator_define]
// Better error messages
#define DELETE_VMT_ASSIGNMENT_OPERATOR(THIS_TYPE)                \
  /* Meta expression etc... */                                   \
  template <typename OTHER_IMPL>                                 \
  THIS_TYPE& operator=(const Crtp<OTHER_IMPL>& other) = delete;  \
  /* Scalar */                                                   \
  THIS_TYPE& operator=(const element_type& scalar) = delete;     \
  /* Be sure that we have a deep copy semantic, even for view */ \
  THIS_TYPE& operator=(const THIS_TYPE& other) = delete;
// [END_delete_vmt_assignment_operator_define]
