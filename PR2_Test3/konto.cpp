#include<iostream>
#include<string>
#include<algorithm>
#include<memory>
#include<vector>
#include"konto.h"
using namespace std;

Account::Account(shared_ptr<Person> auth){
  weak_ptr<Person> pers_ptr = auth;
  authorized_persons.push_back(pers_ptr);    
  number = current_accnumb++;
}


int Account::get_number(){return number;}


bool Account::add_person(shared_ptr<Person> pers){
  if (max_authorized()) throw runtime_error("10 person!");
  auto find_p = count_if(authorized_persons.begin(), authorized_persons.end(),
                        [&pers](const weak_ptr<Person>& wp){ return pers == wp.lock(); }
                        );
  if(find_p != 0) {
    return false;
  } else {
    authorized_persons.push_back(pers);
    return true;
  }
}

GiroAccount::GiroAccount(shared_ptr<Person> auth): Account(auth), tr_fee{0} {}

void GiroAccount::set_fee(double d){
  tr_fee = d;
}

void GiroAccount::transfer(int amount, shared_ptr<Account> k){
 if((amount < get_overdraft() + get_balance()) && amount > 0){
    set_balance(get_balance() - amount);
    k->set_balance((k->get_balance()) + amount);
    Account::add_fee(tr_fee);
  }else{
    cout << "not possible!" << endl;
  }
}


BusinessAccount::BusinessAccount(shared_ptr<Person> auth): Account(auth), intrest{0} {}

void BusinessAccount::set_fee(double d){
  intrest = d;
}
void BusinessAccount::transfer(int amount, shared_ptr<Account> k){
  if((amount < get_overdraft() + get_balance()) && amount > 0){
    set_balance(get_balance() - amount);
    k->set_balance((k->get_balance()) + amount);
    double tr_fee{ (static_cast<double>(intrest*amount)) / 100};
    Account::add_fee(tr_fee);
  }else{
    cout << "not possible!" << endl;
  }
  
}


ostream& Account::print(ostream& o) const{
  o <<"["<<"id: "<<number<<", balance: "<<balance<<", fees: "<<fees<<", overdraft: "<<overdraft<<"]";
  return o;
}


ostream& operator<<(ostream& o, const Account& a){return a.print(o); }





