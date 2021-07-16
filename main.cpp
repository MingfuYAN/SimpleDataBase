
#include <map>
#include <set>
#include <ctime>
#include <cmath>
#include <queue>
#include <stack>
#include <bitset>
#include <cctype>
#include <cstdio>
#include <vector>
#include <utility>
#include <cstdlib>
#include <cstring>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <fstream>

using namespace std;

class Record {
public:
    bool f;
    vector<string> s;

    Record() {
        f = false;
    }

    Record(const vector<string> &v) {
        f = true;
        for (const auto &c : v) {
            s.push_back(c);
        }
    }
};

string DB_NAME;
set<string> tblcata; // 储存所有的数据库的name
map<string, vector<string>> fldcata; // 储存个表名
map<string, map<string, vector<string>>> col; // 储存列名
map<string, map<string, vector<Record>>> record; // 存储每一行的信息
bool createDataBase(const string &dbname); // 创建数据库
bool isExistDbname(const string &dbname); // 查询数据库名是否存在
bool isExistTbname(const string &dbname, const string &tbname); // 查询表名是否存在
bool createTable(const string &dbname, const string &tbname, const vector<string> &colname); // 创建表
bool isExistCol(const string &dbname, const string &tbname, string cc); // 查询列名是否存在
bool
addRecord(const string &dbname, const string &tbname, const vector<string> &key, const vector<string> &value); // 添加记录

vector<string> splitString(const string &s); // 将输入的字符串按空格分隔并返回

bool updateRecord(const string &dbname, const string &tbname, const int &recordID, const vector<string> &key,
                  const vector<string> &value); // 更新记录

bool isExistDbname(const string &dbname) {
    return tblcata.find(dbname) != tblcata.end();
}

bool createDataBase(const string &dbname) {
    if (isExistDbname(dbname)) {
        cout << "Database " << dbname << " already exists" << endl;
        return false;
    }
    tblcata.insert(dbname);
    cout << "Create database " << dbname << " successfully" << endl;
    return true;
}

bool isExistTbname(const string &dbname, const string &tbname) {
    for (const auto &c : fldcata[dbname]) {
        if (c == tbname) return true;
    }
    return false;
}

bool createTable(const string &dbname, const string &tbname, const vector<string> &colname) {
    if (!isExistDbname(dbname)) {
        cout << "Database " << dbname << " does not exist" << endl;
        return false;
    }
    if (isExistTbname(dbname, tbname)) {
        cout << "Table " << tbname << " already exists in database " << dbname << endl;
        return false;
    }
    fldcata[dbname].push_back(tbname);
    for (const auto &c : colname) {
        col[dbname][tbname].push_back(c);
    }
    cout << "Created table " << tbname << " successfully" << endl;
    return true;
}

bool isExistCol(const string &dbname, const string &tbname, string cc) {
    for (const auto &c : col[dbname][tbname]) {
        if (c == cc) return true;
    }
    return false;
}

bool addRecord(const string &dbname, const string &tbname, const vector<string> &key, const vector<string> &value) {
    //    cout << key.size() << " " << value.size() << "\n";
    //    for (auto c : key) cout << c << " ";
    //    puts("");
    //    for (auto c : value) cout << c << " ";
    //    puts("");

    if (!isExistDbname(dbname)) {
        cout << "Database " << dbname << " does not exist" << endl;
        return false;
    }
    if (!isExistTbname(dbname, tbname)) {
        cout << "Table " << tbname << " does not exist " << dbname << endl;
        return false;
    }

    for (auto c : key) {
        if (!isExistCol(dbname, tbname, c)) {
            cout << "Column " << c << " does not exist in table " << tbname << " of database " << dbname << endl;
            return false;
        }
    }
    if (key.size() != value.size()) {
        cout << "key's length and value's length are not equal" << endl;
        return false;
    }
    map<string, string> tmpma;
    for (int i = 0; i < key.size(); ++i) {
        tmpma[key[i]] = value[i];
    }
    vector<string> tmpve;
    for (auto c : col[dbname][tbname]) {
        tmpve.push_back(tmpma[c]);
    }
    bool isAddSuss = false;
    for (auto &c : record[dbname][tbname]) {
        if (!c.f) {
            c = Record(tmpve);
            isAddSuss = true;
            break;
        }
    }
    if (!isAddSuss) {
        record[dbname][tbname].push_back(Record(tmpve));
    }
    for (auto &c : record[dbname][tbname]) {
        for (int i = 0; i < c.s.size(); ++i) {
            if (c.s[i] == "") c.s[i] = "null";
        }
    }
    cout << "Add successfully" << endl;
    return true;
}

