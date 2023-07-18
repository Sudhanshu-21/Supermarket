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
        
        cout<<"____Welcome to Supermarket____"<<endl;
        start:
        cout<<"Select your Identity"<<endl;
        cout<<"1) Administrator"<<endl;
        cout<<"2) Costumer"<<endl;
        cout<<"3) Exit"<<endl;
        int choice;
        cin>>choice;
        switch (choice) { 
            case 1:
                if(administrator() == false){
                    goto start;
                }
                break;

            case 2:
                if(bool() == true){
                    goto start;
                }
                break;

            case 3:
                exit(0);

            default:
                cout<<"Invalid Selection"<<endl;
                cout<<"Select again"<<endl;
                goto start;
        }
    }
    
};




bool supermarket :: administrator(){
    cout<<"Login"<<endl;
    cout<<"Email: ";
    cin>>e;
    cout<<"Password: ";
    cin>>p;
    a.login(e, p);
    if(a.verification(e, p) == true){
        cout<<"Logged in Successfully!"<<endl;
        option:
        cout<<"Select one of the choices"<<endl;
        cout<<"1) Add Item"<<endl;
        cout<<"2) Modify Item"<<endl;
        cout<<"3) Remove Item"<<endl;
        cout<<"4) Exit"<<endl;
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
                cout<<"Enter product code"<<endl;
                cin>>rc;
                a.remove(rc);
                break;
            case 4:
                return false;
                break;
            default:
                cout<<"None of the options selected"<<endl;
                goto option;
        }
        goto option;
    }
    else{
        cout<<"Invalid Credentials"<<endl;
        return false;
    }
    return true;
}


