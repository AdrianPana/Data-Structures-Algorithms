 - Tema 1 -

 - Detalii implementare -

    Pentru rezolvarea temei am folosit 2 fisiere auxiliare, procedures.c
(unde se afla implementarea comenzilor) si list.c (unde se afla functiile
de baza pentru lucrul cu liste dublu, inlantuite asemanatoare cu cele din
laborator)

 1. Datele sunt salvate intr-o lista dublu inlantuita care memoreaza nodurile
head si tail si numarul acestora (len). Un nod memoreaza timestamp-ul (int) si
valoarea data (double), precum si pointeri catre nodurile next si previous.

Am implementat toate functiile de baza pentru o lista dublu inlantuita in
fisierul list.c, separat de tema1.c, iar comenzile se regasesc in procedures.c,
pentru o mai buna organizare a codului.

Programul citeste de la tastatura linie cu linie nodurile listei si le adauga
in aceasta folosind functia insert_new_node()

2.
2.1) Programul initializeaza o lista noua aux_list, la care adauga implicit primele
doua noduri si, ulterior, ultimele doua noduri ale listei initiale.
    Se face parcurgerea nod cu nod, pentru fiecare nod se face o "mini" parcurgere
in fereastra pentru a calcula formulele necesare. Deviatia este calculata
concomitent cu media pentru a evita o parcurgere suplimentara a listei.
    In loc sa elimin noduri din lista initiala, verific daca fiecare nod convine
cerintelor si il adaug in aux_list.
    La final, lista initiala este distrusa pentru a elibera memoria, iar noua
lista va deveni aux_list.

2.2.1) Programul initializeaza o lista noua aux_list, care va deveni noua lista.
    Pentru fiecare nod din lista, se parcurge fereastra cu care incepe acesta
si calculeaza valoarea mediana. Pentru a evita initializarile si distrugerile
repetate ale unei liste in plus, care sa contina nodurile din fereastra,
programul memoreaza doar 3 variabile max1>max2>max3 care contin valorile celor
mai mari 3 date din fereastra. La parcurgerea ferestrei, functia assign_max()
modifica aceste valori, pentru a mentine ordinea.
    Valoarea mediana este adaugata cu timestamp-ul din mijloc al ferestrei in
lista aux_list.
    La final, lista initiala este distrusa pentru a elibera memoria, iar noua
lista va deveni aux_list.

2.2.2) Programul initializeaza o lista noua aux_list, care va deveni noua lista.
    Pentru fiecare nod din lista, se parcurge fereastra cu care incepe acesta
si calculeaza valoarea mediei, care este apoi adaugata in aux_list la 
timestamp-ul nodului din mijlocul ferestrei.
    La final, lista initiala este distrusa pentru a elibera memoria, iar noua
lista va deveni aux_list.

2.3) Programul parcurge lista nod cu nod si verifica daca diferenta de
timestamp-uri dintre nod si nod->next este in intervalul [0.1,1] secunde, caz
in care valorile lui nod->next conform cerintei.

2.4) Programul parcurge lista nod cu nod si verifica daca diferenta de
timestamp-uri dintre nod si nod->next este mai mare decat 1 secunda, caz in
care va adauga noile noduri; Se calculeaza valoarea numitorului fractiilor
w(i,k), apoi se calculeaza w(i,k) (i=0:K-1) cu care se construiesc sum1 si sum2,
conform formulelor (folosind si nodurile left si right care se apropie de nodul
curent la fiecare iteratie).
    Folosind un for din 200 in 200 (pentru a asigura frecventa de 5Hz), se
parcurg timestamp-urile nodurilor care vor fi adaugate in lista. Se calculeaza
C corespunzator nodului si noua valoare a data, folosind sum1 si sum2 deja
obtinute.
    Se adauga nodul cu noile timestamp si data in pozitia in care ne aflam
folosind functia insert_node_after_node() si se actualizeaza pozitia la care
ne aflam in lista pe nodul nou adaugat.

2.5) Programul initializeaza o lista "de frecventa" in care se memoreaza
fiecare interval eligibil si nodurile care se afla in acesta.
    Se parcurge lista si se calculeaza valorile maxima si minima a campului
data din aceasta, apoi se calculeaza limitele intre care se afla aceste
valori, si implicit intervalele din capete (ca multipli de delta).
    Plecand de la limita inferioara, se adauga in field-ul timestamp capatul
din stanga al fiecarui interval (capatul din dreapta se obtine adaugand delta)
la cel din stanga). 
    Se parcurge lista, iar pentru fiecare nod se cauta intervalul in care
se afla si se incrementeaza valoarea field-ului data din lista "de frecventa".
Se va folosi functia auxiliara update_node() care incrementeaza valoarea data
de la o pozitie data.
    La final, se parcurge lista "de frecventa" si daca field-ul data este nenul,
se printeaza intervalul si numarul de noduri din acesta.
    Lista "de frecventa" este distrusa, pentru a elibera memoria folosita.

3. Functia main() initializeaza o lista care va fi modificata de functiile
din procedures.c, iar la final va fi distrusa.
    Se parcurg argumentele argv[] si se apeleaza pentru fiecare functia
corespunzatoare. Daca argumentul este "st" , se parcurg caracterele de dupa
acesta si se construieste in memorie numarul delta, cu care se va apela functia
pentru statistici.

 - Timp de implementare -

-> Aprox. 8 ore

 - Precizari - 

-> Task-ul 2.4 este foarte ambiguu explicat, intelegerea cerintei a intarziat
implementarea cu aproximativ 2 ore. 