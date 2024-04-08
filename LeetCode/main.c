#include "assertions.h"
#include "interviewsolution.h"
#include "recentcounter.h"
#include "solution.h"
#include "testutils.h"

static int main_ret = 0;
static int test_count = 0;
static int test_pass = 0;

static void test_two_sum() {
    int actualReturnSize = 0;
    int *actual = two_sum(ARRAY(int, 2, 7, 11, 15), 4, 9, &actualReturnSize);
    EXPECT_EQ_INT_ARRAY(ARRAY(int, 0, 1), 2, actual, actualReturnSize)
}

static void test_add_two_numbers() {
    ListNode *actual1 = add_two_numbers(create_listnode(ARRAY(int, 2, 4, 3), 3), create_listnode(ARRAY(int, 5, 6, 4), 3));
    ListNode *actual2 = add_two_numbers(create_listnode(ARRAY(int, 0), 1), create_listnode(ARRAY(int, 0), 1));
    ListNode *actual3 = add_two_numbers(create_listnode(ARRAY(int, 9, 9, 9, 9, 9, 9, 9), 7), create_listnode(ARRAY(int, 9, 9, 9, 9), 4));
    ListNode *expected1 = create_listnode(ARRAY(int, 7, 0, 8), 3);
    ListNode *expected2 = create_listnode(ARRAY(int, 0), 1);
    ListNode *expected3 = create_listnode(ARRAY(int, 8, 9, 9, 9, 0, 0, 0, 1), 8);
    EXPECT_EQ_TRUE(is_same_listnode(actual1, expected1));
    EXPECT_EQ_TRUE(is_same_listnode(actual2, expected2));
    EXPECT_EQ_TRUE(is_same_listnode(actual3, expected3));
}

static void test_remove_element() {
    EXPECT_EQ_INT(remove_element(ARRAY(int, 3, 2, 2, 3), 4, 3), 2);
    EXPECT_EQ_INT(remove_element(ARRAY(int, 0, 1, 2, 2, 3, 0, 4, 2), 8, 2), 5);
}

static void test_remove_duplicates() {
    EXPECT_EQ_INT(remove_duplicates(ARRAY(int, 1, 1, 2), 3), 2);
    EXPECT_EQ_INT(remove_duplicates(ARRAY(int, 0, 0, 1, 1, 1, 2, 2, 3, 3, 4), 10), 5);
}

static void test_search() {
    EXPECT_EQ_INT(4, search(ARRAY(int, 4, 5, 6, 7, 0, 1, 2), 7, 0));
}

#define TEST_ROTATE(input_data, row_size, col_size, expected, expected_row_size) \
    do {                                                                         \
        TEST_MATRIX_BASE(input_data, row_size);                                  \
        int col = col_size;                                                      \
        rotate(mat, (row_size), &col);                                           \
        EXPECT_EQ_MATRIX((expected), (expected_row_size), (mat), (row_size));    \
    } while (0)

static void test_rotate() {
    int matrix1[3][3] = {{1, 2, 3},
                         {4, 5, 6},
                         {7, 8, 9}};
    int matrix2[4][4] = {{5, 1, 9, 11},
                         {2, 4, 8, 10},
                         {13, 3, 6, 7},
                         {15, 14, 12, 16}};
    int expected1[3][3] = {{7, 4, 1},
                           {8, 5, 2},
                           {9, 6, 3}};
    int expected2[4][4] = {{15, 13, 2, 5},
                           {14, 3, 4, 1},
                           {12, 6, 8, 9},
                           {16, 7, 10, 11}};
    TEST_ROTATE(matrix1, 3, 3, expected1, 3);
    TEST_ROTATE(matrix2, 4, 4, expected2, 4);
}

static void test_merge() {
    int actual1[6] = {1, 2, 3, 0, 0, 0};
    int nums2[3] = {2, 5, 6};
    merge(actual1, 6, 3, nums2, 3, 3);
    int expected1[6] = {1, 2, 2, 3, 5, 6};
    EXPECT_EQ_INT_ARRAY(expected1, 6, actual1, 6);

    int actual2[1] = {1};
    int nums3[1];
    merge(actual2, 1, 1, nums3, 0, 0);
    int expected2[1] = {1};
    EXPECT_EQ_INT_ARRAY(expected2, 1, actual2, 1);

    int actual3[1] = {0};
    int nums4[1] = {1};
    merge(actual3, 0, 0, nums4, 1, 1);
    int expected3[1] = {1};
    EXPECT_EQ_INT_ARRAY(expected3, 1, actual3, 1);
};

