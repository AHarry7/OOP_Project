User.h
#include <string>
#include "admin.h"
#include "member.h"
#include <iostream>
#include<conio.h>
#include<fstream>
using namespace std;
#pragma once
class user:public admin,public member
{
protected: 
	int id;
	string username;
	string email;
	string status;
public:
	user();
	~user();
	void set(int,string,string);
	void Verifyuser();
	void Adduser();
	void Display();
	void Signup();
	void Login();
	void Delete();
	void viewuser();

};


User.cpp
#include "user.h"
user::user()
{
	id = 0;
	username = "";
	email = "";
	status = "User";
}
user::~user()
{

}
void user::set(int i, string u, string e)
{
	id = i;
	username = u;
	email = e;
}
void user::Verifyuser()
{
	cout << "\n \tThe user is a Normal User ! \n";
}
void user::Display()
{
	cout << "\n\t Status : " << status;
	cout << "\n\t Userid : " << id;
	cout << "\n\t Username : " << username;
	cout << "\n\t Email : " << email;
	
}
void user::Signup() // signup as a normal user
{
	cout << "\n\t --------------SIGN UP----------------\n";
	cout << "\n\t Enter userid of your choice : ";
	cin >> id;
	cout << "\n\t Enter a username of your choice : ";
	cin >> username;
	cout << "\n\t Enter your email : ";
	cin >> email;
	ofstream of("signup.dat", ios::app | ios::binary);
	if (!of)
	{
		cout << "\n\t Unable to open the file! \n";
	}
	else
	{
		of.write((char *)this, sizeof(*this));
		system("cls");
		cout << "\n\t Account Created Successfully! \n";
	}
	of.close();
}

void user::Login()
{
	string u, e;
	bool flag = true;
	cout << "\n\t*************** USER-LOGIN *************** \n";
	cout << "\n" << "\t Enter your username : ";
	cin >> u;
	cout << "\n\t Enter your email : ";
	cin >> e;
	ifstream r("signup.dat", ios::binary);
	if (!r)
	{
		cout << "\n\t Unable to open the file! ";
	}
	else
	{
		while (!r.eof())
		{
			r.read((char *)this, sizeof(*this));
			if (u == username && e == email)
			{
				system("cls");
				cout << "\n\t Login Successful ! \n ";
				cout << "\n\t----------------USER MENU--------------------\n";
			}
			else
			{
				flag = false;
			}
		}
		if (flag == false)
		{
			system("cls");
			cout << "\n\t Invalid username or email! Try again \n";
			Login();
		}
	}

	r.close();
}
void user::viewuser()
{
	ifstream r("signup.dat", ios::binary);
	if (!r)
	{
		cout << "\n\t Unable to open the file! \n";
	}
	else
	{
		cout << "\n\t USER DETAILS \n";
		while (!r.eof())
		{
			if (!r.read((char *)this, sizeof(*this)))break;
			Display();
			cout << "\n";
		}
	}
	r.close();
}

void user::Delete()
{
	string u;
	cout << "\n\t Enter a username to delete : ";
	cin >> u;
	ifstream fin("signup.dat", ios::binary);
	if (!fin)
	{
		cout << "\n\t Unable to open the file! ";
	}
	else
	{
		ofstream fout("temp.dat", ios::binary);
		if (!fout)
		{
			cout << "\n\t Unable to open! ";
		}

		while (!fin.eof())
		{
			fin.read((char *)this, sizeof(*this));
			if (username!=u)
			{
				fout.write((char *)this, sizeof(this));
			}
			fin.read((char *)this, sizeof(*this));
		}
		fin.close();
		fout.close();
		remove("signup.dat");
		rename("temp.dat", "signup.dat");
	}

}
void user::Adduser() // signup As an admin or member
{
	int ch;
	cout << "\n\t Please select any option \n\n";
	cout << "\t 1) Member User \n ";
	cout << "\t 2) Admin User \n\n \t ";
	cin >> ch;
	if (ch == 1)
	{
		member::Signup();
		member::Login();
	}
	else if (ch == 2)
	{
		admin::Signup();
		admin::Login();
	}
	else {
		cout << "\n\t Invalid choice Try again! \n";
		Adduser();
	}
}
Admin.h
#include "adminlist.h"
#include "member.h"
#pragma once
class admin:protected adminlist
{
private:
	
public:
	admin();
	~admin();
	void getData();
	void Verifyuser();
	void Deleteadmin();
	void AddMember();
	void deleteMember();
	void Display();
	void Signup();
	void Login();
	void viewadmins();
};


Admin.cpp
#include "admin.h"
admin::admin()
{
	
}
void admin::Verifyuser()
{
	adminlist::Verifyuser();
}

