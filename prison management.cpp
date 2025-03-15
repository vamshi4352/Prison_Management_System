#include <iostream>
#include <conio.h>
#include <windows.h>
#include <mysql.h>
#include <sstream>
#include <cstring>
#include <string>
using namespace std;

class person;
class inmate;
class officer;

MYSQL* con, * connected;
int qstate;

class person
{
protected:
    string name;
    int age;
    string address;
    string gender;
    int phone_no;
    string email_id;
    int get_gender()
    {
        cout << "M.Male\n";
        cout << "F.FeMale\n";
        cout << "O.Others\n";
        cout << "Enter gender:\n";
        string x;
        cin >> x;
        gender = x;
        return 0;
    }

public:
    person()
    {
        cin.ignore();
        cout << "Enter name:\n";
        getline(cin, name);
        cin.ignore();
        cout << "Enter age:\n";
        cin >> age;
        get_gender();
        cout << "Enter phone no.:\n";
        cin >> phone_no;
        cin.ignore();
        cout << "Enter address:\n";
        getline(cin, address);
    }
};

class inmate : public person
{
protected:
    string spouse_name, father_name, mother_name, guardian_name;
    int id;

    void get_family_details()
    {
        char q;
        cout << "Is convict orphan? [y/n]\n";
        cin >> q;
        if (q == 'n')
        { // yes is 1
            cout << "Enter Father's name:\n";
            cin >> father_name;
            cout << "Enter Mother's name:\n";
            cin >> mother_name;
            guardian_name = mother_name;
        }
        else
        {
            father_name = "***Orphan***";
            mother_name = "***Orphan***";
            cout << "Enter the name of the gaurdian:\n";
            cin >> guardian_name;
        }
        char w;
        cout << "Is the convict married? [y/n]\n";
        cin >> w;
        if (w == 'y')
        {
            cout << "Enter Spouse name:\n";
            cin >> spouse_name;
        }
        else
        {
            spouse_name = "***unmarried**";
        }
    }

public:
    string date;      // the day he is entering the jail
    int serving_time; // time he has to spen in jail after the sentance
    int height;       // height of hte inmate
    string crime_grade;
    string crime_commited;
    string mental_grade;
    string mental_state;
    int cell_no;

    inmate()
    {
        cout << "Enter id:";
        cin >> id;
        cin.ignore();
        cout << "Enter the Inmate's joining date\n";
        getline(cin, date);

        cout << "Enter the height of the convict:\n";
        cin >> height;
        get_family_details();

        cout << "Enter the inmate crime grade:\n";
        cin >> crime_grade;
        cout << "Enter crime(s) commited:";
        cin >> crime_commited;
        cout << "Enter serving time:\n";
        cin >> serving_time;

        cout << "Enter the cell no.:";
        cin >> cell_no;
        upload_details(connected);
    }
    int upload_details(MYSQL* con)
    {
        stringstream a;
        string r;
        r = 'no';
        a << "INSERT INTO inmate_information(id, name, age, gender, adress, phonenumber, entrydate, servingtime, fathername, mothername, spousename, guardianname, crimegrade, crime, cellnumber, released) VALUES (" << id << ", '" << name << "', " << age << ", '" << gender << "', '" << address << "'," << phone_no << ",'" << date << "', " << serving_time << ", '" << father_name << "', '" << mother_name << "', '" << spouse_name << "', '" << guardian_name << "', '" << crime_grade << "', '" << crime_commited << "', " << cell_no << ", '"<<r<<"')";

        string query = a.str();

        const char* q = query.c_str();

        int qstate = mysql_query(con, q);

        if (qstate == 0)
        {
            cout << "Record Inserted..." << endl;
        }
        else
        {
            cout << "Failed" << endl;
        }
        return 0;
    }
    
};

class officer : public person
{
protected:
    int id;
    string shift;
    string date;

public:
    officer()
    {
        cout << "Enter ID:\n";
        cin >> id;
        cin.ignore();
        cout << "Enter the officer's joining date (DD MM YYYY):\n";
        getline(cin, date);
        cout << "Enter working shift:\n";
        cin >> shift;
        insertoff(connected);
    }