static void test_is_same_tree() {
    TreeNode left1 = {2, NULL, NULL};
    TreeNode right1 = {3, NULL, NULL};
    TreeNode root1 = {1, &left1, &right1};
    TreeNode left2 = {2, NULL, NULL};
    TreeNode right2 = {3, NULL, NULL};
    TreeNode root2 = {1, &left2, &right2};
    EXPECT_EQ_TRUE(is_same_tree(&root1, &root2));
    EXPECT_EQ_TRUE(is_same_tree(NULL, NULL));
    EXPECT_EQ_FALSE(is_same_tree(&root1, NULL));
    EXPECT_EQ_FALSE(is_same_tree(NULL, &root1));
}

static void test_reverse_list() {
    ListNode *head1 = create_listnode(ARRAY(int, 1, 2, 3, 4, 5), 5);
    ListNode *actual1 = reverse_list(head1);
    ListNode *expected1 = create_listnode(ARRAY(int, 5, 4, 3, 2, 1), 5);
    EXPECT_EQ_TRUE(is_same_listnode(actual1, expected1));
}

static void test_count_numbers_with_unique_digits() {
    EXPECT_EQ_INT(91, count_numbers_with_unique_digits(2));
    EXPECT_EQ_INT(1, count_numbers_with_unique_digits(0));
}

static void test_lexical_order() {
    int expect1[13] = {1, 10, 11, 12, 13, 2, 3, 4, 5, 6, 7, 8, 9};
    int returnSize1 = 0;
    int *actual1 = lexical_order(13, &returnSize1);
    EXPECT_EQ_INT_ARRAY(expect1, 13, actual1, returnSize1);

    int expect2[2] = {1, 2};
    int returnSize2 = 0;
    int *actual2 = lexical_order(2, &returnSize2);
    EXPECT_EQ_INT_ARRAY(expect2, 2, actual2, returnSize2);
}

static void test_find_substring_in_wraparoundString() {
    EXPECT_EQ_INT(1, find_substring_in_wraparound_string("a"));
    EXPECT_EQ_INT(2, find_substring_in_wraparound_string("cac"));
    EXPECT_EQ_INT(6, find_substring_in_wraparound_string("zab"));
}

static void test_find_diagonal_order() {
    int matrix1[3][3] = {{1, 2, 3},
                         {4, 5, 6},
                         {7, 8, 9}};
    int matrix2[2][2] = {{1, 2},
                         {3, 4}};
    int expected1[9] = {1, 2, 4, 7, 5, 3, 6, 8, 9};
    int expected2[4] = {1, 2, 3, 4};

    TEST_FIND_DIAGONAL_ORDER(matrix1, 3, 3, expected1, 9);
    TEST_FIND_DIAGONAL_ORDER(matrix2, 2, 2, expected2, 4);
}

static void test_find_longest_chain() {
    int **pairs1 = initialize_matrix(ARRAY(int, 1, 2, 2, 3, 3, 4), 3, 2);
    int **pairs2 = initialize_matrix(ARRAY(int, 1, 2, 7, 8, 4, 5), 3, 2);
    int pairsColSize1 = 2;
    int pairsColSize2 = 2;
    EXPECT_EQ_INT(2, find_longest_chain(pairs1, 3, &pairsColSize1));
    EXPECT_EQ_INT(3, find_longest_chain(pairs2, 3, &pairsColSize2));
}

static void test_find_closest_elements() {
    int arr1[] = {1, 2, 3, 4, 5};
    int arr2[] = {1, 2, 3, 4, 5};
    int returnSize1 = 0;
    int returnSize2 = 0;
    int expect1[] = {1, 2, 3, 4};
    int expect2[] = {1, 2, 3, 4};
    int *actual1 = find_closest_elements(arr1, 5, 4, 3, &returnSize1);
    int *actual2 = find_closest_elements(arr2, 5, 4, -1, &returnSize2);
    EXPECT_EQ_INT_ARRAY(expect1, 4, actual1, returnSize1);
    EXPECT_EQ_INT_ARRAY(expect2, 4, actual2, returnSize2);
}

static void test_width_of_binary_tree() {
    // TODO
}

static void test_construct_array() {
    int returnSize1 = 0;
    int returnSize2 = 0;
    int *actual1 = construct_array(3, 1, &returnSize1);
    int *actual2 = construct_array(3, 2, &returnSize2);
    EXPECT_EQ_INT_ARRAY(ARRAY(int, 1, 2, 3), 3, actual1, returnSize1);
    EXPECT_EQ_INT_ARRAY(ARRAY(int, 1, 3, 2), 3, actual2, returnSize2);
}