admin::~admin()
{
}

void admin::Deleteadmin()
{
	int id;
	cout << "\n\t Enter admin-id id to delete : ";
	cin >> id;
	ifstream fin("Asignup.dat", ios::binary);
	if (!fin)
	{
		cout << "\n\t Unable to open the file! ";
	}
	else
	{
		ofstream fout("temp.dat", ios::binary);
		if (!fout)
		{
			cout << "\n\tUnable to open the file!  ";
		}

		while (!fin.eof())
		{
			fin.read((char *)this, sizeof(*this));
			if (admin_id != id)
			{
				fout.write((char *)this, sizeof(this));
			}
			fin.read((char *)this, sizeof(*this));
		}
		fin.close();
		fout.close();
		remove("Asignup.dat");
		rename("temp.dat", "Asignup.dat");
	}
}
void admin::AddMember()
{
	member m;
	m.Signup();
}

void admin::deleteMember()
{
	member m;
	m.deleteMember();
}

void admin::Display()
{
	cout << "\n\t Status : " << status;
	cout << "\n\t Admin name : " << name;
	cout << "\n\t Admin age : " << age;
	cout << "\n\t Admin id : " << admin_id;
	cout << "\n\t Password : " << password;
	cout << "\n\t Email : " << email;
	cout << "\n\t Country : " << country;
	cout << "\n\t Phone : " << phone;
}
void admin::Signup()
{
	cout << "\n\t --------------SIGN UP----------------\n";
	cout << "\n" << "\tEnter an adminid of your choice : ";
	cin >> admin_id;
	cout << "\n\t Enter your password : ";
	cin >> password;
	cout << "\n\t Enter admin's name : ";
	cin >> name;
	cout << "\n\t Enter admin's age : ";
	cin >> age;
	cout << "\n\t Enter email of admin : ";
	cin >> email;
	cout << "\n\t Enter country of admin : ";
	cin >> country;
	cout << "\n\t Enter phone of admin : ";
	cin >> phone;
	ofstream of("Asignup.dat", ios::app | ios::binary);
	if (!of)
		cout << "\n Unable to open the file! ";
	else
	{
		of.write((char *)this, sizeof(*this));
		cout << "\n\t Account Created Successfully! \n";
	}
	of.close();
}

void admin::Login()
{
	bool flag = true;
	int ad;
	string p;
	cout << "\n\t*************** ADMIN-LOGIN *************** \n";
	cout << "\n" << "\tEnter your adminid : ";
	cin >> ad;
	cout << "\n\t Enter your password : ";
	cin >> p;
	ifstream r("Asignup.dat", ios::binary);
	if (!r)
		cout << "\n\t Unable to open the file ! ";
	else
	{
		while (!r.eof())
		{
			r.read((char *)this, sizeof(*this));
			if (p == password && ad == admin_id)
			{
				system("cls");
				cout << "\n\t Login Successful ! \n ";
				cout << "\n\t----------------ADMIN MENU--------------------\n";
			}
			else
				flag = false;
		}
		if (flag == false)
		{
			system("cls");
			cout << "\n\t Invalid id or password! Try again \n";
			Login();
		}
	}
	r.close();

}

void admin::viewadmins()
{
	ifstream r("Asignup.dat",ios::binary);
	cout << "\n\t ADMIN DETAILS \n";
	while (!r.eof())
	{
		if (!r.read((char *)this, sizeof(*this)))break;
		Display();
		cout << "\n";
	}
	r.close();
}
AdminList.h
#pragma once
#include <iostream>
#include <string>
#include <fstream>
using namespace std;
class adminlist
{
protected:
	string name;
	string status;
	string country;
	int age, phone;
	string email;
	int admin_id;
	string password;
	adminlist();
	~adminlist();
	void Verifyuser();
};


Adminlist.cpp
#include "adminlist.h"
adminlist::adminlist()
{
	admin_id = 1234;
	password = "hello";
	status = "Admin";
}

adminlist::~adminlist()
{
}
void adminlist::Verifyuser()
{
	cout << "\n\t The User is an Admin! \n";
}

Baraat.h
#pragma once
#include "walima.h"
class baraat :
	public marraige
{
public:
	baraat();
	baraat(int, string);
	~baraat();
	void Addcard();
	int getid();
	void search();
	void deletecard();
	void Displaycards();
	void write();
	void viewcard();
	void show();
};



Baraat.cpp
#include "baraat.h"


baraat::baraat()
{
	id = 0;
	name = "unknown";
}

baraat::baraat(int i,string n)
{
	id = i;
	name = n;
}

baraat::~baraat()
{
}

