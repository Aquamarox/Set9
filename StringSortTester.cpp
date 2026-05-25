#include "StringSortTester.h"
#include <algorithm>
#include <chrono>
#include <random>

long long StringSortTester::charComparisons = 0;
const int StringSortTester::ALPHABET_SIZE = 74;
const std::string StringSortTester::ALPHABET_STR = "!#%&()*-0123456789:;@ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";

bool StringSortTester::CompareChars(const char a, const char b) {
    ++charComparisons;
    return a == b;
}

void StringSortTester::ResetComparisons() {
    charComparisons = 0;
}

long long StringSortTester::GetCharComparisons() {
    return charComparisons;
}

long long StringSortTester::GetTimeMicroseconds() {
    const auto now = std::chrono::high_resolution_clock::now();
    return std::chrono::duration_cast<std::chrono::microseconds>(now.time_since_epoch()).count();
}

bool StringSortTester::StringLess(const std::string& a, const std::string& b) {
    const size_t minLen = std::min(a.length(), b.length());
    for (size_t i = 0; i < minLen; ++i) {
        CompareChars(a[i], b[i]);
        if (a[i] != b[i]) {
            return a[i] < b[i];
        }
    }
    CompareChars('\0', '\0');
    return a.length() < b.length();
}

// ==================== QuickSort ====================

int StringSortTester::Partition(std::vector<std::string>& a, const int l, const int r) {
    const std::string v = a[(l + r) / 2];
    int i = l;
    int j = r;

    while (i <= j) {
        while (StringLess(a[i], v)) {
            ++i;
        }
        while (StringLess(v, a[j])) {
            --j;
        }
        if (i >= j) {
            break;
        }
        std::swap(a[i++], a[j--]);
    }
    return j;
}

void StringSortTester::QuickSortImpl(std::vector<std::string>& a, const int l, const int r) {
    if (l < r) {
        const int q = Partition(a, l, r);
        QuickSortImpl(a, l, q);
        QuickSortImpl(a, q + 1, r);
    }
}

void StringSortTester::QuickSort(std::vector<std::string>& arr) {
    if (arr.empty()) {
        return;
    }
    ResetComparisons();
    QuickSortImpl(arr, 0, static_cast<int>(arr.size()) - 1);
}

// ==================== MergeSort ====================
void StringSortTester::Merge(std::vector<std::string>& arr, const int left, const int mid, const int right) {
    const int n1 = mid - left + 1;
    const int n2 = right - mid;

    std::vector<std::string> L(n1);
    std::vector<std::string> R(n2);

    for (int i = 0; i < n1; ++i) {
        L[i] = arr[left + i];
    }
    for (int j = 0; j < n2; ++j) {
        R[j] = arr[mid + 1 + j];
    }

    int i = 0;
    int j = 0;
    int k = left;

    while (i < n1 && j < n2) {
        if (StringLess(L[i], R[j])) {
            arr[k] = L[i];
            ++i;
        } else {
            arr[k] = R[j];
            ++j;
        }
        ++k;
    }

    while (i < n1) {
        arr[k] = L[i];
        ++i;
        ++k;
    }

    while (j < n2) {
        arr[k] = R[j];
        ++j;
        ++k;
    }
}

void StringSortTester::MergeSortImpl(std::vector<std::string>& arr, const int left, const int right) {
    if (left < right) {
        const int mid = left + (right - left) / 2;
        MergeSortImpl(arr, left, mid);
        MergeSortImpl(arr, mid + 1, right);
        Merge(arr, left, mid, right);
    }
}

void StringSortTester::MergeSort(std::vector<std::string>& arr) {
    if (arr.empty()) {
        return;
    }
    ResetComparisons();
    MergeSortImpl(arr, 0, static_cast<int>(arr.size()) - 1);
}

// ==================== StringQuickSort ====================

void StringSortTester::StringQuickSortImpl(std::vector<std::string>& arr, const int left, const int right, const int depth) {
    if (left >= right) {
        return;
    }

    const int mid = left + (right - left) / 2;
    if (StringLess(arr[mid], arr[left])) {
        std::swap(arr[left], arr[mid]);
    }
    if (StringLess(arr[right], arr[left])) {
        std::swap(arr[left], arr[right]);
    }
    if (StringLess(arr[mid], arr[right])) {
        std::swap(arr[mid], arr[right]);
    }

    char pivot;
    if (static_cast<size_t>(depth) < arr[right].length()) {
        pivot = arr[right][depth];
    } else {
        pivot = '\0';
    }

    int less = left;
    int greater = right;
    int i = left;

    while (i <= greater) {
        char current;
        if (static_cast<size_t>(depth) < arr[i].length()) {
            current = arr[i][depth];
        } else {
            current = '\0';
        }

        CompareChars(current, pivot);

        if (current < pivot || (current == '\0' && pivot != '\0')) {
            std::swap(arr[less], arr[i]);
            ++less;
            ++i;
        } else if (current > pivot || (current != '\0' && pivot == '\0')) {
            std::swap(arr[i], arr[greater]);
            --greater;
        } else {
            ++i;
        }
    }

    StringQuickSortImpl(arr, left, less - 1, depth);

    if (pivot != '\0') {
        StringQuickSortImpl(arr, less, greater, depth + 1);
    }

    StringQuickSortImpl(arr, greater + 1, right, depth);
}

void StringSortTester::StringQuickSort(std::vector<std::string>& arr) {
    if (arr.empty()) {
        return;
    }
    ResetComparisons();
    StringQuickSortImpl(arr, 0, static_cast<int>(arr.size()) - 1, 0);
}

