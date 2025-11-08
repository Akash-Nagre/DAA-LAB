#include <stdio.h>
#include <limits.h>

// Function to find maximum of two numbers
int max(int a, int b) {
    return (a > b) ? a : b;
}

// Function to find max subarray sum crossing the mid point
int maxCrossingSum(int arr[], int l, int m, int h, int constraint, int *bestSum) {
    int sum = 0;
    int left_sum = 0;
    int right_sum = 0;
    int i;

    // Left side sum (must be <= constraint)
    for (i = m; i >= l; i--) {
        sum += arr[i];
        if (sum <= constraint)
            left_sum = max(left_sum, sum);
    }

    sum = 0;
    // Right side sum (must be <= constraint)
    for (i = m + 1; i <= h; i++) {
        sum += arr[i];
        if (sum <= constraint)
            right_sum = max(right_sum, sum);
    }

    if (left_sum + right_sum <= constraint)
        *bestSum = max(*bestSum, left_sum + right_sum);

    return left_sum + right_sum;
}

// Divide and conquer function to find maximum sum <= constraint
int maxSubArraySum(int arr[], int l, int h, int constraint, int *bestSum) {
    if (l > h)
        return 0;

    if (l == h) {
        if (arr[l] <= constraint)
            *bestSum = max(*bestSum, arr[l]);
        return arr[l];
    }

    int m = (l + h) / 2;

    // Recursively check left and right halves
    maxSubArraySum(arr, l, m, constraint, bestSum);
    maxSubArraySum(arr, m + 1, h, constraint, bestSum);

    // Check subarray crossing the midpoint
    maxCrossingSum(arr, l, m, h, constraint, bestSum);

    return *bestSum;
}

int main() {
    int resources[] = {4, 2, 3, 1};   // Example: can change input
    int n = sizeof(resources) / sizeof(resources[0]);
    int constraint = 5;

    if (n == 0 || constraint == 0) {
        printf("No feasible subarray.\n");
        return 0;
    }

    int bestSum = 0;
    maxSubArraySum(resources, 0, n - 1, constraint, &bestSum);

    if (bestSum == 0)
        printf("No feasible subarray.\n");
    else
        printf("Maximum subarray sum within constraint = %d\n", bestSum);

    return 0;
}
