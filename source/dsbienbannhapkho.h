#ifndef DSBIENBANNHAPKHO_H
#define DSBIENBANNHAPKHO_H
#include "bienbannhapkho.h"
#include <iostream>
using namespace std;

class DsBienBanNhapKho {
    private:
        vector<BienBanNhapKho> dsBienBanNhapKho;
    public:
        DsBienBanNhapKho() = default;
        void load() {
            ifstream inf{"../data/bienbannhapkho.txt"};
            if (!inf) {
                cerr << "Loi mo file\n";
                return;
            }
            string s;
            getline(inf, s);
            int n = stoi(s);
            for (int i = 0; i < n; i++) {
                BienBanNhapKho bb;
                bb.loadBaoCao(inf);
                dsBienBanNhapKho.push_back(bb);
            }
        }
        void luu() {
            ofstream outf{"../data/bienbannhapkho.txt", ios::app};
            if (!outf) {
                cerr << "Loi mo file\n";
                return;
            }
            outf << dsBienBanNhapKho.size() << "\n";
            for (auto& bb : dsBienBanNhapKho) {
                bb.luuBaoCao(outf);
            }
        }
        void them(DanhSachHopDong & dsHopDong, NhaKho& nhaKho) {
            cout << "So bien ban nhap kho muon them: ";
            int n;
            cin >> n;
            cin.ignore(100, '\n');
            if (n < 0) {
                cout << "Nhap so bien ban nhap kho khong hop le\n";
                return;
            }
            while (n--) {
                BienBanNhapKho bb;
                bb.nhapBaoCao(dsHopDong, nhaKho);
                dsBienBanNhapKho.push_back(bb);
            }
        }
        void hienThi() {
            cout << "Danh sach bien ban nhap kho:\n";
            for (auto& bb : dsBienBanNhapKho) {
                bb.hienThiBaoCao();
            }
        }
        void xoa() {
            cout << "Nhap ten nha cung cap muon xoa: ";
            string ten;
            getline(cin, ten);
            if (ten.empty()) {
                cout << "Ten nha cung cap khong duoc de trong\n";
                return;
            }
            dsBienBanNhapKho.erase(find_if(dsBienBanNhapKho.begin(), dsBienBanNhapKho.end(), [&](BienBanNhapKho& bb) {
                return compare(bb.getTenNhaCungCap(), ten);
            }));
            ofstream outf{"../data/bienbannhapkho.txt", ios::trunc};
            if (!outf) {
                cerr << "Loi mo file\n";
                return;
            }
            outf << dsBienBanNhapKho.size() << "\n";
            for (auto& bb : dsBienBanNhapKho) {
                bb.luuBaoCao(outf);
            }
        }
};


#endif