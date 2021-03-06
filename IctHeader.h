//-----------------------------------------------------------------------------
//工业CT数据采集/处理文件头定义(V2.2)
//重庆大学ICT研究中心,明视科技分公司.                                2005.01.19
//增加三维CT扫描参数																	2006.04.20

//2007.07.13修改如下:
//1. 将SpaceBetweenLayer(多层CT层距)和LayerThicknessOfDR(DR分层厚度)合并为LayerThickness(分层厚度)
//2. 增加TotalLayers2(第二段DR扫描总层数)
//3. 增加FirstSectStartCoordinateOfDR(第一段DR扫描起始坐标X1),SecondSectStartCoordinateOfDR(第二段DR扫描起始坐标X3)

//2007.07.26修改如下:
//1. 增加重建参数

//2007.10.04修改如下:
//1. 将LayerThickness命名修改为SpaceBetweenLayer
//2. 增加2代扫描重建参数: NumberOfGraduationOfCt2,SerialOfGraduationOfCt2
//3. 增加3代扫描起始分度号: graduationBase
//3. 增加水平方向中心探测器序号SerialNo1OfMiddleHorizontalDetector/SerialNo2OfMiddleHorizontalDetector
//   用于数据校正时确定中间探测器(扇面中心射线通过探测器时序号1/2相同;
//   扇面中心射线通过两个探测器中间时,序号1/2相差1)

//2008.04.24修改如下:
//	 ICT_HEADER 改为ICT_HEADER21表示2.1版本格式, 对应DATAFORMAT21, 数据总行数为 WORD
//   增加ICT_HEADER22表示2.2版本格式, 对应DATAFORMAT22, 数据总行数改为 DWORD
//   扫描参数中增加NumberOfTable表示扫描时使用的转台数量
//-----------------------------------------------------------------------------
//2008.05.12修改如下:
//   DATAFORMAT22以1字节对齐
//   其他均以默认8字节对齐；

#ifndef __ICTHEADER_H
#define __ICTHEADER_H

#ifndef	ULONG
#define	ULONG	unsigned long
#endif

#ifndef	DWORD
#define	DWORD	unsigned long
#endif

#ifndef	WORD
#define	WORD	unsigned short
#endif

#ifndef	BYTE
#define	BYTE	unsigned char
#endif

#define	MainVersion21	2								//定义主版本号
#define	SubVersion21	1								//定义次版本号
#define	MainVersion22	2								//定义主版本号
#define	SubVersion22	2								//定义次版本号
#define  BiDirect       1                               //扫描方向：双向；
#define  SigDirect      0                               //扫描方向：单向；

//定义探测器类型
enum{
	ARCDETECTOR	=	0,										//弧形探测器
	LINEDETECTOR,											//直线探测器
	FLATDETECTOR											//平板探测器
};

//扫描方式: 0-Ⅰ代扫描,1-Ⅱ代扫描,2-Ⅲ代扫描,3-DR扫描，4-局部扫描,5-螺旋扫描,6-锥束扫描,7-锥束螺旋扫描
//定义扫描方式
enum{
	SCAN1st	=	0,											//Ⅰ代扫描
	SCAN2nd,													//Ⅱ代扫描
	SCAN3rd,													//Ⅲ代扫描
	SCANdr,													//DR扫描
	SCANlocal,												//局部扫描
	SCANhelix,												//螺旋扫描
	SCANcone,												//锥束扫描
	SCANconeHelix											//锥束螺旋扫描
};

//定义数据类型
enum{
	CHARDATA	=	1,											//字符型
	INTDATA,													//整型
	LONGDATA,												//长整型
	FLOATDATA,												//浮点型
	DOUBLEDATA												//双精度型
};

#define	PWDLEN		128								//定义密码串长度

//****** 日期,时间信息 20 bytes *********************************************************
typedef struct  _DATE_TIME{
	char	Date[11];					     				//格式:2003/07/10,以ASCIZ结束
	char	Time[9];					     					//格式:16:35:12,以ASCIZ结束
}DATE_TIME;

//****** 测试任务信息 256 bytes *********************************************************
typedef	struct	_TASKMESSAGE{
	DATE_TIME DateTime;									//测试日期及时间(20字节:2003/07/10 16:35:12 )
	char	Number[32];										//试验任务编号(20字节)
	char	Name[64];										//试验任务名称(64字节),格式:汉字区位码
	char	Toastmaster[16];								//试验主持人(16字节),格式:汉字区位码
	char  SubmitUnit[64];								//送检单位

	BYTE	reserved[60];									//保留字节
}TASKMESSAGE;

