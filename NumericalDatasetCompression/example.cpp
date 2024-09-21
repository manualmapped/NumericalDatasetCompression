#pragma once
#include "compression/compression_decompression.h"
#include "dependencies/pattern.h"
#include <chrono>
#include <iomanip>
// btw, iomanip is for really small numbers (in my case 4.7e-06), i wanna control the precision on output! and also not print in standard form

// @manualmapped / styles // (I tried to comment alot and explain as much as I can, not the most noob-friendly code though.

// Note: On small datasets (5/10 elements inside the list, this would be less efficient than normal iteration, however, on extremely large datasets, or even just big datasets, its more efficient
// Advantages:
/*
    -> Less Storage space (datasets with a lot of numbers which may need to be saved have a bigger train on memory/storage, this decreases it alot by tokenising alot of the numbers)
     -> Means less of a iteration speed
*/
// Cons:
/*
    -> When compressing, it could be a longer process than when decompressing, due to having to iterate through a dataset possibly more than once
*/
// Would I use this? In certain circumstances when needed, yes
// My use for it: Storing data about the localplayer en-masse for my game cheat (For a specific feature where it could take up about 1-3gb of storage WITHOUT the compression)
// ^ and with the compression it can shrink it so far down it may just go into the MB's :')
// Also used hashmaps(unordered_map)s with o(1) time complexity compared to a binary tree! (map) o(log(n)).

std::chrono::high_resolution_clock::time_point gettime() {
    return std::chrono::high_resolution_clock::now();
}

float deltatime(std::chrono::high_resolution_clock::time_point& lastTime) {
    auto currentTime = gettime();
    std::chrono::duration<float> deltaTime = currentTime - lastTime;
    lastTime = currentTime;
    return deltaTime.count();
}

int main()
{
    // Example

    std::vector<int> dataset = { 1, 2, 93, 29, 123, 43, 1, 2, 93, 29, 123, 43, 1, 2, 3, 430, 10, 1, 2, 93 }; // repeating some on purpose to show a demonstration in a relatively small dataset

    // get patterns
    auto patterns = pattern::extract_patterns(dataset);

    // display/print patterns
    std::cout << "patterns:\n";
    for (auto& p : patterns) {
        std::cout << p.first << ": { ";
        for (int n : p.second) {
            std::cout << n << " ";
        }
        std::cout << "}\n";
    }

    // compress data$et
    std::string compressed_data = compression_decompression::compress(dataset, patterns);
    std::cout << "\nCompressed Data: " << compressed_data << std::endl;


    auto start = gettime();
    // try decompress
    auto decompressed_data = compression_decompression::decompress(compressed_data, patterns);

    auto end = deltatime(start);

    std::cout << "Decompression (before std::cout, raw decompression) took: " << std::fixed << std::setprecision(16) << end << " seconds!!";

    std::cout << "\nDecompressed Data: ";
    for (int num : decompressed_data) {
        std::cout << num << " ";
    }
    std::cout << std::endl;



    system("pause"); // NO i didnt use std::cin.

    return 0;
}