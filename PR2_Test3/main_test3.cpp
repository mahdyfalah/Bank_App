#include<iostream>
#include<string>
#include<vector>
#include<memory>
#include<algorithm>
#include"person.h"
#include"konto.h"
#include"bank.h"

using namespace std;

/*class Drawing(){
  vector<shared_ptr<Account>> pointers;
public:
  bool draw(int number){
    for(auto& it: poiters){
      lucky_number(number);
      return true;
    }
    return true;
  }
};*/



int main(){
//Aufgabe 1:
  Bank b;
//create person
  shared_ptr susi{make_shared<Person>("Susi")};
  shared_ptr strolchi{make_shared<Person>("Strolchi")};
  
//create accounts
  //for susi
  susi->add_account(0);
  susi->get_account(0)->set_overdraft(1000);
  susi->get_account(0)->set_fee(0.5); 
  //for strolchi
  strolchi->add_account(1);
  strolchi->get_account(0)->set_fee(2.0);
  
//take customer
  b.customer(susi);
  b.customer(strolchi);
//susi transfers 200e to strolchi
  susi->get_account(0)->transfer(200, strolchi->get_account(0));
//susi transfers 950e to strolchi : NOT POSSIBLE!
  susi->get_account(0)->transfer(950, strolchi->get_account(0));
//strolchi transfers 100e to susi
  strolchi->get_account(0)->transfer(100, susi->get_account(0));
//share authority with susi
  strolchi->share(susi, strolchi->get_account(0));
//susi transfers 100e from b account to g account
  susi->get_account(1)->transfer(150, susi->get_account(0));
//printin bank
  cout << b << endl;
//susi deletes g acc
  susi->delete_account(susi->get_account(0));
//strolchi gives up b acc
  strolchi->give_up_account(strolchi->get_account(0));
//susi exits bank
  b.del_person(strolchi);
//print bank
  cout << b << endl;
  return 0;
}
