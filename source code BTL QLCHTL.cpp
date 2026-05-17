#include <iostream>
#include <vector>
#include <limits>
#include <string>
#include <fstream>
#include <iomanip>
#include <map>
#include <algorithm>
#include <memory>
using namespace std;

//CLASS

class SanPham {
protected:
    string maSP;
    string tenSP;
    double gia;
    int soLuong;

public:
    SanPham() {
        maSP = "";
        tenSP = "";
        gia = 0;
        soLuong = 0;
    }

    SanPham(string ma, string ten, double g, int sl) {
        maSP = ma;
        tenSP = ten;
        gia = g;
        soLuong = sl;
    }

    virtual ~SanPham() {}

    virtual void nhap() {
        cin.ignore();

        cout << "Nhap ma san pham: ";
        getline(cin, maSP);

        cout << "Nhap ten san pham: ";
        getline(cin, tenSP);

        cout << "Nhap gia: ";
        cin >> gia;

        if (gia < 0)
            throw invalid_argument("Gia khong hop le!");

        cout << "Nhap so luong: ";
        cin >> soLuong;

        if (soLuong < 0)
            throw invalid_argument("So luong khong hop le!");
    }

    virtual void xuat() const = 0;

    virtual string loai() const = 0;

    string getMa() const {
        return maSP;
    }

    string getTen() const {
        return tenSP;
    }

    double getGia() const {
        return gia;
    }

    int getSoLuong() const {
        return soLuong;
    }

    void setSoLuong(int sl) {
        soLuong = sl;
    }

    virtual string toCSV() const {
        return maSP + "," + tenSP + "," +
               to_string(gia) + "," +
               to_string(soLuong) + "," + loai();
    }
};

// DO UONG
class DoUong : public SanPham {
private:
    double dungTich;

public:
    DoUong() : SanPham() {
        dungTich = 0;
    }

    void nhap() override {
        SanPham::nhap();

        cout << "Nhap dung tich: ";
        cin >> dungTich;
    }

    void xuat() const override {
        cout << left
             << setw(10) << maSP
             << setw(20) << tenSP
             << setw(10) << gia
             << setw(10) << soLuong
             << setw(10) << dungTich
             << setw(15) << "Do Uong"
             << endl;
    }

    string loai() const override {
        return "DoUong";
    }
};

// BANH KEO

class BanhKeo : public SanPham {
private:
    int calories;

public:
    BanhKeo() : SanPham() {
        calories = 0;
    }

    void nhap() override {
        SanPham::nhap();

        cout << "Nhap calories: ";
        cin >> calories;
    }

    void xuat() const override {
        cout << left
             << setw(10) << maSP
             << setw(20) << tenSP
             << setw(10) << gia
             << setw(10) << soLuong
             << setw(10) << calories
             << setw(15) << "Banh Keo"
             << endl;
    }

    string loai() const override {
        return "BanhKeo";
    }
};

// GIA DUNG

class GiaDung : public SanPham {
private:
    int baoHanh;

public:
    GiaDung() : SanPham() {
        baoHanh = 0;
    }

    void nhap() override {
        SanPham::nhap();

        cout << "Nhap bao hanh(thang): ";
        cin >> baoHanh;
    }

    void xuat() const override {
        cout << left
             << setw(10) << maSP
             << setw(20) << tenSP
             << setw(10) << gia
             << setw(10) << soLuong
             << setw(10) << baoHanh
             << setw(15) << "Gia Dung"
             << endl;
    }

    string loai() const override {
        return "GiaDung";
    }
};

// NHAN VIEN

class NhanVien {
private:
    string maNV;
    string tenNV;
    double luong;

public:
    NhanVien() {
        maNV = "";
        tenNV = "";
        luong = 0;
    }

    void nhap() {
        cin.ignore();

        cout << "Nhap ma nhan vien: ";
        getline(cin, maNV);

        cout << "Nhap ten nhan vien: ";
        getline(cin, tenNV);

        cout << "Nhap luong: ";
        cin >> luong;
    }

    void xuat() const {
        cout << left
             << setw(15) << maNV
             << setw(25) << tenNV
             << setw(15) << luong
             << endl;
    }
};

// KHACH HANG

class KhachHang {
private:
    string maKH;
    string tenKH;
    int diem;

public:
    KhachHang() {
        maKH = "";
        tenKH = "";
        diem = 0;
    }

    void nhap() {
        cin.ignore();

        cout << "Nhap ma khach hang: ";
        getline(cin, maKH);

        cout << "Nhap ten khach hang: ";
        getline(cin, tenKH);

        cout << "Nhap diem tich luy: ";
        cin >> diem;
    }

    void xuat() const {
        cout << left
             << setw(15) << maKH
             << setw(25) << tenKH
             << setw(15) << diem
             << endl;
    }
};

// HOA DON

