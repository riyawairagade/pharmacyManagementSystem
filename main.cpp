#include <iostream>
#include <unordered_map>
#include <list>
#include <fstream>

using namespace std;

bool userLogin()
{
    string uname, pass, u, p;
    cout << "Enter username :";
    cin >> uname;
    cout << "Enter password :";
    cin >> pass;

    ifstream read("C:\\Users\\RIYA WAIRAGADE\\Desktop\\pharmacy\\" + uname + ".txt");
    getline(read, u);
    getline(read, p);


    if ( p == pass && u == uname)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool adminLogin()
{
    string pass, p;

    cout << "Enter password to login as admin:";
    cin >> pass;

    p="admin12!";

    if (p == pass)
    {
        return true;
    }
    else
    {
        return false;
    }
}

//
class medicineType{
public:
    int choice;
    int amount;
    void take_order(const string &inputName, medicineType type, list<unordered_map<std::string, std::string>> medsList, list<unordered_map<std::string, std::string>> cart);
    void view_medicines(medicineType type, list<unordered_map<std::string, std::string>> medsList, list<unordered_map<std::string, std::string>> cart);
    void add(int num, medicineType type, list<unordered_map<std::string, std::string>> medsList, list<unordered_map<std::string, std::string>> cart);
    void deleteMed(const string &inputName, medicineType type, list<unordered_map<std::string, std::string>> medsList, list<unordered_map<std::string, std::string>> cart);
    void update(const string &inputName, medicineType type, list<unordered_map<std::string, std::string>> medsList, list<unordered_map<std::string, std::string>> cart);
    void viewCart(medicineType type, const list<unordered_map<std::string, std::string>>& medsList, list<unordered_map<std::string, std::string>> cart);
    void generateBill(medicineType medicine, list<unordered_map<std::string, std::string>> medsList, list<unordered_map<std::string, std::string>> cart);
    void deleteFromCart(const string &inputName, medicineType type, list<unordered_map<std::string, std::string>> medsList, list<unordered_map<std::string, std::string>> cart);
    void menu(medicineType medicine, list<unordered_map<std::string, std::string>> medsList, list<unordered_map<std::string, std::string>> cart);
    void adminMenu(medicineType medicine, list<unordered_map<std::string, std::string>> medsList, list<unordered_map<std::string, std::string>> cart);
    void login(medicineType medicine2, list<unordered_map<std::string, std::string>> medicines, list<unordered_map<std::string, std::string>> cart);
    void exitToLogin(medicineType medicine2, list<unordered_map<std::string, std::string>> medicines, list<unordered_map<std::string, std::string>> cart);
    void amountGenerated(medicineType medicine, list<unordered_map<std::string, std::string>> medsList, list<unordered_map<std::string, std::string>> cart);
    void exit();
    medicineType();
};

medicineType::medicineType()= default;

//method for taking medicine orders
void medicineType::take_order(const string &inputName, medicineType type, list<unordered_map<std::string, std::string>> medsList, list<unordered_map<std::string, std::string>> cart) {
    int count = 0;
    for (const unordered_map<string, string>&med : medsList)
    {
        if(med.at("Name") == inputName) {
            string inputQuantity;
            cout << "Enter quantity of " << inputName << " to order: " << endl;
            cin >> inputQuantity;
            int q = stoi(med.at("Quantity"));

            if(q>= stoi(inputQuantity)){
                q = q - stoi(inputQuantity);
                unordered_map<string, string> medicineMap;          //hashmap of a medicine
                medicineMap["Name"] = med.at("Name");
                medicineMap["Expiry"] = med.at("Expiry");
                medicineMap["Cost"] = med.at("Cost");
                medicineMap["Quantity"] = to_string(q);
                medsList.remove(med);
                medsList.push_back(medicineMap);        //reducing the quantity of total medicines from the medicines list
                medicineMap["Quantity"] = std::to_string(stoi(inputQuantity));
                cart.push_back(medicineMap);           //medicine is added to cart
                count++;
                cout << inputName << " has been added to your cart " << endl;
                break;
            }
            else{
                cout << "Insufficient amount of " << inputName << " in current medicine stock" << endl;
                count++;
                break;
            }
        }
    }
    if(count == 0){
        cout << inputName << " is not in the pharmacy!" << std::endl;
    }
    menu(type, medsList, cart);
}

//method for viewing all the medicines present in the pharmacy
void medicineType::view_medicines(medicineType type, list<unordered_map<std::string, std::string>> medsList, list<unordered_map<std::string, std::string>> cart) {
    cout << "Medicines present in the pharmacy stock:" << endl;
    for (const unordered_map<string, string>&med : medsList)
    {
        string n = med.at("Name");
        string e = med.at("Expiry");
        string c = med.at("Cost");
        string q = med.at("Quantity");
        cout << "Name: " << n << ", " << "Expiry date: " << e << ", " << "Cost: " << c << ", " << "Quantity: " << q << endl;
    }
    if(choice==2){
        menu(type, medsList, cart);
    }
    else if(choice==3){
        adminMenu(type, medsList, cart);
    }
}

//method to add new medicines to the pharmacy's stock of medicines
void medicineType::add(int num, medicineType type, list<unordered_map<std::string, std::string>> medsList, list<unordered_map<std::string, std::string>> cart) {
    string name, expiry, quantity, cost;
    for(int i = 1; i <= num; i++){
        cout << "New medicine" << endl;
        cout << "Enter name: " << endl;
        cin >> name;
        cout << "Enter expiry date: " << endl;
        cin >> expiry;
        cout << "Enter quantity: " << endl;
        cin >> quantity;
        cout << "Enter cost: " << endl;
        cin >> cost;

        unordered_map<string, string> medicineMap;       //hashmap of a medicine
        medicineMap["Name"] = name;
        medicineMap["Expiry"] = expiry;
        medicineMap["Cost"] = cost;
        medicineMap["Quantity"] = quantity;

        medsList.push_back(medicineMap);
    }
    cout << "Medicines added successfully!" << endl;
    adminMenu(type, medsList, cart);
}

//method to remove medicines from the pharmacy's medicine stock
void medicineType::deleteMed(const string &inputName, medicineType type, list<unordered_map<std::string, std::string>> medsList, list<unordered_map<std::string, std::string>> cart) {
    int count = 0;
    for (const unordered_map<string, string>&med : medsList)
    {
        if(med.at("Name") == inputName) {
            medsList.remove(med);      //removing the medicine from list of medicines
            count++;
            cout << "Successfully deleted " << inputName << " from list of medicines" << endl;
            break;
        }
    }
    if(count == 0){
        cout << inputName << " is not in the pharmacy!" << std::endl;
    }
    adminMenu(type, medsList, cart);
}

//method to update the pharmacy's current medicines data
void medicineType::update(const string &inputName, medicineType type, list<unordered_map<std::string, std::string>> medsList, list<unordered_map<std::string, std::string>> cart) {
    int count = 0;
    for (const unordered_map<string, string>&med : medsList)
    {
        string newName, newExpiry, newCost, newQuantity;
        if(med.at("Name") == inputName) {
            cout << "Enter new name of medicine: " << endl;
            cin >> newName;
            cout << "Enter new expiry date of medicine: " << endl;
            cin >> newExpiry;
            cout << "Enter new cost of medicine: " << endl;
            cin >> newCost;
            cout << "Enter new quantity of medicine: " << endl;
            cin >> newQuantity;
            medsList.remove(med);

            unordered_map<string, string> medicineMap;    //hashmap of a medicine
            medicineMap["Name"] = newName;
            medicineMap["Expiry"] = newExpiry;
            medicineMap["Cost"] = newCost;
            medicineMap["Quantity"] = newQuantity;

            medsList.push_back(medicineMap);     //updated data is added to list of medicines
            count++;
            cout << "Successfully updated!" << endl;
            break;
        }
    }
    if(count == 0){
        cout << inputName << " is not in the pharmacy!" << std::endl;
    }
    adminMenu(type, medsList, cart);
}

//to view all the medicines which have been added to cart
void medicineType::viewCart(medicineType type, const list<unordered_map<std::string, std::string>>& medsList, list<unordered_map<std::string, std::string>> cart) {
    cout << "CART:" << endl;
    for (const unordered_map<string, string>&med : cart)
    {
        string n = med.at("Name");
        string e = med.at("Expiry");
        string c = med.at("Cost");
        string q = med.at("Quantity");
        cout << "Name: " << n << ", " << "Expiry date: " << e << ", " << "Cost: " << c << ", " << "Quantity: " << q << endl;
    }
    menu(type, medsList, cart);
}

//method to remove a medicine from the cart
void medicineType::deleteFromCart(const string &inputName, medicineType type, list<unordered_map<std::string, std::string>> medsList, list<unordered_map<std::string, std::string>> cart) {
    int count = 0;
    for (const unordered_map<string, string>&medC : cart)
    {
        int inputQuantity = stoi(medC.at("Quantity"));

        for (const unordered_map<string, string>&med : medsList)
        {
            if(medC.at("Name") == inputName) {
                if(med.at("Name") == inputName) {
                    int q = stoi(med.at("Quantity"));
                    q = q + inputQuantity;
                    unordered_map<string, string> medicineMap;          //hashmap of a medicine
                    medicineMap["Name"] = med.at("Name");
                    medicineMap["Expiry"] = med.at("Expiry");
                    medicineMap["Cost"] = med.at("Cost");
                    medicineMap["Quantity"] = to_string(q);
                    medsList.remove(med);
                    medsList.push_back(medicineMap);        //increasing the quantity of total medicines in the medicines list

                    cart.remove(medC);         //medicine is removed from cart
                    count++;
                    cout << inputName << " has been removed from your cart " << endl;
                    break;
                }
            }

        }
    }
    if(count == 0){
        cout << inputName << " is not in the cart!" << std::endl;
    }
    menu(type, medsList, cart);
}

//method to generate bill and checkout
void medicineType::generateBill(medicineType medicine, list<unordered_map<std::string, std::string>> medsList, list<unordered_map<std::string, std::string>> cart) {
    cout << "BILL:" << endl;
    int bill = 0;
    for (const unordered_map<string, string>&med : cart)
    {
        string n = med.at("Name");
        string c = med.at("Cost");
        string q = med.at("Quantity");
        cout << "Name: " << n << ", " << "Quantity: " << q << ", " << "Total cost of medicine: " << stoi(c)* stoi(q) << endl;
        bill = bill + stoi(c)* stoi(q);
        medicine.amount = medicine.amount + bill;
        cart.remove(med);    //emptying the cart
    }
    cout << "Total: " << bill << endl;
    cout << "Successfully checked out! Cart is now empty" << endl;
    menu(medicine, std::move(medsList), cart);
}

//to exit the pharmacy
void medicineType::exitToLogin(medicineType medicine2, list<unordered_map<std::string, std::string>> medicines, list<unordered_map<std::string, std::string>> cart) {
    login(medicine2, medicines, cart);
}

void medicineType::amountGenerated(medicineType type, list<unordered_map<std::string, std::string>> medsList, list<unordered_map<std::string, std::string>> cart) {
    cout << "Total revenue generated: " << type.amount << endl;
    adminMenu(type, medsList, cart);
}

void medicineType::exit() {
    exit();
}

//menu to display all the operations which can be performed
void medicineType::menu(medicineType medicine, list<unordered_map<std::string, std::string>> medsList, list<unordered_map<std::string, std::string>> cart) {
    int menu;
    cout << "MENU:" << endl;
    cout << "1. For ordering medicines" <<endl;
    cout << "2. For viewing cart" <<endl;
    cout << "3. To remove medicines from cart" <<endl;
    cout << "4. To generate bill and checkout" <<endl;
    cout << "5. For viewing all medicines" <<endl;
    cout << "6. To logout" <<endl;
    cout << "7. To exit" <<endl;
    cout << "Enter choice: ";
    cin >> menu;

    string inputName;

    switch(menu){
        case 1:
        {
            cout << "Enter name of medicine to order: " << endl;
            cin >> inputName;
            medicine.take_order(inputName, medicine, medsList, cart);
            break;
        }
        case 2:
        {
            medicine.viewCart(medicine, medsList, cart);
            break;
        }
        case 3:
        {
            //remove from cart
            cout << "Enter name of medicine to remove from the cart: " << endl;
            cin >> inputName;
            medicine.deleteFromCart(inputName, medicine, medsList, cart);
            break;
        }
        case 4:
        {
            medicine.generateBill(medicine, medsList, cart);
            break;
        }
        case 5:
        {
            medicine.view_medicines(medicine, medsList, cart);
            break;
        }
        case 6:
        {
            medicine.exitToLogin(medicine, medsList, cart);
            break;
        }
        case 7:
        {
            cout<< "Thank you!" << endl;
            medicine.exit();
            break;
        }
        default:
        {
            cout << "Please enter a valid option number" << endl;
            medicine.menu(medicine, medsList, cart);
        }
    }
}

void medicineType::adminMenu(medicineType medicine, list<unordered_map<std::string, std::string>> medsList, list<unordered_map<std::string, std::string>> cart) {
    int menu;
    cout << "MENU:" << endl;

    cout << "1. For viewing all medicines" <<endl;
    cout << "2. For adding new medicines" <<endl;
    cout << "3. For deleting any medicines" <<endl;
    cout << "4. For updating current medicines" <<endl;
    cout << "5. For displaying total amount generated" <<endl;
    cout << "6. To logout" <<endl;
    cout << "7. To exit" <<endl;
    cout << "Enter choice: ";
    cin >> menu;

    string inputName;

    switch(menu){

        case 1:
        {
            medicine.view_medicines(medicine, medsList, cart);
            break;
        }
        case 2:
        {
            int num;
            cout << "How many medicines would you like to add: " << endl;
            cin >> num;
            medicine.add(num, medicine, medsList, cart);
            break;
        }
        case 3:
        {
            cout << "Enter name of medicine to delete: " << endl;
            cin >> inputName;
            medicine.deleteMed(inputName, medicine, medsList, cart);
            break;
        }
        case 4:
        {
            cout << "Enter name of medicine to update: " << endl;
            cin >> inputName;
            medicine.update(inputName, medicine, medsList, cart);
            break;
        }
        case 5:
        {
            medicine.amountGenerated(medicine, medsList, cart);
            break;
        }
        case 6:
        {
            medicine.exitToLogin(medicine, medsList, cart);
            break;
        }
        case 7:
        {
            cout<< "Thank you!" << endl;
            medicine.exit();
            break;
        }
        default:
        {
            cout << "Please enter a valid option number" << endl;
            medicine.menu(medicine, medsList, cart);
        }
    }
}

void medicineType::login(medicineType medicine2, list<unordered_map<std::string, std::string>> medicines, list<unordered_map<std::string, std::string>> cart){
    string uname, pass;
    cout << "WELCOME TO THE PHARMACY" <<endl;
    cout << "\n1. to Register" <<endl;
    cout << "2. to Login "<<endl;
    cout << "3. to Login as admin" <<endl;
    cout << "4. to Exit\nEnter choice: " <<endl;
    cin >> medicine2.choice;
    switch(medicine2.choice){
        case 1:
        {
            cout << "Enter the username :";
            cin >> uname;
            cout << "Enter the password :";
            cin >> pass;

            ofstream file;
            file.open("C:\\Users\\RIYA WAIRAGADE\\Desktop\\pharmacy\\" + uname + ".txt");
            file<<uname<<endl<<pass;
            file.close();

            login(medicine2, medicines, cart);
        }

        case 2:
        {
            bool status =userLogin();

            if(!status)
            {
                cout<<"Invalid username or password. Please try again. \n"<<endl;
                login(medicine2, medicines, cart);
            }
            else
            {
                cout<<"Log in successful! \n"<<endl;
                medicine2.menu(medicine2, medicines, cart);
            }
        }
        case 3:
        {
            bool status =adminLogin();

            if(!status)
            {
                cout<<"Invalid username or password. Please try again.\n"<<endl;
                login(medicine2, medicines, cart);
            }
            else
            {
                cout<<"Log in successful!\n"<<endl;
                medicine2.adminMenu(medicine2, medicines, cart);
            }

        }
        case 4:
        {
            cout<< "Thank you!" << endl;
            medicine2.exit();
        }
        default:
        {
            cout << "Please enter a valid option number" << endl;
            login(medicine2, medicines, cart);
        }
    }
}

int main() {
    medicineType medicine2;
    list<unordered_map<string, string>> medicines;
    list<unordered_map<string, string>> cart;

    unordered_map<string, string> medicineMap1;       //hashmap of a medicine
    medicineMap1["Name"] = "Crocin";
    medicineMap1["Expiry"] = "05:11:2023";
    medicineMap1["Cost"] = "30";
    medicineMap1["Quantity"] = "100";
    medicines.push_back(medicineMap1);

    unordered_map<string, string> medicineMap2;       //hashmap of a medicine
    medicineMap2["Name"] = "Vicks";
    medicineMap2["Expiry"] = "28:08:2024";
    medicineMap2["Cost"] = "5";
    medicineMap2["Quantity"] = "500";
    medicines.push_back(medicineMap2);

    unordered_map<string, string> medicineMap3;       //hashmap of a medicine
    medicineMap3["Name"] = "Pantocid";
    medicineMap3["Expiry"] = "09:10:2022";
    medicineMap3["Cost"] = "400";
    medicineMap3["Quantity"] = "300";
    medicines.push_back(medicineMap3);

    unordered_map<string, string> medicineMap4;       //hashmap of a medicine
    medicineMap4["Name"] = "Ambrodil";
    medicineMap4["Expiry"] = "17:03:2023";
    medicineMap4["Cost"] = "80";
    medicineMap4["Quantity"] = "60";
    medicines.push_back(medicineMap4);

    medicine2.login(medicine2, medicines, cart);
}