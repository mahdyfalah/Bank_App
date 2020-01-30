#ifndef KONTO_H
#define KONTO_H

#include<iostream>
#include<string>
#include<vector>
#include<memory>
using namespace std;

static int current_accnumb{1};

class Person;

class Account : public enable_shared_from_this<Account>{
  int number;
  vector<weak_ptr<Person>> authorized_persons;
  int balance{0};
  int overdraft{0};
  double fees{0};
public :
  Account(shared_ptr<Person>);
  virtual ~Account() { }
  int get_number();
  bool add_person(shared_ptr<Person>);
  virtual void transfer(int, shared_ptr<Account>) = 0;
  void set_balance(int n){balance = n;}
  void set_overdraft(int n){overdraft = n;}
  void set_balance(double d){fees = d;}
  int get_balance(){return balance;}
  int get_overdraft(){return overdraft;}
  double get_fees(){return fees;}
  void add_fee(double d) {fees += d;}
  virtual void set_fee(double d) = 0;
  ostream& print(ostream&) const;
  vector<weak_ptr<Person>> get_authorized_list(){return authorized_persons;}
  bool max_authorized() const { return authorized_persons.size() == static_cast<size_t>(10); }
};


class GiroAccount : public Account{
  double tr_fee{0};
public:
  GiroAccount(shared_ptr<Person>);
  void set_fee(double);
  void transfer(int, shared_ptr<Account>);
};

class BusinessAccount : public Account{
  double intrest{0};
public:
  BusinessAccount(shared_ptr<Person>);
  void set_fee(double);
  void transfer(int, shared_ptr<Account>);
};
ostream& operator<<(ostream&, const Account&);
#endif