static void test_trim_bst() {
}

static void test_maximum_swap() {
    EXPECT_EQ_INT(7236, maximum_swap(2736));
    EXPECT_EQ_INT(9973, maximum_swap(9973));
}

static void test_longest_univalue_path() {
    // TODO
}

static void test_self_dividing_numbers() {
    int returnSize1 = 0;
    int *actual1 = self_dividing_numbers(1, 22, &returnSize1);
    int expect1[13] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 11, 12, 15, 22};
    EXPECT_EQ_INT_ARRAY(expect1, 13, actual1, returnSize1);
}

static void test_next_greatest_letter() {
    char letters[3] = {'c', 'f', 'j'};
    EXPECT_EQ_CHAR('c', next_greatest_letter(letters, 3, 'a'));
    EXPECT_EQ_CHAR('f', next_greatest_letter(letters, 3, 'c'));
    EXPECT_EQ_CHAR('f', next_greatest_letter(letters, 3, 'c'));
}

static void test_max_chunks_to_sorted() {
    EXPECT_EQ_INT(1, max_chunks_to_sorted(ARRAY(int, 4, 3, 2, 1, 0), 5));
    EXPECT_EQ_INT(4, max_chunks_to_sorted(ARRAY(int, 1, 0, 2, 3, 4), 5));
}

static void test_can_transform() {
    bool actual1 = can_transform("RXXLRXRXL", "XRLXXRRLX");
    bool actual2 = can_transform("X", "L");
    EXPECT_EQ_TRUE(actual1);
    EXPECT_EQ_FALSE(actual2);
}

static void test_preimage_size_fzf() {
    EXPECT_EQ_INT(5, preimage_size_fzf(0));
    EXPECT_EQ_INT(0, preimage_size_fzf(5));
    EXPECT_EQ_INT(5, preimage_size_fzf(3));
}

static void test_min_swap() {
    EXPECT_EQ_INT(1, min_swap(ARRAY(int, 1, 3, 5, 4), 4, ARRAY(int, 1, 2, 3, 7), 4));
    EXPECT_EQ_INT(1, min_swap(ARRAY(int, 0, 3, 5, 8, 9), 5, ARRAY(int, 2, 1, 4, 6, 9), 5));
}

static void test_unique_morse_representations() {
    char *words1[] = {"gin", "zen", "gig", "msg"};
    char *words2[] = {"a"};
    EXPECT_EQ_INT(2, unique_morse_representations(words1, 4));
    EXPECT_EQ_INT(1, unique_morse_representations(words2, 1));
}

static void test_number_of_lines() {
    int widths1[26] = {10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10,
                       10, 10};
    int widths2[26] = {4, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10,
                       10, 10};
    char *s1 = "abcdefghijklmnopqrstuvwxyz";
    char *s2 = "bbbcccdddaaa";
    int widths_size = 26;
    int expected1[2] = {3, 60};
    int expected2[2] = {2, 4};
    TEST_NUMBER_OF_LINES(widths1, widths_size, s1, expected1, 2);
    TEST_NUMBER_OF_LINES(widths2, widths_size, s2, expected2, 2);
}

static void test_unique_letter_string() {
    char *s1 = "ABC";
    char *s2 = "ABA";
    char *s3 = "LEETCODE";
    EXPECT_EQ_INT(10, unique_letter_string(s1));
    EXPECT_EQ_INT(8, unique_letter_string(s2));
    EXPECT_EQ_INT(92, unique_letter_string(s3));
}

static void test_score_of_parentheses() {
    EXPECT_EQ_INT(1, score_of_parentheses("()"));
    EXPECT_EQ_INT(2, score_of_parentheses("(())"));
    EXPECT_EQ_INT(2, score_of_parentheses("()()"));
}

static void test_advantage_count() {
    int returnSize1 = 0;
    int returnSize2 = 0;
    int *actual1 = advantage_count(ARRAY(int, 2, 7, 11, 15), 4, ARRAY(int, 1, 10, 4, 11), 4, &returnSize1);
    int *actual2 = advantage_count(ARRAY(int, 12, 24, 8, 32), 4, ARRAY(int, 13, 25, 32, 11), 4, &returnSize2);
    EXPECT_EQ_INT_ARRAY(ARRAY(int, 2, 11, 7, 15), 4, actual1, returnSize1);
    EXPECT_EQ_INT_ARRAY(ARRAY(int, 24, 32, 8, 12), 4, actual2, returnSize2);
}

