#include <assert.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>

#include "utils.h"
#include "hash_table.h"
#include "solution.h"

#define MAX_NUM 100
#define MAX_NODE_SIZE 3000
#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))

const int MOD = 1000000007;

int *two_sum(int *nums, int nums_size, int target, int *return_size) {
    hashTable = NULL;
    for (int i = 0; i < nums_size; i++) {
        struct HashTable *it = find(target - nums[i]);
        if (it != NULL) {
            int *ret = malloc(sizeof(int) * 2);
            if (ret) {
                ret[0] = it->val, ret[1] = i;
                *return_size = 2;
                return ret;
            }
        }
        insert(nums[i], i);
    }
    *return_size = 0;
    return NULL;
}

ListNode *add_two_numbers(ListNode *l1, ListNode *l2) {
    ListNode *head = NULL, *tail = NULL;
    int carry = 0;
    while (l1 || l2) {
        int n1 = l1 ? l1->val : 0;
        int n2 = l2 ? l2->val : 0;
        int sum = n1 + n2 + carry;
        if (!head) {
            head = tail = malloc(sizeof(ListNode));
            tail->val = sum % 10;
            tail->next = NULL;
        } else {
            tail->next = malloc(sizeof(ListNode));
            tail->next->val = sum % 10;
            tail = tail->next;
            tail->next = NULL;
        }
        carry = sum / 10;
        if (l1) {
            l1 = l1->next;
        }
        if (l2) {
            l2 = l2->next;
        }
    }
    if (carry > 0) {
        tail->next = malloc(sizeof(ListNode));
        tail->next->val = carry;
        tail->next->next = NULL;
    }
    return head;
}

ListNode *remove_nth_from_end(ListNode *head, int n) {
    ListNode *dummy = malloc(sizeof(ListNode));
    dummy->val = -1, dummy->next = head;
    ListNode *fast = head;
    ListNode *slow = dummy;
    for (int i = 0; i < n; ++i) {
        fast = fast->next;
    }
    while (fast) {
        fast = fast->next;
        slow = slow->next;
    }

    fast = fast->next;
    ListNode *res = dummy->next;
    free(dummy);
    return res;
}

int remove_duplicates(int *nums, int nums_size) {
    if (nums_size == 0) {
        return 0;
    }
    int fast = 1, slow = 1;
    while (fast < nums_size) {
        if (nums[fast] != nums[fast - 1]) {
            nums[slow] = nums[fast];
            ++slow;
        }
        ++fast;
    }
    return slow;
}

int remove_element(int *nums, int nums_size, int val) {
    int left = 0;
    for (int right = 0; right < nums_size; ++right) {
        if (nums[right] != val) {
            nums[left] = nums[right];
            left++;
        }
    }
    return left;
}

int search(const int *nums, int num_size, int target) {
    if (num_size < 1) {
        return -1;
    }
    if (num_size == 1) {
        return nums[0] == target ? 0 : -1;
    }
    int l = 0, r = num_size - 1;
    while (l <= r) {
        int mid = l + (r - l) / 2;
        if (nums[mid] == target) {
            return mid;
        }
        if (nums[0] <= nums[mid]) {
            if (nums[0] <= target && target < nums[mid]) {
                r = mid - 1;
            } else {
                l = mid + 1;
            }
        } else {
            if (nums[mid] < target && target <= nums[num_size - 1]) {
                l = mid + 1;
            } else {
                r = mid - 1;
            }
        }
    }
    return -1;
}

void rotate_image(int **matrix, int matrix_size, int *matrix_col_size) {
    for (int i = 0; i < matrix_size / 2; ++i) {
        for (int j = 0; j < matrix_size; ++j) {
            swap_int(&matrix[i][j], &matrix[matrix_size - i - 1][j]);
        }
    }
    for (int i = 0; i < matrix_size; ++i) {
        for (int j = 0; j < i; ++j) {
            swap_int(&matrix[i][j], &matrix[j][i]);
        }
    }
}

void merge(int *nums1, int nums1_size, int m, int *nums2, int nums2_size, int n) {
    int p1 = m - 1, p2 = n - 1, tail = m + n - 1;
    int cur = 0;
    while (p1 >= 0 || p2 >= 0) {
        if (p1 == -1) {
            cur = nums2[p2--];
        } else if (p2 == -1) {
            cur = nums1[p1--];
        } else if (nums1[p1] > nums2[p2]) {
            cur = nums1[p1--];
        } else {
            cur = nums2[p2--];
        }
        nums1[tail--] = cur;
    }
}

bool is_same_tree(TreeNode *p, TreeNode *q) {
    if (p == NULL && q == NULL) {
        return true;
    } else if (p == NULL || q == NULL) {
        return false;
    } else if (p->val != q->val) {
        return false;
    } else {
        return is_same_tree(p->left, q->left) && is_same_tree(p->right, q->right);
    }
}

int single_number_ii(int *nums, int nums_size) {
    int a = 0, b = 0;
    for (int i = 0; i < nums_size; i++) {
        b = ~a & (b ^ nums[i]);
        a = ~b & (a ^ nums[i]);
    }
    return b;
}

bool has_cycle(ListNode *head) {
    if (head == NULL || head->next == NULL) {
        return false;
    }
    ListNode *slow = head;
    ListNode *fast = head;
    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
        if (slow == fast) {
            return true;
        }
    }
    return false;
}

void rotate(int *nums, int nums_size, int k) {
    k %= nums_size;
    reverse(nums, 0, nums_size - 1);
    reverse(nums, 0, k - 1);
    reverse(nums, k, nums_size - 1);
}

struct ListNode *reverse_list(struct ListNode *head) {
    struct ListNode *prev = NULL;
    struct ListNode *curr = head;
    while (curr) {
        struct ListNode *next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }
    return prev;
}

bool is_valid_serialization(const char *preorder) {
    int n = strlen(preorder);
    int i = 0, slots = 1;
    while (i < n) {
        if (!slots) {
            return false;
        }
        if (preorder[i] == ',') {
            i++;
        } else if (preorder[i] == '#') {
            slots--;
            i++;
        } else {
            while (i < n && preorder[i] != ',') {
                i++;
            }
            slots++;
        }
    }

    return !slots;
}

