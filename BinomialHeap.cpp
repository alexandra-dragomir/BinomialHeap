#include <iostream>
#include <fstream>
#include <math.h>
#include <string.h>
#include <chrono>

using namespace std;
using namespace std::chrono;


/*

        Teste

    1. sortedNumbers    2e-6        1       - 2e-6
    2. reverseSorted    2e-6        2e-6    - 1
    3. randomSmallData  100 nr      -1000   - 1000
    4. randomMediumData 10.000 nr   -1e-9   - 1e-9
    5. randomlargeData  2e-6 nr     INT_MIN - INT_MAX
    6. tree4096          4096 nr     -1e6    - 1e6

*/

struct node
{
    int n;
    int degree;
    struct node* parent;
    struct node* child;
    struct node* sibling;

} *H = NULL, *Hr = NULL, *H2 = NULL;

/// Implementare Binomial Heap -->

/// --------------------------- Construire Node --------------------------- ///

struct node* create_node(int k)
{
    struct node* p;
    p = new node;
    p -> n = k;
    return p;
}

/// --------------------------- Initializare Heap --------------------------- ///

struct node* create_heap()
{
    struct node* nou;
    nou = NULL;
    return nou;
}

/// --------------------------- Functia de Print --------------------------- ///

void displayTree(node *h)
{
    while (h)
    {
        cout << h->n << "(" << h->degree << ") ";
        displayTree( h ->child );
        h = h->sibling;
    }
}


/// --------------------------- Merge Pentru 2 Heap-uri --------------------------- ///

struct node* mergeHeaps(struct node* H1, struct node* H2)
{
    struct node* H = create_heap();
    struct node* x;
    struct node* y;
    struct node* a;
    struct node* b;
    x = H1;
    y = H2;

    if ( x != NULL && y != NULL && x->degree <= y->degree )
        H = x;
    else if ( x != NULL && y != NULL && x->degree > y->degree )
        H = y;
    else if ( y == NULL )
        H = x;
    else
        H = y;

    while ( x != NULL && y != NULL )
    {
        if ( x->degree < y->degree )
        {
            x = x->sibling;
        }
        else if( y->sibling && y->degree < y->sibling->degree && y->sibling->degree < x->degree )
        {
            y = y->sibling;
        }
        else if ( x->degree == y->degree )
        {
            a = x->sibling;
            x->sibling = y;
            x = a;
        }
        else
        {
            b = y->sibling;
            y->sibling = x;
            y = b;
        }
    }

    return H;
}

/// --------------------------- Merge Pentru 2 Node-uri de acelasi grad --------------------------- ///

int linkEqNodes(struct node* x, struct node* y)
{
    x->parent = y;
    x->sibling = y->child;
    y->child = x;
    y->degree = y->degree + 1;
}


/// --------------------------- Uniunea a 2 Heap-uri --------------------------- ///

struct node* joinHeaps (struct node* H1, struct node* H2)
{
    struct node* prev_x;
    struct node* next_x;
    struct node* x;
    struct node* H = create_heap();
    H = mergeHeaps(H1, H2);
    if (H == NULL)
        return H;

    prev_x = NULL;
    x = H;
    next_x = x->sibling;

    while (next_x != NULL)
    {
        if ( ( x->degree != next_x->degree ) )
        {
            prev_x = x;
            x = next_x;
        }
        else if ( ( x->degree == next_x->degree ) && ( next_x->sibling != NULL ) && (next_x->sibling)->degree == x->degree )
        {
             prev_x = x;
             x = next_x;
        }
        else
        {
            if (x->n <= next_x->n)
            {
                x->sibling = next_x->sibling;
                linkEqNodes(next_x, x);
            }
            else
            {
                if (prev_x == NULL)
                {
                    H = next_x;
                }
                else
                {
                    prev_x->sibling = next_x;
                }
                linkEqNodes(x, next_x);
                x = next_x;
            }
        }
        next_x = x->sibling;
    }
    return H;
}

/// <-- Gata Implementare Binomial Heap

