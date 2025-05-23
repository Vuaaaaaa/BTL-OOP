#ifndef BIENBANNHAPKHO_H
#define BIENBANNHAPKHO_H
#include <iostream>
#include <sstream>
#include "nhakho.h"
#include "danhsachhopdong.h"
#include "hopdong.h"
using namespace std;

class BienBanNhapKho {
    private:
        string tenNhaCungCap;
        vector<pair<int, string>> sanPhamNhapKho;
    public:
        BienBanNhapKho() {
            tenNhaCungCap = "Unknown";
        }
        string getTenNhaCungCap() { return tenNhaCungCap; }
        vector<pair<int, string>> getSanPhamNhapKho() { return sanPhamNhapKho; }
        void nhapBaoCao(DanhSachHopDong&, NhaKho&);
        void hienThiBaoCao();
        void loadBaoCao(ifstream&);
        void luuBaoCao(ofstream&);
};


void BienBanNhapKho::nhapBaoCao(DanhSachHopDong& dsHopDong, NhaKho& nhaKho) {
    HopDong* hopDong = dynamic_cast<HopDong*> (dsHopDong.timKiem());
    if (hopDong) {
        NhaCungCap& nhaCungCap = *(hopDong);
        tenNhaCungCap = hopDong->getTen();
        if (hopDong->kiemTraThoiHan()) {
            for (auto& sp : nhaCungCap.getSanPham()) {
                pair<int, SanPham> tmp = nhaKho.them(sp);
                sanPhamNhapKho.push_back(make_pair(tmp.first, tmp.second.getMa()));
                nhaKho.luu();
            }
        } else {
            cout << "Nha cung cap da het thoi han hop dong!\n";
        }
    } else {
        cout << "Khong tim thay nha cung cap!\n";
    }
}

void BienBanNhapKho::hienThiBaoCao() {  
    if (tenNhaCungCap != "Unknown") {
        cout << "Ten nha cung cap: " << tenNhaCungCap << endl;
        cout << "Danh sach san pham nhap kho: " << endl;
        for (auto& sp : sanPhamNhapKho) {
            cout << "Ma san pham: " << sp.second << ", So luong: " << sp.first << endl;
        }
    } else {
        cout << "Chua co bao cao nhap kho!\n";
        return;
    }
}

void BienBanNhapKho::luuBaoCao(ofstream& outf) {
    outf << tenNhaCungCap << endl;
    outf << sanPhamNhapKho.size() << endl;
    for (auto& sp : sanPhamNhapKho) {
        outf << sp.first << " " << sp.second << endl;
    }
}

void BienBanNhapKho::loadBaoCao(ifstream& inf) {
    getline(inf, tenNhaCungCap);
    string s;
    getline(inf, s);
    int n = stoi(s);
    sanPhamNhapKho.resize(n);
    
    for (int i = 0; i < n; i++) {
        string line;
        getline(inf, line);
        stringstream ss(line);
        int soLuong;
        string maSP;
        ss >> soLuong >> maSP;
        sanPhamNhapKho[i] = {soLuong, maSP};
        SanPham sp; 
        sp.setMa(maSP); 
    }
}


#endif