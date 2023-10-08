# OOP Revolut-copy Project
 
### If you want to test my app.
The "database" has a test user introduced at the beginning on which you can use the functionalities:
The test user details:
User gmail: "t@t"
User name: "tester"
User cnp: "1234567890123"
User phone number: "0710000000"

### Tema 0

- [x] Nume proiect (poate fi schimbat ulterior)
- [x] Scurtă descriere a temei alese, ce v-ați propus să implementați

O incercare de server bancar cu o viitoare interfata pentru useri (in consola sau pe web printr-o librarie) in care un utilizator poate face cam ce fac toate aplicatiile bancare (creeare cont, creeare cont bancar, adaugare fonduri, transferuri, exchange). 

## Tema 1

#### Cerințe
- [x] definirea a minim 3-4 clase folosind compunere
- [x] constructori de inițializare
- [x] pentru o clasă: constructor de copiere, `operator=` de copiere, destructor
<!-- - [ ] pentru o altă clasă: constructor de mutare, `operator=` de mutare, destructor -->
<!-- - [ ] pentru o altă clasă: toate cele 5 funcții membru speciale -->
- [x] `operator<<` pentru toate clasele pentru afișare (std::ostream)
- [x] cât mai multe `const` (unde este cazul)
- [x] implementarea a minim 3 funcții membru publice pentru funcționalități specifice temei alese
- [x] scenariu de utilizare a claselor definite:
  - crearea de obiecte și apelarea funcțiilor membru publice în main
  - vor fi adăugate în fișierul `tastatura.txt` exemple de date de intrare de la tastatură (dacă există)
- [x] tag de `git`: de exemplu `v0.1`
- [x] serviciu de integrare continuă (CI); exemplu: GitHub Actions

## Tema 2

#### Cerințe
- [x] separarea codului din clase în `.h` (sau `.hpp`) și `.cpp`
- [x] moșteniri
  - [x] clasă cu atribut de tip pointer la o clasă de bază cu derivate
  - [x] funcții virtuale (pure) apelate prin pointeri de bază din clasa de mai sus, constructori virtuali (clone)
    - minim o funcție virtuală va fi **specifică temei** (e.g. nu simple citiri/afișări)
  - [x] apelarea constructorului din clasa de bază din constructori din derivate
  - [x] smart pointers
  - [x] `dynamic_cast`
- [x] suprascris cc/op= pentru copieri/atribuiri corecte, copy and swap
- [x] excepții
  - [x] ierarhie proprie cu baza `std::exception` sau derivată din `std::exception`; minim 2 clase pentru erori specifice
  - [x] utilizare cu sens: de exemplu, `throw` în constructor, `try`/`catch` în `main`
- [x] funcții și atribute `static`
- [x] STL
- [x] cât mai multe `const`
- [x] la sfârșit: commit separat cu adăugarea unei noi derivate fără a modifica restul codului
- [x] tag de `git`: de exemplu `v0.2`

## Tema 3

#### Cerințe
- [x] 2 șabloane de proiectare (design patterns)
- [x] o funcție șablon (template) cu sens; minim 2 instanțieri
- [x] o clasă șablon cu sens; minim 2 instanțieri
<!-- - [ ] o specializare pe funcție/clasă șablon -->
- [x] tag de `git`: de exemplu `v0.3` sau `v1.0`
