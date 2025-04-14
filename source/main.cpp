#include "danhsachhopdong.h"
#include "dsbienbannhapkho.h"
#include "dsbienbanxuatkho.h"
#include "interface.h"
#include "nhacungcap.h"
#include "nhakho.h"
#include "sanpham.h"
#include <iostream>
#include <string>
using namespace std;
int main() {
  int choice;
  bool running = true;
  NhaKho nk;
  vector<NhaCungCap> danhSachNCC;
  DanhSachHopDong ds;
  DsBienBanXuatKho dsBienBanXuatKho;
  DsBienBanNhapKho dsBienBanNhapKho;
  while (running) {
    displayMainMenu();
    cin >> choice;
    switch (choice) {
    case 1: {
      int nhaKhoChoice;
      do {
        clearScreen();
        displayNhaKhoMenu();
        cin >> nhaKhoChoice;
        switch (nhaKhoChoice) {
        case 1:
          nk.them();
          break;
        case 2:
          nk.xoa();
          break;
        case 3:
          nk.sua();
          break;
        case 4: 
          nk.hienThi();
          cout << "Nhan nut enter de tiep tuc...";
          cin.ignore();
          cin.get();
          clearScreen();
          break;
        case 5:
          nk.sapXep();
          break;
        case 6: {
          string ma;
          cin.ignore(100, '\n');
          cout << "Nhap ma san pham can tim: ";
          getline(cin, ma);
          pair<int, SanPham>* p = nk.timKiem(ma);
          cout << p->first << "\n";
          p->second.hienThi();
          cout << "Nhap nut enter de tiep tuc...";
          cin.get();
          clearScreen();
          break;
        }
        case 7: {
          pair<int, SanPham>* p = nk.timKiem();
          cout << p->first << "\n";
          p->second.hienThi();
          cout << "Nhap nut enter de tiep tuc...";
          cin.get();
          clearScreen();
          break;
        }
        case 8: 
          nk.luu();
          break;
        }
      } while (nhaKhoChoice != 0);
    } break;
    case 2: {
      int sanPhamChoice;
      SanPham sp;
      do {
        clearScreen();
        displaySanPhamMenu();
        cin >> sanPhamChoice;
        switch (sanPhamChoice) {
        case 1:
          cin.ignore();
          sp.nhap();
          break;
        case 2:
          sp.hienThi();
          cout << "Nhap nut enter de tiep tuc...";
          cin.ignore();
          cin.get();
          clearScreen();
          break;
        case 3: {
          bool p = sp.kiemTraThoiHan();
          if(sp.getMa() == "SPCT000") {
            cout << "Van chua nhap san pham\n";
          } else {
            if(p) {
              cout << "San pham van con han" << endl;
            } else {
              cout << "San pham da het han" << endl;
            }
          }
          cin.ignore();
          cin.get();
          clearScreen();
          break;
        }
        case 4: {
          ofstream outf{"../data/sanpham.txt", ios::app};
          if(outf.is_open()) {
            sp.luu(outf);
            outf.close();
          } else {
            cout << "Loi mo file\n";
          }
          break;
        }
        }
      } while (sanPhamChoice != 0);
    } break;
    case 3: {
      int nhaCungCapChoice;
      do {
        clearScreen();
        displayNhaCungCapMenu();
        cin >> nhaCungCapChoice;
        switch (nhaCungCapChoice) {
          case 1: {
            NhaCungCap ncc;
            cin.ignore();
            ncc.nhap();
            danhSachNCC.push_back(ncc);
            break;
        }
        case 2: {
            if (danhSachNCC.empty()) {
                cout << "Danh sach rong!\n";
            } else {
                for (auto& ncc : danhSachNCC) {
                    ncc.hienThi();
                }
            }
            cout << "Nhap enter de tiep tuc...";
            cin.ignore();
            cin.get();
            break;
        }
        }
      } while (nhaCungCapChoice != 0);
    } break;
    case 4: {
      int hopDongChoice;
      do {
        clearScreen();
        displayHopDongMenu();
        cin >> hopDongChoice;
        switch (hopDongChoice) {
        case 1:
          ds.them();
          break;
        case 2:
          ds.hienThi();
          cout << "Nhap enter de tiep tuc...";
          cin.ignore();
          cin.get();
          clearScreen();
          break;
        case 3:
          ds.sapXep();
          break;
        case 4:
          ds.luu();
          break;
        case 5: {
          string ma;
          cin.ignore(100, '\n');
          cout << "Nhap ma san pham can tim: ";
          getline(cin, ma);
          HopDong *p = ds.timKiem(ma);
          p->hienThi();
          cout << "Nhap enter de tiep tuc...";
          cin.ignore();
          cin.get();
          clearScreen();
          break;
        }
        case 6: {
          HopDong *q = ds.timKiem();
          q->hienThi();
          cout << "Nhap enter de tiep tuc...";
          cin.ignore();
          cin.get();
          clearScreen();
          break;
        }
        case 7:
          ds.sua();
          break;
        case 8:
          ds.xoa();
          break;
        }
      } while (hopDongChoice != 0);
    } break;
    case 5: {
      int bienBanNhapKhoChoice;
      do {
        displayBienBanNhapKhoMenu();
        cin >> bienBanNhapKhoChoice;
        switch (bienBanNhapKhoChoice) {
        case 1:
          dsBienBanNhapKho.them(ds, nk);
          break;
        case 2:
          dsBienBanNhapKho.hienThi();
          break;
        case 3:
          dsBienBanNhapKho.xoa();
          break;
        case 4:
          dsBienBanNhapKho.luu();
          break;
        }
      } while (bienBanNhapKhoChoice != 0);
    } break;
    case 6: {
      int bienBanXuatKhoChoice;
      do {
        clearScreen();
        displayBienBanXuatKhoMenu();
        cin >> bienBanXuatKhoChoice;
        switch (bienBanXuatKhoChoice) {
          case 1:
          dsBienBanXuatKho.them(nk);
          break;
        case 2:
          dsBienBanXuatKho.hienThi();
          break;
        case 3:
          dsBienBanXuatKho.xoa();
          break;
        }
      } while (bienBanXuatKhoChoice != 0);
    } break;
    case 0:
      clearScreen();
      cout << "Cam on ban da su dung chuong trinh!\n";
      running = false;
      break;
    default:
      clearScreen();
      cout << "Lua chon khong hop le. Vui long thu lai!\n";
      cout << "Nhan phim bat ky de tiep tuc...";
      cin.ignore();
      cin.get();
      break;
    }
  }
  return 0;
}