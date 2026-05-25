#include "StringGenerator.h"
#include <algorithm>
#include <chrono>

const std::string StringGenerator::ALPHABET = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789!@#%:;^&*()-";
const int StringGenerator::ALPHABET_SIZE = 74;

StringGenerator::StringGenerator(const unsigned int seed)
    : rng(seed),
      lengthDist(MIN_LENGTH, MAX_LENGTH),
      charDist(0, ALPHABET_SIZE - 1) {}

char StringGenerator::GetRandomChar() {
    return ALPHABET[charDist(rng)];
}

int StringGenerator::GetRandomLength() {
    return lengthDist(rng);
}

std::string StringGenerator::GenerateRandomString() {
    return GenerateRandomString(GetRandomLength());
}

std::string StringGenerator::GenerateRandomString(const int fixedLength) {
    std::string result;
    result.reserve(fixedLength);
    for (int i = 0; i < fixedLength; ++i) {
        result += GetRandomChar();
    }
    return result;
}

void StringGenerator::ShuffleArray(std::vector<std::string>& arr) {
    std::ranges::shuffle(arr, rng);
}

std::vector<std::string> StringGenerator::GenerateRandomArray(const int size) {
    std::vector<std::string> result;
    result.reserve(size);
    for (int i = 0; i < size; ++i) {
        result.push_back(GenerateRandomString());
    }
    return result;
}

std::vector<std::string> StringGenerator::GenerateSortedArray(const int size) {
    std::vector<std::string> result = GenerateRandomArray(size);
    std::ranges::sort(result);
    return result;
}

std::vector<std::string> StringGenerator::GenerateReversedArray(const int size) {
    std::vector<std::string> result = GenerateSortedArray(size);
    std::ranges::reverse(result);
    return result;
}

std::vector<std::string> StringGenerator::GenerateAlmostSortedArray(const int size, const double swapPercent) {
    std::vector<std::string> result = GenerateSortedArray(size);
    const int swapCount = std::max(1, static_cast<int>(size * swapPercent));
    std::uniform_int_distribution<int> posDist(0, size - 1);

    for (int i = 0; i < swapCount; ++i) {
        const int pos1 = posDist(rng);
        const int pos2 = posDist(rng);
        std::swap(result[pos1], result[pos2]);
    }
    return result;
}

std::vector<std::string> StringGenerator::GenerateSamePrefixArray(const int size, const std::string& prefix) {
    std::vector<std::string> result;
    result.reserve(size);
    const int prefixLen = static_cast<int>(prefix.length());

    for (int i = 0; i < size; ++i) {
        int suffixLen = GetRandomLength();
        if (prefixLen + suffixLen > MAX_LENGTH) {
            suffixLen = MAX_LENGTH - prefixLen;
            if (suffixLen < 0) suffixLen = 0;
        }
        result.push_back(prefix + GenerateRandomString(suffixLen));
    }
    return result;
}

std::vector<std::string> StringGenerator::GetSubarray(const std::vector<std::string>& source, const int size) {
    const int actualSize = std::min(size, static_cast<int>(source.size()));
    return std::vector<std::string>(source.begin(), source.begin() + actualSize);
}

int StringGenerator::GetMaxArraySize() {
    return MAX_ARRAY_SIZE;
}

void StringGenerator::ResetSeed(const unsigned int seed) {
    rng.seed(seed);
}