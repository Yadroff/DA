#ifndef INC_1LAB_SRC_QUEUE_HPP
#define INC_1LAB_SRC_QUEUE_HPP

int abs(int x){
    return x > 0 ? x : -1 * x;
}

template<typename T>
class TQueue {
    TQueue(): FIRST(0), LAST(1), QUEUE_SIZE(10){
        QUEUE = new T[10];
    };
    void push(T item){
        if (abs(FIRST - LAST) < QUEUE_SIZE){
            LAST = (LAST + 1) % QUEUE_SIZE;
            return;
        }
        T* queue = new T[QUEUE_SIZE * 2];
        int cnt = -1;
        for (int i = FIRST; i != LAST; i = (i + 1) % QUEUE_SIZE){
            queue[++cnt] = QUEUE[i];
        }
        FIRST = 0;
        LAST = cnt;
        QUEUE = queue;
        delete[] queue;
    }
    T top(){
        if (FIRST != LAST){
            return QUEUE[FIRST];
        }
    }
    void pop(){
        FIRST = (FIRST + 1) % QUEUE_SIZE;
    }

private:
    T* QUEUE;
    int FIRST;
    int LAST;
    int QUEUE_SIZE;
};


#endif //INC_1LAB_SRC_QUEUE_HPP
