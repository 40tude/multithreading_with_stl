# About the readers
- If you know multithreading, please "Fly, you fools"
- Otherwise knowing that I take some time to put black on white what I red/saw/heard your're more than welcome if you have constructve feedback
- For the rest, as a reader you're supposed to 
    - know some C++
    - have spent some time looking around for information about multithreading (youtube, book, web pages...)
    - be interrested in code snippets which could help you quickly experiments with what you learnt so far elsewhere
    - be willing to avoid the very low level thread API provided by your beloved platform (pthread and others)
    - trust the C++ committee to improve the high level tooling at our disposal

# About the chapters
- The topic is divided in chapters
- Since I don't know what will happen when I will add new chapters, even if today I already have 15 chapters they are numbered from 010 to 150
- Doing so, if at one point, I need to insert more chapters then I can name them 015 and 016 for example.
- However I will not hesitate to reorder the chapters if I really need.

# About the setup
- **OS :** So far I did the testing under Windows 10
- **Compiler :** I use Microsoft compiler. It is usually up to date. Today (May, 9 2017) it is self described as : C/C++ version 19.14.26428.1 for x64. All the code target x64 and it is compiled with std=c++17
- **IDE :** I propose to work with VS Code to edit and build the code snippets. I don't use Visual Studio here because each chapter consist of one single .cpp file. I wanted to keep the setup as light as possible (and yes, I know, Visual Studio can work without project nor solution but to tell the thruth I'm not yet able to do what I want in this mode)
- You might be interrested in readng this page to learn the detail about the setup : https://www.40tude.fr/blog/how-to-compile-cpp-code-with-vscode-cl/
- If you have another IDE, you should be able to copy and paste the C++ source code and compile it.  

# About the source code
- Each chapter consist of a single source code
- Each source code consist of one or more code section
- Each code section is physically separated from the previous one by at least 10 lines (this help to catch the eyes)
- Obviously, only one section can be active at one time otherwise the source contains 2 main() functions and it cannot be built. 
- So... Get prepared to use / and * or to use CTRL+(K, C) and CTRL+(K, U) to comment and uncomment sections of code
- Again, most code sections are autonomous. This means that each uncommented section can be compiled and build on its own. If the section cannot compile or crash at run time a comment warn you at the top of the section of code.
- Each code section contains a fair amount of comments
- These comments usually starts at row 81 (moderns screen and today resolution allow such setup)
- When needed, each comment on the right starts with a number. In this case read the comments following the numbers in increasing order. 
- While progressing along one main.cpp file, if one section of code is an improvment of the previous one then we avoid to repeat the same comments in order to ease the reading of the new section.

# About the process
## If you use VS code and cl
1. Open a developper console
2. Reach the directory of the chapter you're interrested in
3. On the command line interface type in : "code ." (don't forget the dot)
4. Once in VS Code, open the file main.cpp
5. Press CTRL+SHIFT+B to build the code (check tasks.json if needed)
6. SHIFT+F5 to run the debug version of the code
7. When the code ends, come back to the source and read the comments
8. Set breakpoints, debug and trace the code again and again. Ideally you should not need any console output. **The debugger is your friend!**
8. Copy/paste, modify, improve the code. Accumulate experience even if to do so you have to break everything :-)  

## If you don't use cl but use VS Code
1. Open VS Code
2. Open the folder of interrest (CTRL+K, CTRL+O)
4. Open the file main.cpp
3. Open and adapt the tasks.json file
4. Open and adapt the launch.json
5. CTRL+SHIFT+B to build the code
6. SHIFT+F5 to run the debug version
7. Come back to the source and read the comments
8. Set breakpoints, debug and trace the code again and again. Ideally you should not need any console output. **The debugger is your friend!**
8. Copy/paste, modify, improve the code. Accumulate experience even if to do so you have to break everything :-)  

If under Windows you use clang with VS Code you might be interrested in this post : https://www.40tude.fr/blog/compile-cpp-code-with-vscode-clang/

## If you don't use cl nor VS Code
1. Reach the folder of interrest 
2. Copy the file main.cpp
3. Past it in your favorite toolchain
4. Build the code
5. Run the debug version
6. Come back to the source and read the comments
7. Set breakpoints, debug and trace the code again and again. Ideally you should not need any console output. **The debugger is your friend!**
8. Copy/paste, modify, improve the code. Accumulate experience even if to do so you have to break everything :-)  




# Webliograpphy
## Youtube
- [This playlist](https://www.youtube.com/watch?v=eeSC43KQdVI&list=PL_dsdStdDXbrzGQUMh2sy6T8GcCCst3Nm)
- [Bo Qian playlist on concurrency](https://www.youtube.com/watch?v=LL8wkskDlbs&list=PL5jc9xFGsL8E12so1wlMS0r0hTQoJL74M)
- ...

## Books
- [Concurrency in Action](https://www.amazon.fr/gp/product/1617294691/ref=s9u_newr_gw_i4?ie=UTF8&pd_rd_i=1617294691&pd_rd_r=e2edadf8-5395-11e8-ad28-014ae5dc2f42&pd_rd_w=IDehF&pd_rd_wg=vzsJP&pf_rd_m=A1X6FK5RDHNB96&pf_rd_s=&pf_rd_r=Y9F3KRN8RP51AKXYGBAY&pf_rd_t=36701&pf_rd_p=b2aa2a3e-4691-4349-8b50-65f9675cdf61&pf_rd_i=desktop)
- The last chapter (or so) of [The C++ Standard Library: A Tutorial and Reference](https://www.amazon.fr/Standard-Library-Tutorial-Reference/dp/0321623215/ref=pd_sbs_14_7?_encoding=UTF8&psc=1&refRID=0091QTZDXYP9QYR5G3XJ)
- ...

## Web pages
- ...