bool updateRecord(const string &dbname, const string &tbname, const int &recordID, const vector<string> &key,
                  const vector<string> &value) {
    if (!isExistDbname(dbname)) {
        cout << "Database " << dbname << " does not exist" << endl;
        return false;
    }
    if (!isExistTbname(dbname, tbname)) {
        cout << "Table " << tbname << " does not exist " << dbname << endl;
        return false;
    }
    for (auto c : key) {
        if (!isExistCol(dbname, tbname, c)) {
            cout << "Column " << c << " does not exist in table " << tbname << " of database " << dbname << endl;
            return false;
        }
    }
    if (key.size() != value.size()) {
        cout << "key's length and value's length are not equal" << endl;
        return false;
    }
    if (recordID >= record[dbname][tbname].size()) {
        cout << "This record does not exist" << endl;
        return false;
    }
    map<string, string> tmpma;
    for (int i = 0; i < key.size(); ++i) {
        tmpma[key[i]] = value[i];
    }
    vector<string> tmpve;

    for (auto c : col[dbname][tbname]) {
        tmpve.push_back(tmpma[c]);
    }
    int cntt = 0;
    for (auto &c: tmpve) {
        if (c == "") c = record[dbname][tbname][recordID].s[cntt];
        cntt++;
    }
    record[dbname][tbname][recordID] = Record(tmpve);
    cout << "Update successfully" << endl;
    return true;
}

bool deleteRecord(const string &dbname, const string &tbname, const int &recordID) {
    if (!isExistDbname(dbname)) {
        cout << "Database " << dbname << " does not exist" << endl;
        return false;
    }
    if (!isExistTbname(dbname, tbname)) {
        cout << "Table " << tbname << " does not exist " << dbname << endl;
        return false;
    }
    if (recordID >= record[dbname][tbname].size()) {
        cout << "This record does not exist" << endl;
        return false;
    }


    // 直接移除vector
    int cnt = 0;
    int flag = 0;

    for (auto i = record[dbname][tbname].begin(); i != record[dbname][tbname].end(); ++i) {
        if (cnt == recordID) {
            record[dbname][tbname].erase(i);
            flag = 1;
            break;
        }
        cnt++;
    }


    if (flag) {
        cout << "Delete successfully" << endl;
        return true;
    } else {
        cout << "Delete error" << endl;
        return false;

    }


}


const vector<string> key1 = {"create", "use", "show", "insert", "update", "delete", "drop", "select"};
const vector<string> creat_val = {"database", "table"};

int findvector(vector<string> s, string a) {
    int id = 0;
    if (s.empty()) return -1;
    for (auto c : s) {
        if (c == a) {
            return id;
        }
        id++;
    }
    return -1;
}

void show(string s, vector<string> ve) {
    int mxlen = s.length();
    for (auto c : ve) {
        if (mxlen < c.length()) mxlen = c.length();
    }
    mxlen += 2;
    cout << "+";
    for (int i = 1; i <= mxlen; ++i) cout << "-";
    cout << "+\n";
    int tmplen = s.length();
    cout << "| " << s;
    for (int i = 1; i <= mxlen - 1 - tmplen; ++i) cout << " ";
    cout << "|\n";
    cout << "+";
    for (int i = 1; i <= mxlen; ++i) cout << "-";
    cout << "+\n";
    for (auto c : ve) {
        tmplen = c.length();
        cout << "| " << c;
        for (int i = 1; i <= mxlen - 1 - tmplen; ++i) cout << " ";
        cout << "|" << endl;
    }
    cout << "+";
    for (int i = 1; i <= mxlen; ++i) cout << "-";
    cout << "+" << endl;
}