    int insertoff(MYSQL* con)
    {
        stringstream a,b;
        a << "INSERT INTO officer(id, name, age, gender, phonenumber, address, date, shift)VALUES (" << id << ", '" << name << "', " << age << ", '" << gender << "'," << phone_no << ",'" << address << "','" << date << "', '" << shift << "')";

        string query = a.str();

        const char* q = query.c_str();

        int qstate = mysql_query(con, q);

        b << "INSERT INTO offlogin(username, password) VALUES (" << id << ", 'password')";
        string query1 = b.str();

        const char* p = query1.c_str();

        int pstate = mysql_query(con, p);


        if (qstate == 0 && pstate==0)
        {
            cout << "Record Inserted..." << endl;
        }
        else
        {
            cout << "Failed" << endl;
        }
        return 0;
    }
};
class visitor : public person
{
protected:
    string inmate_name;
    string relation;
    string vis_date;
    string vis_time;
    string time_stayed;

public:
    visitor()
    {
        cout << "Enter the name of inmate visiting:\n";
        cin >> inmate_name;
        cout << "Enter the relation to the inmate:\n";
        cin >> relation;
        cin.ignore();
        cout << "Enter visiting date:\n";
        getline(cin, vis_date);
        cin.ignore();
        cout << "Enter the visiting time.\n";
        getline(cin, vis_time);
        insertvisitor(connected);
    }
    int insertvisitor(MYSQL* con)
    {
        stringstream a;
        a << "INSERT INTO visitor_details(name, age, gender, phoneno, adress, inmatename, relation, date, time )VALUES ('" << name << "', " << age << ", '" << gender << "'," << phone_no << ", '" << address << "','" << inmate_name << "', '" << relation << "','" << vis_date << "','" << vis_time << "')";

        string query = a.str();

        const char* q = query.c_str();

        qstate = mysql_query(con, q);

        if (qstate == 0)
        {
            cout << "Record Inserted..." << endl;
        }
        else
        {
            cout << "Failed" << endl;
        }
        return 0;
    }
};

