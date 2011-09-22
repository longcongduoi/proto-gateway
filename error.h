#ifndef ERROR_H
#define ERROR_H

#include "bacnetcommon.h"
namespace Bacnet {

    class Error {
    public:
        Error();
        Error(BacnetError::ErrorClass errorClass, BacnetError::ErrorCode errorCode);

        bool hasError();
        void setError(BacnetError::ErrorClass errorClass, BacnetError::ErrorCode errorCode);
    public:
        BacnetError::ErrorClass errorClass;
        BacnetError::ErrorCode errorCode;
    };

}

#endif // ERROR_H