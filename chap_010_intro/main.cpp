// Under Linux : g++ main.cpp -O3 -pthread -std=c++17










// Low level code with threads
// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
/**/                                                                            // <=====  commenting/uncommenting starts here
#include <iostream>
#include <thread>

using namespace std::chrono_literals;

void MyFunction(){
  std::cout << "Hello from thread named : " << __FUNCTION__ << '\n';
}

int main(){
  std::thread my_thread(MyFunction);                                            // my_thread starts at this point
  
  // Do some stuff in main()...
  std::this_thread::sleep_for(100ms); 

  my_thread.join();                                                             // main() waits for my_thread
                            
  //my_thread.detach();                                                         // If instead of joining, the thread is detached then my_thread becomes a deamon process
                                                                                // In such case nothing may be displayed on screen because main() may end before the thread
  std::cout << "Strike ENTER to exit :";                                        // => synchro mechanisms between threads are needed
  std::cin.get();
}                                                                               // If 2 threads are sharing any ressource (here std::cout for example) the thread that own the resource 
                                                                                // (here the main() function) should not leave as long as the other thread is using the resource
                                                                                // This also apply to global and static variables/object in the case of a detached thread 
                                                                                // The main() function may finish while the detached thread may need to access a global variable...

                                                                                // We can only detach() or join() a thread only ONCE but one can check if the thread is joinnable
                                                                                // if(my_thread.joinable()){
                                                                                //   my_thread.join();
                                                                                // }

/**/                                                                              // <=====  commenting/uncommenting ends here









// High level code with async (C++11 prefered way?)
// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
/*
#include <iostream>
#include <random>
#include <future>

int DisplayChars(char a_char){
  std::default_random_engine my_dre(a_char);
  std::uniform_int_distribution<> id(10, 1000);                                 // default template parameter is int

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

  auto result1 {std::async(fn1)};                                               // result1 is a future
                                                                                // a future is a place where, in the future, we will get a value
                                                                                // fn1 may start now, later or never

  int result2 = fn2();                                                          // result2 is an int
                                                                                // fn2 is executed here and now in the main() thread

  int result = result1.get() + result2;                                         // .get() blocks and waits until the result is available
                                                                                // compare to threads with the help of result1.get() we have returned values
  std::cout << "\n\nThe sum of fn1() and fn2() equals : " << result << '\n';

  std::cout << "Strike ENTER to exit :";                                        
  std::cin.get();
}                                                                                                                                                          
*/  










// Same code with threads
// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
/*
#include <iostream>
#include <thread>
#include <random>

int DisplayChars(char a_char){
  std::default_random_engine my_dre(a_char);
  std::uniform_int_distribution<> id(10, 1000);                                 // default template parameter is int

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