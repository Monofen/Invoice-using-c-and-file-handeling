#include <iostream>
#include <windows.h>
#include <conio.h>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;

class color_set
{
public:
    void color(int color)
    {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
    }

    void gotoxy(int x, int y)
    {
        COORD c;
        c.X = x;
        c.Y = y;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
    }
};

class screenClear
{
    public:
    void clear()
    {
        system("cls");
    }
};

class createInvoice : virtual public color_set, virtual public screenClear
{
private:
    const int first = 20;
    const int second = 14;
    const int third = 10;
    const int fourth= 10;
public:
    int i = 0, found = 0 , b , run , equ;
    int item_quantity , item_price , input_quantity , bill_no , new_num , total , squa;
    int change = 7;
    int Set[5] = {7, 7, 7, 7, 7};
    int def[2] = {7,7};
    int counter = 1;
    char key;
    string input_user , input_password , username , password , fname , lname , set_user , set_fname , set_lname , phnumber , input_phnumber , item_num , input_num , mem_name , test , sname , snum , spri;
    int consoleWidth = 100;
    int menuWidth = 40; // Width of the menu
    int padding = (consoleWidth - menuWidth) / 2; // Calculate left padding

    void displayMenu()
    {
        counter = 1;
        clear();
        color_set::color(def[0]);
        cout << setw(padding) << "" << setw(menuWidth) << setfill('-') << "" << setfill(' ') << endl;
        color_set::color(def[0]);
        cout << setw(padding) << "" << "\t\t\tMenu \tWelcome, "<<set_user<<" "<<set_lname << endl;
        color_set::color(def[0]);
        cout << setw(padding) << "" << setw(menuWidth) << setfill('-') << "" << setfill(' ') << endl;
        while (1)
        {
            color_set::gotoxy(padding + 2, 4);
            color_set::color(Set[0]);
            cout << "1. Create Invoice" << endl;

            color_set::gotoxy(padding + 2, 5);
            color_set::color(Set[1]);
            cout << "2. Edit Costumer Membership" << endl;

            color_set::gotoxy(padding + 2, 6);
            color_set::color(Set[2]);
            cout << "3. Edit Shoplist / Edit Moderators" << endl;

            color_set::gotoxy(padding + 2, 7);
            color_set::color(Set[3]);
            cout << "4. Exit" << endl;

            color_set::color(def[0]);
            cout << setw(padding) << "" << setw(menuWidth) << setfill('-') << "" << setfill(' ') << endl;

            key = _getch();

            if (key == 72 && (counter >= 2 && counter <= 4))
                counter--;
            if (key == 80 && (counter >= 1 && counter <= 3))
                counter++;
            if (key == '\r')
            {
                switch (counter)
                {
                case 1:
                    Set[0] = 7;
                    clear();
                    invoice();
                    break;
                case 2:
                    Set[1] = 7;
                    clear();
                    membershipEdit();
                    break;
                case 3:
                    clear();
                    Set[2] = 7;
                    EditMenu();
                    break;
                case 4:
                    Set[3] = 7;
                    clear();
                    displayLogin();

                    break;
                }
            }
            Set[0] = 7;
            Set[1] = 7;
            Set[2] = 7;
            Set[3] = 7;

            if (counter == 1)
                Set[0] = 12;
            if (counter == 2)
                Set[1] = 12;
            if (counter == 3)
                Set[2] = 12;
            if (counter == 4)
                Set[3] = 12;
        }
    }

    void invoice()
    {
        color_set::color(def[0]);
        cout << setw(padding) << "" << setw(menuWidth+18) << setfill('-') << "" << setfill(' ') << endl;
        color_set::color(def[0]);
        cout << setw(padding) << "" << "\t\t\t\tSelect Item" << endl;
        color_set::color(def[0]);
        cout << setw(padding) << "" << setw(menuWidth+18) << setfill('-') << "" << setfill(' ') << endl;

        i = 5;
        ifstream display("item_data.txt", ios::binary | ios::in);
        color_set::gotoxy(padding+2, 4);
        cout << "Item name \t Quantity \t Price \t Item number" << endl;

        while (display >> fname >> item_num >> item_quantity >> item_price)
        {
            color_set::gotoxy(padding + 2, i);
            color_set::color(change);
            cout << setw(first) << left << fname << setw(second) << item_quantity << setw(third) << item_price << setw(fourth) << item_num << endl;
            i++;
        }
        display.close();
        color_set::color(def[0]);
        cout << setw(padding) << "" << setw(menuWidth+18) << setfill('-') << "" << setfill(' ') << endl;
        cout<<"\n Enter the item number: ";
        cin>>input_num;
        ifstream check("item_data.txt",ios::binary|ios::in);
        found=0;
        while(check>>fname>>item_num>>item_quantity>>item_price)
        {
            if(input_num==item_num)
            {
                check.close();
                cout<<"\nEnter the number of item:";
                cin>>input_quantity;
                if(input_quantity>item_quantity)
                {
                    cout<<"Invalid quantity!!!"<<endl;
                    cout<<"Press any key to continue"<<endl;
                    getch();
                    clear();
                    invoice();
                }
                else
                {
                    cout<<"Would you like to add more item?"<<endl;
                    cout<<"Press enter to continue."<<endl;
                    cout<<"Else press any key."<<endl;
                    key=_getch();
                    if(key=='\r')
                    {
                        ofstream check_out("bill.txt",ios::app|ios::binary|ios::out);
                        check_out<<fname<<" "<<item_num<<" "<<input_quantity<<" "<<item_price<<endl;
                        check_out.close();
                        clear();
                        invoice();
                    }
                    else
                    {
                        ofstream check_out("bill.txt",ios::app|ios::binary|ios::out);
                        check_out<<fname<<" "<<item_num<<" "<<input_quantity<<" "<<item_price<<endl;
                        check_out.close();
                        clear();

                        confirmation();
                    }
                }
            }
            else
            {
                found=1;
            }
        }
        if(found==1)
        {
            check.close();
            cout<<"We do not have that item!!!"<<endl;
            cout<<"Press any key to continue."<<endl;
            getch();
            clear();
            invoice();
        }
    }

