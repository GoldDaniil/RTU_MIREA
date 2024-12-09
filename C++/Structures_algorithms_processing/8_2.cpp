#include <iostream>
#include <vector>
#include <algorithm>

//using namespace std;

//динамическое программирование (снизу вверх)
int max_path_sum_dp(std::vector<std::vector<int>>& triangle) {
    int n = triangle.size();

    for (int i = n - 2; i >= 0; --i) {
        for (int j = 0; j < triangle[i].size(); ++j) {
            int left = triangle[i + 1][j];
            int right = triangle[i + 1][j + 1];
            std::cout << "\ndp: сhoosing between " << left << " and " << right << " for element " << triangle[i][j] << std::endl;
            triangle[i][j] += std::max(left, right);
        }
    }

    return triangle[0][0];
}

//метод грубой силы - рекурсивный brute_force
int max_path_sum_brute_force(std::vector<std::vector<int>>& triangle, int row, int col) {
    if (row == triangle.size() - 1) {
        std::cout << "\nbrute force: reached base level with element " << triangle[row][col] << std::endl;
        return triangle[row][col];
    }

    int left_recursive_level_element = max_path_sum_brute_force(triangle, row + 1, col);
    int right_recursive_level_element = max_path_sum_brute_force(triangle, row + 1, col + 1);

    std::cout << "bute force: for element " << triangle[row][col]
        << ", choosing between " << left_recursive_level_element
        << " (left) and " << right_recursive_level_element << " (right)" << std::endl;

    return triangle[row][col] + std::max(left_recursive_level_element, right_recursive_level_element);
}

//максимум из четырех возможных чисел (соседей на уровне и следующем уровне)
int max_path_sum_custom(std::vector<std::vector<int>>& triangle) {
    int n = triangle.size();

    for (int i = n - 2; i >= 0; --i) {
        for (int j = 0; j < triangle[i].size(); ++j) {
            int number_left_same_level = (j > 0) ? triangle[i][j - 1] : 0;
            int number_right_same_level = (j < triangle[i].size() - 1) ? triangle[i][j + 1] : 0;
            int number_level_left_below_next = triangle[i + 1][j];
            int number_level_right_below_next = (j < triangle[i + 1].size() - 1) ? triangle[i + 1][j + 1] : 0;

            std::cout << "\ncustom: for element " << triangle[i][j]
                << ", considering options: "
                << number_left_same_level << " (left same level), "
                << number_right_same_level << " (right same level), "
                << number_level_left_below_next << " (left below), "
                << number_level_right_below_next << " (right below)" << std::endl;

            triangle[i][j] += std::max({ number_left_same_level, number_right_same_level,
                                         number_level_left_below_next, number_level_right_below_next });
        }
    }

    return triangle[0][0];
}

int main() {
    std::vector<std::vector<int>> triangle = {
        {7},
        {3, 8},
        {8, 1, 0},
        {2, 7, 4, 4},
        {1, 5, 2, 6, 5}
    };

    std::vector<std::vector<int>> dp_triangle = triangle;
    int dp_result = max_path_sum_dp(dp_triangle);
    std::cout << "max sum (1) = " << dp_result << std::endl;

    std::cout << "\n";

    int brute_force_result = max_path_sum_brute_force(triangle, 0, 0);
    std::cout << "max sum (2) = " << brute_force_result << std::endl;

    std::cout << "\n";

    std::vector<std::vector<int>> custom_triangle = triangle;
    int custom_result = max_path_sum_custom(custom_triangle);
    std::cout << "max sum (3) = " << custom_result << std::endl;

    std::cout << "results: " << dp_result << " " << brute_force_result << " " << custom_result << std::endl;

    return 0;
}
