<%@ Page Language="C#" AutoEventWireup="true" Inherits="Admin_Agency_AgencyDetailInfo" Codebehind="AgencyDetailInfo.aspx.cs" %>

<%@ Register Assembly="FredCK.FCKeditorV2" Namespace="FredCK.FCKeditorV2" TagPrefix="FCKeditorV2" %>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head id="Head1" runat="server">
	<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
	<title>代理商信息维护</title>
	<script type="text/javascript" src="/Public/Js/Global.js"></script>
</head>
<body>
	<form id="form1" runat="server">
		<div style="text-align: center; font-size: 13px;">
			<table border="1px;" style="width: 98%; border-collapse: collapse;">
				<tr>
					<td align="center" colspan="2">
						<font size="4"><b>修改代理商资料</b></font>
					</td>
				</tr>
				<tr>
					<td colspan="2">
						<asp:Label ID="lblMsg" runat="server" Font-Bold="True" ForeColor="Red"></asp:Label></td>
				</tr>
				<tr>
					<td style="width: 200px; text-align: right;">
						代理商帐号:</td>
					<td style="text-align: left;">
						&nbsp;&nbsp;&nbsp;&nbsp;
						<asp:TextBox ID="tbxUser" runat="server" ReadOnly="true" BackColor="Gainsboro" />
					</td>
				</tr>
				<tr>
					<td style="width: 200px; text-align: right;">
						帐号密码:</td>
					<td style="text-align: left; height: 29px;">
						&nbsp;&nbsp;&nbsp;&nbsp;
						<asp:TextBox ID="tbxPassword" runat="server" TextMode="Password" Width="149px" />不修改则留空
					</td>
				</tr>
				<tr>
					<td style="width: 200px; text-align: right;">
						确认帐号密码:</td>
					<td style="text-align: left">
						&nbsp;&nbsp;&nbsp;&nbsp;
						<asp:TextBox ID="tbxPassword2" runat="server" TextMode="Password" Width="149px" />
						</td>
				</tr>
				<tr>
					<td style="width: 200px; text-align: right;">
						二级域名:</td>
					<td style="text-align: left;">
						&nbsp;&nbsp;&nbsp;&nbsp;
						<asp:TextBox ID="tbxDomain" runat="server"  MaxLength="20" />
						由3-20个英文字母或数字组成；不填写则与代理商登录帐号一样&nbsp;&nbsp;
                        <a  href="javascript:OnExsitDomainName();">检测二级域名是否存在</a>
					        <span id="span1" style="color: Red" ></span>
					</td>
				</tr>
                <tr>            
                    <td style="width: 200px;text-align:right;"> 门票比例:</td>
                    <td style="text-align:left">&nbsp;&nbsp;&nbsp;&nbsp;
                    <asp:TextBox ID="tbxSpareValue" runat="server"  Text="0" MaxLength="3" Width="30"/>%<span style="color:red">*</span> 允许的变动范围[<%=ChildSV%>% <= 门票比例 <= <%=ParentSV %>%](请输入整数)</td>                
                </tr>  
				<tr>
					<td style="width: 200px; text-align: right;">
						真实姓名:</td>
					<td style="text-align: left;">
						&nbsp;&nbsp;&nbsp;&nbsp;
						<asp:TextBox ID="tbxName" runat="server" ReadOnly="true" BackColor="Gainsboro" />
					</td>
				</tr>
				<tr>
					<td style="width: 200px; text-align: right;">
						银行名称:</td>
					<td style="text-align: left">
						&nbsp;&nbsp;&nbsp;&nbsp;
						<asp:TextBox ID="tbxBankName" runat="server" ReadOnly="true" BackColor="Gainsboro" /></td>
				</tr>
				<tr>
					<td style="width: 200px; text-align: right;">
						开户名:</td>
					<td style="text-align: left; height: 27px;">
						&nbsp;&nbsp;&nbsp;&nbsp;
						<asp:TextBox ID="tbxAccountName" runat="server" ReadOnly="true" BackColor="Gainsboro" /></td>
				</tr>
				<tr>
					<td style="width: 200px; text-align: right;">
						银行账号:</td>
					<td style="text-align: left">
						&nbsp;&nbsp;&nbsp;&nbsp;
						<asp:TextBox ID="tbxAccountNo" runat="server" ReadOnly="true" BackColor="Gainsboro" />
						
					</td>
				</tr>
				<tr>
					<td style="width: 200px; text-align: right;">
						银行地址:</td>
					<td style="text-align: left; height: 27px;">
						&nbsp;&nbsp;&nbsp;&nbsp;
						<asp:TextBox ID="tbxBankAddress" runat="server" ReadOnly="true" BackColor="Gainsboro" /></td>
				</tr>
				<tr>
					<td style="width: 200px; text-align: right;">
						支付宝账号:</td>
					<td style="text-align: left">
						&nbsp;&nbsp;&nbsp;&nbsp;
						<asp:TextBox ID="tbxPayorNo" runat="server" ReadOnly="true" BackColor="Gainsboro" />
					</td>
				</tr>
				<tr>
					<td style="width: 200px; text-align: right;">
						财付通帐号:</td>
					<td style="text-align: left">
						&nbsp;&nbsp;&nbsp;&nbsp;
						<asp:TextBox ID="txtTenpayNo" runat="server" ReadOnly="true" BackColor="Gainsboro" />
					</td>
				</tr>
				<tr>
					<td style="width: 200px; text-align: right;">
						固定电话:</td>
					<td style="text-align: left">
						&nbsp;&nbsp;&nbsp;&nbsp;
						<asp:TextBox ID="tbxPhone" runat="server" ReadOnly="true" BackColor="Gainsboro" /></td>
				</tr>
				<tr>
					<td style="width: 200px; text-align: right;">
						联系地址:</td>
					<td style="text-align: left">
						&nbsp;&nbsp;&nbsp;&nbsp;
						<asp:TextBox ID="tbxAddress" runat="server" MaxLength="50" ReadOnly="true" BackColor="Gainsboro" /></td>
				</tr>
				<tr>
					<td style="width: 200px; text-align: right;">
						Email:</td>
					<td style="text-align: left">
						&nbsp;&nbsp;&nbsp;&nbsp;
						<asp:TextBox ID="tbxEmail" runat="server" ReadOnly="true" BackColor="Gainsboro" /></td>
				</tr>
				<tr>
					<td style="width: 200px; text-align: right;">
						邮编:</td>
					<td style="text-align: left">
						&nbsp;&nbsp;&nbsp;&nbsp;
						<asp:TextBox ID="tbxPostalCode" runat="server" ReadOnly="true" BackColor="Gainsboro" /></td>
				</tr>
				<tr>
					<td style="width: 200px; text-align: right;">
						手机:</td>
					<td style="text-align: left">
						&nbsp;&nbsp;&nbsp;&nbsp;
						<asp:TextBox ID="tbxMobile" runat="server" ReadOnly="true" BackColor="Gainsboro" /></td>
				</tr>
				<tr>
					<td style="width: 200px; text-align: right;">
						QQ号码:</td>
					<td style="text-align: left; height: 27px;">
						&nbsp;&nbsp;&nbsp;&nbsp;
						<asp:TextBox ID="tbxQQ" runat="server" ReadOnly="true" BackColor="Gainsboro" /></td>
				</tr>
				 
				<tr>
					<td style="width: 200px; text-align: right;">
						备注:</td>
					<td style="text-align: left">
						&nbsp;&nbsp;&nbsp;&nbsp;
						<asp:TextBox runat="server" ID="txtRemark" TextMode="multiLine" Width="250px" Rows="5"></asp:TextBox>最多50个字符
					</td>
				</tr>
				<tr>
					<td colspan="2">
					</td>
				</tr>
				<tr>
					<td colspan="2" align="center">
						<asp:Button ID="btnSave" runat="server" Text=" 修 改 " OnClick="btnSave_Click" OnClientClick="return f_checkIsNull()" />
						<input id="btnBack" type="button" onclick="document.location.href='<%=Utility.Common.UrlValue %>'" value=" 返 回 " />
					</td>
				</tr>
			</table>
		</div>
	</form>
