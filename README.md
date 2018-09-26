# Tubes-TBFO-1
File berisi Tubes TBFO 1 yaitu DFA Tic-Tac-Toe <br>

## Dibuat oleh :
#### Aditya Putra Santosa (13517013 / Teknik Informatika ITB)
## Cara compile
(Windows)
```
gcc -g dfa.c game.c papan.c main.c -o TicTacToe.exe
```
(Linux)
```
gcc -g dfa.c game.c papan.c main.c -o TicTacToe
```
Lalu run dengan : <br>
(Windows)
```
TicTacToe
```
(Linux)
```
./TicTacToe
```

### Deskripsi singkat permasalahan :
  Implementasikan game Tic Tac Toe menggunakkan DFA sedemikian rupa sehingga komputer tidak akan pernah kalah. Player selalu menggunakkan "X" dan komputer selalu menggunakkan "O"

## DFA Generator
  DFA Generator adalah progaram singkat yang bertujuan untuk membantu saya membuat tabel transisi yang dibutuhkan oleh DFA Tic-Tac-Toe ini. Dalam pembuatannya, DFA Generator ini tidak menggunakkan satupun library yang terkait dengan DFA, semuanya dibuat sendiri dari 0. Algoritma yang digunakan dalam penentuan gerakan terbaik / best move bagi komputer adalah algoritma MinMax.
  
 ### Algoritma MinMax
  Algoritma MinMax bekerja dengan cara brute-force, yaitu mencoba setiap kemungkinan yang ada. Untuk setiap move / petak kosong yang tersedia, MinMax akan mencoba menaruh gerakan di sana lalu mencatat skornya. Skor dihitung dengan memanggil algoritma MinMax lagi terhadap kondisi papan yang baru. Dilakukan secara rekursif hingga tidak ada petak kosong. Jika komputer kalah maka akan diberi skor -10, jika menang akan diberi skor 10, jika draw akan diberi skor 0.<br>
  <b>Terdapat masalah dalam algortima tersebut</b>. Jika hanya dilakukan seperti itu, sangat mungkin 2 kejadian yang berbeda untuk mendapat skor yang sama. Yang dimaksud dalam kejadian yang berbeda adalah, kemungkinan 1 komputer menang dengan 3 gerakan dan kemungkinan ke 2 komputer menang dengan menghabiskan semua gerakan. Tentulah yang lebih baik yang lebih sedikit menggunakkan gerakan. Sehingga ditambah parameter baru untuk menghitung skor yaitu depth / kedalaman rekursif. Semakin dalam rekursifnya, semakin banyak gerakannya, semakin banyak penalti untuk skor.<br>
    Setelah semua skor dikumpulkan, dipilih gerakan yang mengahsilkan skor paling besar jika sedang giliran komputer dan paling kecil jika giliran player, prilaku minimum maksimum tersebut yang menyebabkan nama algoritmanya MinMax.
   
## DFA Tic Tac Toe
  Pada program ini, hal pertama yang dilakukan adalah meninisialisasi DFA dari file eksternal yang ada, lalu program mensimulasikan cara kerja DFA yaitu menerima input lalu pergi ke state sesuai tabel transisi yang sesuai dengan input tersebut.
 
 ### Game.h
  Berisi segala hal yang perlu untuk memulai game Tic Tac Toe seperti startGame untuk memulai game dan inputValid untuk validasi input
 ### Papan.h
  Berisi segala hal yang menyangkut dengan papan Tic Tac Toe tersebut, seperti initPapan untuk membentuk papan kosong, printBoard untuk menampilkan papan ke layar, cekMenang untuk mengecek apakah sudah ada pemengan di papan tersebut
 ### DFA.h
  Berisi segala hal yang berhubungan dengan DFA seperti inisialisasi kondisi awal DFA, pindah state serta mendapatkan move terbaik dari state tersebut.
  
 ### Deskripsi DFA
  DFA memiliki state yang bernama petak-petak yang telah dilewati sejak awal permainan. Contohnya adalah pada daftar state cpu start duluan <b>(009)5,9,1</b> yang berarti state tersebut bernomor 9, letaknya di tabel transisi ada di baris ke 8 (array mulai dari 0), serta kejadian sejak awal permainan adalah cpu meletakan O di 5, pemain meletakan X di 9, dan cpu harus meletakan O di 1 agar tidak kalah. Sehingga dapat dikatakan bahwa bentuk umum dari state ini adalah (Nomor)KejadianLalu,BestMove.
   Language dari DFA ini adalah angka 1-9 yang masing masing menandakan letak petak di papan Tic Tac Toe
