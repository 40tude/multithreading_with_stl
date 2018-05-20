// Exceptions










// If a thread is destroyed BEFORE it is joined or detached then the program terminates 
// We need to decide BEFORE the thread goes out of scope if we want to join() or detach() 
// In the code below, everything works fine : no exception, no problem...
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

int main(){

  std::thread my_thread(fn1);                                                  
  
  // Do some stuff in main()...
  {
    char const a_char ='-';

    std::default_random_engine my_dre(a_char);
    std::uniform_int_distribution<> id(10, 1000);                                 

    for(int i=0; i<20; ++i){
      std::this_thread::sleep_for(std::chrono::milliseconds(id(my_dre)));
      std::cout.put(a_char).flush();
    }
  }
  my_thread.join();  

  std::cout << "\n\nStrike ENTER to exit :";                                        
  std::cin.get();
}
*/                                                                               







// Same as above but implements a try/catch block
// The exception is thrown in the main() function, NOT in the thread
// We must .join() in the catch blocK
// However, if there is no exception, since we can .join() only once we need to think twice 
// Remember : .join() could be skipped if an exception happens before the call to .join()
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
    std::cout << "Exception caught in main() : " << e.what() << '\n';             // observe on screen how the thread continue after the catch
    my_thread.join();  
  }

  if(my_thread.joinable()){                                                       // if no exception then the thread is joinable otherwise it is not
    my_thread.join();  
  }

  std::cout << "\n\nStrike ENTER to exit :";                                        
  std::cin.get();
}
*/                                                                               










// Same as above but part of the code is now in fn2()
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
    if (i==10) throw std::runtime_error( "Exception for the fun." );            
  }
}

int main(){

  std::thread my_thread(fn1);                                                  
  
  try{
    fn2();                                                                      // fn2() is in a try block because it may throw
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















// see also page 19 of concurrency in action
// An exception in thrown in the main thread (NOT in the thread itself)
// The code shows how to propagate the exception back to main()
// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
/*
#include <iostream>
#include <thread>
#include <random>

void do_something(char const a_char){

  std::default_random_engine my_dre(a_char);
  std::uniform_int_distribution<> id(10, 1000);                                 

  for(int i=0; i<20; ++i){
    std::this_thread::sleep_for(std::chrono::milliseconds(id(my_dre)));
    std::cout.put(a_char).flush();
  }
}

struct func{
  char& m_c;
  
  func(char& c) : m_c {c} {}
  
  void operator()(){
    do_something(m_c);
    std::cout << "The thread is done.\n";
  }
};

void do_something_in_current_thread(){
  char const a_char ='-';

  std::default_random_engine my_dre(a_char);
  std::uniform_int_distribution<> id(10, 1000);                                 

  for(int i=0; i<20; ++i){
    std::this_thread::sleep_for(std::chrono::milliseconds(id(my_dre)));
    std::cout.put(a_char).flush();
    if (i==10) throw std::runtime_error( "Exception for the fun." );            
  }
}

void f(){
  char some_local_state = '_';
  func my_func(some_local_state);
  std::thread t(my_func);
  
  try{
    do_something_in_current_thread();
  }catch(std::exception const& e){
    std::cout << "Exception caught in f() : " << e.what() << '\n'; 
    t.join();                                                                   // see in the console how t terminates before the execption is rethrown
    throw;                                                                      // rethrow the exception back to main() 
  }

  if(t.joinable()){                                                             // if exception happen t is already joined
    t.join();                                                                   // otherwise t is .join() here and now
  }
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
#include <random>

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
  char const a_char{'_'};

  std::default_random_engine my_dre(a_char);
  std::uniform_int_distribution<> id(10, 1000);                                 

  for(int i=0; i<20; ++i){
    std::this_thread::sleep_for(std::chrono::milliseconds(id(my_dre)));
    std::cout.put(a_char).flush();
  }
}

void My_Throwing_Function(){
  char const a_char ='-';

  std::default_random_engine my_dre(a_char);
  std::uniform_int_distribution<> id(10, 1000);                                 

  for(int i=0; i<20; ++i){
    std::this_thread::sleep_for(std::chrono::milliseconds(id(my_dre)));
    std::cout.put(a_char).flush();
    if (i==10) throw std::runtime_error( "Exception for the fun." );            
  }
}                                                                               

int main(){

  //std::thread t {My_Thread_Function};
  //Safe_Thread my_safe_thread {std::move(t)};                                  // A thread cannot be copied but can be moved
  Safe_Thread my_safe_thread {std::thread{My_Thread_Function}};                 // Replace the 2 line above

  // Do some stuff in main()
  try{                                                                          
    My_Throwing_Function();                                                     
  }catch(std::exception const& e){                                              
    std::cout << "Exception caught in main() : " << e.what() << '\n';           // No more .join() in the catch() block                
  }                         
                                                                                // No more .join() outside the catch()

  std::cout << "\nStrike ENTER to exit :";                                      // Press ENTER quickly and watch in the console how the background thread 
  std::cin.get();                                                               // continues and ends before the application closes the console.
}
*/








// Exception in the thread
// Crash at runtime
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
    if (i==10) throw std::runtime_error( "Exception for the fun." ); 
  }
}

