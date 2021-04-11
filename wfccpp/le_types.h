#pragma once
#include <memory>

/*
	Since the transmitted endianess differs from our target device, we need to swap it.
*/

class le_u32 {
private:
	uint8_t data[4];

public:
	operator uint32_t const& () const {
		return data[0] << 24 | data[1] << 16 | data[2] << 8 | data[3];
	}

	le_u32 & operator=(const uint32_t other) {
		data[3] = other & 0xff;
		data[2] = (other >> 8) & 0xff;
		data[1] = (other >> 16) & 0xff;
		data[0] = (other >> 24) & 0xff;

		return *this;
	}
};