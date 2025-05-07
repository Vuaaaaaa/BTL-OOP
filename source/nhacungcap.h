#ifndef NHACUNGCAP_H
#define NHACUNGCAP_H
#include "sanpham.h"
#include "nhakho.h"
#include "hopdong.h"
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

        virtual void nhap(string maHD = "");
        virtual void hienThi();
};

void NhaCungCap::nhap(string maHD) {
    bool valid;
    do {
        valid = true;
        cout << "Nhap ma nha cung cap: ";
        getline(cin, maNhaCungCap);
        if (!checkMa(maNhaCungCap, 5)) {
            cout << "Ma nha cung cap khong hop le!\n";
            valid = false;
            continue;
        }
        cout << "Nhap ten nha cung cap: ";
        getline(cin, tenNhaCungCap);
        if (tenNhaCungCap.empty()) {
            cout << "Ten nha cung cap khong duoc de trong!\n";
            valid = false;
            continue;
        }
        cout << "Nhap thong tin lien he: ";
        getline(cin, thongTinLienHe);
        if (thongTinLienHe.empty()) {
            cout << "Thong tin lien he khong duoc de trong!\n";
            valid = false;
            continue;
        }
        if(!valid) {
            cout << "Nhap lai\n";
            cin.ignore();
        }
    } while (!valid);
    cout << "Nhap so san pham cung cap: ";
    int n;
    cin >> n;
    cin.ignore(100, '\n');
    for (int i = 0; i < n; i++) {
        SanPham x;
        x.nhap();
        sanPhamCungCap.push_back(x);
        string maSuDung = maHD.empty() ? maNhaCungCap : maHD;
        if (sanPhamCungCap.size() == 1) {
            string tmp = "SP" + maSuDung.substr(maSuDung.length() - 3) + "001";
            sanPhamCungCap[i].setMa(tmp);
        } else {
            int tmp = (sanPhamCungCap[i-1].getMa()[5] - '0')*100 + 
                    (sanPhamCungCap[i-1].getMa()[6] - '0')*10 +
                    (sanPhamCungCap[i-1].getMa()[7] - '0');
            int ma = max((int)sanPhamCungCap.size(), tmp+1);
            string tmp1 = "SP" + maSuDung.substr(maSuDung.length() - 3);
            tmp1 += ma < 10 ? "00" : (ma < 100 ? "0" : "");
            sanPhamCungCap[i].setMa(tmp1 + to_string(ma));
        }
    }
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