// ==================== StringMergeSort ====================

std::pair<int, int> StringSortTester::LcpCompare(const std::string& A, const std::string& B, const int k) {
    const int minLen = std::min(static_cast<int>(A.length()), static_cast<int>(B.length()));
    int lcp = k;

    while (lcp < minLen && CompareChars(A[lcp], B[lcp])) {
        ++lcp;
    }


    if (lcp == minLen) {
        CompareChars('\0', '\0');
        if (A.length() == B.length()) {
            return {0, lcp};
        }
        if (A.length() < B.length()) {
            return {-1, lcp};
        }
        return {1, lcp};
    }

    return {A[lcp] < B[lcp] ? -1 : 1, lcp };
}

std::vector<StringSortTester::StringWithLCP> StringSortTester::StringMergeSortImpl(const std::vector<std::string>& arr) {
    const int n = static_cast<int>(arr.size());

    if (n == 1) {
        return {StringWithLCP(arr[0], 0)};
    }

    const int m = n / 2;
    const std::vector<std::string> leftHalf(arr.begin(), arr.begin() + m);
    const std::vector<std::string> rightHalf(arr.begin() + m, arr.end());

    std::vector<StringWithLCP> P = StringMergeSortImpl(leftHalf);
    std::vector<StringWithLCP> Q = StringMergeSortImpl(rightHalf);

    const int pSize = static_cast<int>(P.size());
    const int qSize = static_cast<int>(Q.size());

    std::vector<StringWithLCP> R;
    R.reserve(pSize + qSize);

    int i = 0;
    int j = 0;
    std::vector<int> p_lcp(pSize);
    std::vector<int> q_lcp(qSize);

    for (int t = 0; t < pSize; ++t) {
        p_lcp[t] = P[t].lcp;
    }
    for (int t = 0; t < qSize; ++t) {
        q_lcp[t] = Q[t].lcp;
    }

    while (i < pSize && j < qSize) {
        const int p_i = p_lcp[i];
        const int q_j = q_lcp[j];

        if (p_i > q_j) {
            R.emplace_back(P[i].str, p_i);
            ++i;
        } else if (p_i < q_j) {
            R.emplace_back(Q[j].str, q_j);
            ++j;
        } else {
            const auto [cmp, lcp] = LcpCompare(P[i].str, Q[j].str, p_i);

            if (cmp == -1) {
                R.emplace_back(P[i].str, p_i);
                q_lcp[j] = lcp;
                ++i;
            } else {
                R.emplace_back(Q[j].str, q_j);
                p_lcp[i] = lcp;
                ++j;
            }
        }
    }

    while (i < pSize) {
        R.emplace_back(P[i].str, p_lcp[i]);
        ++i;
    }
    while (j < qSize) {
        R.emplace_back(Q[j].str, q_lcp[j]);
        ++j;
    }

    return R;
}

void StringSortTester::StringMergeSort(std::vector<std::string>& arr) {
    if (arr.empty()) {
        return;
    }
    ResetComparisons();
    const auto result = StringMergeSortImpl(arr);
    for (size_t i = 0; i < result.size(); ++i) {
        arr[i] = result[i].str;
    }
}

// ==================== MSDRadixSort + MSDRadixSortWithSwitch ====================
int StringSortTester::CharAt(const std::string& s, const int depth) {
    if (depth >= static_cast<int>(s.size())) {
        return -1;
    }

    return static_cast<unsigned char>(s[depth]);
}

void StringSortTester::MSDRadixSortImpl(std::vector<std::string>& arr, std::vector<std::string>& buffer, const int left, const int right, const int depth, const bool useSwitch) {
    constexpr int alphabetSize = 256;

    if (right - left <= 1) {
        return;
    }

    if (useSwitch && right - left < alphabetSize) {
        StringQuickSortImpl(arr, left, right - 1, depth);
        return;
    }

    std::vector<int> count(alphabetSize + 2, 0);

    for (int i = left; i < right; ++i) {
        const int currentChar = CharAt(arr[i], depth);

        ++count[currentChar + 2];
    }

    for (int i = 0; i <= alphabetSize; ++i) {
        count[i + 1] += count[i];
    }

    const std::vector<int> startPositions = count;

    for (int i = left; i < right; ++i) {
        const int currentChar = CharAt(arr[i], depth);

        buffer[left + count[currentChar + 1]] = arr[i];
        ++count[currentChar + 1];
    }

    for (int i = left; i < right; ++i) {
        arr[i] = buffer[i];
    }

    for (int currentChar = 0; currentChar < alphabetSize; ++currentChar) {
        const int bucketLeft = left + startPositions[currentChar + 1];
        const int bucketRight = left + startPositions[currentChar + 2];

        MSDRadixSortImpl(arr, buffer, bucketLeft, bucketRight, depth + 1, useSwitch);
    }
}

void StringSortTester::MSDRadixSort(std::vector<std::string>& arr) {
    if (arr.empty()) {
        return;
    }

    ResetComparisons();

    std::vector<std::string> buffer(arr.size());

    MSDRadixSortImpl(arr, buffer, 0, static_cast<int>(arr.size()), 0, false);
}

void StringSortTester::MSDRadixSortWithSwitch(std::vector<std::string>& arr) {
    if (arr.empty()) {
        return;
    }

    ResetComparisons();

    std::vector<std::string> buffer(arr.size());

    MSDRadixSortImpl(arr, buffer, 0, static_cast<int>(arr.size()), 0, true);
}