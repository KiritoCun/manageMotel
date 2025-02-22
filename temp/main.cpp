﻿#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
using namespace std;
#include <io.h>
#include <fcntl.h>
#include <string>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <iomanip>
#include <ctime>
#include <Windows.h>

// Minh họa chương trình quản lý khách sạn

// =============== KHAI BÁO CẤU TRÚC DANH SÁCH LIÊN KẾT ÐON ===============
// Khai báo câu trúc dữ liệu date
struct date
{
	int ngay;
	int thang;
	int nam;
};
// Khai báo cấu trúc dữ liệu bill
struct bill
{
	int maHoaDon;
	string tenKhach;
	string soChungMinh;
	int gioiTinh; // 0: Nữ, 1: Nam
	string soPhong;
	char loaiPhong;
	int donGia;
	date ngayDen;
	date ngayDi;
	int tienPhong;
};
typedef struct bill Bill;

// Khai báo cấu trúc 1 node
struct billNode
{
	Bill data; // Dữ liệu chứa trong 1 node - 1 hóa đơn
	struct billNode *pNext; // con trỏ dùng để liên kết các node với nhau
};
typedef struct billNode BillNode;

// Khai báo cấu trúc danh sách liên kết đơn
struct listBill
{
	BillNode *pHead; // node quản lý đầu danh sách
	BillNode *pTail; // node quản lý cuối danh sách
};
typedef struct listBill ListBill;

// =============== KHỞI TẠO CẤU TRÚC DANH SÁCH LIÊN KẾT ÐƠN ===============
void khoiTao(ListBill &list) {
	list.pHead = NULL;
	list.pTail = NULL;
}

// Hàm khởi tạo 1 node
BillNode *khoiTaoBillNode(Bill b) {
	BillNode *p = new BillNode; // cấp phát vùng nhớ cho node p
	p->data = b;
	p->pNext = NULL;
	return p;
}

// =============== TIỆN ÍCH ==================
// Hàm chuyển 1 string về chữ thường => để so sánh chuỗi không phân biệt hoa thường
string toLower(string s) {
	string str;
	for (int i = 0; i < s.length(); i++)
	{
		char c = s.at(i);
		str.push_back(tolower(c));
	}
	return str;
}

