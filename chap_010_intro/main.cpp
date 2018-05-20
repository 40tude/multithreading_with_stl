// Introduction










// Low level code with threads
// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
/*                                                                          // <=====  commenting/uncommenting starts here
#include <iostream>
#include <thread>

using namespace std::chrono_literals;

void MyFunction(){
  std::cout << "Hello from thread running function named : " << __FUNCTION__ << '\n';
}

int main(){
  std::thread my_thread(MyFunction);                                            // my_thread starts at this point at this moment
  
  // Do some stuff in main()...
  std::this_thread::sleep_for(100ms);                                           // In real life this doe'nt work that way. 
                                                                                // See the other the code sections below
                                                                                // Here, understand that the main thread is doing someting (sleeping)
                                                                                // while at the same time my_thread is doing something else (executes MyFunction)

  my_thread.join();                                                             // main() waits for my_thread
                            
  //my_thread.detach();                                                         // If instead of joining, the thread is detached then my_thread becomes a deamon thread
                                                                                // In such case nothing may be displayed on screen if main() ends before the thread
  std::cout << "\nStrike ENTER to exit :";                                      // This means that synchronization mechanisms between threads are needed
  std::cin.get();
}                                                                               // If 2 threads are sharing any ressource (here they share std::cout) the thread that own the resource 
                                                                                // (here the main() function) should not leave as long as the other thread is using the resource

                                                                                // Pay attantion. This also apply to global and static variables/objects in the case of a detached thread 
                                                                                // The main() function may finish while the detached thread may need to access a global variable...Ooops

                                                                                // We can detach() or join() a thread only ONCE but one can check if the thread is joinnable
                                                                                // if(my_thread.joinable()){
                                                                                //   my_thread.join();
                                                                                // }

*/                                                                           // <=====  commenting/uncommenting ends here










// Same as above
// Higher level code with async (C++ prefered way?)
// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
/*                                                                          
#include <iostream>
#include <future>

using namespace std::chrono_literals;

void MyFunction(){
  std::cout << "Hello from thread named : " << __FUNCTION__ << '\n';
}

int main(){
  
  auto result = std::async(MyFunction);                                         // Set a breakpoint and check when the message is sent to the console 
  
  // Do some stuff in main()...
  std::this_thread::sleep_for(100ms);                                           

  result.get();

  std::cout << "\n\nStrike ENTER to exit :";                                      
  std::cin.get();
}                                                                               
*/                                                                           










// Morerealistic example
// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
/*
#include <iostream>
#include <random>
#include <future>

void fn1(){
  char const a_char {'_'};

  std::default_random_engine my_dre(a_char);
  std::uniform_int_distribution<> id(10, 1000);                                 // the default template parameter of uniform_int_distribution is int

  for(int i=0; i<20; ++i){
    std::this_thread::sleep_for(std::chrono::milliseconds(id(my_dre)));
    std::cout.put(a_char).flush();
  }
}

int main(){

  auto result = std::async(fn1);                                                // fn1 may start now, later or never

  // Do some stuff in main()...
  {
    char const a_char {'-'};

    std::default_random_engine my_dre(a_char);
    std::uniform_int_distribution<> id(10, 1000);                               

    for(int i=0; i<20; ++i){
      std::this_thread::sleep_for(std::chrono::milliseconds(id(my_dre)));
      std::cout.put(a_char).flush();
    }
  }

  result.get();
  std::cout << "\n\nStrike ENTER to exit :";                                        
  std::cin.get();
}                                                                                                                                                          
*/  










// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
/*
#include <iostream>
#include <random>
#include <future>

void fn1(){
  char const a_char {'_'};

  std::default_random_engine my_dre(a_char);
  std::uniform_int_distribution<> id(10, 1000);                                 

  for(int i=0; i<20; ++i){
    std::this_thread::sleep_for(std::chrono::milliseconds(id(my_dre)));
    std::cout.put(a_char).flush();
  }
}

void fn2(){
  char const a_char {'-'};

  std::default_random_engine my_dre(a_char);
  std::uniform_int_distribution<> id(10, 1000);                                 

  for(int i=0; i<20; ++i){
    std::this_thread::sleep_for(std::chrono::milliseconds(id(my_dre)));
    std::cout.put(a_char).flush();
  }
}

int main(){

  auto result = std::async(fn1);                                                // fn1 may start now, later or never
  fn2();                                                                        // fn2 is executed here and now in the main() thread
                                                                                // Ideally while fn1 is working on one core, fn2 is executed on another core
  
  result.get();
  std::cout << "\n\nStrike ENTER to exit :";                                        
  std::cin.get();
}                                                                                                                                                          
*/  










// getting a result from the async() task is easy
// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
/*
#include <iostream>
#include <random>
#include <future>

int DisplayChars(char const a_char){
  std::default_random_engine my_dre(a_char);
  std::uniform_int_distribution<> id(10, 1000);                                 // the default template parameter of uniform_int_distribution is int

  for(int i=0; i<20; ++i){
    std::this_thread::sleep_for(std::chrono::milliseconds(id(my_dre)));
    std::cout.put(a_char).flush();
  }
  return static_cast<int> (a_char);
}

int fn1(){
  return DisplayChars('_');
}

int fn2(){
  return DisplayChars('-');
}

int main(){
  auto result1 {std::async(fn1)};                                               // result1 is a future
                                                                                // a future is a place where, in the future, we will get a value from
                                                                                // fn1 may start now, later or never

  int result2 = fn2();                                                          // result2 is a regular int
                                                                                // fn2 is executed here and now in the main() thread
                                                                                // Ideally while fn1 is working on one core, fn2 is executed on another core

  int result = result1.get() + result2;                                         // .get() blocks and waits until result1 is available
                                                                                // Ideally fn1 is done and result1 is available immediatly
                                                                                // compared to threads, with the help of result1.get(), we have a returned value from an async()
  std::cout << "\n\nThe sum of fn1() and fn2() equals : " << result << '\n';

  std::cout << "\nStrike ENTER to exit :";                                        
  std::cin.get();
}                                                                                                                                                          
*/  










// Same code as above with threads
// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
/*
#include <iostream>
#include <thread>
#include <random>

int DisplayChars(char a_char){
  std::default_random_engine my_dre(a_char);
  std::uniform_int_distribution<> id(10, 1000);                                 

  for(int i=0; i<20; ++i){
    std::this_thread::sleep_for(std::chrono::milliseconds(id(my_dre)));
    std::cout.put(a_char).flush();
  }
  return static_cast<int> (a_char);
}

int fn1(){
  return DisplayChars('_');
}

int fn2(){
  return DisplayChars('-');
}

int main(){
  std::cout << "f1() works in the background\n";
  std::cout << "f2() works in the foreground\n\n";

  std::thread my_thread(fn1);                                                   // no easy way to get a returned value from a thread
  
  // Do some stuff in main()...
  int result = fn2();
                                                                                // no easy way to know if fn1 is done
  my_thread.join();                                                             // main() blocks and waits for my_thread to finish

  std::cout << "\n\nStrike ENTER to exit :";                                        
  std::cin.get();
}
*/                                                                               