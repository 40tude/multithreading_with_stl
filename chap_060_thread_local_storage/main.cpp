// Thread local storage










// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
/*
#include <iostream>
#include <thread>

thread_local int gtl_my_var = 200;                                              // Each thread get a its own unique copy
             int g_my_var   = 100;                                              // All threads can access g_my_var
                                                                                // This is a shared ressource => synchro mechanisms are needed
void MyFunction(){
  std::cout << "In " << __FUNCTION__ << "()\n";
  std::cout << "\tBefore increment :\n";
  std::cout << "\t\tg_my_var   = " << g_my_var << '\n';
  std::cout << "\t\tgtl_my_var = " << gtl_my_var << '\n';
  ++g_my_var;
  ++gtl_my_var;
  std::cout << "\tAfter increment :\n";
  std::cout << "\t\tg_my_var   = " << g_my_var << '\n';
  std::cout << "\t\tgtl_my_var = " << gtl_my_var << '\n';
}

int main(){
  std::cout << "In " << __FUNCTION__ << "()\n";
  std::cout << "\t\tg_my_var   = " << g_my_var << '\n';
  std::cout << "\t\tgtl_my_var = " << gtl_my_var << '\n';

  std::thread MyThread1(MyFunction);                                            // MyThread starts at this point
  MyThread1.join();                                                             // main() waits for MyThread

  std::cout << "In " << __FUNCTION__ << "()\n";
  std::cout << "\t\tg_my_var   = " << g_my_var << '\n';
  std::cout << "\t\tgtl_my_var = " << gtl_my_var << '\n';

  std::thread MyThread2(MyFunction);                                            // MyThread starts at this point
  MyThread2.join();                                                             // main() waits for MyThread

  std::cout << "In " << __FUNCTION__ << "()\n";
  std::cout << "\t\tg_my_var   = " << g_my_var << '\n';
  std::cout << "\t\tgtl_my_var = " << gtl_my_var << '\n';

  std::cout << "\n\nStrike ENTER to exit :";
  std::cin.get();
}
*/







// Same as above with async()
// Pay attention to the std::launch::deferred used with the async()
// Here, no thread are used. MyFunction() is executed in the main() thread
// This is also why gtl_my_var and g_my_var behave the same way (both like global variables)
// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
/*
#include <iostream>
#include <future>

thread_local int gtl_my_var = 200;                                              // Each thread get a its own unique copy
             int g_my_var   = 100;                                              // All threads can access g_my_var
                                                                                // This is a shared ressource => synchro mechanisms are needed
void MyFunction(){
  std::cout << "In " << __FUNCTION__ << "()\n";
  std::cout << "\tBefore increment :\n";
  std::cout << "\t\tg_my_var   = " << g_my_var << '\n';
  std::cout << "\t\tgtl_my_var = " << gtl_my_var << '\n';
  ++g_my_var;
  ++gtl_my_var;
  std::cout << "\tAfter increment :\n";
  std::cout << "\t\tg_my_var   = " << g_my_var << '\n';
  std::cout << "\t\tgtl_my_var = " << gtl_my_var << '\n';
}

int main(){
  std::cout << "In " << __FUNCTION__ << "()\n";
  std::cout << "\t\tg_my_var   = " << g_my_var << '\n';
  std::cout << "\t\tgtl_my_var = " << gtl_my_var << '\n';

  auto result = std::async(std::launch::deferred, MyFunction);                  // No threading involved
  result.get();                                                                 // The function is called here in the main() thread

  std::cout << "In " << __FUNCTION__ << "()\n";
  std::cout << "\t\tg_my_var   = " << g_my_var << '\n';
  std::cout << "\t\tgtl_my_var = " << gtl_my_var << '\n';

  result = std::async(std::launch::deferred, MyFunction);                       // No threading involved
  result.get();                                                                 // The function is called here in the main() thread

  std::cout << "In " << __FUNCTION__ << "()\n";
  std::cout << "\t\tg_my_var   = " << g_my_var << '\n';
  std::cout << "\t\tgtl_my_var = " << gtl_my_var << '\n';

  std::cout << "Strike ENTER to exit :";                                        // Pay lot of attention to the console output
  std::cin.get();                                                               // Everything look like we have 2 global variables
}
*/







