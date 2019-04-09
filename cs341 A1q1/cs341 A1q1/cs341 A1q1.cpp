// This is an assignment solution for CS341 A1q1
// 

#include <iostream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;


int main()
{
	string input;
	getline(cin, input);
	istringstream iss1{ input };
	long long int n = 0;
	iss1 >> n;  //first line to get n

	getline(cin, input);
	istringstream iss2{ input };
	long long int* fx = new long long int[n + 1];
	long long int tempnum;
	long long int tmpi = 0;
	while ((iss2 >> tempnum) && (tmpi <= n)) {
		fx[tmpi] = tempnum;
		tmpi += 1;

	} // second line to get f(x);

	getline(cin, input);
	istringstream iss3{ input };
	long long int* gx = new long long int[n + 1];
	tmpi = 0;
	while ((iss3 >> tempnum) && (tmpi <= n)) {
		gx[tmpi] = tempnum;
		tmpi += 1;
	} // third line to get g(x);


	  //precompute k mult results, for all k <= n; 
	vector<long long int> karr;
	long long int tmpk;
	for (long long int i = 0; i <= n; ++i) {
		tmpk = fx[i] * gx[i];  // precomput and save the result of ak*bk.
		karr.push_back(tmpk);
	}

	//precompute s to t such that s+t = i;
	long long int s, t = 0;

	vector<long long int> carr;
	long long int tmpc;
	tmpc = karr[0];
	carr.push_back(tmpc);
	for (long long int i = 1; i < (2 * n); ++i) {
		s = 0;
		t = 0;
		tmpc = 0;
		if (i % 2 == 0) { //even
			t = i - s;
			while (t > n) { //have to ignore duplicated cases.
				s += 1;
				t = i - s;
			}
			while (((s <= n) && (t <= n)) && (s < t)) { //same reason
				tmpc += (fx[s] + fx[t]) * (gx[s] + gx[t]) - karr[s] - karr[t]; // karatsuba
				s += 1;
				t = i - s;
			}
			tmpc += karr[i / 2]; // from observation, even case add one term from karr[i/2]
			carr.push_back(tmpc);
		}
		else { //odd
			t = i - s;
			while (t > n) {
				s += 1;
				t = i - s;
			}
			while (((s <= n) && (t <= n)) && (s < t)) {
				tmpc += (fx[s] + fx[t]) * (gx[s] + gx[t]) - karr[s] - karr[t];
				s += 1;
				t = i - s;
			}
			carr.push_back(tmpc);
		}
	}
	tmpc = karr[n];
	carr.push_back(tmpc);

	for (long long int i = 0; i < carr.size(); ++i) {
		cout << carr[i] << " ";
	}

	delete[] fx; //free int arr
	delete[] gx;

	return 0;
}