class prison
{
public:
    string password;

public:
    int login(MYSQL* con, int n)
    {
        if (n == 1)
        {
            string username;
            string password;
           






          
            cout << " " << "\n\n\t\t\t============WELCOME TO LOGIN PAGE===============\n\n";
            cout << " " << "Enter Login Credentials\n";
            cout << "Enter Username:\n ";
            cin >> username; cout << endl;
            cout << "Enter Password:\n ";
            cin >> password;


            MYSQL_RES* res;
            MYSQL_ROW  row;
            stringstream a;
            a << "SELECT * FROM login WHERE username = '" << username << "' ";
            string b = a.str();
            const char* query = b.c_str();
            if (!(mysql_query(con, query))) {

                res = mysql_store_result(con);
                while (row = mysql_fetch_row(res))
                {

                    if (password == row[1]) {

                        cout << "\n\n\n\n\t\t\t==================WELCOME========================\n\n\n" << endl;
                        return 100;
                       


                    }
                    else {
                        cout << "Credentials are wrong" << endl;

                    }
                }
            }

        }
        else if(n==2)
        {
            string id;
            string password;
            






            
            cout << " " << "\t\t\t==========WELCOME TO LOGIN PAGE===============\n\n";
            cout << "Enter Login Credentials\n\n\n";
            cout << "Enter id: ";
            cin >> id; cout << endl;
            cout << "Enter Password: ";
            cin >> password;


            MYSQL_RES* res;
            MYSQL_ROW  row;
            stringstream a;
            a << "SELECT * FROM offlogin WHERE username = '" << id << "' ";
            string b = a.str();
            const char* query = b.c_str();
            if (!(mysql_query(con, query))) {

                res = mysql_store_result(con);
                while (row = mysql_fetch_row(res))
                {

                    if (password == row[1]) {

                        cout << "\n\n\n\n\t\t\t==================WELCOME========================\n\n\n" << endl;
                        return 100;
                        


                    }
                    else {
                        cout << "Credentials are wrong" << endl;

                    }
                }
            }

        }
        else
        {
            cout << "invalid option";
        }
        
    }

public:
    void update(MYSQL* con)
    {
        int id, age, phone_no, serving_time, cell_no;
        string name, gender, father_name, mother_name, guardian_name, spouse_name, address, crime_commited, crime_grade;

        MYSQL_ROW row;
        stringstream ss, a;
        MYSQL_RES* res;
        string iquery;

        string table;
        table = "inmate_information";

        cout << "Enter ID:" << endl;
        cin >> id;

        a << "SELECT * FROM " << table << " WHERE Id = '" << id << "' ";
        string b = a.str();
        const char* query = b.c_str();

        if (!(mysql_query(con, query)))
        {
            res = mysql_store_result(con);
            row = mysql_fetch_row(res);
            if (row != 0)
            {
                cout << "Enter name:" << endl;
                cin >> name;
                cout << "Enter gender:" << endl;
                cin >> gender;
                cout << "Enter age:" << endl;
                cin >> age;
                cout << "Enter address:" << endl;
                cin >> address;
                cout << "Enter phone no.:" << endl;
                cin >> phone_no;
                cout << "Enter serving time:" << endl;
                cin >> serving_time;
                cout << "Enter Father's name:" << endl;
                cin >> father_name;
                cout << "Enter Mother's name:" << endl;
                cin >> mother_name;
                cout << "Enter Spouse name:" << endl;
                cin >> spouse_name;
                cout << "Enter Guardian's name:" << endl;
                cin >> guardian_name;
                cout << "enter crime grade" << endl;
                cin >> crime_grade;
                cout << "Enter the crime committed:" << endl;
                cin >> crime_commited;
                cout << "Enter allotted cell no.:" << endl;
                cin >> cell_no;

                ss << "UPDATE " << table << "  SET name = '" << name << "', gender = '" << gender << "', age = " << age << ", adress = '" << address << "', phonenumber = " << phone_no << ", servingtime = " << serving_time << ", fathername = '" << father_name << "', mothername = '" << mother_name << "',spousename = '" << spouse_name << "', guardianname = '" << guardian_name << "', crimegrade= '" << crime_grade << "', cellnumber = " << cell_no << " WHERE id= " << id << " ";

                string query = ss.str();
                const char* q = query.c_str();

                qstate = mysql_query(con, q);
            }
        }
        if (qstate == 0)
        {
            cout << "Details successfully updated" << endl;
        }
        else
        {
            cout << "Failed" << endl;
        }
    }
    void update_officer(MYSQL* con)
    {
        int id, age, phone_no, serving_time, cell_no;
        string date, shift, name, gender, father_name, mother_name, guardian_name, spouse_name, address, crime_commited, crime_grade;

        MYSQL_ROW row;
        stringstream ss, a;
        MYSQL_RES* res;
        string iquery;

        string table;
        table = "officer";

        cout << "Enter the id of the officer" << endl;
        cin >> id;

        a << "SELECT * FROM " << table << " WHERE Id = " << id << " ";
        string b = a.str();
        const char* query = b.c_str();

        if (!(mysql_query(con, query)))
        {
            res = mysql_store_result(con);
            row = mysql_fetch_row(res);
            if (row != 0)
            {
                cout << "enter name" << endl;
                cin >> name;
                cout << "enter gender" << endl;
                cin >> gender;
                cout << "enter age" << endl;
                cin >> age;
                cin.ignore();
                cout << "enter address" << endl;
                // cin >> address;
                getline(cin, address);
                cout << "enter phone no." << endl;
                cin >> phone_no;
                cout << "enter shift" << endl;
                cin >> shift;
                cin.ignore();
                cout << "enter date" << endl;
                getline(cin, date);

                ss << "UPDATE " << table << "  SET name = '" << name << "', gender = '" << gender << "', age = " << age << ", address = '" << address << "', phonenumber = " << phone_no << ", shift = '" << shift << "', date = '" << date << "'  WHERE id = " << id << " ";

                string query = ss.str();
                const char* q = query.c_str();

                qstate = mysql_query(con, q);
            }
        }
        if (qstate == 0)
        {
            cout << "Details successfully updated" << endl;
        }
        else
        {
            cout << "Failed" << endl;
        }
    }
    void alldetails(MYSQL* con)
    {
        string table;
        stringstream ss;
        MYSQL_RES* res;
        MYSQL_ROW row;

        table = "inmate_information";
        // ss << "SELECT * FROM " << table << " WHERE id= " << id << " ";
        ss << "SELECT * FROM " << table << " WHERE released = 'o'";
        string query = ss.str();
       

        const char* q = query.c_str();

        if (!(mysql_query(con, q)))
        {
           
            res = mysql_store_result(con);
            while (row = mysql_fetch_row(res))
            {
                cout << "\n\n  Name -> " << row[1];
                cout << "\n\n  Age -> " << row[2];
                cout << "\n\n  Gender -> " << row[3];
                cout << "\n\n  Address -> " << row[4];
                cout << "\n\n  Phone no.-> " << row[5];
                cout << "\n\n  date of joining-> " << row[6];
                cout << "\n\n  servingtime -> " << row[7];
                cout << "\n\n  Father name -> " << row[8];
                cout << "\n\n  Mother name -> " << row[9];
                cout << "\n\n  Spouse name -> " << row[10];
                cout << "\n\n  Guardian name -> " << row[11];
                cout << "\n\n  Crime grade -> " << row[12];
                cout << "\n\n  Crime -> " << row[13];
                cout << "\n\n  Cell no. -> " << row[14];
                cout << "\n";
            }
        }
    }

