#pragma once

#include <cstdint>

namespace esphome::i2s_audio {

enum class DriverRetryDecision : uint8_t {
  RETRY_SOON,
  BACKOFF_ERROR,
};

constexpr DriverRetryDecision driver_retry_decision(bool transient_bus_busy, uint32_t busy_elapsed_ms) {
  return transient_bus_busy && busy_elapsed_ms < 1000U ? DriverRetryDecision::RETRY_SOON
                                                        : DriverRetryDecision::BACKOFF_ERROR;
}

constexpr bool driver_retry_due(uint32_t now_ms, uint32_t retry_at_ms) {
  return retry_at_ms == 0U || static_cast<int32_t>(now_ms - retry_at_ms) >= 0;
}

}  // namespace esphome::i2s_audio
