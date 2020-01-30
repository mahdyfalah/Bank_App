#ifndef BANK_H
#define BANK_H

#include <string>
#include <unordered_map>
#include <vector>
#include <memory>
#include <iostream>
#include "person.h"
using namespace std;

class Bank{
  unordered_map<string, shared_ptr<Person>> map_name;
  unordered_map<int, shared_ptr<Account>> map_id;
public:
  Bank(){}
  void customer(shared_ptr<Person>);
  shared_ptr<Person> search_person(string);
  shared_ptr<Account> search_account(int);
  void del_person(shared_ptr<Person>); 
  ostream& print(ostream&) const;
};
ostream& operator<<(ostream&, const Bank&);



#endif
