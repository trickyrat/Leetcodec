#include <setjmp.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <cmocka.h>

#include "utils.h"
#include "atm.h"
#include "interview_solution.h"
#include "recent_counter.h"
#include "solution.h"

static void test_two_sum() {
    // Arrange
    int actual_return_size1 = 0;
    int actual_return_size2 = 0;
    int actual_return_size3 = 0;

    // Action
    int *actual1 = two_sum(ARRAY(int, 2, 7, 11, 15), 4, 9, &actual_return_size1);
    int *actual2 = two_sum(ARRAY(int, 3, 2, 4), 3, 6, &actual_return_size2);
    int *actual3 = two_sum(ARRAY(int, 3, 3), 2, 6, &actual_return_size3);

    // Assertion
    assert_true(compare_array(ARRAY(int, 0, 1), actual1, actual_return_size1));
    assert_true(compare_array(ARRAY(int, 1, 2), actual2, actual_return_size2));
    assert_true(compare_array(ARRAY(int, 0, 1), actual3, actual_return_size3));

    // Release resources
    free(actual1);
    free(actual2);
    free(actual3);
}

static void test_add_two_numbers() {
    // Arranges
    ListNode *input1_l1 = create_list_node(ARRAY(int, 2, 4, 3), 3);
    ListNode *input1_l2 = create_list_node(ARRAY(int, 5, 6, 4), 3);
    ListNode *input2_l1 = create_list_node(ARRAY(int, 0), 1);
    ListNode *input2_l2 = create_list_node(ARRAY(int, 0), 1);
    ListNode *input3_l1 = create_list_node(ARRAY(int, 9, 9, 9, 9, 9, 9, 9), 7);
    ListNode *input3_l2 = create_list_node(ARRAY(int, 9, 9, 9, 9), 4);

    ListNode *expected1 = create_list_node(ARRAY(int, 7, 0, 8), 3);
    ListNode *expected2 = create_list_node(ARRAY(int, 0), 1);
    ListNode *expected3 = create_list_node(ARRAY(int, 8, 9, 9, 9, 0, 0, 0, 1), 8);

    // Action
    ListNode *actual1 = add_two_numbers(input1_l1, input1_l2);
    ListNode *actual2 = add_two_numbers(input2_l1, input2_l2);
    ListNode *actual3 = add_two_numbers(input3_l1, input3_l2);

    // Assertion
    assert_true(is_same_list_node(actual1, expected1));
    assert_true(is_same_list_node(actual2, expected2));
    assert_true(is_same_list_node(actual3, expected3));

    // Release resources
    free(input1_l1);
    free(input1_l2);
    free(input2_l1);
    free(input2_l2);
    free(input3_l1);
    free(input3_l2);
    free(actual1);
    free(actual2);
    free(actual3);
    free(expected1);
    free(expected2);
    free(expected3);
}

static void test_remove_element() {
    // Arrange
    int *nums1 = ARRAY(int, 3, 2, 2, 3);
    int *nums2 = ARRAY(int, 0, 1, 2, 2, 3, 0, 4, 2);

    // Action
    int actual1 = remove_element(nums1, 4, 3);
    int actual2 = remove_element(nums2, 8, 2);

    // Assertion
    assert_int_equal(actual1, 2);
    assert_int_equal(actual2, 5);
}

static void test_remove_duplicates() {
    assert_int_equal(remove_duplicates(ARRAY(int, 1, 1, 2), 3), 2);
    assert_int_equal(remove_duplicates(ARRAY(int, 0, 0, 1, 1, 1, 2, 2, 3, 3, 4), 10), 5);
}

static void test_search() {
    assert_int_equal(4, search(ARRAY(int, 4, 5, 6, 7, 0, 1, 2), 7, 0));
}

static void test_rotate_image() {
    // Arrange
    int nums1[9] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    int nums2[16] = {5, 1, 9, 11, 2, 4, 8, 10, 13, 3, 6, 7, 15, 14, 12, 16};
    int **matrix1 = generate_matrix(nums1, 3, 3);
    int **matrix2 = generate_matrix(nums2, 4, 4);
    int matrix_col_size1 = 3;
    int matrix_col_size2 = 4;

    int expected_num1[9] = {7, 4, 1, 8, 5, 2, 9, 6, 3};
    int expected_num2[16] = {15, 13, 2, 5, 14, 3, 4, 1, 12, 6, 8, 9, 16, 7, 10, 11};

    int **expected1 = generate_matrix(expected_num1, 3, 3);
    int **expected2 = generate_matrix(expected_num2, 4, 4);

    // Action
    rotate_image(matrix1, 3, &matrix_col_size1);
    rotate_image(matrix2, 4, &matrix_col_size2);

    // Assertion
    assert_true(compare_2d_array(expected1, matrix1, 3, 3));
    assert_true(compare_2d_array(expected2, matrix2, 4, 4));
}