</body>
<script type="text/javascript">
    function OnExsitDomainName(){
        var txt = document.getElementById('<%=tbxDomain.ClientID %>');
        var msg = document.getElementById('span1');
        if(txt.value.trim() == '')
        {
            msg.innerText = '请输入二级域名';
            txt.focus();
            return;
        }
        var reval = '0';
        var urlData = '../../XmlHttpAdmin.aspx?type=updomainexit&name='+escape(txt.value.trim())+'&id=<%=AgencyID %>';
        //alert(urlData);
        try{
            reval = AjaxCall(urlData);
        }catch(e){}
        if(reval=='1'){
            msg.innerText = '抱歉，二级域名已存在';
        }else{
            msg.innerText = '二级域名可以使用';
        }
    }
    
    function f_checkIsNull()
    {
        var _tbxUser = document.getElementById("<%=tbxUser.ClientID%>");
        
        //---------------------
        var tbxPassword = document.getElementById("<%=tbxPassword.ClientID%>");
        if(tbxPassword.value.trim().length>0){
            var tbxPassword2 = document.getElementById("<%=tbxPassword2.ClientID%>");
            if(tbxPassword.value.trim() != tbxPassword2.value.trim()){
                alert('两次输入的密码不一致，请重新输入！');
                tbxPassword2.focus();
                return false;
            }
        }
        
        //--------------------
        var twoName = document.getElementById("<%=tbxDomain.ClientID%>");
        if(twoName.value.trim()==''){
            twoName.value = _tbxUser.value.trim();
        }
        
        if(!/^[0-9a-zA-Z]{3,20}$/.test(twoName.value.trim())){
            alert('二级域名由3-20个英文字母或数字组成，请重新输入');
            twoName.focus();
            return false;
        }
        
        //----------------------
        var txtRemark = document.getElementById("<%=txtRemark.ClientID%>");
        if(txtRemark.value.length>50){
            alert('备注最多只允许输入50个字符');
            txtRemark.focus();
            return false;
        }
        
        return true;
        
    }
</script>
</html>
