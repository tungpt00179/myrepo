#ifndef LOG_H
#define LOG_H
#include <QDebug>
#include <QTime>
#define LOG qDebug() << QTime::currentTime().toString() << __FUNCTION__
/*
 * Noted: app flow
 *  1) Ket noi, ket noi lai:
 *      - doc cau hinh tu file (network, device, driver)
 *          tai thoi diem ban dau gia tri cua driver se ko co, cac gia tri network
 *          device bat buoc phai co de ket noi.
 *          gia tri cua driver se duoc ghi khi co su kien quet the de dang nhap
 *          cua bac tai.
 *          - neu doc cau hinh thanh cong: chuyen qua trang thai "NeedLogin"
 *          - neu doc cau hinh that bai: chuyen qua trang thai "ErrorConfig"
 *
 *      - thuc hien ket noi ve server dua theo thong tin cau hinh
 *          - truong hop trong chua co thong tin cau hinh ve tai xe: bo qua ko lam gi
 *          - truong hop co thong tin cau hinh ve tai xe:
 *              - neu thong tin da co token: gui lenh login token
 *                  - server tra ve ok, chuyen qua trang thai "Ready" va thoat
 *                  - server tra ve error, thuc hien buoc tiep theo
 *              - neu chua co token hoac co token ma server tra ve eror: gui lenh login new
 *                  - server tra ve ok:
 *                      - thuc hien so sanh gui lenh cap nhat thong tin(name, id, device plate)
 *                      - chuyen qua trang thai "Ready"
 *                  - server tra ve error:
 *                      -  chuyen qua trang thai "InvalidConfig"
 *      - bat ack timer
 *  2) ack timer:
 *      - timeout 15s:
 *      - on_time_out: thuc hien ket noi lai
 *  3) trong su kien nhan goi tin:
 *      - neu nhan duoc goi tin ack:
 *          - reset timer ack
 *      - neu nhan duoc goi tin khac:
 *          - xu ly tuy theo state
 *  4) Luong hien thi Order
 *      - sau khi ket noi toi server, thiet bi cho lenh UpdateJob tu server
 *      - hien thi cac order len man hinh
 *      - khi tai xe bam vao mot order, thong tin chi tiet ve order do se duoc hien thi
 *      - trang thai: "Ready"
 *  5) Luong Bid
 *      - Tai xe co the bam nut "Nhan" tren man hinh Order Details de chuyen qua luong bid.
 *      - thiet bi se gui lenh bid ve server va cho ket qua phan hoi
 *          - neu server tra ve error, viec bid that bai, xoa thong tin order ra khoi list
 *          - neu server tra ve success, chuyen qua luong Bid
 *      - trang thai "OnPickup"
 *      - Khi tai xe thuc hien Bid thanh cong, se chuyen qua man hinh bid:
 *          - Order list: disable
 *          - Order detail: show
 *          - Map: show
 *          - GUI: button<ImHere>, button<Pickup>, button<cancel>
 *      - Tai xe lai xe den noi va bam nut ImHere
 *      - Khi khach hang len xe, chuyen qua man hinh tinh tien trong 2 truong hop sau:
 *          - khach hang bam <Pickup> tren dien thoai
 *          - tai xe bam <Pickup> tren thiet bi
 *  6) Luong tinh tien
 *      - Trang thai: OnRoad
 *      - khi chay toi noi, tai xe bam nut Ket Thuc de thuc hien tinh tien.
 *  7) Lich hen
 *      Sau khi book  se assign lai xe
 *      Lai xe se duoc ve trang thai free
 *      Job state thay doi
 *      Su dung getpendingjob
 *      De lay danh sach lich hen
 *      Khi Lai xe excute cai job day de chay,
 *      luc nay jobstate thay doi, state cua lai xe cung thay doi.
 *      Quy trinh lai nhu binh thuong
 * */

#endif // LOG_H

