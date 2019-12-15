//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
#include <algorithm>
TForm1 *Form1;
TListView *ListViewShow;
int ColumnToSort = 0;
bool a = true;
vector <Store> goods;
int iMax=0 ,iCur=0;


 void __fastcall TForm1::Add()
 {
	try
	{
	   if(Edit5->Text.ToInt() < 10000 && Edit5->Text.ToInt() > 500
	   && Edit4->Text.ToInt() < 46 && Edit4->Text.ToInt() > 25)
		{
			Store NewStore;
			NewStore.country = (AnsiString)Edit1->Text.c_str();
			NewStore.firm = (AnsiString)Edit2->Text.c_str();
			NewStore.model = (AnsiString)ComboBox1->Text.c_str();
			NewStore.size0 = Edit4->Text.ToIntDef(0);
			NewStore.price = Edit5->Text.ToIntDef(0);
			goods.push_back(NewStore);
			iCur = iMax;
			iMax++;
			update();
		}
		else
		{
			ShowMessage("Размер должен быть больше 25, но меньше 46. А цена больше 500, но меньше 10000") ;
		}
	}
	catch(...){ShowMessage("Введите данные");}
 }

   void __fastcall TForm1::update()
  {
		TListItem *Item;
		ListViewShow->Clear() ;
      	for (int i = 1; i<=goods.size(); i++) {
			Item = ListViewShow->Items->Add();
			Item->Caption=i;
			Item->SubItems->Add((AnsiString)(goods[i-1].country));
			Item->SubItems->Add((AnsiString)(goods[i-1].firm));
			Item->SubItems->Add((AnsiString)(goods[i-1].model));
			Item->SubItems->Add(goods[i-1].size0);
			Item->SubItems->Add(goods[i-1].price);
		}
  }


int TForm1::CompareInt(int x, int y)
{
	if(x==y) return 0;
	if(x>y) return 1;
	return -1;
}


//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm1::ButtonAddClick(TObject *Sender) // добавить - завершено
{
	try
	{
		Add();
	}
	catch(...)
	{}
}
//---------------------------------------------------------------------------
void __fastcall TForm1::N5ExitClick(TObject *Sender) //выход
{
	  Close();
}
//----------------------------------------------------------------------------

