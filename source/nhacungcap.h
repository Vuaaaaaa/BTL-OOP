#ifndef NHACUNGCAP_H
#define NHACUNGCAP_H
#include "sanpham.h"
#include <iostream>
#include <math.h>
#include <vector>
using namespace std;

class NhaCungCap{
    protected:
        string maNhaCungCap;
        string tenNhaCungCap;
        string thongTinLienHe;
        vector<SanPham> sanPhamCungCap;
    public:
        NhaCungCap(): tenNhaCungCap {"Unknown"}, thongTinLienHe {"Unknown"} {};
        NhaCungCap(string s1, string s2, string s3, vector<SanPham>& v) {
            maNhaCungCap = s1;
            tenNhaCungCap = s2;
            thongTinLienHe = s3;
            sanPhamCungCap = v;
        }
        void setTen(string_view s) {
            if (!s.empty()) {
                tenNhaCungCap = s;
            } else {
                cout << "set ten loi!\n";
            }
        }
        void setThongTin(string_view s) {
            if (!s.empty()) {
                thongTinLienHe = s;
            } else {
                cout << "set thong tin loi!\n";
            }
        }
        string getMa() { return maNhaCungCap; }
        void setMa(string_view m) { 
            if (checkMa(m, 5)) {
                maNhaCungCap = m;
            } else {
                cout << "set ma loi!\n";
            }
        }
        string getTen() {
            return tenNhaCungCap;
        }
        string getThongTin() {
            return thongTinLienHe;
        }
        vector<SanPham>& getSanPham() {
            return sanPhamCungCap;
        }
        NhaCungCap& operator=(NhaCungCap other) {
            maNhaCungCap = other.maNhaCungCap;
            tenNhaCungCap = other.tenNhaCungCap;
            thongTinLienHe = other.thongTinLienHe;
            sanPhamCungCap = other.sanPhamCungCap;
            return *this;
        }
        bool operator==(NhaCungCap& another) {
            return (maNhaCungCap == another.maNhaCungCap) 
            && (tenNhaCungCap == another.tenNhaCungCap) 
            && (thongTinLienHe == another.thongTinLienHe);
        }

        virtual void nhap();
        virtual void hienThi();
};

void NhaCungCap::nhap() {
    do {
        cout << "Nhap ma nha cung cap: ";
        getline(cin, maNhaCungCap);
        cout << "Nhap ten nha cung cap: ";
        getline(cin, tenNhaCungCap);
        cout << "Nhap thong tin lien he: ";
        getline(cin, thongTinLienHe);
        cout << "Nhap so san pham cung cap: ";
        int n;
        cin >> n;
        cin.ignore(100, '\n');
        for (int i = 0; i < n; i++) {
            SanPham x;
            x.nhap();
            sanPhamCungCap.push_back(x);
            if (sanPhamCungCap.size() == 1) {
                string tmp = "SP" + string(1, maNhaCungCap[0]) + string(1, maNhaCungCap[1]) + "00" + to_string(1);
                sanPhamCungCap[i].setMa(tmp);
            } else {
                int tmp = (sanPhamCungCap[i-1].getMa()[4] - '0')*100 + 
                        (sanPhamCungCap[i-1].getMa()[5] - '0')*10 +
                        (sanPhamCungCap[i-1].getMa()[6] - '0');
                int ma = max((int)sanPhamCungCap.size(), tmp+1);
                string tmp1 = "SP" + string(1, maNhaCungCap[0]) + string(1, maNhaCungCap[1]);
                tmp1 += ma < 10 ? "00" : (ma < 100 ? "0" : "");
                sanPhamCungCap[i].setMa(tmp1 + to_string(ma));
            }
        }
        if (!checkMa(maNhaCungCap, 5) || tenNhaCungCap.empty() || thongTinLienHe.empty()) {
            cout << "Nhap lai\n";
        }
    } while (!checkMa(maNhaCungCap, 5) || tenNhaCungCap.empty() || thongTinLienHe.empty());
}

void NhaCungCap::hienThi() {
    cout << "Ma nha cung cap: " << maNhaCungCap << "\n";
    cout << "Ten nha cung cap: " << tenNhaCungCap << "\n";
    cout << "Thong tin lien he: " << thongTinLienHe << "\n";
    cout << "Danh sach san pham cung cap:\n";
    for (auto& i : sanPhamCungCap) {
        i.hienThi();
    }
}
#endif