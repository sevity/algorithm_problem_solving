#include <stdio.h>
#include <assert.h>
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

vector<int> gen(int n)
{
    vector<int> v;
    for(int i=0;i<n;i++) v.push_back(i+1);
    random_shuffle(v.begin(), v.end());
    return v;
}

void print_vector(vector<int> v)
{
    for(int i=0;i<v.size();i++) printf("%d, ", v[i]);
    printf("\n");
}


vector<int> quick(vector<int> v)
{
    if(v.size()==0) return v;
    int pivot = v[0];
    vector<int> l,r;
    for(int i=1;i<v.size();i++)
        if(v[i] < pivot) l.push_back(v[i]);
        else r.push_back(v[i]);
    l = quick(l);
    r = quick(r);
    l.push_back(pivot);
    for(int i=0;i<r.size();i++)
        l.push_back(r[i]);
    return l;
}

void quick_inplace(vector<int>&v, int s, int e)
{
    if(s >= e) return;
    int pivot = v[s];
    int j=s;
    for(int i=s+1;i<e;i++)
    {
        if(v[i]<pivot) swap(v[i], v[++j]);
    }
    swap(v[j], v[s]);
    quick_inplace(v, s, j);
    quick_inplace(v, j+1, e);
}

vector<int> ref_sort(vector<int> v)
{
    sort(v.begin(), v.end());
    return v;
}

int main(void)
{
    const int TEST_CNT = 1000;
    for(int i=0;i<TEST_CNT;i++)
    {
        vector<int> v = gen(100);
        vector<int> v1 = quick(v);
        vector<int> v2 = ref_sort(v);
        quick_inplace(v, 0, v.size());
        assert(v1 == v2);
        assert(v1 == v);
    }
    printf("O.K.\n");
    return 0;
}
