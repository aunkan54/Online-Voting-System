#include<bits/stdc++.h>
#include<iostream>
#include<stdlib.h>
#include<stdio.h>
#include<conio.h>
#include<vector>
#include<iterator>
#include<map>
#include<string>
#include<fstream>
#include<sstream>
#include<ctime>
#include<windows.h>
#include<dos.h>
#include<typeinfo>

using namespace std;

int sec_count = 0,sec = 0;

map<int,int> voter_count;
map<int,int> candidate_count;


template <typename T> /// Use of Template for publishing Result
void Result(T t,T i1)
{
    if(t==2)
    {
        cout << "\t*****Voting hasn't started yet*****\n\n\t";
        Sleep(400);
        system("pause");
        Sleep(300);
        return;
    }
    else if(t==0)
    {
        cout << "\t*****Voting has not finished yet*****"
             << "\n\n\t   Result will be published soon.\n\n\t";

        Sleep(200);
        system("pause");
        Sleep(300);
        return;
    }
    else if(t==1)
    {
        map<int,int> :: iterator it;
        int max_vote = 0, second_max_vote = 0;

        for(int k=1;k<i1;k++)
        {
            if(candidate_count[k]>max_vote)
            {
                second_max_vote = max_vote;
                max_vote = candidate_count[k];
            }
            else if(candidate_count[k]==max_vote)
            {
                second_max_vote = candidate_count[k];
            }
            else if(candidate_count[k]>second_max_vote&&candidate_count[k]<max_vote)
            {
                second_max_vote = candidate_count[k];
            }

        }

        fstream candidate;

        candidate.open("Candidate.csv", ios::in);

        vector<string> row;
        string line,word,temp;
        int init = 1;

        while(candidate>>temp)
        {
            row.clear(); /// clearing all elements of the vector

            getline(candidate,line);
            stringstream s(line);

            while(getline(s,word,','))   /// pushing values in vector row
            {
                row.push_back(word);
            }
            cout << init << ".Candidate's Name: " << row[0] << "\n"
                 << "Candidate's Party: " << row[1] << "\n"
                 << "Candidate's Symbol: " << row[2] << "\n\n"
                 << "Vote Count: " << candidate_count[init] << "\n\n";
            init++;
        }

        candidate.close();

        if(max_vote==second_max_vote)
        {
            cout << "\n\nElection has Tied\n\n";
            candidate.close();
            system("pause");
            Sleep(300);
            return;
        }
        else
        {
            int initia = 1;

            for(it=candidate_count.begin();it!=candidate_count.end();it++)
            {
                if(it->second==max_vote)
                {
                    fstream candidate;

                    candidate.open("Candidate.csv", ios::in);

                    vector<string> row;
                    string line,word,temp;
                    int initia = 1;

                    while(candidate>>temp)
                    {
                        row.clear(); /// clearing all elements of the vector

                        getline(candidate,line);
                        stringstream s(line);

                        while(getline(s,word,','))   /// pushing values in vector row
                        {
                            row.push_back(word);
                        }
                        if(it->first==initia)
                        {
                            cout << "\nWinner of the Election is: " << row[0] << "\n\n";
                            candidate.close();
                            system("pause");
                            Sleep(300);
                            return;
                        }
                        initia++;
                    }
                }
            }
        } /// end of else case(winner case)
    }
} /// End of template function


class Base
/// abstract base class
{
protected:
    string fname,lname,f_name,add,pass,mob,c_name,c_party,c_symbol;
    int nid_number,vote_end = 2;
public:
    void virtual display() = 0; /// Pure Virtual Function
};


class Admin : public Base /// Base class publicly Inherited
{
public:
    void set_vote_end(int v_end)
    {
        vote_end = v_end;
    }
    int get_vote_end()
    {
        return vote_end;
    }
    void display() /// Runtime Polymorphism
    {
        cout << "All the enlisted Candidate's List: \n\n";

        fstream candidate;

        candidate.open("Candidate.csv", ios::in);

        vector<string> row;
        string line,word,temp;

        while(candidate>>temp)
        {
            row.clear(); /// clearing all elements of the vector

            getline(candidate,line);
            stringstream s(line);

            while(getline(s,word,','))   /// pushing values in vector row
            {
                row.push_back(word);
            }
            cout << "\nCandidate's Name: " << row[0] << "\n"
                 << "Candidate's Party: " << row[1] << "\n"
                 << "Candidate's Symbol: " << row[2] << "\n\n";
        }

        candidate.close();
    }
};