//****** 测试工件信息 640 bytes *********************************************************
typedef	struct	_WORKPIECEMESSAGE{
	char	WorkpieceName[32];							//工件名称(20字节),格式:汉字区位码
	char	WorkpieceSort[32];							//工件类别(20字节),格式:汉字区位码
	char	WorkpieceNumber[32];							//工件编号(20字节),格式:汉字区位码
	char	WorkpieceModel[32];							//工件型号(32字节),格式:汉字区位码
	char	WorkpieceBatch[32];							//工件批次(32字节),格式:汉字区位码
	char	ShellMaterial[64];   						//壳体材料(40字节),格式:汉字区位码
	char	FillerSort[64];								//装填物种类(64字节),格式:汉字区位码
	char	Manufacturer[64];   							//工件制造单位(64字节),格式:汉字区位码
	char	TestPosition[32];								//检测部位(32字节),格式:汉字区位码
	char	ZeroPointDefineAlongAxis[32];				//工件轴向零点文字定义,格式:汉字区位码
	char	ZeroPointDefineAlongCircle[64];			//工件圆周零点文字定义,格式:汉字区位码
	float	WorkpieceZeroPointAlongAxis;				//工件轴向零点坐标(相对于系统坐标零点)
	float	WorkpieceMaxDiameter;						//工件最大直径,单位:mm
	float	WorkpieceDiameter;							//工件检测部位外径,单位:mm
	float	WorkpieceLength;								//工件长度,单位:mm
	float	WorkpieceBeginCoordinate;					//工件起始坐标值
	float	WorkpieceEndCoordinate;						//工件结束坐标值
	float	WorkpieceWeight;								//工件质量,单位:kg
	float	MaxDensity;			     	               //工件最大密度,单位:g/cm3

	BYTE	reserved[128];									//保留字节
}WORKPIECEMESSAGE;

//****** 扫描参数信息 380 bytes **********************************************************
typedef	struct	_SCANPARAMETER{
	WORD	ScanMode;										//扫描方式: 0-Ⅰ代扫描,1-Ⅱ代扫描,2-Ⅲ代扫描,3-DR扫描，4-局部扫描,5-螺旋扫描,6-锥束扫描
	WORD	Ct2ScanMode;									//2代扫描模式:  0-360°,1-180°,2-180°间隔
		//Ⅱ代扫描时,双向表示平移为正反两个方向采集数据
		//Ⅲ代扫描时,双向表示相邻两层插值方向相反
		//DR扫描时,双向表示分层为正反两个方向采集数据
	WORD	ScanDirectionMode;							//扫描方向: 0-单向,1-双向
	WORD	DataTransferMode;								//数据传送方式: 0-整体传送, 1-边扫描边传送

	WORD	Pixels;											//水平图像尺寸代号: 0-64,1-128,2-256,3-512,4-1024,5-2048,6-4096
	float	ViewDiameter;									//视场直径(mm)
	float	RadialDistanceInLocal;						//局部扫描时扫描视场中心至回转中心距离(mm)
	float	AngleInLocal;									//局部扫描时回转中心与扫描视场中心连线与水平正半轴起始夹角(°)

	WORD	CollimationSize;								//准直器尺寸代号:0,1,2...   准直器宽度
	float CollimationThickness;						//准直器高度/断层厚度(mm)
	WORD  DetectorStyle;                         //当前使用的探测器结构(0-弧形, 1-直线, 2-平板)
	WORD	NumberOfSystemHorizontalDetector;		//水平方向系统探头数(横向, 弧形/直线探测器)
	WORD	NumberOfValidHorizontalDetector;			//水平方向有效探头数(横向, 弧形/直线探测器)
	WORD	SerialNo1OfMiddleHorizontalDetector;	//水平方向中心探测器序号1(横向, 弧形/直线探测器, 从0开始计算)
	WORD	SerialNo2OfMiddleHorizontalDetector;	//水平方向中心探测器序号2(横向, 弧形/直线探测器, 从0开始计算)
	WORD  NumberofSystemVerticalDetector;			//垂直方向系统探测器数(列向)
	WORD  NumberofValidVerticalDetector;			//垂直方向有效探测器数(列向)
	float	SpaceOfHorizontalDetector;					//水平方向有效探测器间距(mm)
	float	SpaceOfVerticalDetector;					//垂直方向有效探测器间距(mm)(螺旋扫描多排探测器合并使用情况下为相邻两行数据中心探测器距离)
	float	HorizontalSectorAngle;						//水平方向有效扇角值(°)	
	float VerticalSectorAngle;							//垂直方向有效扇角值(°)
	float	RadialPosition;								//焦点到旋转中心距离(径向位置)(mm)    
	float SourceDetectorDistance;						//焦点到探测器距离(mm)
	float	Azimuth;											//扫描时分度起始方位角(°)
	WORD	GraduationDirection;							//分度方向:0-顺时针,1-逆时针(正方向)
	WORD	NumberOfGraduation;							//分度次数(指单螺距、锥束扫描、或二维CT旋转一周分度数)
	WORD	InterpolationFlag;							//插值数标志:0-标准插值,1-插值数＋1
	WORD	NumberOfInterpolation;						//插值次数(标准插值次数)
	WORD	NumberOfTranslation;							//平移采样点数
	WORD	DelaminationMode;								//CT分层方式:0-等层距,1-不等层距,2-当前层距
	float HelicalScanPitch;								//螺旋扫描螺距大小,单位:mm
	WORD	TotalLayers;									//CT扫描总层数或第一段DR扫描总层数,范围:1-9999
	WORD	TotalLayers2;									//第二段DR扫描总层数,范围:0-9999,只有一段DR扫描时填写0
	float	CurrentLayerCoordinate;						//当前层坐标,单位:mm
	float	SpaceBetweenLayer;							//CT层距/DR分层厚度(层间距,两段DR扫描时每段层间距相同),单位:mm
	float	FirstSectStartCoordinateOfDR;				//第一段DR扫描起始坐标X1, 单位:mm
	float	SecondSectStartCoordinateOfDR;			//第二段DR扫描起始坐标X3, 单位:mm
	WORD	SetupSynchPulseNumber;						//预置同步脉冲数(加速器情况)
	float	SampleTime;										//射束采样时间, 单位:秒
	WORD	UsedScanTime;									//实际扫描时间(s)
	float	TemputreValue;									//探测系统设置温度值(°)
	char	FilenameTemperature[32];					//探测系统实时温度记录文件名
	char	FilenameOfCTdata[32];						//CT数据文件名,按Windows文件名定义的字符串(用于存放CT、DR、锥束扫描数据)
	char	FilenameOf2CTdata[32];						//Ⅱ代数据边采边传文件名(即数据文件名加上编号(00-31))
	char	FilenameOfPictureData[32];					//图像数据文件名, 按Windows文件名定义的字符串
	WORD	NumberofTable;									//扫描检测使用的转台数量(缺省为1, 2表示两个转台)
	WORD	CenterOfTable;									//扫描检测使用的转台号(中间转台号)

	BYTE	reserved[120];									//保留字节
}SCANPARAMETER;

