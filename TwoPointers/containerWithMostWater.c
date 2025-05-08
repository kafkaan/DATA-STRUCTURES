/*
 * Container With Most Water
 * 
 * Description:
 * You are given an integer array heights where heights[i] represents the height of the ith bar.
 * You may choose any two bars to form a container.
 * Return the maximum amount of water a container can store.
 *
 * Example 1:
 * Input: height = [1,7,2,5,4,7,3,6]
 * Output: 36
 * 
 * Example 2:
 * Input: height = [2,2,2]
 * Output: 4
 *
 * Notes:
 * - The water container is formed between two bars
 * - The width of the container is the distance between the two bars
 * - The height of the container is limited by the shorter of the two bars
 * - The amount of water = width * height
 * - Need to find the two bars that create the container with maximum water
 */


 int returnminTwoNumbers(int i,int j)
 {
    if(i < j)
    {
        return i;
    }
    else {
        return j;
    }
 }

 #include <stdio.h>
 #include <stdlib.h>

 int maxArea(int* height, int heightSize) {
    int i,j;

    i = 0;
    j = heightSize - 1;

    int maxWater = 0;

    while(i < j)
    {
        int heightMin = returnminTwoNumbers(height[i],height[j]);

        int width = j - i;

        int waterSize = heightMin * width;

        if(maxWater < waterSize)
        {
            maxWater = waterSize;
        }

        if (height[i] < height[j]) {
            i++;
        } else {
            j--;
        }
    }

    return maxWater;
 }