int count_numbers_with_unique_digits(int n) {
    if (n == 0) {
        return 1;
    }
    if (n == 1) {
        return 10;
    }
    int ans = 10, cur = 9;
    for (int i = 0; i < n - 1; ++i) {
        cur *= 9 - i;
        ans += cur;
    }
    return ans;
}

int *lexical_order(int n, int *return_size) {
    int *ret = (int *) malloc(sizeof(int) * n);
    int num = 1;
    for (int i = 0; i < n; ++i) {
        ret[i] = num;
        if (num * 10 <= n) {
            num *= 10;
        } else {
            while (num % 10 == 9 || num + 1 > n) {
                num /= 10;
            }
            num++;
        }
    }
    *return_size = n;
    return ret;
}

int find_substring_in_wraparound_string(char *p) {
    int dp[26];
    int k = 0;
    int len = strlen(p);
    memset(dp, 0, sizeof(dp));
    for (int i = 0; i < len; ++i) {
        if (i > 0 && (p[i] - p[i - 1] + 26) % 26 == 1) {
            ++k;
        } else {
            k = 1;
        }
        dp[p[i] - 'a'] = MAX(dp[p[i] - 'a'], k);
    }
    int res = 0;
    for (int i = 0; i < 26; ++i) {
        res += dp[i];
    }
    return res;
}

int *find_diagonal_order(int **mat, int mat_size, int *mat_col_size, int *return_size) {
    int m = mat_size;
    int n = mat_col_size[0];
    int *res = (int *) malloc(sizeof(int) * m * n);
    int pos = 0;
    for (int i = 0; i < m + n - 1; i++) {
        if (i % 2) {
            int x = i < n ? 0 : i - n + 1;
            int y = i < n ? i : n - 1;
            while (x < m && y >= 0) {
                res[pos] = mat[x][y];
                pos++;
                x++;
                y--;
            }
        } else {
            int x = i < m ? i : m - 1;
            int y = i < m ? 0 : i - m + 1;
            while (x >= 0 && y < n) {
                res[pos] = mat[x][y];
                pos++;
                x--;
                y++;
            }
        }
    }
    *return_size = m * n;
    return res;
}

int change(int amount, int *coins, int coins_size) {
    int *dp = (int*)calloc(amount + 1, sizeof(int));
    dp[0] = 1;
    for (int i = 0; i < coins_size; i++) {
        for (int j = coins[i]; j <= amount; j++) {
            dp[j] += dp[j - coins[i]];
        }
    }
    int res = dp[amount];
    free(dp);
    return res;
}

int find_longest_chain(int **pairs, int pairs_size, int *pairs_col_size) {
    int curr = INT_MIN, res = 0;
    qsort_s(pairs, pairs_size, sizeof(int *), cmp_array_of_array_at_second_element, NULL);
    for (int i = 0; i < pairs_size; ++i) {
        if (curr < pairs[i][0]) {
            curr = pairs[i][1];
            res += 1;
        }
    }
    return res;
}

int *find_closest_elements(int *arr, int arr_size, int k, int x, int *return_size) {
    int right = binary_search(arr, arr_size, x);
    int left = right - 1;
    while (k--) {
        if (left < 0) {
            right++;
        } else if (right >= arr_size || x - arr[left] <= arr[right] - x) {
            left--;
        } else {
            right++;
        }
    }
    int size = right - left - 1;
    int *res = (int *) malloc(sizeof(int) * size);
    memcpy(res, arr + left + 1, sizeof(int) * size);
    *return_size = size;
    return res;
}

int width_of_binary_tree(struct TreeNode *root) {
    unsigned long long res = 1;
    Pair *arr = (Pair *) malloc(sizeof(Pair) * MAX_NODE_SIZE);
    Pair *tmp = (Pair *) malloc(sizeof(Pair) * MAX_NODE_SIZE);
    int arr_size = 0, tmp_size = 0;
    arr[arr_size].node = root;
    arr[arr_size].index = 1LL;
    arr_size++;
    while (arr_size > 0) {
        tmp_size = 0;
        for (int i = 0; i < arr_size; ++i) {
            if (arr[i].node->left) {
                tmp[tmp_size].node = arr[i].node->left;
                tmp[tmp_size].index = arr[i].index * 2;
                tmp_size++;
            }
            if (arr[i].node->right) {
                tmp[tmp_size].node = arr[i].node->right;
                tmp[tmp_size].index = arr[i].index * 2 + 1;
                tmp_size++;
            }
        }
        res = MAX(res, arr[arr_size - 1].index - arr[0].index + 1);
        arr_size = tmp_size;
        Pair *p = arr;
        arr = tmp;
        tmp = p;
    }
    return res;
}

bool check_possibility(int *nums, int nums_size) {
    int count = 0;
    for (int i = 0; i < nums_size - 1; ++i) {
        int x = nums[i], y = nums[i + 1];
        if (x > y) {
            count++;
            if (count > 1) {
                return false;
            }
            if (i > 0 && y < nums[i - 1]) {
                nums[i + 1] = x;
            }
        }
    }
    return true;
}

int *construct_array(int n, int k, int *return_size) {
    int *res = (int *) malloc(sizeof(int) * n);
    int index = 0;
    for (int i = 1; i < n - k; ++i) {
        res[index++] = i;
    }
    for (int i = n - k, j = n; i <= j; ++i, --j) {
        res[index++] = i;
        if (i != j) {
            res[index++] = j;
        }
    }
    *return_size = n;
    return res;
}

TreeNode *trim_bst(TreeNode *root, int low, int high) {
    while (root && (root->val < low || root->val > high)) {
        if (root->val < low) {
            root = root->right;
        } else {
            root = root->left;
        }
    }
    if (root == NULL) {
        return NULL;
    }
    for (struct TreeNode *node = root; node->left;) {
        if (node->left->val < low) {
            node->left = node->left->right;
        } else {
            node = node->left;
        }
    }
    for (struct TreeNode *node = root; node->right;) {
        if (node->right->val > high) {
            node->right = node->right->left;
        } else {
            node = node->right;
        }
    }
    return root;
}

