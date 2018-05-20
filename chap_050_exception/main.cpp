// Exceptions










// If a thread is destroyed BEFORE it is joined or detached then the program
// terminates 
// We need to decide BEFORE the thread goes out of scope if we want to 
// join() or detach() 
// In the code below, everything works fine : no exception, no problem...
// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
/*
#include <iostream>
#include <thread>

void My_Thread_Function(){
  std::cout << "Hello from thread " << __FUNCTION__ << '\n';
}

void My_Not_Throwing_Function(){
  for(int i=0; i<10; ++i){
    std::cout << "From My_Not_Throwing_Function() : " << i << '\n';
  }
}

int main(){
  std::thread my_thread(My_Thread_Function); 

  // Do some stuff in main()...
  My_Not_Throwing_Function();                                                   

  my_thread.join();                          
  
  std::cout << "\nStrike ENTER to exit :";
  std::cin.get();
}
*/



// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
// /*
#include <iostream>
#include <thread>
#include <random>

void fn1(){
  char const a_char ='_';

  std::default_random_engine my_dre(a_char);
  std::uniform_int_distribution<> id(10, 1000);                                 

  for(int i=0; i<20; ++i){
    std::this_thread::sleep_for(std::chrono::milliseconds(id(my_dre)));
    std::cout.put(a_char).flush();
  }
}

int main(){

  std::thread my_thread(fn1);                                                  
  
  try{
    char const a_char ='-';

    std::default_random_engine my_dre(a_char);
    std::uniform_int_distribution<> id(10, 1000);                                 

    for(int i=0; i<20; ++i){
      std::this_thread::sleep_for(std::chrono::milliseconds(id(my_dre)));
      std::cout.put(a_char).flush();
      if (i==10) throw std::runtime_error( "Exception for the fun." );            // comment this line and run again
    }

  }catch(std::exception const& e){
    std::cout << "Exception caught in main() : " << e.what() << '\n'; 
    my_thread.join();  
  }

  if(my_thread.joinable()){
    my_thread.join();  
  }

  std::cout << "\n\nStrike ENTER to exit :";                                        
  std::cin.get();
}
// */                                                                               




// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
/*
#include <iostream>
#include <thread>
#include <random>

void fn1(){
  char const a_char ='_';

  std::default_random_engine my_dre(a_char);
  std::uniform_int_distribution<> id(10, 1000);                                 

  for(int i=0; i<20; ++i){
    std::this_thread::sleep_for(std::chrono::milliseconds(id(my_dre)));
    std::cout.put(a_char).flush();
  }
}

void fn2(){
  char const a_char ='-';

  std::default_random_engine my_dre(a_char);
  std::uniform_int_distribution<> id(10, 1000);                                 

  for(int i=0; i<20; ++i){
    std::this_thread::sleep_for(std::chrono::milliseconds(id(my_dre)));
    std::cout.put(a_char).flush();
    if (i==10) throw std::runtime_error( "Exception for the fun." );            // comment this line and run again
  }
}

int main(){

  std::thread my_thread(fn1);                                                  
  
  try{
    fn2();
  }catch(std::exception const& e){
    std::cout << "Exception caught in main() : " << e.what() << '\n'; 
    my_thread.join();  
  }

  if(my_thread.joinable()){
    my_thread.join();  
  }

  std::cout << "\n\nStrike ENTER to exit :";                                        
  std::cin.get();
}
*/                                                                               



// Same as above but implements a try/catch block
// The exception is thrown in the main() function, NOT in the thread
// We want to .join() in a catch blocK
// However, if there is no exception, since we can .join() only once we need to think twice 
// .join() could be skipped if an exception happens before the call to .join()
// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
/*
#include <iostream>
#include <thread>

void My_Thread_Function(){
  std::cout << "Hello from thread " << __FUNCTION__ << '\n';
}

void My_Throwing_Function(){
  for(int i=0; i<10; ++i){                                                      
    std::cout << "From My_Throwing_Function() : " << i << '\n';                 // 2 - Do some printing and then...
  }
  throw std::logic_error( "For the fun." );                                     // 3 - Throw by value
                                                                                // Note : comment the line to see .joinable() at work in main()
}

int main(){
  std::thread my_thread(My_Thread_Function);                                    // 1 - Launch the thread

  // Do some stuff in main()
  try{                                                                          // 4 - Implement a try/catch block because My_Throwing_Function()
    My_Throwing_Function();                                                     // may throw an exeption
  }catch(std::exception const& e){                                              // 5 - Catch by reference
    my_thread.join();                                                           // Makes sure to join the thread
    std::cout << "Exception caught in main() : " << e.what() << '\n';                                   
  }                         
  
  if(my_thread.joinable())
    my_thread.join();                                                           // 6 - Join the trhead if My_Throwing_Function() did'nt throw 
                                                                                // Set a breakpoint and check that .joignable() is call when an exception has been thrown
              
                                                                                // We should/could use RAII around my_thread 
                                                                                // Doing so, in the destructor we could the use the .join() function call
                                                                                // This would simplify the code
  std::cout << "\nStrike ENTER to exit :";
  std::cin.get();
}
*/


