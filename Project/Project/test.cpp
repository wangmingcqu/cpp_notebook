# include<iostream>
using namespace std;
# include<map>
# include<vector>
# include<string>

//小美有两个数字，其中第一个数字是任意的正整数，第二个数字是一位仅可能为0到9间的整数。
//
//小美希望能将第二个插入第一个数字中，以得到最大的数字。具体可参见输入输出样例

//小美喜欢整理电脑文件路径。但是她不喜欢一层一层查看文件夹。于是她写了一个程序，将文件信息写入了一行类html代码中。
//
//其中“<folder:name1>…<\folder>”表示一个叫name1的文件夹，省略号中可能包括文件夹和文件，“<file:name2\>”表示一个叫name2的文件。
//
//代码中仅有这两种信息，且文件名或文件夹名中保证不包括“ > ”、“ < ”或”\”且不为空，相同文件夹中的文件夹名各不相同，文件名各不相同。
//
//    小美希望清除文件夹中无用的文件夹，即空的文件夹。具体定义为：
//
//    （1） 没有任何文件和文件夹的文件夹是空文件夹
//
//    （2） 只包含空文件夹的文件夹也是空文件夹。
//
//    即当前目录树下没有任何文件的文件夹就是空文件夹。
//
//    小美希望知道有多少空文件夹。
int main1()
{
    int num;
    cin >> num;
    vector<string> n(num);
    vector<int> m(num);
    for (int i = 0; i < num; i++)
    {
        cin >> n[i];
        cin >> m[i];
    }
    for (int i = 0; i < num; i++)
    {
        string temp = n[i];
        int int_n = m[i];
        string::iterator it = temp.begin();
        for (int j = 0; j < temp.size(); j++)
        {
            if (int_n > (int)temp[j])
            {
                cout << "zhixing" << endl;
                temp.insert(it + j, (char)int_n);
            }
        }
        cout << temp << endl;
    }
    /*string a = "1245";
    string::iterator it = a.begin();
    a.insert(it+1, '5');
    cout << a << endl;*/
    return 0;
}