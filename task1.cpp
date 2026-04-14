#include <iostream>
#include <vector>
#include <string>
#include <initializer_list> // For convenient collection initialization
#include <stdexcept>        // For out_of_range
using namespace std;

namespace Task_1a{

template<typename T>
  T max(T a, T b){
    return a > b ? a: b;
  } 

template<typename T>
  T min(T a, T b){
    return a < b ? a : b;
  }

template<typename T>
  void swap(T& a, T& b){
    T temp = a;
    a = b;
    b  = temp;

  }
}

namespace Task_1b{

  template<typename T>
  T max(T a){
    return a;
  }

template<typename T, typename...Rest>
  T max(T a, Rest... rest){
     T b = max(rest...);
     return a > b? a: b;
  }

 template<typename T>
 T min( T a){
  return a;
 }

 template<typename T, typename...Rest>
T min(T a, Rest... rest){
  T b = min(rest...);
  return a < b? a : b;
}

template<typename T>

class SortableCollection{
  private:
  vector<T> data;

  public:
  SortableCollection() = default;
  SortableCollection(initializer_list<T> init): data(init){}
  void add(T element){
       data.push_back(element);
  }

  int getSize(){
     return data.size();
  }

  void print(){
    cout<<"[ ";
       for(int i = 0; i < data.size(); i++){
        cout<<data[i]<<" , ";        
      }
      cout<<" ]";
  }