    void confirmation()
    {
        counter =1;
        color_set::color(def[0]);
        cout << setw(padding) << "" << setw(menuWidth) << setfill('-') << "" << setfill(' ') << endl;
        color_set::color(def[0]);
        cout << setw(padding) << "" << "\t\t\tConfirmation" <<endl;
        color_set::color(def[0]);
        cout << setw(padding) << "" << setw(menuWidth) << setfill('-') << "" << setfill(' ') << endl;
        ifstream display("bill.txt",ios::binary|ios::in);
        color_set::gotoxy(padding, 4);
        cout << "Item name \t Quantity \t Price ";
        i=5;
        while (display >> fname >> item_num >> item_quantity >> item_price)
        {
            color_set::gotoxy(padding , i);
            color_set::color(change);
            cout << setw(first+2) << left << fname << setw(second) << item_quantity << setw(third) << item_price << endl;
            i++;
        }
        display.close();
        color_set::color(def[0]);
        cout << setw(padding) << "" << setw(menuWidth) << setfill('-') << "" << setfill(' ') << endl;
        while (1)
        {
            color_set::gotoxy(padding + 2, i+1);
            color_set::color(Set[0]);
            cout << "1. Confirm" << endl;

            color_set::gotoxy(padding + 2, i+2);
            color_set::color(Set[1]);
            cout << "2. Cancel" << endl;

            color_set::color(def[0]);
            cout << setw(padding) << "" << setw(menuWidth) << setfill('-') << "" << setfill(' ') << endl;

            key = _getch();
            if (key == 72 && (counter==2))
            {
                counter--;
            }
            if (key == 80 && (counter ==1))
            {
                counter++;
            }
            if (key == '\r')
            {
                switch (counter)
                {
                case 1:
                    Set[0] = 7;
                    clear();
                    checkMembership();
                    break;

                case 2:
                    Set[1] = 7;
                    remove ("bill.txt");
                    clear();
                    displayMenu();
                    break;

                default:
                    cout << "Invalid" << endl;
                    continue;
                }
            }
            Set[0] = 7;
            Set[1] = 7;

            if (counter == 1)
                Set[0] = 12;

            if (counter == 2)
                Set[1] = 12;
        }
    }

    void checkMembership()
    {
        color_set::color(def[0]);
        cout << setw(padding) << "" << setw(menuWidth) << setfill('-') << "" << setfill(' ') << endl;
        color_set::color(def[0]);
        cout << setw(padding) << "" << "\t\tCheck membership" <<endl;
        color_set::color(def[0]);
        cout << setw(padding) << "" << setw(menuWidth) << setfill('-') << "" << setfill(' ') << endl;
        color_set::gotoxy(padding + 2, 4);
        cout<<"Enter phone number of member: ";
        cin>>input_num;
        ifstream check("members_data.txt",ios::binary|ios::in);
        run=0;
        equ=0;
        while(check>>fname>>lname>>phnumber)
        {
            run++;
            if(input_num!=phnumber)
            {
                equ++;
            }
        }
        check.close();
        if(run==equ)
        {
            cout<<"Membership not found"<<endl;
            cout<<"If you would like to check again press enter key."<<endl;
            cout<<"Else press any other key."<<endl;
            key=_getch();
            if(key=='\r')
            {
                clear();
                checkMembership();
            }
            else
            {
                mem_name="Guest";
                clear();
                bill();
            }
        }
        else
        {
            mem_name=fname+" "+lname;
            cout<<"Membership found"<<endl;
            cout<<"Is this the member: "<<mem_name<<endl;
            cout<<"If yes press enter key."<<endl;
            cout<<"Else press any key, which will ask you to enter membership again"<<endl;
            key=_getch();
            if(key=='\r')
            {
                clear();
                bill();
            }
            else
            {
                clear();
                checkMembership();
            }
        }
    }

