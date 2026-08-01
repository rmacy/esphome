#pragma once

#include <cstdint>

namespace esphome::api {

// Nova is a LAN voice appliance: a multi-minute half-open API connection is
// more damaging than an occasional reconnect. Five-second probes preserve
// ample LAN jitter tolerance while bounding half-open eviction to 12.5s.
constexpr uint32_t API_KEEPALIVE_TIMEOUT_MS = 5000U;
constexpr uint32_t API_KEEPALIVE_DISCONNECT_TIMEOUT_MS = (API_KEEPALIVE_TIMEOUT_MS * 5U) / 2U;

constexpr bool should_check_api_keepalive(uint32_t elapsed_ms, uint32_t timeout_ms = API_KEEPALIVE_TIMEOUT_MS) {
  return elapsed_ms > timeout_ms;
}

constexpr bool should_disconnect_api_keepalive(bool sent_ping, uint32_t elapsed_ms,
                                               uint32_t disconnect_timeout_ms = API_KEEPALIVE_DISCONNECT_TIMEOUT_MS) {
  return sent_ping && elapsed_ms > disconnect_timeout_ms;
}

constexpr bool should_send_api_keepalive(bool sent_ping, bool marked_for_removal) {
  return !sent_ping && !marked_for_removal;
}

}  // namespace esphome::api
