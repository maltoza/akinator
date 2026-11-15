#ifndef ERROR_H
#define ERROR_H

#define RETURN_ERROR(err_code) do {                                               \
    printf("%s:%d error (%d) %s\n", __FILE__,  __LINE__, err_code, __FUNCTION__); \
    return err_code;                                                              \
} while (0)

#endif // ERROR_H