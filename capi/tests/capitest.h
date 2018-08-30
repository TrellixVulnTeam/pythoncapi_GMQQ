#ifndef CAPITEST_H
#define CAPITEST_H

typedef enum {
    capitest_enum_SUCCESS,
    capitest_enum_FAIL,
    capitest_enum_SKIPPED
} capitest_ResultEnum;

typedef struct {
    capitest_ResultEnum result;
    const char *msg;
    const char *filename;
    int lineno;
} capitest_Result;

#define capitest_FAIL_MSG(message) \
    (capitest_Result){.result = capitest_enum_FAIL, .msg = (message), .filename = __FILE__, .lineno = __LINE__}
#define capitest_FAIL(message) capitest_FAIL_MSG(NULL)
#define capitest_SUCCESS() \
    (capitest_Result){.result = capitest_enum_SUCCESS, .filename = __FILE__, .lineno = __LINE__}

typedef capitest_Result (*capitest_TestFunc) ();

typedef struct {
    capitest_Result result;
    const char *name;
    capitest_TestFunc func;
} capitest_Test;

typedef struct {
    size_t ntest;
    /* FIXME: don't use hardcoded array size */
    capitest_Test tests[10];
} capitest_TestSuite;

#define capitest_TestSuite_INIT {.ntest = 0}

void capitest_register(capitest_TestSuite *suite, const char *name, capitest_TestFunc func);
void capitest_run_test(capitest_Test *test);
int capitest_run_testsuite(capitest_TestSuite *suite);

#endif   /* CAPITEST_H */