void __fastcall TForm1::ButtonDeleteAllClick(TObject *Sender)  // удалить всё
{
	goods.erase(goods.begin(),goods.end());
    ListViewShow->Clear();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::ListViewShowColumnClick(TObject *Sender, TListColumn *Column)
//сортировка
{
	if((a == true)|| (ColumnToSort != Column->Index)) a = false;
	else if((a==false)|| (ColumnToSort != Column->Index)) a = true;
	ColumnToSort = Column->Index;
	dynamic_cast<TCustomListView*>(Sender)->AlphaSort();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ListViewShowCompare(TObject *Sender, TListItem *Item1, TListItem *Item2,
		  int Data, int &Compare)    // сортировка - завершено
{
		if (ColumnToSort == 0)
		{
			Compare = CompareInt(Item1->Caption.ToIntDef(0),Item2->Caption.ToIntDef(0));
		}
		else if (ColumnToSort == 4)
		{
			Compare = CompareInt(Item1->SubItems->Strings[3].ToIntDef(0),
				Item2->SubItems->Strings[3].ToIntDef(0));
		}
		else if (ColumnToSort == 5)
		{
			Compare = CompareInt(Item1->SubItems->Strings[4].ToIntDef(0),
				Item2->SubItems->Strings[4].ToIntDef(0));
		}
		else
		{
			int ix = ColumnToSort - 1;
			Compare = CompareText(Item1->SubItems->Strings[ix],
				Item2->SubItems->Strings[ix]);
		}
		if(a)
            Compare = -Compare;

}
//---------------------------------------------------------------------------



void __fastcall TForm1::N4SaveClick(TObject *Sender) // сохранение - завершено
{
	if(SaveDialog1->Execute())
	{
		TStringList *GoodsFile = new TStringList;
		for (int i = 0; i < ListViewShow->Items->Count;i++) {
			GoodsFile->Add(ListViewShow->Items->Item[i]->Caption);
			GoodsFile->Add(ListViewShow->Items->Item[i]->SubItems->Text);
		}
		GoodsFile->SaveToFile((AnsiString)SaveDialog1->FileName,TEncoding::UTF8);
	}
}
//---------------------------------------------------------------------------
void __fastcall TForm1::N3OpenClick(TObject *Sender) // открытие - завершено
{
	if(OpenDialog1->Execute())
	{

		TListItem *part,*Item;
		TStringList *GoodsFile1 = new TStringList;
		GoodsFile1->LoadFromFile((AnsiString)OpenDialog1->FileName);
		ListViewShow->Items->Clear();
		goods.clear() ;
		for (int i= 0 ; i <= GoodsFile1->Count-1;i+=7) {
			Store NewStore;
			NewStore.country = GoodsFile1->Strings[i+1];
			NewStore.firm = GoodsFile1->Strings[i+2];
			NewStore.model = GoodsFile1->Strings[i+3];
			NewStore.size0 = GoodsFile1->Strings[i+4].ToInt();
			NewStore.price = GoodsFile1->Strings[i+5].ToInt();
			goods.push_back(NewStore);


		}
		update();
	}
}


//---------------------------------------------------------------------------
void __fastcall TForm1::ButtonSearchClick(TObject *Sender)    // поиск - завершенно
{

	if(RadioButton5->Checked) // цена
	{
		Store a;
		a.size0 = EditSearch->Text.ToInt();
		for(int i = 0; i < ListViewShow->Items->Count;i++  )
		{
		   if(a.size0 == ListViewShow->Items->Item[i]->SubItems->Strings[4])
			{
				ListViewShow->Items->Item[i]->Selected = true;
				return;
			}

		}
	}
	if(RadioButton4->Checked) // размер
	{
		Store a;
		a.size0 = EditSearch->Text.ToInt();
		for(int i = 0; i < ListViewShow->Items->Count;i++  )
		{
		   if(a.size0 == ListViewShow->Items->Item[i]->SubItems->Strings[3])
			{
				ListViewShow->Items->Item[i]->Selected = true;
				return;
			}
		}
	}
	if(RadioButton2->Checked) // страна
	{
		Store a;
		a.country = EditSearch->Text.c_str();
		for(int i = 0; i < ListViewShow->Items->Count;i++  )
		{
		   if(a.country == ListViewShow->Items->Item[i]->SubItems->Strings[0])
			{
				ListViewShow->Items->Item[i]->Selected = true;
				return;
			}
		}
	}
	if(RadioButton1->Checked) // фирма
	{
		Store a;
		a.firm = EditSearch->Text.c_str();
		for(int i = 0; i < ListViewShow->Items->Count;i++  )
		{
		   if(a.firm == ListViewShow->Items->Item[i]->SubItems->Strings[1])
			{
				ListViewShow->Items->Item[i]->Selected = true;
				return;
			}
		}
	}
	if(RadioButton3->Checked)  // модель
	{
		Store a;
		a.model = EditSearch->Text.c_str();
		for(int i = 0; i < ListViewShow->Items->Count;i++  )
		{
		   if(a.model == ListViewShow->Items->Item[i]->SubItems->Strings[2])
			{
				ListViewShow->Items->Item[i]->Selected = true;
				return;
			}
		}
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ButtonEditClick(TObject *Sender)  // изменить - завершено
{
	try
	{
	 if(Edit5->Text.ToInt() < 10000 && Edit5->Text.ToInt() > 500
	   && Edit4->Text.ToInt() < 46 && Edit4->Text.ToInt() > 25)
		{
			TListItem *Item;
			int i = ListViewShow->ItemIndex;
			Item = ListViewShow->Items->Item[i];
			Item->SubItems->Strings[0]=Edit1->Text;
			Item->SubItems->Strings[1]=Edit2->Text;
			Item->SubItems->Strings[2]=ComboBox1->Text;
			Item->SubItems->Strings[3]=Edit4->Text.ToIntDef(0);
			Item->SubItems->Strings[4]=Edit5->Text.ToIntDef(0);
			Edit4->Text = Item->SubItems->Strings[3];
			Edit5->Text = Item->SubItems->Strings[4];
		}
		else
			ShowMessage("Размер должен быть больше 25, но меньше 46. А цена больше 500, но меньше 10000") ;


	}
	catch(...)
	{
		ShowMessage("Пожалуйста, выделити строчку, которую хотите изменить или заполните таблицу");
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ButtonEraseClick(TObject *Sender)  // удалить - завершено
{
	int a = ListViewShow->ItemIndex;
	try{
		if(goods.empty())
		{
			ListViewShow->Items->Delete(a);
			for (int i = 0; i<ListViewShow->Items->Count; i++)
			{
					ListViewShow->Items->Item[i]->Caption = i+1;
			}
		}
		else
		{
			goods.erase(goods.begin()+a);
			ListViewShow->Items->Delete(a);
			for (int i = 0; i<ListViewShow->Items->Count; i++)
				ListViewShow->Items->Item[i]->Caption = i+1;
		}
	}
	catch(...)
		{ShowMessage("Пожалуйста, выделити строчку, которую хотите удалить или таблица пуста");}
}
//---------------------------------------------------------------------------



void __fastcall TForm1::Edit1KeyPress(TObject *Sender, System::WideChar &Key)
{
	if ((AnsiString)(Key) >= 'А' && (AnsiString)(Key) <= 'я')
		return;
	if (Key >= 'A' && Key <= 'z')
		return;
	if(Key == VK_BACK)
		return;
	Key = 0;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Edit2KeyPress(TObject *Sender, System::WideChar &Key)
{
	if ((AnsiString)(Key) >= 'А' && (AnsiString)(Key) <= 'я')
		return;
	if (Key >= 'A' && Key <= 'z')
		return;
	if(Key == VK_BACK)
		return;
	Key = 0;
}
//---------------------------------------------------------------------------


void __fastcall TForm1::ComboBox1KeyPress(TObject *Sender, System::WideChar &Key)

{
if ((AnsiString)(Key) >= 'А' && (AnsiString)(Key) <= 'я')
		return;
	if (Key >= 'A' && Key <= 'z')
		return;
	if(Key == VK_BACK)
		return;
	Key = 0;
}
//---------------------------------------------------------------------------



void __fastcall TForm1::N6Click(TObject *Sender)
{
     ShowMessage("Программа для регистрации обувной продукции");
}
//---------------------------------------------------------------------------


