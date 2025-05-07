#ifndef BIENBANXUATKHO_H
#define BIENBANXUATKHO_H

#include <iostream>
#include <vector>
#include <sstream>
#include "../include/otherstruct.h"
#include "../include/func.h"
#include "nhakho.h"
using namespace std;

class BienBanXuatKho {
    private:
        string nguoiXuatKho;
        string nguoiNhan;
        vector<pair<int, SanPham>> sanphamXuatKho;
    public:
        BienBanXuatKho() {
            nguoiXuatKho = "Unknown";
            nguoiNhan = "Unknown";
        }
        string getNguoiXuatKho() {return nguoiXuatKho;}
        string getNguoiNhan() {return nguoiNhan;}
        vector<pair<int, SanPham>> getSanPhamXuatKho() {return sanphamXuatKho;}
        void nhap(NhaKho&);
        void hienthi();
        void load(ifstream&);
        void luu(ofstream&);
};

void BienBanXuatKho::nhap(NhaKho& nk) {
    cout << "Nhap nguoi xuat kho: ";
    getline(cin, nguoiXuatKho);
    cout << "Nhap nguoi nhan: ";
    getline(cin, nguoiNhan);
    int n;
    cout << "Nhap so san pham muon xuat: ";
    cin >> n;
    if(n > nk.getDS().size() || n <= 0){
        cout << "So san pham muon xuat khong hop le\n";
        return;
    }
    cin.ignore(100, '\n');
    while(n--) {
        string ma;
        int soLuong;
        cout << "Nhap ma san pham muon xuat: ";
        getline(cin, ma);
        pair<int, SanPham>* sp = nk.timKiem(ma);
        if (!sp) {
            cout << "Khong tim thay san pham co ma " << ma << "\n";
            continue;
        }
        cout << "Nhap so luong muon xuat: ";
        cin >> soLuong;
        if(soLuong > sp->first || soLuong <= 0) {
            cout << "So luong khong hop le\n";
            continue;
        }
        sp->first -= soLuong;
        sanphamXuatKho.push_back({soLuong, sp->second});
        if(sp->first == 0) {
            vector<pair<int, SanPham>>& ds = nk.getDS();
            ds.erase(remove_if(ds.begin(), ds.end(), [&](pair<int, SanPham>& p){
                return p.second.getMa() == ma;
            }), ds.end());
        }
        cin.ignore();
    }
    nk.luu();
}

void BienBanXuatKho::hienthi() {
    cout << "Danh sach bien ban xuat kho: \n";
    if(nguoiXuatKho == "Unknown" && nguoiNhan == "Unknown") {
        cout << "Khong ton tai bien ban xuat kho\n";
        return;
    } else {
        cout << "Nguoi xuat kho: " << nguoiXuatKho << "\n";
        cout << "Nguoi nhan: " << nguoiNhan << "\n";
        for(auto& x: sanphamXuatKho) {
            cout << "So luong: " << x.first << "\n";
            x.second.hienThi();
        }
    }
}

void BienBanXuatKho::load(ifstream& inf) {
    if (!inf) {
        cerr << "Loi mo file\n";
        return;
    }
    string line;
    getline(inf, line);
    int n = stoi(line);
    if (n < 0) {
        cerr << "So luong san pham khong hop le\n";
        return;
    }
    getline(inf, nguoiXuatKho);
    getline(inf, nguoiNhan);
    for (int i = 0; i < n; i++) {
        getline(inf, line);
        stringstream ss(line);
        int soLuong;
        ss >> soLuong;
        SanPham sp;
        sp.nhapFile(inf); 
        if (sp.getLoaiHang() < 1 || sp.getLoaiHang() > 6) {
            sp.setLoaiHang(1); 
        }
        sanphamXuatKho.push_back({soLuong, sp});
    }
}

void BienBanXuatKho::luu(ofstream& outf) {
    outf << sanphamXuatKho.size() << endl;
    outf << nguoiXuatKho << endl;
    outf << nguoiNhan << endl;
    for (auto& x : sanphamXuatKho) {
        outf << x.first << endl;
        if (x.second.getLoaiHang() < 1 || x.second.getLoaiHang() > 6) {
            x.second.setLoaiHang(1);
        }
        x.second.luu(outf);
    }
}

#endif
