#pragma once
#include<vector>
using namespace std;	

#include "constents.h";


int digitsCach[2*N]; // extra memory just in case
int digits(int n) { // returns len
	int len = 0;
	while (n) {
		digitsCach[len] = n % 10;
		n /= 10;
		len++;
	}
	reverse(digitsCach, digitsCach + len);
	return len;
}


bool nextDigitCach[10];
void copyNextDigitCach(bool* target) {
	for (int i = 0; i < 10; i++)
		target[i] = nextDigitCach[i];
}

void intresectWithNextDigitCach(bool* target) {
	for (int i = 0; i < 10; i++)
		target[i] = target[i] && nextDigitCach[i];
}

class ST {
public:
	bool end = false;
	ST* next[10];

	ST() {
		for (int i = 0; i < 10; i++)
			next[i] = NULL;
	}

	void add(int n, int index = 0) {
		int len = digits(n);
		add(digitsCach, len, index); 
	}
	void add(int digits[], int digLen, int index = 0) {
		if (index == digLen) {
			end = true;
			return;
		}

		if (!next[digits[index]])
			next[digits[index]] = new ST();

		next[digits[index]]->add(digits, digLen, index + 1);
	}

	bool check(int n, int index = 0) { 
		int len = digits(n);
		return check(digitsCach, len, index); 
	}
	bool check(int digits[], int digLen, int index = 0) {
		if (index == digLen)
			return end;

		if (!next[digits[index]])
			return false;

		return next[digits[index]]->check(digits, digLen, index + 1);
	}


	void nextDigits(int n, int index = 0) { 
		int len = digits(n);
		nextDigits(digitsCach, len, index);
	} 
	void nextDigits(int digits[], int digLen, int index = 0) {

		if (index == digLen) {
			for (int i = 0; i < 10; i++)
				nextDigitCach[i] = (next[i] != NULL);

			return;
		}

		if (!next[digits[index]])
			return;
		next[digits[index]]->nextDigits(digits, digLen, index + 1);
	}
};