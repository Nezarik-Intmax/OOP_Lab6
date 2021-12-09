#ifndef MYCONTAINER_H
#define MYCONTAINER_H
template <class T>
class MyContainerNode{
public:
    MyContainerNode* next;
    MyContainerNode* prev;
    T* node;
    MyContainerNode(T* node){
        this->node = node;
        this->prev = nullptr;
        this->next = nullptr;
    }
    MyContainerNode(T* node, MyContainerNode* prev){
        this->node = node;
        this->prev = prev;
        this->next = nullptr;
    }
    MyContainerNode(T* node, MyContainerNode* prev, MyContainerNode* next){
        this->node = node;
        this->prev = prev;
        this->next = next;
    }
    ~MyContainerNode(){
        next = nullptr;
        prev = nullptr;
    }
};
template <class T>
ref class MyContainer{
private:
    MyContainerNode<T>* head;
    MyContainerNode<T>* tail;
    MyContainerNode<T>* current;
public:
    MyContainer(){
        head = nullptr;
        tail = nullptr;
        current = nullptr;
    }
    MyContainer(T* a){
        head = a;
        tail = a;
        current = a;
    }
    void add(T *a);
    void add(T a, int index);
    void pop();
    void pop(T a);
    void popCurrent();
    void popIndex(int a);
    void first();
    void last();
    bool eol();
    void next();
    void prev();
    MyContainerNode<T> getObject();
    MyContainerNode<T> getObject(int a);
    int length();
};
template <class T>
void MyContainer<T>::add(T *a){
    if(tail == nullptr){
        head = new MyContainerNode<T>(a);
        tail = head;
    } else{
        MyContainerNode<T>* newNode = new MyContainerNode<T>(a, tail);
        tail->next = newNode;
        tail = newNode;
    }
}
template <class T>
void MyContainer<T>::add(T a, int index){
    if((this->length() == 0) || (this->length() == index)){
        this->add(a);
    } else if(index == 0){
        MyContainerNode<T>* newNode = new MyContainerNode<T>(a, nullptr, head);
        head->prev = newNode;
        head = newNode;

    } else if((head != nullptr) && (this->length() > index)){
        MyContainerNode<T>* tempNode = head;
        for(int i = 0; i < index; i++){
            tempNode = tempNode->next;
        }
        MyContainerNode<T>* newNode = new MyContainerNode<T>(a, tempNode->prev, tempNode);
        tempNode->prev->next = newNode;
        tempNode->prev = newNode;
    }
}
template <class T>
void MyContainer<T>::pop(){
    if(tail==head){
        head->next = nullptr;
        delete(head);
        head = nullptr;
        tail = nullptr;
    }else if(tail != nullptr){
        MyContainerNode<T>* newNode = tail->prev;
        delete(tail);
        tail = newNode;
        tail->next = nullptr;
    }
}
template <class T>
void MyContainer<T>::pop(T a){
    if(head != nullptr){
        MyContainerNode<T>* newNode = head;
        do{
            if(newNode->node == a){
                newNode->prev->next = newNode->next;
                delete(newNode);
            }
            newNode = newNode->next;
        }while (newNode!=nullptr);
    }
}
template <class T>
void MyContainer<T>::popCurrent(){
    if(current != nullptr){
        MyContainerNode<T>* newNode = current;
        current = current->next;
        if((newNode->prev != nullptr) && (newNode->next != nullptr)){
            newNode->prev->next = newNode->next;
            newNode->next->prev = newNode->prev;
        } else if(newNode->prev != nullptr){
            newNode->prev->next = nullptr;
            current = nullptr;
            tail = newNode->prev;
        } else if(newNode->next != nullptr){
            newNode->next->prev = nullptr;
            head = newNode->next;
        }else{
            head = nullptr;
            tail = nullptr;
            current = nullptr;
        }
        delete(newNode);
    }
}
template <class T>
void MyContainer<T>::popIndex(int a){
    if((head != nullptr)&&(this->length() > a)){
        MyContainerNode<T>* newNode = head;
        for(int i = 0; i < a; i++){
            newNode = newNode->next;
        }
        if((newNode->prev != nullptr)&&(newNode->next != nullptr)){
            newNode->prev->next = newNode->next;
            newNode->next->prev = newNode->prev;
        }else if(newNode->prev != nullptr){
            newNode->prev->next = nullptr;
            tail = newNode->prev;
        }else if(newNode->next != nullptr){
            newNode->next->prev = nullptr;
            head = newNode->next;
        }
        delete(newNode);
    }
}
template <class T>
void MyContainer<T>::first(){
    if(head != nullptr)
        current = head;
}
template <class T>
void MyContainer<T>::last(){
    if(tail != nullptr)
        current = tail;
}
template <class T>
bool MyContainer<T>::eol(){
    if(current == nullptr)
        return 1;
    else
        return 0;
}
template <class T>
void MyContainer<T>::next(){
    if(current != nullptr)
        current = current->next;
}
template <class T>
void MyContainer<T>::prev(){
    if(current != nullptr)
        current = current->prev;
}
template <class T>
MyContainerNode<T> MyContainer<T>::getObject(){
    if(current != nullptr)
        return *current;
    else if(head != nullptr)
        return *head;
}
template <class T>
MyContainerNode<T> MyContainer<T>::getObject(int a){
    if(head != nullptr){
        MyContainerNode<T>* newNode = head;
        for(int i = 0; i < a; i++){
            newNode = newNode->next;
        }
        return *newNode;
    }
}
template <class T>
int MyContainer<T>::length(){
    MyContainerNode<T>* newNode = head;
    int i = 0;
    while(newNode!=nullptr){
        newNode = newNode->next;
        i++;
    }
    return i;
}
#endif
/*
int main(){
    MyContainer<int> storage;
    int randFunc = 0;
    int a = 0;
    int index = 0;
    unsigned int start_time = clock();
    storage.first();
    for(int i = 0; i < 100000; i++){
        randFunc = rand() % 3;
        switch(randFunc){
        case 0:
            a = rand() % 25;
            storage.add(a);
            cout << i << ": add | " << a << "\n";
            break;
        case 1:
            a = rand() % 25;
            index = rand() % (storage.length() + 1);
            storage.add(a, index);
            cout << i << ": add index | " << a << " " << index << "\n";
            break;
        case 2:
            index = rand() % (storage.length() + 1);
            storage.popIndex(index);
            cout << i << ": popIndex | " << index << "\n";
            break;
        default:
            break;
        }
    }
    unsigned int end_time = clock();
    unsigned int search_time = end_time - start_time;
    for(storage.last(); !storage.eol(); storage.prev())
        cout << storage.getObject().node << "\n";
    cout << "\n\n\n" << search_time << "\n\n\n";
}*/
