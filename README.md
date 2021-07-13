# Perpus 363

Nama  : Adiwijaya Satria Nusantara\n
NPM   : 2017051006\n
Tema  : Layanan Perpustakaan\n
\n
Program ini dibuat sebagai tugas akhir praktikum Pemrograman Terstruktur. Dalam program, saya menggunakan sebuah class Queue yang dibuat dengan menggunakan STL, yaitu deque. Program yang saya buat juga menggunakan file text sebagai basis penyimpanan data sederhana. File text yang dibutuhkan akan dibuat secara otomatis oleh program ketika dijalankan pertama kali.\n
File text yang dibutuhkan antara lain :
- username\n
- password\n
- book_id\n
- book_data\n
- request_list\n
Kelima file diatas merupakan pokok input yang akan digunakan dalam progam.\n
1. username, digunakan sebagai basis penyimpanan data username milik pengguna\n
2. password, berpasangan dengan username, befungsi menyimpan data password milik pengguna\n
3. book_id, menyimpan kode buku yang digenerate secara otomatis oleh program. Struktur kodenya adalah genre (3 digit) - id (8 digit).\n
4. book_data, menyimpan judul buku, penulis, dan status ketersediaan buku.\n
5. request_list, menyimpan daftar request yang dibuat oleh user. Saat ini request yang sudah dapat dibuat adalah peminjaman (kode 001) dan pengembalian (kode 002).\n
