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



struct point
{
	int x;
	int y;
};



MYPROCESS_API void _stdcall gray2rbg( void *src, void *des, int srcw, int srch, int desw, int desh,int desstride );

MYPROCESS_API void _stdcall drawline(void* pdata,  unsigned int w,  unsigned int h, double x1,double x2,double y1,double y2);

MYPROCESS_API void _stdcall process(void* pdata, unsigned int w, unsigned int h, int leftboundx, int rightboundx, double* leftx,double* lefty, double* rightx, double* righty, double* middlex, double* middley);

MYPROCESS_API void _stdcall processfirstimage(void* pdata, unsigned int w, unsigned int h, int* leftboundx,int* rightboundx);

MYPROCESS_API void _stdcall processyinpian(void* pdata, unsigned int w, unsigned int h,  double* leftx, double* lefty,
                                            double* rightx, double* righty, double* middlex, double* middley);
MYPROCESS_API void _stdcall addimage(void* pdata,void* curpdata, unsigned int w, unsigned int h);

MYPROCESS_API void _stdcall invertimage(void* pdata, unsigned int w, unsigned int h);

MYPROCESS_API void _stdcall calibtest();

MYPROCESS_API void _stdcall convertcoordinate(double imagex,double imagey,double* worldx,double* worldy);

MYPROCESS_API int __stdcall test();



#ifdef __cplusplus
}
#endif