static void test_is_alien_sorted() {
    char *words1[2] = {"hello", "leetcode"};
    char *words2[3] = {"word", "world", "row"};
    char *words3[2] = {"apple", "app"};
    char *order1 = "hlabcdefgijkmnopqrstuvwxyz";
    char *order2 = "worldabcefghijkmnpqstuvxyz";
    char *order3 = "abcdefghijklmnopqrstuvwxyz";
    EXPECT_EQ_TRUE(is_alien_sorted(words1, 2, order1));
    EXPECT_EQ_FALSE(is_alien_sorted(words2, 3, order2));
    EXPECT_EQ_FALSE(is_alien_sorted(words3, 2, order3));
}

static void test_defanging_IPadd() {
    EXPECT_EQ_STRING("1[.]1[.]1[.]1", defang_ip_addr("1.1.1.1"));
    EXPECT_EQ_STRING("255[.]100[.]50[.]0", defang_ip_addr("255.100.50.0"));
}

static void test_min_subsequence() {
    int input1[5] = {4, 3, 10, 9, 8};
    int input2[5] = {4, 4, 7, 6, 7};
    int input3[1] = {6};
    int expected1[2] = {10, 9};
    int expected2[3] = {7, 7, 6};
    int expected3[1] = {6};
    int returnSize1 = 0;
    int returnSize2 = 0;
    int returnSize3 = 0;
    int *actual1 = min_subsequence(input1, 5, &returnSize1);
    int *actual2 = min_subsequence(input2, 5, &returnSize2);
    int *actual3 = min_subsequence(input3, 1, &returnSize3);
    EXPECT_EQ_INT_ARRAY(expected1, 2, actual1, returnSize1);
    EXPECT_EQ_INT_ARRAY(expected2, 3, actual2, returnSize2);
    EXPECT_EQ_INT_ARRAY(expected3, 1, actual3, returnSize3);
}

static void test_string_matching() {
    char *words1[4] = {"mass", "as", "hero", "superhero"};
    char *words2[3] = {"leetcode", "et", "code"};
    char *words3[3] = {"blue", "green", "bu"};
    char *expected1[2] = {"as", "hero"};
    char *expected2[2] = {"et", "code"};
    char *expected3[] = {"\0"};
    int returnSize1 = 0;
    int returnSize2 = 0;
    int returnSize3 = 0;
    char **actual1 = string_matching(words1, 4, &returnSize1);
    char **actual2 = string_matching(words2, 3, &returnSize2);
    char **actual3 = string_matching(words3, 3, &returnSize3);
    EXPECT_EQ_STRING_ARRAY(expected1, 2, actual1, returnSize1);
    EXPECT_EQ_STRING_ARRAY(expected2, 2, actual2, returnSize2);
    EXPECT_EQ_STRING_ARRAY(expected3, 0, actual3, returnSize3);
}

static void test_busy_student() {
    int startTimes1[3] = {1, 2, 3};
    int endTimes1[3] = {3, 2, 7};
    int startTimes2[1] = {4};
    int endTimes2[1] = {4};
    EXPECT_EQ_INT(busy_student(startTimes1, 3, endTimes1, 3, 4), 1);
    EXPECT_EQ_INT(busy_student(startTimes2, 1, endTimes2, 1, 4), 1);
}

static void test_is_prefix_of_word() {
    char *sentence1 = "i love eating burger";
    char *sentence2 = "this problem is an easy problem";
    char *sentence3 = "i am tired";
    char *searchWord1 = "burg";
    char *searchWord2 = "pro";
    char *searchWord3 = "you";
    EXPECT_EQ_INT(4, is_prefix_of_word(sentence1, searchWord1));
    EXPECT_EQ_INT(2, is_prefix_of_word(sentence2, searchWord2));
    EXPECT_EQ_INT(-1, is_prefix_of_word(sentence3, searchWord3));
}

static void test_can_be_equal() {
    int target1[] = {1, 2, 3, 4};
    int target2[] = {7};
    int target3[] = {3, 7, 9};
    int arr1[] = {2, 1, 3, 4};
    int arr2[] = {7};
    int arr3[] = {3, 7, 11};
    EXPECT_EQ_TRUE(can_be_equal(target1, 4, arr1, 4));
    EXPECT_EQ_TRUE(can_be_equal(target2, 1, arr2, 1));
    EXPECT_EQ_FALSE(can_be_equal(target3, 3, arr3, 3));
}

