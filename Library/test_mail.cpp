#include "CSendMail.h"
#include "iostream"
using namespace std;


int main()
{
	CSendMail sMailer;
	//    freopen("F://mailfile//out.txt","w+",stdout);

	sMailer.setServerName("mail.stu.ouc.edu.cn");                                                        //����smtp,��"smtp.126.com"
	sMailer.setUserName("skyunv@stu.ouc.edu.cn");                                                                //�����˺�������"****@126.com"
	sMailer.setUserPwd("a1377590675");                                                                //��������
	sMailer.setSenderName("�¼���");                                                                //����������
	sMailer.setSenderAddress("skyunv@stu.ouc.edu.cn");                                                //���������ַ�������˺ŵĵ�ַ,����������˺���"****@126.com"

	sMailer.setReceiver("��������", "1377590675@qq.com");                                            //����ʼ�������
																								 //sMailer.addReceiver("sixbeauty", "sanyue9394@126.com");

																								 //sMailer.AddFilePath("F:\\mailfile\\out.txt");            //��Ӹ���
																								 //    sMailer.AddFilePath("F:/mailfile/libcurl.exp");                                                //��Ӹ���

																								 //���͵�һ���ʼ�
	if (sMailer.Connent())                                                                        //ÿ�η��ʼ�ǰ����Ҫconnect
	{
		if (sMailer.SendMail("CMailSender:����������", "������ٷ����¸�������һҹ�����𣿷��� http://www.sb.com"))            //��һ���ַ������ʼ����⣬�ڶ������ʼ�����
			cout << "�ʼ�������ɣ�";

	}
	else {
		cout << "fal";
	}

	return 0;
}