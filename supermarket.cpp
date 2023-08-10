#include<iostream>
#include<map>
#include<string.h>
#include<list>

using namespace std;

class item{
    int code;
    string name;
    int stock; 
    float price;
    float discount;

    public:
    item(){
        code = -1;
        name = "";
        stock = -1;
        price = -1;
        discount = -1;
    }
    void setItem(int c, string n, int s, float p, float d){
        code = c;
        name = n;
        stock = s;
        price = p;
        discount = d;
    }
    void setName(string n){
        name = n;
    }
    void setStock(int s){
        stock = s;
    }
    void setPrice(float p){
        price = p;
    }
    void setDiscount(float d){
        discount = d;
    }
    int getCode(){
        return code;
    }
    string getName(){
       return name;
    }
    int getStock(){
        return stock;
    }
    float getPrice(){
        return price;
    }
    float getDiscount(){
        return discount;
    }
};

map<int, item> mp;


void displayItem(int c){
    auto i = mp.find(c);
    
    cout<<"\t\t\t"<<i->first<<"\t\t\t"<<i->second.getName()<<"\t\t\t"<<i->second.getStock()<<"\t\t\t"<<i->second.getPrice()<<"\t\t\t"<<i->second.getDiscount()<<endl;
}


class admin{
    string email;
    string password;

    public:
    admin(){
        email = "";
        password = "";

    }
    void login(string Email, string Password){
        email = Email;
        password = Password;
    }
    bool verification(string e, string p){
        if(e == "qwer" && p == "asdf"){
            return true;
        }
        return false;
    };
    void add();
    void modify();
    void updateStock(int s, int c);
    void remove(int c);
};


class order {
    public:
    list<pair<int, int>> items;
    order(){
       
    }
    void addItems(int i, int q){
        pair<int, int> product = {i, q};
        items.push_back(product);
    }
    void removeItems(int code){
        items.remove_if([code](const std::pair<int, int>& p) {           
            return p.first == code;
        });        
    }
};


class customer{
    string name;
    int age;
    string num;
    string address;
    order orders;

    public:
    customer(){
        name = "";
        age = 0;
        num = "";
        address = "";
    }
    void login(string n, int Age, string Num, string add, order id){
        name = n;
        age = Age;
        num = Num;
        address = add;
        orders = id;
    }
    string getName(){
        return name;
    }
    int getAge(){
        return age;
    }
    string getNum(){
        return num;
    }
    string getAdd(){
        return address;
    }
    order getOrder(){
        return orders;
    }
    void printReciept();
    float calculate(int c, int q);
};



class supermarket{
    
    public:

    string e, p;
    int c, rc, code, ri;
    admin a;
    string cn, cadd, cmob;
    char more;
    int ca;
    order id;
    customer user;

    bool administrator();
    bool guest();
    void display(){
        cout<<"\t\t\t**********************************************************\n\n";
        cout<<"\t\t\t\t\t____Welcome to Supermarket____"<<endl;
        cout<<"\n\t\t\t**********************************************************\n";
        start:
        cout<<"\t\t\tSelect your Identity\n\n"<<endl;
        cout<<"\t\t\t1) Administrator\n"<<endl;
        cout<<"\t\t\t2) Costumer\n"<<endl;
        cout<<"\t\t\t3) Exit\n\n\n"<<endl;
        int choice;
        cin>>choice;
        switch (choice) { 
            case 1:
                if(administrator() == false){
                    goto start;
                }
                break;

            case 2:
                if(guest() == true){
                    goto start;
                }
                break;

            case 3:
                exit(0);

            default:
                cout<<"\t\t\tInvalid Selection\n"<<endl;
                cout<<"\t\t\tSelect again\n\n"<<endl;
                goto start;
        }
    }
    
};




bool supermarket :: administrator(){
    cout<<"\t\t\tLogin"<<endl;
    cout<<"\t\t\tEmail: ";
    cin>>e;
    cout<<"\t\t\tPassword: ";
    cin>>p;
    a.login(e, p);
    if(a.verification(e, p) == true){
        cout<<"\t\t\tLogged in Successfully!\n\n"<<endl;
        cout<<"\t\t\t\t\t\t____List of Items___"<<endl;
        cout<<"\t\t\tCode\t\t\tname\t\t\tStock\t\t\tPrice\t\t\tDiscount"<<endl;
        for(auto i:mp){
            displayItem(i.first);
        }
        option:
        cout<<"\n\t\t\tSelect one of the choices"<<endl;
        cout<<"\t\t\t1) Add Item"<<endl;
        cout<<"\t\t\t2) Modify Item"<<endl;
        cout<<"\t\t\t3) Remove Item"<<endl;
        cout<<"\t\t\t4) Exit\n\n"<<endl;
        int option;
        cin>>option;
        switch(option){
            case 1:
                a.add();
                break;
            case 2:
                a.modify();
                break;
            case 3:
                cout<<"\t\t\tEnter product code"<<endl;
                cin>>rc;
                a.remove(rc);
                break;
            case 4:
                return false;
                break;
            default:
                cout<<"\t\t\tNone of the options selected"<<endl;
                goto option;
        }
        goto option;
    }
    else{
        cout<<"\t\t\tInvalid Credentials"<<endl;
        return false;
    }
    return true;
}


