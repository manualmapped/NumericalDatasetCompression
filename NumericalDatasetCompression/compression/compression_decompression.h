#include "../dependencies/includes.h"

namespace compression_decompression
{
    std::string compress(std::vector<int>& dataset, std::unordered_map<std::string, std::vector<int>>& patterns) // Idk if you can tell yet, I love my &'s
    {
        std::string compressed_data;
        int i = 0;

        while (i < dataset.size()) {
            bool matched = false;

            // Try to match a longest possible pattern :pray:
            for (auto& pattern_pair : patterns) {
                auto& pattern = pattern_pair.second;
                if (i + pattern.size() <= dataset.size() &&
                    std::equal(pattern.begin(), pattern.end(), dataset.begin() + i)) {
                    compressed_data += pattern_pair.first + " ";
                    i += pattern.size();
                    matched = true;
                    break;
                }
            }

            if (!matched) {
                // :broken_heart: Didnt match it
                compressed_data += std::to_string(dataset[i]) + " ";
                i++;
            }
        }

        return compressed_data;
    }
    std::vector<int> decompress(std::string& compressed_data, std::unordered_map<std::string, std::vector<int>>& patterns)  // HashMAP!!!! O(1) time complexity. indeed indeed.
    {
        std::vector<int> decompressed_data;
        std::string token;

        for (char c : compressed_data) {
            if (c == ' ') {
                if (!token.empty()) {
                    if (patterns.find(token) != patterns.end()) {
                        // &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&& Who doesnt love &&&&&&&&&&&
                        // Expansion
                        auto& pattern = patterns[token];
                        decompressed_data.insert(decompressed_data.end(), pattern.begin(), pattern.end());
                    }
                    else {
                        // RAW NUMBER orrrrrrrr NO. Pattern! HOWEVER! that might be a ERROR! at that point
                        decompressed_data.push_back(std::stoi(token));
                        // does anyone use this function called stoi?? turns a string into integer.
                    }
                    token.clear();
                }
            }
            else {
                token += c;
            }
        }

        return decompressed_data;
    }
}