void baraat::Addcard()
{
	cout << "\n\t***********BARAATCARD****************\n";
	cout << "\n\t Enter card name : ";
	cin >> name;
	cout << "\n\t Enter card id : ";
	cin >> id;
	fflush(stdin);
	cout << "\n\t Enter a message for the receiver : ";
	getline(cin, message);
	system("cls");
	cout << "\n\t  CARD CREATED SUCCESSFULLY\n";
	write();
}
void baraat::deletecard()
{
	cout << "\n This card has been deleted! ";
}

void baraat::Displaycards()
{
	cout << "\n\t***********BARAATCARD****************\n";
	cout << "\t ID : " << id;
	cout << "\n\t Name : " << name;
	cout << "\n\t******************************************";
	cout << "\n\t Message for receiver : " << message;
	cout << "\n\t******************************************\n\n";
}

void baraat::write()
{
	ofstream of("BBcard.dat", ios::app | ios::binary);
	if (!of)
		cout << "\n\t Unable to open write! ";
	else
	{
		of.write((char *)this, sizeof(*this));
	}
	of.close();
}

void baraat::viewcard()
{
	ifstream in("BBcard.dat", ios::binary);
	if (!in)
		cout << "\n\t Unable to open write! ";
	else
	{
		while (!in.eof())
		{
			if (!in.read((char *)this, sizeof(*this)))break;
			Displaycards();
			cout << endl;
		}
	}

	in.close();
}

int baraat::getid()
{
	return id;
}

void baraat::search()
{
	int id;
	bool flag = false;
	cout << "\n\t Enter card-id : ";
	cin >> id;
	ifstream in("BBcard.dat", ios::binary);
	if (!in)
		cout << "\n\t Unable to open the file! ";
	else
	{
		while (!in.eof())
		{
			if (!in.read((char *)this, sizeof(*this)))break;

			if (id == getid())
			{
				flag = true;
				cout << "\n\t FOUND SUCCESSFULLY ! \n\n";
				Displaycards();
				_getch();
				exit(0);
			}
		}
		if (flag == false)
		{
			cout << "\n\t Not found in Baraat-Cards! \n";
		}
	}
	in.close();

}
void baraat::show()
{
	ifstream in("BBcard.dat", ios::binary);
	if (!in)
		cout << "\n\t Unable to open the file! ";
	else
	{
		while (!in.eof())
		{
			if (!in.read((char *)this, sizeof *this))break;
			Displaycards();
		}
	}
	in.close();
}
Birthdaycard.h
#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <conio.h>
#include <stdio.h>
using namespace std;
class birthcard 
{
private:
	int id;
	string name;
	char message[50];
public:
	birthcard();
	birthcard(int, string);
	void Addcard();
	int getid();
	void search();
	void deletecard();
	~birthcard();
	void write();
	void viewcard();
	void Displaycards();
	void show();
};



Birthdaycard.cpp
#include "birthcard.h"


birthcard::birthcard()
{
	id = 0;
	name = "unknown";
}
birthcard::birthcard(int i,string n)
{
	id = i;
	name = n;
}
birthcard::~birthcard()
{
}

void birthcard::Addcard()
{
	cout << "\n\t***********BIRTHCARD****************\n";
	cout << "\n\t Enter card name : ";
	cin >> name;
	cout << "\n\t Enter card id : ";
	cin >> id;
	fflush(stdin);
	cout << "\n\t Enter a message for the receiver : ";
	cin.get(message,50);
	system("cls");
	cout << "\n\t  CARD CREATED SUCCESSFULLY\n";
	write();
}
void birthcard::deletecard()
{
	cout << "\n\t This card has been deleted! ";
}

void birthcard::Displaycards()
{
	cout << "\n\t***********BIRTHCARD****************";
	cout << "\n\t ID : " << id;
	cout << "\n\t Name : " << name;
	cout << "\n\t******************************************";
	cout << "\n\t Message for receiver : " << message;
	cout << "\n\t******************************************\n\n";
}

void birthcard::write()
{
	ofstream of("Bcard.dat",ios::app|ios::binary);
	if (!of)
		cout << "\n\t Unable to open write! ";
	else
	{
		of.write((char *)this, sizeof(*this));
	}
	of.close();
}

void birthcard::viewcard()
{
	ifstream in("Bcard.dat", ios::binary);
	if (!in)
		cout << "\n\t Unable to open write! ";
	else
	{
		while (!in.eof())
		{
			if (!in.read((char *)this, sizeof(*this)))break;
			Displaycards();
			cout << endl;
		}
	}

	in.close();
}

int birthcard::getid()
{
	return id;
}

