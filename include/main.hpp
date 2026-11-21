#ifndef BINARY_SEARCH_TREE_HPP
#define BINARY_SEARCH_TREE_HPP

#include <cstddef>
#include <vector>
#include <utility>
#include <algorithm>
#include <functional>

template <typename T, typename Compare = std::less<T>>
class BinarySearchTree {
    public:
        using value_type = T;
        using size_type = std::size_t;

    private:
        struct Node {
            T data;
            size_type count;
            Node* left;
            Node* right;

            explicit Node(const T& val)
                : data(val), count(1), left(nullptr), right(nullptr) {}

            explicit Node(T&& val)
                : data(std::move(val)), count(1), left(nullptr), right(nullptr) {}
        };

        Node* root_;
        size_type total_elements_;
        size_type unique_elements_;
        Compare comp_;

        void destroy_subtree(Node* node) noexcept {
            if (!node) return;
            destroy_subtree(node->left);
            destroy_subtree(node->right);
            delete node;
        }

        Node* copy_subtree(const Node* node) {
            if (!node) return nullptr;
            Node* new_node = new Node(node->data);
            new_node->count = node->count;
            new_node->left = copy_subtree(node->left);
            new_node->right = copy_subtree(node->right);
            return new_node;
        }

        void in_order_collect(const Node* node, std::vector<T>& result) const {
            if (!node) return;
            in_order_collect(node->left, result);
            for (size_type i = 0; i < node->count; ++i) {
                result.push_back(node->data);
            }
            in_order_collect(node->right, result);
        }

        template <typename Func>
        void in_order_apply(const Node* node, Func&& visit) const {
            if (!node) return;
            in_order_apply(node->left, visit);
            for (size_type i = 0; i < node->count; ++i) {
                visit(node->data);
            }
            in_order_apply(node->right, visit);
        }

        size_type calculate_height(const Node* node) const noexcept {
            if (!node) return 0;
            size_type left_h = calculate_height(node->left);
            size_type right_h = calculate_height(node->right);
            return 1 + std::max(left_h, right_h);
        }

    public:
        BinarySearchTree()
            : root_(nullptr), total_elements_(0), unique_elements_(0), comp_(Compare()) {}

        explicit BinarySearchTree(const Compare& comp)
            : root_(nullptr), total_elements_(0), unique_elements_(0), comp_(comp) {}

        ~BinarySearchTree() {
            clear();
        }

        BinarySearchTree(const BinarySearchTree& other)
            : root_(copy_subtree(other.root_)),
            total_elements_(other.total_elements_),
            unique_elements_(other.unique_elements_),
            comp_(other.comp_) {}

        BinarySearchTree& operator=(const BinarySearchTree& other) {
            if (this != &other) {
                BinarySearchTree temp(other);
                swap(*this, temp);
            }
            return *this;
        }

        BinarySearchTree(BinarySearchTree&& other) noexcept
            : root_(other.root_),
            total_elements_(other.total_elements_),
            unique_elements_(other.unique_elements_),
            comp_(std::move(other.comp_)) {
            other.root_ = nullptr;
            other.total_elements_ = 0;
            other.unique_elements_ = 0;
        }

        BinarySearchTree& operator=(BinarySearchTree&& other) noexcept {
            if (this != &other) {
                clear();
                root_ = other.root_;
                total_elements_ = other.total_elements_;
                unique_elements_ = other.unique_elements_;
                comp_ = std::move(other.comp_);

                other.root_ = nullptr;
                other.total_elements_ = 0;
                other.unique_elements_ = 0;
            }
            return *this;
        }

        friend void swap(BinarySearchTree& first, BinarySearchTree& second) noexcept {
            using std::swap;
            swap(first.root_, second.root_);
            swap(first.total_elements_, second.total_elements_);
            swap(first.unique_elements_, second.unique_elements_);
            swap(first.comp_, second.comp_);
        }

        void insert(const T& value) {
            if (!root_) {
                root_ = new Node(value);
                total_elements_ = 1;
                unique_elements_ = 1;
                return;
            }

            Node* current = root_;
            while (true) {
                if (comp_(value, current->data)) {
                    if (current->left == nullptr) {
                        current->left = new Node(value);
                        ++unique_elements_;
                        break;
                    }
                    current = current->left;
                } else if (comp_(current->data, value)) {
                    if (current->right == nullptr) {
                        current->right = new Node(value);
                        ++unique_elements_;
                        break;
                    }
                    current = current->right;
                } else {
                    ++current->count;
                    break;
                }
            }
            ++total_elements_;
        }

        void insert(T&& value) {
            if (!root_) {
                root_ = new Node(std::move(value));
                total_elements_ = 1;
                unique_elements_ = 1;
                return;
            }

            Node* current = root_;
            while (true) {
                if (comp_(value, current->data)) {
                    if (current->left == nullptr) {
                        current->left = new Node(std::move(value));
                        ++unique_elements_;
                        break;
                    }
                    current = current->left;
                } else if (comp_(current->data, value)) {
                    if (current->right == nullptr) {
                        current->right = new Node(std::move(value));
                        ++unique_elements_;
                        break;
                    }
                    current = current->right;
                } else {
                    ++current->count;
                    break;
                }
            }
            ++total_elements_;
        }

        bool search(const T& value) const {
            const Node* current = root_;
            while (current != nullptr) {
                if (comp_(value, current->data)) {
                    current = current->left;
                } else if (comp_(current->data, value)) {
                    current = current->right;
                } else {
                    return true;
                }
            }
            return false;
        }

        std::vector<T> in_order_traversal() const {
            std::vector<T> result;
            result.reserve(total_elements_);
            in_order_collect(root_, result);
            return result;
        }

        template <typename Func>
        void in_order(Func&& visit) const {
            in_order_apply(root_, std::forward<Func>(visit));
        }

        static std::vector<T> sort(const std::vector<T>& input) {
            BinarySearchTree tree;
            for (const auto& item : input) {
                tree.insert(item);
            }
            return tree.in_order_traversal();
        }

        void clear() noexcept {
            destroy_subtree(root_);
            root_ = nullptr;
            total_elements_ = 0;
            unique_elements_ = 0;
        }

        [[nodiscard]] size_type size() const noexcept {
            return total_elements_;
        }

        [[nodiscard]] size_type unique_size() const noexcept {
            return unique_elements_;
        }

        [[nodiscard]] bool empty() const noexcept {
            return root_ == nullptr;
        }

        [[nodiscard]] size_type height() const noexcept {
            return calculate_height(root_);
        }
};

#endif