    void bill()
    {
        color_set::color(def[0]);
        cout << setw(padding) << "" << setw(menuWidth) << setfill('-') << "" << setfill(' ') << endl;
        color_set::color(def[0]);
        cout << setw(padding) << "" << "\t\tKrish Store" <<endl;
        cout << setw(padding) << "" << "\t\tKathmandu,Kalimati" <<endl;
        color_set::color(def[0]);
        cout << setw(padding) << "" << setw(menuWidth) << setfill('-') << "" << setfill(' ') << endl;
        color_set::gotoxy(padding + 2, 4);
        ifstream bill("bill_no.txt",ios::binary|ios::in);
        bill>>bill_no;
        bill.close();
        cout<<"Bill no: "<<bill_no;
        bill_no++;
        ofstream add("temp.txt",ios::binary|ios::out);
        add<<bill_no;
        add.close();
        remove("bill_no.txt");
        rename("temp.txt","bill_no.txt");

        color_set::gotoxy(padding + 2, 5);
        cout<<"Bill to: "<<mem_name;

        color_set::gotoxy(0, 6);
        color_set::color(def[0]);
        cout << setw(padding) << "" << setw(menuWidth) << setfill('-') << "" << setfill(' ') << endl;

        ifstream display("bill.txt",ios::binary|ios::in);
        color_set::gotoxy(padding, 7);
        cout << "Item name \t Quantity \t Price ";
        i=8;
        total=0;
        while (display >> fname >> item_num >> item_quantity >> item_price)
        {
            color_set::gotoxy(padding , i);
            color_set::color(change);
            cout << setw(first+2) << left << fname << setw(second) << item_quantity << setw(third) << item_price*item_quantity << endl;
            total=total+(item_price*item_quantity);
            i++;
        }

        display.close();
        color_set::gotoxy(0, i+1);
        color_set::color(def[0]);
        cout << setw(padding) << "" << setw(menuWidth) << setfill('-') << "" << setfill(' ') << endl;

        ifstream orignal("item_data.txt",ios::binary|ios::in);
        ofstream out("temp.txt",ios::binary|ios::out);
        while(orignal>>sname>>snum>>squa>>spri)
        {
            ifstream dew("bill.txt",ios::binary|ios::in);
            while(dew>>fname>>item_num>>item_quantity>>item_price)
            {
                if(item_num==snum)
                {
                    new_num=squa - item_quantity;
                    if(new_num!=0)
                    {
                        out<<fname<<" "<<item_num<<" "<<new_num<<" "<<item_price<<endl;
                    }
                }
            }
            dew.close();
        }
        orignal.close();
        out.close();
        ifstream orig("item_data.txt",ios::binary|ios::in);
        ofstream fin("temp1.txt",ios::binary|ios::out);
        while(orig>>sname>>snum>>squa>>spri)
        {
                ifstream dat("temp.txt",ios::binary|ios::in);
                found=0;
                while(dat>>fname>>item_num>>item_quantity>>item_price)
                {
                    if(item_num==snum && squa>item_quantity)
                    {
                        fin<<fname<<" "<<item_num<<" "<<item_quantity<<" "<<item_price<<endl;
                        found=1;
                        break;
                    }
                }
                dat.close();
                if(!found)
                {
                    fin<<sname<<" "<<snum<<" "<<squa<<" "<<spri<<endl;
                }
        }
        orig.close();
        fin.close();
        remove("item_data.txt");
        remove("bill.txt");
        remove("temp.txt");
        rename("temp1.txt","item_data.txt");
        color_set::gotoxy(padding+20, i+2);
        cout<<setw(padding-14)<<"Total: "<<total;
        color_set::gotoxy(0, i+3);
        cout << setw(padding) << "" << setw(menuWidth) << setfill('-') << "" << setfill(' ') << endl;
        color_set::gotoxy(padding, i+4);
        cout<<"Cashier: "<<set_user<<" "<<set_lname;
        color_set::gotoxy(padding, i+5);
        cout<<"Thank you for choosing us!!";
        color_set::gotoxy(padding, i+6);
        cout<<"Hope to see you again!!";
        color_set::gotoxy(0, i+7);
        cout << setw(padding) << "" << setw(menuWidth) << setfill('-') << "" << setfill(' ') << endl;
        color_set::gotoxy(0, i+9);
        cout<<"Press any key to go back to main menu.";
        getch();
        displayMenu();
    }

    void shoplistMenu()
    {
        counter=1;
        color_set::color(def[0]);
        cout << setw(padding) << "" << setw(menuWidth) << setfill('-') << "" << setfill(' ') << endl;
        color_set::color(def[0]);
        cout << setw(padding) << "" << "\t\tAdd | Remove | Update" <<endl;
        color_set::color(def[0]);
        cout << setw(padding) << "" << setw(menuWidth) << setfill('-') << "" << setfill(' ') << endl;

        while (1)
        {
            color_set::gotoxy(padding + 2, 4);
            color_set::color(Set[0]);
            cout << "1. Add Item" << endl;

            color_set::gotoxy(padding + 2, 5);
            color_set::color(Set[1]);
            cout << "2. Remove Item" << endl;

            color_set::gotoxy(padding +2, 6);
            color_set::color(Set[2]);
            cout<<"3. Update Item"<<endl;

            color_set::gotoxy(padding + 2, 7);
            color_set::color(Set[3]);
            cout << "4. Exit" << endl;

            color_set::color(def[0]);
            cout << setw(padding) << "" << setw(menuWidth) << setfill('-') << "" << setfill(' ') << endl;

            key = _getch();
            if (key == 72 && (counter >= 2 && counter <= 4))
            {
                counter--;
            }
            if (key == 80 && (counter >= 1 && counter <= 3))
            {
                counter++;
            }
            if (key == '\r')
            {
                switch (counter)
                {
                case 1:
                    Set[0] = 7;
                    clear();
                    shoplistAdd();
                    break;

                case 2:
                    Set[1] = 7;
                    clear();
                    shoplistRemove();
                    break;

                case 3:
                    Set[2] = 7;
                    clear();
                    shoplistUpdate();
                    break;

                case 4:
                    Set[3] = 7;
                    clear();
                    EditMenu();
                    break;

                default:
                    cout << "Invalid" << endl;
                    continue;
                }
            }
            Set[0] = 7;
            Set[1] = 7;
            Set[2] = 7;
            Set[3] = 7;

            if (counter == 1)
                Set[0] = 12;

            if (counter == 2)
                Set[1] = 12;

            if (counter == 3)
                Set[2] = 12;

            if (counter ==4)
                Set[3] = 12;
        }
    }

