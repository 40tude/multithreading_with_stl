// Introduction










// Low level code with threads
// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
// /*                                                                          // <=====  commenting/uncommenting starts here
#include <iostream>
#include <thread>

using namespace std::chrono_literals;

void MyFunction(){
  std::cout << "Hello from thread named : " << __FUNCTION__ << '\n';
}

int main(){
  std::thread my_thread(MyFunction);                                            // my_thread starts at this point at this moment
  
  // Do some stuff in main()...
  std::this_thread::sleep_for(100ms);                                           // In real life this doe'nt work that way. 
                                                                                // See the other the code sections below
                                                                                // Here, understand that the main thread is doing someting (sleeping)
                                                                                // while at the same time my_thread is doing something else (executes MyFunction)

  my_thread.join();                                                             // main() waits for my_thread
                            
  //my_thread.detach();                                                         // If instead of joining, the thread is detached then my_thread becomes a deamon process
                                                                                // In such case nothing may be displayed on screen if main() ends before the thread
  std::cout << "Strike ENTER to exit :";                                        // This means that synchronization mechanisms between threads are needed
  std::cin.get();
}                                                                               // If 2 threads are sharing any ressource (here they share std::cout) the thread that own the resource 
                                                                                // (here the main() function) should not leave as long as the other thread is using the resource

                                                                                // Pay attantion. This also apply to global and static variables/objects in the case of a detached thread 
                                                                                // The main() function may finish while the detached thread may need to access a global variable...Ooops

                                                                                // We can detach() or join() a thread only ONCE but one can check if the thread is joinnable
                                                                                // if(my_thread.joinable()){
                                                                                //   my_thread.join();
                                                                                // }

// */                                                                           // <=====  commenting/uncommenting ends here









// Higher level code with async (C++11 prefered way?)
// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
/*
#include <iostream>
#include <random>
#include <future>

int DisplayChars(char a_char){
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
  std::cout << "f1() works in the background\n";
  std::cout << "f2() works in the foreground\n\n";

  auto result1 {std::async(fn1)};                                               // result1 is a future
                                                                                // a future is a place where, in the future, we will get a value from
                                                                                // fn1 may start now, later or never

  int result2 = fn2();                                                          // result2 is a regular int
                                                                                // fn2 is executed here and now in the main() thread
                                                                                // Ideally while fn1 is working on one core, fn2 is executed on another core

  int result = result1.get() + result2;                                         // .get() blocks and waits until the result is available
                                                                                // compare to threads, with the help of result1.get(), we have a returned value from an async()
  std::cout << "\n\nThe sum of fn1() and fn2() equals : " << result << '\n';

  std::cout << "Strike ENTER to exit :";                                        
  std::cin.get();
}                                                                                                                                                          
*/  










// Same code as above but with threads
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









// packaged tasks provide a way to prepare a task and to run it in a thread later
// packaged tasks also provides a future from which we .get() the return value
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
  
  // ...                                                                        // At this pont, the packaged task is created
                                                                                // but there is no need to start the thread now 

  auto my_value = 837'799UL;                                                    // Try differents values : 27, 26'623, 511'935 or 837'799
  my_packaged_task(my_value);                                                   // Later on, the task is invoked

  //int flight_length = my_packaged_task(11);                                   // This won't work                                         
                                                                                // No way to get the return value easily
                                                                                // A packaged task always returns void

  int flight_length = my_packaged_task.get_future().get();                      // This is the way to get the result
                                                                                // Compared with an async() function a packaged_task object provides a future
                                                                                // from which we can .get() the returned value
  std::cout << "The flight length of " << my_value << " is " << flight_length << '\n';                               
  
  std::cout << "\nStrike ENTER to exit :";
  std::cin.get();
}
*/