static void test_max_product() {
    int nums1[] = {3, 4, 5, 2};
    int nums2[] = {1, 5, 4, 5};
    int nums3[] = {3, 7};
    EXPECT_EQ_INT(12, max_product(nums1, 4));
    EXPECT_EQ_INT(16, max_product(nums2, 4));
    EXPECT_EQ_INT(12, max_product(nums3, 2));
}

static void test_num_special() {
    int **mat1 = initialize_matrix(ARRAY(int, 1, 0, 0, 0, 0, 1, 1, 0, 0), 3, 3);
    int **mat2 = initialize_matrix(ARRAY(int, 1, 0, 0, 0, 1, 0, 0, 0, 1), 3, 3);
    int matColSize1 = 3;
    int matColSize2 = 3;
    EXPECT_EQ_INT(1, num_special(mat1, 3, &matColSize1));
    EXPECT_EQ_INT(3, num_special(mat2, 3, &matColSize2));
}

static void test_reorder_spaces() {
    EXPECT_EQ_STRING("this   is   a   sentence", reorder_spaces("  this   is  a sentence "));
    EXPECT_EQ_STRING("practice   makes   perfect ", reorder_spaces(" practice   makes   perfect"));
}

static void test_min_operations() {
    char *logs1[5] = {"d1/", "d2/", "../", "d21/", "./"};
    char *logs2[6] = {"d1/", "d2/", "./", "d3/", "../", "d31/"};
    char *logs3[4] = {"d1/", "../", "../", "../"};
    EXPECT_EQ_INT(2, min_operations(logs1, 5));
    EXPECT_EQ_INT(3, min_operations(logs2, 6));
    EXPECT_EQ_INT(0, min_operations(logs3, 4));
}

static void test_special_array() {
    EXPECT_EQ_INT(2, special_array(ARRAY(int, 3, 5), 2));
    EXPECT_EQ_INT(-1, special_array(ARRAY(int, 0, 0), 2));
    EXPECT_EQ_INT(3, special_array(ARRAY(int, 0, 4, 3, 0, 4), 5));
}

static void test_trim_mean() {
    EXPECT_EQ_TRUE((trim_mean(ARRAY(int, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 3), 20) - 2.00000) <= 0.00001);
    EXPECT_EQ_TRUE((trim_mean(ARRAY(int, 6, 2, 7, 5, 1, 2, 0, 3, 10, 2, 5, 0, 5, 5, 0, 8, 7, 6, 8, 0), 20) - 4.00000) <= 0.00001);
    EXPECT_EQ_TRUE((trim_mean(ARRAY(int, 6, 0, 7, 0, 7, 5, 7, 8, 3, 4, 0, 7, 8, 1, 6, 8, 1, 1, 2, 4, 8, 1, 9, 5, 4, 3, 8, 5, 10, 8, 6, 6, 1, 0, 6, 10, 8, 2, 3, 4), 40) - 4.77778) <= 0.00001);
}

static void test_max_length_between_equal_characters() {
    EXPECT_EQ_INT(0, max_length_between_equal_characters("aa"));
    EXPECT_EQ_INT(2, max_length_between_equal_characters("abca"));
    EXPECT_EQ_INT(-1, max_length_between_equal_characters("cbyzx"));
}

static void test_min_operations_2() {
    EXPECT_EQ_INT(2, min_operations_2(ARRAY(int, 1, 1, 4, 2, 3), 5, 5));
    EXPECT_EQ_INT(-1, min_operations_2(ARRAY(int, 5, 6, 7, 8, 9), 5, 4));
    EXPECT_EQ_INT(5, min_operations_2(ARRAY(int, 3, 2, 20, 1, 1, 3), 6, 10));
}

static void test_maximum_wealth() {
    int accounts_array1[2][3] = {{1, 2, 3}, {3, 2, 1}};
    int accounts_array2[3][3] = {{1, 5}, {7, 3}, {3, 5}};
    int accounts_array3[3][3] = {{2, 8, 7}, {7, 1, 3}, {1, 9, 5}};
    TEST_MATRIX_INT(maximum_wealth, accounts_array1, 2, 3, 6);
    TEST_MATRIX_INT(maximum_wealth, accounts_array2, 3, 3, 10);
    TEST_MATRIX_INT(maximum_wealth, accounts_array3, 3, 3, 17);
}

static void test_reformat_number() {
    EXPECT_EQ_STRING("123-456", reformat_number("1-23-45 6"));
    EXPECT_EQ_STRING("123-45-67", reformat_number("123 4-567"));
    EXPECT_EQ_STRING("123-456-78", reformat_number("123 4-5678"));
}