class HoaDon {
private:
    string maHD;
    vector<pair<string, int>> dsMua;
    double tongTien;

public:
    void nhap() {
        cin.ignore();
        cout << "Nhap ma hoa don: ";
        getline(cin, maHD);

        if (maHD.empty()) maHD = "Unknown"; // Tránh mã trống

        int n;
        cout << "Nhap so san pham mua: ";
        cin >> n;

        for (int i = 0; i < n; i++) {
            string ma;
            int sl;
            cout << "Ma san pham " << i + 1 << ": ";
            cin >> ma;
            cout << "So luong: ";
            cin >> sl;
            dsMua.push_back({ma, sl});
        }
    }

    bool tinhTien(map<string, double> bangGia) {
        if (dsMua.empty()) return false; 
        tongTien = 0;
        for (auto x : dsMua) {
            if (bangGia.find(x.first) == bangGia.end()) {
                cout << "Loi: Ma SP " << x.first << " khong ton tai!\n";
                return false; 
            }
            tongTien += bangGia[x.first] * x.second;
        }
        return true;
    }
    void xuat() const  {
        cout << "\n========= HOA DON =========\n";

        cout << "Ma hoa don: " << maHD << endl;

        for (auto &x : dsMua) {
            cout << "San pham: " << x.first
                 << " | So luong: " << x.second
                 << endl;
        }

        cout << "Tong tien: " << tongTien << endl;
    }
};

// TEMPLATE CLASS

template <class T>
class QuanLyDanhSach {
private:
    vector<T> ds;

public:
    void them(const T &x) {
        ds.push_back(x);
    }

    void hienThi() const {
        for (auto x : ds) {
            x.xuat();
        }
    }

    int size() const {
        return ds.size();
    }
};

// QUAN LY CUA HANG

class QuanLyCuaHang {
private:
    vector<shared_ptr<SanPham>> dsSP;
    vector<NhanVien> dsNV;
    vector<KhachHang> dsKH;
    vector<HoaDon> dsHD;

public:
    // THEM SAN PHAM

    void themSanPham() {
        int chon;

        cout << "\n1. Do Uong";
        cout << "\n2. Banh Keo";
        cout << "\n3. Gia Dung";
        cout << "\nChon loai: ";
        cin >> chon;

        shared_ptr<SanPham> sp;

        try {
            if (chon == 1)
                sp = make_shared<DoUong>();
            else if (chon == 2)
                sp = make_shared<BanhKeo>();
            else if (chon == 3)
                sp = make_shared<GiaDung>();
            else {
                cout << "Lua chon khong hop le!\n";
                return;
            }

            sp->nhap();
            dsSP.push_back(sp);

            cout << "Them san pham thanh cong!\n";
        }
        catch (exception &e) {
            cout << "Loi: " << e.what() << endl;
        }
    }


    // HIEN THI SAN PHAM
  
    void hienThiSP() {
        cout << "\n================ DANH SACH SAN PHAM ================\n";

        cout << left
             << setw(10) << "Ma"
             << setw(20) << "Ten"
             << setw(10) << "Gia"
             << setw(10) << "SL"
             << setw(10) << "ThongSo"
             << setw(15) << "Loai"
             << endl;

        for (auto sp : dsSP) {
            sp->xuat();
        }
    }

 
    // TIM KIEM SAN PHAM

    void timKiemSP() {
        string ma;

        cin.ignore();

        cout << "Nhap ma can tim: ";
        getline(cin, ma);

        bool found = false;

        for (auto sp : dsSP) {
            if (sp->getMa() == ma) {
                sp->xuat();
                found = true;
            }
        }

        if (!found)
            cout << "Khong tim thay!\n";
    }

    // XOA SAN PHAM

    void xoaSP() {
        string ma;

        cin.ignore();

        cout << "Nhap ma san pham can xoa: ";
        getline(cin, ma);

        for (int i = 0; i < dsSP.size(); i++) {
            if (dsSP[i]->getMa() == ma) {
                dsSP.erase(dsSP.begin() + i);
                cout << "Xoa thanh cong!\n";
                return;
            }
        }

        cout << "Khong tim thay san pham!\n";
    }

    // CAP NHAT SO LUONG

    void capNhatSL() {
        string ma;
        int sl;

        cin.ignore();

        cout << "Nhap ma san pham: ";
        getline(cin, ma);

        cout << "Nhap so luong moi: ";
        cin >> sl;

        for (auto sp : dsSP) {
            if (sp->getMa() == ma) {
                sp->setSoLuong(sl);
                cout << "Cap nhat thanh cong!\n";
                return;
            }
        }

        cout << "Khong tim thay san pham!\n";
    }

    // SAP XEP GIA

    void sapXepGiaTang() {
        sort(dsSP.begin(), dsSP.end(),
             [](shared_ptr<SanPham> a, shared_ptr<SanPham> b) {
                 return a->getGia() < b->getGia();
             });

        cout << "Sap xep thanh cong!\n";
    }

    // THEM NHAN VIEN

    void themNhanVien() {
        NhanVien nv;
        nv.nhap();
        dsNV.push_back(nv);

        cout << "Them nhan vien thanh cong!\n";
    }

    // HIEN THI NHAN VIEN

