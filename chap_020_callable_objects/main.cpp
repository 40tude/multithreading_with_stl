// Callable objects










// Any callable object can be use to create a thread object
// See http://en.cppreference.com/w/cpp/concept/Callable
// We already saw how to run a function in a thread (chap_010)
// Here is an example with a functor (a class with an overloaded function call operator)
// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
/*
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
*/










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
  void operator()(){
    for (int i=0; i<40; ++i){
      std::cout.put('_').flush();
    }
  }
};

int main(){

  auto result {std::async(MyStructor())};                                       // result is a future
                                                                                // a future is an object from which we can get a value later (not used here)
  // Do some stuff in main() thread
  for(int i=0; i<40; ++i){
    std::cout.put('-').flush();
  }

  //result.get();                                                               // no need to get since there is no return value
                                                                                // However, the "Strike..." sentence may be displayed
                                                                                // before the thread ends.
                                                                                // Make some experiments, uncommenting/commenting the .get() call
  std::cout << "\n\nStrike ENTER to exit :";
  std::cin.get();
}
*/









// Run a method of a class in a thread
// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
/*
#include <iostream>
#include <thread>

struct MyClass{
  void loooong_call(){
    for (int i=0; i<40; ++i){
      std::cout.put('_').flush();
    }
  }
};

int main(){

  MyClass my_instance;

  std::thread my_thread(&MyClass::loooong_call, my_instance);

  // Do some stuff in main() thread
  for(int i=0; i<40; ++i){
    std::cout.put('-').flush();
  }

  my_thread.join();

  std::cout << "\n\nStrike ENTER to exit :";
  std::cin.get();
}
*/









// Pass a method of a class to an async()
// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
/*
#include <iostream>
#include <future>

struct MyClass{
  void loooong_call(){
    for (int i=0; i<40; ++i){
      std::cout.put('/').flush();
    }
  }
};

int main(){

  MyClass my_instance;

  auto result = std::async(&MyClass::loooong_call, my_instance);

  // Do some stuff in main() thread
  for(int i=0; i<40; ++i){
    std::cout.put('\\').flush();
  }

  result.get();

  std::cout << "\n\nStrike ENTER to exit :";
  std::cin.get();
}
*/










// Run a function object in a thread
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




// A function object can help to pass parameters to threads
// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
/*
#include <iostream>
#include <thread>

using namespace std::chrono_literals;

void Say_Hello_n_Times(int const n){
  for(int i=0; i<n; ++i) std::cout << "From thread : Hello\n";
}

int main(){

  //std::function<void()> my_function = std::bind(Say_Hello_n_Times, 3);        // bind the function and its parameter.
                                                                                // my_function is a function object that takes no parameter and returns void

  auto my_function = std::bind(Say_Hello_n_Times, 5);                           // same thing as above

  std::thread my_thread(my_function);                                           // run the function object in a thread

  // Do some stuff in the main() thread
  std::this_thread::sleep_for(100ms);

  my_thread.join();

  std::cout << "Strike ENTER to exit :";
  std::cin.get();
}
*/










// Pass a function object to an async()
// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
/*
#include <iostream>
#include <future>

using namespace std::chrono_literals;

void Say_Hello_n_Times(int const n){
  for(int i=0; i<n; ++i) std::cout << "From thread : Hello\n";
}

int main(){

  auto my_function = std::bind(Say_Hello_n_Times, 30);
  auto result = async(my_function);

  // Do some stuff in the main() thread
  // std::this_thread::sleep_for(10ms);                                         // There is no sleep on purpose
                                                                                // Doing so, the "Strike..." happen before the thread ends
  // result.get();                                                              // Uncomment the sleep_for() or the .get();

  std::cout << "Strike ENTER to exit :";
  std::cin.get();
}
*/










// Run a lambda in a thread
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









// Pass a lambda to an async()
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










// packaged tasks provide a way to prepare a task and to run it in a later
// In addition packaged tasks also provides a future from which we .get() the return value
// The code below IS NOT multithread.
// It demonstrates how to setup a packaged_task, call it synchronously from main() and get its return value
// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
/*
#include <iostream>
#include <future>

int syracuse(unsigned long n){
  int counter=0;
  while(n>1){
    if(n%2){
      n = n*3 + 1;                                                              // n is odd
    }else{
      n = n/2;                                                                  // n is even
    }
    counter++;
  }
  return counter;
}

int main(){

  std::packaged_task <int(unsigned long)> my_packaged_task(syracuse);           // A packaged task is an object
                                                                                // This is a templated task
                                                                                // It is parametrized with the function signature of its task
                                                                                // See syracuse() definition which takes an unsigned long and returns an int

  // ...                                                                        // At this point, the packaged task is created
                                                                                // but there is no need to start the thread now

  auto my_value = 837'799UL;                                                    // Try differents values : 27, 26'623, 511'935 or 837'799
  my_packaged_task(my_value);                                                   // Later on, the task is invoked

  //int flight_length = my_packaged_task(11);                                   // This won't work
                                                                                // No way to get the return value easily
                                                                                // A packaged task always returns void

  auto flight_length = my_packaged_task.get_future().get();                     // This is the way to get the result
                                                                                // Compared with an async() function a packaged_task object provides a future
                                                                                // from which we can .get() the returned value
  std::cout << "The flight length of " << my_value << " is " << flight_length << '\n';

  std::cout << "\nStrike ENTER to exit :";
  std::cin.get();
}
*/



















// run a packaged_task in a thread
// we can use packaged_task to get a return value from a thread
// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
/*
#include <iostream>
#include <future>

using namespace std::chrono_literals;

int fn1(){
  std::cout << "Hello from fn1()\n";
  return 42;
}

int main(){
  std::packaged_task <int(void)> my_packaged_task(fn1);
  auto my_future = my_packaged_task.get_future();                               // Create a future before the packaged task is moved into the thread

  std::thread my_thread {std::move(my_packaged_task)};                          // a packaged_task cannot be copied but can be moved

  // Do something in main()
  std::this_thread::sleep_for(100ms);

  std::cout << "In main() the result is : " << my_future.get()  << '\n';

  my_thread.join();                                                             // Never forget to join the htread

  std::cout << "\nStrike ENTER to exit :";
  std::cin.get();
}
*/








// Pass a packaged_task to an async()
// Over enginered?
// In fact we can achieve the same result more simply (see chap 010)
// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
/*
#include <iostream>
#include <future>

using namespace std::chrono_literals;

int fn1(){
  std::cout << "Hello from fn1()\n";
  return 42;
}

int main(){
  std::packaged_task <int(void)> my_packaged_task(fn1);
  auto my_future = my_packaged_task.get_future();                               // get a future before the packaged_task is moved

  std::async(std::move(my_packaged_task));                                      // a packaged_task cannot be copied but can be moved
                                                                                // compare to previous sample code in chap_010 there is nothing like
                                                                                // auto result = std::async(std::move(my_packaged_task));
                                                                                // since the future is provided by the packaged task
  // Do something in main()
  std::this_thread::sleep_for(100ms);

  std::cout << "In main() the result is : " << my_future.get()  << '\n';

  std::cout << "\nStrike ENTER to exit :";
  std::cin.get();
}
*/


// This is all fine but what we want is to pass parameters to threads and get returned values