static void test_minimum_length() {
    EXPECT_EQ_INT(2, minimum_length("ca"));
    EXPECT_EQ_INT(0, minimum_length("cabaabac"));
    EXPECT_EQ_INT(3, minimum_length("aabccabba"));
}

static void test_merge_alternately() {
    EXPECT_EQ_STRING("apbqcr", merge_alternately("abc", "pqr"));
    EXPECT_EQ_STRING("apbqrs", merge_alternately("ab", "pqrs"));
    EXPECT_EQ_STRING("apbqcd", merge_alternately("abcd", "pq"));
}

static void test_nearest_valid_point() {
}

static void test_check_ones_segment() {
    EXPECT_EQ_FALSE(check_ones_segment("1001"));
    EXPECT_EQ_TRUE(check_ones_segment("110"));
}

static void test_ara_almost_equal() {
    EXPECT_EQ_TRUE(are_almost_equal("bank", "kanb"));
    EXPECT_EQ_FALSE(are_almost_equal("attack", "defend"));
    EXPECT_EQ_TRUE(are_almost_equal("kelb", "kelb"));
}

static void test_max_ascending_sum() {
    EXPECT_EQ_INT(65, max_ascending_sum(ARRAY(int, 10, 20, 30, 5, 10, 50), 6));
    EXPECT_EQ_INT(150, max_ascending_sum(ARRAY(int, 10, 20, 30, 40, 50), 5));
    EXPECT_EQ_INT(33, max_ascending_sum(ARRAY(int, 12, 17, 15, 13, 10, 11, 12), 7));
}

static void test_shuffle() {
    int returnSize1 = 0;
    int returnSize2 = 0;
    int returnSize3 = 0;
    int *actual1 = shuffle(ARRAY(int, 2, 5, 1, 3, 4, 7), 6, 3, &returnSize1);
    int *actual2 = shuffle(ARRAY(int, 1, 2, 3, 4, 4, 3, 2, 1), 8, 4, &returnSize2);
    int *actual3 = shuffle(ARRAY(int, 1, 1, 2, 2), 4, 2, &returnSize3);
    EXPECT_EQ_INT_ARRAY(ARRAY(int, 2, 3, 5, 4, 1, 7), 6, actual1, returnSize1)
    EXPECT_EQ_INT_ARRAY(ARRAY(int, 1, 4, 2, 3, 3, 2, 4, 1), 8, actual2, returnSize2)
    EXPECT_EQ_INT_ARRAY(ARRAY(int, 1, 2, 1, 2), 4, actual3, returnSize3)
}

static void test_final_prices() {
    int returnSize1 = 0;
    int returnSize2 = 0;
    int returnSize3 = 0;
    int *actual1 = final_prices(ARRAY(int, 8, 4, 6, 2, 3), 5, &returnSize1);
    int *actual2 = final_prices(ARRAY(int, 1, 2, 3, 4, 5), 5, &returnSize2);
    int *actual3 = final_prices(ARRAY(int, 10, 1, 1, 6), 4, &returnSize3);
    EXPECT_EQ_INT_ARRAY(ARRAY(int, 4, 2, 4, 2, 3), 5, actual1, returnSize1)
    EXPECT_EQ_INT_ARRAY(ARRAY(int, 1, 2, 3, 4, 5), 5, actual2, returnSize2)
    EXPECT_EQ_INT_ARRAY(ARRAY(int, 9, 0, 1, 6), 4, actual3, returnSize3)
}

static void test_projection_area() {
    int grid1[2][2] = {{1, 2}, {3, 4}};
    int grid2[1][1] = {{2}};
    int grid3[2][2] = {{1, 0}, {0, 2}};
    TEST_MATRIX_INT(projection_area, grid1, 2, 2, 17);
    TEST_MATRIX_INT(projection_area, grid2, 1, 1, 5);
    TEST_MATRIX_INT(projection_area, grid3, 2, 2, 8);
}

static void test_sort_array_by_parity() {
    int returnSize1 = 0;
    int returnSize2 = 0;
    int *actual1 = sort_array_by_parity(ARRAY(int, 3, 1, 2, 4), 4, &returnSize1);
    int *actual2 = sort_array_by_parity(ARRAY(int, 0), 1, &returnSize2);
    EXPECT_EQ_INT_ARRAY(ARRAY(int, 4, 2, 1, 3), 4, actual1, returnSize1);
    EXPECT_EQ_INT_ARRAY(ARRAY(int, 0), 1, actual2, returnSize2);
}