void showtable(vector<string> key, vector<string> val[], int vallen) {
    vector<int> len;
    int keylen = key.size();
    for (int i = 0; i < keylen; ++i) {
        len.push_back(key[i].length());
        for (int j = 0; j < vallen; ++j) {
            if (len[i] < val[j][i].length()) len[i] = val[j][i].length();
        }
        len[i] += 2;
    }
    // 1
    cout << "+";
    for (auto c : len) {
        for (int i = 1; i <= c; ++i) cout << "-";
        cout << "+";
    }
    cout << "\n";
    // 2
    cout << "| ";
    for (int i = 0; i < keylen; ++i) {
        cout << key[i];
        for (int j = 1; j <= len[i] - 1 - key[i].length(); ++j) {
            cout << " ";
        }
        cout << "| ";
    }
    cout << endl;
    // 3

    cout << "+";
    for (auto c : len) {
        for (int i = 1; i <= c; ++i) cout << "-";
        cout << "+";
    }
    cout << endl;

    // 4

    for (int i = 0; i < vallen; ++i) {
        cout << "| ";
        for (int j = 0; j < keylen; ++j) {
            cout << val[i][j];
            for (int k = 1; k <= len[j] - 1 - val[i][j].length(); ++k) cout << " ";
            cout << "| ";
        }
        cout << endl;
    }


    if (!vallen) return;
    // end
    cout << "+";
    for (auto c : len) {
        for (int i = 1; i <= c; ++i) cout << "-";
        cout << "+";
    }
    cout << endl;
}