/// --------------------------- INSEREAZA --------------------------- ///

struct node* insereaza(struct node* H3, struct node* x)
{
    struct node* H1 = create_heap();

    x->parent = NULL;
    x->child = NULL;
    x->sibling = NULL;
    x->degree = 0;
    H1 = x;
    H3 = joinHeaps(H3, H1);
    return H3;
}


/// --------------------------- Display Radacini --------------------------- ///

int displayRadacini(struct node* H)
{
    struct node* p;
    if (H == NULL) {
        cout << "Heap-ul este gol !\n";
        return 0;
    }
    cout << "\n Radacinile sunt: \n";
    p = H;
    while (p != NULL) {
        cout << p->n;
        cout << "(" << p->degree << ")";
        if ( p->sibling != NULL )
            cout << "-->";
        p = p->sibling;
    }
    cout << endl;
}

/// --------------------------- UTILITIES --------------------------- ///

void reverseList(struct node* y)
{
    if ( y->sibling != NULL ) {
        reverseList(y->sibling);
        ( y->sibling )->sibling = y;
    }
    else Hr = y;
}

void swap(int* a, int* b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}


/// --------------------------- EXTRACT MIN --------------------------- ///

struct node* extrageMinim(struct node* H1, struct node* H2)
{
    int minim;
    struct node* t = NULL;
    struct node* x = H1;
    struct node* p;

    Hr = NULL;
    if (x == NULL)
    {
        cout << "Valoarea " << x << " nu exista in heap! ";
        return x;
    }

    p = x;
    minim = p->n;

    while (p->sibling != NULL)
    {
        if ((p->sibling)->n < minim)
        {
            minim = (p->sibling)->n;
            t = p;
            x = p->sibling;
        }
        p = p->sibling;
    }

    // sterge node-ul extras din frate si urmatorul de extras devine frate
    if (t == NULL && x->sibling == NULL)
        H1 = NULL;
    else if (t == NULL)
        H1 = x->sibling;
    else if (t->sibling == NULL)
        t = NULL;
    else
        t->sibling = x->sibling;

    if (x->child != NULL)
    {
        reverseList(x->child);
        (x->child)->sibling = NULL;
    }

    if(!H1) { swap(H1,Hr); }

    H2 = joinHeaps(H1, Hr);
    return H2;
}

/// --------------------------- ESTE_IN --------------------------- ///


struct node* este_in(struct node* H, int k)
{
    if (H == NULL) {
        cout << " Heap-ul este gol !\n";
        return 0;
    }
    struct node* x = H;
    struct node* p = NULL;
    if (x->n == k) {
        p = x;
        return p;
    }
    if (x->child != NULL && p == NULL) {
        p = este_in(x->child, k);
    }

    if (x->sibling != NULL && p == NULL) {
        p = este_in(x->sibling, k);
    }
    return p;
}



/// --------------------------- Decrease Key --------------------------- ///

struct node* scade(struct node* H, int i, int k)
{
    int temp;
    struct node* p;
    struct node* y;
    struct node* z;
    p = este_in(H, i);

    if (p == NULL) {
        cout << " Valoarea nu fost gasita ! ";
        return 0;
    }
    if (k > p->n) {
        cout << " Valoarea nu poate fi mai mare decat cea deja existenta ! ";
        return 0;
    }

    p->n = k;
    y = p;
    z = p->parent;
    while (z != NULL && y->n < z->n) {
        temp = y->n;
        y->n = z->n;
        z->n = temp;
        y = z;
        z = z->parent;
    }
    return H;
}

/// --------------------------- STERGE --------------------------- ///

struct node* sterge(struct node* H, int k)
{
    struct node* d;

    if (H == NULL) {
        cout << "Heap-ul este gol! \n";
        return 0;
    }
    if(!este_in(H, k)) {
        cout << "Valoarea " << k << " nu se afla in heap ! \n";
        return 0;
    }

    H = scade(H, k, INT_MIN);
    H = extrageMinim(H, H);

