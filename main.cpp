#include <iostream>

typedef struct Node
{
    int iPayload;
    Node* ptrNext;
    Node* ptrPrev;
}Node;

// Struct lista
typedef struct Lista
{
    Node* head;
}Lista;

Node* newNode(int);
Lista* newCircularList(int arr[], int size);
void display(Lista* list );
int getNextPayload(Lista*& list);
int getPreviousPayload(Lista*& list);
void removeid(Lista*& list, int id);
void deleteCircularList(Lista*& list);
Lista* mergeLists(Lista* list1, Lista* list2);

using namespace std;

int main() {
    int array[] = {1 , 2 , 3 ,4 ,5 };
    Lista *myhead = newCircularList(array,5);
    cout << "Lista: " ;
    display(myhead);
    int actual1 = getNextPayload(myhead);
    cout << endl;
    cout << "Obtendo atual e avançando" << endl;
    cout << "Actual: " <<actual1;
    cout << endl;
    cout << "Lista: ";
    display(myhead);
    cout << "Obtendo atual e retrocendendo lista" << endl;
    int actual2 = getPreviousPayload(myhead);
    cout << "Actual: " << actual2 << endl;
    display(myhead);
    cout << "Removendo id: 3" << endl;
    removeid(myhead, 3);
    cout << "Lista: ";
    display(myhead);
    cout << endl;
    cout << "deletando lista:" << endl;
    deleteCircularList(myhead);

    //display(myhead); // Tratar caso de lista null
    int array1[] = {1,3,5,6,7,6,8};
    int array2[] = {2,3,9,8,4,};
    Lista* list1 = newCircularList(array1,5);
    Lista* list2 = newCircularList(array2,5);
    Lista* listafusao = mergeLists(list1,list2);
    cout << "Lista fusion: ";
    display(listafusao);
    cout << endl;
    int arrayWithLoop[] = {1, 2, 3, 4, 5};

    cout << "fim";

    return 0;
}

Node* newNode(int iValue)
{
    Node* temp = (Node*) malloc(sizeof(Node));
    temp->iPayload = iValue;
    temp->ptrNext = nullptr;
    temp->ptrPrev = nullptr;
    return temp;
}

Lista* newCircularList(int arr[], int size)
{
    Lista* list = (Lista*)malloc(sizeof(Lista));
    Node* head = newNode(arr[0]);
    list->head = head;

    // Criando LinkedList normal
    Node* currenty = head;
    for (int i = 1; i < size; ++i)
    {
        Node* temp = newNode(arr[i]);
        currenty->ptrNext = temp;
        temp->ptrPrev = currenty;
        currenty = temp;
    }

    // Torna a linkedlist uma circular
    currenty->ptrNext = head;
    head->ptrPrev = currenty;

    return list;
}

void display(Lista* list )
{
    Node* temp = list->head;
    while (temp != nullptr)
    {
        cout << temp->iPayload << " ";

        // Necessário, evitar printar infinitamente a circular list
        if (temp->ptrNext == list->head)
        {
            return ;
        }

        temp = temp->ptrNext;
    }
}

int getNextPayload(Lista*& list)
{
    int payload = list->head->iPayload;
    list->head = list->head->ptrNext;
    return payload;
}
int getPreviousPayload(Lista*& list)
{
    list->head = list->head->ptrPrev;
    int payload = list->head->iPayload;
    return payload;
}

void removeid(Lista*& list, int id)
{
    Node* currenty = list->head;
    Node* temp = nullptr;

    // procurar nó com id
    do
    {
        if (currenty->iPayload == id)
        {
            if (temp == nullptr) // verificacao caso o id seja o iPayload do head
            {
                list->head = currenty->ptrNext;
                list->head->ptrPrev = currenty->ptrPrev;
            }
            else
            {
                temp->ptrNext = currenty->ptrNext;
                currenty->ptrNext->ptrPrev = temp;
            }
            free(currenty);
            return;
        }
        temp = currenty;
        currenty = currenty->ptrNext;
    } while (currenty != list->head);
}

void deleteCircularList(Lista*& list)
{
    Node* temp = list->head;
    Node* current = list->head;

    do
    {
        current = current->ptrNext;
        free(temp);
        temp = current;
    } while (temp != list->head);
    free(list);
    list = nullptr;
}

Lista* mergeLists(Lista* list1, Lista* list2)
{
    if (list1 == nullptr) return list2; // tratar casos
    if (list2 == nullptr) return list1; // de null pointer

    Lista* mergedList = (Lista*) malloc(sizeof(Lista)); // crio ponteiro de lista
    mergedList->head = nullptr; // set head como null

    Node* currenty1 = list1->head;  // 
    Node* currenty2 = list2->head;

    Node* aux1 = currenty1->ptrPrev;
    Node* aux2 = currenty2->ptrPrev;
    
     // conecto todas as listas uma nas outras
    mergedList->head = currenty1; 
    // faco mergedlist = list1
    aux1->ptrNext = currenty2; 
    currenty2->ptrPrev = aux1; 
    // conecto o fim da mergedlist com o comeco da lista 2
    aux2->ptrNext = currenty1; 
    currenty1->ptrPrev = aux2;

    return mergedList;
}


bool hasLoop(Node* head)
{
    if (head == nullptr) // verificaaar se lsita nao eh nula
    {
        cout << "null list" << endl;
        return false;
    }

    Node* temp1 = head; // criar temps
    Node* temp2 = head; //

    while (temp2 != nullptr && temp2->ptrNext != nullptr)
    {
        temp1 = temp1->ptrNext;
        temp2 = temp2->ptrNext->ptrNext;

        if (temp1 == temp2) // o nó é igual ao next dele mesmo
        {
            return true;
        }
    }

    return false;
}
