//
//  SmartPtrClass.hpp
//  PointerQuiz
//
//  Created by Andrew Cotter on 3/1/17.
//
//

#ifndef SmartPtrClass_hpp
#define SmartPtrClass_hpp

#include <stdio.h>

class SmartPtr;

typedef std::shared_ptr<SmartPtr> SmartPtrRef;

class SmartPtr
{
public:
    static SmartPtrRef create ();
};

#endif /* SmartPtrClass_hpp */