bool supermarket :: guest(){
    cout<<"\t\t\tProvide Customer Details"<<endl;
                cout<<"\t\t\tName: ";
                cin>>cn;
                cout<<"\t\t\tAge: ";
                cin>>ca;
                cout<<"\t\t\tMobile Number: ";
                cin>>cmob;
                cout<<"\t\t\tAddress: ";
                cin>>cadd;
                cout<<"-------"<<endl;
                
                select:
                cout<<"\t\t\t\t\t\t____List of Items___"<<endl;
                cout<<"\t\t\tCode\t\t\tname\t\t\tStock\t\t\tPrice\t\t\tDiscount"<<endl;
                for(auto i:mp){
                    displayItem(i.first);
                }
                cout<<"\t\t\tSelect one of the Items by entering code"<<endl;
                cin>>code;
                if(mp.find(code) != mp.end()){
                    cout<<"\t\t\tEnter quantity: ";
                    int quant;
                    cin>>quant;
                    if(quant<=mp[code].getStock()){
                        id.addItems(code, quant);
                        //user.id.addItems(mp[code], quant);
                        
                        // -------------------------------STOCK update--------------------------------------
                        a.updateStock(mp[code].getStock()-quant, code);
                        cout<<"\t\t\t"<<mp[code].getName()<<" added to your list"<<endl;
                        check:
                        cout<<"\t\t\tPress y to add more items\n Press n to remove item\n Press any other key to checkout"<<endl;
                        cin>>more;
                        if(more == 'y'){
                            goto select;
                        }
                        else if(more == 'n'){
                            cout<<"\t\t\tEnter the code of item to be removed"<<endl;
                            cin>>ri;
                            id.removeItems(ri);
                            a.updateStock(mp[ri].getStock()+quant, ri);
                            cout<<"\t\t\t"<<mp[ri].getName()<<" removed from your list"<<endl;
                            goto check;
                        }
                        else{
                            //-----------------------CHECKOUT------------------------------------------------
                            cout<<"\n\n\t\t\tProceeding to checkout\n\n"<<endl;
                            user.login(cn, ca, cmob, cadd, id);
                            user.printReciept();
                            return true;
                        }
                    }
                    else{
                        cout<<"\t\t\tSorry! this much quantity is not available."<<endl;
                        goto select;
                    }
                }
                else{
                    cout<<"\t\t\tInvalid Selection"<<endl;
                    cout<<"\t\t\tSelect again\n\n"<<endl;
                    goto select;
                }
}


void admin :: add(){
    int c;
    string n;
    int s; 
    float p;
    float d;
    add:
    cout<<"\t\t\tEnter product code: ";
    cin>>c;
    auto it = mp.find(c);
    if(it != mp.end()){
        cout<<"\t\t\tProduct is already added"<<endl;
        cout<<"\t\t\tCode\ttname\t\tStock\t\tPrice\t\tDiscount"<<endl;
        displayItem(it->first);
        cout<<"\n\t\t\tIf you want to modify this item press y"<<endl;
        char y;
        cin>>y;
        if(y == 'y'){
            modify();
        }
        else{
            cout<<"\t\t\tOperation terminated"<<endl;
            cout<<"\t\t\tEnter another product"<<endl;
            goto add;
        }
    }
    cout<<"\t\t\tEnter product name: ";
    cin>>n;
    cout<<"\t\t\tEnter product stock: ";
    cin>>s;
    cout<<"\t\t\tEnter product price: ";
    cin>>p;
    cout<<"\t\t\tEnter product discount: ";
    cin>>d;
    item i;
    i.setItem(c, n, s, p, d);
    mp[c]=i;
    cout<<"\t\t\tItem is added"<<endl;
    cout<<"\t\t\t\t\t\t____List of Items___"<<endl;
    cout<<"\t\t\tCode\t\t\tname\t\t\tStock\t\t\tPrice\t\t\tDiscount"<<endl;
    for(auto i:mp){
        displayItem(i.first);
    }
} 