static void test_merge() {
    int actual1[6] = {1, 2, 3, 0, 0, 0};
    int nums2[3] = {2, 5, 6};
    merge(actual1, 6, 3, nums2, 3, 3);
    int expected1[6] = {1, 2, 2, 3, 5, 6};
    assert_memory_equal(expected1, actual1, 6);

    int actual2[1] = {1};
    int nums3[1];
    merge(actual2, 1, 1, nums3, 0, 0);
    int expected2[1] = {1};
    assert_memory_equal(expected2, actual2, 1);

    int actual3[1] = {0};
    int nums4[1] = {1};
    merge(actual3, 0, 0, nums4, 1, 1);
    int expected3[1] = {1};
    assert_memory_equal(expected3, actual3, 1);
};

static void test_is_same_tree() {
    TreeNode left1 = {2, NULL, NULL};
    TreeNode right1 = {3, NULL, NULL};
    TreeNode root1 = {1, &left1, &right1};
    TreeNode left2 = {2, NULL, NULL};
    TreeNode right2 = {3, NULL, NULL};
    TreeNode root2 = {1, &left2, &right2};
    assert_true(is_same_tree(&root1, &root2));
    assert_true(is_same_tree(NULL, NULL));
    assert_false(is_same_tree(&root1, NULL));
    assert_false(is_same_tree(NULL, &root1));
}

static void test_reverse_list() {
    ListNode *head1 = create_list_node(ARRAY(int, 1, 2, 3, 4, 5), 5);
    ListNode *actual1 = reverse_list(head1);
    ListNode *expected1 = create_list_node(ARRAY(int, 5, 4, 3, 2, 1), 5);
    assert_true(is_same_list_node(actual1, expected1));
}

static void test_is_valid_serialization() {
    assert_true(is_valid_serialization("9,3,4,#,#,1,#,#,2,#,6,#,#"));
    assert_false(is_valid_serialization("1,#"));
    assert_false(is_valid_serialization("9,#,#,1"));
}

static void test_count_numbers_with_unique_digits() {
    assert_int_equal(91, count_numbers_with_unique_digits(2));
    assert_int_equal(1, count_numbers_with_unique_digits(0));
}

static void test_lexical_order() {
    int expect1[13] = {1, 10, 11, 12, 13, 2, 3, 4, 5, 6, 7, 8, 9};
    int returnSize1 = 0;
    int *actual1 = lexical_order(13, &returnSize1);
    assert_memory_equal(expect1, actual1, returnSize1);

    int expect2[2] = {1, 2};
    int returnSize2 = 0;
    int *actual2 = lexical_order(2, &returnSize2);
    assert_memory_equal(expect2, actual2, returnSize2);
}

static void test_find_substring_in_wraparound_string() {
    assert_int_equal(1, find_substring_in_wraparound_string("a"));
    assert_int_equal(2, find_substring_in_wraparound_string("cac"));
    assert_int_equal(6, find_substring_in_wraparound_string("zab"));
}

static void test_find_diagonal_order() {
    int nums1[9] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    int nums2[4] = {1, 2, 3, 4};
    int **matrix1 = generate_matrix(nums1, 3, 3);
    int **matrix2 = generate_matrix(nums2, 2, 2);
    int matrix1_cos_size = 3;
    int matrix2_cos_size = 2;

    int matrix1_return_size = 0;
    int matrix2_return_size = 0;

    int expected1[9] = {1, 2, 4, 7, 5, 3, 6, 8, 9};
    int expected2[4] = {1, 2, 3, 4};

    int *actual1 = find_diagonal_order(matrix1, 3, &matrix1_cos_size, &matrix1_return_size);
    int *actual2 = find_diagonal_order(matrix2, 2, &matrix2_cos_size, &matrix2_return_size);

    assert_true(compare_array(expected1, actual1, 9));
    assert_true(compare_array(expected2, actual2, 4));


    free(actual1);
    free(actual2);
}

static void test_find_longest_chain() {
    int **pairs1 = initialize_matrix(ARRAY(int, 1, 2, 2, 3, 3, 4), 3, 2);
    int **pairs2 = initialize_matrix(ARRAY(int, 1, 2, 7, 8, 4, 5), 3, 2);
    int pairsColSize1 = 2;
    int pairsColSize2 = 2;
    assert_int_equal(2, find_longest_chain(pairs1, 3, &pairsColSize1));
    assert_int_equal(3, find_longest_chain(pairs2, 3, &pairsColSize2));
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
    assert_memory_equal(expect1, actual1, returnSize1);
    assert_memory_equal(expect2, actual2, returnSize2);
}