void fn2(){
  char const a_char ='-';

  std::default_random_engine my_dre(a_char);
  std::uniform_int_distribution<> id(10, 1000);                                 

  for(int i=0; i<20; ++i){
    std::this_thread::sleep_for(std::chrono::milliseconds(id(my_dre)));
    std::cout.put(a_char).flush();
               
  }
}

int main(){

  std::thread my_thread(fn1);                                                  
  fn2();                                                                      
  my_thread.join();  

  std::cout << "\n\nStrike ENTER to exit :";                                        
  std::cin.get();
}
*/                                                                               








// even with a try catch block aroutnt he thread it does'nt work
// the thread call std::terminate and abort the application
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
    if (i==10) throw std::runtime_error( "Exception for the fun." ); 
  }
}

void fn2(){
  char const a_char ='-';

  std::default_random_engine my_dre(a_char);
  std::uniform_int_distribution<> id(10, 1000);                                 

  for(int i=0; i<20; ++i){
    std::this_thread::sleep_for(std::chrono::milliseconds(id(my_dre)));
    std::cout.put(a_char).flush();
               
  }
}

int main(){

  try{
    std::thread my_thread(fn1);                                                  
    my_thread.join();                                                               // somehow ineficient... Sicne we wait here the end of the thread                                          
  }catch(std::exception const& e){ 
    std::cout << "Exception intercepted in main() : " << e.what() << '\n';           // No more .join() in the catch() block                
  }

  fn2();                                                                      
  
  std::cout << "\n\nStrike ENTER to exit :";                                        
  std::cin.get();
}
*/                                                                               









// async comes to the rescue (again?)
// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
// /*
#include <iostream>
#include <random>
#include <future>

void fn1(){
  char const a_char ='_';

  std::default_random_engine my_dre(a_char);
  std::uniform_int_distribution<> id(10, 1000);                                 

  for(int i=0; i<20; ++i){
    std::this_thread::sleep_for(std::chrono::milliseconds(id(my_dre)));
    std::cout.put(a_char).flush();
    if (i==10) throw std::runtime_error( "Exception for the fun." ); 
  }
}

void fn2(){
  char const a_char ='-';

  std::default_random_engine my_dre(a_char);
  std::uniform_int_distribution<> id(10, 1000);                                 

  for(int i=0; i<20; ++i){
    std::this_thread::sleep_for(std::chrono::milliseconds(id(my_dre)));
    std::cout.put(a_char).flush();
  }
}

int main(){

  try{
    auto result = std::async(fn1);
    fn2();  
    result.get();                                                               // comment this line and realise that the exception is then NOT prapagated
  }catch(std::exception const& e){ 
    std::cout << "Exception propagated back to main() : " << e.what() << '\n';                        
  }
  
  std::cout << "\n\nStrike ENTER to exit :";                                        
  std::cin.get();
}
// */                                                                               
