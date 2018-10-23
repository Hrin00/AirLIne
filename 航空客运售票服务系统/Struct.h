#include <cstring>
using namespace std;
//预约信息
typedef struct appo{
    appo *next;
    char name[50];
    int need;
}appo;
typedef struct{
    appo *front;
    appo *rear;
}LinkQueue;
//乘客信息
typedef struct pass{
    pass *next;
    char name[50];
    char pid[50];
    int sid;
}pass;
//座位
typedef struct seat
{
    int s[11][7];      
}seat;
//航班信息
typedef struct Flight_info{
    char start[50];
    char finish[50];
    char flightid[20];
    char date[20];
    int quota;
    int residue;
    int apponum;
    int seat[11][7]; //横坐标1-2为头等舱,3-5为商务舱,5-10为经济舱
    pass *pass; //带头节点的单链表
    appo *appo; //带头节点的单链表
}Flight_info;
typedef struct{
    int size;
    Flight_info *elem;
}List;
