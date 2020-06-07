#include "compression.hpp"

#include <algorithm>
#include <utility>

std::vector<std::pair<uint8_t, uint8_t>> compressGrayscale(const std::array<std::array<uint8_t, 240>, 160>& image) {
    std::vector<std::pair<uint8_t, uint8_t>> compressed{};

    for (const auto& row : image) {
        for (auto it = row.begin(); it != row.end();) {
            auto findIt = std::adjacent_find(it, row.end(), std::not_equal_to<int>{});
            if (findIt != row.end()) {
                findIt++;
            }
            compressed.emplace_back(*it, std::distance(it, findIt));
            it = findIt;
        }
    }

    return compressed;
}

std::array<std::array<uint8_t, 240>, 160> decompressGrayscale(const std::vector<std::pair<uint8_t, uint8_t>>& image) {
    std::array<std::array<uint8_t, 240>, 160> decompressed{};
    int sum{};
    int columnSize = 240;

    for (auto& row : decompressed) {
        for (auto it = image.begin(); it != image.end();) {
            int count = std::count_if(image.begin(), image.end(),
                                      [&sum, columnSize](std::pair<uint8_t, uint8_t> el) { return (sum += el.second) != columnSize; });
            auto secIt = it;
            sum = 0;
            std::vector<uint8_t> rowVector(240);
            std::advance(secIt, count);
            std::for_each(it, secIt, [&rowVector](std::pair<uint8_t, uint8_t> el) { for(auto i = el.second; i <= el.second; i++) 
                                                                                        rowVector.push_back(el.first); });
            it = secIt;
            std::copy(rowVector.begin(), rowVector.end(), row.begin());
        }
    }

    return decompressed;
}
