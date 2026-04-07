# 📚 Könyvtári Nyilvántartó és Kereső Program

Egyszerű, parancssoros könyvtári rendszer C nyelven.  
Könyvek és olvasók adatainak betöltése fájlokból, majd keresés különböző szempontok szerint.

---

## 🚀 Features

### 🔍 Keresés olvasók között
- név
- könyvtári azonosító
- tartozás

### 📖 Keresés könyvek között
- cím
- szerző
- műfaj

- ✏️ Részleges egyezés (nem kell pontos szöveg)
- 🧠 Egységes keresési logika függvénypointerrel
- 📂 Fájl alapú adatkezelés
- 🔗 Láncolt listás megvalósítás

---

## 🛠️ Tech stack

- **Nyelv:** C  
- **Paradigma:** Procedurális  
- **Adatszerkezet:** Láncolt lista  
- **Keresés:** Lineáris keresés  

---

## ▶️ Használat

### 1. Fordítás
```bash
gcc main.c -o library
```

### 2. Futtatás
```bash
./library
```

### 3. Indítás után
- add meg a két adatfájl elérési útját  
- válassz a menüből  
- adj meg egy keresési kulcsot  

---

## 📥 Input formátum

A program két fájlból dolgozik.

### 👤 Olvasók

Egy olvasó adatai több sorban:

```
Név
Beiratkozás dátuma
Azonosító
Tartozás
Utolsó látogatás
```

### 📖 Könyvek

```
Cím
Szerző
Kiadás dátuma
Kiadó
ISBN
Kölcsönzési állapot
Könyvtári azonosító
Műfaj(ok)
```

---

## ⚙️ Hogyan működik?

- Az adatok beolvasása után két külön láncolt lista jön létre:
  - olvasók
  - könyvek

- A keresés:
  - egy általános `perform_search()` függvényen keresztül történik  
  - paraméterként kap egy keresőfüggvényt  
  - végigiterál a listán  

- A konkrét keresést a `search_for_*()` függvények végzik  

---

## 🧹 Memóriakezelés

- Dinamikus memóriafoglalás minden rekordhoz  
- A program végén:
  - lista felszabadítása  
  - stringek felszabadítása  

---

## 🧪 Tesztelés

**Tesztelve:**
- Ubuntu 24.04 LTS  
- Windows 11  24H2

**Tesztelési módszer:**
- folyamatos résztesztelés fejlesztés közben  
- teljes funkcionalitás végigpróbálása  
- teszt input fájlokkal  

---

## 📌 Limitációk

- Lineáris keresés (nagy adathalmaznál lassú lehet)  
- Nincs perzisztens módosítás (csak olvasás)  
- Nem generikus lista implementáció  

---

## 🔮 Lehetséges fejlesztések

- Bináris keresés / indexelés  
- Hash map alapú keresés
- QuickSearch implementálása
- Generikus lista C-ben  
- GUI verzió  
- Adat módosítás / mentés  

---

## 👤 Szerző

Készült az elsőéves *Programozás Alapjai 1* tárgy nagyházijaként HP0GWM (Csirke Dániel) által. 