// Hàm so sánh 2 chuỗi không phân biệt hoa thường
bool kiemTraChuoi(string s1, string s2) {
	string s3 = toLower(s1);
	string s4 = toLower(s2);
	if (s3.compare(s4) == 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

// Hàm kiểm tra chuỗi s1 có chứa chuỗi s2 không ?
bool checkStr(string s1, string s2) {
	string s3 = toLower(s1);
	string s4 = toLower(s2);
	if (strstr(s3.c_str(), s4.c_str()) != NULL)
	{
		return true;
	}
	else
	{
		return false;
	}
}

// =============== 2. THÊM 1 HÓA ĐƠN VÀO DANH SÁCH ===============
// Hàm kiểm tra mã có trùng hay không ?
bool checkMa(int ma, ListBill list) {
	for (BillNode *k = list.pHead; k != NULL; k = k->pNext) {
		if (k->data.maHoaDon == ma)
		{
			return true;
		}
	}
	return false;
}

// Hàm nhập giá trị 1 hóa đơn
BillNode *nhap(Bill b, ListBill list) {
	do
	{
		cout << "Nhap ma hoa don (So nguyen duong): ";
		cin >> b.maHoaDon;
	} while (checkMa(b.maHoaDon, list) || b.maHoaDon <= 0);
	cin.ignore();
	cout << "Nhap ten khach: ";
	getline(cin, b.tenKhach);
	cout << "Nhap so chung minh: ";
	getline(cin, b.soChungMinh);
	do
	{
		cout << "Nhap gioi tinh (0:Nu/ 1:Nam): ";
		cin >> b.gioiTinh;
	} while (b.gioiTinh != 0 && b.gioiTinh != 1);
	cin.ignore();
	int kiemTra;
	do
	{
		cout << "Nhap so phong (bat dau bang chu cai): ";
		getline(cin, b.soPhong);
		kiemTra = int(b.soPhong.at(0));
	} while (!((65 <= kiemTra && kiemTra <= 90) || (97 <= kiemTra && kiemTra <= 122)));
	b.soPhong = toLower(b.soPhong);

	cout << "Nhap ngay den: ";
	cout << "\nNgay: ";
	cin >> b.ngayDen.ngay;
	cout << "Thang: ";
	cin >> b.ngayDen.thang;
	cout << "Nam: ";
	cin >> b.ngayDen.nam;
	cout << "Nhap ngay di: ";
	cout << "\nNgay: ";
	cin >> b.ngayDi.ngay;
	cout << "Thang: ";
	cin >> b.ngayDi.thang;
	cout << "Nam: ";
	cin >> b.ngayDi.nam;
	b.loaiPhong = b.soPhong.at(0);
	switch (b.loaiPhong)
	{
	case 'A':
	case 'a':b.donGia = 400;
		break;
	case 'B':
	case 'b':b.donGia = 300;
		break;
	default:
		b.donGia = 250;
		break;
	}
	b.tienPhong = b.donGia * (b.ngayDi.ngay - b.ngayDen.ngay);
	BillNode *p = khoiTaoBillNode(b);
	return p;
}

// Hàm thêm 1 hóa đơn vào đầu danh sách
void InsertFirst(ListBill &list, BillNode *p) {
	// danh sách đang rỗng
	if (list.pHead == NULL)
	{
		list.pHead = list.pTail = p; // node đầu cũng là node cuối và là p
	}
	else
	{
		p->pNext = list.pHead;
		list.pHead = p;
	}
}

// Hàm thêm 1 sách vào cuối danh sách
void InsertLast(ListBill &list, BillNode *p) {
	// danh sách đang rỗng
	if (list.pHead == NULL)
	{
		list.pHead = list.pTail = p; // node đầu cũng là node cuối và là p
	}
	else
	{
		list.pTail->pNext = p;
		list.pTail = p;
	}
}

// Hàm thêm 1 hóa đơn vào sau 1 hóa đơn nào đó
void InsertAfter(ListBill &list, BillNode *p) {
	int ma;
	cout << "\nBan muon them vao sau hoa don nao? Nhap ma hoa don: ";
	cin >> ma;
	if (list.pHead == NULL)
	{
		list.pHead = list.pTail = p;
		return;
	}
	if (list.pHead->data.maHoaDon == ma && list.pHead->pNext == NULL)
	{
		InsertLast(list, p);
	}
	else
	{
		for (BillNode *k = list.pHead; k != NULL; k = k->pNext)
		{
			if (k->data.maHoaDon == ma)
			{
				BillNode *g = k->pNext; // cho node g trỏ đến node nằm sau node q
				p->pNext = g;
				k->pNext = p;
			}
		}
	}
}

// =============== 1. KHỞI TẠO DANH SÁCH ===============
// Khởi tạo danh mục hóa đơn rỗng (chưa có hóa đơn)
// Ðọc từ file: nhập vào tên file đã lưu danh mục hóa đơn ? (lần làm việc trước đó)
void docMotHoaDon(ifstream &filein, Bill &b) {
	string ma = to_string(b.maHoaDon);
	getline(filein, ma, ';');
	b.maHoaDon = atoi(ma.c_str());
	getline(filein, b.tenKhach, ';');
	getline(filein, b.soChungMinh, ';');
	string sex = to_string(b.gioiTinh);
	getline(filein, sex, ';');
	b.gioiTinh = atoi(sex.c_str());
	getline(filein, b.soPhong, ';');
	// Ngày đến
	string ngay1 = to_string(b.ngayDen.ngay);
	getline(filein, ngay1, '/');
	b.ngayDen.ngay = atoi(ngay1.c_str());
	string thang1 = to_string(b.ngayDen.thang);
	getline(filein, thang1, ';');
	b.ngayDen.thang = atoi(thang1.c_str());
	// Ngày đi
	string ngay2 = to_string(b.ngayDi.ngay);
	getline(filein, ngay2, '/');
	b.ngayDi.ngay = atoi(ngay2.c_str());
	//string thang2 = to_string(b.ngayDi.thang);
	filein >> b.ngayDi.thang;
	//getline(filein, thang2, ';');
	//b.ngayDi.thang = atoi(thang2.c_str());

	b.loaiPhong = b.soPhong[0];
	switch (b.loaiPhong)
	{
	case 'A':
	case 'a': b.donGia = 400;
		break;
	case 'B':
	case 'b':b.donGia = 300;
		break;
	default:
		b.donGia = 250;
		break;
	}
	b.tienPhong = (b.ngayDi.ngay - b.ngayDen.ngay)* b.donGia;
}

void docFile(ifstream &filein, ListBill &list) {
	while (!filein.eof())
	{
		Bill b;
		docMotHoaDon(filein, b);
		if (b.maHoaDon == 0)
		{
			break;
		}
		BillNode *p = khoiTaoBillNode(b);
		InsertLast(list, p);
	}
}

// Hàm kiểm tra file có tồn tại hay không ?
bool checkFile(string path) {
	ifstream isf(path);
	return isf.good();
}

// =============== 3. XOÁ 1 HÓA ĐƠN KHỎI DANH SÁCH ===============
// Xoá hóa đơn ở đầu danh sách
void deleteFirst(ListBill &list) {
	if (list.pHead == NULL)
	{
		cout << "Danh sach rong!" << endl;
		return;
	}
	BillNode *p = list.pHead; // node p là node sẽ xoá
	list.pHead = list.pHead->pNext; // cập nhật lại pHead là phần tử kế tiếp (thứ 2)
	delete p;
	cout << "Xoa thanh cong!" << endl;
}

// Xoá hóa đơn ở cuối danh sách
void deleteLast(ListBill &list) {
	if (list.pHead == NULL)
	{
		cout << "Danh sach rong!" << endl;
		return;
	}
	// trường hợp danh sách có 1 phần tử
	if (list.pHead->pNext == NULL)
	{
		deleteFirst(list);
		return;
	}
	for (BillNode *k = list.pHead; k != NULL; k = k->pNext)
	{
		// nếu node k là phần tử kề cuối - thực hiện xoá
		if (k->pNext == list.pTail)
		{
			delete list.pTail; // xoá đi phần tử cuối danh sách
			k->pNext = NULL; // cho con trỏ của node kề cuối trỏ đến null
			list.pTail = k; // cập nhật lại pTail
			cout << "Xoa thanh cong!" << endl;
			return;
		}
	}
}

// Xoá hóa đơn ở sau hóa đơn có mã số nào đó
void deleteAfter(ListBill &list) {
	if (list.pHead == NULL)
	{
		cout << "Danh sach rong!" << endl;
		return;
	}
	if (list.pHead->pNext == NULL)
	{
		cout << "Danh sach chi co 1 phan tu!" << endl;
		return;
	}
	int ma;
	cout << "Ban muon xoa hoa don o sau hoa don nao? Nhap ma hoa don: ";
	cin >> ma;
	for (BillNode *k = list.pHead; k != NULL; k = k->pNext)
	{
		if (k->data.maHoaDon == ma)
		{
			BillNode *g = k->pNext; // node g là node nằm sau node k - xoá node g
			k->pNext = g->pNext; // cập nhật liên kết giữa node k với node sau node g
			delete g;
			cout << "Xoa thanh cong!" << endl;
			return;
		}
	}
}

// Xoá hóa đơn theo mã số hóa đơn
void deleteMa(ListBill &list) {
	if (list.pHead == NULL)
	{
		cout << "Danh sach rong!" << endl;
		return;
	}
	int ma;
	cout << "Nhap ma hoa don can xoa: ";
	cin >> ma;
	// trường hợp mã hóa đơn nhập vào nằm đầu danh sách
	if (list.pHead->data.maHoaDon == ma)
	{
		deleteFirst(list);
		return;
	}
	// trường hợp mã hóa đơn nhập vào nằm cuối danh sách
	if (list.pTail->data.maHoaDon == ma)
	{
		deleteLast(list);
		return;
	}
	BillNode *g = new BillNode; // node g là node trỏ đến node nằm trước node cần xoá
	for (BillNode *k = list.pHead; k != NULL; k = k->pNext)
	{
		if (k->data.maHoaDon == ma)
		{
			g->pNext = k->pNext; // cập nhật liên kết giữa node g với node sau node k
			delete k;
			cout << "Xoa thanh cong!" << endl;
			return;
		}
		g = k; // cho node g trỏ đến node k
	}
	cout << "Ma ban nhap khong co trong danh sach!" << endl;
}

// Xoá hóa đơn theo tên khách
void deleteTenKhach(ListBill &list) {
	if (list.pHead == NULL)
	{
		cout << "Danh sach rong!" << endl;
		return;
	}
	cin.ignore();
	string tenKhach;
	cout << "Nhap ten khach can xoa: ";
	getline(cin, tenKhach);
	// trường hợp tên khách nhập vào nằm đầu danh sách
	if (kiemTraChuoi(list.pHead->data.tenKhach,tenKhach))
	{
		deleteFirst(list);
	}
	// trường hợp tên khách nhập vào nằm cuối danh sách
	if (kiemTraChuoi(list.pTail->data.tenKhach, tenKhach))
	{
		deleteLast(list);
	}
	int test = 0;
	BillNode *g = new BillNode; // node g là node trỏ đến node nằm trước node cần xoá
	for (BillNode *k = list.pHead; k != NULL; k = k->pNext)
	{
		if (kiemTraChuoi(k->data.tenKhach, tenKhach))
		{
			test++;
			g->pNext = k->pNext; // cập nhật liên kết giữa node g với node sau node k
			delete k;
			k = g; // cập nhật lại k
		}
		g = k; // cho node g trỏ đến node k
	}
	if (test == 0) {
		cout << "Ten khach ban nhap khong co trong danh sach!" << endl;
	}
	else
	{
		cout << "Xoa thanh cong hoa don: " << tenKhach << "!" << endl;
	}
}

// Xoá hóa đơn theo số chứng minh
void deleteSoChungMinh(ListBill &list) {
	if (list.pHead == NULL)
	{
		cout << "Danh sach rong!" << endl;
		return;
	}
	cin.ignore();
	string soChungMinh;
	cout << "Nhap so chung minh can xoa: ";
	getline(cin, soChungMinh);
	// trường hợp số chứng minh nhập vào nằm đầu danh sách
	if (kiemTraChuoi(list.pHead->data.soChungMinh, soChungMinh))
	{
		deleteFirst(list);
	}
	// trường hợp số chứng minh nhập vào nằm cuối danh sách
	if (kiemTraChuoi(list.pTail->data.soChungMinh, soChungMinh))
	{
		deleteLast(list);
	}
	int test = 0;
	BillNode *g = new BillNode; // node g là node trỏ đến node nằm trước node cần xoá
	for (BillNode *k = list.pHead; k != NULL; k = k->pNext)
	{
		if (kiemTraChuoi(k->data.soChungMinh, soChungMinh))
		{
			test++;
			g->pNext = k->pNext; // cập nhật liên kết giữa node g với node sau node k
			delete k;
			k = g; // cập nhật lại k
		}
		g = k; // cho node g trỏ đến node k
	}
	if (test == 0) {
		cout << "So chung minh ban nhap khong co trong danh sach!" << endl;
	}
	else {
		cout << "Xoa thanh cong hoa don theo so chung minh: " << soChungMinh << "!" << endl;
	}
}

// ================= CHUC NANG HIEN THI DANH SACH =================
// Hàm hiển thị một hóa đơn
void showBill(Bill b) {
	
	if (b.gioiTinh == 0)
	{
		cout << "| "<< setw(11)<<b.maHoaDon << " || "<<setw(26) << b.tenKhach<<" || " << setw(13) << b.soChungMinh << " || " << setw(9) << "   Nu   " << " || " << setw(8) << b.soPhong << " || " << setw(10) << b.loaiPhong << " || " << setw(7) << b.donGia << " || " << setw(8) << to_string(b.ngayDen.ngay) + "/" + to_string(b.ngayDen.thang) << " || " << setw(7) << to_string(b.ngayDi.ngay) + "/" + to_string(b.ngayDi.thang) << " || " << setw(10) << b.tienPhong << " |" << endl;
	}
	else
	{

		cout << "| " << setw(11) << b.maHoaDon << " || " << setw(26) << b.tenKhach << " || " << setw(13) << b.soChungMinh << " || " << setw(9) << "   Nam   " << " || " << setw(8) << b.soPhong << " || " << setw(10) << b.loaiPhong << " || " << setw(7) << b.donGia << " || " << setw(8) << to_string(b.ngayDen.ngay) + "/" + to_string(b.ngayDen.thang) << " || " << setw(7) << to_string(b.ngayDi.ngay) + "/" + to_string(b.ngayDi.thang) << " || " << setw(10) << b.tienPhong << " |" << endl;
	}
}

// Hàm hiển thị danh sách
void show(ListBill list) {
	if (list.pHead != NULL)
	{
		cout << setw(15) << "|  Ma hoa don |" << setw(30) << "|       Ten Khach hang       |" << setw(17) << "| So chung minh |" << setw(13) << "| Gioi tinh |" << setw(12) << "| So phong |" << setw(14) << "| Loai phong |" << setw(11) << "| Don gia |" << setw(12) << "| Ngay den |" << setw(11) << "| Ngay di |" << setw(14) << "| Tien phong |"<<endl;		
		int dem = 1;
		for (BillNode *k = list.pHead; k != NULL; k = k->pNext)
		{
			showBill(k->data);
		}
		cout << "|___________________________________________________________________________________________________________________________________________________|"<<endl;
	}
	else
	{
		cout << "Chua co du lieu" << endl;
	}
}

// =============== SẮP XẾP DANH SÁCH ===================
// Hàm hoán vị 2 phần tử trong danh sách liên kết
void swap(Bill &b1, Bill &b2) {
	Bill b3;
	b3.maHoaDon = b1.maHoaDon;
	b3.tenKhach = b1.tenKhach;
	b3.soChungMinh = b1.soChungMinh;
	b3.gioiTinh = b1.gioiTinh;
	b3.soPhong = b1.soPhong;
	b3.loaiPhong = b1.loaiPhong;
	b3.donGia = b1.donGia;
	b3.ngayDen.ngay = b1.ngayDen.ngay;
	b3.ngayDen.thang = b1.ngayDen.thang;
	b3.ngayDen.nam = b1.ngayDen.nam;
	b3.ngayDi.ngay = b1.ngayDi.ngay;
	b3.ngayDi.thang = b1.ngayDi.thang;
	b3.ngayDi.nam = b1.ngayDi.nam;
	b3.tienPhong = b1.tienPhong;

	b1.maHoaDon = b2.maHoaDon;
	b1.tenKhach = b2.tenKhach;
	b1.soChungMinh = b2.soChungMinh;
	b1.gioiTinh = b2.gioiTinh;
	b1.soPhong = b2.soPhong;
	b1.loaiPhong = b2.loaiPhong;
	b1.donGia = b2.donGia;
	b1.ngayDen.ngay = b2.ngayDen.ngay;
	b1.ngayDen.thang = b2.ngayDen.thang;
	b1.ngayDen.nam = b2.ngayDen.nam;
	b1.ngayDi.ngay = b2.ngayDi.ngay;
	b1.ngayDi.thang = b2.ngayDi.thang;
	b1.ngayDi.nam = b2.ngayDi.nam;
	b1.tienPhong = b2.tienPhong;

	b2.maHoaDon = b3.maHoaDon;
	b2.tenKhach = b3.tenKhach;
	b2.soChungMinh = b3.soChungMinh;
	b2.gioiTinh = b3.gioiTinh;
	b2.soPhong = b3.soPhong;
	b2.loaiPhong = b3.loaiPhong;
	b2.donGia = b3.donGia;
	b2.ngayDen.ngay = b3.ngayDen.ngay;
	b2.ngayDen.thang = b3.ngayDen.thang;
	b2.ngayDen.nam = b3.ngayDen.nam;
	b2.ngayDi.ngay = b3.ngayDi.ngay;
	b2.ngayDi.thang = b3.ngayDi.thang;
	b2.ngayDi.nam = b3.ngayDi.nam;
	b2.tienPhong = b3.tienPhong;
}

// Hàm sắp xếp theo alphabet
void sortAlphaBet(ListBill list, int n) {
	for (BillNode *k = list.pHead; k != list.pTail; k = k->pNext) {
		for (BillNode *j = k->pNext; j != NULL; j = j->pNext) {
			string s1, s2;
			if (n == 1)
			{
				s1 = to_string(k->data.maHoaDon);
				s2 = to_string(j->data.maHoaDon);
			}
			else if (n == 2)
			{
				s1 = toLower(k->data.tenKhach);
				s2 = toLower(j->data.tenKhach);
			}
			else
			{
				s1 = toLower(k->data.soChungMinh);
				s2 = toLower(j->data.soChungMinh);
			}
			if (s1.compare(s2) > 0)
			{
				swap(k->data, j->data);
			}
		}
		
	}
}

// Hàm sắp xếp theo ngày đến (theo dòng thời gian)
void sortNgayDen(ListBill list) {
	for (BillNode *k = list.pHead; k != list.pTail; k = k->pNext) {
		for (BillNode *j = k->pNext; j != NULL; j = j->pNext) {
			if (k->data.ngayDen.ngay > j->data.ngayDen.ngay)
			{
				swap(k->data, j->data);
			}
		}
	}
}

// =============== 5. CHUC NANG XEM DANH SÁCH ===============
// Hàm hiển thị danh sách tất cả những hóa đơn
void showListBill(ListBill list) {
	if (list.pHead != NULL)
	{
		cout << "\n ___________________________________________________________________________________________________________________________________________________";
		cout << "\n|                                                                DANH SACH HOA DON                                                                  |";
		cout << "\n|___________________________________________________________________________________________________________________________________________________|" << endl;
		cout << setw(15) << "| Ma hoa don  |" << setw(30) << "|       Ten Khach hang       |" << setw(17) << "| So chung minh |" << setw(13) << "| Gioi tinh |" << setw(12) << "| So phong |" << setw(14) << "| Loai phong |" << setw(11) << "| Don gia |" << setw(12) << "| Ngay den |" << setw(11) << "| Ngay di |" << setw(14) << "| Tien phong |" << endl;
		int dem = 1;
		for (BillNode *k = list.pHead; k != NULL; k = k->pNext)
		{
				dem++;
				showBill(k->data);
		}
		if (dem == 1)
		{
		cout << "|                                                              Danh sach hoa don rong !!!                                                             |" << endl;
		}
		cout << "|___________________________________________________________________________________________________________________________________________________|" << endl;
	}
	else
	{
		cout << "Chua co du lieu" << endl;
	}
}

// Hàm hiển thị danh sách những hóa đơn mà khách chưa trả phòng
void showChuaTra(ListBill list) {
	if (list.pHead != NULL)
	{
		time_t now = time(0);
		tm* ltm = localtime(&now);
		//int nam = 1900 + ltm->tm_year;
		//int thang = 1 + ltm->tm_mon;
		int ngay = ltm->tm_mday;
		cout << "\n ___________________________________________________________________________________________________________________________________________________";
		cout << "\n|                                                    DANH SACH BILL MA KHACH CHUA TRA PHONG                                                         |";
		cout << "\n|___________________________________________________________________________________________________________________________________________________|"<<endl;
		cout << setw(15) << "| Ma hoa don  |" << setw(30) << "|       Ten Khach hang       |" << setw(17) << "| So chung minh |" << setw(13) << "| Gioi tinh |" << setw(12) << "| So phong |" << setw(14) << "| Loai phong |" << setw(11) << "| Don gia |" << setw(12) << "| Ngay den |" << setw(11) << "| Ngay di |" << setw(14) << "| Tien phong |" << endl;
		int dem = 1;
		for (BillNode *k = list.pHead; k != NULL; k = k->pNext)
		{
			if (k->data.ngayDi.ngay > ngay)
			{
				dem++;
				showBill(k->data);
			}
		}
		if (dem == 1)
		{
			cout << "|                                                      Khong co hoa don nao ma khach chua tra phong                                                 |" << endl;
		}
		cout << "|___________________________________________________________________________________________________________________________________________________|" << endl;
	}
	else
	{
		cout << "Chua co du lieu" << endl;
	}
}

// Hàm hiển thị danh sách những hóa đơn mà khách đã trả phòng
void showDaTra(ListBill list) {
	if (list.pHead != NULL)
	{
		time_t now = time(0);
		tm* ltm = localtime(&now);
		//int nam = 1900 + ltm->tm_year;
		//int thang = 1 + ltm->tm_mon;
		int ngay = ltm->tm_mday;
		cout << "\n ___________________________________________________________________________________________________________________________________________________";
		cout << "\n|                                                    DANH SACH BILL MA KHACH DA TRA PHONG                                                           |";
		cout << "\n|___________________________________________________________________________________________________________________________________________________|" << endl;
		cout << setw(15) << "| Ma hoa don  |" << setw(30) << "|       Ten Khach hang       |" << setw(17) << "| So chung minh |" << setw(13) << "| Gioi tinh |" << setw(12) << "| So phong |" << setw(14) << "| Loai phong |" << setw(11) << "| Don gia |" << setw(12) << "| Ngay den |" << setw(11) << "| Ngay di |" << setw(14) << "| Tien phong |" << endl;
		int dem = 1;
		for (BillNode* k = list.pHead; k != NULL; k = k->pNext)
		{
			if (k->data.ngayDi.ngay < ngay)
			{
				dem++;
				showBill(k->data);
			}
		}
		if (dem == 1)
		{
			cout << "|Khong co hoa don nao ma khach da tra phong                                                                                                         |" << endl;
		}
		cout << "|___________________________________________________________________________________________________________________________________________________|" << endl;
	}
	else
	{
		cout << "Chua co du lieu" << endl;
	}
}

// Hàm hiển thị danh sách theo alphabet 
void showAlphaBet(ListBill list, int n) {
	if (list.pHead != NULL)
	{
		if (n == 1)
		{
			sortAlphaBet(list, n);
			cout << "\n ___________________________________________________________________________________________________________________________________________________";
			cout << "\n|                                                      DANH SACH BILL THEO ALPHABET MA HOA DON                                                      |";
			cout << "\n|___________________________________________________________________________________________________________________________________________________|" << endl;
			show(list);
			cout << "\n|___________________________________________________________________________________________________________________________________________________|" << endl;
		}
		else if (n == 2)
		{
			sortAlphaBet(list, n);
			cout << "\n ___________________________________________________________________________________________________________________________________________________";
			cout << "\n|                                                     DANH SACH BILL THEO ALPHABET TEN KHACH HANG                                                   |";
			cout << "\n|___________________________________________________________________________________________________________________________________________________|" << endl;
			show(list);
			cout << "\n|___________________________________________________________________________________________________________________________________________________|" << endl;

		}
		else
		{
			sortAlphaBet(list, n);
			cout << "\n ___________________________________________________________________________________________________________________________________________________";
			cout << "\n|                                                          DANH SACH BILL THEO ALPHABET SO CHUNG MINH                                               |";
			cout << "\n|___________________________________________________________________________________________________________________________________________________|" << endl;
			show(list);
			cout << "\n|___________________________________________________________________________________________________________________________________________________|" << endl;

		}
	}
	else
	{
		cout << "Chua co du lieu !!!" << endl;
	}
}

// Hàm hiển thị danh sách hóa đơn có ngày đến theo dòng thời gian
void showNgayDen(ListBill list) {
	if (list.pHead != NULL)
	{
		sortNgayDen(list);
		cout << "\n ___________________________________________________________________________________________________________________________________________________";
		cout << "\n|                                                 DANH SACH BILL CO NGAY DEN THEO DONG THOI GIAN                                                    |";
		cout << "\n|___________________________________________________________________________________________________________________________________________________|" << endl;
		show(list);
	}
	else
	{
		cout << "Chua co du lieu !!!" << endl;
	}
}

// =============== 4. TÌM KIẾM HÓA ĐƠN ===============
// Hàm tìm kiếm hóa đơn theo mã hóa đơn
void searchMaHoaDon(ListBill list) {
	if (list.pHead == NULL)
	{
		cout << "Danh sach rong !" << endl;
		return;
	}
	cin.ignore();
	string maHoaDon;
	cout << "Nhap ma hoa don can tim: ";
	getline(cin, maHoaDon);
	int dem = 1;
	for (BillNode *k = list.pHead; k != NULL; k = k->pNext)
	{
		if (checkStr(to_string(k->data.maHoaDon), maHoaDon))
		{
			if (dem == 1)
			{
				cout << "\n ___________________________________________________________________________________________________________________________________________________";
				cout << "\n|                                                             KET QUA TIM KIEM                                                                      |";
				cout << "\n|___________________________________________________________________________________________________________________________________________________|" << endl;
				cout << setw(15) << "| Ma hoa don  |" << setw(30) << "|       Ten Khach hang       |" << setw(17) << "| So chung minh |" << setw(13) << "| Gioi tinh |" << setw(12) << "| So phong |" << setw(14) << "| Loai phong |" << setw(11) << "| Don gia |" << setw(12) << "| Ngay den |" << setw(11) << "| Ngay di |" << setw(14) << "| Tien phong |" << endl;
			}
			dem++;
			showBill(k->data);
			cout << "|___________________________________________________________________________________________________________________________________________________|"<<endl;
		}
	}
	if (dem == 1)
	{
		cout << "Khong tim thay " << maHoaDon << endl;
	}
}

// Hàm tìm kiếm hóa đơn theo tên khách hàng
void searchTenKhach(ListBill list) {
	if (list.pHead == NULL)
	{
		cout << "Danh sach rong!" << endl;
		return;
	}
	cin.ignore();
	string tenKhach;
	cout << "Nhap ten Khach can tim: ";
	getline(cin, tenKhach);
	int dem = 1;
	for (BillNode *k = list.pHead; k != NULL; k = k->pNext)
	{
		if (checkStr(k->data.tenKhach, tenKhach))
		{
			if (dem == 1)
			{
				cout << "\n ___________________________________________________________________________________________________________________________________________________";
				cout << "\n|                                                              KET QUA TIM KIEM                                                                     |";
				cout << "\n|___________________________________________________________________________________________________________________________________________________|" << endl;
				cout << setw(15) << "| Ma hoa don  |" << setw(30) << "|       Ten Khach hang       |" << setw(17) << "| So chung minh |" << setw(13) << "| Gioi tinh |" << setw(12) << "| So phong |" << setw(14) << "| Loai phong |" << setw(11) << "| Don gia |" << setw(12) << "| Ngay den |" << setw(11) << "| Ngay di |" << setw(14) << "| Tien phong |" << endl;
			}
			dem++;
			showBill(k->data);
			cout << "|___________________________________________________________________________________________________________________________________________________|"<<endl;
		}
	}
	if (dem == 1)
	{
		cout << "Khong tim thay !" << tenKhach << endl;
	}
}

// Hàm tìm kiếm hóa đơn theo số chứng minh
void searchSoChungMinh(ListBill list) {
	if (list.pHead == NULL)
	{
		cout << "Danh sach rong!" << endl;
		return;
	}
	cin.ignore();
	string soChungMinh;
	cout << "Nhap so chung minh can tim: ";
	getline(cin, soChungMinh);
	int dem = 1;
	for (BillNode *k = list.pHead; k != NULL; k = k->pNext)
	{
		if (checkStr(k->data.soChungMinh, soChungMinh))
		{
			if (dem == 1)
			{
				cout << "\n ___________________________________________________________________________________________________________________________________________________";
				cout << "\n|                                                                KET QUA TIM KIEM                                                                   |";
				cout << "\n|___________________________________________________________________________________________________________________________________________________|" << endl;
				cout << setw(15) << "| Ma hoa don  |" << setw(30) << "|       Ten Khach hang       |" << setw(17) << "| So chung minh |" << setw(13) << "| Gioi tinh |" << setw(12) << "| So phong |" << setw(14) << "| Loai phong |" << setw(11) << "| Don gia |" << setw(12) << "| Ngay den |" << setw(11) << "| Ngay di |" << setw(14) << "| Tien phong |" << endl;
			}
			dem++;
			showBill(k->data);
			cout << "|___________________________________________________________________________________________________________________________________________________|"<<endl;

		}
	}
	if (dem == 1)
	{
		cout << "Khong tim thay !" << soChungMinh << endl;
	}
}



// =============== 6. CHỈNH SỬA NỘI DUNG HÓA ĐƠN ===============
void editHoaDon(ListBill &list) {
	int ma;
	cout << "Nhap ma hoa don can sua: ";
	cin >> ma;
	for (BillNode *k = list.pHead; k != NULL; k = k->pNext)
	{
		if (k->data.maHoaDon == ma)
		{
			cout << "\n ________________________________________________________________";
			cout << "\n|                   TUY CHON SUA THONG TIN                       |";
			cout << "\n|________________________________________________________________|";
			cout << "\n| 1 | Ten khach hang                                             |";
			cout << "\n| 2 | So phong                                                   |";
			cout << "\n| 3 | So chung minh                                              |";
			cout << "\n| 4 | Ngay den                                                   |";
			cout << "\n| 5 | Ngay di                                                    |";
			cout << "\n|___|____________________________________________________________|" << endl;
			cout << "Nhap so tuong ung voi thong tin can sua: ";
			int choise;
			cin >> choise;
			cin.ignore();
			switch (choise) {
			case 1: {
				string str;
				getline(cin, str);
				k->data.tenKhach = str;
				break;
			}
			case 2: {
				string str;
				getline(cin, str);
				k->data.soPhong = str;
				k->data.loaiPhong = k->data.soPhong[0];
				switch (k->data.loaiPhong)
				{
				case 'A':
				case 'a': k->data.donGia = 400;
					break;
				case 'B':
				case 'b':k->data.donGia = 300;
					break;
				default:
					k->data.donGia = 250;
					break;
				}
				k->data.tienPhong = k->data.donGia * (k->data.ngayDi.ngay - k->data.ngayDen.ngay);
				break;
			}
			case 3: {
				string str;
				getline(cin, str);
				k->data.soChungMinh = str;
				break;
			}
			case 4: {
				int ngay, thang, nam;
				cout << "Ngay ";
				cin >> ngay;
				cout << "Thang ";
				cin >> thang;
				cout << "Nam ";
				cin >> nam;
				
				k->data.ngayDen.ngay = ngay;
				k->data.ngayDen.thang = thang;
				k->data.ngayDen.nam = nam;
				break;
			}
			case 5: {
				int ngay, thang, nam;
				cout << "Ngay ";
				cin >> ngay;
				cout << "Thang ";
				cin >> thang;
				cout << "Nam ";
				cin >> nam;

				k->data.ngayDi.ngay = ngay;
				k->data.ngayDi.thang = thang;
				k->data.ngayDi.nam = nam;
				break;
			}
			default: {
				cout << "Khong xac nhan duoc yeu cau !" << endl;
			}
			}
			cout << "Sua thanh cong!" << endl;
			return;
		}
	}
	cout << "Ma ban nhap khong co trong danh sach!" << endl;
}

// =============== 7. THONG KE THEO LOAI PHONG
void statisticalHoaDon(ListBill& list) {
	if (list.pHead != NULL) {
		cout << "\n _____________________________________";
		cout << "\n|    BANG THONG KE THEO LOAI PHONG    |";
		cout << "\n|_____________________________________|" << endl;
		cout << setw(20) << "|    Loai Phong    |" << setw(19) << "|    Tong Tien    |" << endl;
		for (int i = 65; i <= 90; i++)
		{
			int sum = 0;
			for (BillNode* k = list.pHead; k != NULL; k = k->pNext)
			{
				if (int(k->data.loaiPhong) == i)
				{
					sum += k->data.tienPhong;
				}
			}
			if (sum != 0) {
				cout << "|        " << setw(2) << char(i+32) << "        ||" << setw(14) << sum << "   |" << endl;
			}
		}
		cout << "|__________________||_________________|" << endl;
	}
	
}
// =============== 8. LUU VÀO FILE ===============
void ghiMotHoaDon(ofstream &fileout, Bill b) {
	fileout << b.maHoaDon << ";" << b.tenKhach << ";" << b.soChungMinh << ";" << b.gioiTinh << ";" << b.soPhong << ";" << to_string(b.ngayDen.ngay)+"/"+to_string(b.ngayDen.thang) <<";"<< to_string(b.ngayDi.ngay) + "/" + to_string(b.ngayDi.thang);
}

void ghiFile(ofstream &fileout, ListBill  list) {
	for (BillNode*k = list.pHead; k != NULL; k = k->pNext)
	{
		ghiMotHoaDon(fileout, k->data);
	}
}

// Hàm giải phóng vùng nhớ cho danh sách liên kết đơn
void giaiPhongVungNho(ListBill &list) {
	BillNode *k = NULL;
	while (list.pHead != NULL)
	{
		k = list.pHead;
		list.pHead = list.pHead->pNext;
		delete k;
	}
}

// Menu
void menu(ListBill &list) {
	int luaChon;
	while (true)
	{
		system("cls");
		cout << "\n ________________________________________________________________";
		cout << "\n|       DE TAI: CHUONG TRINH QUAN LY THONG TIN KHACH SAN         |";
		cout << "\n|________________________________________________________________|";
		cout << "\n|                     GVHD : DO THI TUYET HOA                    |";
		cout << "\n|________________________________________________________________|";
		cout << "\n|                     SVTH : LE DINH HOA                         |";
		cout << "\n|                     LOP  : 17T2                                |";
		cout << "\n|                     MSSV : 102170085                           |";
		cout << "\n|                     SVTH : NGUYEN DONG CAO                     |";
		cout << "\n|                     LOP  : 17T2                                |";
		cout << "\n|                     MSSV : 102170073                           |";
		cout << "\n|________________________________________________________________|";
		cout << "\n ________________________________________________________________";
		cout << "\n|                 CHUC NANG CHINH CUA CHUONG TRINH               |";
		cout << "\n|________________________________________________________________|";
		cout << "\n| 0 | Exit                                                       |";
		cout << "\n| 1 | Khoi tao danh sach                                         |";
		cout << "\n| 2 | Them 1 hoa don vao danh sach                               |";
		cout << "\n| 3 | Xoa 1 hoa don khoi danh sach                               |";
		cout << "\n| 4 | Tim kiem hoa don                                           |";
		cout << "\n| 5 | Hien thi danh sach                                         |";
		cout << "\n| 6 | Chinh sua noi dung hoa don                                 |";
		cout << "\n| 7 | Thong ke theo loai phong gom (Loai phong, tong tien)       |";
		cout << "\n| 8 | Luu file                                                   |";
		cout << "\n|___|____________________________________________________________|" << endl;

		cout << "Nhap lua chon: ";
		cin >> luaChon;
		if (luaChon == 0)
		{
			cout << "Goodbye !" << endl;
			system("pause");
			break;
		}
		else if (luaChon == 1)
		{
			int luaChon1;
			while (true) {
				system("cls");
				cout << "\n ________________________________________________________________";
				cout << "\n|                    KHOI TAO DANH SACH                          |";
				cout << "\n|________________________________________________________________|";
				cout << "\n| 0 | Exit                                                       |";
				cout << "\n| 1 | Khoi tao danh muc rong                                     |";
				cout << "\n| 2 | Doc tu file lam viec truoc do                              |";
				cout << "\n|___|____________________________________________________________|" << endl;

				cout << "Nhap lua chon: ";
				cin >> luaChon1;
				if (luaChon1 == 0) {
					break;
				}
				else if (luaChon1 == 1)
				{
					khoiTao(list);
					cout << "  Khoi tao thanh cong!" << endl;
					system("pause");
				}
				else if (luaChon1 == 2)
				{
					khoiTao(list);
					cin.ignore();
					string tenFile;
					cout << "Nhap ten file: ";
					getline(cin, tenFile);
					if (checkFile(tenFile))
					{
						ifstream filein;
						filein.open(tenFile, ios_base::in);
						docFile(filein, list);
						filein.close();
						cout << "Doc file thanh cong!" << endl;
					}
					else
					{
						cout << "File ban nhap khong ton tai, vui long kiem tra lai!" << endl;
					}
					system("pause");
				}
				else
				{
					cout << "Lua chon cua ban khong hop le, vui long nhap lua chon tu 0 - 2!" << endl;
					system("pause");
				}
			}
		}
		else if (luaChon == 2)
		{
			int luaChon2;
			while (true)
			{
				system("cls");
				cout << "\n ________________________________________________________________";
				cout << "\n|                   THEM 1 HOA DON VAO DANH SACH                 |";
				cout << "\n|________________________________________________________________|";
				cout << "\n| 0 | Exit                                                       |";
				cout << "\n| 1 | Them vao dau danh sach                                     |";
				cout << "\n| 2 | Them vao sau 1 hoa don nao do                              |";
				cout << "\n| 3 | Them vao cuoi danh sach                                    |";
				cout << "\n|___|____________________________________________________________|" << endl;

				cout << "Nhap lua chon: ";
				cin >> luaChon2;
				if (luaChon2 == 0)
				{
					break;
				}
				else if (luaChon2 == 1)
				{
					cout << "========= Nhap thong tin hoa don =========" << endl;
					Bill b;
					BillNode *p = nhap(b, list);
					InsertFirst(list, p);
				}
				else if (luaChon2 == 2)
				{
					cout << "========= Nhap thong tin hoa don =========" << endl;
					Bill b;
					BillNode *p = nhap(b, list);
					InsertAfter(list, p);
				}
				else if (luaChon2 == 3)
				{
					cout << "========= Nhap thong tin hoa don =========" << endl;
					Bill b;
					BillNode *p = nhap(b, list);
					InsertLast(list, p);
				}
				else
				{
					cout << "Lua chon cua ban khong hop le, vui long nhap lua chon tu 0 - 3!" << endl;
					system("pause");
				}
			}
		}
		else if (luaChon == 3)
		{
			int luachon3;
			while (true)
			{
				system("cls");
				cout << "\n ________________________________________________________________";
				cout << "\n|                  XOA 1 HOA DON KHOI DANH SACH                  |";
				cout << "\n|________________________________________________________________|";
				cout << "\n| 0 | Exit                                                       |";
				cout << "\n| 1 | Xoa theo ma so hoa don                                     |";
				cout << "\n| 2 | Xoa theo ten khach                                         |";
				cout << "\n| 3 | Xoa theo so chung minh                                     |";
				cout << "\n| 4 | Xoa hoa don o dau danh sach                                |";
				cout << "\n| 5 | Xoa hoa don o sau 1 hoa don co ma hoa don nao do           |";
				cout << "\n| 6 | Xoa hoa don o cuoi danh sach                               |";
				cout << "\n|___|____________________________________________________________|" << endl;

				cout << "Nhap lua chon: ";
				cin >> luachon3;
				if (luachon3 == 0)
				{
					break;
				}
				else if (luachon3 == 1)
				{
					deleteMa(list);
					system("pause");
				}
				else if (luachon3 == 2)
				{
					deleteTenKhach(list);
					system("pause");
				}
				else if (luachon3 == 3)
				{
					deleteSoChungMinh(list);
					system("pause");
				}
				else if (luachon3 == 4)
				{
					deleteFirst(list);
					system("pause");
				}
				else if (luachon3 == 5)
				{
					deleteAfter(list);
					system("pause");
				}
				else if (luachon3 == 6)
				{
					deleteLast(list);
					system("pause");
				}
				else
				{
					cout << "Lua chon cua ban khong hop le, vui long nhap lua chon tu 0 - 6!" << endl;
					system("pause");
				}
			}
		}
		else if (luaChon == 4)
		{
			int luaChon4;
			while (true)
			{
				system("cls");
				cout << "\n ________________________________________________________________";
				cout << "\n|                       TIM KIEM HOA DON                         |";
				cout << "\n|________________________________________________________________|";
				cout << "\n| 0 | Exit                                                       |";
				cout << "\n| 1 | Tim kiem theo ma hoa don                                   |";
				cout << "\n| 2 | Tim kiem theo ten khach                                    |";
				cout << "\n| 3 | Tim kiem theo so chung minh                                |";
				cout << "\n|___|____________________________________________________________|" << endl;

				cout << "Nhap lua chon: ";
				cin >> luaChon4;
				if (luaChon4 == 0)
				{
					break;
				}
				else if (luaChon4 == 1)
				{
					searchMaHoaDon(list);
					system("pause");
				}
				else if (luaChon4 == 2)
				{
					searchTenKhach(list);
					system("pause");
				}
				else if (luaChon4 == 3)
				{
					searchSoChungMinh(list);
					system("pause");
				}
				else
				{
					cout << "Lua chon cua ban khong hop le, vui long nhap lua chon tu 0 - 3!" << endl;
					system("pause");
				}
			}
		}
		else if (luaChon == 5)
		{
			int luaChon5;
			while (true)
			{
				system("cls");
				cout << "\n ________________________________________________________________";
				cout << "\n|                      HIEN THI DANH SACH                        |";
				cout << "\n|________________________________________________________________|";
				cout << "\n| 0 | Exit                                                       |";
				cout << "\n| 1 | Hien thi toan bo danh muc hoa don trong danh sach          |";
				cout << "\n| 2 | Hien thi nhung hoa don ma khach hang van dang su dung phong|";
				cout << "\n| 3 | Hien thi nhung hoa don ma khach hang da tra phong          |";
				cout << "\n| 4 | Hien thi sach theo thu tu                                  |";
				cout << "\n|___|____________________________________________________________|" << endl;

				cout << "Nhap lua chon: ";
				cin >> luaChon5;
				if (luaChon5 == 0)
				{
					break;
				}
				else if (luaChon5 == 1)
				{
					cout << "\n ___________________________________________________________________________________________________________________________________________________";
					cout << "\n|                                                               DANH SACH HOA DON                                                                   |";
					cout << "\n|___________________________________________________________________________________________________________________________________________________|" <<endl;
					show(list);
					system("pause");
				}
				else if (luaChon5 == 2)
				{
					showChuaTra(list);
					system("pause");
				}
				else if (luaChon5 == 3)
				{
					showDaTra(list);
					system("pause");
				}
				else if (luaChon5 == 4)
				{
					int luaChon54;
					while (true)
					{
						system("cls");
						cout << "\n ________________________________________________________________";
						cout << "\n|                HIEN THI DANH SACH THEO THU TU                  |";
						cout << "\n|________________________________________________________________|";
						cout << "\n| 0 | Exit                                                       |";
						cout << "\n| 1 | Hien thi hoa don theo alphabet cua ma hoa don              |";
						cout << "\n| 2 | Hien thi hoa don theo alphabet cua ten khach hang          |";
						cout << "\n| 3 | Hien thi hoa don theo alphabet cua so chung minh           |";
						cout << "\n| 4 | Hien thi hoa don theo dong thoi gian (ngay den)            |";
						cout << "\n|___|____________________________________________________________|" << endl;

						cout << "Nhap lua chon: ";
						cin >> luaChon54;
						if (luaChon54 == 0)
						{
							break;
						}
						else if (luaChon54 == 1)
						{
							
							showAlphaBet(list, 1);
							system("pause");
						}
						else if (luaChon54 == 2)
						{
							showAlphaBet(list, 2);
							system("pause");
						}
						else if (luaChon54 == 3)
						{
							showAlphaBet(list, 3);
							system("pause");
						}
						else if (luaChon54 == 4)
						{
							showNgayDen(list);
							system("pause");
						}
						else
						{
							cout << "Lua chon cua ban khong hop le, vui long nhap lua chon tu 0 - 4!" << endl;
							system("pause");
						}
					}
				}
				else
				{
					cout << "Lua chon cua ban khong hop le, vui long nhap lua chon tu 0 - 4!" << endl;
					system("pause");
				}
			}
		}
		else if (luaChon == 6)
		{
		editHoaDon(list);
		system("pause");	
		}
		else if (luaChon == 7)
		{
		statisticalHoaDon(list);
		system("pause");
		}
		else if (luaChon == 8)
		{
			cin.ignore();
			string tenFile;
			cout << "Nhap ten file: ";
			getline(cin, tenFile);			
			ofstream fileout;
			fileout.open(tenFile, ios_base::out);
			ghiFile(fileout, list);
			fileout.close();
			cout << "Luu thanh cong vao file " << tenFile << endl;
			system("pause");
		}
		else
		{
			cout << "Lua chon cua ban khong hop le, vui long nhap lua chon tu 0 - 7!" << endl;
			system("pause");
		}
	}
}

void setupConsole() {
	//Get the window console handle(isn't the right code but works for these sample
	HWND ConsoleWindow;
	ConsoleWindow = GetForegroundWindow();

	//Getting the desktop hadle and rectangule
	HWND   hwndScreen;
	RECT   rectScreen;
	hwndScreen = GetDesktopWindow();
	GetWindowRect(hwndScreen, &rectScreen);

	//Set windows size(see the width problem)
	SetWindowPos(ConsoleWindow, NULL, 0, 0, 1120, 600, SWP_SHOWWINDOW);

	// Get the current width and height of the console
	RECT rConsole;
	GetWindowRect(ConsoleWindow, &rConsole);
	int Width = rConsole.left = rConsole.right;
	int Height = rConsole.bottom - rConsole.top;

	//caculate the window console to center of the screen	
	int ConsolePosX;
	int ConsolePosY;
	ConsolePosX = ((rectScreen.right - rectScreen.left) / 2 - Width / 2);
	ConsolePosY = ((rectScreen.bottom - rectScreen.top) / 2 - Height / 2);
	SetWindowPos(ConsoleWindow, NULL, ConsolePosX, ConsolePosY, Width, Height, SWP_SHOWWINDOW || SWP_NOSIZE);
};
int main() {
	setupConsole();
	ListBill list;
	khoiTao(list); // khởi tạo danh sách
	menu(list);
	giaiPhongVungNho(list);
	
	system("pause");
	return 0;
}
