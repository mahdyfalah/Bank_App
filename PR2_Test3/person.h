#ifndef PERSON_H
#define PERSON_H

#include<iostream>
#include<string>
#include<vector>
#include<memory>
#include"konto.h"
using namespace std;

class Account;

class Person : public enable_shared_from_this<Person>{
  string name;
  vector<shared_ptr<Account>> accounts;
public:
  Person(string);
  ~Person() { }
  string get_name() const;
  int add_account(int);
  bool share(shared_ptr<Person>, shared_ptr<Account>);
  bool has_authority(shared_ptr<Account>);
  bool give_up_account(shared_ptr<Account>);
  void delete_account(shared_ptr<Account>);
  ostream& print(ostream&) const;
  ostream& print_small(ostream&) const;
  const vector<shared_ptr<Account>>& get_accounts() const;
  shared_ptr<Account> get_account(size_t i) const;
};
ostream& operator<<(ostream&, const Person&);

#endif


