// Student name :	ZHOU Zhenghao	
// Student ID   :	54381018

// Submission deadline : Sunday, 8 Oct 2017, 11pm
// Upload your .cpp file via Canvas
// Late submission or submission by other means will not be graded


/*
	In this tutorial, we shall use the string class in C++.

	The string class in C++ offers a lot more functionality than cstring.
	You can compare 2 string objects using the relational operators.
	For example,
		string s1, s2;
		...
		if (s1 == s2)
		   ...

		if (s1 < s2)
		   ...

	You can use the subscript operator [] to access the char at a given index.
	For example,
	   if (s1[i] == ',')  // test if char at index i is equal to ','

	You can use substring(start, end) to get the substring from index start to end-1
	For example,
		string sub = s1.substring(0, i); // get the substring from 0 to i-1

*/

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct telRec {
	string name;
	string tel;
};

struct chatGroup {
	string groupName;
	string *member;  // array of string storing the tel no. of group members
	int size;
};

const string NotFound = "not found";

void readTelList(const string& filename, telRec*& telList, int& n)
{
	// File format :
	// Number of records is given on the first line.
	// Each telephone record is stored in 1 line (starting from 2nd line).
	// Name is delimited by comma ',' followed by a space char, and then the telephone number.
	// Telephone records in the file are ordered by telephone number.

	// Read in the data from the file.
	// Create the array telList, and set the value of n (number of telRec)

	ifstream infile(filename);
	if (!infile.is_open())
	{
		cout << "Error: cannot open data file : " << filename << endl;
		system("pause");
		exit(0);
	}

	string temp;	
	infile >> temp >> n;
	telList = new telRec[n];

	// Use getline() to read in one line of text from the file.
	// The C++ function getline() is similar to Scanner.nextLine() in Java.

	string line;
	getline(infile, line);  // consume the '\n' after the value of n
	
	int num;
	int length=0;
	for (int i = 0; i < n; i++) {
		getline(infile, line);
		length = line.length();
		for (int j = 0; j < length; j++) {
			num++;
			if (line[j] == ',') {
				break;
			}
		}
		telList[i].name = line.substr(0, num);
		telList[i].tel = line.substr(num + 2, length);
	}
	

	
	// Your codes




	infile.close();  // close the file after use
}

void readChatGroup(const string& filename, chatGroup*& groupList, int& g)
{
	// File format :
	// Number of chat groups is given on the first line.
	// Each group contains:
	//    group_name size
	//    telephone numbers of the members in the chat group (not ordered)
	// Chat groups in the file are ordered by group name.

	// Read in the data from the file.
	// Create the array groupList, and set the value of g (number of groups)

	ifstream infile(filename);
	if (!infile.is_open())
	{
		cout << "Error: cannot open data file : " << filename << endl;
		system("pause");
		exit(0);
	}

	string temp;	
	infile >> temp >> g;
	groupList = new chatGroup[g];
	string line;
	getline(infile,line);
	string name;
	int size;

	for (int i=0;i<g;i++){
		getline(infile,line);
		infile >> name >>size;
		groupList[i].groupName = name;
		groupList[i].size = size;
		getline(infile,line);
		for(int j=0;j<size;j++){
			getline(infile,line);
			int length = line.length();
			groupList[i].member[j] = line.substr(0,length);
		}
	}
	// Your codes
	infile.close();
}

const string& getNameByTel(const telRec *telList, int n, const string& tel)
{
	// Return the name (by reference) that is associated with the given tel number
	// If the input tel is not found, 
	// return Notfound (the const string defined at the top of the file).

	// The returned string object is a const, i.e. the calling function cannot modify 
	// the returned string object.

	// Use binary search to find the telRec
	int a=0;
	int b=n-1;
	int c=(a+b)/2;
	string backward = NotFound;
	while (a <= b) {
		if (telList[c].tel == tel) {
			backward = telList[c].name;
			break;
		}
		else if (telList[c].tel < tel) {
			a = c;
			c = (a + b) / 2;
		}
		else{
			b = c;
			c = (a + b) / 2;
		}
		
	}

	// Your codes


	return NotFound;
}

void printChatGroupByName(const chatGroup *groupList, int g, string gname, const telRec *telList, int n)
{
	// Print the chat group to the standard output.
	// If the chat group is found, format of the output:
	//    Chat group : group_name
	//    Number of members :
	//    name, tel (one line per member)

	// If the chat group is not found, format of the output:
	//    Chat group : group_name not found
	
	// Use binary search to find the group
	int a=0;
	int b=g-1;
	int c=(a+b)/2;
	while (a <= b) {
		if (groupList[c].groupName == gname) {
			cout << "Chat group : " << groupList[c].groupName << endl;
			cout << "Number of members : " << groupList[c].size << endl;
			for (int i = 0; i < groupList[c].size; i++) {
				cout << getNameByTel(telList, n, groupList[c].member[i]) << ", " << groupList[c].member[i] << endl;
			}
			break;
		}
		else if (groupList[c].groupName < gname) {
			a = c;
			c = (a + b) / 2;
		}
		else {
			b = c;
			c = (a + b) / 2;
		}
	}
	if (groupList[c].groupName != gname) {
		cout << "Chat group : " << gname << " not found" << endl;
	}

	// Your codes
}

int main()
{	
	telRec *telList;
	int n;  // number of tel records
	chatGroup *groupList;
	int g;  // number of chat groups

	string file1 = "tel-name.txt";    // sorted by telephone number
	string file2 = "chat-groups.txt"; // sorted by group name, tel no. within a group are not sorted
	
	readTelList(file1, telList, n);

	string t1 = "91765295";
	cout << "Owner of tel. no. " << t1 << " is " << getNameByTel(telList, n, t1) << endl << endl;
	// Expected output 
	// Owner of tel. no. 91765295 is WONG Kin Ho

	string t2 = "90001111";
	cout << "Owner of tel. no. " << t2 << " is " << getNameByTel(telList, n, t2) << endl << endl;;
	// Expected output 
	// Owner of tel. no. 90001111 is not found

	readChatGroup(file2, groupList, g);

	string gname = "group-04";
	printChatGroupByName(groupList, g, gname, telList, n);
	// Expected output
	//    Chat group : group-04
	//    Number of members : 7
	//    CHAN Wai Hang, 98512078
	//    LUI Ka Fai, 98529423
	//    TSE Tsz Hin, 95871616
	//    SIU Ka Hin, 92432172
	//    LOK Kam Hung, 93670697
	//    WAN Tsun Man, 97039667
	//    CHAN Man Hong, 92026350

	gname = "group-03";
	printChatGroupByName(groupList, g, gname, telList, n);	
	// Expected output
	//    Chat group : group-03 not found

	system("pause");
	exit(0);
}