#ifdef _WIN32 //makes clearConsole portable for *NIX based terminals(thanks skosveinar)
const bool is_windows = 1; //had to use bool instead of string, otherwise I had endless linker errors
#else
const bool iswindows = 0;
#endif
