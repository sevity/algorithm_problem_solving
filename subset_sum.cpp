#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <map>
#include <cassert>
#include <cstring>
using namespace std;

//#define NOT_IMPLMENTED(exp) do {if(!exp) assert(false);} while(0)

//end not-inclusive
//[start, end)
//if b_allow_duplicate is false, elements will not duplicated
vector<int> get_random_array(int start, int end, int count, bool b_allow_duplicate = true, bool b_avoid_zero = true)
{
    assert(b_allow_duplicate == true); // false, not implemented
    int offset = 0;
    if(start <0) offset=start;
    start += offset;
    end += offset;
    vector<int> r;
    for(int i=0;i<count;i++)
    {
        int n1 = rand() % (end - start) + start - offset;
        if(b_avoid_zero && n1==0) n1=1;
        r.push_back(n1);
    }
    return r;
}

void print(vector<int>& v)
{
    printf("input: ");
    for(int i=0;i<(int)v.size();i++) printf("%d ", v[i]);
    printf("\n");
}

bool go(vector<int>&v, int ix, int cur_sum, int count)
{
    if(ix==(int)v.size())
    {
        if(cur_sum==0&&count>0) return true;
        return false;
    }
    bool r1 = go(v, ix+1, cur_sum+v[ix], count+1);
    bool r2 = go(v, ix+1, cur_sum, count);
    return r1 || r2;
}

bool recursive(vector<int>& v)
{
    return go(v, 0, 0, 0);
}

bool naive(vector<int>& v)
{
    int n = (int)v.size();
    assert(n < 10);
    for(int i=1;i<(1<<n);i++)
    {
        int s = 0;
        for(int j=0;j<n;j++) if((1<<j)&i) s+=v[j];
        if(s==0) return true;
    }
    return false;
}


bool dp(vector<int>& v)
{
    map<int, bool> m, m2;
    for(int i=0;i<(int)v.size();i++)
    {
        m2 = m;
        for(auto it=m.begin();it!=m.end();it++)
        {
            m2[it->first + v[i]] = true;
        }
        m2[v[i]] = true;
        m = m2;
    }
    if (m[0]) return true;
    return false;

}

int main()
{
    for(int i=0;i<100000;i++)
    {
        vector<int> v = get_random_array(-20, 20, 6);
        print(v);
        bool r1 = naive(v);
        bool r2 = recursive(v);
        bool r3 = dp(v);
        assert(r1 == r2 && r2 == r3);
        printf("result: %s\n", r1?"possible":"impossible");
    }

    return 0;
}
