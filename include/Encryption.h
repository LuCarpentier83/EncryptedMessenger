#ifndef ENCRYPTION_H
#define ENCRYPTION_H

template <typename T, typename U>
class disp {
public:
    disp(T value, U value2) : data(value), data2(value2) {}
    auto add() {return data+data2;}
private:
    T data;
    U data2;
};
#endif //ENCRYPTION_H