  T getElement(int index){
        if(index >= data.size()){
      throw out_of_range("Index out of range");
        }
        else
          return data[index];
      
  }
  void sort(){
 
     for(int i= 0; i < data.size(); i++){
        for(int j = 0; j < data.size() -1; j++){
          if(data[j] > data[j + 1]){
            Task_1a::swap(data[j], data[j + 1]);
          }
        }
     }
  }
};
}
int main() {
    std::cout << "--- Testing Task_1a Non-Variadic Template Functions ---" << std::endl;

    // Test max (Task_1a)
    int a = 10, b = 5;
    std::cout << "Task_1a::max(" << a << ", " << b << "): " << Task_1a::max(a, b) << std::endl;
    double c = 3.14, d = 2.718;
    std::cout << "Task_1a::max(" << c << ", " << d << "): " << Task_1a::max(c, d) << std::endl;
    std::string s1 = "zebra", s2 = "apple";
    std::cout << "Task_1a::max(\"" << s1 << "\", \"" << s2 << "\"): " << Task_1a::max(s1, s2) << std::endl;

    std::cout << std::endl;

    // Test min (Task_1a)
    std::cout << "Task_1a::min(" << a << ", " << b << "): " << Task_1a::min(a, b) << std::endl;
    std::cout << "Task_1a::min(" << c << ", " << d << "): " << Task_1a::min(c, d) << std::endl;
    std::cout << "Task_1a::min(\"" << s1 << "\", \"" << s2 << "\"): " << Task_1a::min(s1, s2) << std::endl;

    std::cout << std::endl;

    // Test swap (Task_1a)
    int x = 1, y = 2;
    std::cout << "Before Task_1a::swap: x = " << x << ", y = " << y << std::endl;
    Task_1a::swap(x, y);
    std::cout << "After Task_1a::swap:  x = " << x << ", y = " << y << std::endl;

    double p = 1.1, q = 9.9;
    std::cout << "Before Task_1a::swap: p = " << p << ", q = " << q << std::endl;
    Task_1a::swap(p, q);
    std::cout << "After Task_1a::swap:  p = " << p << ", q = " << q << std::endl;

    std::string str1 = "hello", str2 = "world";
    std::cout << "Before Task_1a::swap: str1 = \"" << str1 << "\", str2 = \"" << str2 << "\"" << std::endl;
    Task_1a::swap(str1, str2);
    std::cout << "After Task_1a::swap:  str1 = \"" << str1 << "\", str2 = \"" << str2 << "\"" << std::endl;

    std::cout << "\n--- Testing Task_1b Variadic Template Functions ---" << std::endl;

    // Test max (Task_1b) with varying arguments
    std::cout << "Task_1b::max(10): " << Task_1b::max(10) << std::endl;
    std::cout << "Task_1b::max(10, 5): " << Task_1b::max(10, 5) << std::endl;
    std::cout << "Task_1b::max(10, 5, 20): " << Task_1b::max(10, 5, 20) << std::endl;
    std::cout << "Task_1b::max(10, 5, 20, -3, 15): " << Task_1b::max(10, 5, 20, -3, 15) << std::endl;

    std::cout << "Task_1b::max(3.14, 1.618, 2.718): " << Task_1b::max(3.14, 1.618, 2.718) << std::endl;
    std::cout << "Task_1b::max(\"cat\", \"apple\", \"zebra\", \"banana\"): " << Task_1b::max("cat", "apple", "zebra", "banana") << std::endl;

    std::cout << std::endl;

    // Test min (Task_1b) with varying arguments
    std::cout << "Task_1b::min(10): " << Task_1b::min(10) << std::endl;
    std::cout << "Task_1b::min(10, 5): " << Task_1b::min(10, 5) << std::endl;
    std::cout << "Task_1b::min(10, 5, 20): " << Task_1b::min(10, 5, 20) << std::endl;
    std::cout << "Task_1b::min(10, 5, 20, -3, 15): " << Task_1b::min(10, 5, 20, -3, 15) << std::endl;

    std::cout << "Task_1b::min(3.14, 1.618, 2.718): " << Task_1b::min(3.14, 1.618, 2.718) << std::endl;
    std::cout << "Task_1b::min(\"cat\", \"apple\", \"zebra\", \"banana\"): " << Task_1b::min("cat", "apple", "zebra", "banana") << std::endl;

    std::cout << "\n--- Testing SortableCollection ---" << std::endl;

    // Test with integers
    std::cout << "Integer Collection:" << std::endl;
   Task_1b::SortableCollection<int> intCollection;
    intCollection.add(5);
    intCollection.add(2);
    intCollection.add(8);
    intCollection.add(1);
    intCollection.add(9);

    std::cout << "Before sorting: ";
    intCollection.print();
    std::cout << std::endl;

    intCollection.sort();

    std::cout << "After sorting:  ";
    intCollection.print();
    std::cout << std::endl;

    std::cout << std::endl;

    // Test with doubles (using initializer list constructor)
    std::cout << "Double Collection:" << std::endl;
    Task_1b::SortableCollection<double> doubleCollection = {3.14, 1.618, 2.718, 0.577, 9.9};

    std::cout << "Before sorting: ";
    doubleCollection.print();
    std::cout << std::endl;

    doubleCollection.sort();

    std::cout << "After sorting:  ";
    doubleCollection.print();
    std::cout << std::endl;

    std::cout << std::endl;

    // Test with strings
    std::cout << "String Collection:" << std::endl;
    Task_1b::SortableCollection<std::string> stringCollection;
    stringCollection.add("zebra");
    stringCollection.add("apple");
    stringCollection.add("cat");
    stringCollection.add("dog");
    stringCollection.add("banana");
    stringCollection.add("ant");

    std::cout << "Before sorting: ";
    stringCollection.print();
    std::cout << std::endl;

    stringCollection.sort();

    std::cout << "After sorting:  ";
    stringCollection.print();
    std::cout << std::endl;

    // Test exception handling for out-of-bounds access
    std::cout << "\n--- Testing SortableCollection Exception Handling ---" << std::endl;
    Task_1b::SortableCollection<int> smallCollection = {10, 20}; // Create a small collection

    std::cout << "Collection size: " << smallCollection.getSize() << std::endl;
    std::cout << "Attempting to access element at index " << smallCollection.getSize() << " (out of bounds)..." << std::endl;

    try {
        // Accessing index 2 in a collection of size 2 (valid indices are 0 and 1)
        smallCollection.getElement(smallCollection.getSize());
        // This line should not be reached if the exception is thrown
        std::cout << "Error: Exception was NOT thrown." << std::endl;
    } catch (const std::out_of_range& e) {
        // This block should be executed if std::out_of_range is thrown
        std::cout << "Caught expected exception: " << e.what() << std::endl;
    } catch (const std::exception& e) {
         // Catch any other standard exceptions
         std::cout << "Caught an unexpected standard exception: " << e.what() << std::endl;
    }
    catch (...) {

        std::cout << "Caught an unknown unexpected exception." << std::endl;
    }
    std::cout << "Exception test complete." << std::endl;


    return 0;
}