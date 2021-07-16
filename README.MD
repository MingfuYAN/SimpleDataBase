# SDB

## 运行环境

c++11 MinGW64

## 注意

运行过程中，会在程序目录下生成sdb.mf 文件，里面存储成功执行的语句，用于恢复数据库中的内容

登录密码为 `******`

## 支持的语法
> "create", "use", "show", "insert", "update", "delete", "select"
```sql
create database dbname;
create table tbname (
    colname Type ,
    colname1 Type ,
) ;
use dbname; 
show datebase; 
show tables; 
show tables from dbname;
show columns from tbname;

insert into tbname ( col1 , col2 , col3 , col4 ) values ( val1 , val2 , val3 , val4 ) ;
update tbname set col = val where col1 = val1;

delete from tbname where col1 = va1l;

select * from tbname where col1 = val1;

```

## 其他支持
创建数据库时，检测数据库是否存在
创建表时，检测该表是否存在
insert支持部分插入
select 语句支持where查找
输出和MySQL基本一样，十分好看
操作成功有语句提示
支持文件存储，即程序重新运行支持恢复之前的运行状态。
## 部分声明的含义

```cpp

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
void putsOption();// 输出前言
string tips();// 提示信息
bool updateRecord(const string &dbname, const string &tbname, const int &recordID, const vector<string> &key,
                  const vector<string> &value); // 更新记录
const vector<string>key1 = {
        "create"
        ,"use"
        ,"show"
        ,"insert"
        ,"update"
        ,"delete"
        ,"drop"
        ,"select"};
const vector<string>creat_val = { "database", "table"};
const vector<string>col_type = {"int", "string"};
```



## 正确执行的sql语句示例

```sql

create database d1 ; 
create database d2 ; 
show databases ; 
use d1 ;
create table t1 ( a int , b int , c int ) ;
create table t2 ( d int , e int , f int ) ;
show tables ; 
use d2 ;
create table tt1 ( aa int , bb int , cc int ) ;
create table tt2 ( dd int , ee int , ff int ) ;
show tables ; 
show tables from d1 ; 
use d1 ; 
show tables ; 
show columns from t1 ; 
show columns from t2 ;
insert into t1 ( a , b , c ) values ( 1 , 2 , 3 ) ;
insert into t1 ( a , c ) values ( 2 , 3 ) ;
insert into t1 ( b , c ) values ( 2 , 3 ) ;
select * from t1 ;
select a from t1 ;
select b , c from t1 ;
select a , c from t1 ;
select * from t1 where b = 2 ;
select * from t1 ;
delete from t1 where b = null ;
select * from t1 ;
update t1 set a = 2 where a = null ;
select * from t1 ;
update t1 set a = 2 where c = 3 ;
select * from t1 ;
show databases ; 
use d1 ; 
show tables ;
select * from t1 ;

```
