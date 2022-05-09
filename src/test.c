#include "recentcounter.h"
#include "solution.h"

#include <assert.h>
#include <stdio.h>

static int main_ret = 0;
static int test_count = 0;
static int test_pass = 0;

#define EXPECT_EQ_BASE(equality, expect, actual, format)                \
  do {                                                                  \
    test_count++;                                                       \
    if (equality) {                                                     \
      test_pass++;                                                      \
    } else {                                                            \
      fprintf(stderr, "%s:%d: expect: " format " actual: " format "\n", \
              __FILE__, __LINE__, expect, actual);                      \
    }                                                                   \
  } while (0)

#define EXPECT_EQ_INT(expect, actual) \
  EXPECT_EQ_BASE((expect) == (actual), expect, actual, "%d")

#define EXPECT_EQ_CHAR(expect, actual) \
  EXPECT_EQ_BASE((expect) == (actual), expect, actual, "%c")

#define EXPECT_EQ_TRUE(actual) \
  EXPECT_EQ_BASE(1 == (actual), 1, actual, "%d")

#define EXPECT_EQ_FALSE(actual) \
  EXPECT_EQ_BASE(0 == (actual), 0, actual, "%d")

#define EXPECT_EQ_STRING(expect, actual, length)              \
  EXPECT_EQ_BASE(sizeof(expect) - 1 == (length) &&            \
                         memcmp(expect, actual, length) == 0, \
                 expect, actual, "%s")

#define EXPECT_EQ_ARRAY(expect, expectedSize, actual, actualSize) \
  EXPECT_EQ_INT(expectedSize, actualSize);                        \
  for (int i = 0; i < (expectedSize); ++i) {                      \
    EXPECT_EQ_INT((expect)[i], (actual)[i]);                      \
  }

#define TEST_MATRIX_BASE(input_data, row_size) \
  int *mat[(row_size)];                        \
  for (int i = 0; i < (row_size); ++i) {       \
    mat[i] = (input_data)[i];                  \
  }

static void test_two_sum() {
  int nums[4] = {2, 7, 11, 15};
  int actualReturnSize = 0;
  int *actual = twoSum(nums, 4, 9, &actualReturnSize);
  int expect[2] = {0, 1};
  int expectedReturnSize = 2;
  EXPECT_EQ_ARRAY(expect, expectedReturnSize, actual, actualReturnSize)
}

static void test_remove_element() {
  int nums1[4] = {3, 2, 2, 3};
  int nums2[8] = {0, 1, 2, 2, 3, 0, 4, 2};
  EXPECT_EQ_INT(removeElement(nums1, 4, 3), 2);
  EXPECT_EQ_INT(removeElement(nums2, 8, 2), 5);
}

static void test_search() {
  int nums[7] = {4, 5, 6, 7, 0, 1, 2};
  EXPECT_EQ_INT(4, search(nums, 7, 0));
}

static void test_is_same_tree() {
  TreeNode left1 = {2, NULL, NULL};
  TreeNode right1 = {3, NULL, NULL};
  TreeNode root1 = {1, &left1, &right1};
  TreeNode left2 = {2, NULL, NULL};
  TreeNode right2 = {3, NULL, NULL};
  TreeNode root2 = {1, &left2, &right2};
  EXPECT_EQ_TRUE(isSameTree(&root1, &root2));
  EXPECT_EQ_TRUE(isSameTree(NULL, NULL));
  EXPECT_EQ_FALSE(isSameTree(&root1, NULL));
  EXPECT_EQ_FALSE(isSameTree(NULL, &root1));
}

static void test_count_numbers_with_unique_digits() {
  EXPECT_EQ_INT(91, countNumbersWithUniqueDigits(2));
  EXPECT_EQ_INT(1, countNumbersWithUniqueDigits(0));
}

static void test_lexical_order() {
  int expect1[13] = {1, 10, 11, 12, 13, 2, 3, 4, 5, 6, 7, 8, 9};
  int returnSize1 = 0;
  int *actual1 = lexicalOrder(13, &returnSize1);
  EXPECT_EQ_ARRAY(expect1, 13, actual1, returnSize1);

  int expect2[2] = {1, 2};
  int returnSize2 = 0;
  int *actual2 = lexicalOrder(2, &returnSize2);
  EXPECT_EQ_ARRAY(expect2, 2, actual2, returnSize2);
}

#define TEST_FIND_DIAGONAL_ORDER(input_data, row_size, col_size, expected, expected_size) \
  do {                                                                                    \
    TEST_MATRIX_BASE(input_data, row_size);                                               \
    int return_size = 0;                                                                  \
    int col = col_size;                                                                   \
    int *actual = findDiagonalOrder(mat, (row_size), &col, &return_size);                 \
    EXPECT_EQ_ARRAY(expected, expected_size, actual, return_size);                        \
  } while (0)

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

static void test_self_dividing_numbers() {
  int returnSize1 = 0;
  int *actual1 = selfDividingNumbers(1, 22, &returnSize1);
  int expect1[13] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 11, 12, 15, 22};
  EXPECT_EQ_ARRAY(expect1, 13, actual1, returnSize1)
}

static void test_next_greatest_letter() {
  char letters[3] = {'c', 'f', 'j'};
  EXPECT_EQ_CHAR('c', nextGreatestLetter(letters, 3, 'a'));
  EXPECT_EQ_CHAR('f', nextGreatestLetter(letters, 3, 'c'));
  EXPECT_EQ_CHAR('f', nextGreatestLetter(letters, 3, 'c'));
}

