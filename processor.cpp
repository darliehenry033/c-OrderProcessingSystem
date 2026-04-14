#include<iostream>
#include<fstream>
#include<string>
#include<iomanip>
#include<sstream>
#include<unordered_map>
#include<algorithm>
using namespace std;

struct product{
string ProductId, ProductName;
float UnitPrice;

};
struct customer{
  
  string CustomerId, CustomerName;
  char CostumerType;
};
struct order{
  string OrderId, CostumerId, ProductId;
  int Quantity, YearsLoyal;
};

/*vector<string> split(string line){
  string temp = line;
  vector<string> list;
  int found = temp.find(",");
  while(found){
    line.push_back(temp.substr(found));
    temp = temp.substr();
  }*/

int main(){

  unordered_map<string, float> productPrices;
  ifstream prod_file;
  prod_file.open("products.csv");

  //int cline = 1;
  string line;
   getline(prod_file, line);
  // line.substr(0, line.find(","))<<endl;  will output the lines before ,
  while(getline(prod_file, line)){
      stringstream ss(line); // convert string into string to extract values seperated  by comas
      string prod_id, prod_name, priceString;
      getline(ss, prod_id, ',');
      getline(ss, prod_name, ',');
      getline(ss, priceString);
      productPrices[prod_id] = stof(priceString);

  }


  //to read the costumer file

  unordered_map<string, pair<string, char>> customerMap;
  ifstream cust_file;
  cust_file.open("customers.csv");
  getline(cust_file, line);
  
  while(getline(cust_file, line)){
    stringstream ss(line);
    string cust_Id, cust_name, typeString;
    getline(ss,cust_Id, ',' );
    getline(ss, cust_name, ',');
    getline(ss, typeString);
    customerMap[cust_Id] = { cust_name, typeString[0]};

   
  }

  ifstream order_file;
  order_file.open("orders.csv");
  ofstream result;
  result.open("result.csv");
  result << "CustomerId,CustomerName,PriceUnit,Quantity,Amount,Discount,Total\n";

  getline(order_file, line);
  while(getline(order_file, line)){
    stringstream ss(line);
    string orderId, custId, prodId, quantityStr, loyalStr;
    getline(ss, orderId, ',' );
    getline(ss, custId, ',');
    getline(ss, prodId, ',');
    getline(ss, quantityStr, ',');
    getline(ss, loyalStr);

   int qty;
   try{
   qty = stoi(quantityStr);
       } catch(...){
        cerr<<"Invalid quantity: "<< quantityStr <<endl;
        continue;
       } 

        int loyal = 0;
try {
    loyal = loyalStr.empty() ? 0 : stoi(loyalStr);
} catch (...) {
    cerr << "Invalid loyalty value: '" << loyalStr << "'\n";
    loyal = 0;
    continue;
}
 if(customerMap.find(custId) == customerMap.end()){
      cerr<< "Unknown CustomerID: "<< custId << endl;
      continue;
    }

    if(productPrices.find(prodId) == productPrices.end()){
  cerr<< "Unknown Produc ID: "<< prodId << endl;
  continue;
}
int commaCount = count(line.begin(), line.end(), ',');
  if(commaCount > 4 || commaCount < 4){
    cerr<<"Malformed line: "<<line<<endl;
    continue;
  }

    float unitPrice =  productPrices[prodId] ;
    string custName = customerMap[custId].first;
    char custType = customerMap[custId].second;

    float amount = qty * unitPrice;
    float discount = 0;
    float VAT = 0.10;

    if(custType =='A'){
      discount = 0;
    }
    else if(custType == 'B'){
      float percent = min(20.0f, loyal * 2.0f);
      discount = amount * (percent / 100);
    }
    else if(custType =='C'){
      discount = amount * 0.70;
    }

    float priceAfterDiscount = amount - discount;
    float vatAmount = priceAfterDiscount * VAT;
    float total = priceAfterDiscount + vatAmount;

    result << custId << ", "<< custName<<", "<< fixed <<setprecision(2) <<unitPrice<< ", "<< qty <<", "<< amount<<", "<< discount <<", "<< total<<"\n"; 
  }

  prod_file.close();
  cust_file.close();
  order_file.close();
  result.close();
}