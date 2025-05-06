#ifndef NHAKHO_H
#define NHAKHO_H
#include "sanpham.h"
#include <vector>
#include <iostream>
using namespace std;

class NhaKho : public ListInterface<pair<int, SanPham>> {
    private:
        vector<pair<int, SanPham>> sp;
    public:
        NhaKho() {
            sp = vector<pair<int, SanPham>>();
        }
        NhaKho(vector<pair<int, SanPham>>& ds) {
            sp = ds;
        }
        NhaKho(NhaKho& ds) {
            sp = ds.sp;
        }
        vector<pair<int, SanPham>>& getDS() {
            return sp;
        }
        void load() override;
        void them() override;
        pair<int, SanPham> them(SanPham&);
        void hienThi() override;
        void xuatFile(string) override;
        void xoa() override;
        void sua() override; 
        void luu(string) override;
        void sapXep() override;
        void KtThoiHan();
        pair<int, SanPham>* timKiem(string ten) override;
        pair<int, SanPham>* timKiem() override;
};

void NhaKho::luu(string s = "../data/sanpham.txt") {
    ofstream outf{s, ios::trunc};
    if(!outf) {
        cerr << "Loi mo file\n";
        return;
    }
    outf << sp.size() << "\n";
    for (pair<int, SanPham>& p : sp) {
        outf << p.first << "\n";
        p.second.luu(outf);
    }
}

void NhaKho::xuatFile(string file) {
    string s = "../out/";
    file = s + file;
    ofstream outf{file};
    if(!outf) {
        cerr << "Loi mo file\n";
        return;
    }
    for (auto p : sp) {
        p.second.xuatFile(outf);
        outf << "So luong san pham: " << p.first << "\n";
        if (p.second.kiemTraThoiHan()) {
            outf << "San pham con han\n";
        } else {
            outf << "San pham het han\n";
        }
    }
}

void NhaKho::them() {
    cout << "Nhap so san pham can them: ";
    int n;
    cin >> n;
    cin.ignore(100, '\n');
    while (n--) {
        SanPham SP;
        SP.nhap();
        int soLuong;
        cout << "Nhap so luong: ";
        cin >> soLuong;
        cin.ignore();
        pair<int, SanPham>* p = timKiem(SP.getMa());
        if (p) {
            p->first += soLuong;
            cout << "Da them so luong\n";
        } else {
            sp.push_back(make_pair(soLuong, SP));
            cout << "Da them san pham vao kho" << endl;
        }
    }
}

pair<int, SanPham> NhaKho::them(SanPham& SP) {
    pair<int, SanPham>* p = timKiem(SP.getMa());
    cout << "Thong tin san pham: \n";
    SP.hienThi();
    int soLuong;
    cout << "Nhap so luong: ";
    cin >> soLuong;
    if (p) {
        p->first += soLuong;
        cout << "Da them so luong\n";
    } else {
        sp.push_back(make_pair(soLuong, SP));
        cout << "Da them san pham vao kho\n";
        cin.ignore();
    }
    return {soLuong, SP};
}

void NhaKho::load() {
    ifstream inf{"../data/sanpham.txt"};
    if (!inf) {
        cerr << "Loi mo file\n";
        return;
    }
    string s;
    getline(inf, s);
    int n = stoi(s);
    while (n--) {
        getline(inf, s);
        int soLuong = stoi(s);
        SanPham SP;
        SP.nhapFile(inf);
        sp.push_back(make_pair(soLuong, SP));
    }
    inf.close();
}

void NhaKho::hienThi() {
    for(auto x: sp) {
        cout << "So luong: " << x.first << endl;
        x.second.hienThi();
    }
}

void NhaKho::xoa() {
    string ma;
    cin.ignore(100, '\n');
    cout << "Nhap ma san pham can xoa: ";
    getline(cin, ma);
    auto it = remove_if(sp.begin(), sp.end(), [&](pair<int, SanPham>& p){
        return p.second.getMa() == ma;
    });
    if(it != sp.end()) {
        sp.erase(it, sp.end());
        cout << "San pham da duoc xoa";
        luu();
    } else {
        cout << "Khong tim thay san pham.\n";
    }
    luu();
}
void NhaKho::sua() {
    string ma;
    cin.ignore(100, '\n');
    cout << "Nhap ma san pham can sua: ";
    getline(cin, ma);
    pair<int, SanPham>* it = timKiem(ma);
    if(it) {
        cout << "Nhap thong tin moi cho san pham: \n";
        cout << "Nhap so luong: ";
        cin >> it->first;
        it->second.nhap();
        luu();
    } else {
        cout << "Khong tin thay ma san pham can sua\n";
    }
}

void NhaKho::sapXep() {
    NhaKho tmp = sp;
    sort(tmp.getDS().begin(), tmp.getDS().end(), [](pair<int, SanPham>& a, pair<int, SanPham>& b){
        return a.first < b.first;
    });
    int m;
    do {
        cout << "Sap xep theo so luong san pham tang dan\n";
        cout << "1. Hien thi\n";
        cout << "2. Xuat file\n";
        cout << "3. exit\n";
        cout << "Nhap lua chon: ";
        cin >> m;   
        switch (m) {
            case 1:
                cout << "Danh sach hop dong sau khi sap xep:\n";
                tmp.hienThi();
                break;
            case 2:
                cout << "Nhap ten file muon luu: ";
                {
                    string file;
                    cin >> file;
                    tmp.xuatFile(file);
                }
                break;
            case 3:
                cout << "exit\n";
                break;
            default:
                cout << "Lua chon khong hop le\n";
        }
    } while (m < 3);
}

pair<int, SanPham>* NhaKho::timKiem(string ma) {
    for(auto &x: sp) {
        if(x.second.getMa() == ma) {
            return &x;
        }
    }
    return nullptr;
}
pair<int, SanPham>* NhaKho::timKiem() {
    string ten;
    cin.ignore(100, '\n');
    cout << "Nhap ten san pham can tim: ";
    getline(cin, ten);
    if(ten.empty()) {
        cout << "Ten san pham khong duoc de trong\n";
        return nullptr;
    }
    for(auto &x: sp) {
        if(compare(x.second.getTen(), ten)) {
            return &x;
        }
    }
    return nullptr;
}

void NhaKho::KtThoiHan() {
    cout << "Danh sach san pham con han: \n";
    for(auto x: sp) {
        if(x.second.kiemTraThoiHan()) {
            x.second.hienThi();
        }
    }
}

#endif