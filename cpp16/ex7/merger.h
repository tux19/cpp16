#ifndef CPP16_MERGE_H
#define CPP16_MERGE_H


template<typename input1,
        typename input2 = input1,
        typename output = input1>
class merger {
public:

    static void merge(const input1 &in1, const input2 &in2, output &out){
        std::copy(in1.begin(), in1.end(), std::back_inserter(out));
        std::copy(in2.begin(), in2.end(), std::back_inserter(out));
    }
};


#endif //CPP16_MERGE_H
