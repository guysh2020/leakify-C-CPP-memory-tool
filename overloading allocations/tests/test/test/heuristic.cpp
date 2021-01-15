#include"heuristic.h"


double MazeAirDistance::calculate(mazeState* curr, mazeState* goal, double step_cost)
{
	pair<int, int> from = curr->getState()->getPos().getPosition();
	pair<int, int> to = goal->getState()->getPos().getPosition();

	int row_d = to.first - from.first;
	int col_d = to.second - from.second;

	double ans = sqrt(double(pow(double(row_d), 2) + pow(double(col_d), 2)));

	return ans * step_cost;
}


double MazeManheten::calculate(mazeState* curr, mazeState* goal, double step_cost)
{
	pair<int, int> from = curr->getState()->getPos().getPosition();
	pair<int, int> to = goal->getState()->getPos().getPosition();

	int row_d = to.first - from.first;
	int col_d = to.second - from.second;

	int ans = row_d + col_d;
	return (double)ans * step_cost;
}