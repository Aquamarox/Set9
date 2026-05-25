#ifndef UNTITLED_STRINGGENERATOR_H
#define UNTITLED_STRINGGENERATOR_H

#include <chrono>
#include <string>
#include <vector>
#include <random>

class StringGenerator {
private:
    static constexpr int MIN_LENGTH = 10;
    static constexpr int MAX_LENGTH = 200;
    static constexpr int MAX_ARRAY_SIZE = 3000;
    static const std::string ALPHABET;
    static const int ALPHABET_SIZE;

    std::mt19937 rng;
    std::uniform_int_distribution<int> lengthDist;
    std::uniform_int_distribution<int> charDist;

    char GetRandomChar();
    int GetRandomLength();
    std::string GenerateRandomString();
    std::string GenerateRandomString(int fixedLength);
    void ShuffleArray(std::vector<std::string>& arr);

public:
    explicit StringGenerator(unsigned int seed = std::chrono::steady_clock::now().time_since_epoch().count());

    std::vector<std::string> GenerateRandomArray(int size);
    std::vector<std::string> GenerateSortedArray(int size);
    std::vector<std::string> GenerateReversedArray(int size);
    std::vector<std::string> GenerateAlmostSortedArray(int size, double swapPercent = 0.05);
    std::vector<std::string> GenerateSamePrefixArray(int size, const std::string& prefix);

    static std::vector<std::string> GetSubarray(const std::vector<std::string>& source, int size);
    [[nodiscard]] static int GetMaxArraySize();
    void ResetSeed(unsigned int seed);

};

#endif //UNTITLED_STRINGGENERATOR_H