#include <iostream>
#include <vector>
#include <algorithm>

int dp_count = 0;
int brute_force_count = 0;
int custom_count = 0;
int top_down_count = 0;

//динамическое программирование (снизу вверх)
int max_path_sum_dp(std::vector<std::vector<int>>& triangle) {
    int n = triangle.size();

    for (int i = n - 2; i >= 0; --i) {
        for (int j = 0; j < triangle[i].size(); ++j) {
            dp_count++;
            int left = triangle[i + 1][j];
            int right = triangle[i + 1][j + 1];
            int chosen = std::max(left, right);
            std::cout << "\ndp: выбор между " << left << " и " << right
                << " для элемента " << triangle[i][j]
                << ", выбираем " << chosen << std::endl;
            triangle[i][j] += chosen;
        }
    }

    return triangle[0][0];
}

//метод грубой силы - рекурсивный brute_force
int max_path_sum_brute_force(std::vector<std::vector<int>>& triangle, int row, int col) {
    brute_force_count++;
    if (row == triangle.size() - 1) {
        std::cout << "\nметод перебора: находимся на базовом уровне с элементом " << triangle[row][col] << std::endl;
        return triangle[row][col];
    }

    int left_recursive_level_element = max_path_sum_brute_force(triangle, row + 1, col);
    int right_recursive_level_element = max_path_sum_brute_force(triangle, row + 1, col + 1);
    int chosen = std::max(left_recursive_level_element, right_recursive_level_element);

    std::cout << "метод перебора: для элемента " << triangle[row][col]
        << ", выбор между " << left_recursive_level_element
        << " (левый) и " << right_recursive_level_element
        << " (правый), выбираем " << chosen << std::endl;

    return triangle[row][col] + chosen;
}


//максимум из четырех возможных чисел (соседей на уровне и следующем уровне)
int max_path_sum_custom(std::vector<std::vector<int>>& triangle) {
    int n = triangle.size();

    for (int i = n - 2; i >= 0; --i) {
        for (int j = 0; j < triangle[i].size(); ++j) {
            custom_count++;
            //custom_count += 4;
            int number_left_same_level = (j > 0) ? triangle[i][j - 1] : 0;
            int number_right_same_level = (j < triangle[i].size() - 1) ? triangle[i][j + 1] : 0;
            int number_level_left_below_next = triangle[i + 1][j];
            int number_level_right_below_next = (j < triangle[i + 1].size() - 1) ? triangle[i + 1][j + 1] : 0;

            int chosen = std::max({ number_left_same_level, number_right_same_level,
                                   number_level_left_below_next, number_level_right_below_next });

            std::cout << "\nдля элемента " << triangle[i][j]
                << ", рассматриваются варианты: "
                << number_left_same_level << " (слева на том же уровне), "
                << number_right_same_level << " (справа на том же уровне), "
                << number_level_left_below_next << " (слева на уровне ниже), "
                << number_level_right_below_next << " (справа на уровне ниже), "
                << "выбираем " << chosen << std::endl;

            triangle[i][j] += chosen;
        }
    }

    return triangle[0][0];
}

//сверху вниз - c вершины треугольника итеративно добавляем значения к двум ближайшим элементам на след уровне
int max_path_sum_top_down(std::vector<std::vector<int>>& triangle) {
    int n = triangle.size();
    std::vector<std::vector<int>> dp = triangle;

    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < triangle[i].size(); ++j) {
            int left_choice = dp[i][j] + triangle[i + 1][j];
            int right_choice = dp[i][j] + triangle[i + 1][j + 1];

            dp[i + 1][j] = std::max(dp[i + 1][j], left_choice);
            dp[i + 1][j + 1] = std::max(dp[i + 1][j + 1], right_choice);

            top_down_count++;

            std::cout << "метод сверху вниз: для узла [" << i << "][" << j << "] (значение: " << triangle[i][j]
                << "), выбор между "
                << left_choice << " (левый узел: [" << i + 1 << "][" << j << "]) и "
                << right_choice << " (правый узел: [" << i + 1 << "][" << j + 1 << "]), ";

            if (left_choice > right_choice) {
                std::cout << "выбираем " << left_choice << std::endl;
            }
            else {
                std::cout << "выбираем " << right_choice << std::endl;
            }
        }
    }

    return *std::max_element(dp[n - 1].begin(), dp[n - 1].end());
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
    std::cout << "максимальная сумма (1) = " << dp_result << std::endl << 
        "переборы (1): " << dp_count << std::endl << std::endl;


    int brute_force_result = max_path_sum_brute_force(triangle, 0, 0);
    std::cout << "максимальная сумма (2) = " << brute_force_result << std::endl <<
        "переборы (1): " << brute_force_count << std::endl << std::endl;

    std::vector<std::vector<int>> custom_triangle = triangle;
    int custom_result = max_path_sum_custom(custom_triangle);
    std::cout << "максимальная сумма (3) = " << custom_result << std::endl <<
        "переборы (1): " << custom_count << std::endl << std::endl;

    std::vector<std::vector<int>> top_down_triangle = triangle;
    int top_down_result = max_path_sum_top_down(top_down_triangle);
    std::cout << "максимальная сумма (4) = " << top_down_result << std::endl <<
        "переборы (1): " << top_down_count << std::endl << std::endl;

    std::cout << "\n\nрезы: " << dp_result << " " << brute_force_result << " " << custom_result << " " << top_down_result << std::endl;

    std::cout << "\nпереборы: " << dp_count << " " << brute_force_count << " " << custom_count << " " << top_down_count;

    return 0;
}