    return H;
}


/// --------------------------- MIN --------------------------- ///

int findMin(struct node* H) {
    struct node* p;

    if (H == NULL) {
        cout << "Heap-ul este gol ! \n";
        return 0;
    }

    p = H;
    int minn = p->n;

    while (p->sibling != NULL)
    {
        if ( (p->sibling)->n < minn ){
            minn = (p->sibling)->n;
        }
        p = p->sibling;
    }
    return minn;
}

/// --------------------------- MAX --------------------------- ///

int findMax(struct node* H, int aux) {
    struct node* x = H;
    if (H == NULL) {
        cout << "Heap-ul este gol ! \n";
        return 0;
    }

    int max1 = INT_MIN, max2 = INT_MIN;
    if (x->child != NULL) {
        max1 = findMax(x->child, aux);
    }
    if (x->sibling != NULL) {
        max2 = findMax(x->sibling, aux);
    }

    if (x->n > max1 && x->n > max2) {
        return x->n;
    }
    else if(max1 > x->n && max1 > max2){
        return max1;
    }

    return max2;
}

/// --------------------------- CARDINAL --------------------------- ///

int cardinal(struct node* H) {
    int card = 0;
    struct node* p;
    if (H == NULL) {
        cout << "Heap-ul este gol ! \n";
        return 0;
    }
    p = H;
    while (p != NULL) {
        card += pow(2, p->degree);
        p = p->sibling;
    }
    return card;
}

/// --------------------------- SUCCCESOR --------------------------- ///

int succesor(struct node* H, int x){
    struct node* p = H;

    if (H == NULL) {
        cout << "Heap-ul este gol ! \n";
        return 0;
    }

    int min1 = x, min2 = x;
    if (p->child != NULL) {
        min1 = succesor(p->child, x);
    }
    if (p->sibling != NULL) {
        min2 = succesor(p->sibling, x);
    }

    if(p->n <= x){
        if(min1 <= x){
            if(min2 <= x)
                return x;
            return min2;
        }
        if(min2 <= x)
            return min1;
        if(min1 < min2)
            return min1;
        return min2;
    }
    if(min1 <= x){
        if(min2 <= x)
            return p->n;
        if(p->n > min2)
            return min2;
        return p->n;
    }
    if(min2 <= x){
        if(p->n > min1)
            return min1;
        return p->n;
    }
    if(p->n < min1 && p->n < min2)
        return p->n;
    if(min1 < p->n && min1 < min2)
        return min1;
    if(min2 < p->n && min2 < min1)
        return min2;
    return x;

}

/// --------------------------- PREDECESOR --------------------------- ///

int predecesor(struct node* H, int x){
    struct node* p = H;

    if (H == NULL) {
        cout << "Heap-ul este gol ! \n";
        return 0;
    }

    int min1 = x, min2 = x;
    if (p->child != NULL) {
        min1 = predecesor(p->child, x);
    }
    if (p->sibling != NULL) {
        min2 = predecesor(p->sibling, x);
    }

    if(p->n >= x){
        if(min1 >= x){
            if(min2 >= x)
                return x;
            return min2;
        }
        if(min2 >= x)
            return min1;
        if(min1 > min2)
            return min1;
        return min2;
    }
    if(min1 >= x){
        if(min2 >= x)
            return p->n;
        if(p->n < min2)
            return min2;
        return p->n;
    }
    if(min2 >= x){
        if(p->n < min1)
            return min1;
        return p->n;
    }
    if(p->n > min1 && p->n > min2)
        return p->n;
    if(min1 > p->n && min1 > min2)
        return min1;
    if(min2 > p->n && min2 > min1)
        return min2;
    return x;
}

/// --------------------------- COPY HEAP --------------------------- ///


struct node* copyHeap(struct node* H1, struct node* H2){
    struct node* p1 = H1;
    struct node* p2;
    if (H1 == NULL) {
        cout << "Heap-ul este gol ! \n";
    }

    int val = H1->n;
    p2 = create_node(val);
    H2 = insereaza(H2, p2);

