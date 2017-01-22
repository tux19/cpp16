//
// Created by Christian Ott on 22.01.2017.
//

#ifndef CPP16_DUMB_POINTER_H
#define CPP16_DUMB_POINTER_H


namespace pointer {

    template <typename T> // T models the pointee.
    class dumb_pointer {
        typedef T* StoredType;
        typedef T* PointerType;
        typedef T& ReferenceType;

        StoredType pointee;

    public:
        explicit dumb_pointer(StoredType obj) : pointee(obj) {};

        dumb_pointer(const dumb_pointer<T>& another) : pointee(another.pointee) {};

        dumb_pointer& operator=(const dumb_pointer<T>& dp) {
            pointee = dp.pointee;
        }


        // Either that or a cast. Which would be even dumber.
        void deletePointee() {
            delete pointee;
        }

        ReferenceType operator*()  const {return *pointee;}
        PointerType   operator->() const {return pointee;}

    };

}


#endif //CPP16_DUMB_POINTER_H