    void shoplistAdd()
    {
        color_set::color(def[0]);
        cout << setw(padding) << "" << setw(menuWidth) << setfill('-') << "" << setfill(' ') << endl;
        color_set::color(def[0]);
        cout << setw(padding) << "" << "\t\t\tInsert" <<endl;
        color_set::color(def[0]);
        cout << setw(padding) << "" << setw(menuWidth) << setfill('-') << "" << setfill(' ') << endl;

        color_set::color(12);
        color_set::gotoxy(padding, 4);
        cout<<"Note: you cannot add item number already in use!!!!"<<endl;
        color_set::color(def[0]);
        color_set::gotoxy(padding,5);
        cout<<"Enter item number of product.";
        cin>>input_num;
        ifstream check("item_data.txt",ios::binary|ios::in);
        run=0;
        equ=0;
        while(check>>fname>>item_num>>item_quantity>>item_price)
        {
            run++;
            if(input_num!=item_num)
            {
                equ++;
            }
        }
        if(equ==run)
        {
            check.close();
            ofstream save("item_data.txt",ios::binary|ios::out|ios::app);

            color_set::gotoxy(padding +2, 7);
            cout<<"You can use the item number!!";
            cin.ignore();

            color_set::gotoxy(padding +2, 8);
            cout<<"Enter item name:";
            getline(cin, fname);

            color_set::gotoxy(padding +2, 9);
            cout<<"Enter quantity of item:";
            cin>>item_quantity;

            color_set::gotoxy(padding +2, 10);
            cout<<"Enter price of item:";
            cin>>item_price;

            color_set::color(def[0]);
            cout << setw(padding) << "" << setw(menuWidth) << setfill('-') << "" << setfill(' ') << endl;

            save<<"\n"<<fname<<" "<<input_num<<" "<<item_quantity<<" "<<item_price<<endl;
            save.close();
            cout<<"Item successfully added!!!!"<<endl;
        }
        else
        {
            cout<<"Item number already in use!!!"<<endl;
            check.close();
        }
        cout<<"Would you like to continue?"<<endl;
        cout<<"Press enter key to continue"<<endl;
        cout<<"Else press any key"<<endl;
        key=_getch();
        if(key=='\r')
        {
            if(b==6)
            {
                clear();
                b=0;
                shoplistUpdate();
            }
            else
            {
                clear();
                shoplistAdd();
            }
        }
        else
        {
            clear();
            shoplistMenu();
        }
    }

    void shoplistRemove()
    {
        color_set::color(def[0]);
        cout << setw(padding) << "" << setw(menuWidth+10) << setfill('-') << "" << setfill(' ') << endl;
        color_set::color(def[0]);
        cout << setw(padding) << "" << "\t\t\tRemove item" <<endl;
        color_set::color(def[0]);
        cout << setw(padding) << "" << setw(menuWidth+10) << setfill('-') << "" << setfill(' ') << endl;

        color_set::gotoxy(padding, 4);
        cout << "Item name \t Quantity \t Item number" << endl;

        i=5;

        ifstream display("item_data.txt",ios::binary|ios::in);
        while(display>>fname>>item_num>>item_quantity>>item_price)
        {
            color_set::gotoxy(padding, i);
            cout <<setw(first) << left << fname << setw(second+3) << item_quantity << setw(third) << item_num << endl;
            i++;
        }
        color_set::color(def[0]);
        cout << setw(padding) << "" << setw(menuWidth+10) << setfill('-') << "" << setfill(' ') << endl;
        display.close();
        found=0;
        cout<<"\nEnter item number of item you want to remove."<<endl;
        cin>>input_num;
        ifstream check("item_data.txt",ios::binary|ios::in);
        ofstream temp("temp.txt",ios::binary|ios::out);
        while(check>>fname>>item_num>>item_quantity>>item_price)
        {
            if(input_num!=item_num)
            {
                temp<<fname<<" "<<item_num<<" "<<item_quantity<<" "<<item_price<<endl;
            }
            else
            {
                found=1;
            }
        }
        check.close();
        temp.close();
        remove("item_data.txt");
        rename("temp.txt","item_data.txt");
        if (found)
        {
            cout << "Item deleted!" << endl;
        }
        else
        {
            cout << "No such Item found." << endl;
            remove("temp.txt");
        }

        cout << "Press enter key to continue." << endl;
        cout << "Else press any other key." << endl;
        key = _getch();
        if (key == '\r')
        {
            clear();
            shoplistRemove();
        }
        else
        {
            clear();
            shoplistMenu();
        }
    }

    void shoplistUpdate()
    {
        color_set::color(def[0]);
        cout << setw(padding) << "" << setw(menuWidth+10) << setfill('-') << "" << setfill(' ') << endl;
        color_set::color(def[0]);
        cout << setw(padding) << "" << "\t\t\tUpdate Item" <<endl;
        color_set::color(def[0]);
        cout << setw(padding) << "" << setw(menuWidth+10) << setfill('-') << "" << setfill(' ') << endl;

        color_set::gotoxy(padding, 4);
        cout << "Item name \t Quantity \t Item number" << endl;
        i=5;
        ifstream display("item_data.txt",ios::binary|ios::in);
        while(display>>fname>>item_num>>item_quantity>>item_price)
        {
            color_set::gotoxy(padding, i);
            cout <<setw(first) << left << fname << setw(second+3) << item_quantity << setw(third) << item_num << endl;
            i++;
        }
        color_set::color(def[0]);
        cout << setw(padding) << "" << setw(menuWidth+10) << setfill('-') << "" << setfill(' ') << endl;
        display.close();

        color_set::gotoxy(padding, i+1);
        cout<<"Enter item number of the item you would like to update: ";
        cin>>input_num;
        found=0;
        ifstream check("item_data.txt",ios::binary|ios::in);
        ofstream temp("temp.txt",ios::binary|ios::out);
        while(check>>fname>>item_num>>item_quantity>>item_price)
        {
            if(item_num!=input_num)
            {
                temp<<fname<<" "<<item_num<<" "<<item_quantity<<" "<<item_price<<endl;
            }
            else
            {
                found=1;
            }
        }
        temp.close();
        check.close();
        remove("item_data.txt");
        rename("temp.txt","item_data.txt");
        if(found)
        {
            clear();
            b=6;
            shoplistAdd();
        }
        else
        {
            cout<<"No such item found!!"<<endl;
            cout<<"If you would like to add it,"<<endl;
        }
        cout << "Press enter key to continue." << endl;
        cout << "Else press any other key." << endl;
        key = _getch();
        if (key == '\r')
        {
            clear();
            shoplistAdd();
        }
        else
        {
            clear();
            shoplistMenu();
        }
    }

