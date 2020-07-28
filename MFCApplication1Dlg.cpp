
// MFCApplication1Dlg.cpp : 实现文件
//

#include "stdafx.h"
#include "MFCApplication1.h"
#include "MFCApplication1Dlg.h"
#include "afxdialogex.h"
#include "HalconCpp.h"
#include <ctime>
#include <iostream>
#include <vector>
#include <fstream>
#include <io.h>
#include <fcntl.h>

using namespace HalconCpp;
using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

ifstream inresult("data.txt", ios::app);
ofstream outresult("data.txt", ios::app);

// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMFCApplication1Dlg 对话框



CMFCApplication1Dlg::CMFCApplication1Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMFCApplication1Dlg::IDD, pParent)
	, jk(14)
	, kr(7)
	, wr(30)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCApplication1Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, jk);
	DDX_Text(pDX, IDC_EDIT2, kr);
	DDX_Text(pDX, IDC_EDIT3, wr);
}

BEGIN_MESSAGE_MAP(CMFCApplication1Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CMFCApplication1Dlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CMFCApplication1Dlg::OnBnClickedButton2)
	ON_WM_SIZE()
END_MESSAGE_MAP()


// CMFCApplication1Dlg 消息处理程序

BOOL CMFCApplication1Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO:  在此添加额外的初始化代码
	InitConsoleWindow();
	CRect rect;
	GetClientRect(&rect);     //取客户区大小 
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMFCApplication1Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMFCApplication1Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CMFCApplication1Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CMFCApplication1Dlg::InitConsoleWindow()
{
	AllocConsole();
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	int hCrt = _open_osfhandle((long)handle, _O_TEXT);
	FILE *hf = _fdopen(hCrt, "w");
	*stdout = *hf;
}


void close_parallels(HObject ho_ParallelContours1, HObject ho_ParallelContours2,
	HObject *ho_Contour)
{

	// Local iconic variables
	HObject  ho_Parallel1, ho_Parallel2, ho_ClosedContour;

	// Local control variables
	HTuple  hv_Number, hv_Index, hv_Row1, hv_Col1;
	HTuple  hv_Row2, hv_Col2;

	CountObj(ho_ParallelContours1, &hv_Number);
	GenEmptyObj(&(*ho_Contour));
	{
		HTuple end_val2 = hv_Number;
		HTuple step_val2 = 1;
		for (hv_Index = 1; hv_Index.Continue(end_val2, step_val2); hv_Index += step_val2)
		{
			SelectObj(ho_ParallelContours1, &ho_Parallel1, hv_Index);
			SelectObj(ho_ParallelContours2, &ho_Parallel2, hv_Index);
			GetContourXld(ho_Parallel1, &hv_Row1, &hv_Col1);
			GetContourXld(ho_Parallel2, &hv_Row2, &hv_Col2);
			GenContourPolygonXld(&ho_ClosedContour, (hv_Row1.TupleConcat(hv_Row2.TupleInverse())).TupleConcat(HTuple(hv_Row1[0])),
				(hv_Col1.TupleConcat(hv_Col2.TupleInverse())).TupleConcat(HTuple(hv_Col1[0])));
			ConcatObj((*ho_Contour), ho_ClosedContour, &(*ho_Contour));
		}
	}
	return;
}



void gen_display_segments(HObject ho_TooThinSegments, HObject ho_LeftContour, HObject ho_RightContour,
	HObject *ho_ContoursIntersection)
{

	// Local iconic variables
	HObject  ho_ParallelContours1, ho_ParallelContours2;
	HObject  ho_Contour, ho_Contour1;

	//Construct contours used to visualize the error segments
	//returned by the bead inspection
	GenParallelContourXld(ho_TooThinSegments, &ho_ParallelContours1, "regression_normal",
		50);
	GenParallelContourXld(ho_TooThinSegments, &ho_ParallelContours2, "regression_normal",
		-50);
	close_parallels(ho_ParallelContours1, ho_ParallelContours2, &ho_Contour);
	close_parallels(ho_LeftContour, ho_RightContour, &ho_Contour1);
	IntersectionClosedContoursXld(ho_Contour, ho_Contour1, &(*ho_ContoursIntersection)
		);
	return;
}


