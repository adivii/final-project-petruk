// Admin account :
// username : adiwijaya
// password : ilkomp2020

#include <bits/stdc++.h>
using namespace std;

// Class Queue
class Queue{
private:
	// Menyajikan data dalam bentuk deque agar dapat dimanipulasi dari depan dan belakang
	deque<string> data;

public:
	// Mengecek apakah Queueu kosong
	bool isEmpty(){
		// Queue kosong apabila jumlah data di dalamnya adalah 0
		return data.size() == 0;
	}

	// Mengakses elemen dengan posisi paling depan
	string getData(){
		// Cek apakah Queue kosong atau tidak
		if(!isEmpty()){
			// Jika tidak kosong, kembalikan elemen paling depan
			return data.front();
		}else{
			// Jika kosong, kembalikan blank ("")
			return "";
		}
	}

	// Tambahkan data ke dalam queue
	void Enqueue(string newData){
		// push data ke dalam deque (data)
		// Masukkan dalam posisi terakhir
		data.push_back(newData);
	}

	// Hapus data dari Queue
	void Dequeue(){
		// Cek apakah queue kosong atau tidak
		if(!isEmpty()){
			// Jika tidak kosong (masih ada data)
			// Buang data paling depan
			data.pop_front();
		}
	}

	// Menghapus semua elemen dalam Queue
	void clear(){
		// Gunakan fungsi clear untuk membersihkan deque (data)
		data.clear();
	}

	// Mengecek elemen dalam Queue
	bool find(string _inData){
		// Jika data ditemukan dalam deque (data), kembalikan true
		// Jika tidak, kembalikan false
		// Menggunakan binary search
		return binary_search(data.begin(), data.end(), _inData);
	}
};

// Global variable
vector<string> username;
vector<string> password;
vector<string> book_id;
vector<vector<string>> book_data;
Queue request_list; // Menggunakan Class Queue

// Berfungsi membaca dan memasukkan database (user, request, dan buku)
void load_database(); // Membaca data username dan password
void load_databook(); // Membaca data buku
void load_request(); // Membaca data request yang dibuat user
void update_book_data(); // Memperbarui data buku
void update_request(); // Memperbarui data request dari user

// Menu dan template
void print_header(); // Template header
void start_menu(); // Menu awal (berisi login dan register)
void main_menu(); // Menu utama (untuk peminjaman dan pengembalian oleh user)
void admin_menu(); // Menu admin (untuk memproses request dari user)

// Berfungsi untuk login
void login_app(); // Login user
void login_admin(); // Login admin
bool validate_account(string _inUser, string _inPass); // Memvalidasi akun user

// Mendaftar akun
void register_account(); // Membuat akun
bool validate_username_availability(string _inUser); // Mengecek ketersediaan username (tidak duplicate)
void submit_account(string _inUser, string _inPass); // Memasukkan data user yang sudah dicek valid, ke dalam database

// Membuat request
void create_request(string req_type, string username, string req_book); // Membuat request (dari user), dan memasukkan ke dalam daftar request
void pinjam_buku(string _inUser, string _inId); // Membuat request pinjam buku
void kembalikan_buku(string _inUser); // Membuat request kembalikan buku

// Memproses Request
string get_request_type(string req_code); // Mengecek jenis request (pinjam atau kembalikan)
void proses_request(string _inUser, string req_type, string req_book); // Mengolah request dari user (oleh admin)
void give_book(string _inUser, string id); // Memproses peminjaman
void take_book(string _inUser, string id); // Memproses pengembalian

// Lain-lain
string removeWhitespace(string _inStr); // Menghilangkan spasi

int main(){
	// Membaca database
	load_database();
	load_databook();
	load_request();
	
	// Membuka start menu
	start_menu();
}