int maximum_swap(int num) {
    char chars[32];
    sprintf_s(chars, sizeof(chars), "%d", num);
    int n = strlen(chars);
    char max_index = n - 1;
    int index1 = -1, index2 = -1;
    for (int i = n - 1; i >= 0; --i) {
        if (chars[i] > chars[max_index]) {
            max_index = i;
        } else if (chars[i] < chars[max_index]) {
            index1 = i;
            index2 = max_index;
        }
    }
    if (index1 >= 0) {
        swap_char(&chars[index1], &chars[index2]);
        return atoi(chars);
    }
    return num;
}

static int longest_univalue_path_dfs(TreeNode *root, int *res) {
    if (root == NULL) {
        return 0;
    }
    int left = longest_univalue_path_dfs(root->left, res), right = longest_univalue_path_dfs(root->right, res);
    int left1 = 0, right1 = 0;
    if (root->left && root->left->val == root->val) {
        left1 = left + 1;
    }
    if (root->right && root->right->val == root->val) {
        right1 = right + 1;
    }
    *res = MAX(*res, left1 + right1);
    return MAX(left1, right1);
}

int longest_univalue_path(TreeNode *root) {
    int res = 0;
    longest_univalue_path_dfs(root, &res);
    return res;
}

static bool isSelfDividing(int num) {
    int tmp = num;
    while (tmp > 0) {
        int digit = tmp % 10;
        if (digit == 0 || num % digit != 0) {
            return false;
        }
        tmp /= 10;
    }
    return true;
}

int *self_dividing_numbers(int left, int right, int *return_size) {
    int *ans = (int *) malloc(sizeof(int) * (right - left + 1));
    int pos = 0;
    for (int i = left; i <= right; ++i) {
        if (isSelfDividing(i)) {
            ans[pos++] = i;
        }
    }
    *return_size = pos;
    return ans;
}

int cherry_pickup(int **grid, int grid_size, int *grid_col_size) {
    int n = grid_size;
    int **f = (int **) malloc(sizeof(int *) * n);
    for (int i = 0; i < n; i++) {
        f[i] = (int *) malloc(sizeof(int) * n);
        for (int j = 0; j < n; j++) {
            f[i][j] = INT_MIN;
        }
    }
    f[0][0] = grid[0][0];
    for (int k = 1; k < n * 2 - 1; k++) {
        for (int x1 = MIN(k, n -1); x1 >= MAX(k-n+1,0); x1--) {
            for (int x2 = MIN(k, n-1); x2 >= x1; x2--) {
                int y1 = k - x1, y2 = k - x2;
                if (grid[x1][y1] == -1 || grid[x2][y2] == -1) {
                    f[x1][x2] = INT_MIN;
                    continue;
                }
                int res = f[x1][x2];
                if (x1) {
                    res = MAX(res, f[x1 - 1][x2]);
                }

                if (x2) {
                    res = MAX(res, f[x1][x2 - 1]);
                }

                if (x1 && x2) {
                    res = MAX(res, f[x1 - 1][x2 - 1]);
                }

                res += grid[x1][y1];
                if (x2 != x1) {
                    res += grid[x2][y2];
                }

                f[x1][x2] = res;
            }
        }
    }

    int ans = MAX(f[n - 1][n - 1], 0);
    for (int i = 0; i < n; i++) {
        free(f[i]);
    }
    free(f);
    return ans;
}

char next_greatest_letter(char *letters, int letters_size, char target) {
    if (target >= letters[letters_size - 1]) {
        return letters[0];
    }
    int low = 0, high = letters_size - 1;
    while (low < high) {
        int mid = (high - low) / 2 + low;
        if (letters[mid] > target) {
            high = mid;
        } else {
            low = mid + 1;
        }
    }
    return letters[low];
}

int max_chunks_to_sorted(int *arr, int arr_size) {
    int m = 0, res = 0;
    for (int i = 0; i < arr_size; ++i) {
        m = MAX(m, arr[i]);
        if (m == i) {
            res++;
        }
    }
    return res;
}

bool can_transform(char *start, char *end) {
    int n = strlen(start);
    int i = 0, j = 0;
    while (i < n && j < n) {
        while (i < n && start[i] == 'X') {
            i++;
        }
        while (j < n && end[j] == 'X') {
            j++;
        }
        if (i < n && j < n) {
            if (start[i] != end[j]) {
                return false;
            }
            char c = start[i];
            if ((c == 'L' && i < j) || (c == 'R' && i > j)) {
                return false;
            }
            i++;
            j++;
        }
    }
    while (i < n) {
        if (start[i] != 'X') {
            return false;
        }
        i++;
    }
    while (j < n) {
        if (end[j] != 'X') {
            return false;
        }
        j++;
    }
    return true;
}

static long long zeta(long x) {
    long long res = 0;
    while (x != 0) {
        res += x / 5;
        x /= 5;
    }
    return res;
}