void birthcard::search()
{
	int id;
	bool flag = false;
	cout << "\n\t Enter card-id : ";
	cin >> id;
	ifstream in("Bcard.dat", ios::binary);
	if (!in)
		cout << "\n\t Unable to open the file! ";
	else
	{
		while (!in.eof())
		{
			if (!in.read((char *)this, sizeof(*this)))break;

			if (id == getid())
			{
				flag = true;
				cout << "\n\t FOUND SUCCESSFULLY ! \n\n";
				Displaycards();
				_getch();
				exit(0);
			}
		}
		if (flag==false)
		{
			cout << "\n\t Not found in Birth-Cards! \n";
		}
	}
	in.close();

}

void birthcard::show()
{
	ifstream in("Bcard.dat",ios::binary);
	if (!in)
		cout << "\n\t Unable to open the file! ";
	else
	{
		while (!in.eof())
		{
			if (!in.read((char *)this, sizeof *this))break;
			Displaycards();
		}
	}
	in.close();
}
Cards.h
#pragma once
#include "friendship.h"
#include "birthcard.h"
#include "baraat.h"

using namespace std;
class cards:public friendship,birthcard,baraat
{
protected:
	int id;
	string name, message;
public:
	cards();
	~cards();
	void Addcard() ;
	void deletecard() ;
	void viewcard();
	void show();
};




Cards.cpp
#include "cards.h"
cards::cards()
{
	id = 0;
	name = "unknown";
	message = "Hi";
}
cards::~cards()
{
}
void cards::Addcard()
{
	walima w;
	mehindi m;
	int ch;
	cout << "\n\t Please select any option ! \n";
	cout << "\n\t1) Birth cards ";
	cout << "\n\t2) Marriage cards ";
	cout << "\n\t3) Friendship cards ";
	cout << "\n\t4) Baraat cards ";
	cout << "\n\t5) Walima cards ";
	cout << "\n\t6) Mehindi cards \n \t \n\t choice : ";
	cin >> ch;
	switch (ch)
	{
	case 1:
		birthcard::Addcard();
		break;
	case 2:
		marraige::Addcard();
		break;
	case 3:
		friendship::Addcard();
		break;
	case 4:
		baraat::Addcard();
		break;
	case 5:
		w.Addcard();
		break;
	case 6:
		m.Addcard();
		break;
	default: cout << "\n\t Invalid choice ! ";
		break;
	}

}

void cards::viewcard()
{
	mehindi m;
	walima t;
	cout << "\n\t**************** SEARCH MENU **************** \n";
	birthcard::search();
	cout << "\n\t Checking in Marraige-Cards! \n";
	marraige::search();
	cout << "\n\t Checking in Friendship-Cards! \n";
	friendship::search();
	cout << "\n\t Checking in Baraat-Cards! \n";
	baraat::search();
	cout << "\n\t Checking in Walima-Cards! \n";
	t.search();
	cout << "\n\t Checking in Mehindi-Cards! \n";
	m.search();

}


void cards::show()
{
	int ch;
	char c = 'y';
	walima w;
	mehindi m;
	do
	{
		cout << "\n\t Please select any option ! \n";
		cout << "\n\t1) Birth cards ";
		cout << "\n\t2) Marriage cards ";
		cout << "\n\t3) Friendship cards ";
		cout << "\n\t4) Baraat cards ";
		cout << "\n\t5) Walima cards ";
		cout << "\n\t6) Mehindi cards \n\n \t choice : ";
		cin >> ch;
		switch (ch)
		{
		case 1:
			birthcard::show();
			break;
		case 2:
			marraige::show();
			break;
		case 3:
			friendship::show();
			break;
		case 4:
			baraat::show();
			break;
		case 5:
			w.show();
			break;
		case 6:
			m.show();
			break;
		default: cout << "\n\t Invalid choice ! ";
			break;
		}
		cout << "\n\t View another? (y/n) : ";
		cin >> c;
		if (c == 'y' || c == 'Y')
		{
			system("cls");
		}
		else if (c == 'n' || c == 'N')
		{
			fflush(stdin);
			system("cls");
			break;
		}
	} while (c == 'y' || c == 'Y');


}

void cards::deletecard()
{
	cout << "\n Cards successfully deleted! ";
}
Friendship.h
#pragma once
#include <string>
#include <iostream>
#include <conio.h>
#include <fstream>
using namespace std;
class friendship 
{
private:
	int id;
	string name, message;
public:
	friendship();
	friendship(int, string);
	~friendship();
	void Addcard();
	void deletecard();
	void Displaycards();
	void write();
	int getid();
	void viewcard();
	void search();
	void show();
};




Friendship.cpp
#include "friendship.h"


friendship::friendship()
{
	id = 0;
	name = "unknown";
}

friendship::friendship(int i,string n)
{
	id = i;
	name = n;
}

friendship::~friendship()
{
}