    void membershipEdit()
    {
        counter=1;
        color_set::color(def[0]);
        cout << setw(padding) << "" << setw(menuWidth) << setfill('-') << "" << setfill(' ') << endl;
        color_set::color(def[0]);
        cout << setw(padding) << "" << "\t\tAdd | Remove | Update" <<endl;
        color_set::color(def[0]);
        cout << setw(padding) << "" << setw(menuWidth) << setfill('-') << "" << setfill(' ') << endl;

        while (1)
        {
            color_set::gotoxy(padding + 2, 4);
            color_set::color(Set[0]);
            cout << "1. Add member" << endl;

            color_set::gotoxy(padding + 2, 5);
            color_set::color(Set[1]);
            cout << "2. Remove member" << endl;

            color_set::gotoxy(padding +2, 6);
            color_set::color(Set[2]);
            cout<<"3. Update member"<<endl;

            color_set::gotoxy(padding + 2, 7);
            color_set::color(Set[3]);
            cout << "4. Exit" << endl;

            color_set::color(def[0]);
            cout << setw(padding) << "" << setw(menuWidth) << setfill('-') << "" << setfill(' ') << endl;

            key = _getch();
            if (key == 72 && (counter >= 2 && counter <= 4))
            {
                counter--;
            }
            if (key == 80 && (counter >= 1 && counter <= 3))
            {
                counter++;
            }
            if (key == '\r')
            {
                switch (counter)
                {
                case 1:
                    Set[0] = 7;
                    clear();
                    membershipAdd();
                    break;

                case 2:
                    Set[1] = 7;
                    clear();
                    membershipRemove();
                    break;

                case 3:
                    Set[2] = 7;
                    clear();
                    membershipUpdate();
                    break;

                case 4:
                    Set[3] = 7;
                    clear();
                    displayMenu();
                    break;

                default:
                    cout << "Invalid" << endl;
                    continue;
                }
            }

            Set[0] = 7;
            Set[1] = 7;
            Set[2] = 7;
            Set[3] = 7;

            if (counter == 1)
                Set[0] = 12;

            if (counter == 2)
                Set[1] = 12;

            if (counter == 3)
                Set[2] = 12;

            if (counter ==4)
                Set[3] = 12;
        }
    }

    void membershipAdd()
    {
        color_set::color(def[0]);
        cout << setw(padding) << "" << setw(menuWidth) << setfill('-') << "" << setfill(' ') << endl;
        color_set::color(def[0]);
        cout << setw(padding) << "" << "\t\t\tInsert" <<endl;
        color_set::color(def[0]);
        cout << setw(padding) << "" << setw(menuWidth) << setfill('-') << "" << setfill(' ') << endl;
        color_set::color(12);
        color_set::gotoxy(padding, 4);
        cout<<"Note: you cannot add a member's phone number that is already in use!!!!"<<endl;
        color_set::color(def[0]);
        color_set::gotoxy(padding,5);
        cout<<"Enter phone number of costumer.";
        cin>>input_phnumber;
        ifstream check("members_data.txt",ios::binary|ios::in);
        run=0;
        equ=0;
        while(check>>fname>>lname>>phnumber)
        {
            run++;
            if(input_phnumber!=phnumber)
            {
                equ++;
            }
        }
        if(equ==run)
        {
            check.close();
            ofstream save("members_data.txt",ios::binary|ios::out|ios::app);

            color_set::gotoxy(padding + 2, 7);
            cout<<"You can use the phone number: ";
            cin.ignore();

            color_set::gotoxy(padding + 2, 8);
            cout<<"Enter costumers First name: ";
            getline(cin, fname);

            color_set::gotoxy(padding + 2, 9);
            cout << "Enter Last Name: ";
            getline(cin, lname);

            color_set::color(def[0]);
            cout << setw(padding) << "" << setw(menuWidth) << setfill('-') << "" << setfill(' ') << endl;

            save<<"\n"<<fname<<" "<<lname<<" "<<input_phnumber<<endl;
            save.close();
            cout<<"Membership successfully added!!!!"<<endl;
        }
        else
        {
            cout<<"Phone number cannot be reused!!!"<<endl;
            check.close();
        }
        cout<<"Would you like to continue?"<<endl;
        cout<<"Press enter key to continue"<<endl;
        cout<<"Else press any key"<<endl;
        key=_getch();
        if(key=='\r')
        {
            if(b==6)
            {
                clear();
                b=0;
                membershipUpdate();
            }
            else
            {
                clear();
                membershipAdd();
            }
        }
        else
        {
            clear();
            membershipEdit();
        }
    }

    void membershipRemove()
    {
        color_set::color(def[0]);
        cout << setw(padding) << "" << setw(menuWidth) << setfill('-') << "" << setfill(' ') << endl;
        color_set::color(def[0]);
        cout << setw(padding) << "" << "\t\tRemove membership" <<endl;
        color_set::color(def[0]);
        cout << setw(padding) << "" << setw(menuWidth) << setfill('-') << "" << setfill(' ') << endl;

        color_set::gotoxy(padding, 4);
        cout<<"First name \t Last name \t Phone number";

        i=5;

        ifstream display("members_data.txt",ios::binary|ios::in);
        while(display>>fname>>lname>>phnumber)
        {
            color_set::gotoxy(padding, i);
            cout <<setw(first-1)<<left<< fname << setw(first -4) << lname << setw(fourth) << phnumber << endl;
            i++;
        }
        color_set::color(def[0]);
        cout << setw(padding) << "" << setw(menuWidth) << setfill('-') << "" << setfill(' ') << endl;
        display.close();
        found=0;
        cout<<"\nEnter phone number of the member you want to remove."<<endl;
        cin>>input_phnumber;
        ifstream check("members_data.txt",ios::binary|ios::in);
        ofstream temp("temp.txt",ios::binary|ios::out);
        while(check>>fname>>lname>>phnumber)
        {
            if(input_phnumber==phnumber)
            {
                found=1;
            }
            else
            {
                temp<<fname<<" "<<lname<<" "<<phnumber<<endl;
            }
        }
        check.close();
        temp.close();
        remove("members_data.txt");
        rename("temp.txt","members_data.txt");
        if (found)
        {
            cout << "Membership deleted!" << endl;
        }
        else
        {
            cout << "No such Member found." << endl;
            remove("temp.txt");
        }
        cout << "Press enter key to continue." << endl;
        cout << "Else press any other key." << endl;
        key = _getch();
        if (key == '\r')
        {
            clear();
            membershipRemove();
        }
        else
        {
            clear();
            membershipEdit();
        }
    }