static long long nx(int k) {
    long long left = 0, right = 5LL * k;
    while (left <= right) {
        long mid = (left + right) / 2;
        if (zeta(mid) < k) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return right + 1;
}

int preimage_size_fzf(int k) {
    return nx(k + 1) - nx(k);
}

int min_swap(int *nums1, int nums1_size, int *nums2, int nums2_size) {
    int n = nums1_size;
    int a = 0, b = 1;
    for (int i = 1; i < n; ++i) {
        int at = a, bt = b;
        a = n, b = n;
        if (nums1[i] > nums1[i - 1] && nums2[i] > nums2[i - 1]) {
            a = MIN(a, at);
            b = MIN(b, bt + 1);
        }
        if (nums1[i] > nums2[i - 1] && nums2[i] > nums1[i - 1]) {
            a = MIN(a, bt);
            b = MIN(b, at + 1);
        }
    }
    return MIN(a, b);
}

int unique_morse_representations(char **words, int words_size) {
    const char *MORSE[26] = {".-", "-...", "-.-.", "-..", ".", "..-.", "--.",
                             "....", "..", ".---", "-.-", ".-..", "--", "-.",
                             "---", ".--.", "--.-", ".-.", "...", "-", "..-",
                             "...-", ".--", "-..-", "-.--", "--.."};
    HashItem *seen = NULL;
    for (int i = 0; i < words_size; ++i) {
        HashItem *pEntry = NULL;
        int len = strlen(words[i]);
        int pos = 0;
        char code[MAX_STR_LEN];
        for (int j = 0; j < len; ++j) {
            pos += sprintf_s(code + pos, MAX_STR_LEN - pos, "%s", MORSE[words[i][j] - 'a']);
        }
        HASH_FIND_STR(seen, code, pEntry);
        if (NULL == pEntry) {
            pEntry = (HashItem *) malloc(sizeof(HashItem));
            strcpy_s(pEntry->key, _countof(pEntry->key), code);
            HASH_ADD_STR(seen, key, pEntry);
        }
    }
    int ans = HASH_COUNT(seen);
    HashItem *curr = NULL, *tmp = NULL;
    HASH_ITER(hh, seen, curr, tmp) {
        HASH_DEL(seen, curr);
        free(curr);
    }
    return ans;
}

int *number_of_lines(int *widths, int widths_size, char *s, int *return_size) {
    const int MAX_WIDTH = 100;
    int lines = 1, width = 0, len = strlen(s);
    for (int i = 0; i < len; ++i) {
        int need = widths[s[i] - 'a'];
        width += need;
        if (width > MAX_WIDTH) {
            lines++;
            width = need;
        }
    }
    int *ans = (int *) malloc(sizeof(int) * 2);
    *return_size = 2;
    ans[0] = lines;
    ans[1] = width;
    return ans;
}

int unique_letter_string(char *s) {
    ListNode **index = (ListNode **) malloc(sizeof(ListNode *) * 26);
    for (int i = 0; i < 26; ++i) {
        index[i] = NULL;
    }
    int len = strlen(s);
    for (int i = 0; i < len; ++i) {
        ListNode *node = (ListNode *) malloc(sizeof(ListNode));
        node->val = i;
        node->next = index[s[i] - 'A'];
        index[s[i] - 'A'] = node;
    }
    int res = 0;
    for (int i = 0; i < 26; ++i) {
        if (index[i]) {
            ListNode *curr = index[i];
            ListNode *prev = NULL;
            ListNode *next = curr->next;
            while (curr) {
                if (prev == NULL && next == NULL) {
                    res += (curr->val + 1) * (len - curr->val);
                } else if (prev == NULL) {
                    res += (curr->val - next->val) * (len - curr->val);
                } else if (next == NULL) {
                    res += (curr->val + 1) * (prev->val - curr->val);
                } else {
                    res += (curr->val - next->val) * (prev->val - curr->val);
                }
                prev = curr;
                curr = curr->next;
                if (next) {
                    next = next->next;
                }
            }
        }
    }
    for (int i = 0; i < 26; ++i) {
        if (index[i]) {
            ListNode *curr = NULL, *temp = NULL;
            for (curr = index[i]; curr;) {
                temp = curr;
                curr = curr->next;
                free(temp);
            }
        }
    }
    return res;
}

int score_of_parentheses(char *s) {
    int bal = 0, n = strlen(s), res = 0;
    for (int i = 0; i < n; ++i) {
        bal += (s[i] == '(' ? 1 : -1);
        if (s[i] == ')' && s[i - 1] == '(') {
            res += 1 << bal;
        }
    }
    return res;
}

int *advantage_count(int *nums1, int nums1_size, int *nums2, int nums2_size, int *return_size) {
    int n = nums1_size;
    int **index1 = (int **) malloc(sizeof(int *) * n);
    int **index2 = (int **) malloc(sizeof(int *) * n);
    for (int i = 0; i < n; ++i) {
        index1[i] = (int *) malloc(sizeof(int) * 2);
        index2[i] = (int *) malloc(sizeof(int) * 2);
    }
    for (int i = 0; i < n; ++i) {
        index1[i][0] = i, index1[i][1] = nums1[i];
        index2[i][0] = i, index2[i][1] = nums2[i];
    }
    qsort(index1, n, sizeof(index1[0]), cmp_array);
    qsort(index2, n, sizeof(index2[0]), cmp_array);

    int *res = (int *) malloc(sizeof(int) * n);
    int left = 0, right = n - 1;
    for (int i = 0; i < n; ++i) {
        if (nums1[index1[i][0]] > nums2[index2[left][0]]) {
            res[index2[left][0]] = nums1[index1[i][0]];
            left++;
        } else {
            res[index2[right][0]] = nums1[index1[i][0]];
            right--;
        }
    }
    *return_size = n;
    return res;
}

int projection_area(int **grid, int grid_size, int *grid_col_size) {
    int xyArea = 0, yzArea = 0, zxArea = 0;
    for (int i = 0; i < grid_size; ++i) {
        int yzHeight = 0, zxHeight = 0;
        for (int j = 0; j < grid_size; ++j) {
            xyArea += grid[i][j] > 0 ? 1 : 0;
            yzHeight = MAX(yzHeight, grid[j][i]);
            zxHeight = MAX(zxHeight, grid[i][j]);
        }
        yzArea += yzHeight;
        zxArea += zxHeight;
    }
    return xyArea + yzArea + zxArea;
}

int *sort_array_by_parity(int *nums, int nums_size, int *return_size) {
    int left = 0, right = nums_size - 1;
    while (left < right) {
        while (left < right && nums[left] % 2 == 0) {
            left++;
        }
        while (left < right && nums[right] % 2 == 1) {
            right--;
        }
        if (left < right) {
            int temp = nums[left];
            nums[left] = nums[right];
            nums[right] = temp;
            left++;
            right--;
        }
    }
    *return_size = nums_size;
    return nums;
}

int partition_disjoint(int *nums, int nums_size) {
    int curr_max = nums[0], left_max = nums[0];
    int index = 0;
    for (int i = 0; i < nums_size - 1; i++) {
        curr_max = MAX(curr_max, nums[i]);
        if (nums[i] < left_max) {
            left_max = curr_max;
            index = i;
        }
    }
    return index + 1;
}

int min_add_to_make_valid(char *s) {
    int res = 0;
    int left_count = 0;
    int n = strlen(s);
    for (int i = 0; i < n; ++i) {
        char c = s[i];
        if (c == '(') {
            left_count++;
        } else {
            if (left_count > 0) {
                left_count--;
            } else {
                res++;
            }
        }
    }
    res += left_count;
    return res;
}

int *three_equal_parts(int *arr, int arr_size, int *return_size) {
    int sum = 0;
    int *res = (int *) malloc(sizeof(int) * 2);
    *return_size = 2;
    for (int i = 0; i < arr_size; ++i) {
        sum += arr[i];
    }
    if (sum % 3 != 0) {
        res[0] = -1, res[1] = -1;
        return res;
    }

    if (sum == 0) {
        res[0] = 0, res[1] = 2;
        return res;
    }

    int partial = sum / 3;
    int first = 0, second = 0, third = 0, curr = 0;
    for (int i = 0; i < arr_size; ++i) {
        if (arr[i] == 1) {
            if (curr == 0) {
                first = i;
            } else if (curr == partial) {
                second = i;
            } else if (curr == 2 * partial) {
                third = i;
            }
            curr++;
        }
    }
    int len = arr_size - third;
    if (first + len <= second && second + len <= third) {
        int i = 0;
        while (third + i < arr_size) {
            if (arr[first + i] != arr[second + i] || arr[first + i] != arr[third + i]) {
                res[0] = -1, res[1] = -1;
                return res;
            }
            i++;
        }
        res[0] = first + len - 1, res[1] = second + len;
        return res;
    }
    res[0] = -1, res[1] = -1;
    return res;
}

static void shortest_bridge_dfs(int x, int y, int **grid, int n, int *queue, int *tail) {
    if (x < 0 || y < 0 || x >= n || y >= n || grid[x][y] != 1) {
        return;
    }
    queue[(*tail)++] = x *n + y;
    grid[x][y] = -1;
    shortest_bridge_dfs(x - 1, y, grid, n, queue, tail);
    shortest_bridge_dfs(x + 1, y, grid, n, queue, tail);
    shortest_bridge_dfs(x, y - 1, grid, n, queue, tail);
    shortest_bridge_dfs(x, y + 1, grid, n, queue, tail);
}
int shortest_bridge(int** grid, int grid_size, int* grid_col_size) {
 int n = grid_size;
    int dirs[4][2] = {{-1, 0}, {1, 0}, {0, 1}, {0, -1}};

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (grid[i][j] == 1) {
                int *queue = (int *)malloc(sizeof(int) * n * n);
                int head = 0, tail = 0;
                shortest_bridge_dfs(i, j, grid, n, queue, &tail);
                int step = 0;
                while (head != tail) {
                    int sz = tail - head;
                    for (int i = 0; i < sz; i++) {
                        int x = queue[head] / n;
                        int y = queue[head] % n;
                        head++;
                        for (int k = 0; k < 4; k++) {
                            int nx = x + dirs[k][0];
                            int ny = y + dirs[k][1];
                            if (nx >= 0 && ny >= 0 && nx < n && ny < n) {
                                if (grid[nx][ny] == 0) {
                                    queue[tail++] = nx * n + ny;
                                    grid[nx][ny] = -1;
                                } else if (grid[nx][ny] == 1) {
                                    free(queue);
                                    return step;
                                }
                            }
                        }
                    }
                    step++;
                }
            }
        }
    }
    return 0;
}