void friendship::Addcard()
{
	cout << "\n\t***********FriendshipCard****************\n";
	cout << "\n\t Enter card name : ";
	cin >> name;
	cout << "\n\t Enter card id : ";
	cin >> id;
	fflush(stdin);
	cout << "\n\t Enter a message for the receiver : ";
	getline(cin, message);
	system("cls");
	cout << "\n\t  CARD CREATED SUCCESSFULLY\n";
	write();
}
void friendship::deletecard()
{
	cout << "\n This card has been deleted! ";
}

void friendship::Displaycards()
{
	cout << "\n\t***********FriendshipCard****************";
	cout << "\n\t ID : " << id;
	cout << "\n\t Name : " << name;
	cout << "\n\t******************************************";
	cout << "\n\t Message for receiver : " << message;
	cout << "\n\t******************************************\n\n";
}

void friendship::write()
{
	ofstream of("Fcard.dat", ios::app | ios::binary);
	if (!of)
		cout << "\n\t Unable to open write! ";
	else
	{
		of.write((char *)this, sizeof(*this));
	}
	of.close();
}
void friendship::viewcard()
{
	ifstream in("Fcard.dat", ios::binary);
	if (!in)
		cout << "\n\t Unable to open write! ";
	else
	{
		while (!in.eof())
		{
			if (!in.read((char *)this, sizeof(*this)))break;
			Displaycards();
			cout << endl;
		}
	}
	in.close();
}

int friendship::getid()
{
	return id;
}

void friendship::search()
{
	int id;
	bool flag = false;
	cout << "\n\t Enter card-id : ";
	cin >> id;
	ifstream in("Fcard.dat", ios::binary);
	if (!in)
		cout << "\n\t Unable to open the file! ";
	else
	{
		while (!in.eof())
		{
			if (!in.read((char *)this, sizeof(*this)))break;

			if (id == getid())
			{
				flag = true;
				cout << "\n\t FOUND SUCCESSFULLY ! \n\n";
				Displaycards();
				_getch();
				exit(0);
			}
		}
		if (flag == false)
		{
			cout << "\n\t Not found in Friendship-Cards! \n";
		}
	}
	in.close();
}
void friendship::show()
{
	ifstream in("Fcard.dat", ios::binary);
	if (!in)
		cout << "\n\t Unable to open the file! ";
	else
	{
		while (!in.eof())
		{
			if (!in.read((char *)this, sizeof *this))break;
			Displaycards();
		}
	}
	in.close();
}
Marriage.h
#pragma once
#include <iostream>
#include <string>
#include <conio.h>
#include <fstream>
using namespace std;
class marraige 
{
protected:
	int id;
	string name,message;
public:
	marraige();
	marraige(int, string);
	~marraige();
	void Addcard();
	void deletecard();
	void Displaycards();
	void viewcard();
	void write();
	int getid();
	void search();
	void show();
};



Marriage.cpp
#include "marraige.h"


marraige::marraige()
{
	id = 0;
	name = "unknown";
}

marraige::marraige(int i,string n)
{
	id = i;
	name = n;
}

marraige::~marraige()
{
}

void marraige::Addcard()
{
	cout << "\n\t***********MarraigeCard****************\n";
	cout << "\n\t Enter card name : ";
	cin >> name;
	cout << "\n\t Enter card id : ";
	cin >> id;
	fflush(stdin);
	cout << "\n\t Enter a message for the receiver : ";
	getline(cin, message);
	system("cls");
	cout << "\n\t  CARD CREATED SUCCESSFULLY\n";
	write();
}
void marraige::deletecard()
{
	cout << "\n This card has been deleted! ";
}

void marraige::Displaycards()
{
	cout << "\n\t***********MarraigeCard****************";
	cout << "\n\t ID : " << id;
	cout << "\n\t Name : " << name;
	cout << "\n\t******************************************";
	cout << "\n\t Message for receiver : " << message;
	cout << "\n\t******************************************\n\n";
}

void marraige::write()
{
	ofstream of("Mcard.dat", ios::app | ios::binary);
	if (!of)
		cout << "\n\t Unable to open write! ";
	else
	{
		of.write((char *)this, sizeof(*this));
	}
	of.close();
}

void marraige::viewcard()
{
	ifstream in("Mcard.dat", ios::binary);
	if (!in)
		cout << "\n\t Unable to open write! ";
	else
	{
		while (!in.eof())
		{
			if (!in.read((char *)this, sizeof(*this)))break;
			Displaycards();
			cout << endl;
		}
	}

	in.close();
}

int marraige::getid()
{
	return id;
}



