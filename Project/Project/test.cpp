# include<iostream>
using namespace std;
# include<map>
# include<vector>
# include<string>

//С�����������֣����е�һ����������������������ڶ���������һλ������Ϊ0��9���������
//
//С��ϣ���ܽ��ڶ��������һ�������У��Եõ��������֡�����ɲμ������������

//С��ϲ����������ļ�·������������ϲ��һ��һ��鿴�ļ��С�������д��һ�����򣬽��ļ���Ϣд����һ����html�����С�
//
//���С�<folder:name1>��<\folder>����ʾһ����name1���ļ��У�ʡ�Ժ��п��ܰ����ļ��к��ļ�����<file:name2\>����ʾһ����name2���ļ���
//
//�����н�����������Ϣ�����ļ������ļ������б�֤�������� > ������ < ����\���Ҳ�Ϊ�գ���ͬ�ļ����е��ļ�����������ͬ���ļ���������ͬ��
//
//    С��ϣ������ļ��������õ��ļ��У����յ��ļ��С����嶨��Ϊ��
//
//    ��1�� û���κ��ļ����ļ��е��ļ����ǿ��ļ���
//
//    ��2�� ֻ�������ļ��е��ļ���Ҳ�ǿ��ļ��С�
//
//    ����ǰĿ¼����û���κ��ļ����ļ��о��ǿ��ļ��С�
//
//    С��ϣ��֪���ж��ٿ��ļ��С�
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