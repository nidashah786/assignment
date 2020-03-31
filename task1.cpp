#include <iostream>
#include <fstream>
#include <string>
#include <queue>
#include <list>
#include <stack>
using namespace std;

struct Node
{
	int state;
	Node * parent;
	int action;
	int cost;
};

int main()
{
	int M, N, T;
	string *states, *rules, *testCasesStart, *testCasesGoal;

	ifstream fin;

	fin.open("input.txt");

	if (fin)
	{
		fin >> M >> N >> T;

		states = new string[M];
		rules = new string[N];
		testCasesStart = new string[T];
		testCasesGoal = new string[T];

		fin.get(); fin.get();

		for (int i = 0; i < M; i++)
		{
			getline(fin, states[i]);
		}

		fin.get();

		for (int i = 0; i < N; i++)
		{
			getline(fin, rules[i]);
		}

		fin.get();

		int **transitionMatrix = new int*[M];
		for (int i = 0; i < M; i++)
		{
			transitionMatrix[i] = new int[N];
		}

		for (int i = 0; i < M; i++)
		{
			for (int j = 0; j < N; j++)
			{
				fin >> transitionMatrix[i][j];
			}
		}

		fin.get(); fin.get();

		for (int i = 0; i < T; i++)
		{
			getline(fin, testCasesStart[i], '-');
			getline(fin, testCasesGoal[i]);
		}

		fin.close();

		for (int i = 0; i < T; i++)
		{
			cout << "Test case " << i + 1 << ": " << endl;

			Node *start = new Node;
			Node *temp;

			int startState = -1, finalState = -1;
			for (int j = 0; j < M; j++)
			{
				if (testCasesStart[i] == states[j])
				{
					start->state = j;
					start->parent = NULL;
					start->action = -1;
					start->cost = 0;
					startState = start->state;
				}
				if (testCasesGoal[i] == states[j])
				{
					finalState = j;
				}
			}
			if (startState == -1)
			{
				cout << "start state not found" << endl;
				continue;
			}
			if (finalState == -1)
			{
				cout << "final state not found" << endl;
				continue;
			}


			queue<Node*> q;
			list<int> discoveredStates;
			discoveredStates.push_front(startState);
			bool alreadyDiscovered = false;

			while (startState != finalState)
			{
				for (int j = 0; j < N; j++)
				{
					for (std::list<int>::iterator it = discoveredStates.begin(); it != discoveredStates.end(); ++it) {
						if (transitionMatrix[startState][j] == *it)
						{
							alreadyDiscovered = true;
						}
					}
					if (alreadyDiscovered)
					{
						alreadyDiscovered = false;
						continue;
					}
					else
					{
						temp = new Node;
						temp->action = j;
						temp->parent = start;
						//cout << temp->parent << endl;
						temp->cost = temp->parent->cost + 1;
						temp->state = transitionMatrix[startState][j];
						q.push(temp);
						//cout << temp->action << " " << temp->cost << " " << temp->state << " " << temp->parent->state << endl;
					}
				}
				start = q.front();
				q.pop();
				startState = start->state;
				discoveredStates.push_front(startState);
			}
			//goal.action = start.action;
			//goal.cost = start.cost;
			//goal.state = start.state;
			//goal.parent = start.parent;

			stack<Node*> s;
			while (start->parent != NULL)
			{
				s.push(start);
				//start->action = start->parent->action;
				//goal->cost = goal->parent->cost;
				//goal->state = goal->parent->state;
				start = start->parent;
			}

			while (!s.empty())
			{
				Node *temp;
				temp = s.top();
				s.pop();
				cout << rules[temp->action];
				if (!s.empty())
				{
					cout << "->";
				}
			}
			cout << endl;
		}
	}
	else
	{
		cout << "File not opened" << endl;
	}
	return 0;
}