    void membershipUpdate()
    {
        color_set::color(def[0]);
        cout << setw(padding) << "" << setw(menuWidth+10) << setfill('-') << "" << setfill(' ') << endl;
        color_set::color(def[0]);
        cout << setw(padding) << "" << "\t\t\tUpdate Membership" <<endl;
        color_set::color(def[0]);
        cout << setw(padding) << "" << setw(menuWidth+10) << setfill('-') << "" << setfill(' ') << endl;
        color_set::gotoxy(padding, 4);
        cout<<"First name \t Last name \t Phone number";
        i=5;
        ifstream display("members_data.txt",ios::binary|ios::in);
        while(display>>fname>>lname>>phnumber)
        {
            color_set::gotoxy(padding, i);
            cout <<setw(first-1)<<left<< fname << setw(first -4) << lname << setw(fourth) << phnumber << endl;
            i++;
        }
        color_set::color(def[0]);
        cout << setw(padding) << "" << setw(menuWidth+10) << setfill('-') << "" << setfill(' ') << endl;
        display.close();

        color_set::gotoxy(padding, i+1);
        cout<<"Enter phone number of the costumer whose membership you would like to update: ";
        found=0;
        cin>>input_phnumber;
        ifstream check("members_data.txt",ios::binary|ios::in);
        ofstream temp("temp.txt",ios::binary|ios::out);
        while(check>>fname>>lname>>phnumber)
        {
            if(phnumber!=input_phnumber)
            {
                temp<<fname<<" "<<lname<<" "<<phnumber<<endl;
            }
            else
            {
                found=1;
            }
        }
        temp.close();
        check.close();
        remove("members_data.txt");
        rename("temp.txt","members_data.txt");
        if(found)
        {
            clear();
            b=6;
            membershipAdd();
        }
        else
        {
            cout<<"No such phone number found!!"<<endl;
            cout<<"If you would like to add it,"<<endl;
        }
        cout << "Press enter key to continue." << endl;
        cout << "Else press any other key." << endl;
        key = _getch();
        if (key == '\r')
        {
            clear();
            membershipAdd();
        }
        else
        {
            clear();
            membershipEdit();
        }
    }

    void read_user_pass()
    {
        ifstream user_password("user_name_and_password.txt", ios::in | ios::binary);
        cout << "Enter username:" << endl;
        cin >> input_user;
        cout << "Enter password:" << endl;
        cin >> input_password;
        found = 0;
        while (user_password >> username >> password>>fname>>lname)
        {
            if (username == input_user && password == input_password)
            {
                found = 1;
                break;
            }
        }
        user_password.close();

        if (found)
        {
            set_user=input_user;
            set_fname=fname;
            set_lname=lname;
            clear();
            displayMenu();
        }
        else
        {
            cout << "Invalid username or password. Please try again." << endl;
            cout<<"Press enter key to continue."<<endl;
            key=_getch();
            if (key == '\r')
            {
            clear();
            displayLogin();
            }
        }
    }

    void updateRecord()
    {
        color_set::color(def[0]);
        cout << setw(padding) << "" << setw(menuWidth+10) << setfill('-') << "" << setfill(' ') << endl;
        color_set::color(def[0]);
        cout << setw(padding) << "" << "\t\t\tUpdate" <<endl;
        color_set::color(def[0]);
        cout << setw(padding) << "" << setw(menuWidth+10) << setfill('-') << "" << setfill(' ') << endl;
        ifstream user_password("user_name_and_password.txt", ios::binary | ios::in|ios::out);

        color_set::gotoxy(padding, 4);
        cout << "First name \t Last name \t User name" << endl;
        i=5;
        found=0;
        while (user_password >> username >> password >> fname >> lname)
        {
            color_set::gotoxy(padding, i);
            cout<<setw(first-1)<<left << fname << setw(first-2) << lname << setw(fourth) << username << endl;
            i++;
        }
        user_password.close();
        color_set::color(def[0]);
        cout << setw(padding) << "" << setw(menuWidth+10) << setfill('-') << "" << endl;
        color_set::color(12);
        color_set::gotoxy(padding, i+1);
        cout<<"Note: you cannot edit the user you are logged in with!!!!"<<endl;
        color_set::gotoxy(padding, i+2);
        color_set::color(7);
        cout<<"Enter username of the user you want to update: ";

        found=0;
        cin>>input_user;
        if(input_user==set_user)
        {
            cout<<"You cannot edit the user you are logged in as!!!"<<endl;
        }
        else
        {
            ifstream check("user_name_and_password.txt",ios::binary|ios::in);
            ofstream temp("temp.txt",ios::binary|ios::out);
            while(check>>username>>password>>fname>>lname)
            {
                if(username!=input_user)
                {
                    temp << username << " " << password << " " << fname << " " << lname << endl;
                }
                else
                {
                    found=1;
                }
            }
            temp.close();
            check.close();
            remove("user_name_and_password.txt");
            rename("temp.txt", "user_name_and_password.txt");
            if(found)
            {
                clear();
                b=6;
                createRecord();
            }
            else
            {
                cout<<"No user found!!"<<endl;
            }
        }
        cout << "Press enter key to continue." << endl;
        cout << "Else press any other key." << endl;
        key = _getch();
        if (key == '\r')
        {
            clear();
            updateRecord();
        }
        else
        {
            clear();
            EditModerator();
        }
    }

