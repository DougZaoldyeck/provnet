#include <iostream>
#include <string>
#include <stdio.h>
#include <math.h>
#include <vector>
#include <map>

/* compile: g++ main.cpp -o main
 * sample input
 *      array:1,1,1,1,2,2,3,3,4,4,4,4,4,4,5,5,6,6,6,6,6,6,6,6,6,7,7,8,9
 *      k:3
 * sample output
 *      1,6,4
 * */

using namespace std;

class TopKElements {
private:
    vector<int> unique;
    map<int, int> count_map;

public:
    int partition(int left, int right, int pivot_index) {
        int pivot_frequency = this->count_map[this->unique[pivot_index]];
        // 1. move pivot to the end
        swap(this->unique[pivot_index], this->unique[right]);

        // 2. move all less frequent elements to the left
        int store_index = left;
        for (int i = left; i <= right; i++) {
            if (this->count_map[this->unique[i]] < pivot_frequency) {
                swap(this->unique[store_index], this->unique[i]);
                store_index += 1;
            }
        }

        // 3. move pivot to its final place
        swap(this->unique[right], this->unique[store_index]);

        return store_index;
    }

    void quickselect(int left, int right, int k_smallest) {
        /*
        Sort a list within left..right till kth less frequent element
        takes its place. 
        */

        // base case: the list contains only one element
        if (left == right) return;

        int pivot_index = left + rand() % (right - left + 1);

        // find the pivot position in a sorted list
        pivot_index = partition(left, right, pivot_index);

        // if the pivot is in its final sorted position
        if (k_smallest == pivot_index) {
            return;
        } else if (k_smallest < pivot_index) {
            // go left
            quickselect(left, pivot_index - 1, k_smallest);
        } else {
            // go right
            quickselect(pivot_index + 1, right, k_smallest);
        }
    }

    vector<int> topKFrequent(vector<int>& nums, int k) {
        // build hash map : element and how often it appears
        for (int n : nums) {
            this->count_map[n] += 1;
        }

        // array of unique elements
        size_t n = this->count_map.size();
        for (pair<int, int> p : this->count_map) {
            this->unique.push_back(p.first);
        }

        // kth top frequent element is (n - k)th less frequent.
        // Do a partial sort: from less frequent to the most frequent, till
        // (n - k)th less frequent element takes its place (n - k) in a sorted array.
        // All element on the left are less frequent.
        // All the elements on the right are more frequent.
        quickselect(0, n - 1, n - k);
        // Return top k frequent elements
        vector<int> top_k_frequent(k);
        copy(this->unique.begin() + n - k, this->unique.end(), top_k_frequent.begin());
        return top_k_frequent;
    }
};

int main()
{
    vector<int> array, results; //initiate the original input array of MinHash values that equals
    cout << "Input the array of same MinHash values occurrences:" ;

    int k, i=0;
    do {
        cin >> i;
        array.push_back(i);
    }while (getchar() != '\n');


    cout << "Input k:" ; //top-k most frequent elements you want to find
    cin >> k;
    TopKElements top_k;
    results=top_k.topKFrequent(array,k);
    for(int j=0; j <results.size(); j++)
    {
        if(j==results.size()-1)
            cout << results[j] << '\n';
        else
            cout << results[j] << ",";
    }
    return 0;
}