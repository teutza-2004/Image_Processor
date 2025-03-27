Task 1:
Am parcurs matricea image pana la jumatate din numarul de coloane si, prin functia Swap, am interschimbat valorile de pe pozitii simetrice.

Task 2:
Am alocat o matrice auxiliara cu M linii si N coloane.
Am copiat valorile din matricea image astfel incat in aux_image sa se gaseasca transpusa primei matrice.
Am dezalocat imaginea initiala si am returnat transpusa aceseia.

Task 3:
Am alocat o matrice cu dimensiunile h si w in care am copiat valorile din matricea image incepand cu linia y si coloana x.
Am dezalocat matricea image si am returnat matricea nou obtinuta.

Task 4:
Am salvat in variabilele n si m marimiea matricei extinse, apoi in functie de acestea am alocat o matrice auxiliara. 
In aux_image am copiat incepand cu pozitia rows si cols matricea initiala, tinand cont de dimensiunea acesteia. 
In restul matricei auxiliare am pus valorile date ca parametrii ai functiei.
Am dezalocat matricea initala si am returnat-o pe cea extinsa.

Task 5:
Am parcurs matricea destinatie incepand cu pozitiile y si x date.
Am tinut cont atat de dimensiunea matricei destinatie cat si de cea sursa. 
Am copiat valorile din sursa, la pozitiile corespunzatoare in matricea destinatie.
Am returnat matricea destinatie modificata.

Task 6:
Am salvat valorile limita ale RGB in doua constante, pentru a nu avea numere magice.
Am alocat o matrice auxiliara in care ar urma sa fie imagine a cu filtrul aplicat.
Prin doua for-uri (dupa i si dupa j) am parcurs practic fiecare pixel din imaginea initiala. 
Cu al treilea for (cel dupa k) am mers prin cele 3 culori respective ficarui pixel. 
Prin for-urile dupa x si y am parcurs "vecinii" pixelului curent necesari pentru aplicarea filtrului.
Pe vecinii care ar fi in afara matricei initiale, i-am ignorat prin folosirea contiune.
In final am veirificat daca valoarea rezultata in urma aplicarii filtrului este in limitele cerute.
Am dezalocat matricea initala si am returnat-o pe cea pe care este aplicat filtrul.

Task 7:
Am creat o structura in care retin pt fiecare index numarul de linii si de coloane al matricei asociate index-ului si matricea.
Am facut o bluca infinita pentru a citi comenzile din care se iese prin comanda e.
comanda e:
-am dezalocat toate matricile, inclusiv vectorul care tine minte adresele catre fiecare matrice si am oprit fortat executia programului.
comanda l:
-am citit datele si am realocat structura astfel incat sa pot pune si matricea noua la indexul corespunzator.
-pentru a pune datele despre imaginea obtinuta in locul aferent in vectorul de matrice am folosit functia read_from_bpm.
comanda s:
-am folosit efectiv functia write_to_bmp pe pozitia index a vectorului de matrice.
comanda ah:
-am aplicat functia flip_horizontal asupra matricei.
comanda ar:
-am retinut matricea returnata de functia rotate_left intr-un auxiliar.
-am alocat din nou matricea de la indexul dat deoarece am dezalocat-o in functia de rotire.
-am pus valoarea de la auxiliar in matricea nou alocata si am interschimbat numarul de linii cu cel de coloane.
comanda ac:
-similar cu comanda ar, la final insa am dat valoarea h numarului de linii si w celui de coloane.
comanda ae:
-similar cu comanda ar, la final insa am dat adaugat la numarului de linii si al celui de coloane, dublul rows, respectiv cols.
comanda ap:
-am folosit functia paste.
comanda cf:
-am facut o structura in care retin pt fiecare index marimea si matricea filtrelor.
-am alocat matricea filtrului si am pus valorile citite in aceasta.
comanda af:
-am folosit functia apply_filter pe matricea imagine, cu matricea filtru date.
comanda df:
-am dezalocat matricea de la pozitia index din vectorul de imagini si apoi am mutat incepand de la index+1 toate matricele cu o pozitie la stanga
comanda di:
-similar comanda df