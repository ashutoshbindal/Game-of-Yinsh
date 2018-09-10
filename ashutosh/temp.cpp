#include <iostream>
#include <string>
#include <vector>

using namespace std;

void split(string str, string splitBy, vector<std::string>& tokens)
{
    tokens.push_back(str);
    size_t splitAt;
    size_t splitLen = splitBy.size();
    std::string frag;
    while(true)
    {
        frag = tokens.back();
        splitAt = frag.find(splitBy);
        if(splitAt == string::npos)
        {
            break;
        }
        tokens.back() = frag.substr(0, splitAt);
        tokens.push_back(frag.substr(splitAt+splitLen, frag.size()-(splitAt+splitLen)));
    }
}

int main()
{
    vector<pair<int, int> > a;
    int b = 1;
    int c = 2;
    pair<int, int> temp (b, c);
    // a.push_back(temp);
    a.push_back(pair<int, int>(b,c));
    cout<<a[0].first<<" "<<a[0].second<<endl;
    return 0;
}
