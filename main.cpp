#include <iostream>
using namespace std;

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
Lista* fusao(Lista* list1, Lista* list2);



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
    int array1[] = {1,3,5,6,7};
    int array2[] = {2,3,9,8,4};
    Lista* list1 = newCircularList(array1,5);
    Lista* list2 = newCircularList(array2,5);
    Lista* listafusao = fusao(list1,list2);
    cout << "Lista fusion: ";
    display(listafusao);
    cout << endl;
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

// Função para juntar duas listas circulares em uma única lista circular, intercalando um iPayload de cada lista
Lista* fusao(Lista* list1, Lista* list2)
{

    Lista* mergedList = (Lista*) malloc(sizeof(Lista));
    mergedList->head = nullptr;

    Node* current1 = list1->head;
    Node* current2 = list2->head;

    Node* tail = nullptr;

    // Percorre as duas listas enquanto houver nós em pelo menos uma delas
    do {
        if (current1 != nullptr) {
            // Adiciona um nó da primeira lista à lista mesclada
            if (mergedList->head == nullptr) {
                mergedList->head = newNode(current1->iPayload);
                tail = mergedList->head;
            } else {
                tail->ptrNext = newNode(current1->iPayload);
                tail->ptrNext->ptrPrev = tail;
                tail = tail->ptrNext;
            }
            current1 = current1->ptrNext;
        }

        if (current2 != nullptr) {
            // Adiciona um nó da segunda lista à lista mesclada
            if (mergedList->head == nullptr) {
                mergedList->head = newNode(current2->iPayload);
                tail = mergedList->head;
            } else {
                tail->ptrNext = newNode(current2->iPayload);
                tail->ptrNext->ptrPrev = tail;
                tail = tail->ptrNext;
            }
            current2 = current2->ptrNext;
        }
    } while (current1 != list1->head || current2 != list2->head);

    // Torna a lista mesclada circular
    tail->ptrNext = mergedList->head;
    mergedList->head->ptrPrev = tail;

    return mergedList;
}