static void test_partition_disjoint() {
    EXPECT_EQ_INT(3, partition_disjoint(ARRAY(int, 5, 0, 3, 8, 6), 5));
    EXPECT_EQ_INT(4, partition_disjoint(ARRAY(int, 1, 1, 1, 0, 6, 12), 6));
}

static void test_min_add_to_make_valid() {
    EXPECT_EQ_INT(1, min_add_to_make_valid("())"));
    EXPECT_EQ_INT(3, min_add_to_make_valid("((("));
}

static void test_three_equal_parts() {
    int returnSize1 = 0;
    int returnSize2 = 0;
    int returnSize3 = 0;
    int *actual1 = three_equal_parts(ARRAY(int, 1, 0, 1, 0, 1), 5, &returnSize1);
    int *actual2 = three_equal_parts(ARRAY(int, 1, 1, 0, 1, 1), 5, &returnSize2);
    int *actual3 = three_equal_parts(ARRAY(int, 1, 1, 0, 0, 1), 5, &returnSize3);
    EXPECT_EQ_INT_ARRAY(ARRAY(int, 0, 3), 2, actual1, returnSize1);
    EXPECT_EQ_INT_ARRAY(ARRAY(int, -1, -1), 2, actual2, returnSize2);
    EXPECT_EQ_INT_ARRAY(ARRAY(int, 0, 2), 2, actual3, returnSize3);
}

static void test_distinct_subseq_ii() {
    EXPECT_EQ_INT(7, distinct_subseq_ii("abc"));
    EXPECT_EQ_INT(6, distinct_subseq_ii("aba"));
    EXPECT_EQ_INT(3, distinct_subseq_ii("aaa"));
}

static void test_di_string_match() {
    int returnSize1 = 0;
    int returnSize2 = 0;
    int returnSize3 = 0;
    int *actual1 = di_string_match("IDID", &returnSize1);
    int *actual2 = di_string_match("III", &returnSize2);
    int *actual3 = di_string_match("DDI", &returnSize3);
    EXPECT_EQ_INT_ARRAY(ARRAY(int, 0, 4, 1, 3, 2), 5, actual1, returnSize1);
    EXPECT_EQ_INT_ARRAY(ARRAY(int, 0, 1, 2, 3), 4, actual2, returnSize2);
    EXPECT_EQ_INT_ARRAY(ARRAY(int, 3, 2, 0, 1), 4, actual3, returnSize3);
}

static void test_min_deletion_size() {
    EXPECT_EQ_INT(1, min_deletion_size(ARRAY(char *, "cba", "daf", "ghi"), 3));
    EXPECT_EQ_INT(0, min_deletion_size(ARRAY(char *, "a", "b"), 2));
    EXPECT_EQ_INT(3, min_deletion_size(ARRAY(char *, "zyx", "wvu", "tsr"), 3));
}

static void test_validate_stack_sequences() {
    EXPECT_EQ_TRUE(validate_stack_sequences(ARRAY(int, 1, 2, 3, 4, 5), 5, ARRAY(int, 4, 5, 3, 2, 1), 5));
    EXPECT_EQ_FALSE(validate_stack_sequences(ARRAY(int, 1, 2, 3, 4, 5), 5, ARRAY(int, 4, 3, 5, 1, 2), 5));
}

static void test_find_the_winner() {
    EXPECT_EQ_INT(3, find_the_winner(5, 2));
    EXPECT_EQ_INT(1, find_the_winner(6, 5));
}

static void test_find_middle_index() {
    int nums1[5] = {2, 3, -1, 8, 4};
    int nums2[3] = {1, -1, 4};
    int nums3[2] = {2, 5};
    EXPECT_EQ_INT(3, find_middle_index(nums1, 5));
    EXPECT_EQ_INT(2, find_middle_index(nums2, 3));
    EXPECT_EQ_INT(-1, find_middle_index(nums3, 2));
}

static void test_first_day_been_in_all_rooms() {
    int nums1[2] = {0, 0};
    int nums2[3] = {0, 0, 2};
    int nums3[4] = {0, 0, 1, 2};
    EXPECT_EQ_INT(2, first_day_been_in_all_rooms(nums1, 2));
    EXPECT_EQ_INT(6, first_day_been_in_all_rooms(nums2, 6));
    EXPECT_EQ_INT(6, first_day_been_in_all_rooms(nums3, 6));
}

static void test_recent_counter() {
    RecentCounter *obj = recentCounterCreate();
    EXPECT_EQ_INT(1, recentCounterPing(obj, 1));
    EXPECT_EQ_INT(2, recentCounterPing(obj, 100));
    EXPECT_EQ_INT(3, recentCounterPing(obj, 3001));
    EXPECT_EQ_INT(3, recentCounterPing(obj, 3002));
    recentCounterFree(obj);
}

