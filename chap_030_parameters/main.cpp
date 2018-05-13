// Passing parameters to threads









// Use an async() call and pass a parameter to the function running in the thread 
// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
// /*
#include <iostream>
#include <future>
#include <string>

void my_function(std::string const msg){                                        // It is safe. The function gets its own copy of the string
  std::cout << "From thread : " << msg << '\n';
}

int main(){
  std::string my_message = "Greetings Pr Falken!";
  auto my_thread=async(my_function, my_message);                                 // The parameter to my_function is the second parameter of the async() call
                                                                                
  std::cout << "From main() : " << my_message << '\n';
  my_thread.get();  

  std::cout << "\nStrike ENTER to exit :";
  std::cin.get();
}
// */













// Rather than a passing a string by const value it might be smarter to pass a string_view
// Use a thread
// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
/*
#include <iostream>
#include <thread>
#include <string_view>

void my_function(std::string_view msg){
  std::cout << "From thread : " << msg << '\n';
}

int main(){
  std::string_view my_message = "Greetings Pr Falken!";                           
  std::thread my_thread(my_function, my_message); 
  std::cout << "From main() : " << my_message << '\n';
  my_thread.join();  

  std::cout << "\nStrike ENTER to exit :";
  std::cin.get();
}
*/










// Pass a parameter to a functor
// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
/*
#include <iostream>
#include <thread>
#include <string_view>

class MyFunctor{
  public:
  void operator()(std::string_view msg){
    std::cout << "From functor : " << msg << '\n';
  }
};

int main(){
  std::string_view my_message = "Greetings Pr Falken!";
  std::thread my_thread(MyFunctor{}, my_message);                                 // The parameter is the second parameter to the thread constructor
                                                                                 
  try{
    std::cout << "From main()  : " << my_message << '\n';
  }catch(...){
    my_thread.join();                          
    throw; 
  }
  my_thread.join();  

  std::cout << "\nStrike ENTER to exit :";
  std::cin.get();
}
*/









// Passing parameter by reference to the thread 
// A parameter to a thread is ALWAYS passed by value
// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
/*
#include <iostream>
#include <future>
#include <string>

void my_function1(std::string& msg){                                                                              
  std::cout << "From function  : " << msg << '\n';
  msg = "Now, the string is modified";                                          // 3 - The reference can be modified in a function
}

void my_function2(std::string& msg){                                                                              
  std::cout << "From thread    : " << msg << '\n';
  msg = "Now the string is modified again";                                     // 6 - The parameter is modified
  std::cout << "From thread    : " << msg << '\n';                              // 7 - The impact is local
}


int main(){
  std::string my_message = "Greetings Pr Falken!";
  std::cout << "From main()    : " << my_message << '\n';                       // 1 - Shows initial message  

  my_function1(my_message);                                                     // 2 - Pass the message as a reference
  std::cout << "Back in main() : " << my_message << '\n';                       // 4 - In effect, the message has been modified
  
  auto my_thread = async(my_function2, my_message);                               // 5 - Pass the parameter to the thread by reference
  my_thread.get();  
  std::cout << "From main()    : " << my_message << '\n';                       // 8 - but the modification does not propagate back to the main() function

  std::cout << "\nStrike ENTER to exit :";
  std::cin.get();
}
*/










// Passing parameter by reference to the thread 
// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
/*
#include <iostream>
#include <future>
#include <string>

void my_function(std::string& msg){                                                                              
  std::cout << "From function : " << msg << '\n';
  msg = "How about a nice game of chess?";                                      // 2 - The reference can be modified as usual
}

int main(){
  std::string my_message = "Greetings Pr Falken!";
  std::cout << "From main()   : " << my_message << '\n';                       
  
  auto my_thread = async(my_function, std::ref(my_message));                    // 1 - std::ref creates a reference wrapup around the parameter
  my_thread.get();  
  std::cout << "From main()   : " << my_message << '\n';                        // 3 - and the modification propagates back to the main() function
                                                                                // DANGER : this means 2 threads can modify the same asset at the same time
  std::cout << "\nStrike ENTER to exit :";
  std::cin.get();
}
*/









// Demonstrates the risk when 2 threads access the same asset 
// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
/*
#include <iostream>
#include <future>
#include <string>

void my_function(std::string& msg){                                                                              
  std::cout << "From function : " << msg << '\n';                               // 2 - the thread expects a string of chars, it may receive a string of digits
  msg = "How about a nice game of chess?";                                      // 3 - The thread can also modify the message
}

int main(){
  std::string my_message = "Greetings Pr Falken!";
  std::cout << "From main()   : " << my_message << '\n';                       
  
  auto my_thread=async(my_function, std::ref(my_message));                      
  my_message = "1 2 3 4 5 6 7 8 9";                                             // 1 - The main() thread can modify my_message
  
  my_thread.get();  
  std::cout << "From main()   : " << my_message << '\n';                        
                                                                                
  std::cout << "\nStrike ENTER to exit :";
  std::cin.get();
}
*/










// Passing parameter by reference to functor running in a thread 
// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
/*
#include <iostream>
#include <thread>
#include <string>

class MyFunctor{
  public:
  void operator()(std::string& msg){                                            
    std::cout << "From thread : " << msg << '\n';
    msg = "How about a nice game of chess?";
  }
};

int main(){
  std::string my_message = "Greetings Pr Falken!";
  std::thread my_thread(MyFunctor{}, std::ref(my_message));                     
  my_thread.join();  
                                                        
  std::cout << "From main() : " << my_message << '\n';

  std::cout << "\nStrike ENTER to exit :";
  std::cin.get();
}
*/










// If, in the main() function, the parameter is no longer needed after the thread initialization
// The parameter can be moved
// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
/*
#include <iostream>
#include <future>
#include <string>

void my_function(std::string msg){
  std::cout << "From thread : " << msg << '\n';
}

int main(){
  std::string my_message = "Greetings Pr Falken!";
  auto my_thread=std::async(my_function,  std::move(my_message));               // 1 - The parameter is a plain string but it is moved
                                                                                // Since my_message is not used in main() this is safe and efficient
  my_thread.get();  
  std::cout << "From main() : " << my_message << '\n';                          // 2 - my_message is no longer available
  
                                                                                // For info : threads cannot be copied but they can be moved
  // std::thread my_thread2 = my_thread1;                                       // Won't compile  
  // std::thread my_thread2 = std::move(my_thread1);                            // OK but then we must call "my_thread2.join();"                                                 

  std::cout << "\nStrike ENTER to exit :";
  std::cin.get();
}
*/