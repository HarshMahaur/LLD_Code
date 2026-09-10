#include <bits/stdc++.h>
#include <mutex>
using namespace std;

class product{
    string name;
    string category;
    double price;
public:
    product(string n,string cat, double p){
        name = name;
        category= cat;
        price= p;
    }
    string get_name(){
        return name;
    }
    string get_category(){
        return category;
    }
    double get_price(){
        return price;
    }
};
class cartItem{
    product* p;
    int quantity;
public:
    cartItem(product* dd,int quant){
        this->p = dd;
        quantity= quant;
    }
    double get_price(){
        return p->get_price()*quantity;
    }
    product* get_product(){
        return p;
    }
};
class cart{
    vector<cartItem*> item;
    bool loyalityMember;
    double originalTotal;
    double finalTotal;
    string payment_bank; // added later.
public:
    string get_payment_bank(){
        return payment_bank;
    }
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
    bool get_loyality_Member(){
        return loyalityMember;
    }
    void addPDT(product* p,int q){
        cartItem* newcart = new cartItem(p,q);
        item.push_back(newcart); 
    }

    vector<cartItem*> get_iten_list(){
        return item;
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
//------------------------------------------------------------------
// stratergy design pattern implimentation in the discount stratergy;

// just realize that the base amount passed to the calculate ovveride function has to be under 32 bit.
// should have done - (amount/100)*percent.
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
        // return amount - DisocuntAmt; // 50 -100 = -50 (wrong) + have to return the amt that needed to be deducted.
        return min(DisocuntAmt,amount); // this amount it the base amount;
    }
    
};
class PercentDiscountStrategy : public DiscountStrategy{
    double Percent{0};
public:
    PercentDiscountStrategy(double per){
        Percent = per;
    }
    double calculate(double amount) override {
        // return amount - (amount*Percent)/100; // this will not return the tota amount ; it will return the amount thet is needed to be deducted from the base amt.
        return (amount*Percent)/100;
    }
    
};
class PercenWithUpperCapDiscountStrategy : public DiscountStrategy{
    double percent{0};
    double Amtcap{0}; // this is the max discount price can be applied on the product.
public:
    PercenWithUpperCapDiscountStrategy(double Per,double Cp){ // my class that set treashold for the baseamount for coupon to be applicable
        percent = Per ;
        Amtcap = Cp;
    }
    double calculate(double amount) override {
        double off{0};
        if(amount<Amtcap){
            std::cout<< "you are short on base amount you need item of Rs."<<Amtcap-amount<<" in your cart for this coupon to be applicable" <<std::endl;
            return 0;
        }
        return ((amount*percent)/100);
        


    }
    
};
class PercenWithCapDiscountStrategy : public DiscountStrategy{
    double percent{0};
    double cap{0}; // this is the min amount has to spend in order to apply coupon.
public:
    PercenWithCapDiscountStrategy(double Per,double Cp){
        percent = Per ;
        cap = Cp;
    }
    double calculate(double amount) override {
        double discount = (amount*percent)/100;
        if(cap<discount){
            std::cout<< "this coupon can not be applied. need at least "<<cap<<" amount to be applied" <<std::endl;
            return cap;
        }
        return discount;

    }
    
};

// now the coupon class that will serve as the bridge bw the discount strat and cart
class coupon{
    coupon* next;
public:
    coupon(){
        next = nullptr;
    } 
    virtual ~coupon(){
        if(next){
            delete next;
        }
    }
    coupon* get_next(){
        return next;
    }
    virtual double getDiscount(cart* c)=0;
    virtual bool isApplicable(cart* c)=0;
    virtual bool isCimbinable(cart* c){
        return true;
    }
    virtual string name()=0;
    void applyDiscount(cart* c){
        if(isApplicable(c)){
            double discount = getDiscount(c);

        }

    }

};

class BankingCoupon : public coupon{
    string bank;
    double minSpend,percent,off; // this is where the persent with cap will be used.
    DiscountStrategy* ds;
public:
    bool isApplicable(cart* c) override{
        return (c->get_payment_bank()==bank);
    }
    
    
};
class loyaltyDiscount : public coupon{
    double percent{0};
    
    DiscountStrategy* ds;
public:
    bool isApplicable(cart* c) override{
        return c->get_loyality_Member();
    }
    
    
    
};
class BulkPurchaseCoupon : public coupon{
    double threshold{0};
    double flatoff{0};
    DiscountStrategy* ds;
public:
    bool isApplicable(cart* c){
        double amt = c->get_originalTotal();
        return amt>=threshold;
    }
    
};
class SeasonalCoupon : public coupon{
    string catagory;
    double percent;
    DiscountStrategy* ds;
public:
    bool isApplicable(cart* c){
        for(cartItem* item : c->get_iten_list()){
            if(item->get_product()->get_category()==catagory){
                return true;
            }
        }
        return false;
    }

};

// ENUM class;
enum class S_type{ // enum class for the strategies
    FLAT,
    PERCENT,
    DISOCUNT,
    PERWITHUPPERCAP,
    PERWITHCAP
};
// coupon manager
class CouponManager{ // will have 1..* relation with coupon class.
    coupon* head;
    static CouponManager* instance;
    mutable mutex mtx; 

    //mutex mtx; // for thread safe things.
public:
    void registerCoupon(coupon* c){ 
        




    }

};

// disocunt stratergy manager 

int main(){
    




    return 0;
}