int handle(vector<string> s) {
//    {
//        cout << "test_handle_start" << endl;
//        for (auto c : s){
//            cout << c <<" ";
//        }
//        cout << "\n";
//        cout << "test_handle_end" << endl;
//    }
    if (s[0] == "exit") return 0;
    int slen = s.size();
    int errorflag = -1;
    if (slen == 0) {
        return errorflag;//-1
    }
    errorflag--;
    for (auto &c : s) {
        transform(c.begin(), c.end(), c.begin(), ::tolower); // 全转化为小写
    }


    int key1id = findvector(key1, s[0]);
    if (key1id == -1) {
        return errorflag;//-2
    }
    errorflag--;
    // create
    if (key1id == 0) {
        if (slen == 1) return false;
        int key2id = findvector(creat_val, s[1]);
        if (key2id == -1) {
            return errorflag;//-3
        }
        errorflag--;
        if (key2id == 0) { // database
            if (slen != 4) {
                return errorflag;// -4
            }
            errorflag--;
            if (createDataBase(s[2])) {
                // 2020年11月19日20:23:03
                return true;
            } else {
                return errorflag;
            }
            errorflag--;
        } else if (key2id == 1) { // table
            // 2020年11月22日之后不写错误示例
            string dbname = DB_NAME;
            string tbname = s[2];
            if (isExistTbname(dbname, tbname)) {
                return errorflag;//-4
            }
            errorflag--;
            vector<string> tmp; // 储存变量名称
            tmp.push_back(s[4]);
            int cnt = 4;
            while (cnt + 3 < slen - 1) {
                cnt += 3;
                tmp.push_back(s[cnt]);
            }
            if (createTable(DB_NAME, tbname, tmp)) {
                return true;
            } else {
                return errorflag;
            }
            errorflag--;
        }
    }
        // use
    else if (key1id == 1) {
        if (!isExistDbname(s[1])) {
            cout << "Database " << s[1] << " not exist!" << endl;
            return errorflag;
        } else {
            errorflag--;

            DB_NAME = s[1];
            cout << "Database changed" << endl;
            return true;
        }
    }
        // show
    else if (key1id == 2) {
        if (s[1] == "databases") {
            string tmps = "Database";
            vector<string> tmpv;
            for (auto c : tblcata) {
                tmpv.push_back(c);
            }
            show(tmps, tmpv);
            return true;
        } else if (s[1] == "tables") {
            string tmps = "Tables_in_";
            vector<string> tmpv;
            string tmpdbname = DB_NAME;
            if (slen > 3) {
                tmpdbname = s[3];
            }
            if (!isExistDbname(tmpdbname)) {
                cout << "Database " << tmpdbname << " not exist!" << endl;;
                return errorflag;
            } else {
                errorflag--;
                tmps = "Tables_in_" + tmpdbname;
                for (auto c : fldcata[tmpdbname]) {
                    tmpv.push_back(c);
                }
                show(tmps, tmpv);
                return true;
            }
        } else if (s[1] == "columns") {
            string dbname = DB_NAME;
            string tbname = s[3];
            vector<string> key;
            for (auto c: col[dbname][tbname]) {
                key.push_back(c);
            }
            vector<string> tmpvv[0];
            showtable(key, tmpvv, 0);
            return true;
        } else {
            return errorflag;
        }
        errorflag--;
    }
        // insert
    else if (key1id == 3) {
        vector<string> tmpkey;
        vector<string> tmpv;
        string dbname = DB_NAME;
        string tbname = s[2];
        if (!isExistTbname(dbname, tbname)) {
            return errorflag;
        }
        errorflag--;
        int cnt = 4;
        for (int i = cnt; i < slen; ++i) {
            if (s[i] == ")") {
                cnt = i + 1;
                break;
            }
            if (s[i] == ",") continue;
            tmpkey.push_back(s[i]);

        }
        if (s[cnt] != "values") {
            return errorflag;
        }
        errorflag--;
        cnt += 2;
        for (int i = cnt; i < slen; ++i) {
            if (s[i] == ")") break;
            if (s[i] == ",") continue;
            tmpv.push_back(s[i]);
        }
        if (addRecord(dbname, tbname, tmpkey, tmpv)) {
            return true;
        } else {
            return errorflag;
        }
        errorflag--;
    }
        // update
    else if (key1id == 4) {
        string dbname = DB_NAME;
        string tbname = s[1];
        if (!isExistTbname(dbname, tbname)) {
            return errorflag;
        }
        errorflag--;
        if (s[2] != "set" || s[6] != "where") {
            return errorflag;
        }
        errorflag--;
        vector<string> tmpk;
        vector<string> tmpv;
        tmpk.push_back(s[3]);
        tmpv.push_back(s[5]);
        int colid = -1, cnt = 0;
        for (auto c : col[dbname][tbname]) {
            if (c == s[7]) {
                colid = cnt;
                break;
            }
            cnt++;
        }
        cnt = 0;
        for (auto c : record[dbname][tbname]) {
            if (c.s[colid] == s[9]) {
                updateRecord(dbname, tbname, cnt, tmpk, tmpv);
            }
            cnt++;
        }
        return true;
    }
        // delete
    else if (key1id == 5) {
        string dbname = DB_NAME;
        string tbname = s[2];
        if (!isExistTbname(dbname, tbname)) {
            return errorflag;
        }
        errorflag--;
        if (s[3] != "where") {
            return errorflag;
        }
        errorflag--;
        string colname = s[4];
        string colvalus = s[6];

        int colid = -1, cnt = 0;
        for (auto c : col[dbname][tbname]) {
            if (c == colname) {
                colid = cnt;
                break;
            }
            cnt++;
        }
        cnt = 0;
        int cntf = 0;
        vector<int> delid;
        for (auto c : record[dbname][tbname]) {
            if (c.s[colid] == colvalus) {
                delid.push_back(cnt - cntf);
                cntf++;
            }
            // 2020年11月23日 delete 迭代器出问题
            cnt++;
        }
        for (auto c : delid) {
            deleteRecord(dbname, tbname, c);
        }
        return true;
    }
        // drop
    else if (key1id == 6) {
        // 暂未实现，咕咕咕
    }
        // select
    else if (key1id == 7) {
        string dbname = DB_NAME;
        string tbname;
        vector<string> tmpk;
        int cnt = 1;
        for (int i = cnt; i < slen; ++i) {
            if (s[i] == "from") {
                cnt = i;
                break;
            }
            if (s[i] == ",") {
                continue;
            }
            tmpk.push_back(s[i]);
        }
        cnt++;
        tbname = s[cnt];
        if (!isExistTbname(dbname, tbname)) {
            return errorflag;
        }
        errorflag--;
        int recordlen = record[dbname][tbname].size();

        vector<string> tmpv[recordlen];
        if (tmpk[0] == "*") {
            tmpk.clear();
            for (auto c : col[dbname][tbname]) {
                tmpk.push_back(c);
            }
        }

//        {
//            for (auto c: tmpk){
//                cout << c << " ";
//            }
//            cout << "\n";
//        }

        cnt++;
        vector<int> recid;
        if (s[cnt] != ";") {
            if (s[cnt] != "where") {
                return errorflag;
            }
            errorflag--;

            string colname = s[cnt + 1];
            string colvalus = s[cnt + 3];

            int colid = -1, cnt = 0;
            for (auto c : col[dbname][tbname]) {
                if (c == colname) {
                    colid = cnt;
                    break;
                }
                cnt++;
            }
            cnt = 0;
            for (auto c : record[dbname][tbname]) {
                if (c.s[colid] == colvalus) {
                    recid.push_back(cnt);
                }
                cnt++;
            }
        } else {
            for (int i = 0; i < recordlen; ++i) recid.push_back(i);
        }
        int cnt1 = 0, cnt2 = 0, cnt3 = 0;

        for (auto c : col[dbname][tbname]) {
            cnt3 = 0;
            if (c == tmpk[cnt2]) {

                for (auto i : recid) {
                    tmpv[cnt3++].push_back(record[dbname][tbname][i].s[cnt1]);
                }
                cnt2++;
                if (cnt2 == tmpk.size()) break;
            }
            cnt1++;
        }
        showtable(tmpk, tmpv, recid.size());
        return true;
    } else {
        return errorflag;
    }
    return 123456;

}

