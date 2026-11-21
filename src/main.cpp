#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include <algorithm>
#include <iomanip>

#include "main.hpp"

template <typename T>
void print_sample(const std::vector<T>& vec, size_t sample_size = 5) {
    if (vec.empty()) {
        std::cout << "[]\n";
        return;
    }

    size_t n = vec.size();
    if (n <= sample_size * 2) {
        std::cout << "[ ";
        for (size_t i = 0; i < n; ++i) {
            std::cout << vec[i] << (i + 1 < n ? ", " : "");
        }
        std::cout << " ]\n";
        return;
    }

    std::cout << "[ ";
    for (size_t i = 0; i < sample_size; ++i) {
        std::cout << vec[i] << ", ";
    }
    std::cout << "... (" << (n - sample_size * 2) << " more) ... ";
    for (size_t i = n - sample_size; i < n; ++i) {
        std::cout << vec[i] << (i + 1 < n ? ", " : "");
    }
    std::cout << " ]\n";
}

int main() {
    constexpr size_t NUM_ELEMENTS = 10000;
    constexpr int MIN_VAL = 0;
    constexpr int MAX_VAL = 1000000;

    std::cout << "====================================================\n";
    std::cout << "   Binary Search Tree (Tree Sort) Demonstration     \n";
    std::cout << "====================================================\n";
    std::cout << "Element count : " << NUM_ELEMENTS << "\n";
    std::cout << "Value range   : [" << MIN_VAL << ", " << MAX_VAL << "]\n\n";

    std::cout << "[1/4] Generating " << NUM_ELEMENTS << " random numbers...\n";
    std::vector<int> numbers;
    numbers.reserve(NUM_ELEMENTS);

    std::random_device rd;
    std::mt19937_64 rng(rd());
    std::uniform_int_distribution<int> dist(MIN_VAL, MAX_VAL);

    auto gen_start = std::chrono::high_resolution_clock::now();
    for (size_t i = 0; i < NUM_ELEMENTS; ++i) {
        numbers.push_back(dist(rng));
    }
    auto gen_end = std::chrono::high_resolution_clock::now();
    double gen_time_ms = std::chrono::duration<double, std::milli>(gen_end - gen_start).count();

    std::cout << "      Generated in: " << std::fixed << std::setprecision(3) << gen_time_ms << " ms\n";
    std::cout << "      Unsorted Sample: ";
    print_sample(numbers, 5);
    std::cout << "\n";

    std::cout << "[2/4] Inserting elements into Binary Search Tree...\n";
    BinarySearchTree<int> bst;

    auto insert_start = std::chrono::high_resolution_clock::now();
    for (int num : numbers) {
        bst.insert(num);
    }
    auto insert_end = std::chrono::high_resolution_clock::now();
    double insert_time_ms = std::chrono::duration<double, std::milli>(insert_end - insert_start).count();

    std::cout << "      Insertion completed in : " << insert_time_ms << " ms\n";
    std::cout << "      Total elements in BST  : " << bst.size() << "\n";
    std::cout << "      Unique elements in BST : " << bst.unique_size() << "\n";
    std::cout << "      Duplicate occurrences  : " << (bst.size() - bst.unique_size()) << "\n";
    std::cout << "      Tree height (depth)    : " << bst.height() << "\n\n";

    std::cout << "[3/4] Extracting sorted array via in-order traversal...\n";
    auto traverse_start = std::chrono::high_resolution_clock::now();
    std::vector<int> sorted_numbers = bst.in_order_traversal();
    auto traverse_end = std::chrono::high_resolution_clock::now();
    double traverse_time_ms = std::chrono::duration<double, std::milli>(traverse_end - traverse_start).count();

    std::cout << "      In-order traversal in  : " << traverse_time_ms << " ms\n";
    std::cout << "      Total Tree Sort time   : " << (insert_time_ms + traverse_time_ms) << " ms\n";
    std::cout << "      Sorted Sample          : ";
    print_sample(sorted_numbers, 5);
    std::cout << "\n";

    std::cout << "[4/4] Verifying sorted result...\n";
    bool is_correct_size = (sorted_numbers.size() == NUM_ELEMENTS);
    bool is_sorted_order = std::is_sorted(sorted_numbers.begin(), sorted_numbers.end());

    std::cout << "      Output size match     : " << (is_correct_size ? "PASSED (10000/10000)" : "FAILED") << "\n";
    std::cout << "      Sorted order verified : " << (is_sorted_order ? "PASSED (strictly ascending)" : "FAILED") << "\n";

    if (is_correct_size && is_sorted_order) {
        std::cout << "\nSUCCESS: All 10,000 numbers successfully sorted using Binary Search Tree!\n";
    } else {
        std::cerr << "\nERROR: Verification failed!\n";
        return 1;
    }

    std::cout << "====================================================\n";
    return 0;
}
