
#include "stdio.h"
#include "sys/types.h"
#include "sys/socket.h"
#include "netinet/in.h"
#include "unistd.h"
#include "string.h"

#define BUF_LEN 128

struct s_alive {
    unsigned short CID;
    unsigned short LENGTH;
    unsigned char ID[12];
    unsigned char mainsys;
    unsigned char mainradar;
    unsigned char subsys;
    unsigned char subradar;
    unsigned int CRC32;
};

union u_alive {
    struct s_alive s_alive_data;
    char c_alive_data[24];
};
 
void main(int argc, char *argv[])
{
        int s, n;
        char *haddr;
        struct sockaddr_in server_addr;
        union u_alive data;

        data.s_alive_data.CID = 0x104;
        data.s_alive_data.LENGTH = 0;
        memcpy(data.s_alive_data.ID, "           1", 12) ;
        data.s_alive_data.mainsys = 0;
        data.s_alive_data.mainradar = 0;
        data.s_alive_data.subsys = 0;
        data.s_alive_data.subradar = 0;
        data.s_alive_data.CRC32 = 0;


        char buf[BUF_LEN+1];

 
        if((s = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        {//소켓 생성과 동시에 소켓 생성 유효검사
                printf("can't create socket\n");
        }
 
        bzero((char *)&server_addr, sizeof(server_addr));
        //서버의 소켓주소 구조체 server_addr을 NULL로 초기화
 
        server_addr.sin_family = AF_INET;
        //주소 체계를 AF_INET 로 선택
        server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
        //32비트의 IP주소로 변환
        server_addr.sin_port = htons(5600);
        //daytime 서비스 포트 번호
 
        if(connect(s, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
        {
                printf("can't connect.\n");
        }
        printf("connected");
	int cnt = 0;
        int first = 0; 
        while(1)
        {
                usleep(5000000);
        	data.s_alive_data.LENGTH = cnt;
                if (cnt == 0) data.s_alive_data.mainsys = 1;
		if (cnt == 1) data.s_alive_data.mainradar = 1;
		if (cnt == 2) data.s_alive_data.subsys = 1;
		if (cnt == 3) data.s_alive_data.subradar = 1;
		if (cnt == 4) {
			data.s_alive_data.subradar = 0;
			data.s_alive_data.subsys = 0;
			data.s_alive_data.mainradar = 0;
			data.s_alive_data.mainsys = 0;
		}
                send(s, data.c_alive_data, sizeof(data.c_alive_data), 0);
		cnt = cnt + 1;
		if (cnt == 6) {
			cnt = 0;
		}
                
        }
 
        close(s);
        //사용이 완료된 소켓을 닫기
}
