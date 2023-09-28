/*
The following divide-and-conquer algorithm is proposed for finding the simultaneous
maximum and minimum: If there is one item, it is the maximum and
minimum, and if there are two items, then compare them, and in one comparison
you can find the maximum and minimum. Otherwise, split the input into two
halves, divided as evenly as possibly (if N is odd, one of the two halves will have
one more element than the other). Recursively find the maximum and minimum
of each half, and then in two additional comparisons produce the maximum and
minimum for the entire problem.
*/

#include <iostream>
#include <vector>

using namespace std;

vector<int> find_min_max(vector<int> v);

int main()
{
    vector<int> test_vector = { 23, 15, 86, 9, 30 };
    vector<int> min_max;
    min_max = find_min_max(test_vector);
    
    cout << "Minimum: " << min_max[0] << endl;
    cout << "Maximum: " << min_max[1] << endl;

    return 0;
}

vector<int> find_min_max(vector<int> v) {
    vector<int> min_max (2);

    // If there is one item, it is the maximum and minimum
    if (v.size() == 1) {
        min_max[0] = v[0];
        min_max[1] = v[0];
        return min_max;
    }

    //if there are two items, then compare them, and in one comparison you can find the maximum and minimum
    else if (v.size() == 2) {
        if (v[0] > v[1]) {
            min_max[0] = v[1];
            min_max[1] = v[0];
        }
        else {
            min_max[0] = v[0];
            min_max[1] = v[1];
        }
        return min_max;
    }

    else {
        int mid = v.size() / 2;
        vector<int> left_side(v.begin(), v.begin() + mid);  //Otherwise, split the input into two halves, divided as evenly as possibly
        vector<int> right_side(v.begin() + mid, v.end());
        vector<int> left = find_min_max(left_side);       //Recursively find the maximum and minimum of each half, and then 
        vector<int> right = find_min_max(right_side);     
        if (left[0] > right[0]) { //find min              //in two additional comparisons produce the maximum and minimum for the entire problem.
            min_max[0] = right[0];
        }
        else {
            min_max[0] = left[0];
        }
        if (left[1] > right[1]) { //find max 
            min_max[1] = left[1];
        }
        else {
            min_max[1] = right[1];
        }
    }

    return min_max;
}
