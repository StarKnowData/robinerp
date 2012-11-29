<%@ Page Language="C#" AutoEventWireup="true" Inherits="Bzw.Inhersits.Manage.Manage_TwoPass" %>

<%@ Register TagName="Control" TagPrefix="WebTop" Src="~/Public/WebTop.ascx" %>
<%@ Register TagName="Control" TagPrefix="WebFooter" Src="~/Public/WebFooter.ascx" %>
<%@ Register TagName="Control" TagPrefix="WebService" Src="~/Public/WebLeft.ascx" %>
<%@ Register TagName="Control" TagPrefix="WebUserLogin" Src="~/Public/WebUserLogin.ascx" %>

<%@ Register TagName="Control" TagPrefix="Left" Src="~/Manage/Left.ascx" %>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head id="Head1" runat="server">
    <meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
    <title>
      
    </title>
  
    <link href="/css/layout.css" rel="stylesheet" type="text/css" />

    <script type="text/javascript" src="/Public/Js/jquery.js"></script>

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
                    银行密保</h3>
                <p class="dqwz">
                    当前位置：首页 > 会员中心 > 银行密保</p>
            </div>
            <div id="sub_nr">
                <div class="cz">
                    <form id="Form1" class="democss" runat="server" onsubmit="return onFormSubmit(this)">
                    <table width="100%" border="0" cellpadding="0" cellspacing="0" class="memberTable">
                        <tr>
                            <td width="20%" height="35" align="right" scope="row">
                                登录密码：
                            </td>
                            <td colspan="2" style="width: 80%">
                                <asp:TextBox ID="txtPassword" runat="server" CssClass="fr_input" TextMode="Password"
                                    MaxLength="20"></asp:TextBox>
                                <font class="red">*</font>
                            </td>
                        </tr>
                        <tr id="dd_1" runat="server" style="display: none;">
                            <td height="35" align="right" scope="row">
                                证件类型：
                            </td>
                            <td colspan="2">
                                <asp:DropDownList ID="ddlCardType" runat="server">
                                </asp:DropDownList>
                                <font class="red">*</font>
                            </td>
                        </tr>
                        <tr id="dd_3" runat="server">
                            <td height="35" align="right" scope="row">
                                身份证号：
                            </td>
                            <td colspan="2">
                                <asp:TextBox ID="txtCardNo" runat="server" CssClass="fr_input" MaxLength="18"></asp:TextBox>
                                <font class="red">*</font>
                            </td>
                        </tr>
                        <tr id="dd_5" runat="server">
                            <td height="35" align="right" scope="row">
                                确认身份证号：
                            </td>
                            <td colspan="2">
                                <asp:TextBox ID="txtCardNo2" runat="server" CssClass="fr_input" MaxLength="18"></asp:TextBox>
                                <font class="red">*</font>重复上面的身份证号
                            </td>
                        </tr>
                        <tr id="dd_7" runat="server">
                            <td height="35" align="right" scope="row">
                                提示问题：
                            </td>
                            <td colspan="2">
                                <asp:DropDownList ID="ddlQuestion" runat="server">
                                </asp:DropDownList>
                            </td>
                        </tr>
                        <tr id="dd_9" runat="server">
                            <td height="35" align="right" scope="row">
                                问题答案：
                            </td>
                            <td colspan="2">
                                <asp:TextBox ID="txtAnwer" runat="server" CssClass="fr_input"></asp:TextBox>
                                <font class="red">*</font>4-20位
                            </td>
                        </tr>
                        <tr id="dd_11" runat="server">
                            <td height="35" align="right" scope="row">
                                原银行密码：
                            </td>
                            <td colspan="2">
                                <asp:TextBox ID="txtOldTwoPass" runat="server" TextMode="Password" CssClass="fr_input"></asp:TextBox>
                                <font class="red"></font>不修改银行密码则不必填写此项！
                            </td>
                        </tr>
                        <tr>
                            <td height="35" align="right" scope="row">
                                新的银行密码：
                            </td>
                            <td colspan="2">
                                <asp:TextBox ID="txtTwoPass" runat="server" TextMode="Password" CssClass="fr_input"></asp:TextBox>
                                <font class="red"></font>不修改则不填，由6-20位英文字母或数字组成
                            </td>
                        </tr>
                        <tr>
                            <td height="35" align="right" scope="row">
                                确认银行密码：
                            </td>
                            <td colspan="2">
                                <asp:TextBox ID="txtTwoPass2" runat="server" TextMode="Password" CssClass="fr_input"></asp:TextBox>
                                <font class="red"></font>重复上面的银行密码
                            </td>
                        </tr>
                        <tr>
                            <td colspan="3" style="height: 20px;">
                                <asp:Label ID="lblMsg" runat="server" Font-Bold="True" ForeColor="Red"></asp:Label>
                            </td>
                        </tr>
                        <tr>
                            <td height="76" scope="row">
                                &nbsp;
                            </td>
                            <td width="47%">
                                <input type="submit" class="but_01" value="  " onserverclick="button5_ServerClick"
                                    runat="server" id="button5" />
                            </td>
                            <td width="31%">
                                &nbsp;
                            </td>
                        </tr>
                    </table>
                    </form>

                    <script type="text/javascript">