void marraige::search()
{
	int id;
	bool flag = false;
	cout << "\n\t Enter card-id : ";
	cin >> id;
	ifstream in("Mcard.dat", ios::binary);
	if (!in)
		cout << "\n\t Unable to open the file! ";
	else
	{
		while (!in.eof())
		{
			if (!in.read((char *)this, sizeof(*this)))break;

			if (id == getid())
			{
				flag = true;
				cout << "\n\t FOUND SUCCESSFULLY ! \n\n";
				Displaycards();
				_getch();
				exit(0);
			}
		}
		if (flag == false)
		{
			cout << "\n\t Not found in Marraige-Cards! \n";
		}
	}
	in.close();
}
void marraige::show()
{
	ifstream in("Mcard.dat", ios::binary);
	if (!in)
		cout << "\n\t Unable to open the file! ";
	else
	{
		while (!in.eof())
		{
			if (!in.read((char *)this, sizeof *this))break;
			Displaycards();
		}
	}
	in.close();
}
Mehindi.h
#pragma once
#include "marraige.h"

class mehindi :
	public marraige
{
private: 
	string Name;
public:
	mehindi();
	mehindi(int, string);
	~mehindi();
	void Addcard();
	int getid();
	void search();
	void deletecard();
	void Displaycards();
	void write();
	void viewcard();
	void show();
};




Mehindi.cpp
#include "mehindi.h"


mehindi::mehindi()
{
	id = 0;
	name = "unknown";
}

mehindi::mehindi(int i,string n)
{
	id = i;
	name = n;
}

mehindi::~mehindi()
{
}

void mehindi::Addcard()
{
	cout << "\n\t***********MEHINDI-CARD****************\n";
	cout << "\n\t Enter card name : ";
	cin >> name;
	cout << "\n\t Enter card id : ";
	cin >> id;
	fflush(stdin);
	cout << "\n\t Enter a message for the receiver : ";
	getline(cin, message);
	system("cls");
	cout << "\n\t  CARD CREATED SUCCESSFULLY\n";
	write();
}
void mehindi::deletecard()
{
	cout << "\n This card has been deleted! ";
}
void mehindi::Displaycards()
{
	cout << "\n\t***********MEHINDI-CARD****************";
	cout << "\n\t ID : " << id;
	cout << "\n\t Name : "<< name;
	cout << "\n\t******************************************";
	cout << "\n\t Message for receiver : " << message;
	cout << "\n\t******************************************\n\n";
}

void mehindi::write()
{
	ofstream of("MMcard.dat", ios::app | ios::binary);
	if (!of)
		cout << "\n\t Unable to open write! ";
	else
	{
		of.write((char *)this, sizeof(*this));
	}
	of.close();
}

void mehindi::viewcard()
{
	ifstream in("MMcard.dat", ios::binary);
	if (!in)
		cout << "\n\t Unable to open write! ";
	else
	{
		while (!in.eof())
		{
			if (!in.read((char *)this, sizeof(*this)))break;
			Displaycards();
			cout << endl;
		}
	}
	in.close();
}

int mehindi::getid()
{
	return id;
}
void mehindi::search()
{
	int id;
	bool flag = false;
	cout << "\n\t Enter card-id : ";
	cin >> id;
	ifstream in("MMcard.dat", ios::binary);
	if (!in)
		cout << "\n\t Unable to open the file! ";
	else
	{
		while (!in.eof())
		{
			if (!in.read((char *)this, sizeof(*this)))break;

			if (id == getid())
			{
				flag = true;
				cout << "\n\t FOUND SUCCESSFULLY ! \n\n";
				Displaycards();
				_getch();
				exit(0);
			}
		}
		if (flag == false)
		{
			cout << "\n\t Not found in Any of the Cards! \n";
		}
	}
	in.close();
}
void mehindi::show()
{
	ifstream in("MMcard.dat", ios::binary);
	if (!in)
		cout << "\n\t Unable to open the file! ";
	else
	{
		while (!in.eof())
		{
			if (!in.read((char *)this, sizeof *this))break;
			Displaycards();
		}
	}
	in.close();
}
Member.h
#include "memberlist.h"
#include <fstream>
#include <string>
#pragma once
class member :public memberlist
{
private:
	int memberid;
	string paSS;
	string status;
public:
	member();
	void set(int,string);
	~member();
	void Verifyuser();
	void deleteMember();
	void Display();
	void Signup();
	void Login();
	void viewmembers();
};



Member.cpp
#include "member.h"

member::member()
{
	memberid = 1234;
	paSS = "harry";
	status = "Member";
}
member::~member()
{
}
void member::set(int m, string p)
{
	memberid = m;
	paSS = p;
}
void member::Verifyuser()
{
	memberlist::Verifyuser();
}

