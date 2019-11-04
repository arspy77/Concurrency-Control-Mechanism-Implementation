# Concurrency-Control-Mechanism-Implementation

## Anggota

Tugas ini dikerjakan oleh:

1. 13517007 Mohammad Ridwan Hady Arifin
2. 13517040 Ariel Ansa Razumardi
3. 13517070 Aidil Rezjki Suljztan S
4. 13517103 Vincent Chuardi
5. 13517133 Fitria Budi Ananda

## Langkah Pengoperasian

Berikut adalah langkah langkah untuk mengoperasikan program

1. Persiapkan g++ compiler yang bisa didapat dari website resminya
2. Untuk pengguna windows, disarankan menggunakan wsl (windows sub system linux), terutama untuk penggunaan beberapa methods dan ```make``` yang dimiliki olehnya
3. Jalankan perintah berikut pada wsl atau linux anda
   ```
   $ sudo rm -rf obj bin
   ```
   Note : 
   _Hal ini dilakukan untuk memastikan pada langkah selanjutnya, dipergunakan hasil kompilasi dari kode terbaru._
4. Selanjutnya jalankan perintah berikut.
   ```
   $ make test
   ``` 
5. Jika terjadi error ```sched_affinity: Invalid argument```, silakan buka txn_processor_test.cc dan ganti ```CPU_SET(7, &cs)``` menjadi sekitar ```CPU_SET(3, &cs)```, atau mengikuti kemampuan komputer anda.
6. Tunggu hingga semua proses selesai dijalankan.
7. Happy Analyzing.