<!--  
     function checkIC()
  {
  var selval=document.getElementById ("ddlCardType").value;//Type
  var values = document.getElementById ("txtCardNo").value;//Num
  var length=document.getElementById ("txtCardNo").value.length;
  
  if (selval=="1")
  {         
        if(values!="")
        {
            if(!checkIDCard(values))
            {
                alert("身份证号码不正确！");
                //document.getElementById ("txtCardNo").focus();
                return false;
            }
        }
    }
    else if(selval=="4")
    {
        if(values!="")
        {
            if(!checkphone(values)){
               alert("电话号码不正确！");               
               return false;         
            }

        }
    }
    else 
    {
        if(values!="")
        {
            if (!isNaN(values))
            {
                 if (length<6 || length>20)
                {
                    alert("证件号码长度必须是6-20位！");
                    return false; 
                }
            }
            else
            {
                alert("证件号码必须是数字！!");
                return false;
            }
        } 
    }
    return true;
  }
  function   checkIDCard   (str)     
  {   //身份证正则表达式(15位)     
        //isIDCard1=/^[1-9]\d{7}((0\d)|(1[0-2]))(([0|1|2]\d)|3[0-1])\d{3}$/;   
        //身份证正则表达式(18位)   
        isIDCard2=/^[1-9]\d{5}[1-9]\d{3}((0\d)|(1[0-2]))(([0|1|2]\d)|3[0-1])\d{3}[x|X|\d]$/;   
        //验证身份证，返回结果     
        return   (isIDCard2.test(str));   
   }
   function checkphone(str)
   {
        isphone=/^(\(\d{3,4}\)|\d{3,4}-|\d{3})\d{7,8}$/;
        return (isphone.test(str));
   }
    function onFormSubmit(f){
        
        //登录密码----------
        var password = document.getElementById('txtPassword');
        var oldTwoPass = document.getElementById("<%=txtOldTwoPass.ClientID%>");
        if(!alertNull(password,'请输入登录密码！')){
            return false;
        }
        if( oldTwoPass != null && !alertNull(oldTwoPass,'请输入原银行密码！')){
            return false;
        }
        
        try{
            //证件新型---------
          //  var ZJ_Type = document.getElementById('ddlCardType');
           
           // if(ZJ_Type.selectedIndex<1){
           //     alert('请选择证件类型！');
           //     ZJ_Type.focus();
            //    return false;
         //   }
            
            //证件号码-----------
            var ZJ_Number = document.getElementById('txtCardNo');
            var ZJ_Number2 = document.getElementById('txtCardNo2');
            if(!alertNull(ZJ_Number,'请输入证件号码！')){
                return false;
            }
            else if(!/^[0-9a-zA-Z]{6,20}$/.test(ZJ_Number.value)){
                alert('证件号码由6-20位数字组成，请重新输入！');
                ZJ_Number.focus();
                return false;
            }
            
            if(ZJ_Number.value.trim() != ZJ_Number2.value.trim()){
                alert('两次输入证件号码不一致！');
                ZJ_Number2.focus();
                return false;
            }
              if(!checkIC())
				return false;
            //提示问题-----------
            var question = document.getElementById('ddlQuestion');
            if(question.selectedIndex<1){
                alert('请选择提示问题！');
                question.focus();
                return false;
            }
            
            //问题答案-----------
            var Answer = document.getElementById('txtAnwer');
            if(!alertNull(Answer,'请输入问题答案！')){
                return false;
            }else if(Answer.value.trim().length<4 || Answer.value.trim().length>20){
                alert('问题答案的长度为4-20位！');
                Answer.focus();
                return false;
            }
        }catch(e){}
        
        
        //银行密码-----------
        var pass = document.getElementById('txtTwoPass');
        var pass2 = document.getElementById('txtTwoPass2');
        
        if(pass.value.trim().length > 0){
            if(!/^[0-9a-zA-Z]{6,20}$/.test(pass.value)){
                alert('银行密码由英文字母或数字组成，长度为6-20位，请重新输入！');
                pass.focus();
                return false;
            }
        }
        
        if(pass.value.trim() != pass2.value.trim()){
            alert('两次输入的银行密码不一致！');
            pass2.focus();
            return false;
        }
        
        return true;
    }
 //-->
                    </script>

                    <br />
                    <div runat="server" id="divNotes">
                        <p>
                            <strong>注意：</strong>请记住您填写的证件号码、提示问题答案。密码保护问题和答案、证件类型和号码输入后不可修改。</p>
                    </div>
                    <div runat="server" id="divNotes2" style="display: none;">
                        <p>
                            <strong>注意：</strong>您已经设置了密码保护答案、证件类型，如果需要修改，请联系客服。</p>
                    </div>
                </div>  
            </div>  <p>
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
