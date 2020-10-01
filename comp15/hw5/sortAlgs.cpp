/*
Christian Zinck
HW 5
11/2/17
Implementation of sorting algotithms
*/

#include "sortAlgs.h"

#include <iostream>
#include <vector>

using namespace std;

// Takes a reference to an unsorted list as an input and sorts the list using
// the insertion sort method.
void insertionSort(vector<int> &nums) {
	for (size_t i = 1; i < nums.size(); i++)
	{
		for (size_t j = 0; j < i; j++)
		{
			if (nums[i] < nums[j])
			{
				int temp = nums[i];
				for (size_t k = i; k > j; k--)
					nums[k] = nums[k-1];
				nums[j] = temp;
				break;
			}
		}
	}
}

// Takes a reference to an unsorted list as an input and sorts the list using
// the merge sort method.
void mergeSort(vector<int> &nums)
{
	if (nums.size() != 1)
	{
		size_t mid = nums.size()/2;
		vector<int> left;
		vector<int> right;
		for (size_t i = 0; i < nums.size(); i++)
		{
			if (i < mid)
				left.push_back(nums[i]);
			else
				right.push_back(nums[i]);
		}
		mergeSort(left);
		mergeSort(right);
		
		size_t l = 0;
	 	size_t r = mid;
	
		for (size_t i = 0; i < nums.size(); i++)
		{
			if (l == mid)
			{
				nums[i] = right[r-mid];
				r++;
			}
			else if (r == nums.size())
			{
				nums[i] = left[l];
				l++;
			}
			else if (left[l] <= right[r-mid])
			{
				nums[i] = left[l];
				l++;
			}
			else if (right[r-mid] < left[l])
			{
				nums[i] = right[r-mid];
				r++;
			}
		}
	}	
}

// Takes a reference to an unsorted list as an input and sorts the list using
// the quick sort method.
void quickSort(vector<int> &nums)
{
	if (nums.size() >= 2)
	{
		int pivot = nums[0];
		vector<int> left;
		vector<int> right;
	
		for (size_t i = 1; i < nums.size(); i++)
		{
			if (nums[i] <= pivot)
				left.push_back(nums[i]);
			else
				right.push_back(nums[i]);
		}
		quickSort(left);
		quickSort(right);

		nums.clear();
		for (size_t i = 0; i < left.size(); i++)
			nums.push_back(left[i]);
		nums.push_back(pivot);
		for (size_t i = 0; i < right.size(); i++)
                        nums.push_back(right[i]);
	}
		
	
}


