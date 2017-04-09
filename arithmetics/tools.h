#define GREEN   "\x1b[32m"
#define YELLOW  "\x1b[33m"
#define RESET   "\x1b[0m"
#define RED     "\x1b[31m"

#define ERR(...)\
    {\
        fprintf(stderr, __VA_ARGS__);\
        fprintf(stderr, "\nERRNO: %s\n", strerror(errno));\
        exit(EXIT_FAILURE);\
    }

#define ERRTEST(...) \
    if ((__VA_ARGS__) == -1) \
        ERR("Code line: [" #__VA_ARGS__ "]")

#ifdef DEBUG

#define PRINT(...)\
    {\
        printf(__VA_ARGS__);\
        printf("\n");\
    }

#else

#define PRINT(...) {};

#endif