void load_database(){
	// Membuat variabel
	ifstream file_user; // Menampung username
	ifstream file_pass; // Menampung password
	string temp; // Untuk menampung sementara

	// Buka file
	file_user.open("main_database/username.txt"); // Membuka file yang berisi username
	file_pass.open("main_database/password.txt"); // Membuka file yang berisi password

	// Kosongkan database
	username.clear();
	password.clear();

	if(file_user.fail() || file_pass.fail()){ // Apabila terdapat kesalahan dalam pembukaan file
		cout << "Error loading database!" << endl;
		system("pause");
		exit(0); // To terminate program
	}else{
		// Load isi dari file username.txt
		while(!file_user.eof()){ // Baca selama masih ada konten dalam file
			getline(file_user,temp); // Membaca masukan dari file dan ditampung sementara pada temp
			if(removeWhitespace(temp) != ""){ // Cek jika temp tidak kosong
				username.push_back(temp); // Masukkan data yang dibaca ke dalam vector username
			}
		}

		// Load isi dari file password.txt
		while(!file_pass.eof()){ // Baca selama masih ada konten dalam file
			getline(file_pass,temp); // Membaca masukan dari file dan ditampung sementara pada temp
			if(removeWhitespace(temp) != ""){ // Cek jika temp tidak kosong
				password.push_back(temp); // Masukkan data yang dibaca ke dalam vector password
			}
		}
	}

	// Cek jumlah username dan password
	if(username.size() != password.size()){ // Jika tidak sama (salah satu lebih banyak)
		cout << "Error! Jumlah username (" << username.size() << ") dan password (" << password.size() << ") tidak sama!" << endl;
		system("pause");
		exit(0); // Terminate program
	}


	// Tutup file
	file_user.close();
	file_pass.close();
}

void load_databook(){
	// Membuat variabel
	ifstream file_book_id; // Membaca file id buku
	ifstream file_book_data; // Membaca file data buku
	vector<string> temp_data; // Menampung sementara data buku
	string temp; // Menampung masukan sementara

	// Buka file
	file_book_id.open("main_database/book_id.txt"); // Membuka file id buku
	file_book_data.open("main_database/book_data.txt"); // Membuka file data buku

	// Kosongkan database
	book_id.clear();
	book_data.clear();

	// Mengecek kegagalan load pada salah satu file
	if(file_book_id.fail() || file_book_data.fail()){
		cout << "Error loading database!" << endl;
		system("pause");
		exit(0); // To terminate program
	}else{
		while(!file_book_id.eof()){ // Membaca selama masih ada masukan
			getline(file_book_id,temp); // Menampung masukan sementara dalam temp
			if(removeWhitespace(temp) != ""){ // Cek apakah masukan kosong
				book_id.push_back(temp); // Jika tidak kosong, masukkan data ke dalam vector book_id
			}
		}

		while(!file_book_data.eof()){ // Membaca selama masih ada masukan
			// Karena data buku terdiri atas 3 data, yaitu judul, penulis, dan status
			while(temp_data.size() < 3){
				getline(file_book_data,temp); // Tampung sementara masukan dalam temp
				if(removeWhitespace(temp) != ""){ // Cek apakah masukan kosong
					temp_data.push_back(temp); // Masukkan data ke dalam temp_data (sementara)
				}

				if(file_book_data.eof()){ // Jika sudah sampai di akhir file, keluar dari looping (tanpa memperhatikan jumlah data yang sudah dibaca)
					break;
				}
			}

			if(temp_data.size() == 3){ // Jika data sudah lengkap (judul, penulis, status)
				book_data.push_back(temp_data); // Masukkan data sementara ke dalam vector book_data
				temp_data.clear(); // Kosongkan data sementara untuk menampung masukan berikutnya
			}
		}
	}

	// Mengecek jumlah id dan data
	if(book_id.size() != book_data.size()){ // Jika tidak sama (salah satu lebih banyak), kirimkan pesan error
		cout << "Error! Jumlah id (" << book_id.size() << ") dan data (" << book_data.size() << ") buku tidak sama!" << endl;
		system("pause");
		exit(0);
	}

	// Tutup file
	file_book_id.close();
	file_book_data.close();
}
// Sampe sini gaes
void load_request(){
	ifstream file_req;
	string temp;

	// Buka file
	file_req.open("main_database/request_list.txt");

	// Bersihkan database
	request_list.clear();

	if(file_req.fail()){
		cout << "Error loading database!" << endl;
		system("pause");
		exit(0);
	}else{
		while(!file_req.eof()){
			getline(file_req,temp);
			if(removeWhitespace(temp) != ""){
				request_list.Enqueue(temp);
			}
		}
	}

	file_req.close();
}

void update_book_data(){
	ofstream file_book_data;

	vector<vector<string>>::iterator it = book_data.begin();

	file_book_data.open("main_database/book_data.txt",ios::out);

	if(file_book_data.fail()){
		cout << "Error loading database!" << endl;
		system("pause");
		exit(0); // To terminate program
	}else{
		file_book_data << "" << endl;
		while(it != book_data.end()){
			for(int i = 0;i < 3;i++){
				file_book_data << (*it)[i] << endl;
			}
			file_book_data << endl;
			it++;
		}
	}

	file_book_data.close();

	load_databook();
}