    if(p1->sibling != NULL)
        H2 = copyHeap(p1->sibling, H2);
    if(p1->child != NULL)
        H2 = copyHeap(p1->child, H2);
    return H2;
}

/// --------------------------- K_ELEMENT --------------------------- ///

int k_element3(struct node* H, int k){
    struct node* p;
    struct node* H2 = create_heap();
    H2 = copyHeap(H, H2);
    int aux = k;
    while(aux - 1){
        H2 = extrageMinim(H2, H2);
        aux--;
    }
    return findMin(H2);
}

/// --------------------------- DISPLAY MENIU --------------------------- ///

void afisareMeniu() {

    cout << "\n\n                                      ---------- BINOMIAL HEAP ----------                            \n\n";
    cout << " 1) Import Data \n";
    cout << " 2) Insereaza Element \n";
    cout << " 3) Sterge Element \n";
    cout << " 4) Minim \n";
    cout << " 5) Maxim \n";
    cout << " 6) Succesor \n";
    cout << " 7) Predecesor \n";
    cout << " 8) K-element \n";
    cout << " 9) Cardinal \n";
    cout << " 10) Cauta Element \n";
    cout << " 11) Afiseaza Heap \n";
    cout << " 0) Exit \n";
}

/// --------------------------- MAIN --------------------------- ///

