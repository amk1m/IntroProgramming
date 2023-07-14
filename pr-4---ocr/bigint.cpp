// Copy in your bigint.cpp (overwrite this file)
//  and then add the appropriate code
#include <iostream>
#include "bigint.h"
#include <cstring>

using namespace std;

// Write your implementation below

// constructor
BigInt::BigInt(string s, int base)
{
  bs = base;
  // get length of string
  int len = s.length();
  int x;

  for(int i = 0; i < len; i++){
    char c = s[len - 1 - i];
    if(c <= '9'){
      x = static_cast<int>(c) - '0';
    }
    else{
      x = 10 + static_cast<int>(c) - 'A';
    }
    my_vec.push_back(x);
  }

  removeLeadingZeroes();

}

// to_string
string BigInt::to_string() const
{
  string result = "";
  int len = my_vec.size();
  char c;
  for(int i = 0; i < len; i++){
    int n = my_vec[len - 1 - i];
    if(n <= 9){
      c = static_cast<char>(n) + '0';
    }
    else{
      c = static_cast<char>(n) + 'A' - 10;
    }
    result = result + c;
  }

  return result;

}

// add
void BigInt::add(BigInt b)
{
  int base = b.bs;
  int lenA = my_vec.size();
  int lenB = b.my_vec.size();
  // num at bottom = sum - base
  // if sum >= base then there is carry
  // carry is always 1 no matter the base

  int minlen;
  if(lenA > lenB){
    minlen = lenB;
  }
  else{
    minlen = lenA;
  }

  int carry = 0;
  int sum = 0;
  int times = 0;

  for(int i = 0; i < minlen; i++){
    sum = my_vec[i] + b.my_vec[i] + carry;
    carry = 0;
    if(sum > base-1){
      carry = 1;
      sum = sum - base;
    }
    my_vec[i] = sum;
  }

  if(lenB > lenA){ // if number added has more digits than original
    times = lenB - lenA;
    for(int i = 0; i < times; i++){
      sum = b.my_vec[lenA + i] + carry;
      carry = 0;
      if(sum > base-1){
        carry = 1;
        sum = sum - base;
      }
      my_vec.push_back(sum);
    }
    if(carry == 1){
      my_vec.push_back(1);
    }
  }

  else if (lenA > lenB){
    times = lenA - lenB;
    for(int i = 0; i < times; i++){
      sum = my_vec[lenB + i] + carry;
      carry = 0;
      if(sum > base-1){
        carry = 1;
        sum = sum - base;
      }
      my_vec[lenB + i] = sum;
    }
    if(carry == 1){
      my_vec.push_back(1);
    }
  }

  else if(lenA == lenB){
    if(carry == 1){
      my_vec.push_back(1);
    }
  }


}

void BigInt::removeLeadingZeroes()
{

  int lastI = my_vec.size() - 1;

  if(my_vec[lastI] == 0){
    bool stillZ = true;
    //int index = -1;
    int counter = 1;

    for(int i = 1; i <= lastI; i++){
      if(my_vec[lastI - i] == 0){
        counter += 1;
      }
      else if(my_vec[lastI - i] != 0){
        stillZ = false;
        //index = lastI - i;
        break;
      }
    }
    //cout << index << endl;

    if(stillZ == false){

      for(int i = 0; i < counter; i++){
        my_vec.pop_back();

      }

    }
    else if(stillZ == true){ // if number is just 0
      for(int i = 0; i < lastI; i++){
        my_vec.pop_back();
      }
    }
  }

}

