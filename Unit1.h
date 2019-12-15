//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.Menus.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.Dialogs.hpp>
//#include <System.ImageList.hpp>
#include <Vcl.ImgList.hpp>
#include <System.ImageList.hpp>

//---------------------------------------------------------------------------
#include <vector>
#include <algorithm>
#include <functional>
#include <string>


//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
 // класс по моей предметной области
class Store
{
	public:
	String country;
	String firm;
	String model;
	int size0;
	int price;
} ;
using namespace std;
extern vector <Store> goods;
extern int iMax,iCur;
//----------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
	TMainMenu *MainMenu1;
	TMenuItem *N1;
	TMenuItem *N3;
	TMenuItem *N4;
	TMenuItem *N5;
	TListView *ListViewShow;
	TGroupBox *GroupBox1;
	TEdit *Edit1;
	TEdit *Edit2;
	TEdit *Edit4;
	TEdit *Edit5;
	TButton *ButtonAdd;
	TButton *Button3;
	TLabel *Label1;
	TLabel *Label2;
	TLabel *Label3;
	TLabel *Label4;
	TLabel *Label5;
	TComboBox *ComboBox1;
	TButton *Button5;
	TSaveDialog *SaveDialog1;
	TOpenDialog *OpenDialog1;
	TButton *Button2;
	TMenuItem *N2;
	TMenuItem *N6;
	TGroupBox *GroupBox2;
	TButton *Button4;
	TEdit *EditSearch;
	TRadioButton *RadioButton1;
	TRadioButton *RadioButton2;
	TRadioButton *RadioButton3;
	TRadioButton *RadioButton4;
	TRadioButton *RadioButton5;
	TImageList *ImageList1;
	void __fastcall ButtonAddClick(TObject *Sender);
	void __fastcall N5ExitClick(TObject *Sender);
	void __fastcall ButtonDeleteAllClick(TObject *Sender);
	void __fastcall ListViewShowColumnClick(TObject *Sender, TListColumn *Column);
	void __fastcall ListViewShowCompare(TObject *Sender, TListItem *Item1, TListItem *Item2,
		  int Data, int &Compare);
	void __fastcall N4SaveClick(TObject *Sender);
	void __fastcall N3OpenClick(TObject *Sender);
	void __fastcall ButtonSearchClick(TObject *Sender);
	void __fastcall ButtonEditClick(TObject *Sender);
	void __fastcall ButtonEraseClick(TObject *Sender);
	void __fastcall Edit1KeyPress(TObject *Sender, System::WideChar &Key);
	void __fastcall Edit2KeyPress(TObject *Sender, System::WideChar &Key);
	void __fastcall ComboBox1KeyPress(TObject *Sender, System::WideChar &Key);
	void __fastcall N6Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TForm1(TComponent* Owner);
	void __fastcall Add();
    void __fastcall update();
	int TForm1::CompareInt(int x, int y);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
