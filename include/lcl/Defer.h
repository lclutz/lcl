#pragma once

#include <utility>

// Use defer(someFunction()); to queue up cleanup functions to be run at the
// end of the scope. Note that this implementation is semantically different
// from implementations if other languages e.g. Go where deferred functions
// are ran at the end of the function instead of the end of the scope.

#define CONCAT0(a, b) a##b
#define CONCAT(a, b) CONCAT0(a, b)
#define defer(body) lcl::Defer CONCAT(defer, __LINE__)([&]() { body; })

namespace lcl
{

//! @brief Runs a user provided cleanup function at the end of the enclosing scope
//! @tparam CleanupFunctionT Type of cleanup function to run
template <typename CleanupFunctionT> class Defer final
{
  public:
    explicit Defer(CleanupFunctionT cleanupFunction)
        : m_cleanupFunction(std::move(cleanupFunction))
    {
    }

    Defer(Defer const &) = delete;
    Defer(Defer &&) noexcept = delete;

    ~Defer()
    {
        m_cleanupFunction();
    }

    Defer &operator=(Defer const &) = delete;
    Defer &operator=(Defer &&) noexcept = delete;

  private:
    CleanupFunctionT m_cleanupFunction;
};

} // namespace lcl