/*
#include <iostream>
#include <thread>

void do_something(char a_char){
  for(int k=0; k<1000; ++k){
    std::cout.put(a_char).flush();
  }
  std::cout << "Thread " << a_char << "finished\n";
}



int main(){

  std::thread t0(do_something, '\\');
  std::thread t1(do_something, '-');
  std::thread t2(do_something, '/');
  std::thread t3(do_something, '-');

  t3.join();
  t2.join();
  t1.join();
  t0.join();

  std::cout << "\nStrike ENTER to exit :";
  std::cin.get();
}
*/





// page 19 - concurrency in action
// An exception in thrown in the main thread (NOT in the thread itself)
// The code shows how to propagate the exception to main()
// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
/*
#include <iostream>
#include <thread>

void do_something(int i){
  for(int k=0; k<1000; ++k){
    i++;
  }
}

struct func{
  int& m_i;
  
  func(int& i):m_i(i){}
  
  void operator()(){
    for(unsigned j=0; j<10000000; ++j){
      do_something(j);
    }
    std::cout << "The thread is done.\n";
  }
};

void do_something_in_current_thread(){
  throw std::runtime_error( "Exception for the fun." );
}

void f(){
  std::cout << "f() starts : \n"; 

  int some_local_state = 42;
  func my_func(some_local_state);
  std::thread t(my_func);
  try{
    do_something_in_current_thread();
  }catch(std::exception const& e){
    t.join();
    std::cout << "Exception caught in f() : " << e.what() << '\n'; 
    throw;
  }
  t.join();
}

int main(){
  try{
    f();
  }catch(std::exception const& e){
     std::cout << "Exception caught in main() : " << e.what() << '\n'; 
  }

  std::cout << "\nStrike ENTER to exit :";
  std::cin.get();
}
*/





// Same as above but implement RAII around the thread object 
// The .join() is now handeled in the destructor
// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
/*
#include <iostream>
#include <thread>

class Safe_Thread{                                                              // Z! This is a naïve RAII implementation
  public:
    Safe_Thread(std::thread t) : m_thread {std::move(t)} {                      // A thread cannot be copied but can be moved
    }

    ~Safe_Thread(){
      m_thread.join();                                                          // Note : Set a breakpoint here once you run the code once or twice
    }
  
  private:
    std::thread m_thread;
};

void My_Thread_Function(){
  std::cout << "Hello from thread " << __FUNCTION__ << '\n';
}

void My_Throwing_Function(){
  for(int i=0; i<10; ++i){                                                      
    std::cout << "From My_Throwing_Function() : " << i << '\n';                 
  }
  throw std::logic_error( "For the fun." );                                     
}                                                                               

int main(){

  Safe_Thread my_safe_thread {std::thread{My_Thread_Function}};                 // Create a Safe_Thread object and launch the thread

  // Do some stuff in main()
  try{                                                                          
    My_Throwing_Function();                                                     
  }catch(std::exception const& e){                                              
    std::cout << "Exception caught in main() : " << e.what() << '\n';           // No more .join() in the catch() block                
  }                         
                                                                                // No more .join() ouside the catch()
  std::cout << "\nStrike ENTER to exit :";
  std::cin.get();
}
*/


































// Implement the try/catch block
// Second example
// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
/*
#include <iostream>
#include <thread>
#include <exception>

void DoTheJob(){
  for(int i=0; i<10; ++i){
    std::cout << "From thread " << __FUNCTION__ << " : counter = " << i << '\n';
  }
  std::cout << "From thread " << __FUNCTION__ << " : throwing an execption." << '\n';
  throw std::runtime_error("Exception from thread");
}

void my_threadFunction(std::exception_ptr &err){
  try{
    DoTheJob();
  }catch(...){
    std::cout << "The thread caught an exception and returns it.\n";
    err = std::current_exception();
  }
}

void DoJobInThread(){
  std::exception_ptr err;
  std::thread t {my_threadFunction, std::ref(err)};

  // Do some stuff 

  t.join();

  if (err){
    std::cout << "main() thread received an exception. Rethrowing it\n";
    std::rethrow_exception(err);
  } else {
    std::cout << "main() did not received any exception.\n";
  }
}

int main(){

  try{
    DoJobInThread();
  }catch(std::exception const &e){
    std::cout << "main() caught : " << e.what() << '\n';
  }
  
  std::cout << "Strike ENTER to exit :";
  std::cin.get();
}
*/