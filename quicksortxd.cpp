#include <bits/stdc++.h>
using namespace std;

void srt(vector<int> &a) {
    if(a.size() <= 1)
        return;
    // l is pivot
    vector<int> left, right;
    // iscie od i == 0 hmmmm
    for(int i = 1; i < a.size(); ++i) {
        (a[i] <= a[0] ? left : right).push_back(a[i]);
    }
    srt(left);
    srt(right);
    // i don't have to do this here xd that's for mergesort, przecie all w right są > w left giga łeb
    /* auto it1 = left.begin(), it2 = right.begin();
    for(int i = 0; i < a.size(); ++i) {
        if(it1 == left.end() || (it2 != right.end() && *it2 <= *it1))
            a[i] = *it2;
        else
            a[i] = *it1;
        cout << a[i] << ' ';
    } */
    int pivot = a[0];
    memcpy(&a[0], &left[0], left.size() << 2);
    // copy(left.begin(), left.end(), a.begin());
    a[left.size()] = pivot;
    memcpy(&a[left.size()+1], &right[0], right.size() << 2);
    // copy(right.begin(), right.end(), a.begin() + left.size() + 1);
    for(int i = 0; i < a.size(); ++i) {
        cout << a[i] << ' ';
    }
    cout << '\n';
}

void quickSort(vector <int> &arr) {
    // srt(arr, 0, arr.size() - 1);
    srt(arr);
}


int main()
{
    int n;
    cin >> n;

    vector <int> arr(n);
    for(int i = 0; i < (int)n; ++i) {
        cin >> arr[i];
    }

    quickSort(arr);

    return 0;
}
