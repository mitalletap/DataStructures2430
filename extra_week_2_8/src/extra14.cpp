#include <iostream>
#include <queue>
#include <stack>
using namespace std;

// Worked with Kevin!

//105943
int main(){
	int start_s=clock();
	stack<int> stack, temp;
	int n, i;
	bool isPrime = true;
	cout << "Enter a positive integer: ";
	cin >> n;
	cout << "One Moment Please :)" << endl;
	for(int i = 0; i <= n; n--){
		for(i = 2; i <= n / 2; ++i)
			{
				if(n % i == 0)
					{
					isPrime = false;
					break;
				}
			}

			if (isPrime){
				//cout << n << " is a prime number" << endl;
				stack.push(n);

			} else{
				//cout << n <<  " is not a prime number" << endl;

			}
			isPrime = true;
	}

	while(!stack.empty()){
		temp.push(stack.top());
		stack.pop();
	}


	while(!temp.empty()){
		cout << "Top: " << temp.top() << endl;
		temp.pop();
	}

	int stop_s=clock();
	cout << "time: " << (stop_s-start_s)/double(CLOCKS_PER_SEC)*1000 << " seconds!"<< endl;
	return 0;


}
