#ifndef DSBIENBANXUATKHO_H
#define DSBIENBANXUATKHO_H
#include "bienbanxuatkho.h"
#include <iostream>
using namespace std;

class DsBienBanXuatKho {
    private:
        vector<BienBanXuatKho> dsBienBanXuatKho;
    public:
        DsBienBanXuatKho() = default;
        void load() {
            ifstream inf{"../data/bienbanxuatkho.txt"};
            if (!inf) {
                cerr << "Loi mo file\n";
                return;
            }
            string s;
            getline(inf, s);
            int n = stoi(s);
            for (int i = 0; i < n; i++) {
                BienBanXuatKho xk;
                xk.load();
                dsBienBanXuatKho.push_back(xk);
            }
        }
        void luu() {
            ofstream outf{"../data/bienbanxuatkho.txt", ios::trunc};
            if (!outf) {
                cerr << "Loi mo file\n";
                return;
            }
            outf << dsBienBanXuatKho.size() << "\n";
            for (auto& xk : dsBienBanXuatKho) {
                xk.luu();
            }
        }
        void them(NhaKho& nhaKho) {
            cout << "So bien ban xuat kho muon them: ";
            int n;
            cin >> n;
            cin.ignore(100, '\n');
            if (n < 0) {
                cout << "Nhap so bien ban xuat kho khong hop le\n";
                return;
            }
            while (n--) {
                BienBanXuatKho xk;
                xk.nhap(nhaKho);
                dsBienBanXuatKho.push_back(xk);
            }
        }
        void hienThi() {
            cout << "Danh sach bien ban nhap kho:\n";
            for (auto& bb : dsBienBanXuatKho) {
                bb.hienthi();
            }
        }
        void xoa() {
            cout << "Nhap ten nguoi xuat kho muon xoa: ";
            string ten;
            getline(cin, ten);
            if (ten.empty()) {
                cout << "Ten nguoi xuat kho khong duoc de trong\n";
                return;
            }
            dsBienBanXuatKho.erase(find_if(dsBienBanXuatKho.begin(), dsBienBanXuatKho.end(), [&](BienBanXuatKho& xk) {
                return compare(xk.getNguoiXuatKho(), ten);
            }));
            ofstream outf{"../data/bienbanxuatkho.txt", ios::trunc};
            if (!outf) {
                cerr << "Loi mo file\n";
                return;
            }
            outf << dsBienBanXuatKho.size() << "\n";
            for (auto& xk : dsBienBanXuatKho) {
                xk.luu();
            }
        }
};


#endif