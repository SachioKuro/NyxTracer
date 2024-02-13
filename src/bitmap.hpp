#pragma once

#include <cstdint>
#include <fstream>

#include "color.hpp"
#include "config.hpp"

namespace Nyx::Image {
    struct __attribute__((packed)) BitmapHeader {
        char signature[2] = {'B', 'M'};
        uint32_t fileSize = 54 + 3 * WIDTH * HEIGHT;
        uint32_t reserved = 0;
        uint32_t dataOffset = 54;
    } bmpHeader;

    struct __attribute__((packed)) BitmapInfoHeader {
        uint32_t size = 40;
        int32_t width = WIDTH;
        int32_t height = HEIGHT;
        uint16_t planes = 1;
        uint16_t colorDepth = 24;
        uint32_t compression = 0;
        uint32_t imageSize = 3 * WIDTH * HEIGHT;
        int32_t xPixelsPerMeter = 3780;
        int32_t yPixelsPerMeter = 3780;
        uint32_t colorTableEntries = 0;
        uint32_t importantColors = 0;
    } bmpInfoHeader;

    void write_bitmap(const char* filename, const Color* pixels) {
        std::ofstream file(filename, std::ios::binary);

        file.write(reinterpret_cast<char*>(&bmpHeader), 14);
        file.write(reinterpret_cast<char*>(&bmpInfoHeader), 40);

        for (int j = HEIGHT - 1; j >= 0; --j) {
            for (int i = 0; i < WIDTH; ++i) {
                ByteColor byteColor = pixels[i + j * WIDTH].to_byte();
                ByteColor bgrByteColor = {byteColor.b, byteColor.g, byteColor.r};
                file.write(reinterpret_cast<char*>(&bgrByteColor), 3);
            }
        }

        file.close();
    }
}