bool supermarket :: guest(){
    cout<<"Provide Customer Details"<<endl;
                cout<<"Name: ";
                cin>>cn;
                cout<<"Age: ";
                cin>>ca;
                cout<<"Mobile Number: ";
                cin>>cmob;
                cout<<"Address: ";
                cin>>cadd;
                cout<<"-------"<<endl;
                
                select:
                cout<<"____List of Items___"<<endl;
                cout<<"\t\t\tCode\t\t\tname\t\t\tStock\t\t\tPrice\t\t\tDiscount"<<endl;
                for(auto i:mp){
                    displayItem(i.first);
                }
                cout<<"Select one of the Items by entering code"<<endl;
                cin>>code;
                if(mp.find(code) != mp.end()){
                    cout<<"Enter quantity: ";
                    int quant;
                    cin>>quant;
                    if(quant<=mp[code].getStock()){
                        id.addItems(code, quant);
                        //user.id.addItems(mp[code], quant);
                        
                        // -------------------------------STOCK update--------------------------------------
                        a.updateStock(mp[code].getStock()-quant, code);
                        cout<<mp[code].getName()<<" added to your list"<<endl;
                        check:
                        cout<<"Press y to add more items\n Press n to remove item\n Press any other key to checkout"<<endl;
                        cin>>more;
                        if(more == 'y'){
                            goto select;
                        }
                        else if(more == 'n'){
                            cout<<"Enter the code of item to be removed"<<endl;
                            cin>>ri;
                            id.removeItems(ri);
                            a.updateStock(mp[ri].getStock()+quant, ri);
                            cout<<mp[ri].getName()<<" removed from your list"<<endl;
                            goto check;
                        }
                        else{
                            //-----------------------CHECKOUT------------------------------------------------
                            cout<<"Proceeding to checkout"<<endl;
                            user.login(cn, ca, cmob, cadd, id);
                            user.printReciept();
                            return true;
                        }
                    }
                    else{
                        cout<<"Sorry! this much quantity is not available."<<endl;
                        goto select;
                    }
                }
                else{
                    cout<<"Invalid Selection"<<endl;
                    cout<<"Select again"<<endl;
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
    cout<<"Enter product code"<<endl;
    cin>>c;
    auto it = mp.find(c);
    if(it != mp.end()){
        cout<<"Product is already added"<<endl;
        cout<<"\t\t\tCode\ttname\t\tStock\t\tPrice\t\tDiscount"<<endl;
        displayItem(it->first);
        cout<<"If you want to modify this item press y"<<endl;
        char y;
        cin>>y;
        if(y == 'y'){
            modify();
        }
        else{
            cout<<"Operation terminated"<<endl;
            cout<<"Enter another product"<<endl;
            goto add;
        }
    }
    cout<<"Enter product name"<<endl;
    cin>>n;
    cout<<"Enter product stock"<<endl;
    cin>>s;
    cout<<"Enter product price"<<endl;
    cin>>p;
    cout<<"Enter product discount"<<endl;
    cin>>d;
    item i;
    i.setItem(c, n, s, p, d);
    mp[c]=i;
    cout<<"Item is added"<<endl;
} 

void admin :: modify(){
    int c;
    string n;
    int s; 
    float p;
    float d;
    cout<<"Enter product code"<<endl;
    cin>>c;
    auto it = mp.find(c);
    if(it != mp.end()){
        again:
        cout<<"What do you want to modify?"<<endl;
        cout<<" 1) Name of product"<<endl;
        cout<<" 2) Stock of product"<<endl;
        cout<<" 3) Price of product"<<endl;
        cout<<" 4) Discount of product"<<endl;
        cout<<"Press any other key to exit"<<endl;
        cout<<"Enter your choice ";
        int choice;
        cin>>choice;
        switch(choice){
            case 1:
                cout<<"Enter Name"<<endl;
                cin>>n;
                it->second.setName(n);
                cout<<"Name is modified"<<endl;
                break;
             case 2:
                cout<<"Enter Stock"<<endl;
                cin>>s;
                it->second.setStock(s);
                cout<<"Stock is modified"<<endl;
                break;
             case 3:
                cout<<"Enter Price"<<endl;
                cin>>p;
                it->second.setPrice(p);
                cout<<"Price is modified"<<endl;
                break;
             case 4:
                cout<<"Enter Discount"<<endl;
                cin>>d;
                it->second.setDiscount(d);
                cout<<"Discount is modified"<<endl;
                break;
            default:
                cout<<"Invalid selection"<<endl;
                return;
        }
        goto again;
    }
    else{
        cout<<"No such product exist"<<endl;
        cout<<"If you want to add this item press y"<<endl;
        char y;
        cin>>y;
        if(y == 'y'){
            add();
        }
        else{
            cout<<"Operation terminated"<<endl;
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
        cout<<"Product is removed"<<endl;
    }
    else{
        cout<<"No such product exist"<<endl;
        cout<<"Operation terminated"<<endl;
    }
}


void customer :: printReciept(){
    float total = 0;
    float amount = 0;
    cout<<"-------------------RECIEPT-----------------------"<<endl;
    cout<<"Name: "<<name<<endl;
    cout<<"Age: "<<age<<endl;
    cout<<"Mobile Number: "<<num<<endl;
    cout<<"Address: "<<address<<endl<<endl;
    cout<<"\t\tCode\t\tname\t\t\tPrice\t\tDiscount\t\tQuantity\t\tAmount"<<endl;
    list<pair<int, int>> temp = getOrder().items;
    for(auto i : temp){
        amount = calculate(i.first, i.second);
        total+=amount;
        cout<<"\t\t"<<i.first<<"\t\t\t"<<mp[i.first].getName()<<"\t\t\t"<<mp[i.first].getPrice()<<"\t\t\t"<<mp[i.first].getDiscount()<<"\t\t\t"<<i.second<<"\t\t\t"<<amount<<endl;
    }
    cout<<"\tTotal Amount:\t\t\t\t\t\t\t\t\t"<<total<<endl;
    cout<<"ThankYou for shopping from us!"<<endl;
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
    customer cust;
    order ord;
    ord.addItems(1, 2);
    ord.addItems(2, 2);
    cust.login("sud", 34, "34566", "hhdf", ord);   
    cust.printReciept();            
    supermarket sp;
    sp.display();

    return 0;
}