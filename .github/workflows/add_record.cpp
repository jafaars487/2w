#include <iostream>
#include <OpenXLSX.hpp>
#include <ctime>
#include <string>

using namespace OpenXLSX;
using namespace std;

string get_current_time() {
    time_t now = time(0);
    tm *ltm = localtime(&now);
    char buffer[20];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", ltm);
    return string(buffer);
}

void add_record(const string &filename, const string &date, double profit, double balance, double zain_cash, double taif, const string &notes) {
    XLDocument doc;
    try {
        doc.open(filename);
    } catch (...) {
        doc.create(filename);
        doc.workbook().addWorksheet("Sheet1");
    }
    auto wks = doc.workbook().worksheet("Sheet1");
    auto row = wks.rowCount() + 1;
    if (row == 1) {
        wks.cell(XLCellReference(1, 1)).value() = "التاريخ";
        wks.cell(XLCellReference(1, 2)).value() = "الربح";
        wks.cell(XLCellReference(1, 3)).value() = "الرصيد";
        wks.cell(XLCellReference(1, 4)).value() = "زين كاش";
        wks.cell(XLCellReference(1, 5)).value() = "الطيف";
        wks.cell(XLCellReference(1, 6)).value() = "الملاحظات";
        row++;
    }
    wks.cell(XLCellReference(row, 1)).value() = date;
    wks.cell(XLCellReference(row, 2)).value() = profit;
    wks.cell(XLCellReference(row, 3)).value() = balance;
    wks.cell(XLCellReference(row, 4)).value() = zain_cash;
    wks.cell(XLCellReference(row, 5)).value() = taif;
    wks.cell(XLCellReference(row, 6)).value() = notes;
    doc.save();
    doc.close();
}

int main() {
    string filename = "records.xlsx";
    string current_time = get_current_time();
    add_record(filename, current_time, 100, 500, 200, 50, "ملاحظات جديدة");

    cout << "تم حفظ السجل بنجاح." << endl;
    cin.get(); // ينتظر حتى يتم الضغط على Enter للخروج
    return 0;
}
