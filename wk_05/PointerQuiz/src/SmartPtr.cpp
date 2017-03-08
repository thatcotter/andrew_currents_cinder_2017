//
//  SmartPtrClass.cpp
//  PointerQuiz
//
//  Created by Andrew Cotter on 3/1/17.
//
//

#include "SmartPtr.hpp"

SmartPtrRef SmartPtr::create()
{
    SmartPtrRef ref = std::shared_ptr<SmartPtr>( new SmartPtr());
    return ref;
}