static void test_unique_morse_representations() {
  char *words1[] = {"gin", "zen", "gig", "msg"};
  char *words2[] = {"a"};
  EXPECT_EQ_INT(2, uniqueMorseRepresentations(words1, 4));
  EXPECT_EQ_INT(1, uniqueMorseRepresentations(words2, 1));
}

#define TEST_NUMBER_OF_LINES(widths, widths_size, s, expected, expected_size) \
  do {                                                                        \
    int return_size = 0;                                                      \
    int *ans = numberOfLines((widths), (widths_size), (s), &(return_size));   \
    EXPECT_EQ_ARRAY(expected, (expected_size), ans, (return_size));           \
  } while (0)

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


#define TEST_MATRIX_INT(function, input_data, row_size, col_size, expected) \
  do {                                                                      \
    TEST_MATRIX_BASE((input_data), (row_size));                             \
    int col_size_ = (col_size);                                             \
    EXPECT_EQ_INT((expected), function(mat, (row_size), &col_size_));       \
  } while (0)

static void test_maximum_wealth() {
  int accounts_array1[2][3] = {{1, 2, 3}, {3, 2, 1}};
  int accounts_array2[3][3] = {{1, 5}, {7, 3}, {3, 5}};
  int accounts_array3[3][3] = {{2, 8, 7}, {7, 1, 3}, {1, 9, 5}};
  TEST_MATRIX_INT(maximumWealth, accounts_array1, 2, 3, 6);
  TEST_MATRIX_INT(maximumWealth, accounts_array2, 3, 3, 10);
  TEST_MATRIX_INT(maximumWealth, accounts_array3, 3, 3, 17);
}

static void test_projection_area() {
  int grid1[2][2] = {{1, 2}, {3, 4}};
  int grid2[1][1] = {{2}};
  int grid3[2][2] = {{1, 0}, {0, 2}};
  TEST_MATRIX_INT(projectionArea, grid1, 2, 2, 17);
  TEST_MATRIX_INT(projectionArea, grid2, 1, 1, 5);
  TEST_MATRIX_INT(projectionArea, grid3, 2, 2, 8);
}

static void test_sort_array_by_parity() {
  int nums1[4] = {3, 1, 2, 4};
  int nums2[1] = {0};
  int returnSize1 = 0;
  int returnSize2 = 0;
  int expected1[4] = {4,2, 1, 3};
  int expected2[1] = {0};
  int* actual1 = sortArrayByParity(nums1, 4, &returnSize1);
  int* actual2 = sortArrayByParity(nums2, 1, &returnSize2);
  EXPECT_EQ_ARRAY(expected1, 4, actual1, returnSize1)
  EXPECT_EQ_ARRAY(expected2, 1, actual2, returnSize2)
}

static void test_di_string_match() {
  char *s1 = "IDID";
  char *s2 = "III";
  char *s3 = "DDI";
  int expected1[5] = {0, 4, 1, 3, 2};
  int expected2[4] = {0, 1, 2, 3 };
  int expected3[4] = {3, 2, 0, 1 };
  int returnSize1 = 0;
  int returnSize2 = 0;
  int returnSize3 = 0;
  int* actual1 = diStringMatch(s1, &returnSize1);
  int* actual2 = diStringMatch(s2, &returnSize2);
  int* actual3 = diStringMatch(s3, &returnSize3);
  EXPECT_EQ_ARRAY(expected1, 5, actual1, returnSize1);
  EXPECT_EQ_ARRAY(expected2, 4, actual2, returnSize2);
  EXPECT_EQ_ARRAY(expected3, 4, actual3, returnSize3);
}

static void test_find_the_winner() {
  EXPECT_EQ_INT(3, findTheWinner(5, 2));
  EXPECT_EQ_INT(1, findTheWinner(6, 5));
}

static void test_pivot_index() {
  int nums1[5] = {2, 3, -1, 8, 4};
  int nums2[3] = {1, -1, 4};
  int nums3[2] = {2, 5};
  EXPECT_EQ_INT(3, pivotIndex(nums1, 5));
  EXPECT_EQ_INT(2, pivotIndex(nums2, 3));
  EXPECT_EQ_INT(-1, pivotIndex(nums3, 2));
}

static void test_recent_counter() {
  RecentCounter *obj = recentCounterCreate();
  EXPECT_EQ_INT(1, recentCounterPing(obj, 1));
  EXPECT_EQ_INT(2, recentCounterPing(obj, 100));
  EXPECT_EQ_INT(3, recentCounterPing(obj, 3001));
  EXPECT_EQ_INT(3, recentCounterPing(obj, 3002));
  recentCounterFree(obj);
}

int main() {
  test_two_sum();
  test_remove_element();
  test_search();
  test_is_same_tree();
  test_count_numbers_with_unique_digits();
  test_lexical_order();
  test_find_diagonal_order();
  test_self_dividing_numbers();
  test_next_greatest_letter();
  test_unique_morse_representations();
  test_number_of_lines();
  test_maximum_wealth();
  test_projection_area();
  test_sort_array_by_parity();
  test_di_string_match();
  test_find_the_winner();
  test_pivot_index();
  test_recent_counter();
  printf("%d/%d (%3.2f%%) passed\n", test_pass, test_count, test_pass * 100.0 / test_count);
  return main_ret;
}