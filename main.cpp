/**
 * @author Branium Academy
 * @website braniumacademy.net
 * @version 2021.06
 * 
 */

#include <iostream>
#include <fstream>
#include <iomanip>
#include "Student.hpp"
#include "Subject.hpp"
#include "Transcript.hpp"
using namespace std;

void showStudentInfoHeader() {
	cout << left << setw(15) << "Ma SV" << setw(25) << "Ho va ten"
		<< setw(25) << "Email" << setw(20) << "So dien thoai" << endl;
}

void showSubjectInfoHeader() {
	cout << left << setw(15) << "Ma mon" << setw(30) << "Ten mon"
		<< setw(10) << "So tiet" << setw(10) << "So tin" << endl;
}

template<class T> int findElementById(T* arr, const int size, const T& t) {
	for (int i = 0; i < size; i++)
	{
		if (arr[i] == t) {
			return i;
		}
	}
	return -1;
}

template<class T> bool removeElement(T* arr, int& size, const T& t) {
	for (int i = 0; i < size; i++)
	{
		if (arr[i] == t) {
			for (int j = i; j < size - 1; j++)
			{
				arr[j] = arr[j + 1];
			}
			size--;
			return true; // xoa thanh cong
		}
	}
	return false; // xoa that bai
}

template<class T> void sortASC(T* arr, const int size) {
	for (int i = 0; i < size - 1; i++)
	{
		for (int j = size - 1; j > i; j--)
		{
			if (arr[j - 1] > arr[j]) { // neu phan tu dung truoc > phan tu dung sau
				swap(arr[j], arr[j - 1]); // doi cho
			}
		}
	}
}

bool isTranscriptExisted(Transcript<Student, Subject>* arr, const int size, const string studentId, const string subjectId) {
	Student student(studentId);
	Subject subject(subjectId);
	for (int i = 0; i < size; i++)
	{
		if (arr[i].getStudent() == student && arr[i].getSubject() == subject) {
			return true;
		}
	}
	return false;
}

void showTranscriptInfoHeader() {
	cout << left << setw(15) << "Ma SV" << setw(25) << "Ho va ten"
		<< setw(15) << "Ma mon" << setw(25) << "Ten mon hoc"
		<< setw(10) << "Diem he 1" << setw(10) << "Diem he 2" << setw(10)
		<< "Diem he 3" << setw(10) << "GPA" << endl;
}

template<class T> void saveToFile(T* arr, const int size, const string fileName) {
	ofstream ofs(fileName, ios::out | ios::binary);
	if (ofs) {
		for (int i = 0; i < size; i++)
		{
			ofs.write(reinterpret_cast<const char*>(&arr[i]), sizeof(T));
		}
		ofs.close();
	}
}

template<class T> void readDataFromFile(T* arr, int& size, const string fileName) {
	ifstream ifs(fileName, ios::in | ios::binary);
	if (ifs) {
		while (!ifs.eof()) {
			T object;
			ifs.read(reinterpret_cast<char*>(&object), sizeof(T));
			if (ifs.eof()) {
				break;
			}
			else {
				arr[size++] = object;
			}
		}
		ifs.close();
	}
}

