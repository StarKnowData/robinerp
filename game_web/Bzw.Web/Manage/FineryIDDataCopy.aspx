<%@ Page Language="C#" AutoEventWireup="true" Inherits="Bzw.Inhersits.Manage.FineryIDDataCopy" %>

<%@ Register TagName="Control" TagPrefix="WebTop" Src="~/Public/WebTop.ascx" %>
<%@ Register TagName="Control" TagPrefix="WebFooter" Src="~/Public/WebFooter.ascx" %>
<%@ Register TagName="Control" TagPrefix="WebService" Src="~/Public/WebLeft.ascx" %>
<%@ Register TagName="Control" TagPrefix="WebUserLogin" Src="~/Public/WebUserLogin.ascx" %>

<%@ Register TagName="Control" TagPrefix="Left" Src="~/Manage/Left.ascx" %>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head id="Head1" runat="server">
    <title>
      
    </title>
  
    <link href="/css/layout.css" rel="stylesheet" type="text/css" />

    <script type="text/javascript" src="/Public/Js/common.js"></script>

    <script type="text/javascript" src="/Public/Js/Global.js"></script>

</head>
<body>
    <div id="container">
        <!--header-->
        <WebTop:Control ID="webTopOne" runat="server" />
        <!--content-->
        <div id="left">
            <Left:Control ID="leftOne" runat="server" />
            <WebService:Control ID="webServiceOne" runat="server" />
        </div>
        <div id="content01">
            <div id="title01">
                <h3 class="fl">
                    靓号数据转移</h3>
                <p class="dqwz">
                    当前位置：首页 > 会员中心 > 靓号数据转移</p>
            </div>
            <div id="sub_nr" style="margin-top: 10px;">
                <div id="memText01">
                    <form id="frmcopy" runat="server" onsubmit="return onFormSubmit(this)" action="">
                        <asp:TextBox ID="hidden" runat="server" Style="visibility: hidden; display: none;"></asp:TextBox>
                    <div class="cz">
                        <table width="100%" border="0">
                            <tr>
                                <th  align="left">
                                    从大号：
                                </th>
                               <td>
                                ID：<%=userid %>
                                    &nbsp; 用户名：<%=username %>
                               </td>
                            </tr>
                            
                            <tr>
                                <th width="18%" height="30" align="left" scope="row">
                                    大号银行密码：
                                </th>
                                <td>
                                    <input name="pwd" type="password" id="pwd" maxlength="20" style="width: 149px;" />
                                    <span class="red">*</span><span class="note" id="pwdspan">请输入您大号银行密码，以确保安全</span>
                                </td>
                            </tr>
                            
                            <tr>
                                <th align="left">
                                    转移至靓号：
                                </th>
                                  <td   height="30" scope="row" align="left">
                                    ID：<%=fineryid %>
                                    &nbsp; 用户名：<%=frusername %>
                                </td>
                            </tr>
                                <tr>
                            <td  colspan="2" style=" text-align:center;">
                                <input type="submit" id="submit" runat="server" onserverclick="Button1_Click" value="确定转移"
                                    class="but_011" />&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
                            </td>
                        </tr>
                        </table>
                    </div>
                 
                    </form>
                </div>
            </div>
            <p>
                <img src="/Images/cont_img01.jpg" alt="" /></p>
        </div>
        <div class="clear">
        </div>
    </div>
    <!--right End-->
   
    <!--footer-->
    <WebFooter:Control ID="webFooterone" runat="server" />
</body>
</html>

<script type="text/javascript">
    /*===Check Pwd========================*/
    function onFormSubmit(f) {
        var txt = document.getElementById('pwd');
        var tip = document.getElementById("pwdspan");

        //valid is null--------------
        if (txt.value.trim().length == 0) {
            tip.className = "note_no";
            return false;
        }
        //valid regx-----------------
        if (!/^[0-9a-zA-Z]{6,20}$/.test(txt.value)) {
            tip.className = "note_no";
            return false;
        }
        return true;
    }
</script>

