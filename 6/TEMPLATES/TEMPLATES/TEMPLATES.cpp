/** @file TEMPLATES.cpp */
#include <string>
#include <iostream>
using namespace std;

//! Klass LIST.
/*!
	Podrobnoe opisanie klassa.
*/
template <class T> class LIST
{
private:
	class NODE /*!< Klass NODE soderzhit dannye spiska */
	{
		friend class LIST<T>;
	private:
		NODE *pNext; /*!< Ukazatel' na sledujushhij jelement */
		T value; /*!< Informacionnoe pole */

		NODE(): pNext(NULL) { } /*!< Ukazatel' na sledujushhij jelement */
		~NODE() { }
	};

	NODE *pHead; //! Ukazatel' na pervyj jelement spiska
	int count; //! Kolichestvo jelementov v spiske
public:
	LIST() : pHead(NULL), count(0) { }
	
	~LIST()
	{
		clear(); //! Funkcija osvobozhdaet pamjat', ispol'zuemuju dlja hranenija spiska
	}	
	
	int getCount() const //! Funkcija, vozvrashhajushhaja kolichestvo jelementov v spiske
	{
		return count;
	}
	
	//! Funkcija, kotoraja dobavljaet jelement v spisok.
	/*!
	\param data - nekotoroe znachenie jelementa spiska
	\param position - pozicija jelementa v spiske
	*/
	int AddLIST(T data, int position)
	{
		NODE *to_add = new NODE; /// Sozdanie novogo jelementa  
		to_add->pNext = NULL;
		to_add->value = data;
		
		if (position <= 1 || pHead == NULL) /// Esli spisok pust:
		{
			to_add->pNext = pHead; /// - Ustanovka ukazatelja pNext
			pHead = to_add; /// - Opredelenie "golovy" spiska
		}
		else /// Esli spisok ne pust:
		{
			/// - Dobavlenie jelementa
			NODE *pA = pHead;
			for (int i = 1; i < position - 1; i++)
			{
				if (pA->pNext != NULL)
					pA = pA->pNext;
			}
			to_add->pNext = pA->pNext;
			pA->pNext = to_add;
		}
		cout << "\nJelement dobavlen v spisok...\n\n";
		count++;
		return count;
	}

	//! Funkcija, kotoraja udaljaet jelement iz spiska. 
	/*!
	\param position - pozicija jelementa v spiske
	\return 0 - esli spisok pust
	*/
	int DeleteLIST(int position) 
	{
		if (pHead == NULL) { cout << "\nSpisok pust! Udaljat' nechego!\n\n"; return 0; } /// Proverka spiska na pustotu 
		NODE *pA = pHead, *pB;
		int i = 0;
		while (pA != NULL)
		{
			pA = pA->pNext;
			i++;
		}
		if (position > i || position < 1) /// Proverka na sushhestvovanie pozicii 
		{
			cout << endl << "Takoj pozicii v spiske net!" << endl << endl;
		}
		else /// Udalenie jelementa:
		{
			if (position == 1) /// - Esli jeto pervyj jelement:
			{
				pA = pHead->pNext; /// 1) Sdvig ukazatelja
				pHead = pA; /// 2) Sdvig "golovy" spiska 
			}
			if (position > 1) /// - Esli jeto ne pervyj jelement:
			{
				i = 1;
				pA = pHead;
				while (i != position - 1)
				{
					i++;
					pA = pA->pNext; /// 1) Nastrojka ukazatelja na jelement, kotoryj stoit pered udaljaemym 
				}
				pB = pA->pNext; /// 2) Nastojka ukazatelja na udaljaemyj jelement 
				pA->pNext = pB->pNext; /// 3) Najstrojka ukazatelja na jelement, kotoryj stoit posle udaljaemogo
				delete pB; /// 4) Udalenie jeementa
			}
			cout << "\nJelement udalen iz spiska...\n\n";
		}
		count--;
		return count;
	}
	
	//! Funkcija, kotoraja ochishhaet spisok
	void ClearLIST() 
	{
		NODE *current = pHead;
		NODE *to_del = pHead;
		while(to_del != NULL)
		{
			current = current->pNext;
			delete to_del;
			to_del = current;
		}
		pHead = NULL;
		count = 0; 
	}

	//! Funkcija, kotoraja pechataet spisok.
	void PrintLIST()
	{
		if (pHead == NULL) cout << "Spisok pust!\n";
		else
		{
			NODE *pA = pHead;
			cout << "Jelementy spiska: ";
			while (pA != NULL)
			{
				cout << pA->value << " -> ";
				pA = pA->pNext;
			}
			cout << "\b\b\b  \n";
		}
	}
};

//! Glavnaja funkcija.
int main()
{
	//setlocale(LC_ALL, "RUS");	
	
	int position, x, n;
	char type;

	LIST<int> *int_head = new LIST <int>;
	LIST<string> *str_head = new LIST <string>;
	void *pHead;
	
	cout << "Vyberite tip (int - 'i', string - 's') > "; cin >> type;
	cout << "Vvedite kolichestvo operacij so spiskom > "; /// Vvod kolichestva dejstvij so spiskom
	cin >> n;
	cout << endl;
	switch (type)
	{
	case 'i':	
		pHead = int_head;
		int int_value;
		for (int i = 0; i < n; i++)	/// Cikl dejstvij so spiskom:
		{
			cout << "1. Dobavit' jelement" << endl; /// - Dobavlenie jelementa
			cout << "2. Udalit' jelement" << endl; /// - Udalenie jelementa
			cout << "\nNomer operacii > "; cin >> x;
			switch (x)
			{
			case 1:
				cout << "Znachenie > "; cin >> int_value;
				cout << "Pozicija > "; cin >> position;
				int_head->AddLIST(int_value, position); break;
			case 2:
				cout << "Pozicija > "; cin >> position;
				int_head->DeleteLIST(position); break;
			}
		}
		int_head->PrintLIST(); /// Pechat' spiska
		int_head->ClearLIST(); break;

	case 's':
		pHead = str_head;
		char str_value[128];
		for (int i = 0; i < n; i++)	/// Cikl dejstvij so spiskom:
		{
			cout << "1. Dobavit' jelement" << endl; /// - Dobavlenie jelementa
			cout << "2. Udalit' jelement" << endl; /// - Udalenie jelementa
			cout << "\nNomer operacii > "; cin >> x;
			switch (x)
			{
			case 1:
				cout << "Znachenie > "; _flushall(); gets_s(str_value);
				cout << "Pozicija > "; cin >> position;
				str_head->AddLIST(str_value, position); break;
			case 2:
				cout << "Pozicija > "; cin >> position;
				str_head->DeleteLIST(position); break;
			}
		}
		str_head->PrintLIST(); /// Pechat' spiska
		str_head->ClearLIST(); break;
	}		
	system("pause");
}