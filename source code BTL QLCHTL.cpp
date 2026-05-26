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

// ==================== CLASS SAN PHAM (BASE CLASS) ====================
class SanPham {
protected:
    string maSP;
    string tenSP;
    double gia;
    int soLuong;
    string donViTinh;
    bool daXoa;

public:
    SanPham() {
        maSP = ""; tenSP = ""; gia = 0; soLuong = 0; donViTinh = "Cai"; daXoa = false;
    }

    SanPham(string ma, string ten, double g, int sl, string dvt) {
        maSP = ma; tenSP = ten; gia = g; soLuong = sl; donViTinh = dvt; daXoa = false;
    }

    virtual ~SanPham() {}

    virtual void nhap() {
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Nhap ten san pham: ";
        getline(cin, tenSP);
        cout << "Nhap don vi tinh (lon/loc/thung/goi...): ";
        getline(cin, donViTinh);

        while (true) {
            cout << "Nhap gia ban: ";
            cin >> gia;
            if (!cin.fail() && gia >= 0) {
                break;
            }
            cout << ">> Loi: Gia khong hop le (phai la so va >= 0). Vui long nhap lai!\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        while (true) {
            cout << "Nhap so luong kho ban dau: ";
            cin >> soLuong;
            if (!cin.fail() && soLuong >= 0) {
                break;
            }
            cout << ">> Loi: So luong khong hop le (phai la so nguyen va >= 0). Vui long nhap lai!\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }

    virtual void xuat() const = 0;
    virtual string loai() const = 0;

    string getMa() const { return maSP; }
    void setMa(string ma) { maSP = ma; } 
    string getTen() const { return tenSP; }
    double getGia() const { return gia; }
    int getSoLuong() const { return soLuong; }
    string getDVT() const { return donViTinh; }
    bool isXoa() const { return daXoa; }
    
    void setXoa(bool status) { daXoa = status; }
    void setSoLuong(int sl) { soLuong = sl; }

    virtual string toCSV() const {
        return maSP + "," + tenSP + "," + to_string(gia) + "," + 
               to_string(soLuong) + "," + donViTinh + "," + (daXoa ? "1" : "0") + "," + loai();
    }
};

// ==================== CAC CLASS CON KE THUA ====================
class DoUong : public SanPham {
private:
    double dungTich;
public:
    DoUong() : SanPham() { dungTich = 0; }
    DoUong(string ma, string ten, double g, int sl, string dvt, double dt) 
        : SanPham(ma, ten, g, sl, dvt), dungTich(dt) {}

    void nhap() override {
        SanPham::nhap();
        while (true) {
            cout << "Nhap dung tich (ml): ";
            cin >> dungTich;
            if (!cin.fail() && dungTich > 0) break;
            cout << ">> Loi: Dung tich phai lon hon 0. Vui long nhap lai!\n";
            cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
    void xuat() const override {
        cout << left << setw(10) << maSP << setw(20) << tenSP << setw(10) << gia 
             << setw(8) << soLuong << setw(10) << donViTinh << setw(12) << to_string(dungTich)+"ml" 
             << setw(12) << "Do Uong" << (daXoa ? " [NGUNG BAN]" : "") << endl;
    }
    string loai() const override { return "DoUong"; }
};

class BanhKeo : public SanPham {
private:
    int calories;
public:
    BanhKeo() : SanPham() { calories = 0; }
    BanhKeo(string ma, string ten, double g, int sl, string dvt, int cal) 
        : SanPham(ma, ten, g, sl, dvt), calories(cal) {}

    void nhap() override {
        SanPham::nhap();
        while (true) {
            cout << "Nhap luong calories (kcal): ";
            cin >> calories;
            if (!cin.fail() && calories >= 0) break;
            cout << ">> Loi: Calories phai >= 0. Vui long nhap lai!\n";
            cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
    void xuat() const override {
        cout << left << setw(10) << maSP << setw(20) << tenSP << setw(10) << gia 
             << setw(8) << soLuong << setw(10) << donViTinh << setw(12) << to_string(calories)+"kcal" 
             << setw(12) << "Banh Keo" << (daXoa ? " [NGUNG BAN]" : "") << endl;
    }
    string loai() const override { return "BanhKeo"; }
};

class GiaDung : public SanPham {
private:
    int baoHanh;
public:
    GiaDung() : SanPham() { baoHanh = 0; }
    GiaDung(string ma, string ten, double g, int sl, string dvt, int bh) 
        : SanPham(ma, ten, g, sl, dvt), baoHanh(bh) {}

    void nhap() override {
        SanPham::nhap();
        while (true) {
            cout << "Nhap thoi gian bao hanh (thang): ";
            cin >> baoHanh;
            if (!cin.fail() && baoHanh >= 0) break;
            cout << ">> Loi: Bao hanh phai >= 0. Vui long nhap lai!\n";
            cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
    void xuat() const override {
        cout << left << setw(10) << maSP << setw(20) << tenSP << setw(10) << gia 
             << setw(8) << soLuong << setw(10) << donViTinh << setw(12) << to_string(baoHanh)+" thang" 
             << setw(12) << "Gia Dung" << (daXoa ? " [NGUNG BAN]" : "") << endl;
    }
    string loai() const override { return "GiaDung"; }
};

// ==================== CLASS NHAN VIEN ====================
class NhanVien {
private:
    string maNV;
    string tenNV;
    string gioiTinh;
    int soCaLam;
    double luongMoiCa;
    string username;
    string password;
    string chucVu; 

public:
    NhanVien() { 
        maNV = ""; tenNV = ""; gioiTinh = "Nam"; soCaLam = 0; luongMoiCa = 0;
        username = ""; password = ""; chucVu = "nhanvien";
    }
    
    NhanVien(string ma, string ten, string gt, int soca, double luong, string user, string pass, string cv) {
        maNV = ma; tenNV = ten; gioiTinh = gt; soCaLam = soca; luongMoiCa = luong;
        username = user; password = pass; chucVu = cv;
    }

    void nhap() {
        cout << "Nhap ma nhan vien: ";
        cin >> maNV;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Nhap ten nhan vien: ";
        getline(cin, tenNV);
        cout << "Nhap gioi tinh: ";
        getline(cin, gioiTinh);

        while (true) {
            cout << "Nhap so ca lam viec: ";
            cin >> soCaLam;
             if (cin.fail() || soCaLam < 0) {
        cout << ">> Loi: So ca lam khong hop le! Nhap lai.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    } else {
        break;
    }
        }

        while (true) {
            cout << "Nhap muc luong moi ca: ";
            cin >> luongMoiCa;
            if (cin.fail() || luongMoiCa < 0) {
        cout << ">> Loi: Luong khong hop le! Nhap lai.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    } else {
        break;
    }
        }

        cout << "Dat Username dang nhap cho NV nay: "; cin >> username;
        cout << "Dat Password dang nhap cho NV nay: "; cin >> password;
       while (true) {
    cout << "Phan quyen chuc vu (admin / nhanvien): ";
    cin >> chucVu;
    if (chucVu == "admin" || chucVu == "nhanvien") {
        break;
    }
    cout << ">> Loi: Chi duoc nhap admin hoac nhanvien!\n";
}
    }

    double tinhLuong() const {
        return soCaLam * luongMoiCa;
    }

    void xuat() const {
        cout << left << setw(10) << maNV << setw(22) << tenNV << setw(12) << gioiTinh 
             << setw(12) << soCaLam << setw(15) << fixed << setprecision(0) << luongMoiCa 
             << setw(15) << tinhLuong() << setw(12) << chucVu << endl;
    }

    string getUsername() const { return username; }
    string getPassword() const { return password; }
    string getChucVu() const { return chucVu; }
    string getTenNV() const { return tenNV; }
};

// ==================== CLASS KHACH HANG ====================
class KhachHang {
private:
    string maKH;
    string tenKH;
    string SDT;
    int diem;
    
public:
    KhachHang() { maKH = ""; tenKH = ""; diem = 0; SDT = ""; }
    KhachHang(string ma, string een, string phone, int d) { maKH = ma; tenKH = een; diem = d; SDT = phone; }

    void nhap() {
        cout << "Nhap ma khach hang: ";
        cin >> maKH;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Nhap ten khach hang: ";
        getline(cin, tenKH);
        cout << "Nhap so dien thoai: ";
        getline(cin, SDT);
        diem = 0;
    }

    string getMa() const { return maKH; }
    string getTen() const { return tenKH; }
    string getSDT() const { return SDT; }
    int getDiem() const { return diem; }
    void congDiem(int d) { diem += d; }

    void xuat() const {
        cout << left << setw(15) << maKH << setw(25) << tenKH << setw(15) << diem << setw(20) << SDT << endl;
    }
};

// ==================== Gio hang ====================
class GioHang {
private:
    vector<pair<string, int>> dsMua;

public:
    void themSP(string ma, int sl) {
        dsMua.push_back({ma, sl});
    }

    vector<pair<string, int>> getDS() const {
        return dsMua;
    }

    void hienThi() {
        cout << "\n===== GIO HANG TAM =====\n";
        for (auto x : dsMua) {
            cout << "Ma SP: " << x.first
                 << " | So luong: " << x.second << endl;
        }
    }

    bool rong() const {
        return dsMua.empty();
    }

    void xoaGH() {
        dsMua.clear();
    }
};

// ==================== CLASS HOA DON ====================
class HoaDon {
private:
    string maHD;
    string maKH; 
    vector<pair<string, int>> dsMua;
    double tongTien;

public:
    HoaDon() { maHD = ""; maKH = ""; tongTien = 0; }

    void setMaHD(string ma) { maHD = ma; }
    void setMaKH(string ma) { maKH = ma; }
    void themSanPhamMua(string ma, int sl) { dsMua.push_back({ma, sl}); }
    void setTongTien(double tt) { tongTien = tt; }
    
    double getTongTien() const { return tongTien; }
    string getMaHD() const { return maHD; }

    void xuat(const map<string, string>& tenSPMap) const {
        cout << "\n================= HOA DON BAN HANG =================" << endl;
        cout << "Ma hoa don  : " << maHD << endl;
        cout << "Khach hang  : " << (maKH.empty() ? "Khach vang lai" : maKH) << endl;
        cout << "----------------------------------------------------" << endl;
        cout << left << setw(15) << "Ma SP" << setw(22) << "Ten SP" << setw(10) << "SL Mua" << endl;
        for (const auto &x : dsMua) {
            string tenSP = "SP Da xoa/An";
            if(tenSPMap.find(x.first) != tenSPMap.end()) {
                tenSP = tenSPMap.at(x.first);
            }
            cout << left << setw(15) << x.first << setw(22) << tenSP << setw(10) << x.second << endl;
        }
        cout << "----------------------------------------------------" << endl;
        cout << "TONG TIEN THANH TOAN: " << fixed << setprecision(0) << tongTien << " VND" << endl;
        cout << "====================================================\n";
    }
};

// ==================== CLASS QUAN LY TRUNG TAM ====================
class QuanLyCuaHang {
private:
    vector<shared_ptr<SanPham>> dsSP;
    vector<NhanVien> dsNV;
    vector<KhachHang> dsKH;
    vector<HoaDon> dsHD;
    GioHang gioHang;
    
    string currentUser = "";
    string currentRole = "";

public:
    QuanLyCuaHang() {
        khoiTaoDuLieuMau();
    }

    void khoiTaoDuLieuMau() {
        dsSP.push_back(make_shared<DoUong>("SP01", "Coca Cola", 12000, 50, "Lon", 330));
        dsSP.push_back(make_shared<DoUong>("SP02", "Pepsi", 11000, 40, "Lon", 330));
        dsSP.push_back(make_shared<DoUong>("SP03", "Nuoc Cam Twister", 15000, 30, "Chai", 450));
        dsSP.push_back(make_shared<DoUong>("SP04", "Sua Tuoi Vinamilk", 36000, 20, "Loc", 180));
        dsSP.push_back(make_shared<BanhKeo>("SP05", "Banh ChocoPie", 55000, 15, "Hop", 130));
        dsSP.push_back(make_shared<BanhKeo>("SP06", "Keo De Haribo", 28000, 25, "Goi", 80));
        dsSP.push_back(make_shared<BanhKeo>("SP07", "Khoai Tay Pringles", 42000, 18, "Lon", 150));
        dsSP.push_back(make_shared<GiaDung>("SP08", "O Cam Dien Quang", 85000, 10, "Cai", 12));
        dsSP.push_back(make_shared<GiaDung>("SP09", "Khan Giay Quataco", 15000, 100, "Goi", 0));
        dsSP.push_back(make_shared<GiaDung>("SP10", "Pin AA Panasonic", 30000, 35, "Vi", 6));

        dsNV.push_back(NhanVien("NV00", "Quan Ly Toi Cao", "Nam", 10, 100000, "admin", "admin123", "admin"));
        dsNV.push_back(NhanVien("NV01", "Nguyen Van Thu Ngan", "Nu", 24, 30000, "nv01", "123", "nhanvien"));
    }

    bool dangNhap() {
        string user, pass;
        cout << "\n+--------------------------------------------------+";
        cout << "\n|        DANG NHAP HE THONG QUAN LY CUA HANG       |";
        cout << "\n+--------------------------------------------------+";
        cout << "\n  Username: "; cin >> user;
        cout << "  Password: "; cin >> pass;
        cout << "+--------------------------------------------------+\n";

        for (const auto &nv : dsNV) {
            if (nv.getUsername() == user && nv.getPassword() == pass) {
                currentUser = nv.getTenNV();
                currentRole = nv.getChucVu();
                cout << "=> DANG NHAP THANH CONG! Xin chao: " << currentUser << " [" << currentRole << "]\n";
                return true;
            }
        }
        cout << "=> Sai tai khoan hoac mat khau! Vui long kiem tra lai.\n";
        return false;
    }
    bool xacThucAdmin() {
    if (currentRole != "admin") {
        return false;
    }

    string pass;
    cout << "\n>> XAC THUC ADMIN - NHAP LAI MAT KHAU: ";
    cin >> pass;

    for (const auto &nv : dsNV) {
        if (nv.getChucVu() == "admin" && nv.getPassword() == pass) {
            return true;
        }
    }

    cout << ">> XAC THUC THAT BAI!\n";
    return false;
}

    void dangXuat() {
        currentUser = ""; currentRole = "";
        cout << "Da dang xuat khoi he thong.\n";
    }

    void themSanPham() {
        if (!xacThucAdmin()) { 
            cout << ">> LOI: Ban khong co quyen ADMIN de dung chuc nang nay!\n";
            return;
        }

        string maCheck;
        cout << "Nhap ma san pham muon them: ";
        cin >> maCheck;

        for (auto sp : dsSP) {
            if (sp->getMa() == maCheck) {
                cout << "\n=> THONG BAO: Ma san pham [" << maCheck << "] da ton tai tren he thong!\n";
                cout << "   Ten san pham hien tai: " << sp->getTen() << " | SL ton kho: " << sp->getSoLuong() << endl;
                
                if (sp->isXoa()) {
                    sp->setXoa(false);
                    cout << "   [He thong]: Tu dong khoi phuc trang thai kinh doanh cho san pham nay.\n";
                }

                int slTangThem;
                while (true) {
                    cout << "Nhap so luong muon TANG THEM vao kho: ";
                    cin >> slTangThem;
                    if (!cin.fail() && slTangThem >= 0) {
                        break;
                    }
                    cout << ">> Loi: So luong phai la so nguyen >= 0. Vui long nhap lai!\n";
                    cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }

                sp->setSoLuong(sp->getSoLuong() + slTangThem);
                cout << "=> CAP NHAT THANH CONG! Kho hien tai cua [" << sp->getTen() << "] la: " << sp->getSoLuong() << endl;
                return; 
            }
        }

        int chon;
        cout << "\nMa chua ton tai. Chon loai san pham de tao moi:\n1. Do Uong\n2. Banh Keo\n3. Gia Dung\nChon: ";
        cin >> chon;

        shared_ptr<SanPham> spMoi;
        if (chon == 1) spMoi = make_shared<DoUong>();
        else if (chon == 2) spMoi = make_shared<BanhKeo>();
        else if (chon == 3) spMoi = make_shared<GiaDung>();
        else { cout << "Lua chon khong hop le!\n"; return; }

        spMoi->setMa(maCheck); 
        spMoi->nhap();         
        
        dsSP.push_back(spMoi);
        cout << "Them san pham moi vao kho thanh cong!\n";
    }

    void hienThiSP() {
        cout << "\n================================ DANH SACH SAN PHAM ================================\n";
        cout << left << setw(10) << "Ma" << setw(20) << "Ten" << setw(10) << "Gia" 
             << setw(8) << "SL Kho" << setw(10) << "DVT" << setw(12) << "Thong So" << setw(12) << "Phan Loai" << endl;
        cout << "------------------------------------------------------------------------------------\n";
        for (const auto &sp : dsSP) {
            sp->xuat();
        }
    }

    void timKiemSP() {
        if (dsSP.empty()) {
            cout << "Kho hang dang trong, khong co san pham de tim kiem!\n";
            return;
        }

        int luaChon;
        cout << "\n--- CHON CHE DO TIM KIEM ---";
        cout << "\n1. Tim kiem theo MA san pham (Chinh xac)";
        cout << "\n2. Tim kiem theo TEN san pham (Goi y gan dung)";
        cout << "\nNhap lua chon cua ban: ";
        cin >> luaChon;

        if (cin.fail() || (luaChon != 1 && luaChon != 2)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Lua chon khong hop le! Quay lai menu chinh.\n";
            return;
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (luaChon == 1) {
            string maCanTim;
            cout << "Nhap MA san pham can tim: ";
            cin >> maCanTim;

            cout << "\n--- KET QUA TIM KIEM THEO MA [" << maCanTim << "] ---\n";
            cout << left << setw(10) << "Ma" << setw(20) << "Ten" << setw(10) << "Gia" 
                 << setw(8) << "SL Kho" << setw(10) << "DVT" << setw(12) << "Thong So" << setw(12) << "Phan Loai" << endl;
            cout << "------------------------------------------------------------------------------------\n";
            
            bool timThay = false;
            for (const auto &sp : dsSP) {
                if (sp->getMa() == maCanTim) {
                    sp->xuat();
                    timThay = true;
                    break;
                }
            }
            if (!timThay) cout << "=> Khong tim thay san pham nao co ma: " << maCanTim << endl;

        } else if (luaChon == 2) {
            string tuKhoa;
            cout << "Nhap ten san pham (hoac mot phan ten): ";
            getline(cin, tuKhoa);

            string tuKhoaThuong = tuKhoa;
            transform(tuKhoaThuong.begin(), tuKhoaThuong.end(), tuKhoaThuong.begin(), ::tolower);

            cout << "\n--- KET QUA GOI Y CHO TU KHOA [ " << tuKhoa << " ] ---\n";
            cout << left << setw(10) << "Ma" << setw(20) << "Ten" << setw(10) << "Gia" 
                 << setw(8) << "SL Kho" << setw(10) << "DVT" << setw(12) << "Thong So" << setw(12) << "Phan Loai" << endl;
            cout << "------------------------------------------------------------------------------------\n";

            bool timThay = false;
            for (const auto &sp : dsSP) {
                string tenSPThuong = sp->getTen();
                transform(tenSPThuong.begin(), tenSPThuong.end(), tenSPThuong.begin(), ::tolower);

                if (tenSPThuong.find(tuKhoaThuong) != string::npos) {
                    sp->xuat();
                    timThay = true;
                }
            }
            if (!timThay) cout << "=> Khong tim thay san pham nao khop voi tu khoa: " << tuKhoa << endl;
        }
    }

    void xoaSP() {
        if (!xacThucAdmin()) {
            cout << ">> LOI: Chi tai khoan ADMIN moi co quyen dung chuc nang nay!\n";
            return;
        }
        string ma;
        cout << "Nhap ma san pham muon xoa/ngung kinh doanh: "; cin >> ma;

        for (auto sp : dsSP) {
            if (sp->getMa() == ma) {
                if(sp->isXoa()) {
                    cout << "San pham nay da duoc danh dau ngung ban tu truoc!\n";
                    return;
                }
                sp->setXoa(true);
                cout << "Xoa thanh cong (San pham da an khoi danh muc ban hang, lich su hoa don duoc giu lai)!\n";
                return;
            }
        }
        cout << "Khong tim thay san pham nao hop le!\n";
    }

    void sapXepGiaTang() {
        sort(dsSP.begin(), dsSP.end(), [](shared_ptr<SanPham> a, shared_ptr<SanPham> b) {
            return a->getGia() < b->getGia();
        });
        cout << "Sap xep danh sach san pham theo gia tang dan thanh cong!\n";
    }

    void themNhanVien() {
        if (!xacThucAdmin()) {
            cout << ">> LOI: Chi ADMIN moi co quyen quan ly nhan su!\n";
            return;
        }
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        NhanVien nv; nv.nhap();
        dsNV.push_back(nv);
        cout << "Them nhan vien moi thanh cong!\n";
    }

    void hienThiNV() {
        cout << "\n===================================== DANH SACH NHAN VIEN =====================================\n";
        cout << left << setw(10) << "Ma NV" << setw(22) << "Ten Nhan Vien" << setw(12) << "Gioi Tinh" 
             << setw(12) << "So Ca" << setw(15) << "Luong/Ca" << setw(15) << "Tong Luong" << setw(12) << "Chuc Vu" << endl;
        cout << "-----------------------------------------------------------------------------------------------\n";
        for (const auto &nv : dsNV) nv.xuat();
    }

    void themKH() {
        KhachHang kh; kh.nhap();
        dsKH.push_back(kh);
        cout << "Them khach hang moi thanh cong!\n";
    }

    void hienThiKH() {
        cout << "\n==================== DANH SACH KHACH HANG ====================\n";
        cout << left << setw(15) << "Ma KH" << setw(25) << "Ten Khach Hang" << setw(15) << "Diem Tich Luy" << setw(20) << "So Dien Thoai" << endl;
        cout << "--------------------------------------------------------------\n";
        for (const auto &kh : dsKH) kh.xuat();
    }

    void taoHoaDon() {
        if (dsSP.empty()) {
            cout << "Cua hang chua co san pham nao trong kho de ban!\n"; return;
        }
        
        string maHD, maKH;
        cout << "\n--- LAP HOA DON BAN HANG TIEU CHUAN ---\n";
        cout << "Nhap ma hoa don: "; cin >> maHD;
        cout << "Nhap ma khach hang than thiet (An Enter neu la khach le): ";
        cin.ignore();
        getline(cin, maKH);

        KhachHang* khPtr = nullptr;
        if (!maKH.empty()) {
            for (auto &kh : dsKH) {
                if (kh.getMa() == maKH) {
                    khPtr = &kh; break;
                }
            }
            if (!khPtr) {
                cout << "Canh bao: Ma khach hang khong khop! He thong tinh vao Khach le.\n";
                maKH = "";
            }
        }
        if (gioHang.rong()) {
    cout << "Gio hang dang rong!\n";
    return;
}
        HoaDon hd;
        hd.setMaHD(maHD);
        hd.setMaKH(maKH);
        double tongTienHD = 0;

        vector<pair<shared_ptr<SanPham>, int>> updateKhoList;
        
    for (auto item : gioHang.getDS()) {

    string ma = item.first;
    int sl = item.second;

    shared_ptr<SanPham> foundSP = nullptr;

    for (auto sp : dsSP) {
        if (sp->getMa() == ma && !sp->isXoa()) {
            foundSP = sp;
            break;
        }
    }

    if (!foundSP) {
        cout << "LOI: San pham khong ton tai!\n";
        return;
    }

    if (foundSP->getSoLuong() < sl) {
        cout << "LOI: Kho khong du hang!\n";
        return;
    }

    tongTienHD += foundSP->getGia() * sl;

    hd.themSanPhamMua(ma, sl);

    updateKhoList.push_back({foundSP, sl});
}
       

        for(auto &item : updateKhoList) {
            int slMoi = item.first->getSoLuong() - item.second;
            item.first->setSoLuong(slMoi);
        }

        hd.setTongTien(tongTienHD);

        if (khPtr != nullptr) {
            int diemThuong = static_cast<int>(tongTienHD / 100000);
            khPtr->congDiem(diemThuong);
            cout << ">> Khach hang: " << khPtr->getTen() << " duoc he thong tich luy tu dong: +" << diemThuong << " diem.\n";
        }

        dsHD.push_back(hd);
        cout << ">>> BAN HANG VA XUAT HOA DON THANH CONG!\n";
        gioHang.xoaGH();
    }

    void hienThiHD() {
        if (dsHD.empty()) {
            cout << "Chua co giao dich nao duoc thuc hien! Danh sach hoa don dang trong.\n"; 
            return;
        }
        
        map<string, string> tenSPMap;
        for(const auto &sp : dsSP) {
            tenSPMap[sp->getMa()] = sp->getTen();
        }

        int luaChon;
        cout << "\n--- CHE DO XEM HOA DON ---";
        cout << "\n1. Xem TOAN BO danh sach hoa don da xuat";
        cout << "\n2. Tra cuu mot HOA DON CU THE theo ma hoa don";
        cout << "\nNhap lua chon cua ban: ";
        cin >> luaChon;

        if (cin.fail() || (luaChon != 1 && luaChon != 2)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Lua chon khong hop le! Quay lai menu chinh.\n";
            return;
        }

        if (luaChon == 1) {
            cout << "\n====================================================";
            cout << "\n           HIEN THI TOAN BO HOA DON CUA HANG        ";
            cout << "\n====================================================";
            for (auto &hd : dsHD) {
                hd.xuat(tenSPMap);
            }
            cout << "\n>>> Da hien thi het tat ca " << dsHD.size() << " hoa don.\n";

        } else if (luaChon == 2) {
            string maHDCanTim;
            cout << "Nhap MA HOA DON can kiem tra: ";
            cin >> maHDCanTim;

            bool timThay = false;
            for (auto &hd : dsHD) {
                if (hd.getMaHD() == maHDCanTim) {
                    hd.xuat(tenSPMap);
                    timThay = true;
                    break;
                }
            }
            if (!timThay) {
                cout << "=> KHONG TIM THAY hoa don nao co ma: " << maHDCanTim << " tren he thong!\n";
            }
        }
    }

    void thongKe() {
        double tongDoanhThu = 0;
        for (auto &hd : dsHD) {
            tongDoanhThu += hd.getTongTien();
        }

        cout << "\n============= BAO CAO DOANH THU & SAO KE =============" << endl;
        cout << "  * Tong so mat hang hien co: " << dsSP.size() << endl;
        cout << "  * Tong so nhan vien:       " << dsNV.size() << endl;
        cout << "  * Tong so khach hang:      " << dsKH.size() << endl;
        cout << "  * Tong so hoa don da xuat: " << dsHD.size() << endl;
        cout << "  ----------------------------------------------------" << endl;
        cout << "  => TONG DOANH THU CUA HANG: " << fixed << setprecision(0) << tongDoanhThu << " VND" << endl;
        cout << "======================================================\n";
    }

    void luuFileSP() {
        ofstream fout("SanPham.csv");
        for (const auto &sp : dsSP) {
            fout << sp->toCSV() << endl;
        }
        fout.close();
        cout << "Luu file thanh cong!\n";
    }

    void docFileSP() {
        ifstream fin("SanPham.csv");
        if (!fin) {
            cout << "Khong mo duoc file!\n";
            return;
        }
        string line;
        cout << "\n========= NOI DUNG FILE CSV =========\n";
        while (getline(fin, line)) {
            cout << line << endl;
        }
        fin.close();
    }
    
void muaHang() {
	 hienThiSP();
    if (dsSP.empty()) {
        cout << "Khong co san pham de mua!\n";
        return;
    }

    int n;
    cout << "\n===== THEM SAN PHAM VAO GIO HANG =====\n";
    cout << "Nhap so loai san pham muon mua: ";
    cin >> n;

    for (int i = 0; i < n; i++) {
        string ma;
        int sl;

        cout << "\nNhap ma san pham: ";
        cin >> ma;

        cout << "Nhap so luong mua: ";
        cin >> sl;

        bool timThay = false;

        for (auto sp : dsSP) {
            if (sp->getMa() == ma && !sp->isXoa()) {

                if (sp->getSoLuong() < sl) {
                    cout << "Kho khong du hang!\n";
                    return;
                }

                gioHang.themSP(ma, sl);

                cout << "Them vao gio hang thanh cong!\n";
                timThay = true;
                break;
            }
        }

        if (!timThay) {
            cout << "Khong tim thay san pham!\n";
        }
    }

    gioHang.hienThi();
}
    void menu() {
        while (!dangNhap());

        int chon;
        do {
            cout << "\n==================================================";
            cout << "\n   QUAN LY CUA HANG TIEN LOI [" << currentUser << " - " << currentRole << "]";
            cout << "\n==================================================";
            cout << "\n[1] Mua hang / Them vao gio";
            cout << "\n[2] Them san pham hoac Tang cuong kho (Admin)";
            cout << "\n[3] Hien thi danh sach san pham";
            cout << "\n[4] Tim kiem san pham nang cao (Theo Ma / Theo Ten)";
            cout << "\n[5] Xoa/Ngung ban san pham (Admin)";
            cout << "\n[6] Sap xep san pham theo gia tang dan";
            cout << "\n[7] Them nhan vien moi (Admin)";
            cout << "\n[8] Hien thi danh sach nhan vien & Luong";
            cout << "\n[9] Them khach hang moi";
            cout << "\n[10] Hien thi danh sach khach hang";
            cout << "\n[11] Lap hoa don (Kiem tra, tru kho & Tich diem)";
            cout << "\n[12] Xem danh sach/Tra cuu hoa don da xuat";
            cout << "\n[13] Bao cao thong ke doanh thu & Sao ke";
            cout << "\n[14] Luu file CSV san pham";
            cout << "\n[15] Doc file CSV san pham";
            cout << "\n[16] Dang xuat / Thay doi tai khoan nguoi dung";
            cout << "\n[0] Thoat chuong trinh";
            cout << "\n==================================================";
            cout << "\nNhap lua chon: ";

          while (true) {
    if (cin >> chon) {
        break; // nháº­p Ä‘Ãºng thÃ¬ thoÃ¡t vÃ²ng láº·p
    }
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "Nhap sai dinh dang! Vui long nhap so.\n";
            }

            switch (chon) {
            	case 1: muaHang(); break;
                case 2: themSanPham(); break;
                case 3: hienThiSP(); break;
                case 4: timKiemSP(); break;
                case 5: xoaSP(); break;
                case 6: sapXepGiaTang(); break;
                case 7: themNhanVien(); break;
                case 8: hienThiNV(); break;
                case 9: themKH(); break;
                case 10: hienThiKH(); break;
                case 11: taoHoaDon(); break;
                case 12: hienThiHD(); break;
                case 13: thongKe(); break;
                case 14: luuFileSP(); break;
                case 15: docFileSP(); break;
                case 16: dangXuat(); while(!dangNhap()); break;
                case 0: cout << "He thong tat. Tam biet!\n"; break;
                default: cout << "Lua chon khong ton tai tren thanh Menu!\n";
            }
        } while (chon != 0);
    }
};

int main() {
    QuanLyCuaHang ql;
    ql.menu();
    return 0;
}
