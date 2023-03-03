#include "UUID.hpp"

uuid64 GenerateUUID() {
	static uuid64 uuid = 0;
	return ++uuid;
}