int main() {
	int choice = 0;
	// khai báo mảng chứa danh sách sinh viên, môn học và bảng điểm
	Student students[200];
	Subject subjects[200];
	Transcript<Student, Subject> transcripts[200];
	// khai báo số phần tử của mỗi mảng
	int numberOfStudent = 0;
	int numberOfSubject = 0;
	int numberOfTranscript = 0;
	// khai báo tên file input/output
	string studentFile = "student.dat";
	string subjectFile = "subject.dat";
	string transcriptFile = "transcript.dat";
	// đọc dữ liệu từ file nhị phân
	readDataFromFile(students, numberOfStudent, studentFile);
	readDataFromFile(subjects, numberOfSubject, subjectFile);
	readDataFromFile(transcripts, numberOfTranscript, transcriptFile);
	// menu chương trình
	do {
		cout << "============================== MENU =============================\n";
		cout << "=\t01. Them sinh vien moi vao danh sach.	\t\t=\n";
		cout << "=\t02. Them mon hoc moi vao danh sach.		\t=\n";
		cout << "=\t03. Hien thi danh sach sinh vien.		\t=\n";
		cout << "=\t04. Hien thi danh sach mon hoc.			\t=\n";
		cout << "=\t05. Tim kiem sinh vien trong danh sach.	\t\t=\n";
		cout << "=\t06. Tim kiem mon hoc trong danh sach.		\t=\n";
		cout << "=\t07. Cap nhat thong tin email cho sinh vien.	\t=\n";
		cout << "=\t08. Xoa mot sinh vien khoi danh sach.		\t=\n";
		cout << "=\t09. Xoa mot mon hoc khoi danh sach.		\t=\n";
		cout << "=\t10. Sap xep danh sach sinh vien theo ten a-z.\t\t=\n";
		cout << "=\t11. Sap xep danh sach mon hoc theo ten a-z.	\t=\n";
		cout << "=\t12. Lap bang diem cho sinh vien.		\t=\n";
		cout << "=\t13. Tinh diem trung binh cho cac sinh vien.	\t=\n";
		cout << "=\t14. Sap xep danh sach bang diem theo diem TB giam dan.\t=\n";
		cout << "=\t15. Hien thi danh sach bang diem.	\t\t=\n";
		cout << "=\t16. Ghi thong tin ra file.		\t\t=\n";
		cout << "=\t0. Thoat chuong trinh.			\t\t=\n";
		cout << "=================================================================\n";
		cout << "Nhap lua chon: ";
		cin >> choice;
		cin.ignore();
		switch (choice) {
		case 0:
			cout << "============ PHIEN LAM VIEC KET THUC. CAM ON BAN DA SU DUNG DICH VU ============\n";
			break;
		case 1: {
			Student s;
			cin >> s;
			students[numberOfStudent++] = s;
			break;
		}
		case 2: {
			Subject s;
			cin >> s;
			subjects[numberOfSubject++] = s;
			break;
		}
		case 3: {
			if (numberOfStudent > 0) {
				cout << "============================= DANH SACH SINH VIEN "
					<< "=============================\n";
				showStudentInfoHeader();
				for (int i = 0; i < numberOfStudent; i++)
				{
					cout << students[i];
				}
			}
			else {
				cout << "<== Danh sach sinh vien rong ==>\n";
			}
			break;
		}
		case 4: {
			if (numberOfSubject > 0) {
				cout << "===================== DANH SACH MON HOC "
					<< "======================\n";
				showSubjectInfoHeader();
				for (int i = 0; i < numberOfSubject; i++)
				{
					cout << subjects[i];
				}
			}
			else {
				cout << "<== Danh sach mon hoc rong ==>\n";
			}
			break;
		}
		case 5: {
			if (numberOfStudent > 0) {
				string id;
				cout << "Nhap ma sinh vien can tim: ";
				cin >> id;
				Student student(id);
				int foundIndex = findElementById(students, numberOfStudent, student);
				if (foundIndex == -1) {
					cout << "<== Khong tim thay sinh vien ma \"" << id << "\" ==>\n";
				}
				else {
					cout << "<== Tim thay sinh vien ma \"" << id << "\" ==>\n";
					showStudentInfoHeader();
					cout << students[foundIndex];
				}
			}
			else {
				cout << "<== Danh sach sinh vien rong ==>\n";
			}
			break;
		}
		case 6: {
			if (numberOfSubject > 0) {
				string id;
				cout << "Nhap ma mon hoc can tim: ";
				cin >> id;
				Subject subject(id);
				int foundIndex = findElementById(subjects, numberOfSubject, subject);
				if (foundIndex == -1) {
					cout << "<== Khong tim thay mon hoc ma \"" << id << "\" ==>\n";
				}
				else {
					cout << "<== Tim thay mon hoc ma \"" << id << "\" ==>\n";
					showSubjectInfoHeader();
					cout << subjects[foundIndex];
				}
			}
			else {
				cout << "<== Danh sach mon hoc rong ==>\n";
			}
			break;
		}
		case 7: {
			if (numberOfStudent > 0) {
				string id;
				cout << "Nhap ma sinh vien can cap nhat email: ";
				cin >> id;
				Student student(id);
				int foundIndex = findElementById(students, numberOfStudent, student);
				if (foundIndex == -1) {
					cout << "<== Khong tim thay sinh vien ma \"" << id << "\" ==>\n";
				}
				else {
					cout << "Nhap email moi: ";
					string email;
					cin >> email;
					students[foundIndex].setEmail(email);
					cout << "<== Cap nhat email thanh cong ==>\n";
				}
			}
			else {
				cout << "<== Danh sach sinh vien rong ==>\n";
			}
			break;
		}
		case 8: {
			if (numberOfStudent > 0) {
				string id;
				cout << "Nhap ma sinh vien can xoa: ";
				cin >> id;
				Student student(id);
				bool isRemoved = removeElement(students, numberOfStudent, student);
				if (!isRemoved) {
					cout << "<== Khong tim thay sinh vien ma \"" << id << "\" ==>\n";
				}
				else {
					cout << "<== Xoa sinh vien thanh cong ==>\n";
				}
			}
			else {
				cout << "<== Danh sach sinh vien rong ==>\n";
			}
			break;
		}
		case 9: {
			if (numberOfSubject > 0) {
				string id;
				cout << "Nhap ma mon hoc can xoa: ";
				cin >> id;
				Subject subject(id);
				bool isRemoved = removeElement(subjects, numberOfSubject, subject);
				if (!isRemoved) {
					cout << "<== Khong tim thay mon hoc ma \"" << id << "\" ==>\n";
				}
				else {
					cout << "<== Xoa mon hoc thanh cong ==>\n";
				}
			}
			else {
				cout << "<== Danh sach mon hoc rong ==>\n";
			}
			break;
		}
		case 10: {
			if (numberOfStudent > 0) {
				sortASC(students, numberOfStudent);
			}
			else {
				cout << "<== Danh sach sinh vien rong ==>\n";
			}
			break;
		}
		case 11: {
			if (numberOfSubject > 0) {
				sortASC(subjects, numberOfSubject);
			}
			else {
				cout << "<== Danh sach mon hoc rong ==>\n";
			}
			break;
		}
		case 12: {
			if (numberOfStudent > 0) {
				string studentId;
				string subjectId;
				cout << "Nhap ma sinh vien: ";
				cin >> studentId;
				cout << "Nhap ma mon hoc: ";
				cin >> subjectId;
				bool isRecordExisted = isTranscriptExisted(transcripts, numberOfTranscript, studentId, subjectId);
				if (isRecordExisted) { // kiểm tra xem sinh viên x với môn học y đã tồn tại trong danh sách bảng điểm chưa
					cout << "<== Thong tin bang diem mon hoc ma \"" << subjectId 
						<< "\" cua sinh vien ma \"" << studentId << "\" da ton tai ==>\n";
				}
				else {
					Student student(studentId);
					int studentIndex = findElementById(students, numberOfStudent, student);
					if (studentIndex == -1) {
						cout << "<== Khong ton tai sinh vien can tim ==>\n";
					}
					else { // đảm bảo sinh viên với mã nhập vào phải tồn tại trước
						Subject sub(subjectId);
						int subjectIndex = findElementById(subjects, numberOfSubject, sub);
						if (subjectIndex == -1) {
							cout << "<== Khong tim thay mon hoc can tim ==>\n";
						}
						else { // đảm bảo cả môn học nhập vào phải tồn tại trước
							student = students[studentIndex];
							sub = subjects[subjectIndex];
							Transcript<Student, Subject> tran(student, sub);
							cin >> tran;
							transcripts[numberOfTranscript++] = tran;
						}
					}
				}
			}
			else {
				cout << "<== Danh sach sinh vien rong ==>\n";
			}
			break;
		}
		case 13: {
			if (numberOfTranscript > 0) {
				for (int i = 0; i < numberOfTranscript; i++)
				{
					transcripts[i].calculateGpa();
				}
				cout << "<== Tinh diem trung binh cho sinh vien trong danh sach hoan tat ==>\n";
			}
			else {
				cout << "<== Danh sach bang diem rong ==>\n";
			}
			break;
		}
		case 14: {
			if (numberOfTranscript > 0) {
				for (int i = 0; i < numberOfTranscript - 1; i++)
				{
					for (int j = numberOfTranscript - 1; j > i; j--) {
						if (transcripts[j].getGpa() > transcripts[j - 1].getGpa()) {
							swap(transcripts[j], transcripts[j - 1]);
						}
					}
				}
				cout << "<== Sap xep danh sach bang diem hoan tat ==>\n";
			}
			else {
				cout << "<== Danh sach bang diem rong ==>\n";
			}
			break;
		}
		case 15: {
			if (numberOfTranscript > 0) {
				cout << "=========================================="
					<< " DANH SACH BANG DIEM SINH VIEN "
					<< "==========================================\n";
				showTranscriptInfoHeader();
				for (int i = 0; i < numberOfTranscript; i++)
				{
					cout << transcripts[i];
				}
			}
			else {
				cout << "<== Danh sach bang diem rong ==>\n";
			}
			break;
		}
		case 16: {
			if (numberOfStudent > 0) {
				saveToFile(students, numberOfStudent, studentFile);
				cout << "<== Ghi file sinh vien hoan tat ==>\n";
			}
			else {
				cout << "<== Danh sach sinh vien rong ==>\n";
			}
			if (numberOfSubject > 0) {
				saveToFile(subjects, numberOfSubject, subjectFile);
				cout << "<== Ghi file mon hoc hoan tat ==>\n";
			}
			else {
				cout << "<== Danh sach mon hoc rong ==>\n";
			}
			if (numberOfTranscript > 0) {
				saveToFile(transcripts, numberOfTranscript, transcriptFile);
				cout << "<== Ghi file bang diem hoan tat ==>\n";
			}
			else {
				cout << "<== Danh sach bang diem rong ==>\n";
			}
			break;
		}
		default:
			cout << "SAI CHUC NANG, VUI LONG KIEM TRA LAI\n";
			break;
		}
	} while (choice != 0);

	return 0;
}
icon mochi
 