//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
      orderNum = 0;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::init()
{
    for(int i=0;i<=30;i++){
      //标签初始化
      label[i]->Visible = false;
      label[i]->Caption = "";
      label[i]->Color=clYellow;

      //线条初始化
      if(i%2 == 0 && i<30)
      {
        image[i]->Canvas->MoveTo(image[i]->Width,0);
        image[i]->Canvas->LineTo(0,image[i]->Height);
        image[i]->Visible = false;
      }
      if(i%2 == 1 && i<30)
      {
        image[i]->Canvas->MoveTo(0,0);
        image[i]->Canvas->LineTo(image[i]->Width,image[i]->Height);
        image[i]->Visible = false;
      }
    }
}

void __fastcall TForm1::firstMap(AnsiString firstList[],AnsiString middleList[],int length,int direction,int pos)
{
       AnsiString root = firstList[0];    //根节点
       if(direction == -1)
          pos = 2*pos+1;
       if(direction == 1)
          pos = 2*pos+2;
       label[pos]->Caption = "    " + root;   //根节点名字

       order[orderNum++] = pos;
       if(orderNum == orderLength)
       {
          orderNum = 0;
          Timer1->Enabled = true;
       }

       if(length == 1) return;      //递归截止条件

       if(root == middleList[0])
       {
           AnsiString temFirst[31];
           AnsiString temMiddle[31];
           for(int i=1;i<length;i++)
           {
              temFirst[i-1] = firstList[i];
              temMiddle[i-1] = middleList[i];
           }
           firstMap(temFirst,temMiddle,length-1,1,pos);
       }
       else if(root == middleList[length-1])
       {
           AnsiString temFirst[31];
           AnsiString temMiddle[31];
           for(int i=1;i<length;i++)
           {
              temFirst[i-1] = firstList[i];
              temMiddle[i-1] = middleList[i-1];
           }
           firstMap(temFirst,temMiddle,length-1,-1,pos);
       }
       else
       {
           for(int i=0;i<length;i++)
           {
               if(root == middleList[i])
               {
                  AnsiString temFirst1[31];
                  AnsiString temMiddle1[31];
                  for(int j=0;j<i;j++)
                  {
                      temFirst1[j] = firstList[j+1];
                      temMiddle1[j] = middleList[j];
                  }
                  firstMap(temFirst1,temMiddle1,i,-1,pos);

                  AnsiString temFirst2[31];
                  AnsiString temMiddle2[31];
                  for(int k=i+1;k<length;k++)
                  {
                      temFirst2[k-i-1] = firstList[k];
                      temMiddle2[k-i-1] = middleList[k];
                  }
                  firstMap(temFirst2,temMiddle2,length-i-1,1,pos);
               }
           }
       }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::lastMap(AnsiString middleList[],AnsiString lastList[],int length,int direction,int pos)
{
       AnsiString root = lastList[length-1];
       if(direction == -1)
          pos = 2*pos+1;
       if(direction == 1)
          pos = 2*pos+2;
       label[pos]->Caption = "    " + root;

       order[orderNum++] = pos;
       if(orderNum == orderLength)
       {
          orderNum = 0;
          Timer1->Enabled = true;
       }

       if(length == 1) return;

       if(root == middleList[length-1])
       {
           AnsiString temMiddle[31];
           AnsiString temLast[31];
           for(int i=0;i<length-1;i++)
           {
              temMiddle[i] = middleList[i];
              temLast[i] = lastList[i];
           }
           lastMap(temMiddle,temLast,length-1,-1,pos);
       }
       else if(root == middleList[0])
       {
           AnsiString temMiddle[31];
           AnsiString temLast[31];
           for(int i=1;i<length;i++)
           {
              temMiddle[i-1] = middleList[i];
              temLast[i-1] = lastList[i-1];
           }
           lastMap(temMiddle,temLast,length-1,1,pos);
       }
       else
       {
           for(int i=0;i<length;i++)
           {
               if(root == middleList[i])
               {
                  AnsiString temMiddle1[31];
                  AnsiString temLast1[31];
                  for(int j=0;j<i;j++)
                  {
                      temMiddle1[j] = middleList[j];
                      temLast1[j] = lastList[j];
                  }
                  lastMap(temMiddle1,temLast1,i,-1,pos);

                  AnsiString temMiddle2[31];
                  AnsiString temLast2[31];
                  for(int k=i;k<length-1;k++)
                  {
                      temMiddle2[k-i] = middleList[k+1];
                      temLast2[k-i] = lastList[k];
                  }
                  lastMap(temMiddle2,temLast2,length-i-1,1,pos);
               }
           }
       }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button1Click(TObject *Sender)
{
    init();
    AnsiString firstList[31];
    AnsiString middleList[31];
    AnsiString lastList[31];

    orderLength = Edit2->Text.Length();

    for(int i=0;i<orderLength;i++)
    {
       firstList[i] = Edit1->Text.SubString(i+1,1);
       middleList[i] = Edit2->Text.SubString(i+1,1);
       lastList[i] = Edit3->Text.SubString(i+1,1);
    }

    if(Edit1->Text.Length() == Edit2->Text.Length())
       firstMap(firstList,middleList,orderLength,0,0);
    else if(Edit3->Text.Length() == Edit2->Text.Length())
       lastMap(middleList,lastList,orderLength,0,0);
    else
       ShowMessage("输入格式有误");
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormCreate(TObject *Sender)
{
    label[0]=Label4;
    label[1]=Label5;
    label[2]=Label6;
    label[3]=Label7;
    label[4]=Label8;
    label[5]=Label9;
    label[6]=Label10;
    label[7]=Label11;
    label[8]=Label12;
    label[9]=Label13;
    label[10]=Label14;
    label[11]=Label15;
    label[12]=Label16;
    label[13]=Label17;
    label[14]=Label18;
    label[15]=Label19;
    label[16]=Label20;
    label[17]=Label21;
    label[18]=Label22;
    label[19]=Label23;
    label[20]=Label24;
    label[21]=Label25;
    label[22]=Label26;
    label[23]=Label27;
    label[24]=Label28;
    label[25]=Label29;
    label[26]=Label30;
    label[27]=Label31;
    label[28]=Label32;
    label[29]=Label33;
    label[30]=Label34;

    image[0] = Image1;
    image[1] = Image2;
    image[2] = Image3;
    image[3] = Image4;
    image[4] = Image5;
    image[5] = Image6;
    image[6] = Image7;
    image[7] = Image8;
    image[8] = Image9;
    image[9] = Image10;
    image[10] = Image11;
    image[11] = Image12;
    image[12] = Image13;
    image[13] = Image14;
    image[14] = Image15;
    image[15] = Image16;
    image[16] = Image17;
    image[17] = Image18;
    image[18] = Image19;
    image[19] = Image20;
    image[20] = Image21;
    image[21] = Image22;
    image[22] = Image23;
    image[23] = Image24;
    image[24] = Image25;
    image[25] = Image26;
    image[26] = Image27;
    image[27] = Image28;
    image[28] = Image29;
    image[29] = Image30;

    init();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Timer1Timer(TObject *Sender)
{
    label[order[orderNum]]->Visible = true;
    if(order[orderNum])
       image[order[orderNum]-1]->Visible = true;
    orderNum++;

    if(orderNum == orderLength)
    {
       orderNum = 0;
       Timer1->Enabled = false;
    }
}
//---------------------------------------------------------------------------





