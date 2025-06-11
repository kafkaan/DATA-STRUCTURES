
/// @brief Binary Search Algorithm
/// @param nums Numbers array
/// @param numsSize Size of the numbers array
/// @param target Target number to search for
/// @return Find or not boolean
int search(int* nums, int numsSize, int target) {
    int left = 0;
    int right = numsSize - 1;

    while(left <= right)
    {
        int mid = (left + right) /2;

        if(nums[mid] == target)
        {
            return mid;
        }
        else if(nums[mid] > target)
        {
            right = mid - 1;
        }
        else 
        {
            left = mid + 1;
        }
    }

    return -1;
}
