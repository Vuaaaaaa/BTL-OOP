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
        }
        string getNguoiXuatKho() {return nguoiXuatKho;}
        string getNguoiNhan() {return nguoiNhan;}
        vector<pair<int, SanPham>> getSanPhamXuatKho() {return sanphamXuatKho;}
        void nhap(NhaKho&);
        void hienthi();
        void load();
        void luu();
};

void BienBanXuatKho::nhap(NhaKho& nk) {
    cout << "Nhap nguoi xuat kho: ";
    getline(cin, nguoiXuatKho);
    cout << "Nhap nguoi nhan: ";
    getline(cin, nguoiNhan);
    int n;
    cout << "Nhap so san pham muon xuat: ";
    cin >> n;
    if(n > nk.getDS().size()){
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
        Date ngaySX = sp->second.getNgaySX();
        Date hsd = sp->second.getHsd();
        cout << "Nhap so luong muon xuat: ";
        cin >> soLuong;
        if(soLuong > sp->first) {
            cout << "So luong trong kho khong du\n";
            continue;
        }
        if(sp->first == 0) {
            vector<pair<int, SanPham>>& ds = nk.getDS();
            ds.erase(remove_if(ds.begin(), ds.end(), [&](pair<int, SanPham>& p){
                return p.second.getMa() == ma;
            }), ds.end());
        }
        sp->first -= soLuong;
        sanphamXuatKho.push_back({soLuong, sp->second});
        luu();
    }
}

void BienBanXuatKho::hienthi() {
    cout << "Nguoi xuat kho: " << nguoiXuatKho << "\n";
    cout << "Nguoi nhan: " << nguoiNhan << "\n";
    for(auto& x: sanphamXuatKho) {
        cout << "So luong: " << x.first << "\n";
        x.second.hienThi();
    }
}

void BienBanXuatKho::load() {
    ifstream inf("../data/bienbanxuatkho.txt");
    if (!inf) {
        cerr << "Loi mo file\n";
        return;
    }
    getline(inf, nguoiXuatKho);
    getline(inf, nguoiNhan);
    string line;
    getline(inf, line);
    int n = stoi(line);
    for (int i = 0; i < n; i++) {
        string line;
        getline(inf, line);
        stringstream ss(line);
        int soLuong;
        ss >> soLuong;
        SanPham sp;
        sp.nhapFile(inf); 
    }
    inf.close();
}

void BienBanXuatKho::luu() {
    ofstream outf{"../data/bienbanxuatkho.txt"};
    if (!outf) {
        cerr << "Khong mo duoc file de luu!\n";
        return;
    }
    outf << sanphamXuatKho.size() << endl;
    outf << nguoiXuatKho << endl;
    outf << nguoiNhan << endl;
    for (auto& x : sanphamXuatKho) {
        outf << x.first << endl;
        x.second.luu(outf);
    }
}

#endif