    void hienThiNV() {
        cout << "\n=========== DANH SACH NHAN VIEN ===========\n";

        cout << left
             << setw(15) << "Ma"
             << setw(25) << "Ten"
             << setw(15) << "Luong"
             << endl;

        for (auto nv : dsNV) {
            nv.xuat();
        }
    }

    // THEM KHACH HANG

    void themKH() {
        KhachHang kh;
        kh.nhap();
        dsKH.push_back(kh);

        cout << "Them khach hang thanh cong!\n";
    }

    // HIEN THI KHACH HANG

    void hienThiKH() {
        cout << "\n=========== DANH SACH KHACH HANG ===========\n";

        cout << left
             << setw(15) << "Ma"
             << setw(25) << "Ten"
             << setw(15) << "Diem"
             << endl;

        for (auto kh : dsKH) {
            kh.xuat();
        }
    }

    // TAO HOA DON

    void taoHoaDon() {
    if (dsSP.empty()) {
        cout << "Cua hang chua co san pham nao! Khong the tao hoa don.\n";
        return;
    }

    HoaDon hd;
    hd.nhap();

    map<string, double> bangGia;
    for (auto sp : dsSP) {
        bangGia[sp->getMa()] = sp->getGia();
    }

    if (hd.tinhTien(bangGia)) {
        dsHD.push_back(hd);
        cout << "Tao hoa don thanh cong!\n";
    } else {
        cout << "Tao hoa don THAT BAI (do sai ma SP hoac gio hang trong)!\n";
    }
}

    // HIEN THI HOA DON

    void hienThiHD() {

    if(dsHD.empty()) {
        cout << "Chua co hoa don nao!\n";
        return;
    }

    for(auto hd : dsHD) {
        hd.xuat();
    }
}

    // THONG KE DOANH THU

    void thongKe() {
        double tong = 0;

        map<string, int> thongKeLoai;

        for (auto sp : dsSP) {
            thongKeLoai[sp->loai()]++;
        }

        cout << "\n===== THONG KE SAN PHAM =====\n";

        for (auto x : thongKeLoai) {
            cout << x.first << ": " << x.second << endl;
        }

        cout << "Tong san pham: " << dsSP.size() << endl;
        cout << "Tong nhan vien: " << dsNV.size() << endl;
        cout << "Tong khach hang: " << dsKH.size() << endl;
        cout << "Tong hoa don: " << dsHD.size() << endl;
    }

    // LUU FILE

    void luuFileSP() {
        ofstream fout("SanPham.csv");

        for (auto sp : dsSP) {
            fout << sp->toCSV() << endl;
        }

        fout.close();

        cout << "Luu file thanh cong!\n";
    }

    // DOC FILE

    void docFileSP() {
        ifstream fin("SanPham.csv");

        if (!fin) {
            cout << "Khong mo duoc file!\n";
            return;
        }

        string line;

        cout << "\n========= NOI DUNG FILE =========\n";

        while (getline(fin, line)) {
            cout << line << endl;
        }

        fin.close();
    }

    // MENU
    
    void menu() {
        int chon;

        do {
            cout << "\n========================================";
            cout << "\n      QUAN LY CUA HANG TIEN LOI";
            cout << "\n========================================";
            cout << "\n1. Them san pham";
            cout << "\n2. Hien thi san pham";
            cout << "\n3. Tim kiem san pham";
            cout << "\n4. Xoa san pham";
            cout << "\n5. Cap nhat so luong";
            cout << "\n6. Sap xep gia tang dan";
            cout << "\n7. Them nhan vien";
            cout << "\n8. Hien thi nhan vien";
            cout << "\n9. Them khach hang";
            cout << "\n10. Hien thi khach hang";
            cout << "\n11. Tao hoa don";
            cout << "\n12. Hien thi hoa don";
            cout << "\n13. Thong ke";
            cout << "\n14. Luu file CSV";
            cout << "\n15. Doc file CSV";
            cout << "\n0. Thoat";
            cout << "\n========================================";
            cout << "\nNhap lua chon: ";
            cin >> chon;
    if(cin.fail()) {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "Nhap sai!\n";
    continue;
}
            switch (chon) {
            case 1:
                themSanPham();
                break;

            case 2:
                hienThiSP();
                break;

            case 3:
                timKiemSP();
                break;

            case 4:
                xoaSP();
                break;

            case 5:
                capNhatSL();
                break;

            case 6:
                sapXepGiaTang();
                break;

            case 7:
                themNhanVien();
                break;

            case 8:
                hienThiNV();
                break;

            case 9:
                themKH();
                break;

            case 10:
                hienThiKH();
                break;

            case 11:
                taoHoaDon();
                break;

            case 12:
                hienThiHD();
                break;

            case 13:
                thongKe();
                break;

            case 14:
                luuFileSP();
                break;

            case 15:
                docFileSP();
                break;

            case 0:
                cout << "Thoat chuong trinh!\n";
                break;

            default:
                cout << "Lua chon khong hop le!\n";
            }

        } while (chon != 0);
    }
};

// MAIN

int main() {
    QuanLyCuaHang ql;

    ql.menu();

    return 0;
}