void member::deleteMember()
{
	int id;
	cout << "\n\t Enter a member id to delete : ";
	cin >> id;
	ifstream fin("Msignup.dat", ios::binary);
	if (!fin)
	{
		cout << "\n\t Unable to open the file! ";
	}
	else
	{
		ofstream fout("temp.dat", ios::binary);
		if (!fout)
		{
			cout << "\n\t Unable to open ";
		}

		while (!fin.eof())
		{
			fin.read((char *)this, sizeof(*this));
			if (memberid != id)
			{
				fout.write((char *)this, sizeof(this));
			}
			fin.read((char *)this, sizeof(*this));
		}
		fin.close();
		fout.close();
		remove("Msignup.dat");
		rename("temp.dat", "Msignup.dat");
	}
}

void member::Display()
{
	cout << "\n\t Status : " << status;
	cout << "\n\t member name : " << name;
	cout << "\n\t member age : " << age;
	cout << "\n\t Member id : " << memberid;
	cout << "\n\t Password : " << paSS;
	cout << "\n\t email : " << Email;
	cout << "\n\t cnic : " << cnic;
	cout << "\n\t phone : " << phone;
}

void member::Signup()
{
	cout << "\n\t --------------SIGN UP----------------\n";
	cout << "\n " << "\tEnter a memberid of your choice : ";
	cin >> memberid;
	cout << "\n\t Enter your password : ";
	cin >> paSS;
	cout << "\n\t Enter member's name : ";
	cin >> name;
	cout << "\n\t Enter member's age : ";
	cin >> age;
	cout << "\n\t Enter email of member : ";
	cin >> Email;
	cout << "\n\t Enter cnic of member : ";
	cin >> cnic;
	cout << "\n\t Enter phone of member's : ";
	cin >> phone;
	ofstream of("Msignup.dat", ios::app | ios::binary);
	if (!of)
		cout << "\n\t Unable to open the file! \n";
	else
	{
		of.write((char *)this, sizeof(*this));
		cout << "\n\t Account Created Successfully! \n";
	}
	of.close();
}

void member::Login()
{
	int m;
	string p;
	bool flag = true;
	cout << "\n\t*************** MEMBER-LOGIN *************** \n";
	cout << "\n" << "\t Enter your memberid : ";
	cin >> m;
	cout << "\n\t Enter your password : ";
	cin >> p;
	ifstream r("Msignup.dat", ios::binary);
	if (!r)
		cout << "\n\t Unable to open the file ! \n";
	else
	{
		while (!r.eof())
		{
			r.read((char *)this, sizeof(*this));
			if (p == paSS && m == memberid)
			{
				system("cls");
				cout << "\n\t Login Successful ! \n ";
				cout << "\n\t----------------MEMBER MENU--------------------\n";
			}
			else flag = false;
		}
		if (flag == false)
		{
			system("cls");
			cout << "\n\t Invalid username or email! Try again \n";
			Login();
		}
	}
	r.close();

}
void member::viewmembers()
{
	ifstream r("Msignup.dat", ios::binary);
	if (!r)
		cout << "\n\t Unable to open the file ! \n";
	else
	{
		cout << "\n\t MEMBER DETAILS \n";
		while (!r.eof())
		{
			if (!r.read((char *)this, sizeof(*this)))break;
			Display();
			cout << "\n";
		}
	}
	r.close();
}
Walima.h
#pragma once
#include "mehindi.h"
#include <conio.h>
class walima :
	public marraige
{
private:
	
public:
	walima();
	walima(int, string);
	~walima();
	void Addcard();
	void deletecard();
	void Displaycards();
	void write();
	int getid();
	void search();
	void viewcard();
	void show();
};




Walima.cpp
#include "walima.h"


walima::walima()
{
	id = 0;
	name = "unknown";
}
walima::walima(int i, string n)
{
	id = i;
	name = n;
}

walima::~walima()
{
}

void walima::Addcard()
{
	cout << "\n\t***********WALIMA-CARD****************\n";
	cout << "\n\t Enter card name : ";
	cin >> name;
	cout << "\n\t Enter card id : ";
	cin >> id;
	fflush(stdin);
	cout << "\n\t Enter a message for the receiver : ";
	getline(cin, message);
	system("cls");
	cout << "\n\t  CARD CREATED SUCCESSFULLY\n";
	write();
}
void walima::deletecard()
{
	cout << "\n This card has been deleted! ";
}
void walima::Displaycards()
{
	cout << "\n\t***********WALIMA-CARD****************";
	cout << "\n\t ID : " << id;
	cout << "\n\t Name : " << name;
	cout << "\n\t******************************************";
	cout << "\n\t Message for receiver : " << message;
	cout << "\n\t******************************************\n\n";
}