void update_request(){
	ofstream file_req;

	// Buka file
	file_req.open("main_database/request_list.txt",ios::out);

	if(file_req.fail()){
		cout << "Error loading database!" << endl;
		system("pause");
		exit(0);
	}else{
		file_req << "" << endl;
		while(!request_list.isEmpty()){
			file_req << request_list.getData() << endl;
			request_list.Dequeue();
		}
	}

	file_req.close();

	load_request();
}

void print_header(){
	cout << "============================" << endl;
	cout << "===== Perpustakaan 363 =====" << endl;
	cout << "============================" << endl;
	cout << "============================" << endl;
}

void start_menu(){
	string choose;

	system("cls");
	print_header();
	cout << "Ketik \"login\" tanpa tanda petik untuk login ke dalam aplikasi" << endl;
	cout << "Ketik \"admin\" tanpa tanda petik untuk login sebagai admin " << endl;
	cout << "Ketik \"register\" tanpa tanda petik untuk membuat akun" << endl;
	cout << "Ketik \"exit\" tanpa tanda petik untuk keluar dari aplikasi" << endl;
	cout << "============================" << endl;
	cout << "=> ";getline(cin, choose);

	if(removeWhitespace(choose) == "login"){
		login_app();
	}else if(removeWhitespace(choose) == "admin"){
		login_admin();
	}else if(removeWhitespace(choose) == "register"){
		register_account();
	}else if(removeWhitespace(choose) == "exit"){
		exit(0);
	}else{
		cout << "Wrong Command!" << endl;
		system("pause");
		start_menu();
	}
}

void main_menu(string _inUser){
	vector<string>::iterator book_id_it = book_id.begin();
	vector<vector<string>>::iterator book_data_it = book_data.begin();

	string choose;

	while(true){
		system("cls");
		print_header();
		cout << "ID      : " << *book_id_it << endl;
		cout << "Judul   : " << (*book_data_it)[0] << endl;
		cout << "Penulis : " << (*book_data_it)[1] << endl;
		cout << "Status  : " << (*book_data_it)[2] << endl;
		cout << "============================" << endl;
		cout << "Ketik \"next\" tanpa tanda petik untuk melihat buku selanjutnya" << endl;
		cout << "Ketik \"back\" tanpa tanda petik untuk melihat buku sebelumnya" << endl;
		cout << "Ketik \"pinjam\" tanpa tanda petik untuk meminjam buku ini" << endl;
		cout << "Ketik \"kembalikan\" tanpa tanda petik untuk mengembalikan buku yang sedang dipinjam" << endl;
		cout << "Ketik \"logout\" tanpa tanda petik untuk logout" << endl;
		cout << "============================" << endl;
		cout << "=> "; getline(cin,choose);

		if(removeWhitespace(choose) == "next"){
			book_id_it++;
			book_data_it++;
			
			if(book_id_it == book_id.end() || book_data_it == book_data.end()){
				book_id_it = book_id.begin();
				book_data_it = book_data.begin();
			}
		}else if(removeWhitespace(choose) == "back"){
			if(book_id_it == book_id.begin() || book_data_it == book_data.begin()){
				book_id_it = book_id.end()-1;
				book_data_it = book_data.end()-1;
			}else{
				book_id_it--;
				book_data_it--;
			}
		}else if(removeWhitespace(choose) == "pinjam"){
			pinjam_buku(_inUser,*book_id_it);
		}else if(removeWhitespace(choose) == "kembalikan"){
			kembalikan_buku(_inUser);
		}else if(removeWhitespace(choose) == "logout"){
			start_menu();
		}else{
			cout << "Wrong Command!" << endl;
			system("pause");
		}
	}
}