BigInt BigInt::operator+(const BigInt& rhs) const
{

  BigInt temp = *this;

  int lenA = temp.my_vec.size();
  int lenB = rhs.my_vec.size();
  // num at bottom = sum - base
  // if sum >= base then there is carry
  // carry is always 1 no matter the base

  int minlen;
  if(lenA > lenB){
    minlen = lenB;
  }
  else{
    minlen = lenA;
  }

  int carry = 0;
  int sum = 0;
  int times = 0;

  for(int i = 0; i < minlen; i++){
    sum = temp.my_vec[i] + rhs.my_vec[i] + carry;
    carry = 0;
    if(sum > 9){
      carry = 1;
      sum = sum - 10;
    }
    temp.my_vec[i] = sum;
  }

  if(lenB > lenA){ // if number added has more digits than original
    times = lenB - lenA;
    for(int i = 0; i < times; i++){
      sum = rhs.my_vec[lenA + i] + carry;
      carry = 0;
      if(sum > 9){
        carry = 1;
        sum = sum - 10;
      }
      temp.my_vec.push_back(sum);
    }
    if(carry == 1){
      temp.my_vec.push_back(1);
    }
  }

  else if (lenA > lenB){
    times = lenA - lenB;
    for(int i = 0; i < times; i++){
      sum = temp.my_vec[lenB + i] + carry;
      carry = 0;
      if(sum > 9){
        carry = 1;
        sum = sum - 10;
      }
      temp.my_vec[lenB + i] = sum;
    }
    if(carry == 1){
      temp.my_vec.push_back(1);
    }
  }

  else if(lenA == lenB){
    if(carry == 1){
      temp.my_vec.push_back(1);
    }
  }

  return temp;

}


bool BigInt::operator<(const BigInt& rhs) const
{
  BigInt temp = *this;

  int lenA = temp.my_vec.size();
  int lenB = rhs.my_vec.size();

  if(lenA < lenB){
    return true;
  }
  else if(lenA > lenB){
    return false;
  }
  else{ // indicates that lenA == lenB

    for(int i = 0; i < lenA; i++){

      int tempA = temp.my_vec[lenA - i - 1];
      int tempB = rhs.my_vec[lenA - i - 1];

      // cout << tempA << " " << tempB << endl;

      if(tempA < tempB){
        return true;
      }
      else if(tempB < tempA){
        return false;
      }

    }
    return false;

  }
}


BigInt BigInt::operator-(const BigInt& rhs) const
{
  BigInt temp = *this;

  int lenA = temp.my_vec.size();
  int lenB = rhs.my_vec.size();

  int minlen;
  if(lenA > lenB){
    minlen = lenB;
  }
  else{
    minlen = lenA;
  }

  int diff = 0;
  int carry = 0;
  int times = 0;

  for(int i = 0; i < minlen; i++){

    if(temp.my_vec[i] - carry < rhs.my_vec[i]){
      diff = temp.my_vec[i] + 10 - rhs.my_vec[i] - carry;
      carry = 1;
    }
    else{
      diff = temp.my_vec[i] - rhs.my_vec[i] - carry;
      carry = 0;
    }
    temp.my_vec[i] = diff;

  }

  if(lenA > lenB){

    times = lenA - lenB;
    for(int i = 0; i < times; i++){
      diff = temp.my_vec[lenB + i] - carry;
      carry = 0;

      temp.my_vec[lenB + i] = diff;
    }

  }

  temp.removeLeadingZeroes();

  return temp;




}

/*
int main(){

  // testing:
  // BigInt b1("0");
  // cout << b1.to_string() << endl; // should print 0
  // BigInt b2("00");
  // cout << b2.to_string() << endl; // should print 0
  BigInt b6("00007");
  cout << b6.to_string() << endl; // should print 7

  // BigInt b3("103"), b4("98");
  // BigInt b5 = b3 + b4;
  // cout << b5.to_string() << endl; // should print 201

  BigInt b7("901"), b8("786");
  //cout << boolalpha;
  cout << (b7 < b8) << endl; // should print true
  cout << (b8 < b7) << endl;

  BigInt b9("103"), b10("98");
  BigInt b11 = b9 - b10;
  cout << b11.to_string() << endl; // should print 5



  return 0;
} */