void admin :: modify(){
    int c;
    string n;
    int s; 
    float p;
    float d;
    cout<<"\t\t\tEnter product code"<<endl;
    cin>>c;
    auto it = mp.find(c);
    if(it != mp.end()){
        cout<<"\t\t\tCode\t\t\tname\t\t\tStock\t\t\tPrice\t\t\tDiscount"<<endl;
        displayItem(c);
        cout<<endl;
        again:
        cout<<"\t\t\tWhat do you want to modify?"<<endl;
        cout<<"\t\t\t 2) Stock of product"<<endl;
        cout<<"\t\t\t 1) Name of product"<<endl;
        cout<<"\t\t\t 3) Price of product"<<endl;
        cout<<"\t\t\t 4) Discount of product"<<endl;
        cout<<"\t\t\tPress any other key to exit"<<endl;
        cout<<"\t\t\tEnter your choice: ";
        int choice;
        cin>>choice;
        switch(choice){
            case 1:
                cout<<"\t\t\tEnter Name: ";
                cin>>n;
                it->second.setName(n);
                cout<<"\t\t\tName is modified: ";
                break;
             case 2:
                cout<<"\t\t\tEnter Stock: ";
                cin>>s;
                it->second.setStock(s);
                cout<<"\t\t\tStock is modified"<<endl;
                break;
             case 3:
                cout<<"\t\t\tEnter Price: ";
                cin>>p;
                it->second.setPrice(p);
                cout<<"\t\t\tPrice is modified"<<endl;
                break;
             case 4:
                cout<<"\t\t\tEnter Discount: ";
                cin>>d;
                it->second.setDiscount(d);
                cout<<"\t\t\tDiscount is modified"<<endl;
                break;
            default:
                cout<<"\n\t\t\tInvalid selection\n"<<endl;
                return;
        }
        cout<<"\t\t\t\t\t\t____List of Items___"<<endl;
        cout<<"\t\t\tCode\t\t\tname\t\t\tStock\t\t\tPrice\t\t\tDiscount"<<endl;
        for(auto i:mp){
            displayItem(i.first);
        }
        goto again;
    }
    else{
        cout<<"\t\t\tNo such product exist"<<endl;
        cout<<"\t\t\tIf you want to add this item press y"<<endl;
        char y;
        cin>>y;
        if(y == 'y'){
            add();
        }
        else{
            cout<<"\t\t\tOperation terminated"<<endl;
        }
    }
}


void admin :: updateStock(int s, int c){
    auto it = mp.find(c);
    it->second.setStock(s);
}


void admin :: remove(int c){
    auto it = mp.find(c);
    if(it != mp.end()){
        mp.erase(it);
        cout<<"\t\t\tProduct is removed\n"<<endl;
        cout<<"\t\t\t\t\t\t____List of Items___"<<endl;
        cout<<"\t\t\tCode\t\t\tname\t\t\tStock\t\t\tPrice\t\t\tDiscount"<<endl;
        for(auto i:mp){
            displayItem(i.first);
        }
    }
    else{
        cout<<"\t\t\tNo such product exist"<<endl;
        cout<<"\t\t\tOperation terminated\n"<<endl;
    }
}


void customer :: printReciept(){
    float total = 0;
    float amount = 0;
    cout<<"\t\t\t\t\t\t-------------------RECIEPT-----------------------"<<endl;
    cout<<"\t\t\tName: "<<name<<endl;
    cout<<"\t\t\tAge: "<<age<<endl;
    cout<<"\t\t\tMobile Number: "<<num<<endl;
    cout<<"\t\t\tAddress: "<<address<<endl<<endl;
    cout<<"\t\tCode\t\tname\t\t\tPrice\t\tDiscount\t\tQuantity\t\tAmount"<<endl;
    list<pair<int, int>> temp = getOrder().items;
    for(auto i : temp){
        amount = calculate(i.first, i.second);
        total+=amount;
        cout<<"\t\t"<<i.first<<"\t\t"<<mp[i.first].getName()<<"\t\t\t"<<mp[i.first].getPrice()<<"\t\t"<<mp[i.first].getDiscount()<<"\t\t\t"<<i.second<<"\t\t\t"<<amount<<endl;
    }

    cout<<"\n\n\t\tTotal Amount:\t\t\t\t\t\t\t\t\t\t\t\tRs. "<<total<<endl;
    cout<<"\n\t\t\t\t\t\tThankYou for shopping from us!\n"<<endl;
}


float customer :: calculate(int c, int q){
        float amount = 0;
        float dis = mp[c].getDiscount();
        float pr = mp[c].getPrice();
        float price = pr*(1 - (float)(dis/100));
        amount = price*q;
        return amount;
}


int main(){
    item i1, i2;
    i1.setItem(1, "Pencil", 10, 55, 4.5); 
    mp[1]=i1;                              
    i2.setItem(2, "Pen", 5, 40, 7.5);     
    mp[2]=i2;      
    // customer cust;
    // order ord;
    // ord.addItems(1, 2);
    // ord.addItems(2, 2);
    // cust.login("sud", 34, "34566", "hhdf", ord);   
    // cust.printReciept();            
    supermarket sp;
    sp.display();

    return 0;
}