void disp_message(HTuple hv_WindowHandle, HTuple hv_String, HTuple hv_CoordSystem,
	HTuple hv_Row, HTuple hv_Column, HTuple hv_Color, HTuple hv_Box)
{

	// Local iconic variables

	// Local control variables
	HTuple  hv_Red, hv_Green, hv_Blue, hv_Row1Part;
	HTuple  hv_Column1Part, hv_Row2Part, hv_Column2Part, hv_RowWin;
	HTuple  hv_ColumnWin, hv_WidthWin, hv_HeightWin, hv_MaxAscent;
	HTuple  hv_MaxDescent, hv_MaxWidth, hv_MaxHeight, hv_R1;
	HTuple  hv_C1, hv_FactorRow, hv_FactorColumn, hv_UseShadow;
	HTuple  hv_ShadowColor, hv_Exception, hv_Width, hv_Index;
	HTuple  hv_Ascent, hv_Descent, hv_W, hv_H, hv_FrameHeight;
	HTuple  hv_FrameWidth, hv_R2, hv_C2, hv_DrawMode, hv_CurrentColor;

	//This procedure displays text in a graphics window.
	//
	//Input parameters:
	//WindowHandle: The WindowHandle of the graphics window, where
	//   the message should be displayed
	//String: A tuple of strings containing the text message to be displayed
	//CoordSystem: If set to 'window', the text position is given
	//   with respect to the window coordinate system.
	//   If set to 'image', image coordinates are used.
	//   (This may be useful in zoomed images.)
	//Row: The row coordinate of the desired text position
	//   If set to -1, a default value of 12 is used.
	//Column: The column coordinate of the desired text position
	//   If set to -1, a default value of 12 is used.
	//Color: defines the color of the text as string.
	//   If set to [], '' or 'auto' the currently set color is used.
	//   If a tuple of strings is passed, the colors are used cyclically
	//   for each new textline.
	//Box: If Box[0] is set to 'true', the text is written within an orange box.
	//     If set to' false', no box is displayed.
	//     If set to a color string (e.g. 'white', '#FF00CC', etc.),
	//       the text is written in a box of that color.
	//     An optional second value for Box (Box[1]) controls if a shadow is displayed:
	//       'true' -> display a shadow in a default color
	//       'false' -> display no shadow (same as if no second value is given)
	//       otherwise -> use given string as color string for the shadow color
	//
	//Prepare window
	GetRgb(hv_WindowHandle, &hv_Red, &hv_Green, &hv_Blue);
	GetPart(hv_WindowHandle, &hv_Row1Part, &hv_Column1Part, &hv_Row2Part, &hv_Column2Part);
	GetWindowExtents(hv_WindowHandle, &hv_RowWin, &hv_ColumnWin, &hv_WidthWin, &hv_HeightWin);
	SetPart(hv_WindowHandle, 0, 0, hv_HeightWin - 1, hv_WidthWin - 1);
	//
	//default settings
	if (0 != (hv_Row == -1))
	{
		hv_Row = 12;
	}
	if (0 != (hv_Column == -1))
	{
		hv_Column = 12;
	}
	if (0 != (hv_Color == HTuple()))
	{
		hv_Color = "";
	}
	//
	hv_String = (("" + hv_String) + "").TupleSplit("\n");
	//
	//Estimate extentions of text depending on font size.
	GetFontExtents(hv_WindowHandle, &hv_MaxAscent, &hv_MaxDescent, &hv_MaxWidth, &hv_MaxHeight);
	if (0 != (hv_CoordSystem == HTuple("window")))
	{
		hv_R1 = hv_Row;
		hv_C1 = hv_Column;
	}
	else
	{
		//Transform image to window coordinates
		hv_FactorRow = (1.*hv_HeightWin) / ((hv_Row2Part - hv_Row1Part) + 1);
		hv_FactorColumn = (1.*hv_WidthWin) / ((hv_Column2Part - hv_Column1Part) + 1);
		hv_R1 = ((hv_Row - hv_Row1Part) + 0.5)*hv_FactorRow;
		hv_C1 = ((hv_Column - hv_Column1Part) + 0.5)*hv_FactorColumn;
	}
	//
	//Display text box depending on text size
	hv_UseShadow = 1;
	hv_ShadowColor = "gray";
	if (0 != (HTuple(hv_Box[0]) == HTuple("true")))
	{
		hv_Box[0] = "#fce9d4";
		hv_ShadowColor = "#f28d26";
	}
	if (0 != ((hv_Box.TupleLength())>1))
	{
		if (0 != (HTuple(hv_Box[1]) == HTuple("true")))
		{
			//Use default ShadowColor set above
		}
		else if (0 != (HTuple(hv_Box[1]) == HTuple("false")))
		{
			hv_UseShadow = 0;
		}
		else
		{
			hv_ShadowColor = ((const HTuple&)hv_Box)[1];
			//Valid color?
			try
			{
				SetColor(hv_WindowHandle, HTuple(hv_Box[1]));
			}
			// catch (Exception) 
			catch (HalconCpp::HException &HDevExpDefaultException)
			{
				HDevExpDefaultException.ToHTuple(&hv_Exception);
				hv_Exception = "Wrong value of control parameter Box[1] (must be a 'true', 'false', or a valid color string)";
				throw HalconCpp::HException(hv_Exception);
			}
		}
	}
	if (0 != (HTuple(hv_Box[0]) != HTuple("false")))
	{
		//Valid color?
		try
		{
			SetColor(hv_WindowHandle, HTuple(hv_Box[0]));
		}
		// catch (Exception) 
		catch (HalconCpp::HException &HDevExpDefaultException)
		{
			HDevExpDefaultException.ToHTuple(&hv_Exception);
			hv_Exception = "Wrong value of control parameter Box[0] (must be a 'true', 'false', or a valid color string)";
			throw HalconCpp::HException(hv_Exception);
		}
		//Calculate box extents
		hv_String = (" " + hv_String) + " ";
		hv_Width = HTuple();
		{
			HTuple end_val93 = (hv_String.TupleLength()) - 1;
			HTuple step_val93 = 1;
			for (hv_Index = 0; hv_Index.Continue(end_val93, step_val93); hv_Index += step_val93)
			{
				GetStringExtents(hv_WindowHandle, HTuple(hv_String[hv_Index]), &hv_Ascent,
					&hv_Descent, &hv_W, &hv_H);
				hv_Width = hv_Width.TupleConcat(hv_W);
			}
		}
		hv_FrameHeight = hv_MaxHeight*(hv_String.TupleLength());
		hv_FrameWidth = (HTuple(0).TupleConcat(hv_Width)).TupleMax();
		hv_R2 = hv_R1 + hv_FrameHeight;
		hv_C2 = hv_C1 + hv_FrameWidth;
		//Display rectangles
		GetDraw(hv_WindowHandle, &hv_DrawMode);
		SetDraw(hv_WindowHandle, "fill");
		//Set shadow color
		SetColor(hv_WindowHandle, hv_ShadowColor);
		if (0 != hv_UseShadow)
		{
			DispRectangle1(hv_WindowHandle, hv_R1 + 1, hv_C1 + 1, hv_R2 + 1, hv_C2 + 1);
		}
		//Set box color
		SetColor(hv_WindowHandle, HTuple(hv_Box[0]));
		DispRectangle1(hv_WindowHandle, hv_R1, hv_C1, hv_R2, hv_C2);
		SetDraw(hv_WindowHandle, hv_DrawMode);
	}
	//Write text.
  {
	  HTuple end_val115 = (hv_String.TupleLength()) - 1;
	  HTuple step_val115 = 1;
	  for (hv_Index = 0; hv_Index.Continue(end_val115, step_val115); hv_Index += step_val115)
	  {
		  hv_CurrentColor = ((const HTuple&)hv_Color)[hv_Index % (hv_Color.TupleLength())];
		  if (0 != (HTuple(hv_CurrentColor != HTuple("")).TupleAnd(hv_CurrentColor != HTuple("auto"))))
		  {
			  SetColor(hv_WindowHandle, hv_CurrentColor);
		  }
		  else
		  {
			  SetRgb(hv_WindowHandle, hv_Red, hv_Green, hv_Blue);
		  }
		  hv_Row = hv_R1 + (hv_MaxHeight*hv_Index);
		  SetTposition(hv_WindowHandle, hv_Row, hv_C1);
		  WriteString(hv_WindowHandle, HTuple(hv_String[hv_Index]));
	  }
  }
  //Reset changed window settings
  SetRgb(hv_WindowHandle, hv_Red, hv_Green, hv_Blue);
  SetPart(hv_WindowHandle, hv_Row1Part, hv_Column1Part, hv_Row2Part, hv_Column2Part);
  return;
}


