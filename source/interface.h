#ifndef INTERFACE_H
#define INTERFACE_H
#include <iostream>
#include <string>
#include <fstream> 

void clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        (void)system("clear");
    #endif
}

void displayMainMenu() {
    clearScreen();
    std::cout << "===========================================\n";
    std::cout << "     HE THONG QUAN LY KHO HANG\n";
    std::cout << "===========================================\n\n";
    std::cout << "1. Quan ly nha kho\n";
    std::cout << "2. Quan ly hop dong\n";
    std::cout << "3. Quan ly bien ban nhap kho\n";
    std::cout << "4. Quan ly bien ban xuat kho\n";
    std::cout << "0. Thoat chuong trinh\n\n";
    std::cout << "Nhap lua chon cua ban: ";
}

void displayNhaKhoMenu() {
    clearScreen();
    std::cout << "===========================================\n";
    std::cout << "     QUAN LY NHA KHO\n";
    std::cout << "===========================================\n\n";
    std::cout << "1. Xoa san pham trong nha kho\n";
    std::cout << "2. Sua thong tin san pham trong nha kho\n";
    std::cout << "3. Xem danh sach san pham trong kho\n";
    std::cout << "4. Sap xep nha kho theo so luong tang dan\n";
    std::cout << "5. Tim kiem san pham theo ma\n";
    std::cout << "6. Tim kiem san pham theo ten\n";
    std::cout << "7. Kiem tra thoi han cua san pham\n";
    std::cout << "8. Xuat du lieu ra file\n";
    std::cout << "0. Quay lai\n\n";
    std::cout << "Nhap lua chon cua ban: ";
}

void displayHopDongMenu() {
    clearScreen();
    std::cout << "===========================================\n";
    std::cout << "     QUAN LY HOP DONG\n";
    std::cout << "===========================================\n\n";
    std::cout << "1. Them hop dong\n";
    std::cout << "2. Xem danh sach hop dong\n";
    std::cout << "3. Sap xep danh sach hop dong\n";
    std::cout << "4. Tim kiem hop dong theo ma hop dong\n";
    std::cout << "5. Tim kiem hop dong theo ten nha cung cap\n";
    std::cout << "6. Sua hop dong\n";
    std::cout << "7. Xoa hop dong\n";
    std::cout << "8. Xuat du lieu ra file\n";
    std::cout << "0. Quay lai\n\n";
    std::cout << "Nhap lua chon cua ban: ";
}

void displayBienBanNhapKhoMenu() {
    clearScreen();
    std::cout << "===========================================\n";
    std::cout << "     QUAN LY BIEN BAN NHAP KHO\n";
    std::cout << "===========================================\n\n";
    std::cout << "1. Tao bien ban nhap kho\n";
    std::cout << "2. Hien thi danh sach bien ban nhap kho\n";
    std::cout << "3. Xoa bien ban nhap kho\n";
    std::cout << "0. Quay lai\n\n";
    std::cout << "Nhap lua chon cua ban: ";
}

void displayBienBanXuatKhoMenu() {
    clearScreen();
    std::cout << "===========================================\n";
    std::cout << "     QUAN LY BIEN BAN XUAT KHO\n";
    std::cout << "===========================================\n\n";
    std::cout << "1. Them bien ban xuat kho\n";
    std::cout << "2. Hien thi danh sach bien ban xuat kho\n";
    std::cout << "2. Xoa bien ban xuat kho\n";
    std::cout << "0. Quay lai\n\n";
    std::cout << "Nhap lua chon cua ban: ";
}
template <class T>
struct ListInterface {
    virtual void load() = 0;
    virtual void luu(string) = 0;
    virtual void them() = 0;
    virtual void hienThi() = 0;
    virtual void xoa() = 0;
    virtual void sua() = 0;
    virtual void xuatFile(string) = 0;
    virtual void sapXep() = 0;
    virtual T* timKiem(string) = 0;
    virtual T* timKiem() = 0;
};

struct ObjectInterface {
    virtual void luu(ofstream&) = 0;
    virtual void nhap() = 0;
    virtual void hienThi() = 0;
    virtual bool kiemTraThoiHan() = 0;
    virtual void nhapFile(ifstream&) = 0;
    virtual void xuatFile(ofstream&) = 0;
};

#endif