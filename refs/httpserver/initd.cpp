#ifdef __linux
#include <iostream>
#include <unistd.h>
#include <signal.h>
#include <sys/param.h>
#include <sys/types.h>
#include <sys/stat.h>

void sighandler(int signum)
{
    if(SIGUSR1 == signum)
    {
        std::cout << "catched external stop signal, now stop the server...\n";
        
        std::cout << "post stop signals to server sucessfully.\n";
    }
}

void sinitd(void)
{
    signal(SIGHUP, sighandler);
    signal(SIGUSR1, sighandler);
}

void pinitd(void)
{
    int pid;
    int i;
    if(pid = fork())
    {
        exit(0);        //�Ǹ����̣�����������
    }
    else if( pid < 0)
    {
        exit(1);        //forkʧ�ܣ��˳�
    }
    //�ǵ�һ�ӽ��̣���̨����ִ��
    setsid();           //��һ�ӽ��̳�Ϊ�µĻỰ�鳤�ͽ����鳤
    //��������ն˷���
    if(pid = fork())
    {
        exit(0);        //�ǵ�һ�ӽ��̣�������һ�ӽ���
    }
    else if(pid < 0)
    {
        exit(1);        //forkʧ�ܣ��˳�
    }
    //�ǵڶ��ӽ��̣�����
    //�ڶ��ӽ��̲����ǻỰ�鳤
    for(i=0;i< NOFILE;++i)  //�رմ򿪵��ļ�������
    {
        close(i);
    }

    chdir("/tmp");      //�ı乤��Ŀ¼��/tmp
    umask(0);           //�����ļ�������ģ
    return;
}

// daemon(0, 0)
#endif