void disp_continue_message(HTuple hv_WindowHandle, HTuple hv_Color, HTuple hv_Box)
{

	// Local iconic variables

	// Local control variables
	HTuple  hv_ContinueMessage, hv_Row, hv_Column;
	HTuple  hv_Width, hv_Height, hv_Ascent, hv_Descent, hv_TextWidth;
	HTuple  hv_TextHeight;

	//This procedure displays 'Press Run (F5) to continue' in the
	//lower right corner of the screen.
	//It uses the procedure disp_message.
	//
	//Input parameters:
	//WindowHandle: The window, where the text shall be displayed
	//Color: defines the text color.
	//   If set to '' or 'auto', the currently set color is used.
	//Box: If set to 'true', the text is displayed in a box.
	//
	hv_ContinueMessage = "Press Run (F5) to continue";
	GetWindowExtents(hv_WindowHandle, &hv_Row, &hv_Column, &hv_Width, &hv_Height);
	GetStringExtents(hv_WindowHandle, (" " + hv_ContinueMessage) + " ", &hv_Ascent, &hv_Descent,
		&hv_TextWidth, &hv_TextHeight);
	disp_message(hv_WindowHandle, hv_ContinueMessage, "window", (hv_Height - hv_TextHeight) - 12,
		(hv_Width - hv_TextWidth) - 12, hv_Color, hv_Box);
	return;
}