int distinct_sub_seq_ii(char *s) {
    int group[26];
    memset(group, 0, sizeof(group));
    int n = strlen(s), res = 0;
    for (int i = 0; i < n; ++i) {
        int index = s[i] - 'a';
        int prev = group[index];
        group[index] = (res + 1) % MOD;
        res = ((res + group[index] - prev) % MOD + MOD) % MOD;
    }
    return res;
}

int *di_string_match(char *s, int *return_size) {
    int n = strlen(s), lo = 0, hi = n;
    int *perm = (int *) malloc(sizeof(int) * (n + 1));
    for (int i = 0; i < n; ++i) {
        perm[i] = s[i] == 'I' ? lo++ : hi--;
    }
    perm[n] = lo;
    *return_size = n + 1;
    return perm;
}

int min_deletion_size(char **strs, int strs_size) {
    int row = strs_size;
    int col = strlen(strs[0]);
    int ans = 0;
    for (int j = 0; j < col; ++j) {
        for (int i = 1; i < row; ++i) {
            if (strs[i - 1][j] > strs[i][j]) {
                ans++;
                break;
            }
        }
    }
    return ans;
}

bool validate_stack_sequences(int *pushed, int pushed_size, int *popped, int popped_size) {
    int *stack = (int *) malloc(sizeof(int) * pushed_size);
    int top = 0;
    for (int i = 0, j = 0; i < pushed_size; ++i) {
        stack[top++] = pushed[i];
        while (top > 0 && stack[top - 1] == popped[j]) {
            top--;
            j++;
        }
    }
    free(stack);
    return top == 0;
}

bool is_alien_sorted(char **words, int words_size, char *order) {
    int index[26];
    for (int i = 0; i < strlen(order); ++i) {
        index[order[i] - 'a'] = i;
    }
    for (int i = 1; i < words_size; ++i) {
        bool valid = false;
        int len1 = strlen(words[i - 1]);
        int len2 = strlen(words[i]);
        int n = len1 < len2 ? len1 : len2;
        for (int j = 0; j < n; ++j) {
            int prev = index[words[i - 1][j] - 'a'];
            int curr = index[words[i][j] - 'a'];
            if (prev < curr) {
                valid = true;
                break;
            } else if (prev > curr) {
                return false;
            }
        }
        if (!valid) {
            if (len1 > len2) {
                return false;
            }
        }
    }
    return true;
}

bool is_unival_tree(TreeNode *root) {
    if (!root) {
        return true;
    }
    if (root->left) {
        if (root->val != root->left->val || !is_unival_tree(root->left)) {
            return false;
        }
    }

    if (root->right) {
        if (root->val != root->right->val || !is_unival_tree(root->right)) {
            return false;
        }
    }
    return true;
}

struct TreeNode *insert_into_max_tree(struct TreeNode *root, int val) {
    struct TreeNode *parent = NULL;
    struct TreeNode *curr = root;
    struct TreeNode *node = NULL;
    while (curr) {
        if (val > curr->val) {
            if (!parent) {
                return generate_tree_node(val, root, NULL);
            }
            parent->right = generate_tree_node(val, curr, NULL);
            return root;
        } else {
            parent = curr;
            curr = curr->right;
        }
    }
    parent->right = generate_tree_node(val, NULL, NULL);
    return root;
}

char *defang_ip_addr(char *address) {
    int len = strlen(address);
    int pos = 0;
    int size = sizeof(char) * (len + 7);
    char *res = (char *) malloc(size);// [] [] []
    for (int i = 0; i < len; ++i) {
        if (address[i] == '.') {
            pos += sprintf_s(res + pos, size - pos, "%s", "[.]");
        } else {
            res[pos++] = address[i];
        }
    }
    res[pos] = '\0';
    return res;
}