void admin_menu(){
	ifstream opened_file;
	char ch;
	string choose;
	string current_request_user, req_code, requested_book_id;

	current_request_user = request_list.getData();
	cout << current_request_user << endl;

	if(request_list.isEmpty()){
		system("cls");
		print_header();
		cout << "No Request" << endl;
		system("pause");
		start_menu();
	}else{
		opened_file.open("user_request/"+current_request_user+".txt");
	}

	while(!request_list.isEmpty()){
		if(opened_file.fail()){
			cout << "Error loading database!" << endl;
			system("pause");
			exit(0); // To terminate program
		}

		// Membaca tipe request
		while(ch = opened_file.get()){
			if(ch == '#'){
				break;
			}else{
				req_code.push_back(ch);
			}
		}

		// Membaca id buku yang direquest
		opened_file.seekg(4,ios::beg);
		getline(opened_file,requested_book_id);

		system("cls");
		print_header();
		cout << "Username       : " << current_request_user << endl;
		cout << "Request Type   : " << get_request_type(req_code) << endl;
		cout << "Requested Book : " << requested_book_id << endl;
		cout << "============================" << endl;
		cout << "Ketik \"proses\" tanpa tanda petik untuk memproses request" << endl;
		cout << "Ketik \"logout\" tanpa tanda petik untuk logout" << endl;
		cout << "============================" << endl;
		cout << "=> ";getline(cin,choose);

		if(removeWhitespace(choose) == "proses"){
			proses_request(current_request_user, get_request_type(req_code), requested_book_id);
		}else if(removeWhitespace(choose) == "logout"){
			opened_file.close();
			start_menu();
		}else{
			cout << "Wrong Command!" << endl;
			system("pause");
			admin_menu();
		}
	}
}

void login_app(){
	string user,pass;

	system("cls");
	print_header();
	cout << "Username : "; getline(cin,user);
	cout << "Password : "; getline(cin,pass);

	if(validate_account(user, pass)){
		main_menu(user);
	}else{
		cout << "Username atau Password Salah!" << endl;
		system("pause");
		start_menu();
	}
}

void login_admin(){
	string user,pass;

	system("cls");
	print_header();
	cout << "Username : "; getline(cin,user);
	cout << "Password : "; getline(cin,pass);

	if(user == "adiwijaya" && pass == "ilkomp2020"){
		admin_menu();
	}else{
		cout << "Username atau Password Salah!" << endl;
		system("pause");
		start_menu();
	}
}

bool validate_account(string _inUser, string _inPass){
	int user_id, pass_id;

	vector<string>::iterator user_it;
	vector<string>::iterator pass_it;

	user_it = find(username.begin(),username.end(),_inUser); // Mencari username pada database
	pass_it = find(password.begin(),password.end(),_inPass); // Mencari password pada database

	user_id = user_it - username.begin(); // Mendapatkan index data username
	pass_id = pass_it - password.begin(); // Mendapatkan index data password

	// Apabila index username sama dengan index password, serta username dan password ada
	// Username dikatakan ada apabila iteratornya bukan terletak pada end, begitupun dengan password
	if(user_id == pass_id && user_it != username.end() && pass_it != password.end()){
		return true;
	}else{
		return false;
	}
}

void register_account(){
	system("cls");

	string user, pass;

	print_header();
	cout << "Username : "; getline(cin,user);
	cout << "Password : "; getline(cin,pass);

	if(validate_username_availability(user)){
		submit_account(user,pass);
		load_database();
		cout << "Account Created!" << endl;
	}else{
		cout << "Username sudah terpakai!" << endl;
	}

	system("pause");
	start_menu();
}

bool validate_username_availability(string _inUser){
	vector<string>::iterator it;

	it = find(username.begin(), username.end(), _inUser);

	return it == username.end(); // Kembalikan true ketika username tersedia (belum terpakai)	
}

void submit_account(string _inUser, string _inPass){
	ofstream file_user, file_pass, created_file;

	file_user.open("main_database/username.txt",ios::app);
	file_pass.open("main_database/password.txt",ios::app);

	if(file_user.fail() || file_pass.fail()){
		cout << "Error Loading File!" << endl;
		system("pause");
		exit(0); // To terminate program
	}else{
		file_user << _inUser << endl;
		file_pass << _inPass << endl;

		// Buat file
		created_file.open("user_log/"+_inUser+".txt");
		created_file.close();

		created_file.open("user_request/"+_inUser+".txt");
		created_file.close();

		created_file.open("user_book/"+_inUser+".txt");
		created_file.close();
	}

	file_user.close();
	file_pass.close();
}

