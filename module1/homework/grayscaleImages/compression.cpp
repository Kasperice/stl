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
    int columnSize = 240;
    auto it = image.begin();

    for (auto& row : decompressed) {
        for (it; it != image.end();) {
            int count = std::count_if(image.begin(), image.end(),
                                      [sum{0}, columnSize](std::pair<uint8_t, uint8_t> el) mutable { 
                                          sum+=el.second; return sum <= columnSize; });
            auto secIt = it;
            std::advance(secIt, count);
            std::vector<uint8_t> rowVector;
            if (secIt != image.end())
                std::for_each(it, secIt, [&rowVector](auto el) { 
                                            for(auto i = 0; i <= el.second; i++) 
                                                rowVector.push_back(el.first); });
            it = secIt;
            std::copy(rowVector.begin(), rowVector.end(), row.begin());
        }
    }

    return decompressed;
}
