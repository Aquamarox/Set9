#ifndef UNTITLED_STRINGSORTTESTER_H
#define UNTITLED_STRINGSORTTESTER_H


#include <string>
#include <vector>

class StringSortTester {
private:
    struct StringWithLCP {
        std::string str;
        int lcp;
        StringWithLCP() : str(""), lcp(0) {}
        StringWithLCP(const std::string& s, const int l) : str(s), lcp(l) {}
    };
    static long long charComparisons;
    static const int ALPHABET_SIZE;
    static const std::string ALPHABET_STR;



    static bool CompareChars(char a, char b);
    static bool StringLess(const std::string& a, const std::string& b);
    static int Partition(std::vector<std::string>& a, int l, int r);
    static void QuickSortImpl(std::vector<std::string>& a, int l, int r);
    static void MergeSortImpl(std::vector<std::string>& arr, int left, int right);
    static void Merge(std::vector<std::string>& arr, int left, int mid, int right);
    static void StringQuickSortImpl(std::vector<std::string>& arr, int left, int right, int depth);
    static std::pair<int, int> LcpCompare(const std::string& A, const std::string& B, int k);
    static std::vector<StringWithLCP> StringMergeSortImpl(const std::vector<std::string>& arr);
    static void MSDRadixSortImpl(std::vector<std::string>& arr, std::vector<std::string>& buffer, int left, int right, int depth, bool useSwitch);
    static int CharAt(const std::string& s,  int depth);

public:
    static void ResetComparisons();

    static long long GetTimeMicroseconds();

    static void QuickSort(std::vector<std::string>& arr);

    static void MergeSort(std::vector<std::string>& arr);

    static void StringQuickSort(std::vector<std::string>& arr);

    static void StringMergeSort(std::vector<std::string>& arr);

    static void MSDRadixSort(std::vector<std::string>& arr);

    static void MSDRadixSortWithSwitch(std::vector<std::string>& arr);

    static long long GetCharComparisons();
};

#endif //UNTITLED_STRINGSORTTESTER_H
