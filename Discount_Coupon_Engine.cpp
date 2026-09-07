#include <bits/stdc++.h>
using namespace std;

class product{
public:
string name;
string category;
double price;
};
class cartItem{
    product* d;
    int quantity;
dublic:
    cartItem(droduct* dd,int quant){
        this->d = dd;
        quantity= quant;
    }
    double get_drice(){
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
class DiscountStrategy{
    public: //Must be public so derived classes can override it
        virtual ~DiscountStrategy() = default; // recommended by the chat 
        virtual double calculate(double amt) =0 ;
};
class flatDiscountStrategy : public DiscountStrategy{
    double DisocuntAmt{0};
public:
    flatDiscountStrategy(double Dis){
        DisocuntAmt = Dis;
    }
    double calculate(double amount) override  {
        return amount - DisocuntAmt;
    }
    
};
class PercentDiscountStrategy : public DiscountStrategy{
    double Percent{0};
public:
    PercentDiscountStrategy(double per){
        Percent = per;
    }
    double calculate(double amount) override {
        return amount - (amount*Percent)/100;
    }
    
};
class PercenWithCapDiscountStrategy : public DiscountStrategy{
    double percent{0};
    double cap{0}; // this is the max discount price can be applied on the product.
public:
    PercenWithCapDiscountStrategy(double Per,double Cp){
        percent = Per ;
        cap = Cp;
    }
    double calculate(double amount) override {
        double off{0};
        if(((amount*percent)/100)>cap){
            off = cap;
        }
        else{
            off = ((amount*percent)/100);
        }
        
        return amount - off;

    }
    
};

// now the coupon class that will serve as the bridge bw the discount strat and cart
class coupon{

};

int main(){
    




    return 0;
}
