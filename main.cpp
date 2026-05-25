#include <fstream>
#include <iostream>
#include <vector>

#include "StringGenerator.h"
#include "StringSortTester.h"

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    StringGenerator generator;

    const vector<string> algorithms = {
        "QuickSort",
        "MergeSort",
        "StringQuickSort",
        "StringMergeSort",
        "MSDRadixSort",
        "MSDRadixSortWithSwitch"
    };

    ofstream file("results.csv");

    file << "algorithm,array_type,size,time_us,char_comparisons\n";

    const vector<string> randomBase =
        generator.GenerateRandomArray(
            StringGenerator::GetMaxArraySize()
        );

    const vector<string> reversedBase =
        generator.GenerateReversedArray(
            StringGenerator::GetMaxArraySize()
        );

    const vector<string> almostBase =
        generator.GenerateAlmostSortedArray(
            StringGenerator::GetMaxArraySize()
        );

    for (int size = 100; size <= 3000; size += 100) {
        const vector<pair<string, vector<string>>> datasets = {
            {
                "random",
                StringGenerator::GetSubarray(randomBase, size)
            },
            {
                "reversed",
                StringGenerator::GetSubarray(reversedBase, size)
            },
            {
                "almost_sorted",
                StringGenerator::GetSubarray(almostBase, size)
            }
        };

        for (const auto& [type, data] : datasets) {

            for (const string& algorithm : algorithms) {

                long long totalTime = 0;
                long long totalComparisons = 0;

                constexpr int repeats = 10;

                for (int run = 0; run < repeats; ++run) {

                    vector<string> arr = data;

                    StringSortTester::ResetComparisons();

                    const long long start =
                        StringSortTester::GetTimeMicroseconds();

                    if (algorithm == "QuickSort") {
                        StringSortTester::QuickSort(arr);
                    }

                    if (algorithm == "MergeSort") {
                        StringSortTester::MergeSort(arr);
                    }

                    if (algorithm == "StringQuickSort") {
                        StringSortTester::StringQuickSort(arr);
                    }

                    if (algorithm == "StringMergeSort") {
                        StringSortTester::StringMergeSort(arr);
                    }

                    if (algorithm == "MSDRadixSort") {
                        StringSortTester::MSDRadixSort(arr);
                    }

                    if (algorithm == "MSDRadixSortWithSwitch") {
                        StringSortTester::MSDRadixSortWithSwitch(arr);
                    }

                    const long long finish =
                        StringSortTester::GetTimeMicroseconds();

                    totalTime += finish - start;

                    totalComparisons +=
                        StringSortTester::GetCharComparisons();
                }

                file
                    << algorithm << ','
                    << type << ','
                    << size << ','
                    << totalTime / repeats << ','
                    << totalComparisons / repeats
                    << '\n';
            }
        }
    }

    file.close();

    return 0;
}