    void deleteRecord()
    {
        color_set::color(def[0]);
        cout << setw(padding) << "" << setw(menuWidth+10) << setfill('-') << "" << setfill(' ') << endl;
        color_set::color(def[0]);
        cout << setw(padding) << "" << "\t\t\t Remove" <<endl;
        color_set::color(def[0]);
        cout << setw(padding) << "" << setw(menuWidth+10) << setfill('-') << "" << setfill(' ') << endl;
        ifstream user_password("user_name_and_password.txt", ios::binary | ios::in|ios::out);

        color_set::gotoxy(padding, 4);
        cout << "First name \t Last name \t User name" << endl;
        i=5;
        found=0;
        while (user_password >> username >> password >> fname >> lname)
        {
            color_set::gotoxy(padding, i);
            cout<<setw(first-1)<<left << fname << setw(first-2) << lname << setw(fourth) << username << endl;
            i++;
        }
        user_password.close();
        color_set::color(def[0]);
        cout << setw(padding) << "" << setw(menuWidth+10) << setfill('-') << "" << endl;

        color_set::color(12);
        color_set::gotoxy(padding, i+2);
        cout<<"Note: You cannot remove the user you are logged in as!!!"<<endl;
        color_set::color(def[0]);
        cout<<"\nEnter username of the user you want to delete"<<endl;
        cin>>input_user;
        if(input_user==set_user)
        {
            cout<<"You cannot delete the data you are logged in with!!"<<endl;
        }
        else
        {
            ifstream check("user_name_and_password.txt", ios::binary|ios::in );
            ofstream data_clear("temp.txt",ios::binary|ios::out);
            while (check >> username >> password >> fname >> lname)
            {
                if (username != input_user)
                {
                data_clear << username << " " << password << " " << fname << " " << lname << endl;
                }
                else
                {
                    found = 1;
                }
            }
            data_clear.close();
            check.close();
            remove("user_name_and_password.txt");
            rename("temp.txt", "user_name_and_password.txt");

            if (found)
            {
            cout << "Record deleted!" << endl;
            }
            else
            {
                cout << "No such data found." << endl;
                remove("temp.txt");
            }
        }
        cout << "Press enter key to continue." << endl;
        cout << "Else press any other key." << endl;
        key = _getch();
        if (key == '\r')
        {
            clear();
            deleteRecord();
        }
        else
        {
            clear();
            EditModerator();
        }
    }

    void createRecord()
    {
        color_set::color(def[0]);
        cout << setw(padding) << "" << setw(menuWidth) << setfill('-') << "" << setfill(' ') << endl;
        color_set::color(def[0]);
        cout << setw(padding) << "" << "\t\t\tInsert" <<endl;
        color_set::color(def[0]);
        cout << setw(padding) << "" << setw(menuWidth) << setfill('-') << "" << setfill(' ') << endl;

        color_set::color(12);
        color_set::gotoxy(padding, 4);
        cout<<"Note: You cannot add the user name that already exists!!!"<<endl;
        color_set::color(def[0]);
        color_set::gotoxy(padding + 2, 6);
        cout << "Enter Username you would like: ";

        cin>>username;

        ifstream data("user_name_and_password.txt",ios::binary|ios::in);
        string temp_user,temp_password,temp_fname,temp_lname;
        run=0;
        equ=0;
        while(data>>temp_user>>temp_password>>temp_fname>>temp_lname)
        {
            run++;
            if(username!=temp_user)
            {
                equ++;
            }
        }
        if(equ==run)
        {
            data.close();
            ofstream user_password("user_name_and_password.txt",ios::app|ios::binary);

            color_set::gotoxy(padding + 2, 7);
            cout << "You can use the username: ";
            cin.ignore();

            color_set::gotoxy(padding + 2, 8);
            cout << "Enter First Name: ";
            getline(cin, fname);

            color_set::gotoxy(padding + 2, 9);
            cout << "Enter Last Name: ";
            getline(cin, lname);

            color_set::gotoxy(padding + 2, 10);
            cout << "Enter Password: ";
            getline(cin, password);

            color_set::color(def[0]);
            cout << setw(padding) << "" << setw(menuWidth) << setfill('-') << "" << setfill(' ') << endl;

            user_password <<"\n"<< username << " " << password << " " << fname << " " << lname << endl;
            user_password.close();
            cout<<"Data successfully added!!"<<endl;
        }
        else
        {
            cout<<"Username cannot be reused!!"<<endl;
            data.close();
        }
        cout<<"Would you like to continue?"<<endl;
        cout<<"Press enter key to continue"<<endl;
        cout<<"Else press any key"<<endl;
        key=_getch();
        if(key=='\r')
        {
            if(b==6)
            {
                clear();
                b=0;
                updateRecord();
            }
            clear();
            createRecord();
        }
        else
        {
            clear();
            EditModerator();
        }
    }