// Using std::launch::async ensure a thread is created in order to run MyFunction
// From now, async() will be always using std::launch::async
// May 20 2018 : I suspect an issue here with the TLS and how cl manage it
// On the seconde call to Myfunction the TLS should be 200 and NOT 201
// Email sent to Dev Community
// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
// /*
#include <iostream>
#include <future>

thread_local int gtl_my_var = 200;                                              // Each thread get a its own unique copy
             int g_my_var   = 100;                                              // All threads can access g_my_var
                                                                                // This is a shared ressource => synchro mechanisms are needed
void MyFunction(){
  std::cout << "In " << __FUNCTION__ << "()\n";
  std::cout << "\tBefore increment :\n";
  std::cout << "\t\tg_my_var   = " << g_my_var << '\n';
  std::cout << "\t\tgtl_my_var = " << gtl_my_var << '\n';
  ++g_my_var;
  ++gtl_my_var;
  std::cout << "\tAfter increment :\n";
  std::cout << "\t\tg_my_var   = " << g_my_var << '\n';
  std::cout << "\t\tgtl_my_var = " << gtl_my_var << '\n';
}

int main(){
  std::cout << "In " << __FUNCTION__ << "()\n";
  std::cout << "\t\tg_my_var   = " << g_my_var << '\n';
  std::cout << "\t\tgtl_my_var = " << gtl_my_var << '\n';

  auto result = std::async(std::launch::async, MyFunction);
  result.get();

  std::cout << "In " << __FUNCTION__ << "()\n";
  std::cout << "\t\tg_my_var   = " << g_my_var << '\n';
  std::cout << "\t\tgtl_my_var = " << gtl_my_var << '\n';

  result = std::async(std::launch::async, MyFunction);
  result.get();


  std::cout << "In " << __FUNCTION__ << "()\n";
  std::cout << "\t\tg_my_var   = " << g_my_var << '\n';
  std::cout << "\t\tgtl_my_var = " << gtl_my_var << '\n';

  std::cout << "Strike ENTER to exit :";
  std::cin.get();
}
// */










// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
/*
#include <iostream>
#include <thread>

void MyFunction(){
  thread_local int tl_my_var = 200;                                             // Declared locally => behaves like a static variable

  std::cout << "From " << __FUNCTION__ << " tl_my_var = " << tl_my_var << '\n';
  tl_my_var++;
  std::cout << "\n\n";
}


int main(){

  std::thread MyThread1(MyFunction);                                            // MyThread starts at this point
  MyThread1.join();                                                             // main() waits for MyThread

  std::thread MyThread2(MyFunction);                                            // MyThread starts at this point
  MyThread2.join();                                                             // main() waits for MyThread

  std::cout << "Strike ENTER to exit :";
  std::cin.get();
}
*/









// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
/*
#include <iostream>
#include <future>

int g_my_var   = 100;                                                           // All threads can access g_my_var
                                                                                // This is a shared ressource => synchro mechanisms are needed
void MyFunction(){
  thread_local int tl_my_var = 200;                                             // Declared locally => behaves like a static variable

  std::cout << "In " << __FUNCTION__ << "()\n";
  std::cout << "\tBefore increment :\n";
  std::cout << "\t\tg_my_var   = " << g_my_var << '\n';
  std::cout << "\t\tgtl_my_var = " << tl_my_var << '\n';
  ++g_my_var;
  ++tl_my_var;
  std::cout << "\tAfter increment :\n";
  std::cout << "\t\tg_my_var   = " << g_my_var << '\n';
  std::cout << "\t\tgtl_my_var = " << tl_my_var << '\n';
}

int main(){
  std::cout << "In " << __FUNCTION__ << "()\n";
  std::cout << "\t\tg_my_var   = " << g_my_var << '\n';

  auto result = std::async(std::launch::async, MyFunction);
  result.get();

  std::cout << "In " << __FUNCTION__ << "()\n";
  std::cout << "\t\tg_my_var   = " << g_my_var << '\n';

  result = std::async(std::launch::async, MyFunction);
  result.get();


  std::cout << "In " << __FUNCTION__ << "()\n";
  std::cout << "\t\tg_my_var   = " << g_my_var << '\n';

  std::cout << "Strike ENTER to exit :";
  std::cin.get();
}
*/
