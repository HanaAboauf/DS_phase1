#include "bits/stdc++.h"
using namespace std;

template<class t>
struct Node{
    t info;
    Node<t>*next;
    Node<t>*prev;
};
template<class t>
class DoubleLinkedList{
protected:
    int count;
    Node<t>*head;
    Node<t>*tail;
public:
    DoubleLinkedList(){
        head= NULL;
        tail = NULL;
        count = 0;
    }
    void insertAtHead (t element)  {

        Node<t>*n=new Node<t>;
        n->info=element;
        n->prev=NULL;
        n->next=NULL;

        if(head==NULL){
            head=tail=n;
            count++;
        } else{
            n->next=head;
            head->prev=n;
            head=n;
            count++;
        }
    }
    void insertAtTail (t element){
        Node<t>*n=new Node<t>;
        n->info=element;
        n->prev=NULL;
        n->next=NULL;
        if(head==NULL){
            head=tail=n;
            count++;
        } else{
            tail->next=n;
            n->prev=tail;
            tail=n;
            count++;
        }
    }
    void insertAt (t element, int index) {

        Node<t>*n=new Node<t>;
        n->info=element;
        n->prev=NULL;
        n->next=NULL;

        if(index<0 || index> count) {
            delete n;
            return;
        }
        if(head==NULL || index==0){
            if (head == NULL) {
                head =tail= n;

            } else if(index==0) {

                insertAtHead(element);
            }
            count++;
            return;
        }
            Node<t>*cu=head;
            int c=0;
            while(cu!=NULL && c<index){
                c++;
                cu=cu->next;
            }
           if(cu!=NULL and c==index){
               n->next=cu->next;
               n->prev=cu;
               if(cu->next!=NULL) {
                   cu->next->prev = n;
               }
               cu->next=n;

               if(n->next==NULL){
                   tail=n;
               }

            count++;
           }
    }

    void removeAtHead () {

        if (head == NULL) {
            return;
        }
        if (head == tail) {
            delete head;
            head = tail = NULL;
        }
        else {
            head = head->next;
            delete head->prev;
            head->prev = NULL;
            count--;
        }

    }
    void removeAtTail () {

        if (head == NULL) {
            return;
        }
        if (head == tail) {
            delete head;
            head = tail = NULL;
        } else{
            tail=tail->prev;
            delete tail->next;
            tail->next=NULL;
            count--;
        }

    }
    void removeAt (int index) {

        if(head==NULL)
            return;

        if(index<0 || index>=count)
            return;

        if (index == 0) {
            if (head != NULL) {
                removeAtHead();
            }
            return;
        }

        int c=0;
        Node<t>*current=head;

        while (current != NULL && c < index){
            c++;
            current=current->next;
        }
        if(current != NULL && c==index){
            Node<t>* prevNode = current->prev;
            Node<t>* nextNode = current->next;

            if (prevNode != NULL) {
                prevNode->next = nextNode;
            }

            if (nextNode != NULL) {
                nextNode->prev = prevNode;
            }

            if(head==current)
                head=nextNode;

            if(tail==current)
                tail=prevNode;


            delete current;
            count--;


        }
    }

    t retrieveAt (int index) {

        if(head==NULL)
            return t();

        if(index<0 || index>count)
            return t();



        int c=0;
        Node<t>*current=head;

        while (current != NULL && c < index){
            c++;
            current=current->next;
        }
        if(current!=NULL && c==index)
            return current->info;


    }
    void replaceAt (t newElement, int index) {

        if(head==NULL)
            return;

        if(index<0 || index>count)
            return;

        int c=0;
        Node<t>*current=head;

        while (current != NULL && c < index){
            c++;
            current=current->next;
        }
        if(current!=NULL && c==index)
            current->info=newElement;


    }

    bool isExist (t element){
        if(head==NULL)
            return false;
        Node<t>*current=head;

        while (current != NULL ){

            if(current->info==element){
                return true;
            }
        }
        return false;

    }
    bool isItemAtEqual (t element, int index) {

        if(head==NULL)
            return false;

        if(index<0 || index>count)
            return false;

        int c=0;
        Node<t>*current=head;

        while (current != NULL && c < index){
            c++;
            current=current->next;
        }

        if(current!=NULL && c==index && current->info==element)
            return true;

        return false;
    }

    void swap (int firstItemIdx, int secondItemIdx){

        if (firstItemIdx < 0 || firstItemIdx >= count || secondItemIdx < 0 || secondItemIdx >= count) {
            return;
        }

        if (firstItemIdx == secondItemIdx) {
            return;
        }

        int smallIndex = min(firstItemIdx, secondItemIdx);
        int largIndex = max(firstItemIdx, secondItemIdx);

        Node<t>* n1 = head;
        Node<t>* n2 = head;
        int c = 0;

        while (c < smallIndex) {
            n1 = n1->next;
            c++;
        }

        while (c < largIndex) {
            n2 = n2->next;
            c++;
        }

        // Swap the nodes in the list
        if (n1 != NULL && n2 != NULL) {
            // Swap the next pointers of the nodes
            if (n1->next == n2) {
                // Nodes are adjacent
                Node<t>* tempNext = n2->next;
                Node<t>* tempPrev = n1->prev;

                if (tempPrev != NULL) {
                    tempPrev->next = n2;
                }
                n2->prev = tempPrev;
                n2->next = n1;
                n1->prev = n2;
                n1->next = tempNext;

                if (tempNext != NULL) {
                    tempNext->prev = n1;
                }

                // Update head and tail pointers if necessary
                if (head == n1) {
                    head = n2;
                }
                if (tail == n2) {
                    tail = n1;
                }
            } else {
                // Nodes are not adjacent
                Node<t>* tempPrev1 = n1->prev;
                Node<t>* tempNext1 = n1->next;
                Node<t>* tempPrev2 = n2->prev;
                Node<t>* tempNext2 = n2->next;

                if (tempPrev1 != NULL) {
                    tempPrev1->next = n2;
                }
                if (tempNext1 != NULL) {
                    tempNext1->prev = n2;
                }
                if (tempPrev2 != NULL) {
                    tempPrev2->next = n1;
                }
                if (tempNext2 != NULL) {
                    tempNext2->prev = n1;
                }

                // Swap the prev and next pointers of the nodes
                n1->prev = tempPrev2;
                n1->next = tempNext2;
                n2->prev = tempPrev1;
                n2->next = tempNext1;

                // Update head and tail pointers if necessary
                if (head == n1) {
                    head = n2;
                } else if (head == n2) {
                    head = n1;
                }
                if (tail == n1) {
                    tail = n2;
                } else if (tail == n2) {
                    tail = n1;
                }
            }
        }
    }
    bool isEmpty () {

        return (head==NULL);
    }

    int linkedListSize (){

        return count;
    }
    void clear (){

        Node<t>*temp;

        while(head!=NULL){
            temp=head;
            head=head->next;
            delete temp;
        }
        tail=NULL;
        count=0;
    }
    void print (){
        Node<t>*cu=head;
        while(cu!=NULL){
            cout<<cu->info<<" -> ";
            cu=cu->next;
        }
        cout<<"\n";

    }
};

int main(){
    DoubleLinkedList<int>d;
    d.insertAtHead(5);
    d.insertAtHead(3);
    d.insertAtTail(6);
    d.removeAt(0);
    d.insertAt(4,0);
    d.replaceAt(7,2);
    cout<<d.retrieveAt(1)<<"\n";
    cout<<d.isItemAtEqual(6,2)<<"\n";
    d.swap(0,2);
    d.print();




}