int *min_subsequence(int *nums, int nums_size, int *return_size) {
    int total = 0;
    for (int i = 0; i < nums_size; ++i) {
        total += nums[i];
    }
    qsort_s(nums, nums_size, sizeof(int), cmp_asc_s, NULL);
    int *ans = (int *) malloc(sizeof(int) * nums_size);
    int curr = 0, pos = 0;
    for (int i = nums_size - 1; i >= 0; --i) {
        curr += nums[i];
        ans[pos++] = nums[i];
        if (total - curr < curr) {
            break;
        }
    }
    *return_size = pos;
    return ans;
}

char **string_matching(char **words, int words_size, int *return_size) {
    char **res = (char **) malloc(sizeof(char *) * words_size);
    int pos = 0;
    for (int i = 0; i < words_size; ++i) {
        for (int j = 0; j < words_size; ++j) {
            if (i != j && strstr(words[j], words[i])) {
                res[pos++] = words[i];
                break;
            }
        }
    }
    *return_size = pos;
    return res;
}

char **build_array(int *target, int target_size, int n, int *return_size) {
    char **res = (char **) malloc(sizeof(char *) * n * 2);
    int prev = 0, pos = 0;
    for (int j = 0; j < target_size; ++j) {
        for (int i = 0; i < target[j] - prev - 1; ++i) {
            res[pos] = (char *) malloc(sizeof(char) * 8);
            strcpy_s(res[pos], strlen(res[pos]), "Push");
            pos++;
            res[pos] = (char *) malloc(sizeof(char) * 8);
            strcpy_s(res[pos], strlen(res[pos]), "Pop");
            pos++;
        }
        res[pos] = (char *) malloc(sizeof(char) * 8);
        strcpy_s(res[pos], strlen(res[pos]), "Push");
        pos++;
        prev = target[j];
    }
    *return_size = pos;
    return res;
}

int busy_student(int *start_time, int start_time_size, int *end_time, int end_time_size, int query_time) {
    int res = 0;
    for (int i = 0; i < start_time_size; ++i) {
        if (start_time[i] <= query_time && query_time <= end_time[i]) {
            res++;
        }
    }
    return res;
}

static bool is_prefix(const char *sentence, int start, int end, const char *search_word) {
    int len = strlen(search_word);
    for (int i = 0; i < len; ++i) {
        if (start + i >= end || sentence[start + i] != search_word[i]) {
            return false;
        }
    }
    return true;
}

int is_prefix_of_word(char *sentence, char *search_word) {
    int n = strlen(sentence), index = 1, start = 0, end = 0;
    while (start < n) {
        while (end < n && sentence[end] != ' ') {
            end++;
        }
        if (is_prefix(sentence, start, end, search_word)) {
            return index;
        }
        index++;
        end++;
        start = end;
    }
    return -1;
}

bool can_be_equal(int *target, int target_size, int *arr, int arr_size) {
    int descending = 0;
    qsort_s(target, target_size, sizeof(int), cmp_asc_s, NULL);
    qsort_s(arr, arr_size, sizeof(int), cmp_asc_s, NULL);
    return memcmp(target, arr, sizeof(int) * arr_size) == 0;
}

int max_product(int *nums, int nums_size) {
    int a = nums[0], b = nums[1];
    if (a < b) {
        int temp = a;
        a = b;
        b = temp;
    }
    for (int i = 2; i < nums_size; i++) {
        if (nums[i] > a) {
            b = a;
            a = nums[i];
        } else if (nums[i] > b) {
            b = nums[i];
        }
    }
    return (a - 1) * (b - 1);
}

int *shuffle(int *nums, int nums_size, int n, int *return_size) {
    int *res = (int *) malloc(sizeof(int) * n * 2);
    for (int i = 0; i < n; ++i) {
        res[2 * i] = nums[i];
        res[2 * i + 1] = nums[n + i];
    }
    *return_size = n * 2;
    return res;
}

int *final_prices(int *prices, int prices_size, int *return_size) {
    int *res = (int *) malloc(sizeof(int) * prices_size);
    int *stack = (int *) malloc(sizeof(int) * prices_size);
    int top = 0;
    for (int i = prices_size - 1; i >= 0; --i) {
        while (top > 0 && stack[top - 1] > prices[i]) {
            top--;
        }
        res[i] = top == 0 ? prices[i] : prices[i] - stack[top - 1];
        stack[top++] = prices[i];
    }
    *return_size = prices_size;
    free(stack);
    return res;
}

int num_special(int **mat, int mat_size, int *mat_col_size) {
    int m = mat_size, n = mat_col_size[0];
    for (int i = 0; i < m; ++i) {
        int count = 0;
        for (int j = 0; j < n; ++j) {
            if (mat[i][j] == 1) {
                count++;
            }
        }
        if (i == 0) {
            count--;
        }
        if (count > 0) {
            for (int j = 0; j < n; ++j) {
                if (mat[i][j] == 1) {
                    mat[0][j] += count;
                }
            }
        }
    }
    int sum = 0;
    for (int i = 0; i < n; ++i) {
        if (mat[0][i] == 1) {
            sum++;
        }
    }
    return sum;
}

char *reorder_spaces(char *text) {
    int length = strlen(text);
    int wordsSize = 0;
    char **words = split(text, ' ', &wordsSize);
    int spaceCount = length;
    int wordCount = 0;
    for (int i = 0; i < wordsSize; ++i) {
        int len = strlen(words[i]);
        if (len > 0) {
            spaceCount -= len;
            wordCount++;
        }
    }
    int size = sizeof(char) * (length + 1);
    char *res = (char *) malloc(size);
    int pos = 0;
    if (wordsSize == 1) {
        pos += sprintf_s(res + pos, size - pos, "%s", words[0]);
        for (int i = 0; i < spaceCount; ++i) {
            res[pos++] = ' ';
        }
        res[pos] = '\0';
        free(words[0]);
        free(words);
        return res;
    }

    int perSpace = spaceCount / (wordCount - 1);
    int restSpace = spaceCount % (wordCount - 1);
    for (int i = 0; i < wordsSize; i++) {
        if (strlen(words[i]) == 0) {
            continue;
        }
        if (pos > 0) {
            for (int j = 0; j < perSpace; j++) {
                res[pos++] = ' ';
            }
        }
        pos += sprintf_s(res + pos, size - pos, "%s", words[i]);
    }
    for (int i = 0; i < restSpace; i++) {
        res[pos++] = ' ';
    }
    res[pos] = '\0';
    for (int i = 0; i < wordsSize; i++) {
        free(words[i]);
    }
    free(words);
    return res;
}

