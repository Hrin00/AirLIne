#include <iostream>
#include <cstdlib>
#include <string>

#include "Struct.h"
#include "Header.h"

using namespace std;

int main(int argc, const char * argv[]) {
    List L;                                                     //航班顺序表
    L.elem=(Flight_info *)malloc(300*sizeof(Flight_info));      //为顺序表申请空间
    cout << "--------欢迎使用航空客运售票模拟系统--------" << endl;
    L.size = 0;
    Init(L,L.size);                                             //初始化
    string n;
    while(1)
    {
        cout<<"***********************************"<<endl;
        cout<<"1.查询航班";cout<<"        2.查询乘客信息"<<endl;
        cout<<"3.查询座位";cout<<"        4.订票"<<endl;
        cout<<"5.退票";cout<<"            6.增加航班"<<endl;
        cout<<"7.删除航班";cout<<"        0.退出系统"<<endl;
        cout<<"***********************************"<<endl;
        cout<<"请输入您要执行的步骤:";
        cin >> n;
        if(n == "1"){
            display(L);
        }
        else if(n == "2"){
            displaypass(L);
        }
        else if(n == "3"){
            displayseat(L);
        }
        else if(n == "4"){
            Book(L);
        }
        else if(n == "5"){
            refund(L);
        }
        else if(n == "6"){
            addflight(L);
        }
        else if(n == "7"){
            delflight(L);
        }
        else if(n == "0"){
            writeback(L);
            break;
        }
        else{
            cout<<"输入有误,请重新输入!"<<endl;
        }
    }
    cout<<"--------感谢您使用航空客运售票模拟系统--------"<<endl;
    return 0;
}