    void off_all_details(MYSQL* con)
    {

        string table;
        stringstream ss;
        MYSQL_RES* res;
        MYSQL_ROW row;

        table = "officer";
        // ss << "SELECT * FROM " << table << " WHERE id= " << id << " ";
        ss << "SELECT * FROM " << table << "";
        string query = ss.str();
        cout << query << endl;

        const char* q = query.c_str();

        if (!(mysql_query(con, q)))
        {
            cout << "enteer" << endl;
            res = mysql_store_result(con);
            while (row = mysql_fetch_row(res))
            {
                cout << "\n\n  Name -> " << row[1];
                cout << "\n\n  Age -> " << row[2];
                cout << "\n\n  Gender -> " << row[3];
                cout << "\n\n  Address -> " << row[5];
                cout << "\n\n  Phone no.-> " << row[4];
                cout << "\n\n  date of joining-> " << row[6];
                cout << "\n\n  working shift -> " << row[7];
                cout << "\n";
            }
        }
    }
    void search_officer(MYSQL* con)
    {
        int id;
        string table;
        stringstream ss;
        MYSQL_RES* res;
        MYSQL_ROW row;
        cout << "Enter id" << endl;
        cin >> id;
        table = "officer";
        ss << "SELECT * FROM " << table << " WHERE id= " << id << " ";

        string query = ss.str();

        const char* q = query.c_str();

        if (!(mysql_query(con, q)))
        {
            res = mysql_store_result(con);
            while (row = mysql_fetch_row(res))
            {
                cout << "\n\n  Name -> " << row[1];
                cout << "\n\n  Age -> " << row[2];
                cout << "\n\n  Gender -> " << row[3];
                cout << "\n\n  Address -> " << row[5];
                cout << "\n\n  Phone no.-> " << row[4];
                cout << "\n\n  date of joining-> " << row[6];
                cout << "\n\n  working shift -> " << row[7];
                cout << "\n";
            }
        }
        if (qstate == 0)
        {
            cout << "\nsuccess\n"
                << endl;
        }
        else
        {
            cout << "\nrecord not found\n"
                << endl;
        }
    }
    void search_inmate(MYSQL* con)
    {

        int id;
        string table;
        stringstream ss;
        MYSQL_RES* res;
        MYSQL_ROW row;

        cout << "Enter id" << endl;
        cin >> id;

        table = "inmate_information";

        ss << "SELECT * FROM " << table << " WHERE id= " << id << " ";

        string query = ss.str();
        const char* q = query.c_str();

        if (!(mysql_query(con, q)))
        {
            res = mysql_store_result(con);

            while (row = mysql_fetch_row(res))

            {
                cout << "\n\n  Name -> " << row[1];
                cout << "\n\n  Age -> " << row[2];
                cout << "\n\n  Gender -> " << row[3];
                cout << "\n\n  Address -> " << row[4];
                cout << "\n\n  Phone no.-> " << row[5];
                cout << "\n\n  date of joining-> " << row[6];
                cout << "\n\n  servingtime -> " << row[7];
                cout << "\n\n  Father name -> " << row[8];
                cout << "\n\n  Mother name -> " << row[9];
                cout << "\n\n  Spouse name -> " << row[10];
                cout << "\n\n  Guardian name -> " << row[11];
                cout << "\n\n  Crime grade -> " << row[12];
                cout << "\n\n  Crime -> " << row[13];
                cout << "\n\n  Cell no. -> " << row[14];
                cout << "\n";
            }
        }
        else
        {

            cout << "\n\n *** Query Failed ****";
        }
    }
    void search_visitor(MYSQL* con)
    {
        string name;
        string table;
        stringstream ss;
        MYSQL_RES* res;
        MYSQL_ROW row;

        cout << "Enter name" << endl;
        cin >> name;

        table = "visitor_details";

        ss << "SELECT * FROM " << table << " WHERE name= '" << name << "' ";

        string query = ss.str();
        const char* q = query.c_str();

        if (!(mysql_query(con, q)))
        {
            res = mysql_store_result(con);

            while (row = mysql_fetch_row(res))

            {
                cout << "\n\n  Name -> " << row[0];
                cout << "\n\n  Age -> " << row[1];
                cout << "\n\n  Gender -> " << row[2];
                cout << "\n\n  Phone no -> " << row[3];
                cout << "\n\n  Address -> " << row[4];
                cout << "\n\n  Name of the inmate visited-> " << row[5];
                cout << "\n\n  Realation -> " << row[6];
                cout << "\n\n  Visiting date -> " << row[7];
                cout << "\n\n  Visiting time -> " << row[8];
                cout << "\n";
            }
        }
        else
        {

            cout << "\n\n *** Query Failed ****";
        }
    }
    void all_visitor_details(MYSQL* con)
    {

        string table;
        stringstream ss;
        MYSQL_RES* res;
        MYSQL_ROW row;

        table = "visitor_details";

        ss << "SELECT * FROM " << table << "";

        string query = ss.str();
        const char* q = query.c_str();

        if (!(mysql_query(con, q)))
        {
            res = mysql_store_result(con);

            while (row = mysql_fetch_row(res))

            {
                cout << "\n\n  Name -> " << row[0];
                cout << "\n\n  Age -> " << row[1];
                cout << "\n\n  Gender -> " << row[2];
                cout << "\n\n  Phone no -> " << row[3];
                cout << "\n\n  Address -> " << row[4];
                cout << "\n\n  Name of the inmate visited-> " << row[5];
                cout << "\n\n  Realation -> " << row[6];
                cout << "\n\n  Visiting date -> " << row[7];
                cout << "\n\n  Visiting time -> " << row[8];
                cout << "\n";
            }
        }
        else
        {

            cout << "\n\n *** Query Failed ****";
        }
    }
    void release_inmate(MYSQL* con)
    {
        int id;
           string r ;       
           MYSQL_ROW row;
           stringstream ss, a;
           MYSQL_RES* res;
           string iquery;

           string table;
           table = "inmate_information";

           cout << "Enter id" << endl;
           cin >> id;

           a << "SELECT * FROM " << table << " WHERE id = " << id << " ";
           string b = a.str();
           const char* query = b.c_str();

           if (!(mysql_query(con, query)))
           {
               res = mysql_store_result(con);
               row = mysql_fetch_row(res);
               if (row != 0)
               {
                   

                   cout << "do you want to release the inmate(yes/no)\n";
                   cin >> r;


                   ss << "UPDATE " << table << "  SET released  = '" << r << "' WHERE id = " << id << " ";

                   string query = ss.str();
                   const char* q = query.c_str();

                   qstate = mysql_query(con, q);
               }
           }
           if (qstate == 0)
           {
               cout << "Inmate successfully Released" << endl;
           }
           else
           {
               cout << "Failed" << endl;
           }
          
       
    }
    void veiw_releases(MYSQL* con)
    {
        string table, released;
        stringstream ss;
        MYSQL_RES* res;
        MYSQL_ROW row;

        table = "inmate_information";
         ss << "SELECT * FROM " << table << " WHERE released= 'yes' ";
        
        string query = ss.str();
        cout << query << endl;

        const char* q = query.c_str();

        if (!(mysql_query(con, q)))
        {
            cout << "enteer" << endl;
            res = mysql_store_result(con);
            while (row = mysql_fetch_row(res))
            {
                cout << "\n\n  Name -> " << row[1];
                cout << "\n\n  Age -> " << row[2];
                cout << "\n\n  Gender -> " << row[3];
                cout << "\n\n  Address -> " << row[4];
                cout << "\n\n  Phone no.-> " << row[5];
                cout << "\n\n  date of joining-> " << row[6];
                cout << "\n\n  servingtime -> " << row[7];
                cout << "\n\n  Father name -> " << row[8];
                cout << "\n\n  Mother name -> " << row[9];
                cout << "\n\n  Spouse name -> " << row[10];
                cout << "\n\n  Guardian name -> " << row[11];
                cout << "\n\n  Crime grade -> " << row[12];
                cout << "\n\n  Crime -> " << row[13];
                cout << "\n\n  Cell no. -> " << row[14];
                cout << "\n";
            }
        }
    }
    
};

