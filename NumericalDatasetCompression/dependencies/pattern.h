#include "includes.h"

namespace pattern
{
	std::string patternid(int index) // This generates a new pattern id which follows a system for the compression 
    { 
        std::string id;

        // ln10 : A-Z, ln11: a-z (lower) ln12: 0-9
        if (index < 26) return std::string(1, 'A' + index);
        if (index < 52) return std::string(1, 'a' + (index - 26));
        if (index < 62) return std::string(1, '0' + (index - 52)); 

        index -= 62;
        while (index >= 0) 
        {
            id = char('A' + (index % 26)) + id;
            index = index / 26 - 1;
        }
        return id;
	}

    std::unordered_map<std::string, std::vector<int>> extract_patterns(std::vector<int>& dataset) {
        std::unordered_map<std::string, std::vector<int>> pattern_map;
        std::set<std::vector<int>> found_patterns;
        int pattern_id = 0;

        // range window, window, whatever you want to call it, linear way of finding patterns, probably not the most optimised, ill probably update it ;')
        // (this is painful to look at, lol)
        for (int window_size = 2; window_size <= dataset.size() / 2; ++window_size) 
        {
            for (int i = 0; i <= dataset.size() - window_size; ++i) 
            {
                std::vector<int> candidate(dataset.begin() + i, dataset.begin() + i + window_size);

                for (int j = i + window_size; j <= dataset.size() - window_size; ++j) 
                {
                    if (std::equal(candidate.begin(), candidate.end(), dataset.begin() + j))
                    {
                        if (found_patterns.find(candidate) == found_patterns.end())
                        {
                            std::string pattern_id_str = patternid(pattern_id++);
                            pattern_map[pattern_id_str] = candidate;
                            found_patterns.insert(candidate);
                        }
                    }
                }
            }
        }

        return pattern_map;
    }
}