int min_operations(char **logs, int logs_size) {
    int depth = 0;
    for (int i = 0; i < logs_size; ++i) {
        if (!strcmp(logs[i], "./")) {
            continue;
        } else if (!strcmp(logs[i], "../")) {
            if (depth > 0) {
                depth--;
            }
        } else {
            depth++;
        }
    }
    return depth;
}

int special_array(int *nums, int nums_size) {
    qsort_s(nums, nums_size, sizeof(int), cmp_desc_s, NULL);
    for (int i = 1; i <= nums_size; ++i) {
        if (nums[i - 1] >= i && (i == nums_size || nums[i] < i)) {
            return i;
        }
    }
    return -1;
}

double trim_mean(int *arr, int arr_size) {
    qsort(arr, arr_size, sizeof(int), cmp_asc);
    int sum = 0;
    for (int i = arr_size / 20; i < (19 * arr_size / 20); i++) {
        sum += arr[i];
    }
    return sum / (arr_size * 0.9);
}

int max_length_between_equal_characters(char *s) {
    int res = -1;
    int map[26];
    int n = strlen(s);
    memset(map, -1, sizeof(map));
    for (int i = 0; i < n; ++i) {
        if (map[s[i] - 'a'] < 0) {
            map[s[i] - 'a'] = i;
        } else {
            res = MAX(res, i - map[s[i] - 'a'] - 1);
        }
    }
    return res;
}

int min_operations_2(int *nums, int nums_size, int x) {
    int sum = 0;
    for (int i = 0; i < nums_size; i++) {
        sum += nums[i];
    }
    if (sum < x) {
        return -1;
    }
    int right = 0;
    int left_sum =0, right_sum = sum;
    int res = nums_size + 1;

    for (int left = -1; left < nums_size; left++) {
        if (left != -1) {
            left_sum += nums[left];
        }
        while (right < nums_size && left_sum + right_sum > x) {
            right_sum -= nums[right];
            right++;
        }
        if (left_sum + right_sum == x) {
            res = MIN(res, (left + 1) + (nums_size - right));
        }
    }
    return res > nums_size ? - 1 : res;
}

int maximum_wealth(int **accounts, int accounts_size, int *accounts_col_size) {
    int maxWealth = INT_MIN;
    for (int i = 0; i < accounts_size; ++i) {
        int sum = 0;
        for (int j = 0; j < accounts_col_size[0]; ++j) {
            sum += accounts[i][j];
        }
        maxWealth = MAX(maxWealth, sum);
    }
    return maxWealth;
}

char *reformat_number(char *number) {
    int len = strlen(number);
    char *digits = (char *) malloc(sizeof(char) * (len + 1));
    int pos = 0;
    for (int i = 0; i < len; ++i) {
        char ch = number[i];
        if (isdigit(ch)) {
            digits[pos++] = ch;
        }
    }

    int n = pos;
    int pt = 0;
    int size = sizeof(char) * n * 2;
    char *res = (char *) malloc(size);
    pos = 0;
    while (n) {
        if (n > 4) {
            strncpy_s(res + pos, size, digits + pt, 3);
            pos += 3;
            res[pos++] = '-';
            pt += 3;
            n -= 3;
        } else {
            if (n == 4) {
                strncpy_s(res + pos, size, digits + pt, 2);
                pos += 2;
                res[pos++] = '-';
                strncpy_s(res + pos, size, digits + pt + 2, 2);
                pos += 2;
            } else {
                strncpy_s(res + pos, size, digits + pt, n);
                pos += n;
            }
            break;
        }
    }
    res[pos] = '\0';
    return res;
}

int minimum_length(char *s) {
    int n = strlen(s);
    int left = 0, right = n - 1;
    while (left < right && s[left] == s[right]) {
        char c = s[left];
        while (left <= right && s[left] == c) {
            left++;
        }
        while (left <= right && s[right] == c) {
            right--;
        }
    }
    return right - left + 1;
}

char *merge_alternately(char *word1, char *word2) {
    int m = strlen(word1);
    int n = strlen(word2);
    char *res = (char*) malloc(sizeof(char)*(m+n+1));
    res[m+n] = '\0';
    int i = 0, j = 0, curr = 0;
    while (i < m || j < n) {
        if (i < m) {
            res[curr++] = word1[i++];
        }
        if (j < n) {
            res[curr++] = word2[j++];
        }
    }
    return res;
}

int nearest_valid_point(int x, int y, int** points, int points_size, int* points_col_size) {
    int min = INT_MAX, res = -1;
    for (int i = 0; i < points_size; ++i) {
        int px = points[i][0], py = points[i][1];
        if (x == px) {
            int dist = abs(y - py);
            if (dist < min) {
                min = dist;
                res = i;
            }
        }
        else if (y == py) {
            int dist = abs(x - px);
            if (dist < min) {
                min = dist;
                res = i;
            }
        }
    }
    return res;
}

bool check_ones_segment(char *s) {
    return strstr(s, "01") == NULL;
}

bool are_almost_equal(char *s1, char *s2) {
    int n = strlen(s1), pos = 0;
    int diff[2];
    for (int i = 0; i < n; ++i) {
        if (s1[i] != s2[i]) {
            if (pos >= 2) {
                return false;
            }
            diff[pos++] = i;
        }
    }
    if (pos == 0) {
        return true;
    }
    if (pos != 2) {
        return false;
    }
    return s1[diff[0]] == s2[diff[1]] && s1[diff[1]] == s2[diff[0]];
}

int max_ascending_sum(int *nums, int nums_size) {
    int res = 0;
    int i = 0;
    while (i < nums_size) {
        int currSum = nums[i++];
        while (i < nums_size && nums[i] > nums[i - 1]) {
            currSum += nums[i++];
        }
        res = MAX(res, currSum);
    }
    return res;
}