class Candidate : public Base
{
public:
    int initial = 1;
    void candidate_name(string can_name)
    {
        c_name = can_name;
    }
    void candidate_party(string can_party)
    {
        c_party = can_party;
    }
    void candidate_symbol(string can_symbol)
    {
        c_symbol = can_symbol;
    }

    void operator++(int) /// Operator Overloading
    {
        initial++;
    }

    void candidate_write()
    {
        fstream candidate;

        candidate.open("Candidate.csv", ios::out | ios::app);

        candidate << initial << ", "
                  << c_name << ", "
                  << c_party << ", "
                  << c_symbol << "\n";

        candidate.close();
    }

    void display()
    {

    }
};


class Voter : public Base
/// class for setting values of voter registration
/// abstract base class publicly inherited
{
public:
    int initial = 1;
    void first_name(string f)
    {
        fname = f;
    }
    void last_name(string l)
    {
        lname = l;
    }
    void father_name(string fn)
    {
        f_name = fn;
    }
    void address(string a)
    {
        add = a;
    }
    void mobile(string m)
    {
        mob = m;
    }
    void national_id(int n)
    {
        nid_number = n;
    }
    void password(string p)
    {
        pass = p;
    }

    void file_write() /// function to write voter information in csv file
    {
        fstream f_reg;

        f_reg.open("Voter_List.csv", ios::out | ios::app);

        f_reg << initial << ", "
              << pass << ", "
              << nid_number << ", "
              << fname << ", "
              << lname << ", "
              << f_name << ", "
              << add << ", "
              << mob << "\n";
        initial++;

        f_reg.close();
    }

    void display() /// Runtime Polymorphism
    {
        cout << "All the enlisted Candidate's List: \n\n";

        fstream candidate;

        candidate.open("Candidate.csv", ios::in);

        vector<string> row;
        string line,word,temp;

        while(candidate>>temp)
        {
            row.clear(); /// clearing all elements of the vector

            getline(candidate,line);
            stringstream s(line);

            while(getline(s,word,','))   /// pushing values in vector row
            {
                row.push_back(word);
            }
            cout << "\nCandidate's Name: " << row[0] << "\n"
                 << "Candidate's Party: " << row[1] << "\n"
                 << "Candidate's Symbol: " << row[2] << "\n\n";
        }

        candidate.close();
    }
};

/// called from main function after successful login

/// c,C,C1,C2,C3,C4 used
///A,B,D,E,F,G,H,I,J used

