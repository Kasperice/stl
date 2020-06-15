#include "compression.hpp"

#include <algorithm>
#include <utility>

std::vector<std::pair<uint8_t, uint8_t>> compressGrayscale(const std::array<std::array<uint8_t, width>, height>& image) {
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

std::array<std::array<uint8_t, width>, height> decompressGrayscale(const std::vector<std::pair<uint8_t, uint8_t>>& image) {
    std::array<std::array<uint8_t, width>, height> decompressed{};
    int columnSize = width;
    //TODO Change iterator names
    auto it = image.begin();

    for (auto& row : decompressed) {
        while (it != image.end()) {
            int count = std::count_if(it, image.end(),
                                      [sum{0}, columnSize](const auto& el) mutable { 
                                          sum+=el.second; return sum <= columnSize; });
            count;
            auto secIt = it;
            std::vector<uint8_t> rowVector;
            //TODO Fix everything below this line as it's not filling decompressed array properly
            std::advance(secIt, count);
            std::for_each(it, secIt, [&rowVector](const auto& el) { 
                                        for(auto i = 0; i < el.second; i++) 
                                            rowVector.push_back(el.first); });
            it = secIt;
            std::copy(rowVector.begin(), rowVector.end(), row.begin());
        }
    }

    return decompressed;
}
