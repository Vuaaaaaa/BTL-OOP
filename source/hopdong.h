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
    outf << ngayKyHopDong << endl;
    outf << ngayHetHan << endl;
}

void HopDong::nhap() {
    cout << "Nhap ma hop dong: ";
    cin >> maHopDong;
    cin.ignore(100, '\n');
    if (!checkMa(maHopDong, 5)) {
        cout << "Ma hop dong khong hop le!\n";
        return;
    }
    
    NhaCungCap::nhap(maHopDong);
    do {
        cout << "Nhap ngay ky hop dong\n";
        cin >> ngayKyHopDong;
        cout << "Nhap ngay het han\n";
        cin >> ngayHetHan;
        cin.ignore(100, '\n');
        if (ngayKyHopDong >= ngayHetHan || ngayKyHopDong.gNow()) {
            cout << "Ngay khong hop le, vui long nhap lai\n";
        }
    } while (ngayKyHopDong >= ngayHetHan || ngayKyHopDong.gNow());
}

void HopDong::hienThi() {
    cout << "Ma nha cung cap: " << maNhaCungCap << endl;
    cout << "Ten nha cung cap: " << tenNhaCungCap << endl;
    cout << "Thong tin lien he: " << thongTinLienHe << endl;
    cout << "Danh sach san pham cung cap:" << endl;
    if (!sanPhamCungCap.empty()) {
        cout << left << setw(10) << "Ma"
             << left << setw(25) << "LoaiHang"
             << left << setw(15) << "Ten"
             << left << setw(15) << "XuatXu"
             << left << setw(20) << "NgaySX"
             << left << setw(20) << "HanSD" << endl;
        cout << setfill('-') << setw(85) << "" << setfill(' ') << endl;
        for (auto& sp : sanPhamCungCap) {
            cout << left << setw(10) << sp.getMa()
                 << left << setw(25) << loai.at(sp.getLoaiHang())
                 << left << setw(15) << sp.getTen()
                 << left << setw(15) << sp.getXuatXu()
                 << left << setw(20) << sp.getNgaySX().toString()
                 << left << setw(20) << sp.getHsd().toString() << endl;
        }
    }
    cout << "Ma hop dong: " << maHopDong << "\n";
    cout << "Ngay ky hop dong: " << ngayKyHopDong << "\n";
    cout << "Ngay het han: " << ngayHetHan << "\n";
    cout << string(85, '-') << endl;
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