HTuple hv_WindowHandle;
void CMFCApplication1Dlg::CreateImageWindow()
{
	HTuple HWindowID;
	CRect Rect;
	CWnd* pWnd = GetDlgItem(IDC_PIC);
	HWindowID = (Hlong)pWnd->m_hWnd;
	pWnd->GetWindowRect(&Rect);
	OpenWindow(0, 0, Rect.Width(), Rect.Height(), HWindowID, "visible", "", &hv_WindowHandle);
}



struct Ready
{
	vector<double> r1;
	vector<vector<double>> r2;
}ready;
bool b = true;
//检测准备
void CMFCApplication1Dlg::OnBnClickedButton1()
{
	// TODO:  在此添加控件通知处理程序代码
	HObject  ho_ContOut, ho_ImageRef;
	HTuple  hv_Width, hv_Height, hv_Rows, hv_Cols, hv_Weights, m_ImageWidth, m_ImageHeight;
	if (b)
	{
		CreateImageWindow();
		b = false;
	}
	ReadImage(&ho_ImageRef, "./卷材溢胶原图/7.jpg");       //标准图像
	GetImagePointer1(ho_ImageRef, NULL, NULL, &m_ImageWidth, &m_ImageHeight);
	SetPart(hv_WindowHandle, 0, 0, m_ImageHeight - 1, m_ImageWidth - 1);
	HDevWindowStack::Push(hv_WindowHandle);
	if (HDevWindowStack::IsOpen())
		DispObj(ho_ImageRef, HDevWindowStack::GetActive());
	DrawNurbs(&ho_ContOut, hv_WindowHandle, "true", "true", "true", "true", 3, &hv_Rows, &hv_Cols, &hv_Weights);
	if (HDevWindowStack::IsOpen())
		DispObj(ho_ContOut, HDevWindowStack::GetActive());
	for (int i = 1; i <= 3; i++)
	{
		for (int j = 0; j < hv_Weights.TupleLength(); j++)
		{
			switch (i)
			{
			case 1:
					ready.r1.push_back((double)hv_Rows.TupleReal()[j]);
					break;
			case 2:
					ready.r1.push_back((double)hv_Cols.TupleReal()[j]);
					break;
			default:
					ready.r1.push_back((double)hv_Weights.TupleReal()[j]);
			}
		}
		ready.r2.push_back(ready.r1);
		ready.r1.clear();
	}
	int l = hv_Weights.TupleLength();
	outresult << l << endl;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < hv_Weights.TupleLength(); j++)
		{
			outresult << ready.r2[i][j] << "  ";
		}
		outresult << endl;
	}
	AfxMessageBox(_T("准备结束"));
}