//static void test_width_of_binary_tree() {
//    // TODO
//}
//
static void test_construct_array() {
    int returnSize1 = 0;
    int returnSize2 = 0;
    int *actual1 = construct_array(3, 1, &returnSize1);
    int *actual2 = construct_array(3, 2, &returnSize2);
    assert_memory_equal(ARRAY(int, 1, 2, 3), actual1, returnSize1);
    assert_memory_equal(ARRAY(int, 1, 3, 2), actual2, returnSize2);
}

//static void test_trim_bst() {
//}

static void test_maximum_swap() {
    assert_int_equal(7236, maximum_swap(2736));
    assert_int_equal(9973, maximum_swap(9973));
}

//static void test_longest_univalue_path() {
//    // TODO
//}

static void test_self_dividing_numbers() {
    int returnSize1 = 0;
    int *actual1 = self_dividing_numbers(1, 22, &returnSize1);
    int expect1[13] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 11, 12, 15, 22};
    assert_memory_equal(expect1, actual1, returnSize1);
}

static void test_next_greatest_letter() {
    char letters[3] = {'c', 'f', 'j'};
    assert_int_equal('c', next_greatest_letter(letters, 3, 'a'));
    assert_int_equal('f', next_greatest_letter(letters, 3, 'c'));
    assert_int_equal('f', next_greatest_letter(letters, 3, 'c'));
}

static void test_max_chunks_to_sorted() {
    assert_int_equal(1, max_chunks_to_sorted(ARRAY(int, 4, 3, 2, 1, 0), 5));
    assert_int_equal(4, max_chunks_to_sorted(ARRAY(int, 1, 0, 2, 3, 4), 5));
}

static void test_can_transform() {
    bool actual1 = can_transform("RXXLRXRXL", "XRLXXRRLX");
    bool actual2 = can_transform("X", "L");
    assert_true(actual1);
    assert_false(actual2);
}

static void test_preimage_size_fzf() {
    assert_int_equal(5, preimage_size_fzf(0));
    assert_int_equal(0, preimage_size_fzf(5));
    assert_int_equal(5, preimage_size_fzf(3));
}

static void test_min_swap() {
    assert_int_equal(1, min_swap(ARRAY(int, 1, 3, 5, 4), 4, ARRAY(int, 1, 2, 3, 7), 4));
    assert_int_equal(1, min_swap(ARRAY(int, 0, 3, 5, 8, 9), 5, ARRAY(int, 2, 1, 4, 6, 9), 5));
}

static void test_unique_morse_representations() {
    char *words1[] = {"gin", "zen", "gig", "msg"};
    char *words2[] = {"a"};
    assert_int_equal(2, unique_morse_representations(words1, 4));
    assert_int_equal(1, unique_morse_representations(words2, 1));
}

static void test_number_of_lines() {
    int widths1[26] = {10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10,
                       10, 10};
    int widths2[26] = {4, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10,
                       10, 10};
    char *s1 = "abcdefghijklmnopqrstuvwxyz";
    char *s2 = "bbbcccdddaaa";
    int returnSize1 = 0;
    int returnSize2 = 0;
    int widths_size = 26;
    int expected1[2] = {3, 60};
    int expected2[2] = {2, 4};

    int *actual1 = number_of_lines(widths1, widths_size, s1, &returnSize1);
    int *actual2 = number_of_lines(widths2, widths_size, s2, &returnSize2);

    assert_memory_equal(expected1, actual1, returnSize1);
    assert_memory_equal(expected2, actual2, returnSize2);
}

static void test_unique_letter_string() {
    char *s1 = "ABC";
    char *s2 = "ABA";
    char *s3 = "LEETCODE";
    assert_int_equal(10, unique_letter_string(s1));
    assert_int_equal(8, unique_letter_string(s2));
    assert_int_equal(92, unique_letter_string(s3));
}

static void test_score_of_parentheses() {
    assert_int_equal(1, score_of_parentheses("()"));
    assert_int_equal(2, score_of_parentheses("(())"));
    assert_int_equal(2, score_of_parentheses("()()"));
}

static void test_advantage_count() {
    int returnSize1 = 0;
    int returnSize2 = 0;
    int *actual1 = advantage_count(ARRAY(int, 2, 7, 11, 15), 4, ARRAY(int, 1, 10, 4, 11), 4, &returnSize1);
    int *actual2 = advantage_count(ARRAY(int, 12, 24, 8, 32), 4, ARRAY(int, 13, 25, 32, 11), 4, &returnSize2);
    assert_memory_equal(ARRAY(int, 2, 11, 7, 15), actual1, returnSize1);
    assert_memory_equal(ARRAY(int, 24, 32, 8, 12), actual2, returnSize2);
}

