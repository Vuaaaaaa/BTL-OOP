#include "danhsachhopdong.h"
#include "dsbienbannhapkho.h"
#include "dsbienbanxuatkho.h"
#include "interface.h"
#include "nhacungcap.h"
#include "nhakho.h"
#include "sanpham.h"
#include <iostream>
using namespace std;

#ifndef APP_H
#define APP_H

class App {
    private:
        int choice; 
        bool running = true;
        NhaKho nk;
        NhaCungCap ncc;
        DanhSachHopDong ds;
        DsBienBanXuatKho dsBienBanXuatKho;
        DsBienBanNhapKho dsBienBanNhapKho;
    public:
        App() {
            while (running) {
                ds.load();
                dsBienBanNhapKho.load();
                dsBienBanXuatKho.load();
                displayMainMenu();
                cin >> choice;
                switch (choice) {
                case 1: {
                int nhaKhoChoice;
                do {
                    clearScreen();
                    displayNhaKhoMenu();
                    cin >> nhaKhoChoice;
                    switch (nhaKhoChoice) {
                    case 1:
                    nk.xoa();
                    break;
                    case 2:
                    nk.sua();
                    break;
                    case 3: 
                    nk.hienThi();
                    cout << "Nhan nut enter de tiep tuc...";
                    cin.ignore();
                    cin.get();
                    clearScreen();
                    break;
                    case 4:
                    nk.sapXep();
                    break;
                    case 5: {
                    string ma;
                    cin.ignore(100, '\n');
                    cout << "Nhap ma san pham can tim: ";
                    getline(cin, ma);
                    pair<int, SanPham>* p = nk.timKiem(ma);
                    if(p == nullptr) {
                        cout << "Khong co san pham can tim kiem" << endl;
                    } else {
                        cout << p->first << "\n";
                        p->second.hienThi();
                    }
                    cout << "Nhap nut enter de tiep tuc...";
                    cin.get();
                    clearScreen();
                    break;
                    }
                    case 6: {
                    pair<int, SanPham>* p = nk.timKiem();
                    if(p == nullptr) {
                        cout << "Khong co san pham can tim kiem" << endl;
                    } else {
                        cout << p->first << "\n";
                        p->second.hienThi();
                    }
                    cout << "Nhap nut enter de tiep tuc...";
                    cin.get();
                    clearScreen();
                    break;
                    }
                    case 7: 
                    nk.KtThoiHan();
                    break;
                    case 8:
                    if(nk.getDS().empty()) {
                        cout << "Khong co san pham nao de xuat\n";
                    } else {
                        nk.xuatFile("../out/sanpham.txt");
                        cout << "Xuat file thanh cong\n";
                    }
                    cout << "Nhap enter de tiep tuc...";
                    cin.ignore();
                    cin.get();
                    break;
                    }
                } while (nhaKhoChoice != 0);
                } break;
                case 2: {
                int hopDongChoice;
                do {
                    clearScreen();
                    displayHopDongMenu();
                    cin >> hopDongChoice;
                    switch (hopDongChoice) {
                    case 1:
                    ds.them();
                    break;
                    case 2:
                    ds.hienThi();
                    cout << "Nhap enter de tiep tuc...";
                    cin.ignore();
                    cin.get();
                    clearScreen();
                    break;
                    case 3:
                    ds.sapXep();
                    break;
                    case 4: {
                    string ma;
                    cin.ignore(100, '\n');
                    cout << "Nhap ma hop dong can tim: ";
                    getline(cin, ma);
                    HopDong *p = ds.timKiem(ma);
                    if(p != nullptr) {
                        p->hienThi();
                    } else {
                        cout << "Khong co ma hop dong can tim\n";
                    }
                    cout << "Nhap enter de tiep tuc...";
                    cin.ignore();
                    cin.get();
                    clearScreen();
                    break;
                    }
                    case 5: {
                    cin.ignore();
                    HopDong *q = ds.timKiem();
                    if(q != nullptr) {
                        q->hienThi();
                    } else {
                        cout << "Khong co ma hop dong can tim\n";
                    }
                    cout << "Nhap enter de tiep tuc...";
                    cin.get();
                    clearScreen();
                    break;
                    }
                    case 6:
                    ds.sua();
                    break;
                    case 7:
                    ds.xoa();
                    break;
                    case 8:
                    if(ds.getDS().empty()) {
                        ds.load();
                        ds.luu("../out/hopdong.txt");
                    } else {
                        ds.luu("../out/hopdong.txt");
                    }
                    cout << "Luu thanh cong";
                    cin.ignore();
                    cin.get();
                    break;
                    }
                } while (hopDongChoice != 0);
                } break;
                case 3: {
                int bienBanNhapKhoChoice;
                do {
                    displayBienBanNhapKhoMenu();
                    cin >> bienBanNhapKhoChoice;
                    switch (bienBanNhapKhoChoice) {
                    case 1:
                    dsBienBanNhapKho.them(ds, nk);
                    dsBienBanNhapKho.luu();
                    cin.get();
                    break;
                    case 2:
                    dsBienBanNhapKho.hienThi();
                    cout << "Nhap enter de tiep tuc...";
                    cin.ignore();
                    cin.get();
                    break;
                    case 3:
                    dsBienBanNhapKho.xoa();
                    break;
                    }
                } while (bienBanNhapKhoChoice != 0);
                } break;
                case 4: {
                int bienBanXuatKhoChoice;
                do {
                    clearScreen();
                    displayBienBanXuatKhoMenu();
                    cin >> bienBanXuatKhoChoice;
                    switch (bienBanXuatKhoChoice) {
                    case 1:
                    dsBienBanXuatKho.them(nk);
                    dsBienBanXuatKho.luu();
                    case 2:
                    dsBienBanXuatKho.hienThi();
                    cout << "Nhap enter de tiep tuc...";
                    cin.ignore();
                    cin.get();
                    break;
                    case 3:
                    cin.ignore();
                    dsBienBanXuatKho.xoa();
                    break;
                    }
                } while (bienBanXuatKhoChoice != 0);
                } break;
                case 0:
                clearScreen();
                cout << "Cam on ban da su dung chuong trinh!\n";
                running = false;
                break;
                default:
                clearScreen();
                cout << "Lua chon khong hop le. Vui long thu lai!\n";
                cout << "Nhan phim bat ky de tiep tuc...";
                cin.ignore();
                cin.get();
                break;
                }
            }
        }
};

#endif