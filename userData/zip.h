#pragma once
#include <string>
#include <vector>

using namespace std;

class zip
{
public:
	zip() = default;
	~zip() = default;

	vector<int> compress(vector<int> ans);
	vector<vector<int>> uncompress(vector<int> final);
};
