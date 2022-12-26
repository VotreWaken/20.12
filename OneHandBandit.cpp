#include <iostream>
#include <Windows.h>
using namespace std;

// Queue Class
class QueueRing
{
public:
	// Default constructor
	QueueRing() : max_(3), top_(0), QueuePtr_(new char[3])
	{

	}

	// Constructor with Parametres
	QueueRing(int MaxValue)
	{
		max_ = MaxValue;
		top_ = 0;
		QueuePtr_ = new char[MaxValue];
	};

	// Add Element to Queue
	void AddToQueue(int value)
	{
		if (top_ >= max_)
			return;
		QueuePtr_[top_++] = value;
	}

	// Show Queue
	void Show() const 
	{
		int j = 200;
		for (int i = 0; i < 3; i++)
		{
			Sleep(j);
			cout << QueuePtr_[i] << " ";
			j += 150;
		}
		cout << endl;
	}

	// Check Win Method
	int CheckWin(int value) const 
	{
		return QueuePtr_[value];
	}

	// Random Swap Method
	void RandomSwap()   
	{
		int q = rand() % 20;
		for (int k = 1; k < q; k++)
			QueuePtr_[top_] = Extract();
	}

	// Return if Empty
	bool IsEmpty() const 
	{
		return top_ == 0;
	}

	// Extract Method
	bool Extract() 
	{
		if (!IsEmpty())
		{
			int temp = QueuePtr_[0];

			for (int i = 1; i < max_; i++)
				QueuePtr_[i - 1] = QueuePtr_[i];

			QueuePtr_[max_ - 1] = temp;
			return 1;
		}
		else return 0;
	}

	// Destructor 
	~QueueRing()
	{
		delete[] QueuePtr_;
	};

private:

	char* QueuePtr_;
	int top_;
	int max_;
};

// Singleton Pattern Interface 
class SingleGameInterface
{
private:

	static SingleGameInterface* Game_;
	int value_;
	QueueRing* Queue_;
	int bet_;

	// Constructor with Parametres
	SingleGameInterface(int value)
	{
		value_ = value;
		Queue_ = nullptr;
		bet_ = 0;
	};

public:

	// Get Class Pointer
	static SingleGameInterface* GetPtr()
	{
		return Game_;
	}

	// Main Game Method 
	void ShowGame()
	{
		for (int i = 0; i < 1; i++)
		{
			system("cls");
			Queue_[0].RandomSwap();
			Queue_[1].RandomSwap();
			Queue_[2].RandomSwap();
			Queue_[0].Show();
			Queue_[1].Show();
			Queue_[2].Show();
			WinValue();
			cout << "Your value: " << GetBetCount() << '\n';
		}
	}

	// Calculate Win 
	void WinValue()  
	{
		//		A
		//		A
		//		A
		if (Queue_[0].CheckWin(0) == Queue_[1].CheckWin(0) && Queue_[0].CheckWin(0) == Queue_[2].CheckWin(0))
		{
			bet_ += bet_ / 2;
			cout << "You Have Big Win (All Match)\n";
		}

		//	    A			 A
		//		 A    ||    A	
		//		  A		   A
		else if (Queue_[0].CheckWin(0) == Queue_[1].CheckWin(1) && Queue_[0].CheckWin(0) == Queue_[2].CheckWin(2))
		{
			bet_ += bet_ / 8;
			cout << "You Have Medium Win (Diagonal)\n";
		}
		else if (Queue_[0].CheckWin(2) == Queue_[1].CheckWin(1) && Queue_[0].CheckWin(2) == Queue_[2].CheckWin(0))
		{
			bet_ += bet_ / 8;
			cout << "You Have Medium Win (Diagonal)\n";
		}

		// A B C         
		// A B C   ||   A B C 
		//		  	    A B C 
		else if (Queue_[0].CheckWin(0) == Queue_[1].CheckWin(0) || Queue_[1].CheckWin(0) == Queue_[2].CheckWin(0))
		{
			bet_ += bet_ / 16;
			cout << "You Have Small Win (One of field Match)\n";
		}

		else
			bet_ -= bet_ / 4;
	}

	// Add Queue field to Interface 
	void AddQueue()
	{
		QueueRing* a = new QueueRing[3];
		for (int i = 1; i < 4; i++)
		{
			a[0].AddToQueue(i);
			a[1].AddToQueue(i);
			a[2].AddToQueue(i);
		}
		Queue_ = a;
	}

	// Add Bet Field Method
	void AddBet()
	{
		cout << "Enter Bet Value\n";
		int value;
		cin >> value;
		bet_ = value;
	}

	// Return Bet Value
	int GetBetCount() const 
	{
		return bet_;
	}

	// Destructor
	~SingleGameInterface()
	{

	};

private:

};
// Static Interface static variable
SingleGameInterface* SingleGameInterface::Game_ = new SingleGameInterface(1);

int main()
{
	srand(time(0));

	SingleGameInterface* p = SingleGameInterface::GetPtr();

	p->AddQueue();
	p->AddBet();

	while (1)
	{
		cout << "Press Enter to do Roll" << endl;
		switch ((cin.get() != ' '))
		{
		default:
			p->ShowGame(); cin.clear(); break;
		}
	}
}