static void test_minimum_moves() {
    EXPECT_EQ_INT(1, minimum_moves("XXX"));
    EXPECT_EQ_INT(2, minimum_moves("XXOX"));
    EXPECT_EQ_INT(0, minimum_moves("OOOO"));
}

static void test_min_moves_to_seat() {
    EXPECT_EQ_INT(4, min_moves_to_seat(ARRAY(int, 3, 1, 5), 3, ARRAY(int, 2, 7, 4), 3));
    EXPECT_EQ_INT(7, min_moves_to_seat(ARRAY(int, 4, 1, 5, 9), 4, ARRAY(int, 1, 3, 2, 6), 4));
    EXPECT_EQ_INT(4, min_moves_to_seat(ARRAY(int, 2, 2, 6, 6), 4, ARRAY(int, 1, 3, 2, 6), 4));
}

static void test_are_number_ascending() {
    EXPECT_EQ_TRUE(are_number_ascending("1 box has 3 blue 4 red 6 green and 12 yellow marbles"));
    EXPECT_EQ_FALSE(are_number_ascending("hello world 5 x 5"));
    EXPECT_EQ_FALSE(are_number_ascending("sunset is at 7 51 pm overnight lows will be in the low 50 and 60 s"));
}

static void test_count_even() {
    EXPECT_EQ_INT(2, count_even(4));
    EXPECT_EQ_INT(14, count_even(30));
}

static void test_repeated_character() {
    EXPECT_EQ_CHAR('c', repeated_character("abccbaacz"));
    EXPECT_EQ_CHAR('d', repeated_character("abcdd"));
    EXPECT_EQ_CHAR('a', repeated_character("aa"));
    EXPECT_EQ_CHAR('z', repeated_character("zz"));
}

static void test_solution() {
    test_two_sum();
    test_add_two_numbers();
    test_remove_element();
    test_remove_duplicates();
    test_search();
    test_rotate();
    test_merge();
    test_is_same_tree();
    test_reverse_list();
    test_count_numbers_with_unique_digits();
    test_lexical_order();
    test_find_substring_in_wraparoundString();
    test_find_diagonal_order();
    test_find_longest_chain();
    test_find_closest_elements();
    test_construct_array();
    test_maximum_swap();
    test_self_dividing_numbers();
    test_next_greatest_letter();
    test_max_chunks_to_sorted();
    test_can_transform();
    test_preimage_size_fzf();
    test_min_swap();
    test_unique_morse_representations();
    test_number_of_lines();
    test_unique_letter_string();
    test_score_of_parentheses();
    test_advantage_count();
    test_projection_area();
    test_sort_array_by_parity();
    test_partition_disjoint();
    test_min_add_to_make_valid();
    test_three_equal_parts();
    test_distinct_subseq_ii();
    test_di_string_match();
    test_min_deletion_size();
    test_validate_stack_sequences();
    test_is_alien_sorted();
    test_defanging_IPadd();
    test_min_subsequence();
    test_string_matching();
    test_busy_student();
    test_is_prefix_of_word();
    test_can_be_equal();
    test_max_product();
    test_shuffle();
    test_final_prices();
    test_num_special();
    test_reorder_spaces();
    test_min_operations();
    test_special_array();
    test_trim_mean();
    test_max_length_between_equal_characters();
    test_min_operations_2();
    test_maximum_wealth();
    test_reformat_number();
    test_minimum_length();
    test_merge_alternately();
    test_nearest_valid_point();
    test_check_ones_segment();
    test_ara_almost_equal();
    test_max_ascending_sum();
    test_find_the_winner();
    test_find_middle_index();
    test_recent_counter();
    test_minimum_moves();
    test_min_moves_to_seat();
    test_are_number_ascending();
    test_count_even();
    test_repeated_character();
}

static void test_is_flipped_string() {
    EXPECT_EQ_TRUE(is_flipped_string("waterbottle", "erbottlewat"));
    EXPECT_EQ_FALSE(is_flipped_string("aa", "aba"));
}

static void test_get_kth_magic_number() {
    EXPECT_EQ_INT(get_kth_magic_number(5), 9);
}

static void test_interview_solution() {
    test_is_flipped_string();
    test_get_kth_magic_number();
}

int main() {
    test_solution();
    test_interview_solution();
    printf("%d/%d (%3.2f%%) passed\n", test_pass, test_count, test_pass * 100.0 / test_count);
    return main_ret;
}
