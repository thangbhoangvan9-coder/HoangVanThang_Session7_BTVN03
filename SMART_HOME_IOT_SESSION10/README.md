1. Phân tích Input / Output
Input

Thông tin thiết bị:

deviceID: mã thiết bị.
voltage: điện áp U, đơn vị V.
current: dòng điện I, đơn vị A.
measuredPower: công suất đo được, đơn vị W.
status: trạng thái thiết bị:
0: Tắt
1: Bật
operatingMinutes: thời gian hoạt động, đơn vị phút.
Output

Chương trình cần:

In sizeof() của struct chưa tối ưu.
In sizeof() của struct đã tối ưu.
Kiểm tra dữ liệu đầu vào.
Tính công suất:
Pcalc = U × I
Kiểm tra sai lệch công suất > 5%.
Kiểm tra quá tải:
I > 30A
hoặc P > 6600W
Kiểm tra rò rỉ khi thiết bị tắt nhưng I > 0.05A.
Tính điện năng:
kWh = P × (t / 60.0) / 1000
2. Phân tích Memory Padding

Ví dụ struct chưa tối ưu:

struct UnoptimizedDevice {
    int deviceID;
    float voltage;
    int status;
    double measuredPower;
    float current;
    int operatingMinutes;
};

Các kiểu dữ liệu có kích thước khác nhau:

int    → thường 4 bytes
float  → thường 4 bytes
double → thường 8 bytes

Trình biên dịch có thể thêm padding để căn chỉnh dữ liệu trong bộ nhớ.

Struct tối ưu

Ta nhóm các kiểu có kích thước lớn trước:

struct OptimizedDevice {
    double measuredPower;
    float voltage;
    float current;
    int deviceID;
    int status;
    int operatingMinutes;
};

Cách này giúp giảm khả năng xuất hiện padding không cần thiết.

Lưu ý: kích thước sizeof() thực tế phụ thuộc compiler và kiến trúc máy. Vì vậy chương trình nên dùng sizeof() để kiểm tra thay vì tự kết luận một con số cố định.

3. Hai giải pháp tái cấu trúc
Tiêu chí	Giải pháp 1: Flat Struct	Giải pháp 2: Nested Struct
Cách tổ chức	Sắp xếp lại field	Nhóm field theo chức năng
Bộ nhớ	Thường tối ưu tốt	Có thể phát sinh padding ở các struct
Truy xuất	Đơn giản device.voltage	Phải truy xuất nhiều cấp
Dễ hiểu	Dễ	Dễ khi dữ liệu lớn
Bảo trì	Khá dễ	Tốt hơn khi hệ thống mở rộng
Khả năng mở rộng	Trung bình	Tốt
Phù hợp Gateway RAM thấp	Tốt	Tùy trường hợp

4. Lựa chọn giải pháp

Trong bài toán IoT Gateway có RAM hạn chế, chọn Giải pháp 1 - Flat Struct Optimization.

Lý do:

Cấu trúc đơn giản.
Truy xuất nhanh bằng toán tử .
Dễ lập trình với kiến thức hiện tại.
Có thể giảm padding bằng cách sắp xếp field hợp lý.
Không tạo thêm nhiều lớp struct.

Nested Struct phù hợp hơn khi hệ thống lớn và cần tổ chức dữ liệu thành nhiều nhóm chức năng.

5. Luồng xử lý
Bắt đầu
   ↓
Khai báo struct
   ↓
In sizeof struct cũ/mới
   ↓
Nhập dữ liệu thiết bị
   ↓
Kiểm tra U <= 0
I < 0
t < 0
status không phải 0/1
   ↓
Có lỗi? ── Có → Báo lỗi → Kết thúc
   ↓ Không
Tính Pcalc = U × I
   ↓
Kiểm tra sai lệch > 5%
   ↓
Kiểm tra I > 30A hoặc P > 6600W
   ↓
Kiểm tra status = 0 và I > 0.05A
   ↓
Tính kWh
   ↓
In kết quả
   ↓
Kết thúc