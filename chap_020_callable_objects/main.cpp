// Callable objects










// Any callable object can be use to create a thread object
// We already saw how to run a function in a thread (see chap_010)
// Here is an example with a functor (a class with a function call operator overloaded)
// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
/**/
#include <iostream>
#include <thread>

class MyFunctor{
  public:
  void operator()(){
    for (int i=0; i>-100; --i){
      std::cout << "From thread : " << i << '\n';
    }
  }
};


int main(){
  
  //MyFunctor fct;                                                              // One way to launch the functor fct as a thread  
  //std::thread my_thread(fct);
   
  std::thread my_thread(MyFunctor{});                                           // Another way to launch the functor fct as a thread. It saves one line of code

  //std::thread my_thread(MyFunctor());                                         // This line is NOT correct. Search for "Most vexing parse in C++" 
                                                                                // The standard says that if it can be interpreted as a function declaration it will be interpreted as such
                                                                                // This is a function declaration
                                                                                // A function my_thread, which takes one parameter, a pointer to a function wich takes 
                                                                                // no parameter and return a MyFunctor object. Finally the function my_thread returns a std::thread

  //std::thread my_thread((MyFunctor());                                        // Works but it is heavy

  // Do some stuff in main() thread
  for(int i=0; i<100; ++i){
    std::cout << "From main() : " << i << '\n';
  }

  my_thread.join();  

  std::cout << "Strike ENTER to exit :";
  std::cin.get();
}
/**/










// Same as above but with a struct (a class whose members are all public)
// structor :-)
// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
/*
#include <iostream>
#include <thread>

struct MyStructor{
  public:
  void operator()(){
    for (int i=0; i<40; ++i){
      std::cout.put('_').flush();
    }
  }
};

int main(){
  
  std::thread my_thread(MyStructor{});                                            // Another way to launch the functor fct as a thread. It saves one line of code

  // Do some stuff in main() thread
  for(int i=0; i<40; ++i){
    std::cout.put('-').flush();
  }

  my_thread.join();  

  std::cout << "\n\nStrike ENTER to exit :";
  std::cin.get();
}
*/










// Same as above but with a async() function
// Every callable used in a thread can be a parameter of an async()
// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
/*
#include <iostream>
#include <future>

struct MyStructor{
  public:
  void operator()(){
    for (int i=0; i<40; ++i){
      std::cout.put('_').flush();
    }
  }
};

int main(){
  
  auto result {std::async(MyStructor())};                                           

  // Do some stuff in main() thread
  for(int i=0; i<40; ++i){
    std::cout.put('-').flush();
  }

  //result.get();                                                               // no need to get since there is no return value
                                                                                // However, the "Strik..." sentence may be displayed
                                                                                // before the thread ends. Make some experiments :-)
  std::cout << "\n\nStrike ENTER to exit :";
  std::cin.get();
}
*/









// function object
// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
/*
#include <iostream>
#include <thread>

using namespace std::chrono_literals;

void Say_Hello(){
  std::cout << "From thread : Hello\n";
}

int main(){
  
  std::function<void()> my_function = Say_Hello;
  std::thread my_thread(my_function);                                            // Another way to launch the functor fct in a thread. 

  // Do some stuff in main() thread
  std::this_thread::sleep_for(100ms);

  my_thread.join();  

  std::cout << "Strike ENTER to exit :";
  std::cin.get();
}
*/




// function object can help to pass parameters to threads
// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
/*
#include <iostream>
#include <thread>

using namespace std::chrono_literals;

void Say_Hello_n_times(int const n){
  for(int i=0; i<n; ++i) std::cout << "From thread : Hello\n";
}

int main(){
  
  //std::function<void()> my_function = std::bind(Say_Hello_n_times, 3);        // bind the function and its parameter. 
                                                                                // my_function is a function object that takes no parameter and returns void 

  auto my_function = std::bind(Say_Hello_n_times, 5);                           // same thing as above
  
  std::thread my_thread(my_function);                                           // run the function object in a thread

  // Do some stuff in the main() thread
  std::this_thread::sleep_for(100ms);

  my_thread.join();  

  std::cout << "Strike ENTER to exit :";
  std::cin.get();
}
*/










// Same as above but with async()
// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
/*
#include <iostream>
#include <future>

using namespace std::chrono_literals;

void Say_Hello_n_times(int const n){
  for(int i=0; i<n; ++i) std::cout << "From thread : Hello\n";
}

int main(){

  auto my_function = std::bind(Say_Hello_n_times, 30);                           
  auto result = async(my_function);          

  // Do some stuff in the main() thread
  // std::this_thread::sleep_for(10ms);                                         // There is no sleep on purpose
                                                                                // Doing so, the "Strike..." happen before the thread ends
  // result.get();                                                              // Uncomment the sleep_for() or the .get();
  
  std::cout << "Strike ENTER to exit :";
  std::cin.get();
}
*/










// lambda
// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
/*
#include <iostream>
#include <thread>

using namespace std::chrono_literals;

int main(){

  std::thread my_thread([](){
    std::cout << "Hello, Pr Falkens, my name is Joshua.\n";
  });

  // Do some stuff in the main() thread
  std::this_thread::sleep_for(100ms);

  my_thread.join();  

  std::cout << "Strike ENTER to exit :";
  std::cin.get();
}
*/









// same as above with async()
// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
/*
#include <iostream>
#include <future>

using namespace std::chrono_literals;

int main(){

  auto result = std::async([](){
    std::cout << "The only winning move is not to play.\n";
  });

  // Do some stuff in the main() thread
  std::this_thread::sleep_for(100ms);

  // result.get();                                                              // be careful here...
  
  std::cout << "Strike ENTER to exit :";
  std::cin.get();
}
*/