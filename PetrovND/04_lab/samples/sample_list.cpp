#include "list.h"

int main() {
	TList<int> l;
	while (true) {
		cout << "Enter Action:" << endl;
		cout << "1. Insert First" << endl << "2. Insert Last" << endl <<
			"3. Insert After" << endl << "4. Insert Before" << endl << "5. Descending Insert" << 
			endl << "6. Remove Element" << endl << "7. Output List" << endl << "8. EXIT" << endl;

		int userInput, userInput1;
		cin >> userInput;
		switch (userInput){
		case 1:
			cout << "Enter element: ";
			cin >> userInput;
			l.insertFirst(userInput);
			break;
		case 2:
			cout << "Enter element: ";
			cin >> userInput;
			l.insertLast(userInput);
			break;
		case 3:
			cout << "Enter data and after data: ";
			cin >> userInput >> userInput1;
			l.insertAfter(userInput, userInput1);
			break;
		case 4:
			cout << "Enter data and before data: ";
			cin >> userInput >> userInput1;
			l.insertBefore(userInput, userInput1);
			break;
		case 5:
			cout << "Enter element: ";
			cin >> userInput;
			l.descendingInsert(userInput);
			break;
		case 6:
			cout << "Enter element: ";
			cin >> userInput;
			l.remove(userInput);
			break;
		case 7:
			for (auto& el : l) {
				cout << el << ", ";
			}
			cout << endl;
			break;
		default:
			return 0;
		}
	}
	return 0;
}