    void EditModerator()
    {
        counter=1;
        color_set::color(def[0]);
        cout << setw(padding) << "" << setw(menuWidth) << setfill('-') << "" << setfill(' ') << endl;
        color_set::color(def[0]);
        cout << setw(padding) << "" << "\t\tAdd | Remove | Update" <<endl;
        color_set::color(def[0]);
        cout << setw(padding) << "" << setw(menuWidth) << setfill('-') << "" << setfill(' ') << endl;

        while (1)
        {
            color_set::gotoxy(padding + 2, 4);
            color_set::color(Set[0]);
            cout << "1. Add moderator" << endl;

            color_set::gotoxy(padding + 2, 5);
            color_set::color(Set[1]);
            cout << "2. Remove moderator" << endl;

            color_set::gotoxy(padding +2, 6);
            color_set::color(Set[2]);
            cout<<"3. Update moderator"<<endl;

            color_set::gotoxy(padding + 2, 7);
            color_set::color(Set[3]);
            cout << "4. Exit" << endl;

            color_set::color(def[0]);
            cout << setw(padding) << "" << setw(menuWidth) << setfill('-') << "" << setfill(' ') << endl;

            key = _getch();
            if (key == 72 && (counter >= 2 && counter <= 4))
            {
                counter--;
            }
            if (key == 80 && (counter >= 1 && counter <= 3))
            {
                counter++;
            }
            if (key == '\r')
            {
                switch (counter)
                {
                case 1:
                    Set[0] = 7;
                    clear();
                    createRecord();
                    break;

                case 2:
                    Set[1] = 7;
                    clear();
                    deleteRecord();
                    break;

                case 3:
                    Set[2] = 7;
                    clear();
                    updateRecord();
                    break;

                case 4:
                    Set[3] = 7;
                    clear();
                    EditMenu();
                    break;

                default:
                    cout << "Invalid" << endl;
                    continue;
                }
            }
            Set[0] = 7;
            Set[1] = 7;
            Set[2] = 7;
            Set[3] = 7;

            if (counter == 1)
                Set[0] = 12;

            if (counter == 2)
                Set[1] = 12;

            if (counter == 3)
                Set[2] = 12;

            if (counter ==4)
                Set[3] = 12;
        }
    }

    void EditMenu()
    {
        counter=1;
        color_set::color(def[0]);
        cout << setw(padding) << "" << setw(menuWidth) << setfill('-') << "" << setfill(' ') << endl;
        color_set::color(def[0]);
        cout << setw(padding) << "" << "\t\t\tChoose Edit" <<endl;
        color_set::color(def[0]);
        cout << setw(padding) << "" << setw(menuWidth) << setfill('-') << "" << setfill(' ') << endl;

        while (1)
        {
            color_set::gotoxy(padding + 2, 4);
            color_set::color(Set[0]);
            cout << "1. Edit shoplist" << endl;

            color_set::gotoxy(padding + 2, 5);
            color_set::color(Set[1]);
            cout << "2. Edit moderator" << endl;

            color_set::gotoxy(padding + 2, 6);
            color_set::color(Set[2]);
            cout << "3. Exit" << endl;

            color_set::color(def[0]);
            cout << setw(padding) << "" << setw(menuWidth) << setfill('-') << "" << setfill(' ') << endl;

            key = _getch();
            if (key == 72 && (counter >= 2 && counter <= 3))
            {
                counter--;
            }
            if (key == 80 && (counter >= 1 && counter <= 2))
            {
                counter++;
            }
            if (key == '\r')
            {
                switch (counter)
                {
                case 1:
                    Set[0] = 7;
                    clear();
                    shoplistMenu();
                    break;

                case 2:
                    Set[1] = 7;
                    clear();
                    EditModerator();
                    break;

                case 3:
                    Set[2] = 7;
                    clear();
                    displayMenu();
                    break;

                default:
                    cout << "Invalid" << endl;
                    continue;
                }
            }
            Set[0] = 7;
            Set[1] = 7;
            Set[2] = 7;

            if (counter == 1)
                Set[0] = 12;

            if (counter == 2)
                Set[1] = 12;

            if (counter == 3)
                Set[2] = 12;
        }
    }


    void displayLogin()
    {
        counter=1;
        color_set::color(def[0]);
        cout << setw(padding) << "" << setw(menuWidth) << setfill('-') << "" << setfill(' ') << endl;
        color_set::color(def[0]);
        cout << setw(padding) << "" << "\t\t\tLogin" <<endl;
        color_set::color(def[0]);
        cout << setw(padding) << "" << setw(menuWidth) << setfill('-') << "" << setfill(' ') << endl;

        while (1)
        {
            color_set::gotoxy(padding + 2, 4);
            color_set::color(Set[0]);
            cout << "1. Login" << endl;

            color_set::gotoxy(padding + 2, 5);
            color_set::color(Set[1]);
            cout << "2. Exit" << endl;

            color_set::color(def[0]);
            cout << setw(padding) << "" << setw(menuWidth) << setfill('-') << "" << setfill(' ') << endl;

            key = _getch();
            if (key == 72 && (counter == 2))
            {
                counter--;
            }
            if (key == 80 && (counter == 1))
            {
                counter++;
            }
            if (key == '\r')
            {
                switch (counter)
                {
                case 1:
                    Set[0] = 7;
                    read_user_pass();
                    break;

                case 2:
                    Set[1] = 7;
                    clear();
                    cout << "Closing shop...." << endl;
                    ExitProcess(0);
                    break;

                default:
                    cout << "Invalid" << endl;
                    continue;
                }
            }

            Set[0] = 7;
            Set[1] = 7;

            if (counter == 1)
                Set[0] = 12;

            if (counter == 2)
                Set[1] = 12;
        }
    }
};

int main()
{
    fstream data("item_data.txt");
    fstream data1("members_data.txt");
    fstream data2("user_name_and_password.txt");
    fstream data3("bill_no.txt");
    if(!data||!data1||!data2||!data3)
    {
        cout<<"The required file were not found, please open the program after confirming the existence of file.";
    }
    else
    {
        data.close();
        data1.close();
        data2.close();
        data3.close();
        createInvoice object;
        object.displayLogin();
    }
    return 0;
}
