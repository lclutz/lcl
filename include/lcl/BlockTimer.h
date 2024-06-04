#pragma once

#include <functional>
#include <utility>

namespace lcl
{

//! @brief Calls a user provided callback at the end of the scope with the time elapsed in ms
//! @tparam ClockT Clock type to use for time measurement
template <typename ClockT> class BlockTimer final
{
  public:
    using StopFunction = std::function<void(typename ClockT::duration const &)>;

    explicit BlockTimer(StopFunction stopFunction)
        : m_stopFunction(std::move(stopFunction))
    {
    }

    BlockTimer(BlockTimer const &) = delete;
    BlockTimer(BlockTimer &&) noexcept = delete;

    ~BlockTimer()
    {
        m_stopFunction(ClockT::now() - m_startTime);
    }

    BlockTimer &operator=(BlockTimer const &) = delete;
    BlockTimer &operator=(BlockTimer &&) noexcept = delete;

  private:
    StopFunction m_stopFunction;
    typename ClockT::time_point const m_startTime = ClockT::now();
};

} // namespace lcl
