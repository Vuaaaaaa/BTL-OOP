#ifndef HOPDONG_H
#define HOPDONG_H       
#include "nhacungcap.h"
#include "interface.h"
#include "../include/otherstruct.h"
#include <iostream>
using namespace std;

class HopDong : public NhaCungCap, public ObjectInterface {
    private:
        string maHopDong;
        Date ngayKyHopDong;
        Date ngayHetHan;
    public:
        HopDong() : NhaCungCap() {
            maHopDong = "HD000";
            ngayKyHopDong = Date();
            ngayHetHan = Date();
        }
        HopDong(string s1, string s2, string s3, vector<SanPham>& v, string_view mhd, Date ky, Date het)
            : NhaCungCap(s1, s2, s3, v) {
            if (!mhd.empty() && ngayHetHan >= ngayKyHopDong && checkMa(mhd, 5) && ngayKyHopDong.leNow()) {
                maHopDong = mhd;
                ngayKyHopDong = ky;
                ngayHetHan = het;
            } else {
                cout << "Constructor hop dong loi\n";
            }
        }
        HopDong(NhaCungCap& ncc): NhaCungCap(ncc) {}
        HopDong& operator=(HopDong other) {
            NhaCungCap::operator=(other);
            maHopDong = other.maHopDong;
            ngayKyHopDong = other.ngayKyHopDong;
            ngayHetHan = other.ngayHetHan;
            return *this;
        }
        void setMa(string_view m) { maHopDong = m; }
        string getMa() { return maHopDong; }
        void setNgayKy(Date ky) { 
            if (ngayHetHan > ky && ky.leNow()) {
                ngayKyHopDong = ky;
            } else {
                cout << "ngay ky hop dong khong hop le\n";
            }
        }
        void setNgayHetHan(Date& het) {
            if (het >= ngayKyHopDong) {
                ngayHetHan = het;
            } else {
                cout << "ngay het han khong hop le\n";
            }
        }
        Date getNgayKy() { return ngayKyHopDong; }
        Date getNgayHetHan() { return ngayHetHan; }

        void luu(ofstream&) override;
        void nhap() override;
        void hienThi() override;
        bool kiemTraThoiHan() override;
        void nhapFile(ifstream&) override;
        void xuatFile(ofstream&) override;
};

void HopDong::luu(ofstream& outf) {
    outf << NhaCungCap::maNhaCungCap << endl; 
    outf << NhaCungCap::tenNhaCungCap << endl;
    outf << NhaCungCap::thongTinLienHe << endl;
    outf << NhaCungCap::sanPhamCungCap.size() << endl;
    for (auto& i : NhaCungCap::sanPhamCungCap) {
        i.luu(outf);
    }
    outf << maHopDong << endl;
    outf << ngayKyHopDong << ngayHetHan;
}

void HopDong::nhap() {
    NhaCungCap::nhap();
    do {
        cout << "Nhap ma hop dong: ";
        cin >> maHopDong;
        cout << "Nhap ngay ky hop dong\n";
        cin >> ngayKyHopDong;
        cout << "Nhap ngay het han\n";
        cin >> ngayHetHan;
        cin.ignore(100, '\n');
        if ( ngayKyHopDong > ngayHetHan || !checkMa(maHopDong, 5) || ngayKyHopDong.gNow()) {
            cout << "nhap loi\n";
        }
    } while (ngayKyHopDong > ngayHetHan || !checkMa(maHopDong, 5) || ngayKyHopDong.gNow());
}

void HopDong::hienThi() {
    NhaCungCap::hienThi();
    cout << "Ma hop dong: " << maHopDong << "\n";
    cout << "Ngay ky hop dong: " << ngayKyHopDong;
    cout << "Ngay het han: " << ngayHetHan;
}

void HopDong::xuatFile(ofstream& outf) {
    outf << "Ma nha cung cap: " << NhaCungCap::maNhaCungCap << endl; 
    outf << "Ten nha cung cap: "<< NhaCungCap::tenNhaCungCap << endl;
    outf << "Thong tin lien he: "<< NhaCungCap::thongTinLienHe << endl;
    for (auto& i : NhaCungCap::sanPhamCungCap) {
        i.xuatFile(outf);
    }
    outf << maHopDong << endl;
    outf << ngayKyHopDong << ngayHetHan;
}

void HopDong::nhapFile(ifstream& inf) {
    string s;
    getline(inf, NhaCungCap::maNhaCungCap);
    getline(inf, NhaCungCap::tenNhaCungCap);
    getline(inf, NhaCungCap::thongTinLienHe);
    getline(inf, s);
    int n = stoi(s);
    for (int i = 0; i < n; i++) {
        SanPham sp;
        sp.nhapFile(inf);
        NhaCungCap::sanPhamCungCap.push_back(sp);
    }
    getline(inf, maHopDong);
    getline(inf, s);
    ngayKyHopDong.parseString(s);
    getline(inf, s);    
    ngayHetHan.parseString(s);
}

bool HopDong::kiemTraThoiHan() {
    return ngayHetHan.lNow();
}

#endif