static void test_is_alien_sorted() {
    char *words1[2] = {"hello", "leetcode"};
    char *words2[3] = {"word", "world", "row"};
    char *words3[2] = {"apple", "app"};
    char *order1 = "hlabcdefgijkmnopqrstuvwxyz";
    char *order2 = "worldabcefghijkmnpqstuvxyz";
    char *order3 = "abcdefghijklmnopqrstuvwxyz";
    assert_true(is_alien_sorted(words1, 2, order1));
    assert_false(is_alien_sorted(words2, 3, order2));
    assert_false(is_alien_sorted(words3, 2, order3));
}

static void test_defanging_ip_addr() {
    assert_string_equal("1[.]1[.]1[.]1", defang_ip_addr("1.1.1.1"));
    assert_string_equal("255[.]100[.]50[.]0", defang_ip_addr("255.100.50.0"));
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
    assert_memory_equal(expected1, actual1, returnSize1);
    assert_memory_equal(expected2, actual2, returnSize2);
    assert_memory_equal(expected3, actual3, returnSize3);
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
    assert_memory_equal(expected1, actual1, returnSize1);
    assert_memory_equal(expected2, actual2, returnSize2);
    assert_memory_equal(expected3, actual3, returnSize3);
}

static void test_busy_student() {
    int startTimes1[3] = {1, 2, 3};
    int endTimes1[3] = {3, 2, 7};
    int startTimes2[1] = {4};
    int endTimes2[1] = {4};
    assert_int_equal(busy_student(startTimes1, 3, endTimes1, 3, 4), 1);
    assert_int_equal(busy_student(startTimes2, 1, endTimes2, 1, 4), 1);
}

static void test_is_prefix_of_word() {
    char *sentence1 = "i love eating burger";
    char *sentence2 = "this problem is an easy problem";
    char *sentence3 = "i am tired";
    char *searchWord1 = "burg";
    char *searchWord2 = "pro";
    char *searchWord3 = "you";
    assert_int_equal(4, is_prefix_of_word(sentence1, searchWord1));
    assert_int_equal(2, is_prefix_of_word(sentence2, searchWord2));
    assert_int_equal(-1, is_prefix_of_word(sentence3, searchWord3));
}

static void test_can_be_equal() {
    int target1[] = {1, 2, 3, 4};
    int target2[] = {7};
    int target3[] = {3, 7, 9};
    int arr1[] = {2, 1, 3, 4};
    int arr2[] = {7};
    int arr3[] = {3, 7, 11};
    assert_true(can_be_equal(target1, 4, arr1, 4));
    assert_true(can_be_equal(target2, 1, arr2, 1));
    assert_false(can_be_equal(target3, 3, arr3, 3));
}

static void test_max_product() {
    int nums1[] = {3, 4, 5, 2};
    int nums2[] = {1, 5, 4, 5};
    int nums3[] = {3, 7};
    assert_int_equal(12, max_product(nums1, 4));
    assert_int_equal(16, max_product(nums2, 4));
    assert_int_equal(12, max_product(nums3, 2));
}

static void test_num_special() {
    int **mat1 = initialize_matrix(ARRAY(int, 1, 0, 0, 0, 0, 1, 1, 0, 0), 3, 3);
    int **mat2 = initialize_matrix(ARRAY(int, 1, 0, 0, 0, 1, 0, 0, 0, 1), 3, 3);
    int matColSize1 = 3;
    int matColSize2 = 3;
    assert_int_equal(1, num_special(mat1, 3, &matColSize1));
    assert_int_equal(3, num_special(mat2, 3, &matColSize2));
}

static void test_reorder_spaces() {
    const char *actual1 = reorder_spaces("  this   is  a sentence ");
    const char *actual2 = reorder_spaces(" practice   makes   perfect");

    assert_string_equal("this   is   a   sentence", actual1);
    assert_string_equal("practice   makes   perfect ", actual2);
}

static void test_min_operations() {
    char *logs1[5] = {"d1/", "d2/", "../", "d21/", "./"};
    char *logs2[6] = {"d1/", "d2/", "./", "d3/", "../", "d31/"};
    char *logs3[4] = {"d1/", "../", "../", "../"};
    assert_int_equal(2, min_operations(logs1, 5));
    assert_int_equal(3, min_operations(logs2, 6));
    assert_int_equal(0, min_operations(logs3, 4));
}

static void test_special_array() {
    assert_int_equal(2, special_array(ARRAY(int, 3, 5), 2));
    assert_int_equal(-1, special_array(ARRAY(int, 0, 0), 2));
    assert_int_equal(3, special_array(ARRAY(int, 0, 4, 3, 0, 4), 5));
}

static void test_trim_mean() {
    assert_true((trim_mean(ARRAY(int, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 3), 20) - 2.00000) <= 0.00001);
    assert_true((trim_mean(ARRAY(int, 6, 2, 7, 5, 1, 2, 0, 3, 10, 2, 5, 0, 5, 5, 0, 8, 7, 6, 8, 0), 20) - 4.00000) <= 0.00001);
    assert_true((trim_mean(ARRAY(int, 6, 0, 7, 0, 7, 5, 7, 8, 3, 4, 0, 7, 8, 1, 6, 8, 1, 1, 2, 4, 8, 1, 9, 5, 4, 3, 8, 5, 10, 8, 6, 6, 1, 0, 6, 10, 8, 2, 3, 4), 40) - 4.77778) <= 0.00001);
}

