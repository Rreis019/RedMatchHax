#pragma once

void initLogger();
void closeLogger();

#ifdef _DEBUG //If release mod

#define INIT_CONSOLE() initLogger()
#define CLOSE_CONSOLE() closeLogger();
#define PRINT(format, ...)  printf(format, __VA_ARGS__)
#define PRINT_POINTER(x) printf("%s = %p\n", #x, x)

#else

#define INIT_CONSOLE()
#define CLOSE_CONSOLE()
#define PRINT(format, ...)
#define PRINT_POINTER(x)

#endif // !_DEBUG //If release mod
