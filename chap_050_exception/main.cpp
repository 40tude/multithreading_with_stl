// https://www.youtube.com/watch?v=f2nMqNj7vxE&list=PL5jc9xFGsL8E12so1wlMS0r0hTQoJL74M&index=2

// Exceptions


// If a thread is destroyed BEFORE it is joined or detached then the program will terminate
// We need to decide BEFORE the thread goes out of scope if we want to join() or detach()
// In the for loop, without try/catch blocks, if an exception is thrown then my_thread is destroyed before it is joined
// => we need to wrap it up with try & catch
// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
/**/
#include <iostream>
#include <thread>

void MyFunction(){
  std::cout << "Hello from thread " << __FUNCTION__ << '\n';
}

int main(){
  std::thread my_thread(MyFunction); 

  // Do some stuff in main()...
  for(int i=0; i<100; ++i)
    std::cout << "From main() : " << i << '\n';

  my_thread.join();                          
  
  std::cout << "Strike ENTER to exit :";
  std::cin.get();
}
/**/










// Implement the try/catch block
// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
/*
#include <iostream>
#include <thread>

void MyFunction(){
  std::cout << "Hello from thread " << __FUNCTION__ << '\n';
}

int main(){
  std::thread my_thread(MyFunction); 

  // Do some stuff in main()
  try{
    for(int i=0; i<100; ++i)
      std::cout << "From main() : " << i << '\n';
  }catch(...){
    my_thread.join();                                                            // If the thread throw an exception we join here then                    
    throw;                                                                       // retrow the exception hoppping someone will take care of it
  }                         
  my_thread.join();                                                              // If the thread does not throw an exception we join here
              
  // We should/could use RAII around my_thread 
  // In the destructor we could the use the join() function call

  std::cout << "Strike ENTER to exit :";
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
  std::cout << "From thread " << __FUNCTIONW__ << " : throwing an execption." << '\n';
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