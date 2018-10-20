// ���� ifdef ���Ǵ���ʹ�� DLL �������򵥵�
// ��ı�׼�������� DLL �е������ļ��������������϶���� MYPROCESS_EXPORTS
// ���ű���ġ���ʹ�ô� DLL ��
// �κ�������Ŀ�ϲ�Ӧ����˷��š�������Դ�ļ��а������ļ����κ�������Ŀ���Ὣ
// MYPROCESS_API ������Ϊ�Ǵ� DLL ����ģ����� DLL ���ô˺궨���
// ������Ϊ�Ǳ������ġ�
#ifdef MYPROCESS_EXPORTS
#define MYPROCESS_API __declspec(dllexport)
#else
#define MYPROCESS_API __declspec(dllimport)
#endif

#ifdef __cplusplus
extern "C" {
#endif

struct Result_stru 
{
	int x;
	int y;
	int status;
};


MYPROCESS_API int _stdcall process(void* pdata,unsigned int w, unsigned int h ,double* worldx,double* worldy);
MYPROCESS_API double _stdcall calibration(char* filename);
MYPROCESS_API int __stdcall test();
MYPROCESS_API void _stdcall processtest(double* worldx,double* worldy);
MYPROCESS_API void _stdcall buffertt(void* pdata, int w,  int h );


#ifdef __cplusplus
}
#endif