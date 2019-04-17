#include<cstdio>
#include<vector>
#include<fstream>
#include<iostream>

using namespace std;
int pCnt = 5;
int rCnt = 3;

int available[4];
int maxR[10][4];
int allocationR[10][4];

int tempRequest[4];

int Work[4];
bool Finish[10];

int tempAlloctionR[4];
int tempAvailable[4];

bool safetyAlgorithm() {
	for (int i = 0; i < rCnt; i++) {
		Work[i] = available[i];
	}

	for (int i = 0; i < pCnt; i++) {
		Finish[i] = false;
	}

	int state = 0;
	
	while (true) {

		if (state == pCnt)
			break;
		if (Finish[state] == false) {
			int sw = 0;
			
			for (int i = 0; i < rCnt; i++) {
				if ((maxR[state][i] - allocationR[state][i]) > Work[i])
				{
					sw = 1;
					break;
				}

			}
			
			if (sw == 0)
			{
				for (int i = 0; i < rCnt; i++) {
					Work[i] += allocationR[state][i];
				}
				Finish[state] = true;
				state = -1;
			}
		}
		state++;

	}
	for (int i = 0; i < pCnt; i++) {
		if (Finish[i] == false)
			return false;
	}
	return true;


}


int main() {
	ifstream input("available.txt");
	for (int i = 0; i < rCnt; i++) {
		input >> available[i];
	}
	input.close();

	ifstream input1("max.txt");
	for (int i = 0; i < pCnt; i++) {
		for (int j = 0; j < 3; j++) {
			input1 >> maxR[i][j];
		}
	}
	input1.close();
	
	ifstream input2("allocation.txt");
	for (int i = 0; i < pCnt; i++) {
		for (int j = 0; j < rCnt; j++) {
			input2 >> allocationR[i][j];
		}
	}
	input2.close();

	while (true) {
		cout << "Insert a resource request: ";
		cin >> tempRequest[0];
		if (tempRequest[0] == -1)
			break;
		for (int i = 1; i < 1+rCnt; i++) {
			cin >> tempRequest[i];
		}
		
		int sw = 0;
		for (int i = 0; i < rCnt; i++) {
			if (tempRequest[i + 1] > maxR[tempRequest[0]][i] - allocationR[tempRequest[0]][i]) {
				sw = 1;
				break;
			}
		}
		if (sw == 1)
		{
			cout << "Rejected!\n";
			continue;
		}
		sw = 0;
		for (int i = 0; i < rCnt; i++) {
			if (tempRequest[i + 1] > available[i]) {
				sw = 1;
				break;
			}
		}
		if (sw == 1)
		{
			cout << "Rejected!\n";
			continue;
		}
		for (int i = 0; i < rCnt; i++) {
			tempAlloctionR[i] = allocationR[tempRequest[0]][i];
			allocationR[tempRequest[0]][i] += tempRequest[1 + i];
		}
		for (int i = 0; i < rCnt; i++) {
			tempAvailable[i] = available[i];
			available[i] -= tempRequest[1 + i];
		}
		if (safetyAlgorithm() == false) {
			cout << "Rejected!\n";
			
			for (int i = 0; i < rCnt; i++) {
				allocationR[tempRequest[0]][i]= tempAlloctionR[i];
				
			}
			for (int i = 0; i < rCnt; i++) {
				available[i] = tempAvailable[i];
			}
		}
		else {
			cout << "Granted!\n";
		}
	}
	





}