int main()
{
    prison in;
    
    
    //loading animation
    int count = 0;
    cout << "\n\n\n\n\n\n\n\n\n\n";
    cout << "\t\t";
    cout << "\t\t\t\t\tLoading. ";
    for (count; count < 12; ++count)
    {
        system("color 0B");
        cout << ". ";
        for (int j = 0; j <= 100000000.7; j++)
            ;
    }

    system("cls");
    system("color 0B");

    //introduction
    cout << "\n\n\n\n\n\n\n\n";
    cout << "\n\t\t\t\t\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\n";
    cout << "\t\t\t\t\xdb                                                      \xdb\n";
    cout << "\t\t\t\t\xdb ==================================================   \xdb\n";
    cout << "\t\t\t\t\xdb         WELCOME TO PRISON MANAGEMENT SYSTEM          \xdb\n";
    cout << "\t\t\t\t\xdb ==================================================   \xdb\n";
    cout << "\t\t\t\t\xdb                                                      \xdb\n";
    cout << "\t\t\t\t\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\n\n\n";
    getchar();
    system("cls");

    int s = 0;
    

    con = mysql_init(0);
    connected = mysql_real_connect(con, "localhost", "root", "", "prison", 3306, NULL, 0);
    if (connected)
    {
        cout << "connection successfull" << endl;
        s++;
        system("cls");
    }
    else
    {
        cout << "connection failed" << endl;
    }

    prison off;
    int n;
   
    cout << "1.If you are the Warden. Enter ->'1'\n";
    cout << "2.If you are the Officer. Enter ->'2'\n";
    
    cout << "Enter here : \n";
    cin >> n;
    system("pause");
    system("cls");
    int entry = 0;

    entry = off.login(connected,n);
    system("pause");
    system("cls");
    

    if (entry == 100)
    {
        
        if (n == 1 || n == 2)
        {
            int swth_whle_1 = 0;
            while (swth_whle_1 != 5)
            {
                cout << "1.Inmate options\n";
                cout << "2.Visitor options\n";
                if (n == 1)
                {
                    cout << "3.Officer options\n";
                    cout << "4.Warden and presonel options\n";
                    cout << "5.Exit\n";
                    cout << "enter here\n";
                }
                else
                {
                    cout << "3.Edit password\n";
                    cout << "4.Exit\n";
                    cout << "enter here\n";
                }
                cin >> swth_whle_1;
                system("cls");
                switch (swth_whle_1)
                {
                case 1:
                {
                    cout << "1.Add inmate\n";
                    cout << "2.Search inmate\n";
                    cout << "3.All inmate details\n";
                    cout << "4.Edit inmate details\n";
                    if (n == 1)
                    {
                        cout << "5.Release inmate\n";
                    }
                    else
                    {
                        cout << "5.Veiw released inmate details\n";
                    }
                        cout << "6.exit\n";

                        
                    

                    
                    int s;
                    cin >> s;
                    system("cls");

                    switch (s)
                    {
                    case 1:
                    {
                        inmate x;
                        
                        break;
                    }
                    case 2:
                    {
                        in.search_inmate(connected);
                        break;
                    }
                    case 3:
                    {
                        in.alldetails(connected);
                        break;
                    }
                    case 4:
                    {
                        in.update(connected);
                        break;
                    }
                    case 5:
                    {
                        
                        if (n == 1)
                        {
                            cout << "1.Release inmate\n";
                            cout << "2.Veiw released inmate details\n";
                            int c;
                            cin >> c;
                            
                            switch (c)
                            {
                            case 1:
                            {
                                in.release_inmate(connected);
                                break;
                            }
                            case 2:
                            {
                                in.veiw_releases(connected);
                                break;

                            }
                            case 3:
                            {
                                break;
                            }
                            }
                        }
                        else
                        {
                            in.veiw_releases(connected);
                            
                        }
                        break;
                            
                       
                    }
                  
                  
                    default:
                    {
                        if (s != 6)
                        {
                            cout << "invalid option.\n";
                        }
                    }
                    }
                    system("pause");
                    system("cls");

                    break;
                }
                case 2:
                {
                    cout << "1.Add visitor\n";
                    cout << "2.Search visitor\n";
                    cout << "3.All visitor details\n";
                    cout << "4.Exit\n";
                    int s1;
                    cin >> s1;
                    system("cls");
                    switch (s1)
                    {
                    case 1:
                    {
                        visitor v;
                        break;
                    }
                    case 2:
                    {
                        in.search_visitor(connected);
                        break;
                    }
                    case 3:
                    {
                        in.all_visitor_details(connected);
                        break;
                    }
                    default:
                    {
                        if (s1 != 4)
                        {
                            cout << "invalid option.\n";
                        }
                    }
                    }
                    system("pause");
                    system("cls");
                    break;
                }
                case 3:
                {
                    if (n == 1) // Warden options
                    {
                        cout << "1.Add officer\n";
                        cout << "2.Search officer\n";
                        cout << "3.All officer details\n";
                        cout << "4.Edit officer\n";
                        cout << "5.Exit\n";
                        int s2;
                        cin >> s2;
                        system("cls");

                        switch (s2)
                        {
                        case 1:
                        {
                            officer o;
                            break;
                        }
                        case 2:
                        {
                            in.search_officer(connected);
                            break;
                        }
                        case 3:
                        {
                            in.off_all_details(connected);
                            break;
                        }
                        case 4:
                        {
                            in.update_officer(connected);
                            break;
                        }
                        default:
                        {
                            if (s2 != 5)
                            {
                                cout << "invalid option.\n";
                            }
                        }
                        }
                    }
                    else
                    {
                        string username, password;
                        MYSQL_ROW row;
                        stringstream ss, a;
                        MYSQL_RES* res;
                        string iquery;
                        string table;
                        table = "officer_login";
                        cout << "Enter your username" << endl;
                        cin >> username;
                        a << "SELECT * FROM " << table << " WHERE username = '" << username << "' ";
                        string b = a.str();
                        const char* query = b.c_str();

                        if (!(mysql_query(con, query)))
                        {
                            res = mysql_store_result(con);
                            row = mysql_fetch_row(res);
                            if (row != 0)
                            {
                                cout << "enter new password" << endl;
                                cin >> password;

                                ss << "UPDATE " << table << "  SET password = '" << password << "' WHERE username = '" << username << "' ";

                                string query = ss.str();
                                const char* q = query.c_str();

                                qstate = mysql_query(con, q);
                            }
                        }
                        if (qstate == 0)
                        {
                            cout << "\nsuccess\n"
                                << endl;
                        }
                        else
                        {
                            cout << "\nFailed\n"
                                << endl;
                        }
                    }
                    system("pause");
                    system("cls");
                    break;
                }
                case 4:
                {
                    if (n == 2)
                    {
                        // officer exit
                        swth_whle_1 = 5;
                    }
                    else
                    {
                        int v;
                        cout << "1.Edit login details\n";
                        cout << "2.veiw your profile\n";
                        cout << "3.Edit your profile\n";
                        cin >> v;
                        system("cls");
                        if (v == 1)
                        {
                            string username, password;
                            MYSQL_ROW row;
                            stringstream ss, a;
                            MYSQL_RES* res;
                            string iquery;

                            string table;
                            table = "login";

                            cout << "Enter your username" << endl;
                            cin >> username;

                            a << "SELECT * FROM " << table << " WHERE username = '" << username << "' ";
                            string b = a.str();
                            const char* query = b.c_str();

                            if (!(mysql_query(con, query)))
                            {
                                res = mysql_store_result(con);
                                row = mysql_fetch_row(res);
                                if (row != 0)
                                {
                                    cout << "enter new password" << endl;
                                    cin >> password;

                                    ss << "UPDATE " << table << "  SET password = '" << password << "' WHERE username = '" << username << "' ";

                                    string query = ss.str();
                                    const char* q = query.c_str();

                                    qstate = mysql_query(con, q);
                                }
                            }
                            if (qstate == 0)
                            {
                                cout << "\nsuccess\n"
                                    << endl;
                            }
                            else
                            {
                                cout << "\nFailed\n"
                                    << endl;
                            }
                            system("pause");
                            system("cls");
                            break;
                        }
                        else
                        {
                            if (v == 2)
                            {
                                string table;
                                stringstream ss;
                                MYSQL_RES* res;
                                MYSQL_ROW row;

                                table = "warden_details";

                                ss << "SELECT * FROM " << table << "";
                                string query = ss.str();

                                const char* q = query.c_str();

                                if (!(mysql_query(con, q)))
                                {

                                    res = mysql_store_result(con);
                                    while (row = mysql_fetch_row(res))
                                    {
                                        cout << "\n\n  Username -> " << row[0];
                                        cout << "\n\n  Name -> " << row[1];
                                        cout << "\n\n  Age -> " << row[2];
                                        cout << "\n\n  Address -> " << row[4];
                                        cout << "\n\n  phone no. -> " << row[3];

                                        cout << "\n\n  Joining Date -> " << row[5];
                                        cout << "\n\n  Qualifications-> " << row[6];

                                        cout << "\n";
                                    }
                                }
                                else
                                {
                                    cout << "\nfailed\n";
                                }
                                system("pause");
                                system("cls");
                                break;
                            }
                            else
                            {
                                string username, address, name, study, date;
                                int phone_no, age;
                                MYSQL_ROW row;
                                stringstream ss, a;
                                MYSQL_RES* res;
                                string iquery;

                                string table;
                                table = "warden_details";

                                cout << "Enter username" << endl;
                                cin >> username;

                                a << "SELECT * FROM " << table << " WHERE username = '" << username << "' ";
                                string b = a.str();
                                const char* query = b.c_str();

                                if (!(mysql_query(con, query)))
                                {
                                    res = mysql_store_result(con);
                                    row = mysql_fetch_row(res);
                                    if (row != 0)
                                    {
                                        cout << "enter name" << endl;
                                        cin >> name;

                                        cout << "enter age" << endl;
                                        cin >> age;
                                        cin.ignore();
                                        cout << "enter phone no." << endl;
                                        cin >> phone_no;
                                        cin.ignore();
                                        cout << "enter address" << endl;
                                        // cin >> address;
                                        getline(cin, address);
                                        cin.ignore();
                                        cout << "enter qualifications" << endl;
                                        getline(cin, study);
                                        cin.ignore();
                                        cout << "enter date" << endl;
                                        getline(cin, date);

                                        ss << "UPDATE " << table << "  SET name = '" << name << "', age = " << age << ", address = '" << address << "', phoneno = " << phone_no << ", date = '" << date << "', study= '" << study << "'  WHERE username = '" << username << "' ";

                                        string query = ss.str();
                                        const char* q = query.c_str();

                                        qstate = mysql_query(con, q);
                                    }
                                }
                                if (qstate == 0)
                                {
                                    cout << "\ndetails successfully updated\n"
                                        << endl;
                                }
                                else
                                {
                                    cout << "\nFailed\n"
                                        << endl;
                                }
                                system("pause");
                                system("cls");
                                break;
                            }
                        }
                    }
                    system("pause");
                    system("cls");
                    break;
                }
                default:
                {
                    if (swth_whle_1 != 5)
                    {
                        cout << "invalid option.\n";
                    }
                }
                }
            }
        }
    }
    else
    {
        cout << "\nEntry denied\n";
    }
}