static void test_max_length_between_equal_characters() {
    assert_int_equal(0, max_length_between_equal_characters("aa"));
    assert_int_equal(2, max_length_between_equal_characters("abca"));
    assert_int_equal(-1, max_length_between_equal_characters("cbyzx"));
}

static void test_min_operations_2() {
    assert_int_equal(2, min_operations_2(ARRAY(int, 1, 1, 4, 2, 3), 5, 5));
    assert_int_equal(-1, min_operations_2(ARRAY(int, 5, 6, 7, 8, 9), 5, 4));
    assert_int_equal(5, min_operations_2(ARRAY(int, 3, 2, 20, 1, 1, 3), 6, 10));
}

static void test_maximum_wealth() {
    int nums1[6] = {1, 2, 3, 3, 2, 1};
    int nums2[6] = {1, 5, 7, 3, 3, 5};
    int nums3[9] = {2, 8, 7, 7, 1, 3, 1, 9, 5};

    int **accounts_array1 = generate_matrix(nums1, 2, 3);
    int **accounts_array2 = generate_matrix(nums2, 3, 2);
    int **accounts_array3 = generate_matrix(nums3, 3, 3);

    int accounts_array1_col_size = 3;
    int accounts_array2_col_size = 2;
    int accounts_array3_col_size = 3;

    assert_int_equal(maximum_wealth(accounts_array1, 2, &accounts_array1_col_size), 6);
    assert_int_equal(maximum_wealth(accounts_array2, 3, &accounts_array2_col_size), 10);
    assert_int_equal(maximum_wealth(accounts_array3, 3, &accounts_array3_col_size), 17);
}

static void test_reformat_number() {
    assert_string_equal("123-456", reformat_number("1-23-45 6"));
    assert_string_equal("123-45-67", reformat_number("123 4-567"));
    assert_string_equal("123-456-78", reformat_number("123 4-5678"));
}

static void test_minimum_length() {
    assert_int_equal(2, minimum_length("ca"));
    assert_int_equal(0, minimum_length("cabaabac"));
    assert_int_equal(3, minimum_length("aabccabba"));
}

static void test_merge_alternately() {
    assert_string_equal("apbqcr", merge_alternately("abc", "pqr"));
    assert_string_equal("apbqrs", merge_alternately("ab", "pqrs"));
    assert_string_equal("apbqcd", merge_alternately("abcd", "pq"));
}

static void test_nearest_valid_point() {
}

static void test_check_ones_segment() {
    assert_false(check_ones_segment("1001"));
    assert_true(check_ones_segment("110"));
}

static void test_ara_almost_equal() {
    assert_true(are_almost_equal("bank", "kanb"));
    assert_false(are_almost_equal("attack", "defend"));
    assert_true(are_almost_equal("kelb", "kelb"));
}

static void test_max_ascending_sum() {
    assert_int_equal(65, max_ascending_sum(ARRAY(int, 10, 20, 30, 5, 10, 50), 6));
    assert_int_equal(150, max_ascending_sum(ARRAY(int, 10, 20, 30, 40, 50), 5));
    assert_int_equal(33, max_ascending_sum(ARRAY(int, 12, 17, 15, 13, 10, 11, 12), 7));
}

static void test_shuffle() {
    int returnSize1 = 0;
    int returnSize2 = 0;
    int returnSize3 = 0;
    int *actual1 = shuffle(ARRAY(int, 2, 5, 1, 3, 4, 7), 6, 3, &returnSize1);
    int *actual2 = shuffle(ARRAY(int, 1, 2, 3, 4, 4, 3, 2, 1), 8, 4, &returnSize2);
    int *actual3 = shuffle(ARRAY(int, 1, 1, 2, 2), 4, 2, &returnSize3);
    assert_memory_equal(ARRAY(int, 2, 3, 5, 4, 1, 7), actual1, returnSize1);
    assert_memory_equal(ARRAY(int, 1, 4, 2, 3, 3, 2, 4, 1), actual2, returnSize2);
    assert_memory_equal(ARRAY(int, 1, 2, 1, 2), actual3, returnSize3);
}

