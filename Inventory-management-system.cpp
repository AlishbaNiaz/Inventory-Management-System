#include<iostream>
#include<fstream>
using namespace std;
void MainMenu();
int Getlength(char* name);
bool CompareTwoArrays(char* Arr, char* Arr2);
void CopyArray(char*&Arr, char*Arr2);
char* AddTXT(char* name, int Length);
void Menuoption1();
char* Menuoption2();
void RemoveTXT(char* name, int Length);
bool PasswordNotMatch(char* Password, char* FilePassword);
void UserMenu();
void PrintTillSpace(int Space, char* ProductName);
void PrintTillSpace(int Space);
void PrintTillSpace(ofstream& fout1, int Space, char* ProductName);
void useroption1();
bool IDFoundinFile(const char* Filename, int x);
bool FoundInFile(const char* Filename, char* Word);
int ReturnIndexofID(const char* Filename);
int ReturnIndexofIDUser(const char*);
int* Create1DArray(int Size);
char** Create2DArray(int Size);
float* Create1DArrayFloat(int Size);
void FillFromFile(const char* FileName, int* ID, char** Name, float* Cost, int* Quantity, char** Catergory, int linestoskip);
void DisplayDataStructure(int* ID, char** Name, float* Cost, int* Quantity, char** Catergory, int size);
int getLengthfromFile(char* FileName);
int InputNumber(const char*);
void WriteFileFromMatrix(const char* FileName, int* ID, char** Name, float* Cost, int* Quantity, char** Catergory, int size);
void AdminMenu();
int main()
{
	char* UserName = nullptr;
	bool isAdmin = false;
	while (1)
	{
		char* Menuoptions = new char('\0');
		MainMenu();
		cin >> Menuoptions;
		if (*Menuoptions == '1')
		{
			Menuoption1();

		}
		else if (*Menuoptions == '2')
		{
			UserName = Menuoption2();
			if (UserName[0] == 'A'
				&&  UserName[1] == 'd'
				&& UserName[2] == 'm'
				&&  UserName[3] == 'i'
				&& UserName[4] == 'n')
			{
				isAdmin = true;
			}
			cout << UserName << endl;
			if (isAdmin == false)
			{
				while (1)
				{
					char* Useroption = new char('\0');
					UserMenu();
					cin >> Useroption;
					cout << endl;
					if (*Useroption == '1')
					{
						useroption1();
					}
					else if (*Useroption == '2')
					{
						int Size = ReturnIndexofID("Product.txt");
						int ReadSize = getLengthfromFile(AddTXT(UserName, Getlength(UserName))) - 2;
						int* ID = Create1DArray(Size);
						float* Cost = Create1DArrayFloat(Size);
						int* Quantity = Create1DArray(Size);
						char** Name = Create2DArray(Size);
						char** Category = Create2DArray(Size);

						int* ReadID = Create1DArray(Size);
						float* ReadCost = Create1DArrayFloat(Size);
						int* ReadQuantity = Create1DArray(Size);
						char** ReadName = Create2DArray(Size);
						char** ReadCategory = Create2DArray(Size);

						FillFromFile("Product.txt", ID, Name, Cost, Quantity, Category, 1);
						//DisplayDataStructure(ID, Name, Cost, Quantity, Category, ReturnIndexofID("Product.txt"));
						FillFromFile(UserName, ReadID, ReadName, ReadCost, ReadQuantity, ReadCategory, 2);
						//DisplayDataStructure(ID, Name, Cost, Quantity, Category, ReturnIndexofID("Product.txt"));
						//DisplayDataStructure(ReadID, ReadName, ReadCost, ReadQuantity, ReadCategory, getLengthfromFile(UserName) - 2);

						int inputID = InputNumber("Enter ID");
						int inputQuantity = InputNumber("Enter Quantity");
						bool isFound = false;
						bool isFoundUser = false;
						int IndexFound = -1, IndexFoundUser = -1;
						while (isFound == false)
						{
							for (int i = 0; i < Size; i++)
							{
								if (inputID == ID[i])
								{
									isFound = true;
									IndexFound = i;
									break;
								}
							}
							if (isFound == false)
							{
								inputID = InputNumber("ID not found enter again");
							}
							if (isFound == true)
							{
								for (int i = 0; i < ReadSize; i++)
								{
									if (inputID == ReadID[i])
									{
										isFoundUser = true;
										IndexFoundUser = i;
										break;
									}
								}
							}
						}
						if (isFound == true && isFoundUser == true)
						{
							ifstream fin(UserName);
							char* NameofUser = new char[20]{'\0'};
							char* PassofUser = new char[20]{'\0'};
							fin >> PassofUser >> NameofUser;
							fin.close();

							Quantity[IndexFound] -= inputQuantity;
							ReadQuantity[IndexFoundUser] += inputQuantity;
							ofstream fout("Product.txt");
							char* Skip = new char[100]{'\0'};
							fout << "ID       NAME            COST       QUANTITY    CATEGORY" << endl;
							WriteFileFromMatrix("Product.txt", ID, Name, Cost, Quantity, Category, Size);
							fout.close();
							fout.open(UserName);
							fout << PassofUser << endl;
							fout << NameofUser << endl;
							WriteFileFromMatrix(UserName, ReadID, ReadName, ReadCost, ReadQuantity, ReadCategory, ReadSize);
							fout.close();
						}
						//DisplayDataStructure(ID, Name, Cost, Quantity, Category, ReturnIndexofID("Product.txt"));
						//DisplayDataStructure(ReadID, ReadName, ReadCost, ReadQuantity, ReadCategory, getLengthfromFile(UserName) - 2);
						else if (isFound == true && isFoundUser == false)
						{
							Quantity[IndexFound] -= inputQuantity;
							ofstream fout(UserName, ios::app);
							fout << "\n" << ID[IndexFound] << "\t";
							fout << Name[IndexFound];
							PrintTillSpace(fout, 15, Name[IndexFound]);
							fout << " " << Cost[IndexFound] << "\t\t" << inputQuantity << "\t\t" << Category[IndexFound];
							fout.close();

							fout.open("Product.txt");
							char* Skip = new char[100]{'\0'};
							fout << "ID       NAME            COST       QUANTITY    CATEGORY" << endl;
							WriteFileFromMatrix("Product.txt", ID, Name, Cost, Quantity, Category, Size);
							fout.close();
						}
						RemoveTXT(UserName, Getlength(UserName));
					}
					else if (*Useroption == '3')
					{
						int ReadSize = getLengthfromFile(AddTXT(UserName, Getlength(UserName))) - 2;

						int* ReadID = Create1DArray(ReadSize);
						float* ReadCost = Create1DArrayFloat(ReadSize);
						int* ReadQuantity = Create1DArray(ReadSize);
						char** ReadName = Create2DArray(ReadSize);
						char** ReadCategory = Create2DArray(ReadSize);

						FillFromFile(UserName, ReadID, ReadName, ReadCost, ReadQuantity, ReadCategory, 2);

						DisplayDataStructure(ReadID, ReadName, ReadCost, ReadQuantity, ReadCategory, getLengthfromFile(UserName) - 2);
						float TotalCost = 0;
						for (int i = 0; i < ReadSize; i++)
						{
							TotalCost += (ReadCost[i] * ReadQuantity[i]);
						}
						cout << "Total Cost is $" << TotalCost << endl;
						RemoveTXT(UserName, Getlength(UserName));
					}
					else if (*Useroption == '4')
					{
						AddTXT(UserName, Getlength(UserName));
						char* choice = new char(0);
						cout << "Order confirm?? (Y/N)" << endl;
						cin >> choice;
						if (*choice == 'y' || *choice == 'Y')
						{
							int Size = getLengthfromFile(UserName) - 2;
							int* ReadID = Create1DArray(Size);
							float* ReadCost = Create1DArrayFloat(Size);
							int* ReadQuantity = Create1DArray(Size);
							char** ReadName = Create2DArray(Size);
							char** ReadCategory = Create2DArray(Size);

							FillFromFile(UserName, ReadID, ReadName, ReadCost, ReadQuantity, ReadCategory, 2);
							RemoveTXT(UserName, Getlength(UserName));
							cout << "Order confirm!" << endl;
							cout << "Thank you for shopping with us," << UserName << "! Your order has been confirmed." << endl;
							ifstream fin(AddTXT(UserName, Getlength(UserName)));
							char* Password = new char[30]{'\0'};
							char* NameofUser = new char[30]{'\0'};
							fin >> Password >> NameofUser;
							fin.close();

							ofstream fout(UserName);
							fout << Password << endl << NameofUser;
							fout.close();
							RemoveTXT(UserName, Getlength(UserName));

							fout.open("Admin.txt", ios::app);
							fout << endl;
							const int Space = 15;
							int OrderID = ReturnIndexofIDUser("Admin.txt") + 1;
							cout << OrderID << endl;
							for (int i = 0; i < Size; i++)
							{
								fout << "OrderNo:" << OrderID << "\t";
								fout << ReadID[i] << "\t";
								fout << ReadQuantity[i] << "\t\t" << ReadCost[i] << "\t\t" << ReadQuantity[i] * ReadCost[i];
								if (i != Size - 1)fout << endl;
							}
							fout.close();
						}
						else
						{
							while (*choice != 'n' && *choice != 'N'&&*choice != 'y' && *choice != 'Y')
							{
								cout << "Wrong input only Typr Y/N" << endl;
								cin >> choice;
							}
							cout << "Your order is not confirmed" << endl;
						}
						int Length = Getlength(UserName);
						if (UserName[Length - 4] == '.')UserName[Length - 4] = '\0';
					}
					else if (*Useroption == '5')
					{
						cout << "Logged out successfully. Goodbye! " << endl;
						system("pause");
						system("CLS");
						break;
					}
					else
					{
						cout << "Wrong Input" << endl;
					}
					system("pause");
					system("CLS");
				}
			}
			else  //this is for admin
			{
				char* Adminoption = new char('\0');
				while (-1)
				{

					AdminMenu();
					cin >> Adminoption;
					cout << endl;
					if (*Adminoption == '1')
					{
						int Size = ReturnIndexofID("Product.txt");
						int* ID = Create1DArray(Size);
						float* Cost = Create1DArrayFloat(Size);
						int* Quantity = Create1DArray(Size);
						char** Name = Create2DArray(Size);
						char** Category = Create2DArray(Size);

						FillFromFile("Product.txt", ID, Name, Cost, Quantity, Category, 1);
						DisplayDataStructure(ID, Name, Cost, Quantity, Category, ReturnIndexofID("Product.txt"));

					}
					else if (*Adminoption == '2')
					{
						int Size = ReturnIndexofID("Product.txt");
						int ReadSize = getLengthfromFile(AddTXT(UserName, Getlength(UserName))) - 2;
						int* ID = Create1DArray(Size);
						float* Cost = Create1DArrayFloat(Size);
						int* Quantity = Create1DArray(Size);
						char** Name = Create2DArray(Size);
						char** Category = Create2DArray(Size);

						FillFromFile("Product.txt", ID, Name, Cost, Quantity, Category, 1);

						int inputID = ReturnIndexofID("Product.txt") + 1;
						float inputCost = 0;
						int inputQuantity = 0;
						char* inputName = new char[100]{'\0'};
						char* inputCategory = new char[100]{'\0'};
						cout << "Enter Name of Product" << endl;
						cin >> inputName;
						bool isFound = false;
						int IndexFound = -1;
						for (int i = 0; i < Size; i++)
						{
							if (CompareTwoArrays(Name[i], inputName))
							{
								isFound = true;
								IndexFound = i;
								break;
							}
						}
						if (isFound == true)
						{
							cout << "Input Quantity" << endl;
							cin >> inputQuantity;
							Quantity[IndexFound] += inputQuantity;

							ofstream fout("Product.txt");
							fout << "ID       NAME            COST       QUANTITY    CATEGORY" << endl;
							WriteFileFromMatrix("Product.txt", ID, Name, Cost, Quantity, Category, Size);
							fout.close();
						}
						else
						{
							cout << "IT IS A NEW PRODUCT" << endl;
							cout << "Input Quantity" << endl;
							cin >> inputQuantity;
							cout << "Enter Category of Product" << endl;
							cin >> inputCategory;
							cout << "Cost of Product" << endl;
							cin >> inputCost;

							ofstream fout("Product.txt", ios::app);
							fout << "\n" << inputID << "\t";
							fout << inputName;
							PrintTillSpace(fout, 15, inputName);
							fout << inputCost << "\t\t" << inputQuantity << "\t\t";
							fout << inputCategory;
							fout.close();
						}
						RemoveTXT(UserName, Getlength(UserName));
					}
					else if (*Adminoption == '3')
					{
						int Size = ReturnIndexofID("Product.txt");
						int ReadSize = getLengthfromFile(AddTXT(UserName, Getlength(UserName))) - 2;
						int* ID = Create1DArray(Size);
						float* Cost = Create1DArrayFloat(Size);
						int* Quantity = Create1DArray(Size);
						char** Name = Create2DArray(Size);
						char** Category = Create2DArray(Size);

						FillFromFile("Product.txt", ID, Name, Cost, Quantity, Category, 1);

						int inputID = ReturnIndexofID("Product.txt") + 1;
						float inputCost = 0;
						int inputQuantity = 0;
						char* inputName = new char[100]{'\0'};
						char* inputCategory = new char[100]{'\0'};
						cout << "Enter Name of Product" << endl;
						cin >> inputName;
						bool isFound = false;
						int IndexFound = -1;
						for (int i = 0; i < Size; i++)
						{
							if (CompareTwoArrays(Name[i], inputName))
							{
								isFound = true;
								IndexFound = i;
								break;
							}
						}
						if (isFound == true)
						{
							for (int i = IndexFound; i < Size - 1; i++)
							{
								ID[i] = ID[i + 1];
								Cost[i] = Cost[i + 1];
								Quantity[i] = Quantity[i + 1];
								CopyArray(Name[i], Name[i + 1]);
								CopyArray(Category[i], Category[i + 1]);
							}
							delete Name[Size - 1];
							delete Category[Size - 1];
							Name[Size] = nullptr;
							Category[Size] = nullptr;
							Size--;
							ofstream fout("Product.txt");
							fout << "ID       NAME            COST       QUANTITY    CATEGORY" << endl;
							WriteFileFromMatrix("Product.txt", ID, Name, Cost, Quantity, Category, Size);
							fout.close();
							cout << "PRODUCT DELETED SUCESSFULLY" << endl;
						}
						else
						{
							cout << "Product Not Found" << endl;
						}
						RemoveTXT(UserName, Getlength(UserName));
					}
					else if (*Adminoption == '4')
					{
						int Size = ReturnIndexofID("Product.txt");
						int ReadSize = getLengthfromFile(AddTXT(UserName, Getlength(UserName))) - 2;
						int* ID = Create1DArray(Size);
						float* Cost = Create1DArrayFloat(Size);
						int* Quantity = Create1DArray(Size);
						char** Name = Create2DArray(Size);
						char** Category = Create2DArray(Size);

						FillFromFile("Product.txt", ID, Name, Cost, Quantity, Category, 1);

						int inputID = ReturnIndexofID("Product.txt") + 1;
						float inputCost = 0;
						int inputQuantity = 0;
						char* inputName = new char[100]{'\0'};
						char* inputCategory = new char[100]{'\0'};
						cout << "Enter ID of Product" << endl;
						cin >> inputID;
						bool isFound = false;
						int IndexFound = -1;
						for (int i = 0; i < Size; i++)
						{
							if (inputID == ID[i])
							{
								isFound = true;
								IndexFound = i;
								break;
							}
						}
						if (isFound == true)
						{
							cout << "Input Quantity" << endl;
							cin >> inputQuantity;
							Quantity[IndexFound] += inputQuantity;

							ofstream fout("Product.txt");
							fout << "ID       NAME            COST       QUANTITY    CATEGORY" << endl;
							WriteFileFromMatrix("Product.txt", ID, Name, Cost, Quantity, Category, Size);
							fout.close();
							cout << "UPDATED SUCESSFULLY" << endl;
						}
						else
						{
							cout << "CAN NOT FIND THE PRODUCT" << endl;
						}
						RemoveTXT(UserName, Getlength(UserName));
					}
					else if (*Adminoption == '5')
					{
						ifstream fin("Admin.txt");
						char* Waste = new char[100]{'\0'};
						fin.getline(Waste, 100);
						fin.getline(Waste, 100);
						cout << "Order ID | Product ID      | Quantity | Price    | Total Cost" << endl;
						while (!fin.eof())
						{
							fin >> Waste;
							cout << Waste << "\t";
							fin >> Waste;
							cout << Waste << "\t\t";
							fin >> Waste;
							cout << Waste << "\t";
							fin >> Waste;
							cout << Waste << "\t\t";
							fin >> Waste;
							cout << Waste << "\t";
							cout << endl;
						}

						fin.close();
					}
					else if (*Adminoption == '6')
					{
						cout << "Logged out successfully. Goodbye! " << endl;
						system("pause");
						system("CLS");
						break;
					}
					else
					{
						cout << "Wrong Input" << endl;
					}
					system("pause");
					system("CLS");
				}
			}
		}
		else if (*Menuoptions == '3'){
			cout << "Existing program" << endl;
			break;
		}
		else
		{
			cout << "WRONG INPUT" << endl;
		}

	}
	system("pause");
	return 0;
}
void MainMenu()
{
	cout << "1.Register" << endl;
	cout << "2.Login" << endl;
	cout << "3.Exit" << endl;
	cout << "Enter your choice:";
}
int Getlength(char* name){
	int Length = 0;
	for (int i = 0; name[i] != '\0'; i++)
		Length++;
	return Length;
}
char* AddTXT(char* name, int Length){
	name[Length] = '.';
	name[Length + 1] = 't';
	name[Length + 2] = 'x';
	name[Length + 3] = 't';
	name[Length + 4] = '\0';
	return name;
}
void RemoveTXT(char* name, int Length)
{
	name[Length - 4] = '\0';

}
void Menuoption1(){
	char* Name = new char[20]{'\0'};
	char* Username = new char[20]{'\0'};
	char* Password = new char[20]{'\0'};
	bool isAdmin = false;
	cin.ignore();
	cout << "Enter Name:";
	cin.getline(Name, 20);
	cout << "Enter Username:";
	cin >> Username;
	AddTXT(Username, Getlength(Username));
	ifstream fin(Username);
	while (fin.is_open()){
		cout << "User already exist with this NAME " << endl;
		cout << "Enter New Username:";
		cin >> Username;
		AddTXT(Username, Getlength(Username));
		fin.close();
		fin.open(Username);
	}
	cout << "Enter Password:";
	cin >> Password;
	ofstream fout(Username);
	fout << Password << endl;
	fout << Name << endl;
	fout.close();
	cout << "Registeration successfully!" << endl;
	system("pause");
	system("CLS");
	RemoveTXT(Username, Getlength(Username));
	cout << "Username :";
	cout << Username << endl;
	cout << "Password :";
	for (int i = 0; i < Getlength(Password); i++)cout << "*";
	cout << endl;
}
bool PasswordNotMatch(char* Password, char* FilePassword){
	if (Getlength(Password) != Getlength(FilePassword))
		return true;
	for (int i = 0; i<Getlength(Password); i++){
		if (Password[i] != FilePassword[i])return true;
	}
	return false;
}
char* Menuoption2()
{
	cout << "Login" << endl;
	char* Name = new char[20]{'\0'};
	char* Username = new char[20]{'\0'};
	char* Password = new char[20]{'\0'};
	char* FilePassword = new char[20]{'\0'};
	cout << "Enter Username:";
	cin >> Username;
	AddTXT(Username, Getlength(Username));
	ifstream fin(Username);
	while (!fin.is_open()){
		cout << "User not Exist" << endl;
		cout << "Enter new Username:";
		cin >> Username;
		AddTXT(Username, Getlength(Username));
		fin.close();
		fin.open(Username);
	}
	cout << "Enter Password:";
	cin >> Password;
	fin.getline(FilePassword, 20);
	while (PasswordNotMatch(Password, FilePassword)){
		cout << "WRONG PASSWORD TRY AGAIN " << endl;
		cin >> Password;
	}
	RemoveTXT(Username, Getlength(Username));
	cout << "Username:" << Username << endl;
	cout << "Password:";
	for (int i = 0; i < Getlength(Password); i++)cout << "*";
	cout << endl;
	cout << endl;
	fin.getline(Name, 20);
	cout << "Logged in as " << Name << endl;
	cout << endl;
	return Username;
}
void UserMenu(){
	cout << "1. Display available products" << endl;
	cout << "2. Add items to the cart" << endl;
	cout << "3. View cart" << endl;
	cout << "4. Place order" << endl;
	cout << "5. Logout" << endl;
	cout << endl;
	cout << "Enter your choice:";
}
void PrintTillSpace(ofstream& fout1, int Space, char* ProductName)
{
	for (int i = 0; i < Space - Getlength(ProductName); i++)
	{
		fout1 << " ";
	}
}
void PrintTillSpace(int Space, char* ProductName)
{
	for (int i = 0; i < Space - Getlength(ProductName); i++)
	{
		cout << " ";
	}
}
void PrintTillSpace(int Space)
{
	for (int i = 0; i < Space; i++)
	{
		cout << " ";
	}
}
void useroption1()
{
	int* ID = new int(0);
	char* ProductName = new char[20]{'\0'};
	float* Price = new float(0);
	int* Quantity = new int[20]{'\0'};
	char* Waste = new char[20];
	cout << "AVAILABLE PRODUCTS" << endl;
	char* Heading = new char[100];
	const int Space = 15;
	ifstream fin("Product.txt");
	fin.getline(Heading, 100);
	cout << "ID\tNAME";
	PrintTillSpace(11);
	cout << "Cost";
	PrintTillSpace(10);
	cout << "Quantity" << endl;
	//\tCOST\tQUANTITY " << endl;

	while (fin >> *ID)
	{

		fin >> ProductName >> *Price >> *Quantity >> Waste;
		//cout << *ID << "\t" << ProductName << "\t" << *Price << "\t" << Quantity << endl;
		cout << *ID << "\t";
		cout << ProductName;
		PrintTillSpace(Space, ProductName);
		cout << *Price << "\t\t" << *Quantity << endl;
	}
	fin.close();
}
bool IDFoundinFile(const char* Filename, int x)
{
	ifstream fin(Filename);
	int ids;
	char* Skip = new char[100]{'\0'};
	fin.getline(Skip, 100);
	while (!fin.eof())
	{
		fin >> ids;
		fin.getline(Skip, 100);
		if (ids == x)return true;
	}
	return false;
}
bool FoundInFile(const char* Filename, char* Word)
{
	ifstream fin(Filename);
	char* Read = new char[100]{'\0'};
	char* Waste = new char[100]{'\0'};
	int Index = 0;
	fin.getline(Read, 100);
	while (!fin.eof())
	{
		fin >> Index;
		fin >> Read;
		fin.getline(Waste, 100);
		if (!PasswordNotMatch(Word, Read))return true;
	}
	return false;
}
int ReturnIndexofIDUser(const char* Name)
{
	ifstream fin(Name);
	char* Read = new char[100]{'\0'};
	int Index = 0;
	fin.getline(Read, 100);
	fin.getline(Read, 100);
	while (!fin.eof())
	{
		fin >> Index;
		fin.getline(Read, 100);
	}
	return Index;
}
int ReturnIndexofID(const char* Filename)
{
	ifstream fin(Filename);
	char* Read = new char[100]{'\0'};
	int Index = 0;
	fin.getline(Read, 100);
	while (!fin.eof())
	{
		fin >> Index;
		fin.getline(Read, 100);
	}
	return Index;
}
int* Create1DArray(int Size)
{
	int* Array = new int[Size];
	for (int i = 0; i < Size; i++)Array[i] = 0;
	return Array;
}
char** Create2DArray(int Size)
{
	char** Array = new char*[Size];
	for (int i = 0; i < Size; i++)Array[i] = new char[100]{'\0'};
	return Array;
}
float* Create1DArrayFloat(int Size)
{
	float* Array = new float[Size];
	for (int i = 0; i < Size; i++)Array[i] = 0;
	return Array;
}
void FillFromFile(const char* FileName, int* ID, char** Name, float* Cost, int* Quantity, char** Catergory, int linestoskip)
{
	ifstream fin(FileName);
	int size = 0;
	char* Waste = new char[1000];
	for (int i = 0; i < linestoskip; i++)
	{
		fin.getline(Waste, 1000);
	}
	if (fin.is_open())
	{
		while (!fin.eof())
		{
			fin >> ID[size] >> Name[size] >> Cost[size] >> Quantity[size] >> Catergory[size];
			size++;
		}
	}

	fin.close();
}
void DisplayDataStructure(int* ID, char** Name, float* Cost, int* Quantity, char** Catergory, int size)
{
	const int Space = 15;
	if (size != 0)
	{

		cout << "ID\tNAME";
		PrintTillSpace(11);
		cout << "Cost";
		PrintTillSpace(10);
		cout << "Quantity" << endl;
	}
	for (int i = 0; i < size; i++)
	{
		cout << ID[i] << "\t";
		cout << Name[i];
		PrintTillSpace(Space, Name[i]);
		cout << Cost[i] << "\t\t" << Quantity[i] << endl;
	}
}
int getLengthfromFile(char* FileName)
{
	int count = 0;
	ifstream fin(FileName);
	char* Waste = new char[1000];
	while (!fin.eof())
	{
		fin.getline(Waste, 1000);
		count++;
	}
	return count;
}
int InputNumber(const char* Text = "")
{
	cout << Text << endl;
	int Num = 0;
	cin >> Num;
	while (Num <= 0)
	{
		cout << "Wrong Input Enter again" << endl;
		cin >> Num;
	}
	return Num;
}
void WriteFileFromMatrix(const char* FileName, int* ID, char** Name, float* Cost, int* Quantity, char** Catergory, int size)
{
	ofstream fout(FileName, ios::app);
	const int Space = 15;
	for (int i = 0; i < size; i++)
	{
		fout << ID[i] << "\t";
		fout << Name[i];
		PrintTillSpace(fout, Space, Name[i]);
		fout << Cost[i] << "\t\t" << Quantity[i] << "\t\t";
		fout << Catergory[i];
		if (i != size - 1)fout << endl;
	}
	fout.close();
}
void AdminMenu()
{
	cout << "1. Display available products" << endl;
	cout << "2. Insert new product" << endl;
	cout << "3. Delete specific product" << endl;
	cout << "4. Update product information" << endl;
	cout << "5. View orders" << endl;
	cout << "6. Logout" << endl;

}
bool CompareTwoArrays(char* Arr, char* Arr2)
{
	int Size1 = Getlength(Arr);
	int Size2 = Getlength(Arr2);
	if (Size1 != Size2)return false;
	for (int i = 0; i < Size1; i++)
	{
		if (Arr[i] != Arr2[i])return false;
	}
	return true;
}
void CopyArray(char*&Arr, char*Arr2)
{
	if (Arr != nullptr)
	{
		delete Arr;
		Arr = nullptr;
	}
	int Size = Getlength(Arr2);
	Arr = new char[Size + 1];
	for (int i = 0; i < Size; i++)
	{
		Arr[i] = Arr2[i];
	}
	Arr[Size] = { '\0' };
}