//****** 系统参数信息 192 bytes ***********************************************************
typedef	struct	_SYSTEMPARAMETER{
	char	ModelOfCT[32];									//CT设备型号
	WORD	RaySort;											//射线源类型:0-X球管,1-加速器,2-钴60,3-铯137
	float	RayEngery;										//射线能量(MeV)
	float	RayDosage;										//射线剂量(cGy)
	WORD	SynchFrequency;								//同步频率(Hz)
	WORD	AmplifyMultiple;								//采样放大倍数
	WORD	IntegralTime;									//采样积分时间(us)

	BYTE	reserved[140];									//保留字节
}SYSTEMPARAMETER;

//****** II代CT重建信息 128 bytes *********************************************************
typedef	struct	_RECONSTRUCTMESSAGE{
	BYTE	Ct2ReconstructPara[64];						//2代CT扫描分度重建标志(每个分度1字节,0-该分度未重建,1-该分度已重建)
	float	Zmax;												//FDK并行重建用
	float	Zmin;												//FDK并行重建用
	float	RotationAngle;									//三代重建图像旋转角度
	float	PixelMax;										//原始重建图像最大值
	float	PixelMin;										//原始重建图像最小值
	WORD	VolumeLayer;									//三维重建层数
	WORD	VolumeWidth;									//三维重建宽度
	float	SpaceBetweenPixel;							//像素之间宽度
	BYTE	NumberOfGraduationOfCt2;					//分度总数(2代CT扫描, 2007.10.04增加)
	BYTE	SerialOfGraduationOfCt2;					//分度序号(2代CT扫描, 2007.10.04增加)
	BYTE	reserved[32];									//保留字节
}RECONSTRUCTMESSAGE;