void fileread() {
    ifstream infile;
    infile.open("sdb.mf", ios::in);

    vector<string> tmp;
    string ts;
    while (infile >> ts) {
        if (ts != ";") tmp.push_back(ts);
        else {
            tmp.push_back(";");
            handle(tmp);
            system("cls");
            tmp.clear();
        }
    }
    infile.close();
}

bool flagfirst = true;

string sen;

// 输入并拆分
vector<string> input() {
    string tmp;
    vector<string> s;
    cout << "SDB > ";

    while (getline(cin, tmp)) {
        if (tmp == "" && flagfirst) {
            flagfirst = false;
            continue;
        }
        flagfirst = false;
        istringstream is(tmp);
        string tmp1;
        bool flag = true;
        while (is >> tmp1) {
            if (tmp1 == ";") {
                s.push_back(";");
                sen = "";
                for (auto c : s) sen += c, sen += " ";
                sen += "\n";
                return s;
            } else if (tmp1.back() == ';') {
                tmp1.pop_back();
                s.push_back(tmp1);
                s.push_back(";");
                sen = "";
                for (auto c : s) sen += c, sen += " ";
                sen += "\n";
                return s;
            } else if (tmp1 == "^c") {
                cout << "SDB > ";
                flagfirst = true;
                s.clear();
                flag = false;
                break;
            } else {
                s.push_back(tmp1);
            }
        }
        if (flag) cout << "   -> ";
    }
}

int main() {
    cout << "Welcome to SDB..." << endl;
    cout << "Please input password : ";
    while (true) {
        string psd;
        cin >> psd;
        if (psd == "******") {
            cout << "Password correct" << endl;
            break;
        } else {
            cout << "Password error, please input again: " << endl;
        }
    }
    fileread();

    while (true) {
        int flag = handle(input());
        if (flag > 0) {
            ofstream outfile;
            outfile.open("sdb.mf", ios::app | ios::out);
            outfile << sen;
            outfile.close();
        } else if (flag == 0) break;
        else {
            cout << "error" << endl;
        }
    }
    cout << "Bye Bye~" << endl;;
    system("pause");
    return 0;
}