static void test_final_prices() {
    int returnSize1 = 0;
    int returnSize2 = 0;
    int returnSize3 = 0;
    int *actual1 = final_prices(ARRAY(int, 8, 4, 6, 2, 3), 5, &returnSize1);
    int *actual2 = final_prices(ARRAY(int, 1, 2, 3, 4, 5), 5, &returnSize2);
    int *actual3 = final_prices(ARRAY(int, 10, 1, 1, 6), 4, &returnSize3);
    assert_memory_equal(ARRAY(int, 4, 2, 4, 2, 3), actual1, returnSize1);
    assert_memory_equal(ARRAY(int, 1, 2, 3, 4, 5), actual2, returnSize2);
    assert_memory_equal(ARRAY(int, 9, 0, 1, 6), actual3, returnSize3);
}

static void test_projection_area() {
    int nums1[4] = {1, 2, 3, 4};// 2*2
    int nums2[1] = {2};         // 1*1
    int nums3[4] = {1, 0, 0, 2};// 2*2

    int **grid1 = generate_matrix(nums1, 2, 2);
    int **grid2 = generate_matrix(nums2, 1, 1);
    int **grid3 = generate_matrix(nums3, 2, 2);

    int grid1_col_size = 2;
    int grid2_col_size = 1;
    int grid3_col_size = 2;

    assert_int_equal(projection_area(grid1, 2, &grid1_col_size), 17);
    assert_int_equal(projection_area(grid2, 1, &grid2_col_size), 5);
    assert_int_equal(projection_area(grid3, 2, &grid3_col_size), 8);
}

static void test_sort_array_by_parity() {
    int returnSize1 = 0;
    int returnSize2 = 0;
    int *actual1 = sort_array_by_parity(ARRAY(int, 3, 1, 2, 4), 4, &returnSize1);
    int *actual2 = sort_array_by_parity(ARRAY(int, 0), 1, &returnSize2);
    assert_memory_equal(ARRAY(int, 4, 2, 1, 3), actual1, returnSize1);
    assert_memory_equal(ARRAY(int, 0), actual2, returnSize2);
}

static void test_partition_disjoint() {
    assert_int_equal(3, partition_disjoint(ARRAY(int, 5, 0, 3, 8, 6), 5));
    assert_int_equal(4, partition_disjoint(ARRAY(int, 1, 1, 1, 0, 6, 12), 6));
}

static void test_min_add_to_make_valid() {
    assert_int_equal(1, min_add_to_make_valid("())"));
    assert_int_equal(3, min_add_to_make_valid("((("));
}

static void test_three_equal_parts() {
    int returnSize1 = 0;
    int returnSize2 = 0;
    int returnSize3 = 0;
    int *actual1 = three_equal_parts(ARRAY(int, 1, 0, 1, 0, 1), 5, &returnSize1);
    int *actual2 = three_equal_parts(ARRAY(int, 1, 1, 0, 1, 1), 5, &returnSize2);
    int *actual3 = three_equal_parts(ARRAY(int, 1, 1, 0, 0, 1), 5, &returnSize3);
    assert_memory_equal(ARRAY(int, 0, 3), actual1, returnSize1);
    assert_memory_equal(ARRAY(int, -1, -1), actual2, returnSize2);
    assert_memory_equal(ARRAY(int, 0, 2), actual3, returnSize3);
}

static void test_distinct_sub_seq_ii() {
    assert_int_equal(7, distinct_sub_seq_ii("abc"));
    assert_int_equal(6, distinct_sub_seq_ii("aba"));
    assert_int_equal(3, distinct_sub_seq_ii("aaa"));
}

static void test_di_string_match() {
    int returnSize1 = 0;
    int returnSize2 = 0;
    int returnSize3 = 0;
    int *actual1 = di_string_match("IDID", &returnSize1);
    int *actual2 = di_string_match("III", &returnSize2);
    int *actual3 = di_string_match("DDI", &returnSize3);
    assert_memory_equal(ARRAY(int, 0, 4, 1, 3, 2), actual1, returnSize1);
    assert_memory_equal(ARRAY(int, 0, 1, 2, 3), actual2, returnSize2);
    assert_memory_equal(ARRAY(int, 3, 2, 0, 1), actual3, returnSize3);
}

static void test_min_deletion_size() {
    assert_int_equal(1, min_deletion_size(ARRAY(char *, "cba", "daf", "ghi"), 3));
    assert_int_equal(0, min_deletion_size(ARRAY(char *, "a", "b"), 2));
    assert_int_equal(3, min_deletion_size(ARRAY(char *, "zyx", "wvu", "tsr"), 3));
}

static void test_validate_stack_sequences() {
    assert_true(validate_stack_sequences(ARRAY(int, 1, 2, 3, 4, 5), 5, ARRAY(int, 4, 5, 3, 2, 1), 5));
    assert_false(validate_stack_sequences(ARRAY(int, 1, 2, 3, 4, 5), 5, ARRAY(int, 4, 3, 5, 1, 2), 5));
}

static void test_find_the_winner() {
    assert_int_equal(3, find_the_winner(5, 2));
    assert_int_equal(1, find_the_winner(6, 5));
}