int main()
{
    Voter V;
    Candidate Can;
    Admin Ad;

    /// Runtime Polymorphism
    Base* bptr[2];
    bptr[0] = &V;
    bptr[1] = &Ad;

    time_t start, finish;

    int c,i1=0; /// to check login or registration

    while(true) /// choice for Login or Registration
    {
        string f,l,fn,a,m,p,s;
        int n;
        J:cout << "1. Login\n2. Registration\n3. Exit\n\nEnter your choice: ";
        cin >> c;
        Sleep(300);
        system("CLS");

        switch(c)
        {
        case 1: /// login
        {
            int C; /// to check login as admin or voter

            A:cout << "To Log in as Admin \"Press 1\": "; /// A used
            cout << "\nTo Log in as Voter \"Press 2\": \n\nEnter your choice: ";
            cin >> C;
            Sleep(300);
            system("CLS");
            if(C==1) /// Login as an Admin
            {
                string pass = "admin";
                int code = 6000,wrong_count = 0;

                cout << "Enter Admin Code: ";
                D:cin >> n;
                if(n==code)
                {
                    cout << "\n\nEnter Password: ";
                    B:string P ="";
                    char ch;
                    ch = _getch();
                    while(ch != 13)
                    {
                       P.push_back(ch);
                       cout << '*';
                       ch = _getch();
                    }
                    if(P==pass)
                    {
                        Sleep(500);
                        system("CLS");
                        cout << "!!!!!!Login Successful!!!!!!\n\n";
                        int C2; /// to check functions of successful admin login
                        H:cout << "1. Voter Lists\n2. Candidates List"
                               << "\n3. Start Voting"
                               << "\n4. Result\n5. Log Out"
                               << "\n\nEnter your Choice: ";
                        cin >> C2;
                        Sleep(300);
                        system("CLS");
                        switch(C2) /// start of switch case for
                        {
                        case 1: ///Voters List
                            {
                                cout << "All the enlisted Voters list: \n\n";

                                fstream vote_list;
                                vote_list.open("Voter_List.csv", ios::in);

                                vector<string> row;
                                string line,word,temp;
                                int nid;

                                while(vote_list>>temp)
                                {
                                    row.clear(); /// clearing all elements of the vector

                                    getline(vote_list,line);
                                    stringstream s(line);

                                    while(getline(s,word,','))   /// pushing values in vector row
                                    {
                                        row.push_back(word);
                                    }
                                    cout << "First Name: " << row[2]
                                         << "\nLast Name: " << row[3]
                                         << "\nFather's Name: " << row[4]
                                         << "\nAddress: " << row[5]
                                         << "\nMobile No: +880-" << row[6]
                                         << "\nNID Number: " << row[1] << "\n\n";
                                } /// end of file reading for voters list

                                vote_list.close();
                                Sleep(1000);
                                system("pause");
                                system("CLS");
                                Sleep(200);
                                goto H;
                            } /// end of case 1 for admin successful login
                        case 2: ///Candidates List
                            {
                                int C3; /// to check functions of candidate's list
                                I:cout << "1. Enlist a New Candidate"
                                     << "\n2. Check List of all the Candidates"
                                     << "\n3. Return to Admin Menu\n\n";
                                cout << "Enter your choice: ";
                                cin >> C3;
                                system("CLS");
                                Sleep(200);
                                switch(C3)
                                {
                                case 1:
                                    {
                                        if(Ad.get_vote_end()==2)
                                        {
                                            string can_name,can_party,can_symbol;

                                            cout << "Enter Candidate's Name: ";
                                            cin >> can_name;
                                            Can.candidate_name(can_name);

                                            cout << "\nEnter Candidate's Party Name: ";
                                            cin >> can_party;
                                            Can.candidate_party(can_party);

                                            cout << "\nEnter Candidate's Symbol: ";
                                            cin >> can_symbol;
                                            Can.candidate_symbol(can_symbol);

                                            Can++;

                                            Sleep(400);
                                            cout << "\n\n!!!!!!Canidate Enlisted Successfully!!!!!!\n\n\n";

                                            Can.candidate_write();

                                            Sleep(300);

                                            system("pause");
                                            Sleep(500);
                                            system("CLS");
                                            goto I;
                                        }
                                        else
                                        {
                                            cout << "*****You can't add any more Candidate*****\n\n";
                                            Sleep(500);
                                            system("pause");
                                            Sleep(500);
                                            system("CLS");
                                            goto I;
                                        }

                                    }
                                case 2:
                                    {
                                        bptr[1]->display();  /// Runtime polymorphism
                                        Sleep(500);
                                        system("pause");
                                        Sleep(500);
                                        system("CLS");
                                        goto I;
                                    }
                                case 3:
                                    {
                                        goto H;
                                    }
                                } /// end of switch case for candidates list check in outer case 2
                            } /// end of case 2 for admin successful login
                        case 3: /// Start Voting
                            {
                                if(Ad.get_vote_end()==2)
                                {
                                    Ad.set_vote_end(0);
                                    i1 = 1;

                                    fstream candidate;

                                    candidate.open("Candidate.csv", ios::in);

                                    vector<string> row;
                                    string line,word,temp;

                                    while(candidate>>temp)
                                    {
                                        row.clear(); /// clearing all elements of the vector

                                        getline(candidate,line);
                                        stringstream s(line);

                                        while(getline(s,word,','))   /// pushing values in vector row
                                        {
                                            row.push_back(word);
                                        }
                                        candidate_count[i1] = 0;
                                        i1++;
                                    }

                                    candidate.close();
                                    cout << "Enter Time Period for Voting: ";
                                    cin >> sec;
                                    Sleep(500);
                                    system("CLS");
                                    cout << "\t******Vote has Started******\n\n\t";
                                    time(&start);
                                    system("pause");
                                    Sleep(300);
                                    system("CLS");
                                    goto H;
                                }
                                else if(Ad.get_vote_end()==0)
                                {
                                    cout << "\t***Vote has already started***\n\n\t";
                                    system("pause");
                                    Sleep(300);
                                    system("CLS");
                                    goto H;
                                }
                                else if(Ad.get_vote_end()==1)
                                {
                                    cout << "\t\t***ERROR***\nVoting has already ended. You can't start voting again\n\n\n\t";
                                    system("pause");
                                    Sleep(300);
                                    system("CLS");
                                    goto H;
                                }
                            }
                        case 4: ///result publish
                            {
                                Result<int>(Ad.get_vote_end(),i1);
                                Sleep(300);
                                system("CLS");
                                goto H;
                            }
                        case 5: /// Admin Logging out
                            {
                                cout << "\t\tLogging out\n\n\t";
                                Sleep(200);
                                system("pause");
                                system("CLS");
                                Sleep(300);
                                goto J;
                            }
                        } /// end of switch case condition for admin successful login
                    } /// end of admin successful login

                    else
                    {
                        system("CLS");
                        cout << "\n\t  !!!Wrong Password!!!\n        You have ";
                        wrong_count++;
                        cout << 3-wrong_count << " chances left.";
                        if(wrong_count==3)
                        {
                            system("CLS");
                            cout << "\n\t   *******WARNNING*******\n  You have entered wrong password for 3 times.\n\n";
                            Sleep(1000);

                            cout << "\n\tReturning to Main Menu in 3 sec!" << '\r';
                            Sleep(1400);

                            cout << "\tReturning to Main Menu in 2 sec!" << '\r';
                            Sleep(1400);

                            cout << "\tReturning to Main Menu in 1 sec!" << '\r';
                            Sleep(1400);

                            cout << "\t";
                            system("pause");
                            Sleep(1000);
                            system("CLS");
                            goto J;
                        }
                        Sleep(1500);
                        system("CLS");
                        cout << "Entered Admin Code: " << n << "\n\n";
                        cout << "Enter your password again: ";
                        goto B;
                    }
                }
                else
                {
                    system("CLS");
                    Sleep(100);
                    cout << "Wrong Code for login. Enter again: ";
                    goto D;
                }

            } /// end of login as admin

            else if(C==2) /// Login as a Voter
            {
                cout << "Enter your NID number: "; /// taking input for login
                G:cin >> n;

                fstream f_login;  /// declaring file

                f_login.open("Voter_List.csv", ios::in);

                vector<string> row;
                string line,word,temp;
                int nid;

                while(f_login>>temp)
                {
                    row.clear(); /// clearing all elements of the vector

                    getline(f_login,line);
                    stringstream s(line);

                    while(getline(s,word,','))   /// pushing values in vector row
                    {
                        row.push_back(word);
                    }

                    nid = std::stoi(row[1]); /// converting nid from string to integer

                    int i,j,Count = 0;
                    if(n==nid)  /// checking nid
                    {
                        int wrong_count = 0;
                        cout << "\nEnter your Password: ";
                        E:string P = "";
                        char ch;
                        ch = _getch();
                        while(ch != 13)
                        {
                            P.push_back(ch);
                            cout << '*';
                            ch = _getch();
                        }
                        if(P.size()!=(row[0].size()-1))
                        {
                            Count = 0;
                            system("CLS");
                            cout << "\n\t  !!!Wrong Password!!!\n        You have ";
                            wrong_count++;
                            cout << 3-wrong_count << " chances left.";
                            if(wrong_count==3)
                            {
                                Sleep(1000);
                                system("CLS");
                                cout << "\t   *******WARNNING*******\n  You have entered wrong password for 3 times.\n\n";
                                cout << "     Returning to Main Menu in 3 sec!" << '\r';
                                Sleep(1200);

                                cout << "     Returning to Main Menu in 2 sec!" << '\r';
                                Sleep(1200);

                                cout << "     Returning to Main Menu in 1 sec!" << '\r';
                                Sleep(1200);

                                cout << "     ";
                                system("pause");
                                system("CLS");
                                goto J;
                            }
                            Sleep(1500);
                            system("CLS");
                            cout << "Entered NID number: " << n << "\n";
                            cout << "\nEnter your password again: ";
                            goto E;
                        }
                        else
                        {
                            for(i=0,j=1; i<P.size(),j<row[0].size(); i++,j++)
                            {
                                if(P.at(i)!=row[0].at(j))
                                {
                                    Count = 0;
                                    system("CLS");
                                    cout << "\n\t  !!!Wrong Password!!!\n        You have ";
                                    wrong_count++;
                                    cout << 3-wrong_count << " chances left.";
                                    if(wrong_count==3)
                                    {
                                        Sleep(1000);
                                        system("CLS");
                                        cout << "\t   *******WARNNING*******\n  You have entered wrong password for 3 times.\n\n";
                                        cout << "     Returning to Main Menu in 3 sec!" << '\r';
                                        Sleep(1200);

                                        cout << "     Returning to Main Menu in 2 sec!" << '\r';
                                        Sleep(1200);

                                        cout << "     Returning to Main Menu in 1 sec!" << '\r';
                                        Sleep(1200);

                                        cout << "     ";
                                        system("pause");
                                        system("CLS");
                                        goto J;
                                    }
                                    Sleep(1500);
                                    system("CLS");
                                    cout << "Entered NID number: " << n << "\n";
                                    cout << "\n\nEnter your password again: ";
                                    goto E;
                                }
                                else Count = 1;
                            }
                            if(Count==1)
                            {
                                system("CLS");
                                Sleep(200);
                                cout << "\t!!!!!!Successful Login!!!!!!\n\n";
                                int C1;
                                F:cout << "1. Personal Information\n2. Candidates List"
                                     << "\n3. Cast your vote\n4. Result\n5. Log Out"
                                     << "\n\nEnter your Choice: ";
                                cin >> C1; /// to check functions of successful voter login
                                system("CLS");
                                Sleep(300);
                                switch(C1)
                                {
                                case 1: /// Personal Information
                                    {
                                        cout << "First Name: " << row[2]
                                             << "\nLast Name: " << row[3]
                                             << "\nFather's Name: " << row[4]
                                             << "\nAddress: " << row[5]
                                             << "\nMobile No: +880-" << row[6]
                                             << "\nNID Number: " << row[1] << "\n\n";

                                        Sleep(400);
                                        system("pause");
                                        system("CLS");
                                        Sleep(300);
                                        goto F;
                                    }

                                case 2: /// Candidates List
                                    {
                                        bptr[0]->display(); /// Runtime polymorphism function
                                        Sleep(400);
                                        system("pause");
                                        system("CLS");
                                        Sleep(300);
                                        goto F;
                                    }

                                case 3: /// Cast your vote
                                    {
                                        if(Ad.get_vote_end()==0)
                                        {
                                            time(&finish);
                                            sec_count += difftime(finish,start);
                                            if(sec_count>=sec)
                                            {
                                                Ad.set_vote_end(1);
                                            }
                                            else time(&start);
                                        }

                                        if(voter_count[n]==0 && Ad.get_vote_end()==0)
                                        {
                                            cout << "All the enlisted Candidate's List: \n\n";

                                            fstream candidate;

                                            candidate.open("Candidate.csv", ios::in);

                                            vector<string> row;
                                            string line,word,temp;
                                            int ini = 1;

                                            while(candidate>>temp)
                                            {
                                                row.clear(); /// clearing all elements of the vector

                                                getline(candidate,line);
                                                stringstream s(line);

                                                while(getline(s,word,','))   /// pushing values in vector row
                                                {
                                                    row.push_back(word);
                                                }
                                                cout << ini << ".Candidate's Name: " << row[0] << "\n"
                                                     << " Candidate's Party: " << row[1] << "\n"
                                                     << " Candidate's Symbol: " << row[2] << "\n\n";
                                                ini++;
                                            }

                                            cout << "Enter your vote: ";
                                            int vote;
                                            cin >> vote;
                                            candidate_count[vote] += 1;
                                            voter_count[n] = 1;
                                            candidate.close();

                                            system("CLS");

                                            Sleep(400);
                                            cout << "\n!!!!!!You Voted Successfully!!!!!!\n\n\n";
                                            Sleep(300);
                                            system("pause");
                                            system("CLS");
                                            Sleep(200);

                                            goto F;
                                        }
                                        else if(Ad.get_vote_end()==2)
                                        {
                                            cout << "\t\t!!!!!!ERROR!!!!!!\n\n\t   Voting hasn't started yet.\n"
                                                 << "\tYou can't vote at this moment.\n\n\t";

                                            Sleep(400);
                                            system("pause");
                                            system("CLS");
                                            Sleep(300);
                                            goto F;
                                        }
                                        else if(Ad.get_vote_end()==1)
                                        {
                                            cout << "\t\t!!!!!!ERROR!!!!!!\n\t\tVoting has Ended.\n"
                                                 << "\t You can't vote at this moment.\n\n\t";

                                            Sleep(400);
                                            system("pause");
                                            system("CLS");
                                            Sleep(300);
                                            goto F;
                                        }
                                        else if(voter_count[n]==1)
                                        {
                                            cout << "\t  *****ERROR*****\n\tYou have already voted\n Voting more than once is restricted."
                                                 << "\n\n\t!!!Redirecting to Menu!!!\n     ";
                                            Sleep(200);
                                            system("pause");
                                            system("CLS");
                                            Sleep(300);
                                            goto F;
                                        }
                                    }

                                case 4: /// Result
                                    {
                                        Result<int>(Ad.get_vote_end(),i1);
                                        system("CLS");
                                        Sleep(300);
                                        goto F;
                                    } /// end of case 4 (Result)

                                case 5: ///Log Out
                                    {
                                        f_login.close();
                                        cout << "\n\n\t!!!!!!Logging Out!!!!!!\n\n    ";
                                        Sleep(300);
                                        system("pause");
                                        system("CLS");
                                        Sleep(300);
                                        break;
                                    }
                                }
                                break;
                            }
                        }
                    } /// checking nid ends
                } /// entering login system ends

                if(f_login.eof())
                {
                    system("CLS");
                    cout << "ID not found. Enter another NID: ";
                    goto G;
                }
            } /// end of login as voter
            else
            {
                cout << "Wrong Key Entered. Press again.\n\n";
                goto A;
            }
            break;
        } /// end of login menu
        case 2: ///registration
        {
            cout << "Enter your First Name: ";
            cin >> f;
            V.first_name(f);

            cout << "\nEnter your Last Name: ";
            cin >> l;
            V.last_name(l);

            cout << "\nEnter your Father's Name: ";
            cin >> fn;
            V.father_name(fn);

            cout << "\nEnter your Address: ";
            cin >> a;
            V.address(a);

            cout << "\nEnter your Mobile Number: +880";
            cin >> m;
            V.mobile(m);

            cout << "\nEnter your NID Number: ";
            cin >> n;
            V.national_id(n);

            cout << "\nEnter your Password: ";
            cin >> p;
            V.password(p);

            Sleep(500); ///sleep the console for 500 milliseconds
            cout << "\n\nRegistration Successful!!!" << "\n\n";

            voter_count[n] = 0;

            system("pause"); ///press any key to continue
            system("CLS");
            Sleep(300);

            V.file_write();

            break;
        }
        case 3: ///Exit
            {
                exit(0);
            }
        }
    }
}
