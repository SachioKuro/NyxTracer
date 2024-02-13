#pragma once

#include <cstdint>
#include <compare>

namespace Nyx {
    struct UID {
        uint64_t value;

        UID() : value(++next) {}

        UID(const UID& other) : value(other.value) {}

        UID& operator=(const UID& other) {
            value = other.value;
            return *this;
        }

        static void reset() {
            next = 0;
        }

        bool operator==(const UID& other) const {
            return value == other.value;
        }

        bool operator!=(const UID& other) const {
            return value != other.value;
        }

        std::strong_ordering operator<=>(const UID& other) const {
            return value <=> other.value;
        }
    private:
        static uint64_t next;
    };
}