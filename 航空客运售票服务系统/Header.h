void Init(List &L,int &count);
void refund(List &L);
void writeback(List L ,int count);
void display(List L);
void appoint(List &L,int count,int tcount);
void displayseat(List L);
void displayT(List L,int i);
void displayJ(List L,int i);
void Book(List &L);
void book(List &L ,int count , int tcount);  //count表示航班  tcount表示预定人数  book(订票中实际用于订票的模块)
void refund_appo(List &L, int count);//退票后联系预约客户
void displaypass(List L);
void addflight(List &L);
void delflight(List &L);

void refund(List &L){
    cout<<"--------欢迎使用退票系统--------"<<endl;
    while(1){
        cout<<"1.退票"<<endl;
        cout<<"0.返回"<<endl;
        cout<<"请输入您要执行的步骤:";
        string n;
        cin >> n;
        if(n == "1"){
            char str[20];
            char date[20];
            cout<<"请您输入要退票的航班号:";
            cin >> str;
            cout<<"请您输入该航班的日期:";
            cin >> date;
            int count = -1;
            for(int i = 0; i < L.size; i++){
                if(strcmp(str, L.elem[i].flightid) == 0 && strcmp(date, L.elem[i].date) == 0){
                    count = i;
                    break;
                }
            }
            if(count == -1){
                cout<<"退票失败,无此航班!"<<endl;
                continue;
            }
            int tcount;              //票数
            cout<<"请您输入要退的票数:";
            cin >> tcount;
            cin.clear();
            cin.sync();
            if(tcount > (L.elem[count].quota - L.elem[count].residue) ){
                cout<<"退票失败,输入有误,已超出总订票人数!"<<endl;
                continue;
            }
            if(tcount <= 0){
                cout<<"退票失败,输出有误,请输出正确的票数!"<<endl;
                continue;
            }
            
            int flag = 0;
            cout<<"请依次输入"<<tcount<<"个人的信息"<<endl;
            for(int i = 0; i < tcount; i++){
                pass *ckp1,*ckp2;
                char name[50],pid[50];
                int sid = 0;
                cout<<"请输入第"<<i+1<<"个乘客的姓名:";
                cin >> name;
                cout<<"请输入第"<<i+1<<"个乘客的身份证号:";
                cin >> pid;
                ckp1 = L.elem[count].pass->next;
                ckp2 = L.elem[count].pass;
                while(ckp1){
                    if(strcmp(pid, ckp1->pid) == 0)
                        if(strcmp(name, ckp1->name) == 0){
                            sid = ckp1->sid ;
                            ckp2->next = ckp2->next->next;
                            free(ckp1);
                            
                            
                            int x,y;
                            x = sid / 6 + 1;
                            y = sid % 6;
                            if(y == 0){
                                x--;
                                y = 6;
                            }
                            L.elem[count].seat[x][y] = 0;
                            
                            L.elem[count].residue ++;
                            flag = 1;
                            break;
                        }
                    ckp2 = ckp1;
                    ckp1 = ckp1->next;
                }
                if(sid != 0)
                    cout<<"客户"<<name<<"已成功退票!"<<endl;
                else
                    cout<<"退票失败,没有搜索到客户"<<name<<"信息"<<endl;
            }
            if(flag == 1)
                refund_appo(L, count);  //退票后联系预约客户
        }
        else if(n == "0"){
            return;
        }
        else{
            cout<<"输入有误,请重试!"<<endl;
        }
    }
}
void refund_appo(List &L, int count){
    while(1){
        appo *yyf,*yyr,*yyp1,*yyp2;         //yyr队列头  yyr队列尾  yyp1 yyp2 做删除的2个指针
        yyf = L.elem[count].appo;
        yyr = yyf;
        while(yyr->next){
            yyr = yyr->next;
        }
        int flag = 0;
        yyp1 = yyf;
        yyp2 = yyf->next;
        while(yyp2){
            if(yyp2->need <= L.elem[count].residue){
                cout<<"找到可订票的预约乘客"<<yyp2->name<<",下面开始为该乘客订票"<<endl;
                yyp1->next = yyp1->next->next;
                book(L, count, yyp2->need);
                free(yyp2);
                L.elem[count].apponum--;
                flag = 1;
            }
            
            if(flag == 1)
                break;
            
            yyp1 = yyp2;
            yyp2 = yyp2->next;
        }
        
        if(flag == 0){
            cout<<"已为可订票的预约用户订票!"<<endl;            //把所有可订票客户订票后输出  所以flag是0 而不是1
            return;
        }
    }
}
void appoint(List &L,int count,int tcount){
    cout<<"--------欢迎使用预约系统--------"<<endl;
    appo *yyp = L.elem[count].appo;
    appo *yynew;
    while(yyp->next){
        yyp=yyp->next;
        yynew = yyp;
    }
    yynew = new appo;
    yynew->next = NULL;
    cout<<"请输入您的名字:";
    cin >> yynew->name;
    cout<<"下面开始为您预约"<<tcount<<"张票"<<endl;
    yynew->need = tcount;
    cin.clear();
    cin.sync();
    if(yynew->need <= 0 || yynew->need > L.elem[count].quota){
        cout<<"预约失败,您的预约人数有误或超过飞机定额!"<<endl;
        return;
    }
    yyp->next = yynew;
    yyp = yyp->next;
    L.elem[count].apponum ++;
    cout<<"您的预约已完成,我们会在有座位的第一时间通知您!"<<endl;
}
void book(List &L ,int count , int tcount){
    cout<<"请依次输入"<<tcount<<"个人的信息"<<endl;
    pass *ckp = L.elem[count].pass;
    pass *cknew;
    while(ckp->next){
        ckp=ckp->next;
        cknew = ckp;
    }
    for(int i = 0; i < tcount; i++){
        cknew = new pass;
        cknew->next = NULL;
        cout<<"请输入第"<<i+1<<"个乘客的姓名:";
        cin >> cknew->name;
        cout<<"请输入第"<<i+1<<"个乘客的身份证号:";
        cin >> cknew->pid;
        while(1){
            cout<<"1.头等舱"<<endl;
            cout<<"2.经济舱"<<endl;
            cout<<"请选择第"<<i+1<<"个乘客要订的舱室:";
            string cabin;
            cin >> cabin;
            int sid;
            if(cabin == "1"){
                displayT(L, count);
                cout<<"请输入座位号:";
                cin >> sid;
                cin.clear();
                cin.sync();
                if(sid > 12 || sid < 1){
                    cout<<"订票失败,座位号输入有误"<<endl;
                    continue;
                }
                int x,y;
                x = sid / 6 + 1;
                y = sid % 6;
                if(y == 0){
                    x--;
                    y = 6;
                }
                if(L.elem[count].seat[x][y] == 1){
                    cout<<"订票失败,该座位已被预定!"<<endl;
                    continue;
                }
                else if(L.elem[count].seat[x][y] == 0){
                    L.elem[count].seat[x][y] = 1;
                    cknew->sid = sid;
                    cout<<"订票成功!"<<endl;
                    break;
                }
            }
            else if(cabin == "2"){
                displayJ(L, count);
                cout<<"请输入座位号:";
                cin >> sid;
                if(sid > 48 || sid < 1){
                    cout<<"订票失败,座位号输入有误"<<endl;
                    continue;
                }
                int x,y;
                x = sid / 6 + 3;
                y = sid % 6;
                if(y == 0){
                    x--;
                    y = 6;
                }
                if(L.elem[count].seat[x][y] == 1){
                    cout<<"订票失败,该座位已被预定!"<<endl;
                    continue;
                }
                else if(L.elem[count].seat[x][y] == 0){
                    L.elem[count].seat[x][y] = 1;
                    cknew->sid = sid + 12;
                    cout<<"订票成功!"<<endl;
                    break;
                }
                
            }
            else{
                cout<<"订票失败,输入有误"<<endl;
            }
        }
        ckp->next = cknew;
        ckp = ckp->next;
        L.elem[count].residue--;
        
    }
}
void Book(List &L){
    cout<<"--------欢迎使用订票系统--------"<<endl;
    while(1){
        string n;
        cout<<"1.订票"<<endl;
        cout<<"0.返回"<<endl;
        cout<<"请输入您要执行的步骤:";
        cin >> n;
        if(n == "1"){
            char str[20];
            cout<<"请您输入要订票的航班号:";
            cin >> str;
            char date[20];
            cout<<"请您输入该航班的日期:";
            cin >> date;
            int count = -1;
            for(int i = 0; i < L.size; i++){
                if(strcmp(str, L.elem[i].flightid) == 0 && strcmp(date, L.elem[i].date) == 0){
                    count = i;
                    break;
                }
            }
            if(count == -1){
                cout<<"订票失败,无此航班!"<<endl;
                continue;
            }
            
            int tcount;
            cout<<"请您输入要订的票数:";
            cin >> tcount;
            cin.clear();
            cin.sync();
            if(tcount > L.elem[count].residue){
                cout<<"订票失败,航班余座不足!"<<endl;
                while(1){
                    string yyn;
                    cout<<"1.预约"<<endl;
                    cout<<"2.不预约"<<endl;
                    cout<<"请问是否需要预约航班:";
                    cin >> yyn;
                    if(yyn == "1"){
                        appoint(L,count,tcount);
                        break;
                    }
                    else if(yyn == "2"){
                        break;
                    }
                    else{
                        cout<<"输入有误"<<endl;
                        continue;
                    }
                    
                }
                continue;
            }
            if(tcount <= 0){
                cout<<"订票失败,请输入正确的票数!"<<endl;
                continue;
            }
            book(L, count, tcount);
            
        }
        else if(n == "0"){
            return;
        }
        else{
            cout<<"输入有误,请重试!"<<endl;
        }
        
    }
    
}
void displayseat(List L){
    char str[20];
    cout<<"请您输入要查询的航班号:";
    cin >> str;
    char date[20];
    cout<<"请您输入该航班的日期::";
    cin >> date;
    int count = -1;
    for(int i = 0; i < L.size; i++){
        if(strcmp(str, L.elem[i].flightid) == 0 && strcmp(date, L.elem[i].date) == 0){
            count = i;
            break;
        }
    }
    if(count == -1){
        cout<<"查询失败,无此航班!"<<endl;
        return;
    }
    displayT(L,count);
    displayJ(L,count);
    
}
void displayT(List L , int i){
    cout<<"头等舱:"<<endl;
    for(int r = 1; r <= 2 ; r ++){
        for(int c = 1; c <= 6 ; c ++){
            if(L.elem[i].seat[r][c] == 0){
                if((6*(r-1)+c) >= 10)
                    cout<<" "<<6*(r-1)+c;
                else
                    cout<<" "<<0<<6*(r-1)+c;
            }
            else if(L.elem[i].seat[r][c] == 1)
                cout<<" 无";
        }
        cout<<endl;
    }
}
void displayJ(List L,int i){
    cout<<"经济舱:"<<endl;
    for(int r = 3; r <= 10 ; r ++){
        for(int c = 1; c <= 6 ; c ++){
            if(L.elem[i].seat[r][c] == 0){
                if((6*(r-3)+c) >= 10)
                    cout<<" "<<6*(r-3)+c;
                else
                    cout<<" "<<0<<6*(r-3)+c;
            }
            else if(L.elem[i].seat[r][c] == 1)
                cout<<" 无";
        }
        cout<<endl;
    }
}
void display(List L){
    string n;
    cout<<"************************************"<<endl;
    cout<<"   请问您要以何种方式查询航班信息"<<endl;
    cout<<"      1.起始地";cout<<"       2.目的地"<<endl;
    cout<<"      3.日期";cout<<"         4.航班号"<<endl;
    cout<<"      0.返回"<<endl;
    cout<<"************************************"<<endl;
    cout<<"请选择查询方式:";
    cin >> n;
    if(n == "1"){
        int count = L.size;
        pass *ckp;
        appo *yyp;
        char start[50];
        cout<<"请输入起始地:";
        cin >> start;
        cout<<"起点站名    终点站名    航班号码    飞行日期    乘员定额(位)    机票余额(张)    预约记录(条)"<<endl;
        for(int i = 0; i < count; i++){
            if(strcmp(start,L.elem[i].start) == 0){
                cout<<"   "<<L.elem[i].start<<"          ";
                cout<<L.elem[i].finish<<"        ";
                cout<<L.elem[i].flightid<<"       ";
                cout<<L.elem[i].date<<"          ";
                cout<<L.elem[i].quota<<"              ";
                cout<<L.elem[i].residue<<"               ";
                cout<<L.elem[i].apponum<<"          "<<endl;
            }
        }
    }
    else if(n == "2"){
        int count = L.size;
        pass *ckp;
        appo *yyp;
        char finish[50];
        cout<<"请输入目的地:";
        cin >> finish;
        cout<<"起点站名    终点站名    航班号码    飞行日期    乘员定额(位)    机票余额(张)    预约记录(条)"<<endl;
        for(int i = 0; i < count; i++){
            if(strcmp(finish,L.elem[i].finish) == 0){
                cout<<"   "<<L.elem[i].start<<"          ";
                cout<<L.elem[i].finish<<"        ";
                cout<<L.elem[i].flightid<<"       ";
                cout<<L.elem[i].date<<"          ";
                cout<<L.elem[i].quota<<"              ";
                cout<<L.elem[i].residue<<"               ";
                cout<<L.elem[i].apponum<<"          "<<endl;
            }
        }
    }
    else if(n == "3"){
        int count = L.size;
        pass *ckp;
        appo *yyp;
        char date[50];
        cout<<"请输入航班时间(月份.日期):";
        cin >> date;
        cout<<"起点站名    终点站名    航班号码    飞行日期    乘员定额(位)    机票余额(张)    预约记录(条)"<<endl;
        for(int i = 0; i < count; i++){
            if(strcmp(date,L.elem[i].date) == 0){
                cout<<"   "<<L.elem[i].start<<"          ";
                cout<<L.elem[i].finish<<"        ";
                cout<<L.elem[i].flightid<<"       ";
                cout<<L.elem[i].date<<"          ";
                cout<<L.elem[i].quota<<"              ";
                cout<<L.elem[i].residue<<"               ";
                cout<<L.elem[i].apponum<<"          "<<endl;
            }
        }
    }
    
    else if(n == "4"){
        int count = L.size;
        pass *ckp;
        appo *yyp;
        char flight[50];
        cout<<"请输入航班号:";
        cin >> flight;
        cout<<"起点站名    终点站名    航班号码    飞行日期    乘员定额(位)    机票余额(张)    预约记录(条)"<<endl;
        for(int i = 0; i < count; i++){
            if(strcmp(flight,L.elem[i].flightid) == 0){
                cout<<"   "<<L.elem[i].start<<"          ";
                cout<<L.elem[i].finish<<"        ";
                cout<<L.elem[i].flightid<<"       ";
                cout<<L.elem[i].date<<"          ";
                cout<<L.elem[i].quota<<"              ";
                cout<<L.elem[i].residue<<"               ";
                cout<<L.elem[i].apponum<<"          "<<endl;
            }
        }
    }
    else if(n == "0"){
        return;
    }
    else{
        cout<<"输入有误,请重新输入!"<<endl;
    }
}
void Init(List &L,int &count){
    FILE *fp;
    Flight_info hb;
    appo *yyp,*yyf,*yyr; //f:front  r:rear;
    pass *ckp,*cknew,*ckh; //h:head
    cout<<"  --------------程序初始化中--------------"<<endl;
    if((fp = fopen("/Users/mashiro/学习/短学期/大一/航空客运售票模拟系统/航空客运售票服务系统/hangban.txt", "r")) == NULL){
        cout<<"file open error"<<endl;
        exit(1);
    }
    while(!feof(fp)){
        
        if(fscanf(fp, "%s %s %s %s %d %d %d",hb.start,hb.finish,hb.flightid,hb.date,&hb.quota,&hb.residue,&hb.apponum)!=EOF){
            L.elem[count].appo = NULL;
            L.elem[count].pass = NULL;
            strcpy(L.elem[count].start,hb.start);
            strcpy(L.elem[count].finish,hb.finish);
            strcpy(L.elem[count].flightid,hb.flightid);
            strcpy(L.elem[count].date,hb.date);
            L.elem[count].quota = hb.quota;
            L.elem[count].residue = hb.residue;
            L.elem[count].apponum = hb.apponum;
            
            //读取座位表
            int rows = 11;
            int cols = 7;
            for(int r = 0; r < rows; r ++){
                for(int c = 0; c < cols; c ++){
                    fscanf(fp," %d",&L.elem[count].seat[r][c]);
                }
            }
            
            
            ckh = new pass;
            ckh->next = NULL;
            cknew = ckh;
            ckp = ckh;
            L.elem[count].pass = ckh;
            for(int i = 0; i < (L.elem[count].quota - L.elem[count].residue); i++){
                cknew = new pass;
                fscanf(fp, "%s %s %d",cknew->name,cknew->pid,&cknew->sid);
                cknew->next = NULL;
                ckp->next = cknew;
                ckp = ckp->next;
            }
            
            
            
            
            yyf = new appo;
            yyf->next = NULL;
            yyr = yyf;
            yyp = yyf;
            L.elem[count].appo = yyf;
            for(int i = 0; i < L.elem[count].apponum; i++){
                yyp = new appo;
                fscanf(fp, "%s %d",yyp->name,&yyp->need);
                yyp->next = NULL;
                yyr->next = yyp;
                yyr = yyp;
            }
            count++;
            
        }
    }
}
void writeback(List L){
    FILE *fp;
    pass *ckp;
    appo *yyp;
    int count = L.size;
    if((fp = fopen("/Users/mashiro/学习/短学期/大一/航空客运售票模拟系统/航空客运售票服务系统/hangban.txt", "w")) == NULL){
        cout<<"file open error"<<endl;
        exit(1);
    }
    
    for(int i = 0; i < count; i ++){
        /* typedef struct Flight_info{
         char start[50];
         char finish[50];
         char flightid[20];
         char date[20];
         int quota;
         int residue;
         int apponum;
         int seat[11][7]; //横坐标1-2为头等舱,3-5为商务舱,5-10为经济舱
         pass *pass;
         appo *appo;
         }Flight_info;*/
        fprintf(fp, "%s %s %s %s %d %d %d",L.elem[i].start,L.elem[i].finish,L.elem[i].flightid,L.elem[i].date,L.elem[i].quota,L.elem[i].residue,L.elem[i].apponum);
        
        int rows = 11;
        int cols = 7;
        for(int r = 0; r < rows; r ++){
            for(int c = 0; c < cols; c ++){
                fprintf(fp," %d",L.elem[i].seat[r][c]);
            }
        }
        
        ckp = L.elem[i].pass->next;
        while(ckp){
            fprintf(fp, " %s %s %d",ckp->name,ckp->pid,ckp->sid);
            ckp = ckp->next;
        }
        
        yyp = L.elem[i].appo->next;
        while(yyp){
            fprintf(fp, " %s %d",yyp->name,yyp->need);
            yyp = yyp->next;
        }
        fprintf(fp, "\n");
    }
    
}
void displaypass(List L){
    pass *ckp;
    appo *yyp;
    cout<<"请输入您要查询的航班号:";
    char flightid[20];
    cin >> flightid;
    cout<<"请输入该航班的日期:";
    char date[20];
    cin >> date;
    int count = -1;
    for(int i = 0; i < L.size; i++){
        if(strcmp(flightid, L.elem[i].flightid) == 0 && strcmp(date, L.elem[i].date) == 0){
            count = i;
            break;
        }
    }
    if(count == -1){
        cout<<"查询失败,无此航班!!"<<endl;
        return;
    }
    
    cout<<"乘客姓名        "<<"身份证号    "<<"       座位号"<<endl;
    ckp = L.elem[count].pass->next;
    while(ckp){
        if(strcmp((ckp->name)+6,"\0") == 0)
            cout<<" "<<ckp->name<<"       "<<ckp->pid<<"       ";
        else
            cout<<" "<<ckp->name<<"     "<<ckp->pid<<"       ";
        if(ckp->sid <= 12){
            cout <<"T";
            if(ckp->sid >= 10)
                cout<<ckp->sid;
            else
                cout<<0<<ckp->sid;
        }
        else{
            cout <<"J";
            int s = ckp->sid - 12;
            if(s >= 10)
                cout<<s;
            else
                cout<<0<<s;
        }
        cout<<endl;
        ckp = ckp->next;
    }
    cout<<endl;
}
void addflight(List &L){
    pass *ckp;
    appo *yyp;
    char start[50];
    char finish[50];
    char flightid[20];
    char date[20];
    cout<<"请输入起始地:";
    cin >> start;
    cout<<"请输入目的地:";
    cin >> finish;
    cout<<"请输入航班号:";
    cin >> flightid;
    for(int i = 0; i < L.size; i++){
        if(strcmp(flightid, L.elem[i].flightid) == 0 ){
            cout<<"已存在该航班,插入失败!"<<endl;
            return;
        }
    }
    cout<<"请输入日期:";
    cin >> date;
    strcpy(L.elem[L.size].start,start);
    strcpy(L.elem[L.size].finish,finish);
    strcpy(L.elem[L.size].flightid,flightid);
    strcpy(L.elem[L.size].date,date);
    L.elem[L.size].quota = 60;
    L.elem[L.size].residue = 60;
    L.elem[L.size].apponum = 0;
    
    for (int i = 0; i < 11; ++i)
        for (int j = 0; j < 7; ++j) {
            L.elem[L.size].seat[i][j] = 0;
        }
    
    ckp = new pass;
    ckp->next = NULL;
    L.elem[L.size].pass = ckp;
    
    yyp = new appo;
    yyp->next = NULL;
    L.elem[L.size].appo = yyp;
    
    L.size++;
    cout<<"航班插入成功,现在共有"<<L.size<<"个航班!"<<endl;
}
void delflight(List &L){
    char flightid[20];
    char date[20];
    cout<<"请输入航班号:";
    cin >> flightid;
    cout<<"请输入日期:";
    cin >> date;
    
    int count = -1;
    for(int i = 0; i < L.size; i++){
        if(strcmp(flightid, L.elem[i].flightid) == 0 && strcmp(date, L.elem[i].date) == 0){
            count = i;
            break;
        }
    }
    if(count == -1){
        cout<<"删除失败,无此航班!"<<endl;
        return;
    }
    
    for(int i = 0; i < L.size; i++)
        if(i >= count)
            L.elem[i] = L.elem[i+1];
    
    L.size--;
    cout<<"航班删除成功,现在共有"<<L.size<<"个航班!"<<endl;
}
