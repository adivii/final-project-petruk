# Perpus 363

Nama  : Adiwijaya Satria Nusantara

NPM   : 2017051006

Tema  : Layanan Perpustakaan

Program ini dibuat sebagai tugas akhir praktikum Pemrograman Terstruktur. Dalam program, saya menggunakan sebuah class Queue yang dibuat dengan menggunakan STL, yaitu deque. Program yang saya buat juga menggunakan file text sebagai basis penyimpanan data sederhana. File text yang dibutuhkan akan dibuat secara otomatis oleh program ketika dijalankan pertama kali.

File text yang dibutuhkan antara lain :
- username
- password
- book_id
- book_data
- request_list

Kelima file diatas merupakan pokok input yang akan digunakan dalam progam.
1. username, digunakan sebagai basis penyimpanan data username milik pengguna
2. password, berpasangan dengan username, befungsi menyimpan data password milik pengguna
3. book_id, menyimpan kode buku yang digenerate secara otomatis oleh program. Struktur kodenya adalah genre (3 digit) - id (8 digit).
4. book_data, menyimpan judul buku, penulis, dan status ketersediaan buku.
5. request_list, menyimpan daftar request yang dibuat oleh user. Saat ini request yang sudah dapat dibuat adalah peminjaman (kode 001) dan pengembalian (kode 002).
