//
// Created by Christian Ott on 22.01.2017.
//

#ifndef CPP16_SMART_POINTER_H
#define CPP16_SMART_POINTER_H

#include <cstddef>

#include "smart_pointer_store.h"

namespace pointer {

    template <typename T> // T models the Object
    class smart_pointer {
        typedef T* StoredType;
        typedef T* PointerType;
        typedef T& ReferenceType;

        StoredType pointee; // Data

        detail::SmartPointerStore* store;

    public:
        //  This is to prevent a memory leak in the process of object instantiation.
        smart_pointer() : pointee(nullptr), store(nullptr) {}

        smart_pointer(StoredType ptr) : smart_pointer() {
            pointee = ptr;
            store = new detail::SmartPointerStore();
            store->addRef();
        }

        smart_pointer(const smart_pointer<T>& sp) : pointee(sp.pointee), store(sp.store) {
            store->addRef();
        }

        smart_pointer& operator=(const smart_pointer<T>& sp) {
            if (this != &sp) {
                if (store->releaseRef() == 0) {
                    delete store;
                    delete pointee;
                }

                pointee = sp.pointee;
                store = sp.store;
                store->addRef();
            }

            return *this;
        }

        ~smart_pointer() {
            if (pointee != nullptr) {
                if (store->releaseRef() == 0) {
                    delete store;
                    delete pointee;
                }
            }
        }

        ReferenceType operator*()  const {return *pointee;}
        PointerType   operator->() const {return pointee;}

        // Only for the assignement.
        unsigned counter() {
            if (pointee == nullptr) {
                return 0; // but should throw something
            }
            return store->counter();
        }

    };

}

#endif //CPP16_SMART_POINTER_H
