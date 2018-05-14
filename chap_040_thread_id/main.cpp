// Thread Id & Number of cores










// Retreive the Id of the thread
// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
// /*
#include <iostream>
#include <thread>

void Show_me_your_id(){
  std::thread::id my_id = std::this_thread::get_id();

  std::cout << "From thread : " << my_id << " is the Id of the thread\n";
}

int main(){                                                                     // Do no make any assumption about the returned value (0, 1000...)
  std::cout << "From main() : " << std::this_thread::get_id() << " is the Id of the main thread\n";

  std::thread my_thread(Show_me_your_id);
  my_thread.join();
  
  std::cout << "\nStrike ENTER to exit :";
  std::cin.get();
}
// */










// How many threads can run in parallel?
// May help to avoid oversubscrition
// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
/*
#include <iostream>
#include <thread>

int main(){
  std::cout << std::thread::hardware_concurrency() << " threads can run in parallel.\n";

  std::cout << "\nStrike ENTER to exit :";
  std::cin.get();
}
*/










// Two other hardware constants also helps to manage optimization of data locality
//      - hardware_destructive_interference_size 
//      - hardware_constructive_interference_size
// Before to play with them we should learn more about threads synchronization