void walima::write()
{
	ofstream of("Wcard.dat", ios::app | ios::binary);
	if (!of)
		cout << "\n\t Unable to open write! ";
	else
	{
		of.write((char *)this, sizeof(*this));
	}
	of.close();

}

void walima::viewcard()
{
	ifstream in("Wcard.dat", ios::binary);
	if (!in)
		cout << "\n\t Unable to open write! ";
	else
	{
		while (!in.eof())
		{
			if (!in.read((char *)this, sizeof(*this)))break;
			Displaycards();
			cout << endl;
		}
	}

	in.close();
}

void walima::search()
{
	int id;
	bool flag = false;
	cout << "\n\t Enter card-id : ";
	cin >> id;
	ifstream in("Wcard.dat", ios::binary);
	if (!in)
		cout << "\n\t Unable to open the file! ";
	else
	{
		while (!in.eof())
		{
			if (!in.read((char *)this, sizeof(*this)))break;

			if (id == getid())
			{
				flag = true;
				cout << "\n\t FOUND SUCCESSFULLY ! \n\n";
				Displaycards();
				_getch();
				exit(0);
			}
		}
		if (flag == false)
		{
			cout << "\n\t Not found in Walima-Cards! \n";
		}
	}
	in.close();

}

int walima::getid()
{
	return id;
}

void walima::show()
{
	ifstream in("Wcard.dat", ios::binary);
	if (!in)
		cout << "\n\t Unable to open the file! ";
	else
	{
		while (!in.eof())
		{
			if (!in.read((char *)this, sizeof *this))break;
			Displaycards();
		}
	}
	in.close();
}
Driver File:
#include <iostream>
#include "admin.h"
#include "cards.h"
#include "baraat.h"
#include "birthcard.h"
#include "friendship.h"
#include "marraige.h"
#include "user.h"
#include "mehindi.h"
#include "walima.h"
#include <conio.h>
#include <stdio.h>
using namespace std;
int main()
{ 
	char ch,Ch;
	user *u = new user;
	member *m = new member;
	admin *a = new admin;
	cards *c = new cards;
	menu:
	cout << "\n\t********************************* WELCOME TO ELECTRONIC CARD SYSTEM *********************************\n";
	cout << "\n\t  1) Admin Details ";
	cout << "\n\t  2) Member Details ";
	cout << "\n\t  3) User Details ";
	cout << "\n\t  4) Signup as a User";
	cout << "\n\t  5) Addusers (signup) (member/admin) ";
	cout << "\n\t  6) Login as User ";
	cout << "\n\t  7) Login as Member ";
	cout << "\n\t  8) Login as Admin ";
	cout << "\n\t  9) Delete Admin ";
	cout << "\n\t 10) Delete Member ";
	cout << "\n\t 11) Delete User \n\n\t choice : ";
	cin >> ch;
	if (ch == '1')
	{
		system("cls");
		u->viewadmins();   // existing Admins reading data from files
		goto menu;
	}
	else if (ch == '2')
	{
		system("cls");
		u->viewmembers();  // data of existing members from files 
		goto menu;
	}
	else if (ch == '3')
	{
		system("cls");
		u->viewuser();
		goto menu;
	}
	
	else if (ch == '4')
	{
		system("cls");
		u->Signup();     // signup as a user
		u->Login();
	}
	else if (ch == '5')
	{
		system("cls");
		u->Adduser();     // either Admin or Member
	}
	else if (ch == '6')
	{
		system("cls");
		u->Login();       // admin and member class have their separat login system 
	}
	else if (ch == '7')
	{
		system("cls");
		m->Login();
	}
	else if (ch == '8')
	{
		system("cls");
		a->Login();
	}
	else if (ch == '9')
	{
		system("cls");
		a->Deleteadmin();
	}
	else if (ch == '10')
	{
		system("cls");
		m->deleteMember();
	}
	else if (ch == '11')
	{
		system("cls");
		u->Delete();
	}
	
	ccard:
	cout << "\n\t******************* CARD DESIGN MENU *********************************\n";
	cout << "\n\t 1) Add Card ";
	cout << "\n\t 2) Search Card ";
	cout << "\n\t 3) View Cards ";
	cout << "\n\t 4) Delete Cards \n\n\t ";
	cin >> Ch;
	if (Ch == '1')
	{
		system("cls");
		c->Addcard();
		goto ccard;
	}
	else if (Ch == '2')
	{
		system("cls");
		c->viewcard();
	}
	else if (Ch == '3')
	{
		system("cls");
		c->show();
		goto ccard;
	}
	else if (Ch == '4')
	{
		system("cls");
		c->deletecard();
	}
	else
	{
		cout << "\n\t Invalid Choice! Try again ";
	}

	_getch();
}