void create_request(string req_type, string _inUser, string req_book){
	ofstream file_user, file_req, file_log;
	string req_code;

	if(!request_list.find(_inUser)){
		file_user.open("user_request/"+_inUser+".txt");
		file_req.open("main_database/request_list.txt",ios::app);
		file_log.open("user_log/"+_inUser+".txt",ios::app);

		if(file_user.fail() || file_req.fail() || file_log.fail()){
			cout << "Error Loading Database!" << endl;
			system("pause");
			exit(0);
		}else{
			file_req << _inUser << endl;

			if(req_type == "Peminjaman"){
				req_code = "001";
			}else if(req_type == "Pengembalian"){
				req_code = "002";
			}

			file_user << req_code << "#" << req_book << endl;
			file_log << req_code << "#" << req_type << "#" << req_book << endl;

			cout << "Request anda sudah dibuat, mohon tunggu konfirmasi dari admin" << endl;
			
		}
		file_user.close();
	}else{
		cout << "Mohon tunggu request sebelumnya dikonfirmasi oleh admin" << endl;
	}

	
	file_req.close();
	file_log.close();

	load_request();
}

void pinjam_buku(string _inUser, string _inId){
	int book_index = find(book_id.begin(), book_id.end(), _inId) - book_id.begin();
	string temp;

	if(book_data[book_index][2] == "Tersedia"){
		fstream file_user;
		string temp;

		file_user.open("user_book/"+_inUser+".txt",ios::in);

		if(file_user.fail()){
			cout << "Error Loading Database!" << endl;
			system("pause");
			exit(0);
		}else{
			getline(file_user,temp);
			if(removeWhitespace(temp) == ""){
				create_request("Peminjaman", _inUser, _inId);
			}else{
				cout << "Anda hanya dapat meminjam 1 buku" << endl;
			}
		}

		file_user.close();
	}else{
		cout << "Buku sedang dipinjam oleh orang lain. Request Tertolak!" << endl;
	}

	system("pause");
	main_menu(_inUser);
}

void kembalikan_buku(string _inUser){
	ifstream file_user;
	string id;

	file_user.open("user_book/"+_inUser+".txt");

	if(file_user.fail()){
		cout << "Error Loading Database!" << endl;
		system("pause");
		exit(0);
	}else{
		getline(file_user,id);
		if(removeWhitespace(id) == ""){
			cout << "Anda belum meminjam buku apapun!" << endl;
			system("pause");
			main_menu(_inUser);
		}else{
			create_request("Pengembalian",_inUser,id);
		}
	}

	file_user.close();

	system("pause");
	main_menu(_inUser);
}

string get_request_type(string req_code){
	string result = "";

	if(req_code == "001"){
		result = "Peminjaman";
	}else if(req_code == "002"){
		result = "Pengembalian";
	}

	return result;
}

void proses_request(string _inUser, string req_type, string req_book){
	ofstream file_user;

	file_user.open("user_request/"+_inUser+".txt");

	if(file_user.fail()){
		cout << "Error Loading Database!" << endl;
		system("pause");
		exit(0);
	}else{
		if(req_type == "Peminjaman"){
			give_book(_inUser, req_book);
		}else if(req_type == "Pengembalian"){
			take_book(_inUser, req_book);
		}

		file_user << "";

		system("pause");
		admin_menu();
	}

	file_user.close();
}

void give_book(string _inUser, string id){
	int book_index = find(book_id.begin(), book_id.end(), id) - book_id.begin();
	ofstream file_user;
	string temp;

	if(book_data[book_index][2] == "Tersedia"){
		file_user.open("user_book/"+_inUser+".txt");

		if(file_user.fail()){
			cout << "Error Loading Database!" << endl;
			system("pause");
			exit(0);
		}else{			
			file_user << id << endl;
			book_data[book_index][2] = "Dipinjam oleh " + _inUser;
			cout << "Request Berhasil Diproses!" << endl;
		}

		file_user.close();
	}else{
		cout << "Buku sedang dipinjam oleh user lain" << endl;
	}

	request_list.Dequeue();
	update_book_data();
	update_request();
}

void take_book(string _inUser, string id){
	ofstream file_book;
	int book_index = find(book_id.begin(), book_id.end(), id) - book_id.begin();

	file_book.open("user_book/"+_inUser+".txt");

	if(file_book.fail()){
		cout << "Error Loading Database!" << endl;
		system("pause");
		exit(0);
	}else{
		file_book << "";
		book_data[book_index][2] = "Tersedia";

		cout << "Request Berhasil Diproses" << endl;
	}

	file_book.close();
	request_list.Dequeue();
	update_book_data();
	update_request();
}

string removeWhitespace(string _inStr){
	string result;
	string::iterator it;

	it = _inStr.begin();

	while(it != _inStr.end()){
		if(*it != ' '){
			result.push_back(*it);
		}
		it++;
	}

	return result;
}