#pragma once
#include <cstdint>

class util
{
public:
    util() = delete;
    
    auto static pack_into_32_bit_integer(const uint8_t a, const uint8_t b=0, const uint8_t c=0, const uint8_t d=0)-> uint32_t //lsb to msb
    {
        uint32_t packed = 0;
        packed  |=    (a & 0xff);
        packed  |=    ((b & 0xff)<<8);
        packed  |=    ((c & 0xff)<<16);
        packed  |=    ((d & 0xff)<<24);
        return packed;
    }

    auto static extract_from_32_bit_integer(const uint32_t packed, const uint8_t byte_num)-> uint8_t
    {
       return ((packed >> byte_num * 8)& 0xff); 
    }
    
};