bool a = true;
int l;
HTuple hv_Rows, hv_Cols, hv_Weights;
//检测开始
void CMFCApplication1Dlg::OnBnClickedButton2()
{
	// TODO:  在此添加控件通知处理程序代码
	HObject  ho_Image, ho_ModelSide1;
	HObject  ho_ModelSide2, ho_PositionToleranceSide1;
	HObject  ho_PositionToleranceSide2, ho_ContourRef, ho_ModelSides, ho_PositionToleranceSides;
	HObject  ho_LeftContour, ho_RightContour, ho_ErrorSegment;
	HObject  ho_SelectedSegments, ho_ErrorParts, ho_Imageresult;

	HTuple  hv_TargetWidth, hv_WidthTolerance, hv_PositionTolerance;
	HTuple  hv_Polarity, hv_E, hv_BeadInspectionModel;
	HTuple  hv_Message, hv_TextOffset, hv_ImageFiles, hv_Index;
	HTuple  hv_idx, hv_ErrorType, hv_ErrorClasses, hv_ClassIndex;
	HTuple  hv_Class, hv_ErrorIndices, hv_Area, hv_Row, hv_Column, hv_Width, hv_Height, m_ImageWidth, m_ImageHeight;
	double d;
	if (b)
	{
		CreateImageWindow();
		b = false;
	}
	if (a)
	{
		//加载数据
		inresult >> l;
		for (int i = 1; i <= 3; i++)
		{
			for (int j = 0; j < l; j++)
			{
				switch (i)
				{
				case 1:
					inresult >> d;
					hv_Rows[j] = d;
					break;
				case 2:
					inresult >> d;
					hv_Cols[j] = d;
					break;
				default:
					inresult >> d;
					hv_Weights[j] = d;
				}
			}
		}
		a = false;
	}
	cout << l << endl;
	for (int i = 0; i < hv_Weights.TupleLength(); i++)
	{
		cout << "hv_Rows:" << (double)hv_Rows.TupleReal()[i] << "  hv_Cols:" << (double)hv_Cols.TupleReal()[i] << "  hv_Weights:" << (double)hv_Weights.TupleReal()[i] << endl;
	}
	UpdateData(TRUE);
	//参数设置
	hv_TargetWidth = jk;           //胶宽
	hv_WidthTolerance = kr;        //宽度容忍度
	hv_PositionTolerance = wr;     //位置容忍度
	hv_Polarity = "dark";
	GenContourNurbsXld(&ho_ContourRef, hv_Rows, hv_Cols, "auto", hv_Weights, 3, 1, 5);
	//Create a new bead inspection model with the following parameters
	CreateBeadInspectionModel(ho_ContourRef, hv_TargetWidth, hv_WidthTolerance, hv_PositionTolerance,
		hv_Polarity, HTuple(), HTuple(), &hv_BeadInspectionModel);
	//Create two parallel contours to give an impression of how
	//thick a correct adhesive bead should be
	GenParallelContourXld(ho_ContourRef, &ho_ModelSide1, "regression_normal", hv_TargetWidth*0.5);
	GenParallelContourXld(ho_ContourRef, &ho_ModelSide2, "regression_normal", (-hv_TargetWidth)*0.5);
	ConcatObj(ho_ModelSide1, ho_ModelSide2, &ho_ModelSides);
	//Create two parallel contours to give an impression of where
	//a correct adhesive bead should be located
	GenParallelContourXld(ho_ContourRef, &ho_PositionToleranceSide1, "regression_normal",
		hv_PositionTolerance);
	GenParallelContourXld(ho_ContourRef, &ho_PositionToleranceSide2, "regression_normal",
		-hv_PositionTolerance);
	ConcatObj(ho_PositionToleranceSide1, ho_PositionToleranceSide2, &ho_PositionToleranceSides);
	//Now, perform the inspection task
	hv_TextOffset = 20;
	ListFiles("./卷材溢胶原图", ((HTuple("files").Append("follow_links")).Append("recursive")),
		&hv_ImageFiles);
	TupleRegexpSelect(hv_ImageFiles, (HTuple("\\.(tif|tiff|gif|bmp|jpg|jpeg|jp2|png|pcx|pgm|ppm|pbm|xwd|ima|hobj)$").Append("ignore_case")),
		&hv_ImageFiles);
	{
		HTuple end_val186 = (hv_ImageFiles.TupleLength()) - 1;
		HTuple step_val186 = 1;
		for (hv_Index = 0; hv_Index.Continue(end_val186, step_val186); hv_Index += step_val186)
		{
			clock_t ts = clock();
			hv_idx = hv_Index + 1;
			ReadImage(&ho_Image, HTuple(hv_ImageFiles[hv_Index]));
			//Apply the bead inspection model to image
			ApplyBeadInspectionModel(ho_Image, &ho_LeftContour, &ho_RightContour, &ho_ErrorSegment,
				hv_BeadInspectionModel, &hv_ErrorType);
			//Display the segmented adhesive bead with its error segments
			GetImagePointer1(ho_Image, NULL, NULL, &m_ImageWidth, &m_ImageHeight);
			SetPart(hv_WindowHandle, 0, 0, m_ImageHeight - 1, m_ImageWidth - 1);
			HDevWindowStack::Push(hv_WindowHandle);
			if (HDevWindowStack::IsOpen())
				DispObj(ho_Image, HDevWindowStack::GetActive());
			if (HDevWindowStack::IsOpen())
				SetLineWidth(HDevWindowStack::GetActive(), 1);
			if (HDevWindowStack::IsOpen())
				SetColor(HDevWindowStack::GetActive(), "white");
			if (HDevWindowStack::IsOpen())
				DispObj(ho_ContourRef, HDevWindowStack::GetActive());
			if (HDevWindowStack::IsOpen())
				DispObj(ho_ModelSides, HDevWindowStack::GetActive());
			if (HDevWindowStack::IsOpen())
				DispObj(ho_PositionToleranceSides, HDevWindowStack::GetActive());
			if (HDevWindowStack::IsOpen())
				SetLineWidth(HDevWindowStack::GetActive(), 2);
			if (HDevWindowStack::IsOpen())
				SetColor(HDevWindowStack::GetActive(), "green");
			if (HDevWindowStack::IsOpen())
				DispObj(ho_LeftContour, HDevWindowStack::GetActive());
			if (HDevWindowStack::IsOpen())
				DispObj(ho_RightContour, HDevWindowStack::GetActive());
			if (HDevWindowStack::IsOpen())
				SetColor(HDevWindowStack::GetActive(), "red");
			if (HDevWindowStack::IsOpen())
				DispObj(ho_ErrorSegment, HDevWindowStack::GetActive());
			if (0 != ((hv_ErrorType.TupleLength()) == 0))
			{
				//No errors detected
				hv_Message = "Adhesive bead is OK";
				disp_message(hv_WindowHandle, hv_Message, "window", 12, 12, "white", "forest green");
				disp_continue_message(hv_WindowHandle, "black", "true");
				// stop(); only in hdevelop
			}
			else
			{
				//Display errors by error class
				hv_Message[0] = "Adhesive bead is not OK:";
				//
				hv_ErrorClasses.Clear();
				hv_ErrorClasses[0] = "no bead";
				hv_ErrorClasses[1] = "too thin";
				hv_ErrorClasses[2] = "too thick";
				hv_ErrorClasses[3] = "incorrect position";
				{
					HTuple end_val215 = (hv_ErrorClasses.TupleLength()) - 1;
					HTuple step_val215 = 1;
					for (hv_ClassIndex = 0; hv_ClassIndex.Continue(end_val215, step_val215); hv_ClassIndex += step_val215)
					{
						hv_Class = ((const HTuple&)hv_ErrorClasses)[hv_ClassIndex];
						hv_ErrorIndices = hv_ErrorType.TupleFind(hv_Class);
						if (0 != (hv_ErrorIndices != -1))
						{
							SelectObj(ho_ErrorSegment, &ho_SelectedSegments, hv_ErrorIndices + 1);
							if (HDevWindowStack::IsOpen())
								SetColor(HDevWindowStack::GetActive(), "red");
							if (HDevWindowStack::IsOpen())
								SetLineWidth(HDevWindowStack::GetActive(), 3);
							if (0 != (hv_Class != HTuple("no bead")))
							{
								gen_display_segments(ho_SelectedSegments, ho_LeftContour, ho_RightContour,
									&ho_ErrorParts);
								if (HDevWindowStack::IsOpen())
									DispObj(ho_ErrorParts, HDevWindowStack::GetActive());
							}
							else
							{
								if (HDevWindowStack::IsOpen())
									DispObj(ho_SelectedSegments, HDevWindowStack::GetActive());
							}
							AreaCenterPointsXld(ho_SelectedSegments, &hv_Area, &hv_Row, &hv_Column);
							{
								HTuple end_val229 = (hv_ErrorIndices.TupleLength()) - 1;
								HTuple step_val229 = 1;
								for (hv_E = 0; hv_E.Continue(end_val229, step_val229); hv_E += step_val229)
								{
									disp_message(hv_WindowHandle, HTuple(hv_ErrorIndices[hv_E]) + 1, "image",
										HTuple(hv_Row[hv_E]), HTuple(hv_Column[hv_E]) - hv_TextOffset, "white",
										"red");
									hv_TextOffset = 20 - hv_TextOffset;
								}
							}
						}
					}
				}
				disp_message(hv_WindowHandle, hv_Message, "window", 12, 12, "white", "red");
				disp_message(hv_WindowHandle, (HTuple::TupleGenSequence(1, hv_ErrorType.TupleLength(), 1) + ": ") + hv_ErrorType,
					"image", 500, 500, "red", "false");
				DumpWindowImage(&ho_Imageresult, hv_WindowHandle);
				WriteImage(ho_Imageresult, "jpg", 0, "./检测图像/" + hv_idx);
				// stop(); only in hdevelop
			}
			cout << "时间：" << clock() - ts << "ms" << endl;
			Sleep(1000);
			if (HDevWindowStack::IsOpen())
				CloseWindow();
		}
	}
	//Release all allocated memory
	ClearBeadInspectionModel(hv_BeadInspectionModel);
	AfxMessageBox(_T("检测结束"));
}


