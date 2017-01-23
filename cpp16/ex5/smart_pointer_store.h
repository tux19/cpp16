#ifndef CPP16_SMART_POINTER_STORE_H
#define CPP16_SMART_POINTER_STORE_H
namespace pointer {
    namespace detail {

        class SmartPointerStore {
            unsigned count;

        public:
            void addRef() {++count;}
            unsigned releaseRef(){return --count;}

            // Only for the assignment:
            unsigned counter () {return count;}
        };


    }
}
#endif //CPP16_SMART_POINTER_STORE_H
