#pragma once
#include <vector>
#include <iostream>
#include <fstream>
using namespace std;

#include "searchTree.h"

#include <chrono>


void tryConstract(int row);
vector<int> allPosNextRow(int row);


ST* root = new ST();

int howManyFound = 0;
vector<vector<vector<int>>> allSquares;

ofstream outputFile;


chrono::steady_clock::time_point startTime;
template <
	class result_t = std::chrono::milliseconds,
	class clock_t = std::chrono::steady_clock,
	class duration_t = std::chrono::milliseconds
>
float deltaTime() { // in ms
	return std::chrono::duration_cast<result_t>(clock_t::now() - startTime).count();
}


int sumDigits(int n) {
	int sum = 0;
	while (n) {
		sum += n % 10;
		n /= 10;
	}
	return sum;
}


bool isPrime(int n) {
	if (n <= 1) return false;
	if (n <= 3) return true;
	if (n % 2 == 0 || n % 3 == 0) return false;
	for (int i = 5; i * i <= n; i += 6) {
		if (n % i == 0 || n % (i + 2) == 0) return false;
	}
	return true;
}


vector<int> allPrimesWithNDigits(int N, int A=-1) {
	int end = pow(10, N);
	int start = pow(10, N - 1);
	vector<int> primes;
	for (int i = start; i < end; i++) {
		if ((A == -1 || sumDigits(i) == A) && isPrime(i)) 
			primes.push_back(i);
	}
	return primes;
}


void print(int n) { outputFile << n << endl; }
void print(const vector<int> &vec) {
	#ifdef STORE_IN_FILE
		outputFile << "[";
		for (int i = 0; i < vec.size(); i++) {
			outputFile << vec[i];
			if (i != vec.size() - 1)
				outputFile << ", ";
		}
		outputFile << "]\n";
	#endif // STORE_IN_FILE
}

void printSquare() {
	#ifdef STORE_IN_FILE
		for(int i = 0; i < N; i++){
			for (int j = 0; j < N; j++) {
				outputFile << sq[i][j] << " ";
			}
			outputFile << endl;
		}
		outputFile << "\n";
	#endif // STORE_IN_FILE
}



void tryConstractMain(int sp[]) {
	for (int i = 0; i < N; i++) {
		sq[0][i] = sp[i];
	}

	tryConstract(1);
}

void fillRow(int p, int row) {
	digits(p);
	for (int i = 0; i < N; i++) {
		sq[row][i] = digitsCach[i];
	}
}

vector<vector<int>> getSqVec() {
	vector<vector<int>> sqvec(N, vector<int>(N));
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			sqvec[i][j] = sq[i][j];
	return sqvec;
}

void tryConstract(int row) {
	if (row == N) {
		allSquares.push_back(getSqVec());
		printSquare();
		howManyFound++;
		return;
	}

	vector<int> posPrimes = allPosNextRow(row);
	for (int p : posPrimes) {
		fillRow(p, row);
		tryConstract(row + 1);
	}
}



vector<int> allPosNextRow(int row) {
	bool pos[N][10];
	int num[N];

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < row; j++) {
			num[j] = sq[j][i];
		}

		root->nextDigits(num, row);
		copyNextDigitCach(pos[i]);
	}

	for (int j = 0; j < row; j++) {
		num[j] = sq[j][j];
	}
	root->nextDigits(num, row);
	intresectWithNextDigitCach(pos[row]);
	
	
	for (int j = 0; j < row; j++) {
		num[j] = sq[j][N-j-1];
	}
	root->nextDigits(num, row);
	intresectWithNextDigitCach(pos[N - row - 1]);


	vector<pair<ST*, int>> ss, next;
	ss.push_back({ root, 0 });
	for (int i = 0; i < N; i++) {
		for (int digit = 0; digit < 10; digit++) {
			if (pos[i][digit]) 
				for (const auto& p : ss) {
					if (p.first->next[digit] != NULL)
						next.push_back({ p.first->next[digit], p.second * 10 + digit });
				}
			
		}
		
		swap(ss, next);
		next.clear();
	}
	
	vector<int> out;
	for (const auto& p : ss) {
		out.push_back(p.second);
	}
	return out;
}


void addAllWithA(int A) {
	root = new ST;
	vector<int> primes = allPrimesWithNDigits(N, A);

	for (int p : primes)
		root->add(p);

	for(int i = 0; i < primes.size(); i++){
		digits(primes[i]);
		tryConstractMain(digitsCach);
		
		#ifdef  PRINT_PROGRESS
			cout << i + 1 << " / " << primes.size() << " | " << howManyFound << " | In: " << A  << " :: dt=" << deltaTime()/1000 << "s\n";
		#endif //  PRINT_PROGRESS
	}
}



int main() {
	outputFile.open("FILE_PATH");
	startTime = std::chrono::steady_clock::now();

	for (int A = 0; A <= 9*N; A++) {
		#ifdef PRINT_PROGRESS
			cout << "\n\nA:" << A << "\n";
		#endif // PRINT_PROGRESS
		addAllWithA(A);
	}

	cout << "\nTime takem: " << deltaTime()/1000 << "s\n";
	outputFile << "Time takem: " << deltaTime() / 1000 << "s\n";
	
	outputFile.close();
}



