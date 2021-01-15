#include"zip.h"


vector<int> zip::compress(vector<int> ans)
{
	vector<int> comp, final;
	string tmp;

	int num = ans[0];
	comp.push_back(ans[0]);				// name length

	int i;
	for (i = 1; i <= num; i++)
		comp.push_back(ans[i]);


	for (int j = 0; j < 5; j++)
		comp.push_back(ans[i++]);


	for (i; i < (signed)ans.size();)
	{
		tmp.clear();
		for (int j = 0; j < 4; j++)
			tmp += ans[i++] + 48;

		if (tmp == "0000")
			comp.push_back('a');

		if (tmp == "0001")
			comp.push_back('b');

		if (tmp == "0010")
			comp.push_back('c');

		if (tmp == "0011")
			comp.push_back('d');

		if (tmp == "0100")
			comp.push_back('e');

		if (tmp == "0101")
			comp.push_back('f');

		if (tmp == "0110")
			comp.push_back('g');

		if (tmp == "0111")
			comp.push_back('h');

		if (tmp == "1000")
			comp.push_back('i');

		if (tmp == "1001")
			comp.push_back('j');

		if (tmp == "1010")
			comp.push_back('k');

		if (tmp == "1011")
			comp.push_back('l');

		if (tmp == "1100")
			comp.push_back('m');

		if (tmp == "1101")
			comp.push_back('n');

		if (tmp == "1110")
			comp.push_back('o');

		if (tmp == "1111")
			comp.push_back('p');

	}

	num = comp[0];
	final.push_back(comp[0]);

	for (i = 1; i <= num; i++)
		final.push_back(comp[i]);


	for (int j = 0; j < 5; j++)
		final.push_back(comp[i++]);


	for (i; i < (signed)comp.size();)
	{
		int count = 1;
		int j = i;
		while (j + 1 < (signed)comp.size() && comp[j] == comp[j + 1])
		{
			count++;
			j++;
		}
		if (count > 3)
		{
			i = j;
			final.push_back('X');
			final.push_back(count);
			final.push_back(comp[i++]);
		}
		else
			final.push_back(comp[i++]);

	}
	return final;
}

vector<vector<int>> zip::uncompress(vector<int> final)
{
	vector<vector<int>> first;
	string tmp;

	first.resize(2);

	int num = final[0];
	int i;
	int row = 0;

	for (i = 1; i <= num; i++)
		first[row].push_back(final[i]);

	row++;

	for (int j = 0; j < 5; j++)
		first[row].push_back(final[i++]);

	row++;


	vector<int> vec;

	for (i; i < (signed)final.size() - 1; i++)
	{
		num = 1;
		if (final[i] == 'X')
		{
			num = final[++i];
			i++;;
		}

		tmp.clear();
		if (final[i] == 'a')
			tmp = "0000";

		if (final[i] == 'b')
			tmp = "0001";

		if (final[i] == 'c')
			tmp = "0010";

		if (final[i] == 'd')
			tmp = "0011";

		if (final[i] == 'e')
			tmp = "0100";

		if (final[i] == 'f')
			tmp = "0101";

		if (final[i] == 'g')
			tmp = "0110";

		if (final[i] == 'h')
			tmp = "0111";

		if (final[i] == 'i')
			tmp = "1000";

		if (final[i] == 'j')
			tmp = "1001";

		if (final[i] == 'k')
			tmp = "1010";

		if (final[i] == 'l')
			tmp = "1011";

		if (final[i] == 'm')
			tmp = "1100";

		if (final[i] == 'n')
			tmp = "1101";

		if (final[i] == 'o')
			tmp = "1110";

		if (final[i] == 'p')
			tmp = "1111";

		for (int n = 0; n < num; n++)
		{
			first.push_back(vec);
			for (int t = 0; t < 4; t++)
				first[row].push_back(tmp[t] - 48);

			row++;
		}
	}


	return first;

};


