#include <bits/stdc++.h>
using namespace std;

class product{
public:
string name;
string category;
double price;
};
class cartItem{
    product* p;
    int quantity;
public:
    cartItem(product* pd,int quant){
        this->p = pd;
        quantity= quant;
    }
    double get_price(){
        return p->price*quantity;
    }
};
class cart{
    vector<cartItem*> item;
    bool loyalityMember;
    double originalTotal;
    double finalTotal;
public:
    double get_originalTotal(){
        double total{0};
        for(auto c: item){
            total+=c->get_price();
        }
        originalTotal= total;
        return originalTotal;
    }
    double get_finalTotal(){
        return finalTotal;
    }
    void addPDT(product* p,int q){
        cartItem* newcart = new cartItem(p,q);
        item.push_back(newcart); 
    }

    void applyDiscount(double amt){ // this amt the final amt that we will get after applying the coupons on th original amount
        finalTotal= amt; // the work of calculation will be done by coupons(class).
    }
    ~cart(){
        for(auto c: item){
            delete c;
        }
    }
};

// stratergy design pattern implimentation in the discount stratergy;
class DiscountStratergy(){
        vitrual calculate(double amt);
};
class flatDiscount 

int main(){
    




    return 0;
}
