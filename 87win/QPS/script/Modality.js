// JScript 文件

//弹出一个模态窗口 有返回值
function OpenEditWin(frmWin,width,height,textbox) 
{      
    var me;
    // 把父页面窗口对象当作参数传递到对话框中，以便对话框操纵父页自动刷新。
    me = window;
    // 显示对话框。
     var selname = new Array(3);
         selname = window.showModalDialog(frmWin,me,'dialogWidth='+width +'px;dialogHeight='+height+'px;help:no;status:no;scroll=no;')
         
         
    switch(textbox){   
  　　case   "SampType":
  　　if(selname != null)
        {
    
          document.MainFrom.txSampType.value = selname[0];
          document.MainFrom.txShowSampTypeID.value = selname[1];
          //document.MainFrom.txSampNO.value = selname[2];
          
         }
      
  　　
  　　break;   
  　　
  　　case   "CheckUserinfo":
  　　if(selname != null)
      {

          document.MainFrom.Txt_jspm.value = selname[0];
          document.MainFrom.HiJspmId.value = selname[1];
          //document.MainFrom.txSampNO.value = selname[2];
          
      }
  　　break;   
  　　
  　　case   "SampFactory":   
  　　
  　　if(selname != null)
        {
          document.MainFrom.txSampFactory.value = selname[0];
          document.MainFrom.txShowFactory.value = selname[1];
         }
     
  　　  　break;
  　　  　
  　　case   "SampQuanUnit":   
  　　
  　　if(selname != null)
        {
          document.MainFrom.txSampQuanUnit.value = selname[0];
          document.MainFrom.txSampQuanUnitID.value = selname[1];
         }
     
  　　  　break;
  　　  　
  　　 case   "SampSource":   
  　　
  　　if(selname != null)
        {
          document.MainFrom.txSampSource.value = selname[0];
          document.MainFrom.txSampSourceID.value = selname[1];
         }
       
  　　  　break; 　
  　　  　
  　　 case   "SampPack":   
  　　
  　　if(selname != null)
        {
          document.MainFrom.txSampPack.value = selname[0];
          document.MainFrom.txSampPackID.value = selname[1];
         }
     
  　　  　break; 　
  　　  　
  　 case   "CollUnit":   
  　　
  　　if(selname != null)
        {
          document.MainFrom.txSampCollUnit.value = selname[0];
          document.MainFrom.txSampCollUnitID.value = selname[1];
         }
       
  　　  　break; 　
  　　  　
  　 case   "TestUnit":   
  　　
  　　if(selname != null)
        {
          document.MainFrom.txSampTestUnit.value = selname[0];
          document.MainFrom.txSampTestUnitID.value = selname[1];
         }
   
  　　  　break; 　
  　　case   "Purpose":   
  　　
  　　if(selname != null)
        {
          document.MainFrom.txSampPurpose.value = selname[0];
          document.MainFrom.txSampPurposeID.value = selname[1];
         }
   
  　　  　break; 
  　　 case   "QuanUnit":   
  　　
  　　if(selname != null)
        {
          document.QuanUnitFrom.txQuanUnit.value = selname[0];
          
          document.QuanUnitFrom.txQuanUnitID.value = selname[1];
          
         }
   
  　　  　break;　
  　　case   "Laboratory":   
  　　
  　　if(selname != null)
        {
          document.QuanUnitFrom.txLaboratory.value = selname[0];
          
          document.QuanUnitFrom.txLaboratoryID.value = selname[1];
          
         }
   
  　　  　break;
  　　  　
  　　 case "TestSign":
  　　  if(selname != null)
        {
          document.TestFrom.txSign.value = selname[0];
          
          document.TestFrom.txSigeID.value = selname[1];
          
         }
         break;
         
        case "TestMethod":
  　　  if(selname != null)
        {
          document.TestFrom.txMtdName.value = selname[0];
          
          document.TestFrom.txMtdID.value = selname[1];
          
         }
         break;
         
        case "AddProject":
  　　  if(selname != null)
        {
          document.FormProj.tx_Project.value = selname[0];
          
          document.FormProj.txProjectID.value = selname[1];
          
         }
         break;
  　　default:
  　　break;  
  }

} 
//


//弹出一个模态窗口 无返回值
function OpenWin(frmWin,width,height) 
{      
    var me;
    // 把父页面窗口对象当作参数传递到对话框中，以便对话框操纵父页自动刷新。
    me = window;
    // 显示对话框。
    var i = window.showModalDialog(frmWin,me,'dialogWidth='+width +'px;dialogHeight='+height+'px;help:no;status:no;scroll=no;')
    if(i != null) {

        window.dialogArguments.location.reload();
        window.close();
        return true;
    }
    return false;
} 




//AJAX JS调用后台程序 (没做完)
// function TypeShow() 
// { 
//     var TypeName=document.getElementById("txTypeName");
//     var SampType =document.getElementById("txddlTypeSel");
//     MyAjaxNetTest.EnvironmentalTest_SampTypes.GetShowBind(SampType.value,TypeName.value,Result_CallBack);
//     
// }
// function Result_CallBack(response)
// {
//     if (response.value != null)
//     {                    
//         //debugger;
//         document.getElementById("dglist").style.display="block";
//                   
//         var ds = response.value;
//         if(ds != null && typeof(ds) == "object" && ds.Tables != null)
//         {                    
//             for(var i=0; i<ds.Tables[0].Rows.length; i++)
//             {
//                 var TypeID=ds.Tables[0].Rows[i].TypeID;
//                 var Type=ds.Tables[0].Rows[i].Type;
//                 var TypeCode=ds.Tables[0].Rows[i].TypeCode;
//                 var IME_PY=ds.Tables[0].Rows[i].IME_PY;
//                 var IME_EX=ds.Tables[0].Rows[i].IME_EX;
//                 
//                 document.getElementById("dglist").options.add(new Option(TypeID,Type,TypeCode,IME_PY,IME_EX));
//             }
//         }
//     }
//     else
//     {
//         document.getElementById("dglist").style.display="none";
//     }             
//     return
// }
 

 var objcolor
 //------------鼠标经过时-----------
function OnFoucsMouseOver(obj)
{
 objcolor= obj.style.backgroundColor;
  obj.style.backgroundColor =  "#68A6E4";

}


//-----------鼠标离开时-----------
function OnFoucsMouseOut(obj)
{
   obj.style.backgroundColor = objcolor;
}

//------------鼠标双击时----------
function OnFoucsDbClick(index,id)
{

  var myArray=new Array(2);
    myArray[0] =index;
     myArray[1] = id;
 
  window.returnValue = myArray;
 
  window.close();
}

//------------鼠标双击时----------
function OnFoucsDbClickTo(index,id,text)
{

  var myArray=new Array(3);
    myArray[0] =document.getElementById("dglist").rows[index+1].cells[0].innerText;
     myArray[1] = id;
 myArray[2] =text;
  window.returnValue = myArray;
 
  window.close();
}



//全选
function SelectAll(tempControl)
{
       //将除头模板中的其它所有的CheckBox取反 

        var theBox=tempControl;
         xState=theBox.checked;    

        elem=theBox.form.elements;
        for(i=0;i<elem.length;i++)
        if(elem[i].type=="checkbox" && elem[i].id!=theBox.id)
         {
             elem[i].checked=xState;
                   
        }
  }  


  

 