//****** 图像识别信息 64 bytes ***********************************************************
typedef	struct	_IDENTIFYMESSAGE{
	WORD	DefectMode;										//缺陷类型: 0-装配,1-导爆索,2-其它(气孔,裂缝,脱粘),默认为0
	char	NumberofTemplate[32];						//识别模板编号(字符串), 输入方式参照word打印页码格式; 例如,1-3表示模板编号从1到3; 1,4,6,8表示识别模板分别为1,4,6,8
	BYTE	reserved[30];									//保留字节
}IDENTIFYMESSAGE;

//#pragma pack(1)		//按字节对齐数据
//****** 数据格式信息 32 bytes  (V2.1版本用)***********************************************************
typedef	struct	_DATAFORMAT21{
	WORD	DataType;										//数据存储类型: char=01,int=02,unsigned long=03,float=04,double=05
	WORD	TotalLines;										//数据总行数  
	WORD	dataColAtRow;									//每行数据个数(不包括附加数据)
	WORD	appendColAtRow;								//每行中前导附加数据个数
	WORD	graduationBase;								//3代扫描分度起始号(2007.10.04增加)
	BYTE	reserved[22];									//保留字节
}DATAFORMAT21;
//****** 保留字节长度 *******************************************************************
#define	RESERVEDBYTES	2048-4-2-PWDLEN-sizeof(TASKMESSAGE)-sizeof(WORKPIECEMESSAGE)-sizeof(SCANPARAMETER)-sizeof(SYSTEMPARAMETER)-sizeof(RECONSTRUCTMESSAGE)-sizeof(IDENTIFYMESSAGE)-sizeof(DATAFORMAT21)

//****** 头文件信息(V2.1版本使用) *********************************************************************
typedef	struct _ICT_HEADER21{
	BYTE						MainVersion;				//版本标识(主版本号: 0x02)
	BYTE						SubVersion;					//版本标识(次版本号: 0x01)
	BYTE						reserved1[2];				//保留
	TASKMESSAGE				Task;							//测试任务信息
	WORKPIECEMESSAGE		Workpiece;					//测试工件信息
	SCANPARAMETER			ScanParameter;				//扫描参数
	SYSTEMPARAMETER		SystemParameter;			//系统参数
	RECONSTRUCTMESSAGE	ReconstructParameter;	//重建参数
	IDENTIFYMESSAGE		IdentifyMessage;			//图像识别信息
	DATAFORMAT21			DataFormat;					//数据格式
	BYTE	       			reserved2[RESERVEDBYTES];//保留(316)
	WORD						SizeofHeader;				//文件头尺寸: >2048(文件头尺寸为随机长度)
	BYTE						Password[PWDLEN];			//加密字符串
}ICT_HEADER21;
#pragma pack(1)		//按字节对齐数据
//****** 数据格式信息 32 bytes  (V2.2版本用)***********************************************************
typedef	struct	_DATAFORMAT{
	WORD	DataType;										//数据存储类型: char=01,int=02,unsigned long=03,float=04,double=05
	DWORD	TotalLines;										//数据总行数  .2008-01-23由RORD改为DWORD,同时版本号从V2.1 改为V2.2
	WORD	dataColAtRow;									//每行数据个数(不包括附加数据)
	WORD	appendColAtRow;								//每行中前导附加数据个数
	WORD	graduationBase;								//3代扫描分度起始号(2007.10.04增加)
	BYTE	reserved[20];									//保留字节
}DATAFORMAT22;

#pragma pack(8)		//按缺省值对齐数据

//****** 头文件信息 (V2.2版本使用)*********************************************************************
typedef	struct _ICT_HEADER22{
	BYTE						MainVersion;				//版本标识(主版本号: 0x02)
	BYTE						SubVersion;					//版本标识(次版本号: 0x02)
	BYTE						reserved1[2];				//保留
	TASKMESSAGE				Task;							//测试任务信息
	WORKPIECEMESSAGE		Workpiece;					//测试工件信息
	SCANPARAMETER			ScanParameter;				//扫描参数
	SYSTEMPARAMETER		SystemParameter;			//系统参数
	RECONSTRUCTMESSAGE	ReconstructParameter;   //重建参数
	IDENTIFYMESSAGE		IdentifyMessage;			//图像识别信息
	DATAFORMAT22				DataFormat;					//数据格式
	BYTE	       			reserved2[RESERVEDBYTES];//保留(316)
	WORD						SizeofHeader;				//文件头尺寸: >2048(文件头尺寸为随机长度)
	BYTE						Password[PWDLEN];			//加密字符串
}ICT_HEADER22;
//螺旋CT扫描工件实际高度 = 扫描总层数*螺距
//文件头之后按照先行后列的顺序依次存放数据
//系统提供若干个动态库函数完成各部分信息的加密和解密
#endif