int find_the_winner(int n, int k) {
    int winner = 1;
    for (int i = 2; i <= n; ++i) {
        winner = (k + winner - 1) % i + 1;
    }
    return winner;
}

int find_middle_index(int *nums, int nums_size) {
    int total = 0;
    for (int i = 0; i < nums_size; i++) {
        total += nums[i];
    }
    int sum = 0;
    for (int i = 0; i < nums_size; i++) {
        if (2 * sum + nums[i] == total) {
            return i;
        }
        sum += nums[i];
    }
    return -1;
}

int first_day_been_in_all_rooms(int *next_visit, int next_visit_size) {
    int *dp = (int *) malloc(next_visit_size * sizeof(int));
    memset(dp, 0, sizeof(dp));

    dp[0] = 2;
    for (int i = 1; i < next_visit_size; i++) {
        int to = next_visit[i];
        dp[i] = 2 + dp[i - 1];
        if (to) {
            dp[i] = (dp[i] - dp[to - 1] + MOD) % MOD;
        }
        dp[i] = (dp[i] + dp[i - 1]) % MOD;
    }
    int res = dp[next_visit_size - 2];
    free(dp);
    return res;
}

int final_value_after_operations(char **operations, int operations_size) {
    int res = 0;
    for (int i = 0; i < operations_size; ++i) {
        char *op = operations[i];
        if (op[1] == '+') {
            res++;
        } else {
            res--;
        }
    }
    return res;
}

int minimum_moves(char *s) {
    int count = -1, res = 0;
    for (int i = 0; s[i] != '\0'; ++i) {
        if (s[i] == 'X' && i > count) {
            count = i + 2;
            res++;
        }
    }
    return res;
}

int *two_out_of_three(int *nums1, int nums1_size, int *nums2, int nums2_size, int *nums3, int nums3_size, int *return_size) {
    int map[MAX_NUM + 1];
    memset(map, 0, sizeof(map));
    for (int i = 0; i < nums1_size; i++) {
        map[nums1[i]] = 1;
    }
    for (int i = 0; i < nums2_size; i++) {
        map[nums2[i]] |= 2;
    }
    for (int i = 0; i < nums3_size; i++) {
        map[nums3[i]] |= 4;
    }
    int *res = (int*) malloc(sizeof(int) * MAX_NUM);
    int pos = 0;
    for (int i = 0; i <= MAX_NUM; i++) {
        if (map[i] & (map[i] -1)) {
           res[pos++] = i;
        }
    }
    *return_size = pos;
    return res;
}

int min_moves_to_seat(int *seats, int seats_size, int *students, int students_size) {
    qsort(seats, seats_size, sizeof(int), cmp_asc);
    qsort(students, students_size, sizeof(int), cmp_asc);
    int res = 0;
    for (int i = 0; i < seats_size; i ++) {
        res += abs(seats[i] - students[i]);
    }
    return res;
}

bool are_number_ascending(char *s) {
    int prev = 0, pos = 0;
    while (s[pos] != '\0') {
        if (isdigit(s[pos])) {
           int curr = 0;
           while (s[pos] != '\0' && isdigit(s[pos])) {
                curr = curr * 10 + s[pos] - '0';
                pos++;
           }
           if (curr <= prev) {
                return false;
           }
           prev = curr;
        } else {
           pos++;
        }
    }
    return true;
}

int count_even(int num) {
    int y = num / 10, x = num % 10;
    int res = y * 5, y_sum = 0;
    while (y) {
        y_sum += y % 10;
        y /= 10;
    }
    if (y_sum % 2 == 0) {
        res += x / 2 + 1;
    } else {
        res += (x + 1) / 2;
    }
    return res - 1;
}

int prefix_count(char **words, int words_size, char *pref) {
    int res = 0;
    int len = strlen(pref);
    for (int i = 0; i < words_size; ++i) {
        if (strncmp(words[i], pref, len) == 0) {
           res++;
        }
    }
    return res;
}

char repeated_character(char *s) {
    int seen = 0;
    for (int i = 0; s[i] != '\0'; i++) {
        int index = s[i] - 'a';
        if (seen & (1 << index)) {
           return s[i];
        }
        seen |= (1 << index);
    }
    return ' ';
}

int lower_bound(const int* nums, int nums_size, int val) {
    int l = 0, r = nums_size;
    while (l < r) {
        int mid = (r - l) / 2 + l;
        if (nums[mid] >= val) {
            r = mid;
        } else {
            l = mid + 1;
        }
    }
    return l;
}

int maximum_count(int *nums, int nums_size) {
    int pos1 = lower_bound(nums, nums_size, 0);
    int pos2 = lower_bound(nums, nums_size, 1);
    return fmax(pos1, nums_size - pos2);
}

int count_ways(int **ranges, int ranges_size, int *ranges_col_size) {
    qsort_s(ranges, ranges_size, sizeof(int *), cmp_array_of_array_at_first_element, NULL);
    long long res = 1;
    for (int i = 0; i < ranges_size;) {
        int r = ranges[i][1];
        int j = i + 1;
        while (j < ranges_size && ranges[j][0] <= r) {
            r = fmax(r, ranges[j][1]);
            j++;
        }
        res = res * 2 % MOD;
        i = j;
    }
    return res;
}

int minimum_sum(int *nums, int nums_size) {
    int res = 1000, mini = 1000;
    int *left = (int *) malloc(nums_size * sizeof(int));
    int right = nums[nums_size - 1];
    for (int i = 1; i < nums_size; i++) {
        mini = nums[i - 1] < mini ? nums[i - 1] : mini;
        left[i] = mini;
    }
    for (int i = nums_size - 2; i > 0; i--) {
        if (left[i] < nums[i] && nums[i] > right) {
            res = res < left[i] + nums[i] + right ? res : left[i] + nums[i] + right;
        }
        right = right - nums[i] < 0 ? right : nums[i];
    }

    return res < 1000 ? res : -1;
}

int minimum_added_coins(int *coins, int coins_size, int target) {
    qsort_s(coins, coins_size, sizeof(int), cmp_asc_s, NULL);
    int res = 0;
    int x = 1;
    int index = 0;
    while (x <= target) {
        if (index < coins_size && coins[index] <= x) {
            x += coins[index];
            index++;
        } else {
            x <<= 1;
            res++;
        }
    }
    return res;
}