void CMFCApplication1Dlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);
	// TODO:  在此处添加消息处理程序代码
	if (nType != SIZE_MINIMIZED)
	{
		CWnd *pWnd = GetWindow(GW_CHILD);
		while (pWnd)
		{
			changeControlSize(pWnd, cx, cy);
			pWnd = pWnd->GetNextWindow();
		}
		//重新获取界面大小
		GetClientRect(&m_rect);
	}
}

void CMFCApplication1Dlg::changeControlSize(CWnd* pWnd, int x, int y)
{
	if (pWnd != NULL)
	{
		CRect rect;
		pWnd->GetWindowRect(&rect);
		ScreenToClient(&rect);
		//保存原高度，供下拉框使用
		int height = rect.Height();
		rect.left = rect.left*x / m_rect.Width();
		rect.top = rect.top*y / m_rect.Height();
		rect.right = rect.right*x / m_rect.Width();
		rect.bottom = rect.bottom*y / m_rect.Height();
		//如果是下拉框，则不改变其高度
		TCHAR szClass[65] = { 0 };
		if (GetClassName(pWnd->m_hWnd, szClass, 64) && _tcsicmp(szClass, _T("COMBOBOX")) == 0)
		{
			pWnd->SetWindowPos(NULL, rect.left, rect.top, rect.Width(), height, SWP_NOZORDER | SWP_SHOWWINDOW);
		}
		else
			pWnd->SetWindowPos(NULL, rect.left, rect.top, rect.Width(), rect.Height(), SWP_NOZORDER | SWP_SHOWWINDOW);
	}
}


