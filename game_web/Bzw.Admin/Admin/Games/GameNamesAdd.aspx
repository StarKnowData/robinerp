<%@ Page Language="C#" AutoEventWireup="true" Inherits="Admin_Games_GameNamesAdd" Codebehind="GameNamesAdd.aspx.cs" %>

<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head runat="server">
    <title>无标题页</title>
    <meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
    <link href="../css/inc_style.css" rel="stylesheet" type="text/css" />
    <script type="text/javascript" src="/Public/Js/Global.js"></script>
    <style type="text/css">
    <!--
    body {
	    background-color: #FFFFFF;
	    margin-top: 0px;
    }
    -->
    </style>
    <script language="javascript" type="text/javascript">

    function CheckForm() {

        var nameId = document.getElementById("NameID");
      if(!alertNull(nameId,'温馨提示：\n\n请输入游戏ID号！')) {
        return false;
      }
      else if(!alertNonNegativeNumber(nameId,'温馨提示：\n\n游戏ID号请输入一个正的数字！')) {
        return false;
      }else{
        var urlData = '../XmlHttpAdmin.aspx?type=nameidexist&nameid='+escape(nameId.value);
        //alert(urlData);
        var strReturn = AjaxCall(urlData);
        //alert(strReturn);
        if(strReturn=="1"){
            alert('对不起，这个游戏ID号已经存在。');
            nameId.focus();
            return false;
        }
      }
      
      if(document.getElementById("ComName").value == '') {
        alert('温馨提示：\n\n请输入游戏名称！');
        document.getElementById("ComName").focus();
        return false;
      }
      
        if(document.getElementById("ComProcess").value == '') {
        alert('温馨提示：\n\n请输入客户端EXE文件名！');
        document.getElementById("ComProcess").focus();
        return false;
      }
      
      if(!alertNull(document.getElementById("IDSort"),'温馨提示：\n\n请输入排列号！')) {
        return false;
      }
      else if(!alertNonNegativeNumber(document.getElementById("IDSort"),'温馨提示：\n\n排列号请输入一个正的数字！')) {
        return false;
      }
      
        if(document.getElementById("DLLFileName").value == '') {
        alert('温馨提示：\n\n请输入游戏服务端文件名！');
        document.getElementById("DLLFileName").focus();
        return false;
      }
      
        if(!alertNull(document.getElementById("DeskPeople"),'温馨提示：\n\n请输入桌子上的人数！')) {
        return false;
      }
      else if(!alertNonNegativeNumber(document.getElementById("DeskPeople"),'温馨提示：\n\n桌子上的人数请输入一个正的数字！')) {
        return false;
      }
    }
    </script>

</head>
<body>
    <form id="form1" runat="server"  >
        <table width="100%" border="1" align="center" cellpadding="3" cellspacing="0" bordercolor="A4B6D7"
            bgcolor="F2F8FF" class="admin_table">
            <tr>
                <td class="title_03" colspan="2">
                    <strong>添加游戏信息</strong></td>
            </tr>
            <tr>
                <td align="right">
                    游戏类别：</td>
                <td align="left">
                    <asp:DropDownList ID="KindID" runat="server" 
                        onselectedindexchanged="KindID_SelectedIndexChanged"  
                        AutoPostBack="true" >
                    </asp:DropDownList>
                    <a href="GameTypesAdd.aspx">添加游戏类别</a>
                </td>
            </tr>
            <tr>
            <td align="right">二级游戏目录：</td>
            <td align="left">
            <asp:DropDownList ID="ChildKindID" runat="server">
            
            </asp:DropDownList>
            </td>
            </tr>
            <tr>
                <td align="right">
                    游戏ID号：</td>
                <td align="left">
                    <input type="text" name="NameID" value='' class="put" maxlength="9" /><font color="red">（需与游戏提供商咨询）</font>
                </td>
            </tr>
            <tr>
                <td align="right">
                    游戏名称：</td>
                <td align="left">
                    <input type="text" id="ComName" name="ComName" class="put" maxlength="14"/></td>
            </tr>
            <% %>
             <tr>
                <td align="right">
                    房间租赁价格设置：</td>
                <td align="left">
                    <input type="text" id="EveryDayRent" name="EveryDayRent" class="put" maxlength="19"  value="0" />金币/每日（填写整数，0表示不开通租凭房间）</td>
            </tr>
            
            
            
            <tr><td style="padding-left:250px;" colspan="2"><b>客户端资料</b></td></tr>
            
            <tr>
                <td align="right">
                    客户端EXE文件名：</td>
                <td align="left">
                    <input type="text" id="ComProcess" name="ComProcess" class="put" maxlength="20"/>（如：10000305.exe，需与游戏提供商咨询）</td>
            </tr>
            <tr>
                <td align="right">
                    排列号：</td>
                <td align="left">
                    <input type="text" id="IDSort" name="IDSort" value="0" class="put" maxlength="4" /></td>
            </tr>
            <tr>
                <td align="right">
                    是否激活：</td>
                <td align="left">
                    <input name="Enable" type="radio" value="1" checked Class="put"/>激活
                    <input name="Enable" type="radio" value="0" Class="put"/>未激活
                </td>
            </tr>
            
            <tr><td style="padding-left:250px;" colspan="2"><b>服务端资料</b></td></tr>
            
            <tr>
                <td align="right">
                    服务端文件名：</td>
                <td align="left">
                    <input type="text" id="DLLFileName" name="DLLFileName" class="put" maxlength="20" />（比如：XQSrv.DLL）</td>
            </tr>
            <tr>
                <td align="right">
                    桌子上的人数：</td>
                <td align="left">
                    <input type="text" id="DeskPeople" name="DeskPeople" value="4" class="put" maxlength="4" />
                </td>
            </tr>
            
            <tr>
            <td align="right">
                <input type="hidden" name="action" value="add" />
                <input type="hidden" name="action2" value="add" />
            </td>
            <td align="left">
                <asp:Button ID="Button1" runat="server" Text=" 添 加 " class="put"  OnClick="GameNaemAdd"/>
                <input name="reback" type="button" value="返回上一页" class="put" onclick="javascript:history.back();" />
            </td>
            </tr>
        </table>
    </form>
</body>
</html>