static void test_find_middle_index() {
    int nums1[5] = {2, 3, -1, 8, 4};
    int nums2[3] = {1, -1, 4};
    int nums3[2] = {2, 5};
    assert_int_equal(3, find_middle_index(nums1, 5));
    assert_int_equal(2, find_middle_index(nums2, 3));
    assert_int_equal(-1, find_middle_index(nums3, 2));
}

static void test_first_day_been_in_all_rooms() {
    assert_int_equal(2, first_day_been_in_all_rooms(ARRAY(int, 0, 0), 2));
    assert_int_equal(6, first_day_been_in_all_rooms(ARRAY(int, 0, 0, 2), 3));
    assert_int_equal(6, first_day_been_in_all_rooms(ARRAY(int, 0, 1, 2, 0), 4));
}

static void test_recent_counter() {
    RecentCounter *counter = recent_counter_create();
    assert_int_equal(1, recent_counter_ping(counter, 1));
    assert_int_equal(2, recent_counter_ping(counter, 100));
    assert_int_equal(3, recent_counter_ping(counter, 3001));
    assert_int_equal(3, recent_counter_ping(counter, 3002));
    recent_counter_free(counter);
}

static void test_minimum_moves() {
    assert_int_equal(1, minimum_moves("XXX"));
    assert_int_equal(2, minimum_moves("XXOX"));
    assert_int_equal(0, minimum_moves("OOOO"));
}

static void test_min_moves_to_seat() {
    assert_int_equal(4, min_moves_to_seat(ARRAY(int, 3, 1, 5), 3, ARRAY(int, 2, 7, 4), 3));
    assert_int_equal(7, min_moves_to_seat(ARRAY(int, 4, 1, 5, 9), 4, ARRAY(int, 1, 3, 2, 6), 4));
    assert_int_equal(4, min_moves_to_seat(ARRAY(int, 2, 2, 6, 6), 4, ARRAY(int, 1, 3, 2, 6), 4));
}

static void test_are_number_ascending() {
    assert_true(are_number_ascending("1 box has 3 blue 4 red 6 green and 12 yellow marbles"));
    assert_false(are_number_ascending("hello world 5 x 5"));
    assert_false(are_number_ascending("sunset is at 7 51 pm overnight lows will be in the low 50 and 60 s"));
}

static void test_count_even() {
    assert_int_equal(2, count_even(4));
    assert_int_equal(14, count_even(30));
}

static void test_repeated_character() {
    assert_int_equal('c', repeated_character("abccbaacz"));
    assert_int_equal('d', repeated_character("abcdd"));
    assert_int_equal('a', repeated_character("aa"));
    assert_int_equal('z', repeated_character("zz"));
}

static void test_maximum_count() {
    assert_int_equal(3, maximum_count(ARRAY(int, -2, -1, -1, 1, 2, 3), 6));
    assert_int_equal(3, maximum_count(ARRAY(int, -3, -2, -1, 0, 0, 1, 2), 7));
    assert_int_equal(4, maximum_count(ARRAY(int, 5, 20, 66, 1314), 4));
}

static void test_minimum_sum() {
    assert_int_equal(9, minimum_sum(ARRAY(int, 8, 6, 1, 5, 3), 5));
    assert_int_equal(13, minimum_sum(ARRAY(int, 5, 4, 8, 7, 10, 2), 6));
    assert_int_equal(-1, minimum_sum(ARRAY(int, 6, 5, 4, 3, 4, 5), 6));
}

static void test_minimum_added_coins() {
    assert_int_equal(2, minimum_added_coins(ARRAY(int, 1, 4, 10), 3, 19));
    assert_int_equal(1, minimum_added_coins(ARRAY(int, 1, 4, 10, 5, 7, 19), 6, 19));
    assert_int_equal(3, minimum_added_coins(ARRAY(int, 1, 1, 1), 3, 20));
}