int main() {
    char opt;
    int option, x, n;
    struct node* p;
    struct node* q;


    cout << "Denumiti fisierul de export: \n";
    string sout;
    cin >> sout;
    string fisier = sout + ".txt";
    ofstream fout(fisier);


/// -- Meniu Binomial Heap -- ///

    while ( option != 0 ) {

        afisareMeniu();
        cout << "\n" << " Introduceti o comanda: ";
        cin >> option;
        switch (option) {

        default: {
            cout << " Introduceti o valoarea valida! \n ";
            break;
        }

        case 1 : {

            cout << " Introduceti numele fisierului din care importati: ";
            string sin;
            cin >> sin;
            ifstream fin(sin);
            auto start = high_resolution_clock::now();
            while(fin >> x){
                struct node* y = create_node(x);
                H = insereaza(H, y);
            }
            auto stop = high_resolution_clock::now();
            auto duration = duration_cast<microseconds>(stop - start);
            cout << "Durata Inserare : " << duration.count() << endl;
            break;
        }

        case 2 : {

            do {
                cout << "\n Introduceti elementul : ";
                cin >> n;
                p = create_node(n);
                H = insereaza(H, p);

                cout << endl;
                cout << "\n Introdu 'y' or 'Y' pentru a insera elemente in continuare: ";
                cin >> opt;
            } while (opt == 'y' || opt == 'Y');

            break;
        }

        case 3 : {

            do {
                cout << " Introduceti valoarea : ";
                cin >> n;

                auto start = high_resolution_clock::now();

                H = sterge(H, n);

                auto stop = high_resolution_clock::now();
                auto duration = duration_cast<microseconds>(stop - start);
                cout << "Durata Stergere : " << duration.count() << endl;

                fout << "A fost stearsa valoarea " << n << " din heap ! \n";

                cout << "\n Introdu 'y' or 'Y' pentru a sterge in continuare : ";
                cin >> opt;
            } while (opt == 'y' || opt == 'Y');
            break;
        }

        case 4 : {

            auto start = high_resolution_clock::now();

            cout <<  "\n Minimul din heap este: "<< findMin(H) << endl;
            fout <<  "\n Minimul din heap este: "<< findMin(H) << endl;

            auto stop = high_resolution_clock::now();
            auto duration = duration_cast<microseconds>(stop - start);
            cout << "Durata findMinim : " << duration.count() << endl;
            break;
        }

        case 5 : {

            auto start = high_resolution_clock::now();

            cout << "\n Maximul din heap este: " << findMax(H, INT_MIN) << endl;
            fout << "\n Maximul din heap este: " << findMax(H, INT_MIN) << endl;

            auto stop = high_resolution_clock::now();
            auto duration = duration_cast<microseconds>(stop - start);
            cout << "Durata findMaxim : " << duration.count() << endl;
            break;
        }

        case 6 : {

            int x;
            cout << "\n Introduceti numarul pt succesor: "; cin >> x;
            auto start = high_resolution_clock::now();

            if( !este_in(H, x) ) {
                    cout << "Nu exista elementul " << x << " in heap ! \n";
                    fout << "Nu exista elementul " << x << " in heap ! \n";
            }
            else if ( x == findMax(H, INT_MIN) ) { cout << "\n " << x << " este deja maximul din heap ! \n"; }
            else {
                    cout << "Succesorul lui " << x << " este: " << succesor(H, x) << endl;
                    fout << "Succesorul lui " << x << " este: " << succesor(H, x) << endl;
            }

            auto stop = high_resolution_clock::now();
            auto duration = duration_cast<microseconds>(stop - start);
            cout << "Durata Succesor : " << duration.count() << endl;

            break;
        }

        case 7 : {

            int x;
            cout << "\n Introduceti numarul pt predecesor: "; cin >> x;
            auto start = high_resolution_clock::now();

            if( !este_in(H, x) ) {
                    cout << "Nu exista elementul " << x << " in heap ! \n";
                    fout << "Nu exista elementul " << x << " in heap ! \n";
            }
            else if ( x == predecesor(H, x) ) { cout << "\n " << x << " este deja minimul din heap ! \n"; }
            else {
                    cout << "Predecesorul lui " << x << " este: " << predecesor(H, x) << endl;
                    fout << "Predecesorul lui " << x << " este: " << predecesor(H, x) << endl;
            }

            auto stop = high_resolution_clock::now();
            auto duration = duration_cast<microseconds>(stop - start);
            cout << "Durata Predecesor : " << duration.count() << endl;

            break;
        }

        case 8 : {

            cout << "Introduceti k: \n";
            int k; cin >> k;
            auto start = high_resolution_clock::now();
            if(k > cardinal(H)) {
                    cout << "Valoarea este peste limitele heap-ului ! \n";
                    fout << "Valoarea este peste limitele heap-ului ! \n";
            }
            else {
                    cout << "Elementul de pe pozitia " << k << ": " << k_element3(H, k) << endl;
                    fout << "Elementul de pe pozitia " << k << ": " << k_element3(H, k) << endl;
            }
            auto stop = high_resolution_clock::now();
            auto duration = duration_cast<microseconds>(stop - start);
            cout << "Durata k-Element : " << duration.count() << endl;
            break;
        }

        case 9 : {

            auto start = high_resolution_clock::now();
            if(cardinal(H) != 0) {
                cout << "\n Cardinalul Heap-ului curent este: " << cardinal(H) << endl;
                fout << "\n Cardinalul Heap-ului curent este: " << cardinal(H) << endl;
            }

            auto stop = high_resolution_clock::now();
            auto duration = duration_cast<microseconds>(stop - start);
            cout << "Durata Cardinal : " << duration.count() << endl;
            break;
            }

        case 10 : {

            int x;
            cout << "\n Introduceti elementul de cautat ( x ) : ";
            cin >> x;
            auto start = high_resolution_clock::now();
            if(este_in(H, x)){
                cout << " Elementul " << x << " EXISTA in H ! \n";
                fout << " Elementul " << x << " EXISTA in H ! \n";
            }

            else {
                    cout << " Elementul " << x << " NU A FOST GASIT in H ! \n";
                    fout << " Elementul " << x << " NU A FOST GASIT in H ! \n";
            }
            auto stop = high_resolution_clock::now();
            auto duration = duration_cast<microseconds>(stop - start);
            cout << "\n Durata findElement : " << duration.count() << endl;
            break;
        }

        case 11 : {

            cout << "\n Heap-ul actual este: ";
            displayTree(H);
            cout << endl;

            break;
            }

        case 0 : { break; }

        }
    }

return 0;
}