static int test_solution() {
    const struct CMUnitTest solution_tests[] = {
            cmocka_unit_test(test_two_sum),
            cmocka_unit_test(test_add_two_numbers),
            cmocka_unit_test(test_remove_element),
            cmocka_unit_test(test_remove_duplicates),
            cmocka_unit_test(test_search),
            cmocka_unit_test(test_rotate_image),
            cmocka_unit_test(test_merge),
            cmocka_unit_test(test_is_same_tree),
            cmocka_unit_test(test_reverse_list),
            cmocka_unit_test(test_is_valid_serialization),
            cmocka_unit_test(test_count_numbers_with_unique_digits),
            cmocka_unit_test(test_lexical_order),
            cmocka_unit_test(test_find_diagonal_order),
            cmocka_unit_test(test_find_longest_chain),
            cmocka_unit_test(test_find_closest_elements),
            cmocka_unit_test(test_construct_array),
            cmocka_unit_test(test_maximum_swap),
            cmocka_unit_test(test_self_dividing_numbers),
            cmocka_unit_test(test_next_greatest_letter),
            cmocka_unit_test(test_max_chunks_to_sorted),
            cmocka_unit_test(test_can_transform),
            cmocka_unit_test(test_preimage_size_fzf),
            cmocka_unit_test(test_min_swap),
            cmocka_unit_test(test_unique_morse_representations),
            cmocka_unit_test(test_number_of_lines),
            cmocka_unit_test(test_unique_letter_string),
            cmocka_unit_test(test_score_of_parentheses),
            cmocka_unit_test(test_advantage_count),
            cmocka_unit_test(test_is_alien_sorted),
            cmocka_unit_test(test_defanging_ip_addr),
            cmocka_unit_test(test_min_subsequence),
            cmocka_unit_test(test_string_matching),
            cmocka_unit_test(test_busy_student),
            cmocka_unit_test(test_is_prefix_of_word),
            cmocka_unit_test(test_can_be_equal),
            cmocka_unit_test(test_max_product),
            cmocka_unit_test(test_num_special),
            cmocka_unit_test(test_reorder_spaces),
            cmocka_unit_test(test_min_operations),
            cmocka_unit_test(test_special_array),
            cmocka_unit_test(test_trim_mean),
            cmocka_unit_test(test_max_length_between_equal_characters),
            cmocka_unit_test(test_min_operations_2),
            cmocka_unit_test(test_maximum_wealth),
            cmocka_unit_test(test_reformat_number),
            cmocka_unit_test(test_minimum_length),
            cmocka_unit_test(test_merge_alternately),
            cmocka_unit_test(test_nearest_valid_point),
            cmocka_unit_test(test_check_ones_segment),
            cmocka_unit_test(test_ara_almost_equal),
            cmocka_unit_test(test_max_ascending_sum),
            cmocka_unit_test(test_shuffle),
            cmocka_unit_test(test_final_prices),
            cmocka_unit_test(test_projection_area),
            cmocka_unit_test(test_sort_array_by_parity),
            cmocka_unit_test(test_partition_disjoint),
            cmocka_unit_test(test_min_add_to_make_valid),
            cmocka_unit_test(test_three_equal_parts),
            cmocka_unit_test(test_distinct_sub_seq_ii),
            cmocka_unit_test(test_di_string_match),
            cmocka_unit_test(test_min_deletion_size),
            cmocka_unit_test(test_validate_stack_sequences),
            cmocka_unit_test(test_find_the_winner),
            cmocka_unit_test(test_find_middle_index),
            cmocka_unit_test(test_first_day_been_in_all_rooms),
            cmocka_unit_test(test_recent_counter),
            cmocka_unit_test(test_minimum_moves),
            cmocka_unit_test(test_min_moves_to_seat),
            cmocka_unit_test(test_are_number_ascending),
            cmocka_unit_test(test_count_even),
            cmocka_unit_test(test_repeated_character),
            cmocka_unit_test(test_maximum_count),
            cmocka_unit_test(test_minimum_sum),
            cmocka_unit_test(test_minimum_added_coins),
    };
    return cmocka_run_group_tests(solution_tests, NULL, NULL);
}

static void test_is_flipped_string() {
    assert_true(is_flipped_string("waterbottle", "erbottlewat"));
    assert_false(is_flipped_string("aa", "aba"));
}

static void test_get_kth_magic_number() {
    assert_int_equal(get_kth_magic_number(5), 9);
}

static int test_interview_solution() {
    const struct CMUnitTest interview_solution_tests[] = {
            cmocka_unit_test(test_is_flipped_string),
            cmocka_unit_test(test_get_kth_magic_number),
    };

    return cmocka_run_group_tests(interview_solution_tests, NULL, NULL);
}


static void test_atm_functionality() {
    ATM *atm = atm_create();
    atm_deposit(atm, ARRAY(int, 0, 0, 1, 2, 1), 5);
    int return_size = 0;
    int *actual1 = atm_withdraw(atm, 600, &return_size);
    assert_memory_equal(ARRAY(int, 0, 0, 1, 0, 1), actual1, 5);
    atm_deposit(atm, ARRAY(int, 0, 1, 0, 1, 1), 5);
    int *actual2 = atm_withdraw(atm, 600, &return_size);
    assert_memory_equal(ARRAY(int, -1), actual2, 1);
    int *actual3 = atm_withdraw(atm, 550, &return_size);
    assert_memory_equal(ARRAY(int, 0, 1, 0, 0, 1), actual3, 5);

    atm_free(atm);
}

static int test_atm() {
    const struct CMUnitTest atm_tests[] = {
            cmocka_unit_test(test_atm_functionality),
    };

    return cmocka_run_group_tests(atm_tests, NULL, NULL);
}


int main() {
    test_solution();
    test_interview_solution();
    test_atm();
    return 0;
}
